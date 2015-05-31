#ifdef	__SR030PC50_H__
#define __SR030PC50_H__

static const u16 sr030pc50_Init_Reg[] = {
0x0300,
0x0171,
0x0173,
0x0171,


// PLL Setting 
0x0300,                                     

0x080f, //Parallel NO Output_PAD Out
0x1000,
0x1190,
0x1200,
0x1488,

0x0baa,                                                             
0x0caa,                                                             
0x0daa,                                                             
                                                                    
0xc095,                                     
0xc118,                                     
0xc291,                                     
0xc300,                                     
0xc401,   

0x0320, //page 20                                                   
0x100c, //ae off                                                    
0x0322, //page 22                                                   
0x107b, //awb off                                                   
                                                                    
0x0300,
0x1200,
0x2000,
0x2104,
0x2200,
0x2304,

0x4000, //Hblank 144                                                
0x4190,                                                             
0x4200, //Vblank 129
0x4381, 

//BLC
0x802e, //don't touch
0x817e, //don't touch
0x8290, //don't touch
0x8330, //don't touch
0x842c, //don't touch
0x854b, //don't touch
0x8601, //don't touch
0x8847, //don't touch
//0x8948,//BLC hold

0x900f, //BLC_TIME_TH_ON
0x910f, //BLC_TIME_TH_OFF
0x9298, //BLC_AG_TH_ON
0x9390, //BLC_AG_TH_OFF

0x9838, //don't touch
0x9940, //Out BLC
0xa040, //Dark BLC
0xa844, //Normal BLC 44

//Page2 Last Update 12_01_20
0x0302,
0x1000,
0x1100,
0x1340, 
0x1404, 
0x181c,
0x1900, //01
0x1a00,
0x1b08,
0x1c9c,
0x1d03,
0x2033,
0x2177,
0x22a7,
0x2332,
0x2433,
0x2b40,
0x2d32,
0x3199,
0x3200,
0x3300,
0x343c,
0x350d,
0x3b60, //80

//timing control 1 // //don't touch
0x5021,
0x511c,
0x52aa,
0x535a,
0x5430,
0x5510,
0x560c,
0x5800,
0x590f,

//timing control 2 // //don't touch
0x6034,
0x613a,
0x6234,
0x6339,
0x6434,
0x6539,
0x7235,
0x7338,
0x7435,
0x7538,
0x8002,
0x812e,
0x820d,
0x8310,
0x840d,
0x8510,
0x921d,
0x9320,
0x941d,
0x9520,
0xa003,
0xa12d,
0xa42d,
0xa503,
0xa812,
0xa91b,
0xaa22,
0xab2b,
0xac10,
0xad0e,
0xb833,
0xb935,
0xbc0c,
0xbd0e,
0xc03a,
0xc13f,
0xc23a,
0xc33f,
0xc43a,
0xc53e,
0xc63a,
0xc73e,
0xc83a,
0xc93e,
0xca3a,
0xcb3e,
0xcc3b,
0xcd3d,
0xce3b,
0xcf3d,
0xd033,
0xd13f,

//Page 10
0x0310,
0x1001, //03, //ISPCTL1, YUV ORDER(FIX)
0x1143,
0x1230, //Y offet, dy offseet enable
0x4080,
0x4102, //00 DYOFS  00->10  _100318
0x4885, //Contrast  88->84  _100318
0x5048, //AGBRT

0x6001, //7f //7c
0x6100, //Use default
0x627e, //80 SATB_B  (1.4x)
0x637c, //80 SATR_R  (1.2x)
0x6448, //AGSAT
0x6690, //wht_th2
0x6736, //wht_gain  Dark (0.4x), Normal (0.75x)

0x8000,

//Page 11
//LPF
0x0311,
0x1025,
0x1107,
0x2000,
0x2160,
0x230a,
0x6013,
0x6185,
0x6200,
0x6300,
0x6400,

0x6770,
0x6824,
0x6904,

//Page 12
//2D
0x0312,
0x40d3,
0x4109,
0x5018,
0x5124,
0x701f,
0x7100,
0x7200,
0x7300,
0x7412,
0x7512,
0x7620,
0x7780,
0x7888,
0x7918,

///////////////////////
0x903d,
0x9134,
0x9928,
0x9c05, //14 For defect
0x9d08, //15 For defect
0x9e28,
0x9f28,

0xb07d, //75 White Defect
0xb544,
0xb682,
0xb752,
0xb844,
0xb915,
///////////////////////

//Edge
0x0313,
0x1001,
0x1189,
0x1214,
0x1319,
0x1408,
0x2003,
0x2104,
0x2325,
0x2421,
0x2508,
0x2640,
0x2700,
0x2808,
0x2950,
0x2ae0,
0x2b10,
0x2c28,
0x2d40,
0x2e00,
0x2f00,
0x3011,
0x8005,
0x8107,
0x9004,
0x9105,
0x9200,
0x9330,
0x9430,
0x9510,

0x0314,
0x1001,

0x2244,  //54,
0x2334,  //41,
0x2432,  //40, //30

0x2758, //60 RXCEN
0x2880, //RYCEN
0x2958, //60 GXCEN
0x2a80, //GYCEN
0x2b58, //60 BXCEN
0x2c80, //BYCEN

//15page//////////////////////////
0x0315,
0x1003,

0x1452,
0x163a,
0x172f,

//CMC
0x30f1,
0x3171,
0x3200,
0x331f,
0x34e1,
0x3542,
0x3601,
0x3731,
0x3872,
//CMC OFS
0x4090,
0x4182,
0x4212,
0x4386,
0x4492,
0x4518,
0x4684,
0x4702,
0x4802,

0x0316,
0x1001,
0x3000,
0x310d,
0x321b,
0x332b,  //2d,
0x3452,  //4e,
0x3576,  //6f,
0x368e,  //86,
0x37a3,  //9d,
0x38b7,  //af,
0x39c7,  //c0,
0x3ad5,  //cf,
0x3be7,  //e2,
0x3cf3,  //f0,    
0x3df9,    
0x3eff,    

//Page 17 AE 
0x0317,
0xc43c,
0xc532,

//Page 20 AE 
0x0320,
0x100c,
0x1104,

0x2001,
0x2827,
0x29a1,

0x2af0,
0x2bf4,
0x2c2b, 

0x30f8,

0x3b22,
0x3cde,

0x3922,
0x3ade,
0x3b22, //23->22 _10_04_06 hhzin
0x3cde,

0x6070, //70
0x6100, //11 //22

0x6270,
0x6300, //11 //22

0x682c,// x no Flip 34
0x696e,// x no Flip 66
0x6A27,
0x6Bbb,

0x7034,//Y Targe 32

0x7611, //Unlock bnd1
0x7772, //Unlock bnd2 02->a2 _10_04_06 hhzin

0x7812, //Yth 1
0x7926, //Yth 2 26->27 _10_04_06 hhzin
0x7a23, //Yth 3

0x7c17, //1c->1d _10_04_06 hhzin
0x7d22,

//60Hz
0x8300, //EXP Normal 30.00 fps 
0x84c3,                                                             
0x8550,                                                             

0x8600, //EXPMin 7500.00 fps                                        
0x87c8,                                                             

0x8802, //EXP Max(120Hz) 8.00 fps 
0x89dc, 
0x8a6c, 
0xa002, //EXP Max(100Hz) 8.33 fps 
0xa1bf, 
0xa220,                                                            

0x8B3a, //EXP100                                                    
0x8C98,                                                             
0x8D30, //EXP120                                                    
0x8Ed4,                                                             

0x988C,
0x9923,

0x9c07, //EXP Limit 833.33 fps 
0x9d08,
0x9e00, //EXP Unit 
0x9fc8,                                                             

0xb01d,
0xb114,
0xb2a0, //80
0xb317, //AGLVL //17
0xb417,
0xb53e,
0xb62b,
0xb724,
0xb821,
0xb91f,
0xba1e,
0xbb1d,
0xbc1c,
0xbd1b,

0xc01a,
0xc348,
0xc448,

//Page 22 AWB
0x0322,
0x10e2,
0x112e, //2e
0x2075, //01 //69
0x2180,
0x24fe,

0x3080, //Cb
0x3180, //Cr
0x3811, //Lock Boundary //13
0x3933,
0x40e3, //f0
0x4143,
0x4233,
0x43f3,
0x4444,
0x4566,
0x4608,
0x4763,

0x803d, //3a //3c
0x8120,
0x8240,

0x835a, //RMAX 5a
0x8420, //22 RMIN 23
0x8556, //BMAX 5a
0x8624, //BMIN 

0x8748, //42
0x883a,
0x893e,
0x8a34,

0x8b00, //OUT TH
0x8d24, //21 //22
0x8e41, //41

0x8f63,
0x9062,
0x915e,
0x925a,
0x9350,
0x9442,
0x953b,
0x9634,
0x972d,
0x982b,
0x9929,
0x9a27,
0x9b0b,
0xb47f,
                  
///////////////////////////// Page 48
0x0348,

0x1005,
0x1100, //async_fifo off
0x1200,

0x16c4,
0x1700,
0x1900,
0x1a00,
0x1c02,
0x1d04,
0x1e07,
0x1f06,
0x2000,
0x21b8,
0x2200,
0x2301,

0x3005,
0x3100,
0x3402,
0x3206,
0x3503,
0x3601,
0x3703,
0x3800,
0x394a, 
0x3c00,
0x3dfa,
0x3f10,
0x4000,
0x4120,
0x4200,

0x0322,
0x10fb,

0x0320,
0x108c,

0x0170,
};

