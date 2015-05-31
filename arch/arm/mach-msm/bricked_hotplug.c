/*
 * Bricked Hotplug Driver
 *
 * Copyright (c) 2013-2014, Dennis Rassmann <showp1984@gmail.com>
 * Copyright (c) 2013-2014, Pranav Vashi <neobuddy89@gmail.com>
 * Copyright (c) 2010-2014, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#include <linux/powersuspend.h>
#include <linux/init.h>
#include <linux/cpufreq.h>
#include <linux/workqueue.h>
#include <linux/completion.h>
#include <linux/cpu.h>
#include <linux/cpumask.h>
#include <asm-generic/cputime.h>
#include <linux/hrtimer.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/module.h>
#include <linux/device.h>
#include "acpuclock.h"

#define DEBUG 0

#define HOTPLUG_TAG			"[BRICKED]"
#define HOTPLUG_ENABLED			1
#define BRICKED_STARTDELAY		20000
#define BRICKED_DELAY			130
#define DEFAULT_MIN_CPUS_ONLINE		2
#define DEFAULT_MAX_CPUS_ONLINE		NR_CPUS
#define DEFAULT_MAX_CPUS_ONLINE_SUSP	1
#define DEFAULT_SUSPEND_DEFER_TIME	10

#define BRICKED_IDLE_FREQ		422400

enum {
	BRICKED_DISABLED = 0,
	BRICKED_IDLE,
	BRICKED_DOWN,
	BRICKED_UP,
};

static struct delayed_work hotplug_work;
static struct delayed_work suspend_work;
static struct work_struct resume_work;
static struct workqueue_struct *hotplug_wq;
static struct workqueue_struct *susp_wq;

static struct cpu_hotplug {
	unsigned int startdelay;
	unsigned int suspended;
	unsigned int suspend_defer_time;
	unsigned int min_cpus_online_res;
	unsigned int max_cpus_online_res;
	unsigned int max_cpus_online_susp;
	unsigned int delay;
	unsigned long int idle_freq;
	unsigned int max_cpus_online;
	unsigned int min_cpus_online;
	unsigned int bricked_enabled;
	struct mutex bricked_hotplug_mutex;
	struct mutex bricked_cpu_mutex;
} hotplug = {
	.startdelay = BRICKED_STARTDELAY,
	.suspended = 0,
	.suspend_defer_time = DEFAULT_SUSPEND_DEFER_TIME,
	.min_cpus_online_res = DEFAULT_MIN_CPUS_ONLINE,
	.max_cpus_online_res = DEFAULT_MAX_CPUS_ONLINE,
	.max_cpus_online_susp = DEFAULT_MAX_CPUS_ONLINE_SUSP,
	.delay = BRICKED_DELAY,
	.idle_freq = BRICKED_IDLE_FREQ,
	.max_cpus_online = DEFAULT_MAX_CPUS_ONLINE,
	.min_cpus_online = DEFAULT_MIN_CPUS_ONLINE,
	.bricked_enabled = HOTPLUG_ENABLED,
};

static unsigned int NwNs_Threshold[8] = {12, 0, 20, 7, 25, 10, 0, 18};
static unsigned int TwTs_Threshold[8] = {140, 0, 140, 190, 140, 190, 0, 190};

extern unsigned int get_rq_info(void);

unsigned int state = BRICKED_DISABLED;

static unsigned long get_rate(int cpu) {
	return msm_cpufreq_get_freq(cpu);
}

static int get_slowest_cpu(void) {
	int i, cpu = 0;
	unsigned long rate, slow_rate = 0;

	for (i = 1; i < DEFAULT_MAX_CPUS_ONLINE; i++) {
		if (!cpu_online(i))
			continue;
		rate = get_rate(i);
		if (slow_rate == 0) {
			cpu = i;
			slow_rate = rate;
			continue;
		}
		if ((rate <= slow_rate) && (slow_rate != 0)) {
			cpu = i;
			slow_rate = rate;
		}
	}

	return cpu;
}

static unsigned long get_slowest_cpu_rate(void) {
	int i = 0;
	unsigned long rate, slow_rate = 0;

	for (i = 0; i < DEFAULT_MAX_CPUS_ONLINE; i++) {
		if (!cpu_online(i))
			continue;
		rate = get_rate(i);
		if ((rate < slow_rate) && (slow_rate != 0)) {
			slow_rate = rate;
			continue;
		}
		if (slow_rate == 0) {
			slow_rate = rate;
		}
	}

	return slow_rate;
}

static int mp_decision(void) {
	static bool first_call = true;
	int new_state = BRICKED_IDLE;
	int nr_cpu_online;
	int index;
	unsigned int rq_depth;
	static cputime64_t total_time = 0;
	static cputime64_t last_time;
	cputime64_t current_time;
	cputime64_t this_time = 0;

	if (!hotplug.bricked_enabled)
		return BRICKED_DISABLED;

	current_time = ktime_to_ms(ktime_get());

	if (first_call) {
		first_call = false;
	} else {
		this_time = current_time - last_time;
	}
	total_time += this_time;

	rq_depth = get_rq_info();
	nr_cpu_online = num_online_cpus();

	if (nr_cpu_online) {
		index = (nr_cpu_online - 1) * 2;
		if ((nr_cpu_online < DEFAULT_MAX_CPUS_ONLINE) && (rq_depth >= NwNs_Threshold[index])) {
			if ((total_time >= TwTs_Threshold[index]) &&
				(nr_cpu_online < hotplug.max_cpus_online)) {
				new_state = BRICKED_UP;
				if (get_slowest_cpu_rate() <=  hotplug.idle_freq)
					new_state = BRICKED_IDLE;
			}
		} else if ((nr_cpu_online > 1) && (rq_depth <= NwNs_Threshold[index+1])) {
			if ((total_time >= TwTs_Threshold[index+1]) &&
				(nr_cpu_online > hotplug.min_cpus_online)) {
				new_state = BRICKED_DOWN;
				if (get_slowest_cpu_rate() > hotplug.idle_freq)
					new_state = BRICKED_IDLE;
			}
		} else {
			new_state = BRICKED_IDLE;
			total_time = 0;
		}
	} else {
		total_time = 0;
	}

	if (new_state != BRICKED_IDLE) {
		total_time = 0;
	}

	last_time = ktime_to_ms(ktime_get());
#if DEBUG
	pr_info(HOTPLUG_TAG"[DEBUG MASK] rq: %u, new_state: %i | Mask=[%d%d%d%d]",
			rq_depth, new_state, cpu_online(0), cpu_online(1), cpu_online(2), cpu_online(3));
	pr_info(HOTPLUG_TAG"[DEBUG RATE] CPU0 rate: %lu | CPU1 rate: %lu | CPU2 rate: %lu | CPU3 rate: %lu",
			get_rate(0), get_rate(1), get_rate(2), get_rate(3));
#endif
	return new_state;
}

static void __ref bricked_hotplug_work(struct work_struct *work) {
	unsigned int cpu;

	if (hotplug.suspended && hotplug.max_cpus_online_susp <= 1)
		goto out;

	if (!mutex_trylock(&hotplug.bricked_cpu_mutex))
		goto out;

	state = mp_decision();
	switch (state) {
	case BRICKED_DISABLED:
	case BRICKED_IDLE:
		break;
	case BRICKED_DOWN:
		cpu = get_slowest_cpu();
		if (cpu > 0) {
			if (cpu_online(cpu))
				cpu_down(cpu);
		}
		break;
	case BRICKED_UP:
		cpu = cpumask_next_zero(0, cpu_online_mask);
		if (cpu < DEFAULT_MAX_CPUS_ONLINE) {
			if (!cpu_online(cpu))
				cpu_up(cpu);
		}
		break;
	default:
		pr_err(HOTPLUG_TAG": %s: invalid mpdec hotplug state %d\n",
			__func__, state);
	}
	mutex_unlock(&hotplug.bricked_cpu_mutex);

out:
	if (hotplug.bricked_enabled)
		queue_delayed_work(hotplug_wq, &hotplug_work,
					msecs_to_jiffies(hotplug.delay));
	return;
}

static void bricked_hotplug_suspend(struct work_struct *work)
{
	int cpu;

	if (!hotplug.bricked_enabled)
		return;

	mutex_lock(&hotplug.bricked_hotplug_mutex);
	hotplug.suspended = 1;
	hotplug.min_cpus_online_res = hotplug.min_cpus_online;
	hotplug.min_cpus_online = 1;
	hotplug.max_cpus_online_res = hotplug.max_cpus_online;
	hotplug.max_cpus_online = hotplug.max_cpus_online_susp;
	mutex_unlock(&hotplug.bricked_hotplug_mutex);

	if (hotplug.max_cpus_online_susp > 1) {
		pr_info(HOTPLUG_TAG": Screen -> off\n");
		return;
	}

	/* main work thread can sleep now */
	cancel_delayed_work_sync(&hotplug_work);

	for_each_possible_cpu(cpu) {
		if ((cpu >= 1) && (cpu_online(cpu)))
			cpu_down(cpu);
	}

	pr_info(HOTPLUG_TAG": Screen -> off. Deactivated bricked hotplug. | Mask=[%d%d%d%d]\n",
			cpu_online(0), cpu_online(1), cpu_online(2), cpu_online(3));
}

