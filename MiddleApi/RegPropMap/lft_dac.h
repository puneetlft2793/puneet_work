

#pragma once

#define REG16_DEF(adds, start, end) ((adds << 16) | (start << 8) | (end-start+1))

#define DAC_BASE_ADDRESS  0x00   

//__MODIFIED__: HP 4 Aug 2015
#define LFT_SPPU_NUM_DACS			0x03			//3 dacs are attached to System (all dacs are smae)
#define LFT_SPPU_TOTAL_DAC_REGS		0x32			//Total 50 DAC registers in each dac

#pragma region Enumeration SPPU DAC Registers

// DEFINATION of ALL dac register here

typedef enum SPPUDACRegsDefs 
{
                
	LFT_SPPU_DAC_ALARMS_ZERO_CHECK_FROM_ZEROCLOCK		    = REG16_DEF(0x07,15,15),  // used in advaned
	LFT_SPPU_DAC_ALARMS_NOTUSED1				            = REG16_DEF(0x07,14,14),
	LFT_SPPU_DAC_ALARMS_FIFO_COLLISION                      = REG16_DEF(0x07,13,13),
	LFT_SPPU_DAC_ALARMS_FIFO_1AWAY                          = REG16_DEF(0x07,12,12),
	LFT_SPPU_DAC_ALARMS_FIFO_2WAY                           = REG16_DEF(0x07,11,11),
	LFT_SPPU_DAC_ALARMS_DACCLK_GONE                         = REG16_DEF(0x07,10,10),
	LFT_SPPU_DAC_ALARMS_DATACLK_GONE                        = REG16_DEF(0x07,9,9),
	LFT_SPPU_DAC_ALARMS_CLK_OUTPUT_GONE                     = REG16_DEF(0x07,8,8),
	LFT_SPPU_DAC_ALARMS_IO_TEST_FROM_IOTEST                 = REG16_DEF(0x07,7,7),
	LFT_SPPU_DAC_ALARMS_OSTR                       			= REG16_DEF(0x07,6,6),
	LFT_SPPU_DAC_ALARMS_PLLLOCK_FROM_PLL                    = REG16_DEF(0x07,5,5),
	LFT_SPPU_DAC_ALARMS_PARITY_Rising_edge_RPARITY          = REG16_DEF(0x07,4,4),
	LFT_SPPU_DAC_ALARMS_PARITY_Falling_edge_LPARITY         = REG16_DEF(0x07,3,3),
	LFT_SPPU_DAC_ALARMS_Block_FRAME_PARITY                  = REG16_DEF(0x07,2,2),
	LFT_SPPU_DAC_ALARMS_NOTUSED2                            = REG16_DEF(0x07,1,1),
	LFT_SPPU_DAC_ALARMS_NOTUSED3                            = REG16_DEF(0x07,0,0),


	LFT_SPPU_DAC_SLEEP_CNT_notused_RESERVED1                = REG16_DEF(0x23,15,15),  // used in advaned
	LFT_SPPU_DAC_SLEEP_CNT_DACI_SLP                         = REG16_DEF(0x23,14,14), 
	LFT_SPPU_DAC_SLEEP_CNT_DACQ_SLP                         = REG16_DEF(0x23,13,13), 
	LFT_SPPU_DAC_SLEEP_CNT_notused_RESERVED2                = REG16_DEF(0x23,12,12), 
	LFT_SPPU_DAC_SLEEP_CNT_CLK_RCV_SLP                      = REG16_DEF(0x23,11,11), 
    LFT_SPPU_DAC_SLEEP_CNT_PLL_SLEEP                        = REG16_DEF(0x23,10,10),
	LFT_SPPU_DAC_SLEEP_CNT_LVDS_DATA_SLP                    = REG16_DEF(0x23,9,9),
	LFT_SPPU_DAC_SLEEP_CNT_LVDS_CNT_SLP                     = REG16_DEF(0x23,8,8),
	LFT_SPPU_DAC_SLEEP_CNT_temp_sensor_TMP_CNT              = REG16_DEF(0x23,7,7),
	LFT_SPPU_DAC_SLEEP_CNT_fuses_RESERVED                   = REG16_DEF(0x23,6,6),
	LFT_SPPU_DAC_SLEEP_CNT_bias_opamp_BIAS_AMP_SLP          = REG16_DEF(0x23,5,5),
	LFT_SPPU_DAC_SLEEP_CNT_NOTINUSED                        = REG16_DEF(0x23,0,4),  // not in used


	LFT_SPPU_DAC_IOTEST_IO_DISA                             = REG16_DEF(0x01,8,10),   // disabled the io test bit
	LFT_SPPU_DAC_IOTEST_IO_ENA                              = REG16_DEF(0x01,15,15),  // enable the io test bit
	LFT_SPPU_DAC_IOTEST_RESERVED1                           = REG16_DEF(0x01,14,14),  //not in used
	LFT_SPPU_DAC_IOTEST_RESERVED2                           = REG16_DEF(0x01,13,13),  //not in used
	LFT_SPPU_DAC_IOTEST_Alarm_reset64count_64CNT_ENA        = REG16_DEF(0x01,12,12),  // not in used
	LFT_SPPU_DAC_IOTEST_ODDEVEN_PARITY                      = REG16_DEF(0x01,11,11),  //not in used
	LFT_SPPU_DAC_IOTEST_RESERVED4                           = REG16_DEF(0x01,7,7),    //not in used
	LFT_SPPU_DAC_IOTEST_DACI_COMPLEMENT                     = REG16_DEF(0x01,6,6),    //not in used
	LFT_SPPU_DAC_IOTEST_DACQ_COMPEMENT                      = REG16_DEF(0x01,5,5),    //not in used
    LFT_SPPU_DAC_IOTEST_Alarm_FIFO_2away_ena                = REG16_DEF(0x01,3,3),    // not in used
	LFT_SPPU_DAC_IOTEST_Alarm_FIFO_1away_ena                = REG16_DEF(0x01,2,2),    // not in used
	LFT_SPPU_DAC_IOTEST_Alarm_FIFO_collision_ena            = REG16_DEF(0x01,1,1),    // not in used
	LFT_SPPU_DAC_IOTEST_RESERVED                            = REG16_DEF(0x01,0,0),    //not in used
    LFT_SPPU_DAC_PATTERN0                                   = REG16_DEF(0x25,0,15),   // used in advaned
	LFT_SPPU_DAC_PATTERN1                                   = REG16_DEF(0x26,0,15),
    LFT_SPPU_DAC_PATTERN2                                   = REG16_DEF(0x27,0,15),
	LFT_SPPU_DAC_PATTERN3                                   = REG16_DEF(0x28,0,15),
	LFT_SPPU_DAC_PATTERN4                                   = REG16_DEF(0x29,0,15),
	LFT_SPPU_DAC_PATTERN5                                   = REG16_DEF(0x2A,0,15),
	LFT_SPPU_DAC_PATTERN6                                   = REG16_DEF(0x2B,0,15),
	LFT_SPPU_DAC_PATTERN7                                   = REG16_DEF(0x2C,0,15),
    LFT_SPPU_DAC_IOTEST_RESULT1                             = REG16_DEF(0x04,0,0),
    LFT_SPPU_DAC_IOTEST_RESULT2                             = REG16_DEF(0x04,1,1),
	LFT_SPPU_DAC_IOTEST_RESULT3                             = REG16_DEF(0x04,2,2),
	LFT_SPPU_DAC_IOTEST_RESULT4                             = REG16_DEF(0x04,3,3),
	LFT_SPPU_DAC_IOTEST_RESULT5                             = REG16_DEF(0x04,4,4),
	LFT_SPPU_DAC_IOTEST_RESULT6                             = REG16_DEF(0x04,5,5),
	LFT_SPPU_DAC_IOTEST_RESULT7                             = REG16_DEF(0x04,6,6),
	LFT_SPPU_DAC_IOTEST_RESULT8                             = REG16_DEF(0x04,7,7),
	LFT_SPPU_DAC_IOTEST_RESULT9                             = REG16_DEF(0x04,8,8),
	LFT_SPPU_DAC_IOTEST_RESULT10                             = REG16_DEF(0x04,9,9),
	LFT_SPPU_DAC_IOTEST_RESULT11                             = REG16_DEF(0x04,10,10),
	LFT_SPPU_DAC_IOTEST_RESULT12                             = REG16_DEF(0x04,11,11),
	LFT_SPPU_DAC_IOTEST_RESULT13                             = REG16_DEF(0x04,12,12),
	LFT_SPPU_DAC_IOTEST_RESULT14                             = REG16_DEF(0x04,13,13),
	LFT_SPPU_DAC_IOTEST_RESULT15                             = REG16_DEF(0x04,14,14),
	LFT_SPPU_DAC_IOTEST_RESULT16                             = REG16_DEF(0x04,15,15),

	
	
	
	
	
	//enum of digital tab
	LFT_SPPU_DAC_Offset_adjust                               = REG16_DEF(0x00,15,15), // used in (digital)
	LFT_SPPU_DAC_Correct_corr_ena                            = REG16_DEF(0x00,13,13), //not in used
	LFT_SPPU_DAC_digital_filter_interpolation_interp         = REG16_DEF(0x00,8,11),  // interpolation(digital)
	LFT_SPPU_DAC_clkdiv_sync_ena                             = REG16_DEF(0x00,2,2),  // clock syn used in digital
	LFT_SPPU_DAC_invsinc_ena_compensate_IQ                   = REG16_DEF(0x00,1,1),   // USED IN DIGITAL
    LFT_SPPU_DAC_MIXER_cmix_mode                             = REG16_DEF(0x0D,12,15), // coarse mixer  (used in digital)  // doubtanother x10 value //
	LFT_SPPU_DAC_MIXER_reserved1                             = REG16_DEF(0x0D,11,11),
	LFT_SPPU_DAC_qmcGain_second                              = REG16_DEF(0x0D,0,10),   // (used in digital)
    LFT_SPPU_DAC_mixer_RESERVED                              = REG16_DEF(0x10,12,13),  // MIXER IN (DIGITAL)
	LFT_SPPU_DAC_qmc_phase                                   = REG16_DEF(0x10,0,11),   // PHASEAB USED IN DIGITAL 
	LFT_SPPU_DAC_Clock_receiver_sleep_clkrecv_sleep          = REG16_DEF(0x1A,4,4),   //(doubt another 0x18 value set)
	LFT_SPPU_DAC_mixer_ena                                   = REG16_DEF(0x02,6,6),       // mixer ena(digital)
    LFT_SPPU_DAC_NCO_Gain                                    = REG16_DEF(0x02,5,5),       //  (in digital )
	LFT_SPPU_DAC_NCO_ena                                     = REG16_DEF(0x02,4,4),      // in digital nco enable
	LFT_SPPU_DAC_SYNC_clkdiv_sync_sel                        = REG16_DEF(0x20,0,0),    // clock sysn used in digital
	LFT_SPPU_DAC_GRP_DELAY_I_RESERVED                        = REG16_DEF(0X2E,8,15),
    LFT_SPPU_DAC_GRP_DELAY_I_grpdelay                        = REG16_DEF(0X2E,0,7),   // GRP dealy I (used in digital)
    LFT_SPPU_DAC_GRP_DELAY_Q_grpdelay                        = REG16_DEF(0X2F,8,15),   // grp delay Q (used in digital)
    LFT_SPPU_DAC_GRP_DELAY_Q_RESERVED                        = REG16_DEF(0X2F,0,7),
    LFT_SPPU_DAC_GAIN_coarse_dac_gain                        = REG16_DEF(0X03,12,15),  // gain in  (used in digital)
    LFT_SPPU_DAC_NCO_MixAB_Sync_mixer                           = REG16_DEF(0X1F,12,15),               // nco mixed ab sync
	LFT_SPPU_DAC_RESERVED1                                   = REG16_DEF(0X1F,8,11),
	LFT_SPPU_DAC_NCO_Acc_SYNC                                = REG16_DEF(0X1F,4,7),                
	LFT_SPPU_DAC_Offset_first                                = REG16_DEF(0X08,0,12), 
	LFT_SPPU_DAC_OffsetB_second                              = REG16_DEF(0X09,0,12),
	LFT_SPPU_DAC_qmcgain_first                               = REG16_DEF(0X0C,0,10),   // USED IN DIGITAL(nother 0x10)
    LFT_SPPU_DAC_QMC_Offset_Sync                             = REG16_DEF(0X1E,12,15),   // USED IN DIGITAL
    LFT_SPPU_DAC_QMC_syncsel_RESERVED1                       = REG16_DEF(0X1E,8,11),
	LFT_SPPU_DAC_QMC_Correctsync                             = REG16_DEF(0X1E,4,7),  // used in digital
	LFT_SPPU_DAC_NCO_phase_offset_AB                         = REG16_DEF(0X12,0,15),           // used in digital
	LFT_SPPU_DAC_NCO_phase_offset_CD                         = REG16_DEF(0X13,0,15),          //  used in digital
    LFT_SPPU_DAC_NCO_DDS_AB_phase_add                        = REG16_DEF(0X14,0,15),         // USED IN (DIGITAL)
    LFT_SPPU_DAC_NCO_DDS_AB_phase_add1                       = REG16_DEF(0X15,0,15),        // USED IN (DIGITAL)
	LFT_SPPU_DAC_NCO_START                                   = REG16_DEF(0x02,0,15),      // MODIFIED ON AUG21
	
	// enum of input tab
	LFT_SPPU_DAC_FIFO_ena                                   = REG16_DEF(0x00,7,7),   // fifo enable (input)
	LFT_SPPU_DAC_sif4_ena                                   = REG16_DEF(0x02,7,7),       //    used in input
	LFT_SPPU_DAC_PLL_RESET                                  = REG16_DEF(0x18,12,12),    //reset bit  (input using)
    LFT_SPPU_DAC_PLL_Sync_pll_dividers_NDIVSYNC_ENA         = REG16_DEF(0x18,11,11),    // sync pll dividers (input)
    LFT_SPPU_DAC_PLL_ENA                                    = REG16_DEF(0x18,10,10),    // used in input
	LFT_SPPU_DAC_PLL_RESERVED2                              = REG16_DEF(0x18,8,9),
    LFT_SPPU_DAC_PLL_Charge_pump                            = REG16_DEF(0x18,6,7),    // used input
    LFT_SPPU_DAC_PLL_Prescaler                              = REG16_DEF(0x18,3,5),    //  presecler changed(input)
    LFT_SPPU_DAC_ATEST_FUSE_SLEEP                           = REG16_DEF(0x1B,11,11),   // used in input
	LFT_SPPU_DAC_Freq_tune_PLL_vco                          = REG16_DEF(0x1A,10,15),  //   used in input
    LFT_SPPU_DAC_opamp_off_bias_sleep                       = REG16_DEF(0x1A,7,7),    // used input
	LFT_SPPU_DAC_tsense_sleep                               = REG16_DEF(0x1A,6,6),
	LFT_SPPU_DAC_PLL_sleep                                  = REG16_DEF(0x1A,5,5),    // used in input
	LFT_SPPU_DAC_FIFO_input_sync                            = REG16_DEF(0x20,12,15),   // used in  input
	LFT_SPPU_DAC_FIFO_output_sync                           = REG16_DEF(0x20,0,8),     // used in input
	LFT_SPPU_DAC_GAIN_sif_txenable                          = REG16_DEF(0X03,0,0),    // used in input
	LFT_SPPU_DAC_dataformatter                              = REG16_DEF(0X1F,2,3),                // used in input
	LFT_SPPU_DAC_SIF_sync                                   = REG16_DEF(0X1F,1,1),                // (input & digital) 
	LFT_SPPU_DAC_FIFO_offset                                = REG16_DEF(0X09,13,15),    // (used in input)
	LFT_SPPU_DAC_PLL_m                                      = REG16_DEF(0X19,8,15),          // used in input
	LFT_SPPU_DAC_PLL_n                                      = REG16_DEF(0X19,4,7),            // used in input
	LFT_SPPU_DAC_PLL_vcoibiastune                           = REG16_DEF(0X19,2,3),           //       (input)    
	LFT_SPPU_DAC_LVDS_datadly                               = REG16_DEF(0X24,13,15), // used in input
	LFT_SPPU_DAC_LVDS_CLKdly                                = REG16_DEF(0X24,10,12),  // used in input
	LFT_SPPU_DAC_PLL_LFVOLT                                 = REG16_DEF(0x18,0,2),
	LFT_SPPU_DAC_PLL_STATUS_LOCK                            = REG16_DEF(0x05,5,5),   // doubt
	LFT_SPPU_DAC_NCO_ENABLE_STATE                           = REG16_DEF(0x1F,0,15), 
	
	
	
	LFT_SPPU_DAC_Alarm_out_ena                              = REG16_DEF(0x00,4,4),
    LFT_SPPU_DAC_Alarm_polarity_pos_neg                     = REG16_DEF(0x00,3,3),
	

	LFT_SPPU_DAC_16bit_in                                   = REG16_DEF(0x02,15,15),     //not in used
	LFT_SPPU_DAC_dacclkgone_ena                             = REG16_DEF(0x02,14,14),     //not in used
	LFT_SPPU_DAC_dataclkgone_ena                            = REG16_DEF(0x02,13,13),     //not in used
    LFT_SPPU_DAC_collisiongone_ena                          = REG16_DEF(0x02,12,12),     //not in used
    
   
    LFT_SPPU_DAC_revbus                                     = REG16_DEF(0x02,3,3),       //not in used
	LFT_SPPU_DAC_twos                                       = REG16_DEF(0x02,1,1),        //not in used
    
                
    LFT_SPPU_DAC_SPARES_ns_REV1                             = REG16_DEF(0x1C,8,15),    // not in used
	LFT_SPPU_DAC_SPARES_ns_REV2                             = REG16_DEF(0x1C,0,7),     // not in used


	LFT_SPPU_DAC_SPARES_EW_REV1                             = REG16_DEF(0x1D,8,15),   // not in used
	LFT_SPPU_DAC_SPARES_EW_REV2                             = REG16_DEF(0x1D,0,7),   // not in used


	
	


    LFT_SPPU_DAC_ATEST_extref_ena                           = REG16_DEF(0x1B,15,15),   // not in used
	LFT_SPPU_DAC_ATEST_RESERVED1                            = REG16_DEF(0x1B,14,14),   // not in used
	LFT_SPPU_DAC_ATEST_RESERVED2                            = REG16_DEF(0x1B,13,13),   // not in used
	LFT_SPPU_DAC_ATEST_RESERVED3                            = REG16_DEF(0x1B,12,12),   // not in used
	
	LFT_SPPU_DAC_ATEST_RESERVED4                            = REG16_DEF(0x1B,10,10),   // not in used
	LFT_SPPU_DAC_ATEST_RESERVED5                            = REG16_DEF(0x1B,9,9),     // not in used
	LFT_SPPU_DAC_ATEST_RESERVED6                            = REG16_DEF(0x1B,8,8),    //  not in used
	LFT_SPPU_DAC_ATEST_RESERVED7                            = REG16_DEF(0x1B,7,7),    // not in used
	LFT_SPPU_DAC_ATEST_RESERVED8                            = REG16_DEF(0x1B,6,6),    // not in used
	LFT_SPPU_DAC_ATEST_atest                                = REG16_DEF(0x1B,0,5),   // not in used

	
	LFT_SPPU_DAC_IOTEST_Result                              = REG16_DEF(0x04,0,15),  


	LFT_SPPU_DAC_resync_RESERVED1                           = REG16_DEF(0x2D,15,15),       // not in used
	LFT_SPPU_DAC_ostrtodig_sel                              = REG16_DEF(0x2D,14,14),       // not in used
    LFT_SPPU_DAC_ramp_ena                                   = REG16_DEF(0x2D,13,13),       // not in used
    LFT_SPPU_DAC_resync_RESERVED2                           = REG16_DEF(0x2D,1,12),       // not in used



	LFT_SPPU_DAC_sifdac_ena                                 = REG16_DEF(0x2D,0,0),
   


	
	LFT_SPPU_DAC_SYNC_RESERVED                              = REG16_DEF(0x20,1,7),    // not used
	
	LFT_SPPU_DAC_GAIN_RESERVED                              =  REG16_DEF(0X03,8,11),
	LFT_AC1_GAIN_RESERVED                                    =  REG16_DEF(0X03,1,7),
	

	
	LFT_SPPU_DAC_RESERVED2                                  =  REG16_DEF(0X1F,0,0),

	
    

	LFT_SPPU_DAC_LVDS_RESERVED                               =   REG16_DEF(0X24,0,9),

	LFT_SPPU_DAC_SIFDAC                                      =   REG16_DEF(0X30,0,15),


	//IO Test Result Reset
	LFT_SPPU_DAC_IO_TEST_RESULT_CLEAR						= REG16_DEF(0X04,0,15),

	//Alarm
	LFT_SPPU_DAC_READ_ALARM									= REG16_DEF(0X05,11,13),
	LFT_SPPU_DAC_WRITE_ALARM                                = REG16_DEF(0X05,0,15),
	LFT_SPPU_DAC1_TX_ENABLE									= REG16_DEF(0X18,6,6),
	LFT_SPPU_DAC2_TX_ENABLE									= REG16_DEF(0X18,7,7),	
	LFT_SPPU_DAC3_TX_ENABLE									= REG16_DEF(0X18,8,8),
	
	
	/* DEFULT REGISTER OF DAC */

	LFT_SPPU_DAC_ADDR0							=	REG16_DEF(0x00,0,16),
	LFT_SPPU_DAC_ADDR1							=	REG16_DEF(0x01,0,16),
	LFT_SPPU_DAC_ADDR2							=	REG16_DEF(0x02,0,16),
	LFT_SPPU_DAC_ADDR3							=	REG16_DEF(0x03,0,16),
	LFT_SPPU_DAC_ADDR4							=	REG16_DEF(0x04,0,16),
	LFT_SPPU_DAC_ADDR5							=	REG16_DEF(0x05,0,16),
	LFT_SPPU_DAC_ADDR6							=	REG16_DEF(0x06,0,16),
	LFT_SPPU_DAC_ADDR7							=	REG16_DEF(0x07,0,16),
	LFT_SPPU_DAC_ADDR8							=	REG16_DEF(0x08,0,16),
	LFT_SPPU_DAC_ADDR9						    =	REG16_DEF(0x09,0,16),
	LFT_SPPU_DAC_ADDR10							=	REG16_DEF(0x0A,0,16),
	LFT_SPPU_DAC_ADDR11							=	REG16_DEF(0x0B,0,16),
	LFT_SPPU_DAC_ADDR12							=	REG16_DEF(0x0C,0,16),
	LFT_SPPU_DAC_ADDR13							=	REG16_DEF(0x0D,0,16),
	LFT_SPPU_DAC_ADDR14							=	REG16_DEF(0x0E,0,16),
	LFT_SPPU_DAC_ADDR15							=	REG16_DEF(0x0F,0,16),
	LFT_SPPU_DAC_ADDR16							=	REG16_DEF(0x10,0,16),
	LFT_SPPU_DAC_ADDR17						    =	REG16_DEF(0x11,0,16),
	LFT_SPPU_DAC_ADDR18							=	REG16_DEF(0x12,0,16),
	LFT_SPPU_DAC_ADDR19							=	REG16_DEF(0x13,0,16),
	LFT_SPPU_DAC_ADDR20							=	REG16_DEF(0x14,0,16),
	LFT_SPPU_DAC_ADDR21							=	REG16_DEF(0x15,0,16),
	LFT_SPPU_DAC_ADDR22							=	REG16_DEF(0x16,0,16),
	LFT_SPPU_DAC_ADDR23							=	REG16_DEF(0x17,0,16),
	LFT_SPPU_DAC_ADDR24							=	REG16_DEF(0x18,0,16),
	LFT_SPPU_DAC_ADDR25							=	REG16_DEF(0x19,0,16),
	LFT_SPPU_DAC_ADDR26							=	REG16_DEF(0x1A,0,16),
	LFT_SPPU_DAC_ADDR27							=	REG16_DEF(0x1B,0,16),
	LFT_SPPU_DAC_ADDR28							=	REG16_DEF(0x1C,0,16),
	LFT_SPPU_DAC_ADDR29						    =	REG16_DEF(0x1D,0,16),
	LFT_SPPU_DAC_ADDR30					        =	REG16_DEF(0x1E,0,16),
	LFT_SPPU_DAC_ADDR31						    =	REG16_DEF(0x1F,0,16),
	LFT_SPPU_DAC_ADDR32						    =	REG16_DEF(0x20,0,16),
	LFT_SPPU_DAC_ADDR33						    =	REG16_DEF(0x22,0,16),
	LFT_SPPU_DAC_ADDR34							=	REG16_DEF(0x23,0,16),
	LFT_SPPU_DAC_ADDR35							=	REG16_DEF(0x24,0,16),
	LFT_SPPU_DAC_ADDR36						    =	    REG16_DEF(0x25,0,16),
	LFT_SPPU_DAC_ADDR37							=	REG16_DEF(0x26,0,16),
	LFT_SPPU_DAC_ADDR38							=	REG16_DEF(0x27,0,16),
	LFT_SPPU_DAC_ADDR39							=	REG16_DEF(0x28,0,16),
	LFT_SPPU_DAC_ADDR40							=	REG16_DEF(0x29,0,16),
	LFT_SPPU_DAC_ADDR41							=	REG16_DEF(0x2A,0,16),
	LFT_SPPU_DAC_ADDR42						    =  	REG16_DEF(0x2B,0,16),
	LFT_SPPU_DAC_ADDR43							=	REG16_DEF(0x2C,0,16),
	LFT_SPPU_DAC_ADDR44							=	REG16_DEF(0x2D,0,16),
	LFT_SPPU_DAC_ADDR45						    =	REG16_DEF(0x2E,0,16),
	LFT_SPPU_DAC_ADDR46							=	REG16_DEF(0x2F,0,16),
	LFT_SPPU_DAC_ADDR47							=	REG16_DEF(0x30,0,16),
	LFT_SPPU_DAC_ADDR48					        =	REG16_DEF(0x7F,0,16),

	//3 wire to 4 wire mode
	LFT_SPPU_DAC_WIRE_MODE						=	REG16_DEF(0x02,0,16),


	/***************************************************************power on self test***********************************************************/
	LFT_SPPU_RUN_TEST_DAC_FPGA_INTERFACE                           = REG16_DEF(0X02,0,16)

	};

	#pragma endregion