static const u16 sr030pc50_stop_stream[]  = {
0x0300,
0x0171,
};

static const u16 sr030pc50_start_stream[]  = {
0x0300,
0x0170,
};

static const u16 sr030pc50_Capture[]  = {
0xff03,
};
static const u16 sr030pc50_i2c_check[]  = {
0x0300,
0x1000,

0xff0a,

};
static const u16 sr030pc50_fps_Auto[]  = {
0x0300,
0x01f1,
0x1190,

0x4000,
0x4190,
0x4200,
0x4380,

0x0320,
0x100c,

0x2af0,
0x2b34,
0x3078,

0x8300,
0x84c3,
0x8550,

0x8802,
0x89dc,
0x8a6c,

0x108c,
0x0300,
0x1190,
0x01f0,
};


static const u16 sr030pc50_25_fps_50Hz[]  = {
0x0300,
0x0171,
0x1190,

0x4000,
0x4190,
0x4200,
0x4314, // 20

0x9003,
0x9103,
0x9298,
0x9390,

0x0320,
0x101c, // ae off

0x2a90,
0x2bf5,
0x30f8,

0x8300, // exp normal 33.33
0x84af,
0x85c8,

0xa000, // exp max 33.33
0xa1af,
0xa2c8,

0x9100, // exp fix 25fps
0x92ea,
0x9360,

0x109c, // ae on
0x0300,
0x1194,
0x0170,
};