static void __ref bricked_hotplug_resume(struct work_struct *work)
{
	int cpu, required_reschedule = 0, required_wakeup = 0;

	if (!hotplug.bricked_enabled)
		return;

	if (hotplug.suspended) {
		mutex_lock(&hotplug.bricked_hotplug_mutex);
		hotplug.suspended = 0;
		hotplug.min_cpus_online = hotplug.min_cpus_online_res;
		hotplug.max_cpus_online = hotplug.max_cpus_online_res;
		mutex_unlock(&hotplug.bricked_hotplug_mutex);
		required_wakeup = 1;
		/* Initiate hotplug work if it was cancelled */
		if (hotplug.max_cpus_online_susp <= 1) {
			required_reschedule = 1;
			INIT_DELAYED_WORK(&hotplug_work, bricked_hotplug_work);
		}
	}

	if (required_wakeup) {
		/* Fire up all CPUs */
		for_each_cpu_not(cpu, cpu_online_mask) {
			if (cpu == 0)
				continue;
			cpu_up(cpu);
		}
	}

	/* Resume hotplug workqueue if required */
	if (required_reschedule) {
		queue_delayed_work(hotplug_wq, &hotplug_work, 0);
		pr_info(HOTPLUG_TAG": Screen -> on. Activated bricked hotplug. | Mask=[%d%d%d%d]\n",
				cpu_online(0), cpu_online(1), cpu_online(2), cpu_online(3));
	}
}

