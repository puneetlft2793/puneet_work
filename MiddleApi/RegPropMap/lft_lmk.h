
#pragma once

#define REG16_DEF(adds, start, end) ((adds << 16) | (start << 8) | (end-start+1))

#define LMK_BASE_ADDRESS  0x00    




#pragma region Enumeration SPPU LMK Registers

// DEFINATION of ALL dac register here




typedef enum SPPULMKRegsDefs
{
    
	LFT_SPPU_LMK_CLK0_CLK1_CLKout0_TYPE        = REG16_DEF(0x06,16,19),
	LFT_SPPU_LMK_CLK0_CLK1_CLK1out1_TYPE       = REG16_DEF(0x06,20,23),
	LFT_SPPU_LMK_CLK0_CLK1_divider             = REG16_DEF(0x00,5,15),
	LFT_SPPU_LMK_CLK0_CLK1_digdelay            = REG16_DEF(0x00,18,27),
	LFT_SPPU_LMK_CLK0_CLK1_AnalogDelay         = REG16_DEF(0x06,5,9),
	LFT_SPPU_LMK_CLK0_CLK1_AnalogDelay_sel     = REG16_DEF(0x00,28,29),
	LFT_SPPU_LMK_CLK0_CLK1_DD_hlfshft          = REG16_DEF(0x00,16,16),
	LFT_SPPU_LMK_CLK0_CLK1_switch_off_pd       = REG16_DEF(0x00,31,31),


	

	LFT_SPPU_LMK_CLK2_CLK3_CLKout2_TYPE         = REG16_DEF(0x06,24,27),
	LFT_SPPU_LMK_CLK2_CLK3_CLK1out3_TYPE        = REG16_DEF(0x06,28,31),
	LFT_SPPU_LMK_CLK2_CLK3_divider              = REG16_DEF(0x01,5,15),
	LFT_SPPU_LMK_CLK2_CLK3_digdelay             = REG16_DEF(0x01,18,27),
	LFT_SPPU_LMK_CLK2_CLK3_AnalogDelay          = REG16_DEF(0x06,11,15),
	LFT_SPPU_LMK_CLK2_CLK3_AnalogDelay_sel      = REG16_DEF(0x01,28,29),
	LFT_SPPU_LMK_CLK2_CLK3_DD_hlfshft           = REG16_DEF(0x01,16,16),
    LFT_SPPU_LMK_CLK2_CLK3_switch_off_pd        = REG16_DEF(0x01,31,31),

    
	LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE         = REG16_DEF(0x07,16,19),
	LFT_SPPU_LMK_CLK4_CLK5_CLK1out5_TYPE        = REG16_DEF(0x07,20,23),
	LFT_SPPU_LMK_CLK4_CLK5_divider              = REG16_DEF(0x02,5,15),
	LFT_SPPU_LMK_CLK4_CLK5_digdelay             = REG16_DEF(0x02,18,27),
	LFT_SPPU_LMK_CLK4_CLK5_AnalogDelay          = REG16_DEF(0x07,5,9),
	LFT_SPPU_LMK_CLK4_CLK5_AnalogDelay_sel      = REG16_DEF(0x02,28,29),
	LFT_SPPU_LMK_CLK4_CLK5_DD_hlfshft           = REG16_DEF(0x02,16,16),
	LFT_SPPU_LMK_CLK4_CLK5_switch_off_pd        = REG16_DEF(0x02,31,31),

    
	LFT_SPPU_LMK_CLK6_CLK7_CLKout6_TYPE         = REG16_DEF(0x07,24,27),
	LFT_SPPU_LMK_CLK6_CLK7_CLK1out7_TYPE        = REG16_DEF(0x07,28,31),
	LFT_SPPU_LMK_CLK6_CLK7_divider              = REG16_DEF(0x03,5,15),
	LFT_SPPU_LMK_CLK6_CLK7_digdelay             = REG16_DEF(0x03,18,27),
	LFT_SPPU_LMK_CLK6_CLK7_AnalogDelay          = REG16_DEF(0x07,11,15),
	LFT_SPPU_LMK_CLK6_CLK7_AnalogDelay_sel      = REG16_DEF(0x03,28,29),
	LFT_SPPU_LMK_CLK6_CLK7_OScin_sel            = REG16_DEF(0x03,30,30),
	LFT_SPPU_LMK_CLK6_CLK7_DD_hlfshft           = REG16_DEF(0x03,16,16),
    LFT_SPPU_LMK_CLK6_CLK7_switch_off_pd        = REG16_DEF(0x03,31,31),


	LFT_SPPU_LMK_CLK8_CLK9_CLKout8_TYPE         = REG16_DEF(0x08,16,19),
	LFT_SPPU_LMK_CLK8_CLK9_CLK1out9_TYPE        = REG16_DEF(0x08,20,23),
	LFT_SPPU_LMK_CLK8_CLK9_divider              = REG16_DEF(0x04,5,15),
	LFT_SPPU_LMK_CLK8_CLK9_digdelay             = REG16_DEF(0x04,18,27),
	LFT_SPPU_LMK_CLK8_CLK9_AnalogDelay          = REG16_DEF(0x08,5,9),
	LFT_SPPU_LMK_CLK8_CLK9_AnalogDelay_sel      = REG16_DEF(0x04,28,29),
    LFT_SPPU_LMK_CLK8_CLK9_OScin_sel            = REG16_DEF(0x04,30,30),
	LFT_SPPU_LMK_CLK8_CLK9_DD_hlfshft           = REG16_DEF(0x04,16,16),
    LFT_SPPU_LMK_CLK8_CLK9_switch_off_pd        = REG16_DEF(0x04,31,31),


	LFT_SPPU_LMK_CLK10_CLK11_CLKout0_TYPE       = REG16_DEF(0x08,24,27),
	LFT_SPPU_LMK_CLK10_CLK11_CLK1out1_TYPE      = REG16_DEF(0x08,28,31),
	LFT_SPPU_LMK_CLK10_CLK11_divider            = REG16_DEF(0x05,5,15),
	LFT_SPPU_LMK_CLK10_CLK11_digdelay           = REG16_DEF(0x05,18,27),
	LFT_SPPU_LMK_CLK10_CLK11_AnalogDelay        = REG16_DEF(0x08,11,15),
	LFT_SPPU_LMK_CLK10_CLK11_AnalogDelay_sel    = REG16_DEF(0x05,28,29),  
	LFT_SPPU_LMK_CLK10_CLK11_DD_hlfshft         = REG16_DEF(0x05,16,16),
	LFT_SPPU_LMK_CLK10_CLK11_switch_off_pd      = REG16_DEF(0x05,31,31),



	LFT_SPPU_LMK_PLL1_Setting_En_CLKin0          = REG16_DEF(0x0D,5,5),
	LFT_SPPU_LMK_PLL1_Setting_En_CLKin1          = REG16_DEF(0x0D,6,6),
	LFT_SPPU_LMK_PLL1_Setting_CLKIN_sel_INV      = REG16_DEF(0x0D,8,8),
	LFT_SPPU_LMK_PLL1_Setting_CLKIN_SEL_Mode     = REG16_DEF(0x0D,9,11),
	LFT_SPPU_LMK_PLL1_Setting_CLKIN0_MUX         = REG16_DEF(0x0D,12,14),    
	LFT_SPPU_LMK_PLL1_Setting_CLKIN0_TYPE        = REG16_DEF(0x0D,16,18),   
	LFT_SPPU_LMK_PLL1_Setting_CLKIN1_MUX         = REG16_DEF(0x0D,20,22),   
	LFT_SPPU_LMK_PLL1_Setting_CLKIN1_TYPE        = REG16_DEF(0x0E,24,26),   
	LFT_SPPU_LMK_PLL1_Setting_CLK0BUF_TYPE0      = REG16_DEF(0x0E,20,20),
	LFT_SPPU_LMK_PLL1_Setting_CLK1BUF_TYPE1      = REG16_DEF(0x0E,21,21),
	LFT_SPPU_LMK_PLL1_Setting_CLKIN0_Div         = REG16_DEF(0x1B,20,21),   
	LFT_SPPU_LMK_PLL1_Setting_CLK1N1_Div         = REG16_DEF(0x1B,22,23),   

    LFT_SPPU_LMK_PLL1_wind_size                  = REG16_DEF(0x18,6,7), 
	LFT_SPPU_LMK_PLL1_R_DLY                      = REG16_DEF(0x18,8,10),
	LFT_SPPU_LMK_PLL1_N_DLY_2                    = REG16_DEF(0x18,12,14),
    LFT_SPPU_LMK_PLL1_DLD_CNT                    = REG16_DEF(0x19,6,19),
	LFT_SPPU_LMK_PLL1_SYNC_DLD                   = REG16_DEF(0x0C,22,22),  
	LFT_SPPU_LMK_PLL1_REF_Divider                = REG16_DEF(0x1B,6,19),   
	LFT_SPPU_LMK_PLL1_N_Divider                  = REG16_DEF(0x1C,6,19),   
	LFT_SPPU_LMK_PLL1_ChargePump_state           = REG16_DEF(0x1B,5,5),    
	LFT_SPPU_LMK_PLL1_ChargePump_Gain            = REG16_DEF(0x1B,26,27),  
    LFT_SPPU_LMK_PLL1_ChargePump_polarity        = REG16_DEF(0x1B,28,28), 

  LFT_SPPU_LMK_PLL2_XTAL_OSC                     = REG16_DEF(0x0B,5,5), 
  LFT_SPPU_LMK_PLL2_SYNC_DLD                     = REG16_DEF(0x0C,23,23), 
  LFT_SPPU_LMK_PLL12_DLD_CNT                     = REG16_DEF(0x1A,6,9), 
  LFT_SPPU_LMK_PLL2_PLL_WIND_SIZE                = REG16_DEF(0x1A,30,31), // DOUBT
  LFT_SPPU_LMK_PLL2_REF_DIVIER                   = REG16_DEF(0x1C,20,31), 
  LFT_SPPU_LMK_PLL2_N_CALL                       = REG16_DEF(0x1D,5,22), 
  LFT_SPPU_LMK_PLL2_N_DIVIDER                    = REG16_DEF(0x1E,5,22), 
  LFT_SPPU_LMK_PLL2_PRESCALAR                    = REG16_DEF(0x1E,24,26), 
  LFT_SPPU_LMK_PLL2_INPUT_FREQ                   = REG16_DEF(0x1D,24,26), 
  LFT_SPPU_LMK_PLL2_2X_REF                       = REG16_DEF(0x1A,29,29), 
  LFT_SPPU_LMK_PLL2_PLL2_FAST_PDF                = REG16_DEF(0x1D,23,23), 
  LFT_SPPU_LMK_PLL2_LOOP_FILTER_R3               = REG16_DEF(0x18,16,18), 
  LFT_SPPU_LMK_PLL2_LOOP_FILTER_C3               = REG16_DEF(0x18,24,27), 
  LFT_SPPU_LMK_PLL2_LOOP_FILTER_R4               = REG16_DEF(0x18,20,24), 
  LFT_SPPU_LMK_PLL2_LOOP_FILTER_C4               =  REG16_DEF(0x18,28,31), 
  LFT_SPPU_LMK_PLL2_ChargePump_STATE             = REG16_DEF(0x1A,5,5), 
  LFT_SPPU_LMK_PLL2_ChargePump_GAIN              = REG16_DEF(0x1A,26,27), 
  LFT_SPPU_LMK_PLL2_ChargePump_polarity          = REG16_DEF(0x1A,28,28), 


	LFT_SPPU_LMK_GEN_Setting_FeedbackMux_Source_CLKOUT        =  REG16_DEF(0x0A,5,7),  
	LFT_SPPU_LMK_GEN_Setting_FeedbackMux_Enable               =  REG16_DEF(0x0A,11,11),
	LFT_SPPU_LMK_GEN_Setting_VCO_Divider                      =  REG16_DEF(0x0A,8,10), 
	LFT_SPPU_LMK_GEN_Setting_VCO_Mux                          =  REG16_DEF(0x0A,12,12), 

	LFT_SPPU_LMK_GEN_Setting_SYN_Type                         =  REG16_DEF(0x0B,12,14),
    LFT_SPPU_LMK_GEN_Setting_SYN_Polarity                     =  REG16_DEF(0x0B,16,16),  
	LFT_SPPU_LMK_GEN_Setting_SYN_sync_mux                     =  REG16_DEF(0x0B,18,19), 
	LFT_SPPU_LMK_GEN_Setting_SYN_ena_auto                     =  REG16_DEF(0x0B,15,15), 
	LFT_SPPU_LMK_GEN_Setting_SYN_Qualification                =  REG16_DEF(0x0B,17,17),  
	LFT_SPPU_LMK_GEN_Setting_SYN_ENABLE                       =  REG16_DEF(0x0B,26,26),   
	LFT_SPPU_LMK_GEN_Setting_SYN_sync_op_01_STATE             =  REG16_DEF(0x0B,20,20),
	LFT_SPPU_LMK_GEN_Setting_SYN_sync_op_02_STATE             =  REG16_DEF(0x0B,21,21),
	LFT_SPPU_LMK_GEN_Setting_SYN_sync_op_03_STATE             =  REG16_DEF(0x0B,22,22),
	LFT_SPPU_LMK_GEN_Setting_SYN_sync_op_04_STATE             =  REG16_DEF(0x0B,23,23),
	LFT_SPPU_LMK_GEN_Setting_SYN_sync_op_05_STATE             =  REG16_DEF(0x0B,24,24),
	LFT_SPPU_LMK_GEN_Setting_SYN_sync_op_06_STATE             =  REG16_DEF(0x0B,25,25),

	LFT_SPPU_LMK_GEN_Setting_Holdover_Mode                    =   REG16_DEF(0x0C,6,7),   
	LFT_SPPU_LMK_GEN_Setting_Holdover_dld1_DET                =   REG16_DEF(0x0D,15,15),
	LFT_SPPU_LMK_GEN_Setting_Holdover_force                   =   REG16_DEF(0x0F,5,5),
	LFT_SPPU_LMK_GEN_Setting_Holdover_DLD_count               =   REG16_DEF(0x0F,6,19),

	

	LFT_SPPU_LMK_GEN_Setting_status_Outputs_LD_TYPE           =   REG16_DEF(0x0E,24,26),
	LFT_SPPU_LMK_GEN_Setting_status_Outputs_LD_MUX            =   REG16_DEF(0x0E,27,31),
	
	
	LFT_SPPU_LMK_GEN_Setting_status_Outputs_Holdover_type     =   REG16_DEF(0x0D,24,26),
	LFT_SPPU_LMK_GEN_Setting_status_Outputs_Holdover_MUX      =   REG16_DEF(0x0D,27,31),
	
	LFT_SPPU_LMK_GEN_Setting_XTAL_LVL                         =   REG16_DEF(0x10,30,31),
	LFT_SPPU_LMK_GEN_Setting_LOS_TIMEOUT                      =   REG16_DEF(0x0E,30,31),
	LFT_SPPU_LMK_GEN_Setting_En_Los                           =   REG16_DEF(0x0E,28,28),
	



	LFT_SPPU_LMK_OSCOUT_Divider                  = REG16_DEF(0x0A,16,18), 
	LFT_SPPU_LMK_OSCOUT_OSC1_Amp                 = REG16_DEF(0x0A,30,31), 
	LFT_SPPU_LMK_OSCOUT_OSC0_Type                = REG16_DEF(0x0A,24,27),  
	LFT_SPPU_LMK_OSCOUT_OSC1_Mux                 = REG16_DEF(0x0A,21,21), 
	LFT_SPPU_LMK_OSCOUT_OSC0_Mux                 = REG16_DEF(0x0A,20,20), 
	LFT_SPPU_LMK_OSCOUT_ENABLE_OSCout0           = REG16_DEF(0x0A,22,22),
	LFT_SPPU_LMK_OSCOUT_ENABLE_OSCout1           = REG16_DEF(0x0A,23,23), 
	LFT_SPPU_LMK_OSCOUT_Swich_off                = REG16_DEF(0x0A,19,19),  

	//Default Values
	LFT_SPPU_LMK_ADDR1							=	REG16_DEF(0x00,0,31),
	LFT_SPPU_LMK_ADDR2							=	REG16_DEF(0x01,0,31),
	LFT_SPPU_LMK_ADDR3							=	REG16_DEF(0x02,0,31),
	LFT_SPPU_LMK_ADDR4							=	REG16_DEF(0x03,0,31),
	LFT_SPPU_LMK_ADDR5							=	REG16_DEF(0x04,0,31),
	LFT_SPPU_LMK_ADDR6							=	REG16_DEF(0x05,0,31),
	LFT_SPPU_LMK_ADDR7							=	REG16_DEF(0x06,0,31),
	LFT_SPPU_LMK_ADDR8							=	REG16_DEF(0x07,0,31),
	LFT_SPPU_LMK_ADDR9							=	REG16_DEF(0x08,0,31),
	LFT_SPPU_LMK_ADDR10							=	REG16_DEF(0x09,0,31),
	LFT_SPPU_LMK_ADDR11							=	REG16_DEF(0x0A,0,31),
	LFT_SPPU_LMK_ADDR12							=	REG16_DEF(0x0B,0,31),
	LFT_SPPU_LMK_ADDR13							=	REG16_DEF(0x0C,0,31),
	LFT_SPPU_LMK_ADDR14							=	REG16_DEF(0x0D,0,31),
	LFT_SPPU_LMK_ADDR15							=	REG16_DEF(0x0E,0,31),
	LFT_SPPU_LMK_ADDR16							=	REG16_DEF(0x0F,0,31),
	LFT_SPPU_LMK_ADDR17							=	REG16_DEF(0x10,0,31),
	LFT_SPPU_LMK_ADDR18							=	REG16_DEF(0x18,0,31),
	LFT_SPPU_LMK_ADDR19							=	REG16_DEF(0x19,0,31),
	LFT_SPPU_LMK_ADDR20							=	REG16_DEF(0x1A,0,31),
	LFT_SPPU_LMK_ADDR21							=	REG16_DEF(0x1B,0,31),
	LFT_SPPU_LMK_ADDR22							=	REG16_DEF(0x1C,0,31),
	LFT_SPPU_LMK_ADDR23							=	REG16_DEF(0x1D,0,31),
	LFT_SPPU_LMK_ADDR24							=	REG16_DEF(0x1E,0,31),

	/************************************************ power on self test****************************/
	LFT_SPPU_TEST_LMK                          =    REG16_DEF(0x01,4,4)

	};