static const u16 sr030pc50_15_fps_50Hz[]  = {
0x0300,
0x0171,
0x1190,

0x4000, //Hblank 144
0x4190, 
0x4200, //Vblank 20
0x4314, 

0x9003, //BLC_TIME_TH_ON
0x9103, //BLC_TIME_TH_OFF 
0x9298, //BLC_AG_TH_ON
0x9390, //BLC_AG_TH_OFF


0x0320,
0x101c, // ae off

0x2a90, 
0x2bf5, 
0x30f8,

0x8300, /*EXP Normal 33.33 fps*/
0x84af, 
0x85c8, 

0xa001, //EXP Max(100Hz) 16.67 fps 
0xa15f, 
0xa290, 

0x9101, //EXP Fix 15.00 fps
0x9286, 
0x93a0, 

0x109c, //ae on
0x0300,
0x1194,
0x0170,
};

static const u16 sr030pc50_24_fps_60Hz[]  = {
0x0300,
0x0171,
0x1190,

0x4000, //Hblank 144
0x4190, 
0x4200, //Vblank 20
0x4314, 


0x9004,
0x9104,
0x9298,
0x9390,

0x0320,
0x100c, //AE Off

0x2a90,
0x2bf5,
0x30f8,

0x8300, //EXP Normal 30.00 fps
0x84c3,
0x8550,

0x8800, //EXP Max 120Hz 30 fps
0x89c3,
0x8a50,

0x9100, //EXP Fix 24.00 fps
0x92f4,
0x9324,

0x108c, //AE On
0x0300,
0x1194,
0x0170,
};

static const u16 sr030pc50_15_fps_60Hz[]  = {
0x0300,
0x0171,
0x1190,

0x4000, //Hblank 144
0x4190, 
0x4200, //Vblank 20
0x4314, 


0x0320,
0x100c,

0x2a90,
0x2bf5,
0x30f8,

0x8300, //EXP Normal 30.00 fps
0x84c3,
0x8550,


0x8801, //EXP Max(120Hz) 17.14 fps 
0x8955, 
0x8acc, 


0x9101, // EXP Fix 15.00 fps
0x9286,
0x93a0,

0x108c,
0x0300,
0x1194,
0x0170,
};

static const u16 sr030pc50_brightness_M4[] = {
0x0310,
0x40d0,
};

static const u16 sr030pc50_brightness_M3[] = {
0x0310,
0x40B0,
};

static const u16 sr030pc50_brightness_M2[] = {
0x0310,
0x40A0,
};

static const u16 sr030pc50_brightness_M1[] = {
0x0310,
0x4090,

};

static const u16 sr030pc50_brightness_default[] = {
0x0310,
0x4080,
};

static const u16 sr030pc50_brightness_P1[] = {
0x0310,
0x4010,
};

static const u16 sr030pc50_brightness_P2[] = {
0x0310,
0x4020,
};

static const u16 sr030pc50_brightness_P3[] = {
0x0310,
0x4030,
};

static const u16 sr030pc50_brightness_P4[] = {
0x0310,
0x4050,
};

static const u16 sr030pc50_640x480[] = {
0x0300,
0x1000,

0x2000,
0x2104,
0x2200,
0x2304,

0x2401,
0x25e0,

0x2602,
0x2780,

0xc291,

0x0348,
0x3005,
0x3100,
};
static const u16 sr030pc50_320x240[] = {
0x0300,
0x1010,

0x2000,
0x2104,
0x2200,
0x2304,

0x2401,
0x25e0,

0x2602,
0x2780,

0xc295,

0x0348,
0x3002,
0x3180,
};