static void __bricked_hotplug_suspend(struct power_suspend *handler)
{
	INIT_DELAYED_WORK(&suspend_work, bricked_hotplug_suspend);
	queue_delayed_work_on(0, susp_wq, &suspend_work,
				msecs_to_jiffies(hotplug.suspend_defer_time * 1000));
}

static void __bricked_hotplug_resume(struct power_suspend *handler)
{
	flush_workqueue(susp_wq);
	cancel_delayed_work_sync(&suspend_work);
	queue_work_on(0, susp_wq, &resume_work);
}

static struct power_suspend bricked_hotplug_power_suspend_driver = {
	.suspend = __bricked_hotplug_suspend,
	.resume = __bricked_hotplug_resume,
};

static int bricked_hotplug_start(void)
{
	int ret = 0;

	hotplug_wq = alloc_workqueue(
						"bricked_hotplug_wq",
						WQ_UNBOUND | WQ_RESCUER | WQ_FREEZABLE,
						1
						);
	if (!hotplug_wq) {
		ret = -ENOMEM;
		goto err_out;
	}

	susp_wq =
	    alloc_workqueue("susp_wq", WQ_FREEZABLE, 0);
	if (!susp_wq) {
		pr_err("%s: Failed to allocate suspend workqueue\n",
		       HOTPLUG_TAG);
		ret = -ENOMEM;
		goto err_out;
	}

	mutex_init(&hotplug.bricked_cpu_mutex);
	mutex_init(&hotplug.bricked_hotplug_mutex);

	register_power_suspend(&bricked_hotplug_power_suspend_driver);

	INIT_DELAYED_WORK(&hotplug_work, bricked_hotplug_work);
	INIT_DELAYED_WORK(&suspend_work, bricked_hotplug_suspend);
	INIT_WORK(&resume_work, bricked_hotplug_resume);

	if (hotplug.bricked_enabled)
		queue_delayed_work(hotplug_wq, &hotplug_work,
					msecs_to_jiffies(hotplug.startdelay));

	return ret;
err_out:
	hotplug.bricked_enabled = 0;
	return ret;
}

static void bricked_hotplug_stop(void)
{
	int cpu;

	flush_workqueue(susp_wq);
	cancel_work_sync(&resume_work);
	cancel_delayed_work_sync(&suspend_work);
	cancel_delayed_work_sync(&hotplug_work);
	mutex_destroy(&hotplug.bricked_hotplug_mutex);
	mutex_destroy(&hotplug.bricked_cpu_mutex);
	destroy_workqueue(susp_wq);
	destroy_workqueue(hotplug_wq);

	unregister_power_suspend(&bricked_hotplug_power_suspend_driver);

	/* Put all sibling cores to sleep */
	for_each_online_cpu(cpu) {
		if (cpu == 0)
			continue;
		cpu_down(cpu);
	}
}

/**************************** SYSFS START ****************************/

#define show_one(file_name, object)					\
static ssize_t show_##file_name						\
(struct device *dev, struct device_attribute *bricked_hotplug_attrs,	\
 char *buf)								\
{									\
	return sprintf(buf, "%u\n", hotplug.object);			\
}

show_one(startdelay, startdelay);
show_one(delay, delay);
show_one(min_cpus_online, min_cpus_online);
show_one(max_cpus_online, max_cpus_online);
show_one(max_cpus_online_susp, max_cpus_online_susp);
show_one(suspend_defer_time, suspend_defer_time);
show_one(bricked_enabled, bricked_enabled);