static const u16 sr030pc50_flip_off_No15fps[] = {
0x0300,
0x1194, /*0x91 : mirror mode*/
};

static const u16 sr030pc50_flip_off[] = {
0x0300,
0x1190, /*0x91 : mirror mode*/
};

static const u16 sr030pc50_hflip_No15fps[] = {
0x0300,
0x1195, /*0x91 : mirror mode*/
};

static const u16 sr030pc50_hflip[] = {
0x0300,
0x1191, /*0x91 : mirror mode*/
};

/* Effect Setting */
static const u16 sr030pc50_effect_none[] = {
0x0310,
0x1103,
0x1230,
0x0313,
0x103b,
0x2002,
};
static const u16 sr030pc50_effect_gray[] = {
0x0310,
0x1103,
0x1230,
0xff03,
0x4480,
0x4580,
0x1233,
0x0313,
0x103b,
0x2002,	
};
static const u16 sr030pc50_effect_sepia[] = {
0x0310,
0x1103,
0x1230,
0xff03,
0x4470,
0x4598,
0x1233,
0x0313,
0x103b,
0x2002,	
};
static const u16 sr030pc50_effect_negative[] = {
0x0310,
0x1103,
0x1238,
0x0313,
0x103b,
0x2002,
};

static const unsigned short sr030pc50_wb_auto_regs[] =
{
0x0322,
0x10e2,
0x112e,
0x803d, //3a //3c
0x8120,
0x8240,
0x835a, //RMAX
0x8420, //(0216_kjh20>>23) RMIN
0x8556, //(0216_kjh5c>>5a) BMAX //51
0x8624, //BMIN //20
0x10fb,

};

static const unsigned short sr030pc50_wb_daylight_regs[] =
{
0x0322, //MWB Sunny
0x107b,
0x1126,
0x803f, //52 R Gain
0x8120, //G Gain
0x8230, //B Gain
0x833a, //R Max //41
0x843a, //R Min
0x8538, //B Max
0x862a, //B Min //2f
0x10fb,

};

static const unsigned short sr030pc50_wb_cloudy_regs[] =
{
0x0322, //MWB Cloudy
0x107b,
0x1126,
0x804f, //R Gain
0x8120, //G Gain
0x8225, //B Gain
0x8353, //R Max
0x8448, //R Min
0x8535, //B Max
0x862b, //B Min
0x10fb,

};
static const unsigned short sr030pc50_wb_incandescent_regs[] =
{
0x0322,
0x107b,
0x1126,
0x8020, 
0x8120, 
0x8257, 
0x8321,
0x841d,
0x8559, 
0x8656,
0x10fb,

};

static const unsigned short sr030pc50_wb_fluorescent_regs[] =
{
0x0322,
0x107b,
0x1126,
0x8042,
0x8120,
0x8251,
0x834a,
0x843a,
0x8555,
0x8645,
0x10fb,

};

static const unsigned short sr030pc50_fps_auto_normal_regs[] =
{
0x0300,
0x0171, //sleep
       
0x0300,
0x1190, //fixed fps disable
0x4200, //Vblank 129
0x4381, 

0x900f, //BLC_TIME_TH_ON
0x910f, //BLC_TIME_TH_OFF 
0x9298, //BLC_AG_TH_ON
0x9390, //BLC_AG_TH_OFF

0x0320,
0x100c, //ae off
0x2af0, //antibanding
0x2bf4,
0x30f8,

0x8802, //EXP Max(120Hz) 8.00 fps 
0x89dc, 
0x8a6c, 
     

0x0320,                                                           
0x108c, //ae on

0x0300,
0x0170,

0xff28, //delay 400ms
};

static const unsigned short sr030pc50_fps_auto_dark_regs[] =
{
0x0300,
0x0171, //sleep
       
0x0300,
0x1190, //fixed fps disable
0x4200, //Vblank 129
0x4381, 

0x900f, //BLC_TIME_TH_ON
0x910f, //BLC_TIME_TH_OFF 
0x9298, //BLC_AG_TH_ON
0x9390, //BLC_AG_TH_OFF

0x0320,
0x100c, //ae off
0x2af0, //antibanding
0x2bf4,
0x30f8,

0x8302, //exp normal 8.00fps
0x84dc,
0x856c,

0x8802, //EXP Max(120Hz) 8.00 fps 
0x89dc, 
0x8a6c, 

0x0320,                                                           
0x108c, //ae on

0x0300,
0x0170,

0xff28, //delay 400ms
};