#define define_one_twts(file_name, arraypos)				\
static ssize_t show_##file_name						\
(struct device *dev, struct device_attribute *bricked_hotplug_attrs,	\
 char *buf)								\
{									\
	return sprintf(buf, "%u\n", TwTs_Threshold[arraypos]);		\
}									\
static ssize_t store_##file_name					\
(struct device *dev, struct device_attribute *bricked_hotplug_attrs,	\
 const char *buf, size_t count)						\
{									\
	unsigned int input;						\
	int ret;							\
	ret = sscanf(buf, "%u", &input);				\
	if (ret != 1)							\
		return -EINVAL;						\
	TwTs_Threshold[arraypos] = input;				\
	return count;							\
}									\
static DEVICE_ATTR(file_name, 644, show_##file_name, store_##file_name);
define_one_twts(twts_threshold_0, 0);
define_one_twts(twts_threshold_1, 1);
define_one_twts(twts_threshold_2, 2);
define_one_twts(twts_threshold_3, 3);
define_one_twts(twts_threshold_4, 4);
define_one_twts(twts_threshold_5, 5);
define_one_twts(twts_threshold_6, 6);
define_one_twts(twts_threshold_7, 7);

#define define_one_nwns(file_name, arraypos)				\
static ssize_t show_##file_name						\
(struct device *dev, struct device_attribute *bricked_hotplug_attrs,	\
 char *buf)								\
{									\
	return sprintf(buf, "%u\n", NwNs_Threshold[arraypos]);		\
}									\
static ssize_t store_##file_name					\
(struct device *dev, struct device_attribute *bricked_hotplug_attrs,	\
 const char *buf, size_t count)						\
{									\
	unsigned int input;						\
	int ret;							\
	ret = sscanf(buf, "%u", &input);				\
	if (ret != 1)							\
		return -EINVAL;						\
	NwNs_Threshold[arraypos] = input;				\
	return count;							\
}									\
static DEVICE_ATTR(file_name, 644, show_##file_name, store_##file_name);
define_one_nwns(nwns_threshold_0, 0);
define_one_nwns(nwns_threshold_1, 1);
define_one_nwns(nwns_threshold_2, 2);
define_one_nwns(nwns_threshold_3, 3);
define_one_nwns(nwns_threshold_4, 4);
define_one_nwns(nwns_threshold_5, 5);
define_one_nwns(nwns_threshold_6, 6);
define_one_nwns(nwns_threshold_7, 7);

static ssize_t show_idle_freq (struct device *dev,
				struct device_attribute *bricked_hotplug_attrs,
				char *buf)
{
	return sprintf(buf, "%lu\n", hotplug.idle_freq);
}

static ssize_t store_startdelay(struct device *dev,
				struct device_attribute *bricked_hotplug_attrs,
				const char *buf, size_t count)
{
	unsigned int input;
	int ret;
	ret = sscanf(buf, "%u", &input);
	if (ret != 1)
		return -EINVAL;

	hotplug.startdelay = input;

	return count;
}

static ssize_t store_delay(struct device *dev,
				struct device_attribute *bricked_hotplug_attrs,
				const char *buf, size_t count)
{
	unsigned int input;
	int ret;
	ret = sscanf(buf, "%u", &input);
	if (ret != 1)
		return -EINVAL;

	hotplug.delay = input;

	return count;
}

static ssize_t store_idle_freq(struct device *dev,
				struct device_attribute *bricked_hotplug_attrs,
				const char *buf, size_t count)
{
	long unsigned int input;
	int ret;
	ret = sscanf(buf, "%lu", &input);
	if (ret != 1)
		return -EINVAL;

	hotplug.idle_freq = input;

	return count;
}

static ssize_t __ref store_min_cpus_online(struct device *dev,
				struct device_attribute *bricked_hotplug_attrs,
				const char *buf, size_t count)
{
	unsigned int input, cpu;
	int ret;
	ret = sscanf(buf, "%u", &input);
	if ((ret != 1) || input < 1 || input > DEFAULT_MAX_CPUS_ONLINE)
		return -EINVAL;

	if (hotplug.max_cpus_online < input)
		hotplug.max_cpus_online = input;

	hotplug.min_cpus_online = input;

	if (!hotplug.bricked_enabled)
		return count;

	if (num_online_cpus() < hotplug.min_cpus_online) {
		for (cpu = 1; cpu < DEFAULT_MAX_CPUS_ONLINE; cpu++) {
			if (num_online_cpus() >= hotplug.min_cpus_online)
				break;
			if (cpu_online(cpu))
				continue;
			cpu_up(cpu);
		}
		pr_info(HOTPLUG_TAG": min_cpus_online set to %u. Affected CPUs were hotplugged!\n", input);
	}

	return count;
}

static ssize_t store_max_cpus_online(struct device *dev,
				struct device_attribute *bricked_hotplug_attrs,
				const char *buf, size_t count)
{
	unsigned int input, cpu;
	int ret;
	ret = sscanf(buf, "%u", &input);
	if ((ret != 1) || input < 1 || input > DEFAULT_MAX_CPUS_ONLINE)
			return -EINVAL;

	if (hotplug.min_cpus_online > input)
		hotplug.min_cpus_online = input;

	hotplug.max_cpus_online = input;

	if (!hotplug.bricked_enabled)
		return count;

	if (num_online_cpus() > hotplug.max_cpus_online) {
		for (cpu = DEFAULT_MAX_CPUS_ONLINE; cpu > 0; cpu--) {
			if (num_online_cpus() <= hotplug.max_cpus_online)
				break;
			if (!cpu_online(cpu))
				continue;
			cpu_down(cpu);
		}
		pr_info(HOTPLUG_TAG": max_cpus set to %u. Affected CPUs were unplugged!\n", input);
	}

	return count;
}

static ssize_t store_max_cpus_online_susp(struct device *dev,
				struct device_attribute *bricked_hotplug_attrs,
				const char *buf, size_t count)
{
	unsigned int input;
	int ret;
	ret = sscanf(buf, "%u", &input);
	if ((ret != 1) || input < 1 || input > DEFAULT_MAX_CPUS_ONLINE)
			return -EINVAL;

	hotplug.max_cpus_online_susp = input;

	return count;
}

static ssize_t store_suspend_defer_time(struct device *dev,
				    struct device_attribute *bricked_hotplug_attrs,
				    const char *buf, size_t count)
{
	int ret;
	unsigned int val;

	ret = sscanf(buf, "%u", &val);
	if (ret != 1)
		return -EINVAL;

	hotplug.suspend_defer_time = val;

	return count;
}

static ssize_t store_bricked_enabled(struct device *dev,
				struct device_attribute *bricked_hotplug_attrs,
				const char *buf, size_t count)
{
	unsigned int input;
	int ret;
	ret = sscanf(buf, "%u", &input);
	if (ret != 1)
		return -EINVAL;

	if (input > 1)
		input = 1;

	if (input == hotplug.bricked_enabled)
		return count;

	hotplug.bricked_enabled = input;

	if (!hotplug.bricked_enabled) {
		state = BRICKED_DISABLED;
		bricked_hotplug_stop();
		pr_info(HOTPLUG_TAG": Disabled\n");
	} else {
		state = BRICKED_IDLE;
		bricked_hotplug_start();
		pr_info(HOTPLUG_TAG": Enabled\n");
	}

	return count;
}

static DEVICE_ATTR(startdelay, 644, show_startdelay, store_startdelay);
static DEVICE_ATTR(delay, 644, show_delay, store_delay);
static DEVICE_ATTR(idle_freq, 644, show_idle_freq, store_idle_freq);
static DEVICE_ATTR(min_cpus_online, 644, show_min_cpus_online, store_min_cpus_online);
static DEVICE_ATTR(max_cpus_online, 644, show_max_cpus_online, store_max_cpus_online);
static DEVICE_ATTR(max_cpus_online_susp, 644, show_max_cpus_online_susp, store_max_cpus_online_susp);
static DEVICE_ATTR(suspend_defer_time, 644, show_suspend_defer_time, store_suspend_defer_time);
static DEVICE_ATTR(enabled, 644, show_bricked_enabled, store_bricked_enabled);

static struct attribute *bricked_hotplug_attrs[] = {
	&dev_attr_startdelay.attr,
	&dev_attr_delay.attr,
	&dev_attr_idle_freq.attr,
	&dev_attr_min_cpus_online.attr,
	&dev_attr_max_cpus_online.attr,
	&dev_attr_max_cpus_online_susp.attr,
	&dev_attr_suspend_defer_time.attr,
	&dev_attr_enabled.attr,
	&dev_attr_twts_threshold_0.attr,
	&dev_attr_twts_threshold_1.attr,
	&dev_attr_twts_threshold_2.attr,
	&dev_attr_twts_threshold_3.attr,
	&dev_attr_twts_threshold_4.attr,
	&dev_attr_twts_threshold_5.attr,
	&dev_attr_twts_threshold_6.attr,
	&dev_attr_twts_threshold_7.attr,
	&dev_attr_nwns_threshold_0.attr,
	&dev_attr_nwns_threshold_1.attr,
	&dev_attr_nwns_threshold_2.attr,
	&dev_attr_nwns_threshold_3.attr,
	&dev_attr_nwns_threshold_4.attr,
	&dev_attr_nwns_threshold_5.attr,
	&dev_attr_nwns_threshold_6.attr,
	&dev_attr_nwns_threshold_7.attr,
	NULL,
};

static struct attribute_group attr_group = {
	.attrs = bricked_hotplug_attrs,
	.name = "conf",
};

/**************************** SYSFS END ****************************/

static int __devinit bricked_hotplug_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct kobject *bricked_kobj;

	bricked_kobj =
		kobject_create_and_add("bricked_hotplug", kernel_kobj);
	if (!bricked_kobj) {
		pr_err("%s kobject create failed!\n",
			__func__);
		return -ENOMEM;
        }

	ret = sysfs_create_group(bricked_kobj,
			&attr_group);

        if (ret) {
		pr_err("%s bricked_kobj create failed!\n",
			__func__);
		goto err_dev;
	}

	if (hotplug.bricked_enabled) {
		ret = bricked_hotplug_start();
		if (ret != 0)
			goto err_dev;
	}

	return ret;
err_dev:
	if (bricked_kobj != NULL)
		kobject_put(bricked_kobj);
	return ret;
}

static struct platform_device bricked_hotplug_device = {
	.name = HOTPLUG_TAG,
	.id = -1,
};

static int bricked_hotplug_remove(struct platform_device *pdev)
{
	if (hotplug.bricked_enabled)
		bricked_hotplug_stop();

	return 0;
}

static struct platform_driver bricked_hotplug_driver = {
	.probe = bricked_hotplug_probe,
	.remove = bricked_hotplug_remove,
	.driver = {
		.name = HOTPLUG_TAG,
		.owner = THIS_MODULE,
	},
};

static int __init bricked_init(void)
{
	int ret = 0;

	ret = platform_driver_register(&bricked_hotplug_driver);
	if (ret) {
		pr_err("%s: Driver register failed: %d\n", HOTPLUG_TAG, ret);
		return ret;
	}

	ret = platform_device_register(&bricked_hotplug_device);
	if (ret) {
		pr_err("%s: Device register failed: %d\n", HOTPLUG_TAG, ret);
		return ret;
	}

	pr_info(HOTPLUG_TAG": %s init complete.", __func__);

	return ret;
}

void bricked_exit(void)
{
	platform_device_unregister(&bricked_hotplug_device);
	platform_driver_unregister(&bricked_hotplug_driver);
}

late_initcall(bricked_init);
module_exit(bricked_exit);

MODULE_AUTHOR("Pranav Vashi <neobuddy89@gmail.com>");
MODULE_DESCRIPTION("Bricked Hotplug Driver");
MODULE_LICENSE("GPLv2");