static const unsigned short sr030pc50_vt_mode_regs[] = 
{
0x0300,
0x0171,
0x0173,
0x0171,

// PLL Setting 
0x0300,                                     

0x080f, //Parallel NO Output_PAD Out
0x1000,
0x1194,
0x1200,
0x1488,
                                             
0x0baa,                                                  
0x0caa,                                                  
0x0daa,                                                  
                                                                    
0xc095,                                     
0xc118,                                     
0xc291,
0xc300,                                     
0xc401,   

0x0320, //page 20                                        
0x100c, //ae off                                         
0x0322, //page 22                                        
0x107b, //awb off                                        
                                                                    
0x0300,
0x1200,
0x2000,
0x2104,
0x2200,
0x2304,

0x4000, //Hblank 144
0x4190, 
0x4200, //Vblank 20
0x4314, 

//BLC
0x802e, //don't touch
0x817e, //don't touch
0x8290, //don't touch
0x8330, //don't touch
0x842c, //don't touch
0x854b, //don't touch
0x8601, //don't touch
0x8847, //don't touch

0x900b, //BLC_TIME_TH_ON
0x910b, //BLC_TIME_TH_OFF 
0x92f0, //BLC_AG_TH_ON
0x93e8, //BLC_AG_TH_OFF

0x9838, //don't touch
0x9940, //Out BLC
0xa040, //Dark BLC
0xa842, //Normal BLC 44

//Page2 Last Update 12_01_20
0x0302,
0x1000,
0x1100,
0x1340,
0x1404,
0x181c,
0x1900, //01
0x1a00,
0x1b08,
0x1c9c,
0x1d03,
0x2033,
0x2177,
0x22a7,
0x2332,
0x2433,
0x2b40,
0x2d32,
0x3199,
0x3200,
0x3300,
0x343c,
0x350d,
0x3b60, //80

//timing control 1 // //don't touch
0x5021,
0x511c,
0x52aa,
0x535a,
0x5430,
0x5510,
0x560c,
0x5800,
0x590f,

//timing control 2 // //don't touch
0x6034,
0x613a,
0x6234,
0x6339,
0x6434,
0x6539,
0x7235,
0x7338,
0x7435,
0x7538,
0x8002,
0x812e,
0x820d,
0x8310,
0x840d,
0x8510,
0x921d,
0x9320,
0x941d,
0x9520,
0xa003,
0xa12d,
0xa42d,
0xa503,
0xa812,
0xa91b,
0xaa22,
0xab2b,
0xac10,
0xad0e,
0xb833,
0xb935,
0xbc0c,
0xbd0e,
0xc03a,
0xc13f,
0xc23a,
0xc33f,
0xc43a,
0xc53e,
0xc63a,
0xc73e,
0xc83a,
0xc93e,
0xca3a,
0xcb3e,
0xcc3b,
0xcd3d,
0xce3b,
0xcf3d,
0xd033,
0xd13f,

//Page 10
0x0310,
0x1001, //03, //ISPCTL1, YUV ORDER(FIX)
0x1143,
0x1230, //Y offet, dy offseet enable
0x4080,
0x4102, //00 DYOFS  00->10  _100318
0x4880, //Contrast  88->84  _100318
0x5048, //AGBRT

0x6001, //7f //7c
0x6100, //Use default
0x6280, //SATB_B  (1.4x)
0x6380, //SATR_R  (1.2x)
0x6448, //AGSAT
0x6690, //wht_th2
0x6736, //wht_gain  Dark (0.4x), Normal (0.75x)

0x8000,

//Page 11
//LPF
0x0311,
0x1025,	//LPF_CTL1 //0x01
0x1107,	//06
0x2000,	//LPF_AUTO_CTL
0x2160,	//LPF_PGA_TH
0x230a,	//LPF_TIME_TH
0x6013,	//ZARA_SIGMA_TH //40->10
0x6185,
0x6200,	//ZARA_HLVL_CTL
0x6300,	//ZARA_LLVL_CTL
0x6400,	//ZARA_DY_CTL

0x6770,	//Dark //f0
0x6824,	//Middle //04 //34
0x6904,	//High //04

//Page 12
//2D
0x0312,
0x40d3,	//YC2D_LPF_CTL1 //bc
0x4109,	//YC2D_LPF_CTL2
0x5018,	//Test Setting
0x5124,	//Test Setting
0x701f,	//GBGR_CTL1 //0x1f
0x7100,	//Test Setting
0x7200,	//Test Setting
0x7300,	//Test Setting
0x7412,	//GBGR_G_UNIT_TH//12
0x7512,	//GBGR_RB_UNIT_TH//12
0x7620,	//GBGR_EDGE_TH
0x7780,	//GBGR_HLVL_TH
0x7888,	//GBGR_HLVL_COMP
0x7918,	//Test Setting

///////////////////////
0x903d,
0x9134,
0x9928,
0x9c05, //14 For defect
0x9d08, //15 For defect
0x9e28,
0x9f28,

0xb07d, //75 White Defect
0xb544,
0xb682,
0xb752,
0xb844,
0xb915,
///////////////////////

//Edge
0x0313,
0x1001,	
0x1189,	
0x1214,	
0x1319,	
0x1408,	//Test Setting
0x2003,	//SHARP_Negative
0x2104,	//SHARP_Positive
0x2325,	//SHARP_DY_CTL 
0x2421,	//40->33
0x2508,	//SHARP_PGA_TH
0x2640,	//Test Setting
0x2700,	//Test Setting
0x2808,	//Test Setting
0x2950,	//AG_TH
0x2ae0,	//region ratio
0x2b10,	//Test Setting
0x2c28,	//Test Setting
0x2d40,	//Test Setting
0x2e00,	//Test Setting
0x2f00,	//Test Setting
0x3011,	//Test Setting
0x8005,	//SHARP2D_CTL
0x8107,	//Test Setting
0x9004,	//SHARP2D_SLOPE
0x9105,	//SHARP2D_DIFF_CTL
0x9200,	//SHARP2D_HI_CLIP
0x9330,	//SHARP2D_DY_CTL
0x9430,	//Test Setting
0x9510,	//Test Setting

0x0314,
0x1001,

0x2254,
0x2341,
0x2440, //30

0x2760, //RXCEN
0x2880,      //RYCEN
0x2960, //GXCEN
0x2a80,      //GYCEN
0x2b60, //BXCEN
0x2c80,       //BYCEN

//15page//////////////////////////
0x0315, 
0x1003,

0x1452,
0x163a,
0x172f,

//CMC
0x30f1,
0x3171,
0x3200,
0x331f,
0x34e1,
0x3542,
0x3601,
0x3731,
0x3872,
//CMC OFS
0x4090,
0x4182,
0x4212,
0x4386,
0x4492,
0x4518,
0x4684,
0x4702,
0x4802,

0x0316,
0x1001,
0x3000,
0x310c,
0x3220,
0x3335,
0x3458,
0x3575,
0x368e,
0x37a3,
0x38b4,
0x39c3,
0x3acf,
0x3be2,
0x3cf0,
0x3df9,
0x3eff,

//Page 17 AE 
0x0317,
0xc43c,
0xc532,

//Page 20 AE 
0x0320,
0x100c,
0x1104,

0x2001,
0x2827,
0x29a1,

0x2a90,
0x2bf5,
0x2c2b, //23->2b 2010_04_06 hhzin

0x30f8,

0x3b22,
0x3cde,

0x3922,
0x3ade,
0x3b22, //23->22 _10_04_06 hhzin
0x3cde,

0x6070, //70
0x6110, //11 //22

0x6270,
0x6310, //11 //22

0x6830,// x no Flip 34
0x696a,// x no Flip 66
0x6A27,
0x6Bbb,

0x7042,//Y Targe 32

0x7622, //Unlock bnd1
0x7781, //Unlock bnd2 02->a2 _10_04_06 hhzin

0x7822, //Yth 1
0x7927, //Yth 2 //1f
0x7a23, //Yth 3

0x7c17, //1c->1d _10_04_06 hhzin
0x7d22,

//50Hz
0x8300, //EXP Normal 30.00 fps 
0x84c3, 
0x8550, 

0x8600, //EXPMin 7500.00 fps
0x87c8, 

0x8802, //EXP Max(120Hz) 10.91 fps 
0x8919, 
0x8a1c, 



0x8B3a, //EXP100 
0x8C98, 
0x8D30, //EXP120 
0x8Ed4, 

0x9102, //EXP Fix 10.00 fps
0x9249, 
0x93f0, 

0x988C, //Outdoor th1
0x9923, //Outdoor th2

0x9c05, //EXP Limit 1071.43 fps 
0x9d78, 
0x9e00, //EXP Unit 
0x9fc8, 

0xb01d,
0xb114, //14
0xb2f8, //80 //90
0xb317, //AGLVL //17
0xb417,
0xb53e,
0xb62b,
0xb724,
0xb821,
0xb91f,
0xba1e,
0xbb1d,
0xbc1c,
0xbd1b,

0xc01a,
0xc348,
0xc448,

//Page 22 AWB
0x0322,
0x10e2,
0x112e, //2e
0x2041, //01 //69
0x2140,
0x24fe,

0x3080, //Cb
0x3180, //Cr
0x3812, //Lock Boundary //13
0x3933,
0x40f3, //f0
0x4143, //32-->33
0x4233, //22
0x43f3,
0x4444, //88
0x4566, //
0x4608, //02
0x4763,

0x803d, //3a //3c
0x8120,
0x8240, //3a

//Cb_7b, Cr_85
0x835a, //RMAX
0x8422, //(0216_kjh20>>23) RMIN
0x8557, //(0216_kjh5c>>5a) BMAX //51
0x8624, //BMIN //20

0x8741,
0x8833, //3a
0x893e, //3e //40
0x8a34, //32

0x8b03, //OUT TH
0x8d22, //21 //22
0x8e21, //41

0x8f58,
0x9056,
0x9153,
0x924e,
0x9347,
0x9441,
0x953b,
0x9633,
0x972f,
0x982b,
0x9929,
0x9a27,
0x9b06,

///////////////////////////// Page 48
0x0348,

0x1005,
0x1100, //async_fifo off
0x1200,

0x16c4,
0x1700,
0x1900,
0x1a00,
0x1c02,
0x1d04,
0x1e07,
0x1f06,
0x2000,
0x21b8,
0x2200,
0x2301,

0x3005,
0x3100,
0x3402,
0x3206,
0x3503,
0x3601,
0x3703,
0x3800,
0x394a, 
0x3c00,
0x3dfa,
0x3f10,
0x4000,
0x4120,
0x4200,

0x0322,
0x10fb,

0x0320,
0x108c,

0x0300,
0x1194,
0x0170,     

};

static const unsigned short sr030pc50_init_regs_smart_stay[] = {
0x0300,
0x0171,
0x0173,
0x0171,


//  PLL Setting 
0x0300,                                     
   
0x080f, //Parallel NO Output_PAD Out
0x1000,
0x1190,
0x1200,
0x1488,
 
0x0baa,                                                             
0x0caa,                                                             
0x0daa,                                                             
                                                                 
0xc095,                                     
0xc118,                                     
0xc291,                                     
0xc300,                                     
0xc401,   
    
0x0320, //page 20                                                   
0x100c, //ae off                                                    
0x0322, //page 22                                                   
0x107b, //awb off                                                   
                                                                 
0x0300,
0x1200,
0x2000,
0x2104,
0x2200,
0x2304,
    
0x4000, //Hblank 144                                                
0x4190,                                                             
0x4200, //Vblank 129
0x4381, 
        
// BLC  
0x802e, //don't touch
0x817e, //don't touch
0x8290, //don't touch
0x8330, //don't touch
0x842c, //don't touch
0x854b, //don't touch
0x8601, //don't touch
0x8847, //don't touch
        
0x900f, //BLC_TIME_TH_ON
0x910f, //BLC_TIME_TH_OFF 
0x92f7, //BLC_AG_TH_ON
0x93ef, //BLC_AG_TH_OFF
       
0x9838, //don't touch
0x9940, //Out BLC
0xa040, //Dark BLC
0xa842, //Normal BLC 44
   
// Page2 Last Update 12_01_20
0x0302,
0x1000,
0x1100,
0x1340, 
0x1404, 
0x181c,
0x1900, //01
0x1a00,
0x1b08,
0x1c9c,
0x1d03,
0x2033,
0x2177,
0x22a7,
0x2332,
0x2433,
0x2b40,
0x2d32,
0x3199,
0x3200,
0x3300,
0x343c,
0x350d,
0x3b60, //80
   
// timing control 1 // //don't touch
0x5021,
0x511c,
0x52aa,
0x535a,
0x5430,
0x5510,
0x560c,
0x5800,
0x590f,
   
// timing control 2 // //don't touch
0x6034,
0x613a,
0x6234,
0x6339,
0x6434,
0x6539,
0x7235,
0x7338,
0x7435,
0x7538,
0x8002,
0x812e,
0x820d,
0x8310,
0x840d,
0x8510,
0x921d,
0x9320,
0x941d,
0x9520,
0xa003,
0xa12d,
0xa42d,
0xa503,
0xa812,
0xa91b,
0xaa22,
0xab2b,
0xac10,
0xad0e,
0xb833,
0xb935,
0xbc0c,
0xbd0e,
0xc03a,
0xc13f,
0xc23a,
0xc33f,
0xc43a,
0xc53e,
0xc63a,
0xc73e,
0xc83a,
0xc93e,
0xca3a,
0xcb3e,
0xcc3b,
0xcd3d,
0xce3b,
0xcf3d,
0xd033,
0xd13f,
   
// Page 10
0x0310,
0x1001, //03 $f //ISPCTL1 $f YUV ORDER(FIX)
0x1143,
0x1230, //Y offet $f dy offseet enable
0x4080,
0x4102, //00 DYOFS  00->10  _100318
0x4885, //Contrast  88->84  _100318
0x5048, //AGBRT
    
0x6001, //7f //7c
0x6100, //Use default
0x6280, //SATB_B  (1.4x)
0x6380, //SATR_R  (1.2x)
0x6448, //AGSAT
0x6690, //wht_th2
0x6736, //wht_gain  Dark (0.4x) Normal (0.75x)
    
0x8000,
   
// Page 11
// LPF
0x0311,
0x1025,
0x1107,
0x2000,
0x2160,
0x230a,
0x6013,
0x6185,
0x6200,
0x6300,
0x6400,

0x6770,
0x6824,
0x6904,
   
// Page 12
// 2D
0x0312,
0x40d3,
0x4109,
0x5018,
0x5124,
0x701f,
0x7100,
0x7200,
0x7300,
0x7412,
0x7512,
0x7620,
0x7780,
0x7888,
0x7918,
   
// /////////////////////
0x903d,
0x9134,
0x9928,
0x9c05, //14 For defect
0x9d08, //15 For defect
0x9e28,
0x9f28,

0xb07d, //75 White Defect
0xb544,
0xb682,
0xb752,
0xb844,
0xb915,
// /////////////////////
   
// Edge
0x0313,
0x1001,
0x1189,
0x1214,
0x1319,
0x1408,
0x2003,
0x2104,
0x2325,
0x2421,
0x2508,
0x2640,
0x2700,
0x2808,
0x2950,
0x2ae0,
0x2b10,
0x2c28,
0x2d40,
0x2e00,
0x2f00,
0x3011,
0x8005,
0x8107,
0x9004,
0x9105,
0x9200,
0x9330,
0x9430,
0x9510,
   
0x0314,
0x1001,

0x2254,
0x2341,
0x2440, //30

0x2794, //RXCEN
0x2880, //RYCEN
0x2994, //GXCEN
0x2a80, //GYCEN
0x2b94, //BXCEN
0x2c80, //BYCEN

0x0315, 
0x1003, 

0x1452, 
0x163a, 
0x172f, 

0x30f1, 
0x3171, 
0x3200, 
0x331f, 
0x34e1, 
0x3542, 
0x3601, 
0x3731, 
0x3872,
0x4090, 
0x4182, 
0x4212, 
0x4386, 
0x4492, 
0x4518, 
0x4684, 
0x4702, 
0x4802, 

0x0316, 
0x1001, 
0x3000, 
0x310e, 
0x3226, 
0x333f, 
0x3465, 
0x3580, 
0x3697, 
0x37a8, 
0x38b9, 
0x39c5, 
0x3ad1, 
0x3be3, 
0x3cf0, 
0x3df9, 
0x3eff, 


0x0317, 
0xc43c, 
0xc532, 

//page 20
0x0320, 
0x100c, 
0x1104, 

0x2001, 
0x2827, 
0x29a1, 

0x2af0, 
0x2b04, 
0x2c2b, 
0x2e23, 

0x30f8, 

0x3b22, 
0x3cde, 

0x3922, 
0x3ade, 
0x3b22, 
0x3cde, 

0x6040, 
0x6131, 

0x6240, 
0x6331, 

0x6826, 
0x6976, 
0x6A3c, 
0x6Bb4, 

0x7048, 

0x7621, 
0x7791, 

0x7822, 
0x792b, 
0x7a23, 

0x7c24, 
0x7d22, 


0x8300, 
0x8457, 
0x8524, 

0x8600, 
0x87c8, 

0x8801, 
0x8986, 
0x8aa0, 

0xa001, //EXP Max(100Hz) 16.67 fps 
0xa15f,                           
0xa290,
                           
0x8B75, 
0x8C30, 
0x8D61, 
0x8Ea8, 

0x988C, 
0x9923, 

0x9c06, 
0x9d40, 
0x9e00, 
0x9fc8, 

0xb038, 
0xb138, 
0xb2ff, 
0xb340, 
0xb440, 
0xb570, 
0xb62b, 
0xb724, 
0xb821, 
0xb91f, 
0xba1e, 
0xbb1d, 
0xbc1c, 
0xbd1b, 

0xc01a, 
0xc348, 
0xc448, 

0x0322, 
0x10e2, 
0x112e, 
0x2041, 
0x2140, 
0x24fe, 

0x3080, 
0x3180, 
0x3812, 
0x3933, 
0x40f3, 
0x4132, 
0x4222, 
0x43f3, 
0x4443, 
0x4533, 
0x4608, 

0x803d, 
0x8120, 
0x8240, 

0x835a, 
0x8422, 
0x8557, 
0x8624, 

0x873f, 
0x8833, 
0x893e, 
0x8a34, 

0x8b03, 
0x8d22, 
0x8e21, 

0x8f58, 
0x9056, 
0x9153, 
0x924e, 
0x9347, 
0x9441, 
0x953b, 
0x9633, 
0x972f, 
0x982b, 
0x9929, 
0x9a27, 
0x9b06, 

0x0348, 

0x1005, 
0x1100, 
0x1200, 

0x16c4, 
0x1700, 
0x1900, 
0x1a00, 
0x1c02, 
0x1d04, 
0x1e07, 
0x1f06, 
0x2000, 
0x21b8, 
0x2200, 
0x2301, 

0x3005, 
0x3100, 
0x3402, 
0x3206, 
0x3503, 
0x3601, 
0x3703, 
0x3800, 
0x394a, 
0x3c00, 
0x3dfa, 
0x3f10, 
0x4000, 
0x4120, 
0x4200, 

0x0322, 
0x10fb, 

0x0320, 
0x108c, 

0x0170, 

0xff14, //200ms

};

#endif
