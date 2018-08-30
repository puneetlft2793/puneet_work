#pragma once

#define REG16_DEF(adds, start, end) ((adds << 16) | (start << 8) | (end-start+1))

#define FPGA_BASE_ADDRESS      

#pragma region Enumeration SPPU Registers

// DEFINATION of ALL dac register here

typedef enum SPPUFPGARegsDefs
{

	/*********************** To Access DAC Registers *****************************/
	LFT_SPPU_FPGA_SPI_DAC_NUM									= REG16_DEF(0x1000,2,3),
	LFT_SPPU_FPGA_SPI_DAC_ADR									= REG16_DEF(0x1000,8,14),
	LFT_SPPU_FPGA_SPI_DAC_WR_VAL								= REG16_DEF(0x1000,16,31),
	LFT_SPPU_FPGA_SPI_DAC_RD_VAL								= REG16_DEF(0x1004,16,31),
	LFT_SPPU_FPGA_SPI_DAC_WR									= REG16_DEF(0x1000,0,0),
	LFT_SPPU_FPGA_SPI_DAC_RD									= REG16_DEF(0x1000,1,1),
	LFT_SPPU_FPGA_SPI_DAC_READY_READ							= REG16_DEF(0x1004,0,0),
	/*****************************************************************************/

	/*********************** To Access LMK Registers *****************************/
	LFT_SPPU_FPGA_SPI_LMK_ADR									= REG16_DEF(0x100C,10,14),
	LFT_SPPU_FPGA_SPI_LMK_WR_VAL								= REG16_DEF(0x1010,5,31),
	LFT_SPPU_FPGA_SPI_LMK_RD_VAL								= REG16_DEF(0x1014,5,31),
	LFT_SPPU_FPGA_SPI_LMK_WR									= REG16_DEF(0x100C,0,0),
	LFT_SPPU_FPGA_SPI_LMK_RD									= REG16_DEF(0x100C,1,1),
	LFT_SPPU_FPGA_SPI_LMK_POST_CLOCK							= REG16_DEF(0x100C,2,9),
	LFT_SPPU_FPGA_SPI_LMK_SYNC_EN_AUTO							= REG16_DEF(0x100C,15,15),
	LFT_SPPU_FPGA_SPI_LMK_READY_READ							= REG16_DEF(0x1014,0,0),
	/*****************************************************************************/
	
	/*********************** To Access ATTEANUATOR Registers *****************************/
	LFT_SPPU_FPGA_SPI_ATT_NUM									= REG16_DEF(0x1008,1,1),
	LFT_SPPU_FPGA_SPI_ATT_ADR									= REG16_DEF(0x1008,3,10),
	LFT_SPPU_FPGA_SPI_ATT_WR_VAL								= REG16_DEF(0x1008,11,18),
	LFT_SPPU_FPGA_SPI_ATT_RD_VAL								= REG16_DEF(0x1008,20,20),
	LFT_SPPU_FPGA_SPI_ATT_WR									= REG16_DEF(0x1008,0,0),
	LFT_SPPU_FPGA_SPI_ATT_READY_READ							= REG16_DEF(0x1008,2,2),
	LFT_SPPU_FPGA_SPI_ATT_RD									= REG16_DEF(0x1008,19,19),
	
	/*****************************************************************************/
								       
	LFT_SPPU_FPGA_WRITE_AXIS_BURST_LENGTH						= REG16_DEF(0x0118,0,7), // both are common for read and writhe
	LFT_SPPU_FPGA_WRITE_START_ADDRESS							= REG16_DEF(0x0100,0,31),
	LFT_SPPU_FPGA_WRITE_WRAP_ADDRESS							= REG16_DEF(0x0104,0,31),
	LFT_SPPU_FPGA_WRITE_START_ADDRESS_MSB						= REG16_DEF(0x0104,0,1),
	
	LFT_SPPU_FPGA_WRITE_SIZE									= REG16_DEF(0x0108,0,31),
	LFT_SPPU_FPGA_WRITE_SIZE_MSB								= REG16_DEF(0x0104,2,3),
	
	LFT_SPPU_FPGA_WRITE_INDEFINITE								= REG16_DEF(0x0118,8,8),
	
  
	LFT_SPPU_FPGA_WRITE_DATA_PULSE								= REG16_DEF(0x0118,10,10),
	LFT_SPPU_FPGA_READ_DATA_PULSE								= REG16_DEF(0x0118,11,11),
	LFT_SPPU_FPGA_WRITE_COMPLETE								= REG16_DEF(0x011C,1,1),	

	//Added 4 new Reg Settings : DDR Bulk Read
	LFT_SPPU_FPGA_READ_WRAP_ADDRESS								= REG16_DEF(0x0110,0,31),
	LFT_SPPU_FPGA_DDR_READ_START_ADDRESS						= REG16_DEF(0x010C,0,31),
	LFT_SPPU_FPGA_DDR_READ_SIZE									= REG16_DEF(0x0114,0,31),
	LFT_SPPU_FPGA_DDR_READ_INDEFINITE							= REG16_DEF(0x0118,9,9),
	
	
	LFT_SPPU_FPGA_TEST_MODULE									= REG16_DEF(0x000C,4,4),
	LFT_SPPU_FPGA_DDR_DATATYPE									= REG16_DEF(0x000C,0,1),
	LFT_SPPU_FPGA_DDR_DATAPATTERN								= REG16_DEF(0x0008,0,31),
	LFT_SPPU_FPGA_DDR_TEST_WRITESIZE							= REG16_DEF(0x0000,0,31), // chenge on aug13
	LFT_SPPU_FPGA_DDR_TEST1										= REG16_DEF(0x000C,2,2),
  
  
	LFT_SPPU_FPGA_DDR_BUSY_CHECK1								= REG16_DEF(0x011C,1,1),
	LFT_SPPU_FPGA_DDR_BUSY_CHECK2								= REG16_DEF(0x0010,1,1),
  
  
	LFT_SPPU_FPGA_DDR_TEST_WRITESIZE1							= REG16_DEF(0x0004,0,31),
	LFT_SPPU_FPGA_DDR_TEST2										= REG16_DEF(0x000C,3,3),
	LFT_SPPU_FPGA_DDR_BUSY_CHECK12								= REG16_DEF(0x011C,2,2),
	LFT_SPPU_FPGA_DDR_BUSY_CHECK22								= REG16_DEF(0x0010,2,2),

	LFT_SPU_FPGA_TEST_CASE_PASS									= REG16_DEF(0x0010,7,7),


	LFT_SPPU_FPGA_READ_AXIS_BURST_LENGTH						= REG16_DEF(0x2118,0,7),
	LFT_SPPU_FPGA_READ_START_ADDRESS							= REG16_DEF(0x210C,0,31),
	LFT_SPPU_FPGA_READ_WRAPPER_ADDRESS							= REG16_DEF(0x2110,0,31),

	LFT_SPPU_FPGA_READ_START_ADDRESS_MSB						= REG16_DEF(0x2110,0,1),

	LFT_SPPU_FPGA_READ_SIZE										= REG16_DEF(0x2114,0,31),
	LFT_SPPU_FPGA_READ_SIZE_MSB									= REG16_DEF(0x2110,2,3),

	LFT_SPPU_FPGA_READ_INDEFINITE								= REG16_DEF(0x2118,9,9),	

	LFT_SPPU_FPGA_READ_AXIS_BURST_LENGTH_CH2					= REG16_DEF(0x2158,0,7),
	LFT_SPPU_FPGA_READ_START_ADDRESS_CH2						= REG16_DEF(0x214C,0,31),

	LFT_SPPU_FPGA_READ_START_ADDRESS_MSB_CH2					= REG16_DEF(0x2150,0,1),

	LFT_SPPU_FPGA_READ_WRAPPER_ADDRESS_CH2						= REG16_DEF(0x2150,0,31),
	LFT_SPPU_FPGA_READ_SIZE_CH2									= REG16_DEF(0x2154,0,31),

	LFT_SPPU_FPGA_READ_SIZE_MSB_CH2								= REG16_DEF(0x2150,2,3),

	LFT_SPPU_FPGA_READ_INDEFINITE_CH2							= REG16_DEF(0x2158,9,9),

	
	LFT_SPPU_FPGA_DAC_SETUP_AMPLITUDE_LEVEL						= REG16_DEF(0x00,0,0),
	LFT_SPPU_FPGA_DAC_SETUP_IQ_SAMPLING_RATE					= REG16_DEF(0x00,0,0),

	LFT_SPPU_FPGA_DAC_SETUP_INTERPOLATION						= REG16_DEF(0x5000,16,17),
	LFT_SPPU_FPGA_DAC_SETUP_STEP_PULSE							= REG16_DEF(0x5000,15,15),

	LFT_SPPU_FPGA_DAC_SETUP_PULSEWIDTH_DAC0						= REG16_DEF(0x2008,0,31),
	LFT_SPPU_FPGA_DAC_SETUP_READ_FROM_DAC0 						= REG16_DEF(0x200C,0,0),

	LFT_SPPU_FPGA_DAC_SETUP_PULSEWIDTH_DAC1						= REG16_DEF(0x2014,0,31),
	LFT_SPPU_FPGA_DAC_SETUP_READ_FROM_DAC1 						= REG16_DEF(0x200C,3,3),

	LFT_SPPU_FPGA_DAC_SETUP_NCO_OUTPUT_FREQUENCY				= REG16_DEF(0x00,0,0),
	LFT_SPPU_FPGA_DAC_SETUP_CLOCK_SOURCE						= REG16_DEF(0x00,0,0),
	
	//Trigger Setup
	LFT_SPPU_FPGA_TRIGGER_PRI									= REG16_DEF(0x2004,0,31),
	LFT_SPPU_FPGA_TRIGGER_WIDTH									= REG16_DEF(0x2000,0,31),
	LFT_SPPU_FPGA_TRIGGER_ENABLE								= REG16_DEF(0x200C,1,1),
	LFT_SPPU_FPGA_TRIGGER_START									= REG16_DEF(0x200C,2,2),	

	LFT_SPPU_FPGA_clock_Setup_DAC_DATA_CLK						= REG16_DEF(0x5000,0,0),
	LFT_SPPU_FPGA_clock_Setup_FPGA_OUT_CLK						= REG16_DEF(0x00,0,0),
	LFT_SPPU_FPGA_clock_Setup_PLL_LOCK_STATUS					= REG16_DEF(0x1010,0,0),
	LFT_SPPU_FPGA_clock_Setup_DAC_FIFO_ENTRY_ERROR				= REG16_DEF(0x00,0,0),

	LFT_SPPU_FPGA_RESET_FPGA									= REG16_DEF(0x5000,9,9),
	LFT_SPPU_FPGA_MAX_OP_TEMP									= REG16_DEF(0x5014,0,6), // 2OTHAUG

	//Update Clock Frequency Status
	LFT_SPPU_FPGA_RESET_CLOCK_COUNTER							= REG16_DEF(0x5000,7,7),
	LFT_SPPU_FPGA_SET_TIMING_WINDOW								= REG16_DEF(0x5004,0,31),
	LFT_SPPU_FPGA_START_CLOCK_COUNTER							= REG16_DEF(0x5000,8,8),
	LFT_SPPU_FPGA_OUT_CLOCK_FREQUENCY							= REG16_DEF(0x5008,0,31),
	LFT_SPPU_FPGA_DAC_DATA_CLOCK_FREQUENCY						= REG16_DEF(0x500C,0,31),

	//DAC Reset
	LFT_SPPU_FPGA_DAC_RESET_set0									= REG16_DEF(0x2018,0,0),
	LFT_SPPU_FPGA_DAC_RESET_set1									= REG16_DEF(0x2018,1,1),
	LFT_SPPU_FPGA_DAC_RESET_set2									= REG16_DEF(0x2018,2,2),
	LFT_SPPU_FPGA_DAC_RESET_set3									= REG16_DEF(0x2018,3,3),
	LFT_SPPU_FPGA_DAC_RESET_set4									= REG16_DEF(0x2018,4,4),
	LFT_SPPU_FPGA_DAC_RESET_set5									= REG16_DEF(0x2018,5,5),
	LFT_SPPU_FPGA_DAC_RESET_set6									= REG16_DEF(0x2018,6,6),
	LFT_SPPU_FPGA_DAC_RESET_set7									= REG16_DEF(0x2018,7,7),
	LFT_SPPU_FPGA_DAC_RESET_set8									= REG16_DEF(0x2018,8,8),
	LFT_SPPU_FPGA_DAC_RESET_set9									= REG16_DEF(0x2018,9,9),		//__HP__1; Added this line
	LFT_SPPU_FPGA_DAC_RESET_set10									= REG16_DEF(0x2018,10,10),
	LFT_SPPU_FPGA_SIGNAL_DELAY_DAC0									= REG16_DEF(0x201C,0,31),
	LFT_SPPU_FPGA_SIGNAL_DELAY_DAC1									= REG16_DEF(0x2020,0,31),
	
	//Training Pattern
	LFT_SPPU_FPGA_TRAINING_PATTERN1								= REG16_DEF(0x2204,0,31),
	LFT_SPPU_FPGA_TRAINING_PATTERN2								= REG16_DEF(0x2208,0,31),
	LFT_SPPU_FPGA_TRAINING_PATTERN3								= REG16_DEF(0x220C,0,31),
	LFT_SPPU_FPGA_TRAINING_PATTERN4								= REG16_DEF(0x2210,0,31),
	LFT_SPPU_FPGA_TRAINING_PATTERN5								= REG16_DEF(0x2214,0,8),

	LFT_SPPU_FPGA_TRAINING_PATTERN_ENABLE						= REG16_DEF(0x2200,0,0),
	LFT_SPPU_FPGA_operation_Mode_RF_IF							= REG16_DEF(0x2200,1,2),
	LFT_SPPU_FPGA_GENERAL_PURPOSE_REG							= REG16_DEF(0x5018,0,31), // ADD ON 20TH AUG
	LFT_SPPU_FPGA_GENERAL_PURPOSE_DAC_IN						= REG16_DEF(0x5018,0,0),  // ADD ON 25TH AUG
	LFT_SPPU_FPGA_GENERAL_PURPOSE_LMK_IN						= REG16_DEF(0x5018,1,1),  // ADD ON 25TH AUG
	/************************************************* power on self test*************************************************************************/
	
	LFT_SPPU_RUN_TEST_FPGA                                         = REG16_DEF(0X08,0,31),  // REGISTER ADDRESS DOUBT    
	LFT_SPPU_RUN_TEST_SPI_FLASH_STRADDER                           = REG16_DEF(0X0244,0,31),
	LFT_SPPU_RUN_TEST_SPI_FLASH_FILE_SIZE                          = REG16_DEF(0X024C,0,31),
	LFT_SPPU_RUN_TEST_SPI_FLASH_FILE_MODE_ENABLE                   = REG16_DEF(0X0240,0,4),
	LFT_SPPU_RUN_TEST_SPI_FLASH_BUSY_CHECK                         = REG16_DEF(0X0250,0,0),
	LFT_SPPU_RUN_TEST_SPI_FLASH_WRTIE_NOR                          = REG16_DEF(0X0248,0,31),
	LFT_SPPU_RUN_TEST_SPI_FLASH_READ_NOR                           = REG16_DEF(0X0254,0,31),
	LFT_SPPU_RUN_TEST_I2C_MSGCODE                                  = REG16_DEF(0X4100,12,19),
	LFT_SPPU_RUN_TEST_I2C_MSGSIZE                                  = REG16_DEF(0X4100,4,11),
	LFT_SPPU_RUN_TEST_I2C_DEVICE_ADD                               = REG16_DEF(0X4104,16,31),
	LFT_SPPU_RUN_TEST_I2C_RESISTER_ADD                             = REG16_DEF(0X4104,0,15),
	LFT_SPPU_RUN_TEST_I2C_DATA_WRITE                               = REG16_DEF(0X4108,0,7),
	LFT_SPPU_RUN_TEST_I2C_DATA_WRITE_ENB                           = REG16_DEF(0X4100,0,0),
	LFT_SPPU_RUN_TEST_I2C_DATA_READ_ENB                            = REG16_DEF(0X4100,2,2),

	LFT_SPPU_RUN_TEST_I2C_MSG_VALID                                = REG16_DEF(0X4100,20,20),
	LFT_SPPU_RUN_TEST_I2C_BUSY_CHECK                               = REG16_DEF(0X410C,0,0),
	LFT_SPPU_RUN_TEST_I2C_BUSY_CHECK1                              = REG16_DEF(0X410C,3,3),
	LFT_SPPU_RUN_TEST_READ_DATA                                    = REG16_DEF(0X4110,0,7),
	LFT_SPPU_RUN_TEST_TRIGGER_IN_CHECK_PLUSE                       = REG16_DEF(0X200C,4,4),
	LFT_SPPU_RUN_TEST_TRIGGER_IN_CHECK                             = REG16_DEF(0X200C,5,5),
	LFT_SPPU_RUN_TEST_FPGA_WRITE_COMPLETE						   = REG16_DEF(0x011C,0,0),	
	LFT_SPPU_VERSION_REG                                           = REG16_DEF(0x0010,24,31),   // 5TH OCT	

	LFT_SPPU_RUN_TEST_TEMP										   = REG16_DEF(0x501C,16,16),	// ADD ON 20TH AUG	
	
	LFT_SPPU_FPGA_RESET_DDR										   = REG16_DEF(0x5000,3,3),
	LFT_SPPU_FPGA_RESET_DAC										   = REG16_DEF(0x5000,2,2),




	LFT_CENTROIED_DATASELECT										= REG16_DEF(0X0000,4,4),  // _chenged new 1.1.2016
	LFT_CENTROIED_RAMWREN											= REG16_DEF(0X0000,5,5),//// _chenged new 1.1.2016
	LFT_CENTROIED_I2CBUSY											= REG16_DEF(0X0008,22,22),
	LFT_CENTROIED_I2CCMDCODE										= REG16_DEF(0X0000,1,8),
	LFT_CENTROIED_datasize											= REG16_DEF(0X0000,9,16),
	LFT_CENTROIED_i2c_no_stop										= REG16_DEF(0X0000,28,28),
	LFT_CENTROIED_i2c_data_rdack									= REG16_DEF(0X0000,30,30),
	LFT_CENTROIED_i2c_speed											= REG16_DEF(0X0004,24,26),
	LFT_CENTROIED_i2c_regoffset										= REG16_DEF(0X0004,0,15),
	LFT_CENTROIED_i2c_slave_addr									= REG16_DEF(0X0000,17,26),
	LFT_CENTROIED_i2c_data_in_valid									= REG16_DEF(0X0000,29,29),
	LFT_CENTROIED_i2c_data_in								        = REG16_DEF(0X0004,16,23),
	LFT_CENTROIED_i2c_cmd_exe								        = REG16_DEF(0X0000,0,0),
	LFT_CENTROIED_I2c_data_out_valid                                = REG16_DEF(0X0008,21,21),
	LFT_CENTROIED_I2c_data_out                                      = REG16_DEF(0X0008,8,15),
	LFT_CENTROIED_I2c_read_ack                                      = REG16_DEF(0X0008,8,15),
	
	// __FC__ Adding Cenroid_appplication code, __HP__ , 24 May 2016. Revised 13 June 2016 HP.
	
	//Reg 0x00
	LFT_CENTROIED_FPGA_IMAGE_VERSION								= REG16_DEF(0X0000,0,31),
	LFT_CENTROIED_FPGA_STREAM_SELECT								= REG16_DEF(0X0000,0,7),

	//Reg 0x04
	LFT_CENTROIED_Design_Reset										= REG16_DEF(0X0004,0,0),
	LFT_CENTROIED_Ddr_Start_Retrive									= REG16_DEF(0X0004,1,1),
	LFT_CENTROIED_Ddr_Start_Record									= REG16_DEF(0X0004,2,2),
	LFT_CENTROIED_Stream_Enable										= REG16_DEF(0X0004,3,3),
	LFT_CENTROIED_Threshold_Vlaue									= REG16_DEF(0X0004,4,11),		//
	LFT_CENTROIED_Cam_Frame_Rate									= REG16_DEF(0X0004,12,13),
	LFT_CENTROIED_DAC_Output_Range_Control							= REG16_DEF(0X0004,14,16),
	LFT_CENTROIED_ADC_Input_Range_Control							= REG16_DEF(0X0004,17,19),
	LFT_CENTROIED_Stream_FIFO_Reset									= REG16_DEF(0X0004,31,31),
	LFT_CENTROIED_Stream_Design_Reset								= REG16_DEF(0X0004,0,0),

	//Reg 0x08
	LFT_CENTROIED_Capture_Done										= REG16_DEF(0x0008,0,0),
	LFT_CENTROIED_Ddr_Upload_Done									= REG16_DEF(0x0008,1,1),
	LFT_CENTROIED_Read_Done											= REG16_DEF(0x0008,2,2),		//Reading DDR

	//Reg 0x0C
	LFT_CENTROIED_Num_Centroid_Data_Size_Read						= REG16_DEF(0X000C,0,31),		//This size has to be multiplied by 8 for actual data size in bytes., Laki

	//Reg 0x10
	LFT_CENTROIED_Num_Frame_Data_Size_Read							= REG16_DEF(0X0010,0,31),		//This size has to be multiplied by 4 for actual data size in bytes., Laki

	//Reg 0x14
	LFT_CENTROIED_DDR_Rd_WR_end_Address								= REG16_DEF(0X0014,0,31),	
	
	//Reg 0x18
	//LFT_CENTROIED_DDR_Frame_RateConfig								= REG16_DEF(0X0018,0,31),	
	//Reg 0x28
	LFT_CENTROIED_DDR_Frame_RateConfig								= REG16_DEF(0X0028,0,31),	
//----------------------------------------------------------------------------------------------.


	LFT_SIC_RAM_Reset_SW										   = REG16_DEF(0x0000,0,0),
	LFT_SIC_WriteComplet_SRAM									   = REG16_DEF(0x0000,1,1),
	LFT_SIC_ReadComplet_SRAM									   = REG16_DEF(0x0000,2,2),
	LFT_SIC_ErrorReading_SRAM									   = REG16_DEF(0x0000,31,31),
	LFT_CENTROIED_sram_dataselect                                  = REG16_DEF(0X0000,4,4),
	LFT_CENTROIED_sram_wren                                        = REG16_DEF(0X0000,5,5),
	LFT_CENTROIED_sram_write_add                                   = REG16_DEF(0X0000,6,25),
	LFT_CENTROIED_sram_write_data                                  = REG16_DEF(0X0004,0,15),
	LFT_CENTROIED_Frame_Count	                                   = REG16_DEF(0X1C,0,31),
	LFT_CENTROIED_Time_Count	                                   = REG16_DEF(0X20,0,31),
	LFT_CENTROIED_Byte_Count	                                   = REG16_DEF(0X24,0,31),

	LFT_CENTROIED_sram_read                                        = REG16_DEF(0X0008,0,0),
	LFT_CENTROIED_sram_read_add                                    = REG16_DEF(0X0008,1,20),

	LFT_CENTROIED_sram_read_data                                   = REG16_DEF(0X0004,16,31),

	LFT_CENTROIED_spiflash_inserttype                              = REG16_DEF(0X0240,0,4),
	LFT_CENTROIED_spiflash_busycheck                               = REG16_DEF(0X0250,0,0),

	LFT_CENTROIED_spiflash_writetype                               = REG16_DEF(0X0240,25,26),
	LFT_CENTROIED_spiflash_add_in                                  = REG16_DEF(0X0244,0,31),
	LFT_CENTROIED_spiflash_flash_size                              = REG16_DEF(0X024c,0,31),

	LFT_CENTROIED_almost_fullcheck									= REG16_DEF(0X0250,1,1),
	LFT_CENTROIED_spiFlashFifoDataIn								=REG16_DEF(0X0248,0,31),
	LFT_CENTROIED_spiFlashFifoDataout								=REG16_DEF(0X0254,0,31),
	LFT_CENTROIED_emtycheck											=REG16_DEF(0X0250,2,2),

	LFT_CENTROIED_PARALLELNORFLASH_strtadd							=REG16_DEF(0X000,0,31),
	LFT_CENTROIED_PARALLELNORFLASH_blocksize						=REG16_DEF(0X004,0,31),
	LFT_CENTROIED_PARALLELNORFLASH_memory_busy						=REG16_DEF(0X001C,31,31),
	LFT_CENTROIED_PARALLELNORFLASH_flash_busy						=REG16_DEF(0X001C,30,30),
	LFT_CENTROIED_PARALLELNORFLASH_Block_write_ready				=REG16_DEF(0X001C,0,0),
	LFT_CENTROIED_PARALLELNORFLASH_writedata						=REG16_DEF(0X000C,0,31),
	LFT_CENTROIED_PARALLELNORFLASH_readdata							=REG16_DEF(0X0014,0,31),
	LFT_CENTROIED_PARALLELNORFLASH_blockreadready					=REG16_DEF(0X0010,2,2),
	LFT_CENTROIED_PARALLELNORFLASH_rw_status						=REG16_DEF(0X0018,0,0),
	LFT_CENTROIED_PARALLELNORFLASH_word_count						=REG16_DEF(0X0020,0,31),

	LFT_AIPB_SIC_write_frame_size									=REG16_DEF(0X08,0,31),

	LFT_AIPB_SIC_start_avg_flag										=REG16_DEF(0X000,0,0),
	LFT_AIPB_SIC_senSorIntigration_TIme								=REG16_DEF(0X000,12,15),
	LFT_AIPB_SIC_CalibratedImage_OnOff								=REG16_DEF(0X000,2,2),
	LFT_AIPB_SIC_CalibratedImage_Pulse								=REG16_DEF(0X000,3,3),
	LFT_AIPB_SIC_BitFile_Check										=REG16_DEF(0x003C,0,4),
	LFT_AIPB_SIC_Device_Reset										=REG16_DEF(0X000,31,31),
	LFT_AIPB_SIC_frame_rd_disable									=REG16_DEF(0X000,0,31),
	LFT_AIPB_SIC_frame_size											=REG16_DEF(0X008,0,31),
	LFT_AIPB_SIC_frame_wr_flag										=REG16_DEF(0X000,8,8),
	LFT_AIPB_SIC_puts_select_sector									=REG16_DEF(0X000,4,7),
	LFT_AIPB_SIC_sram_rd_flag										=REG16_DEF(0X000,1,1),
	LFT_AIPB_SIC_frame_rd_flag										=REG16_DEF(0X000,9,9),
	LFT_AIPB_SIC_start_avg_done									    =REG16_DEF(0X004,0,0),
	LFT_AIPB_SIC_flash_ready_out									=REG16_DEF(0X004,1,1),
	LFT_AIPB_SIC_Bulk_data                                          =REG16_DEF(0x4200,0,31),
	LFT_AIPB_SIC_Bulk_write_data0                                   =REG16_DEF(0x4204,0,31),
	LFT_AIPB_SIC_block_write										=REG16_DEF(0X0010,0,0),
	LFT_AIPB_SIC_block_read										    =REG16_DEF(0X0010,1,1),
	LFT_AIPB_SIC_strtadd											=REG16_DEF(0X000,0,31),
	LFT_AIPB_SIC_word_count											=REG16_DEF(0X0020 ,0,31),
	LFT_AIPB_SIC_memory_busy										=REG16_DEF(0X001C,31,31),
	LFT_AIPB_SIC_flash_busy											=REG16_DEF(0X001C,30,30),
	LFT_AIPB_SIC_Block_write_ready									=REG16_DEF(0X001C,0,0),
	LFT_AIPB_SIC_block_page_write									=REG16_DEF(0X0008,3,3),
	LFT_AIPB_SIC_writedata						                    =REG16_DEF(0X000C,0,31),
	LFT_AIPB_SIC_blockreadready										=REG16_DEF(0X0010,2,2),
	LFT_AIPB_SIC_SRAM_Wrt_Pulse										=REG16_DEF(0X0010,0,0),
	LFT_AIPB_SIC_SRAM_Rd_Pulse										=REG16_DEF(0X0010,0,0),
	LFT_AIPB_SIC_ChipErase											=REG16_DEF(0X0008,1,1),
	LFT_AIPB_SIC_PNOR_ChipErase										=REG16_DEF(0X0008,1,1),
	LFT_AIPB_SIC_internal_data_rw_done								=REG16_DEF(0X01C,2,2),
	LFT_AIPB_SIC_DataMismatc_Check									=REG16_DEF(0X01C,1,1),
	LFT_AIPB_SIC_block_size 								        =REG16_DEF(0X004,0,31),
	LFT_AIPB_SIC_rw_status											=REG16_DEF(0X0018,0,0),
	LFT_AIPB_SIC_Read_status										=REG16_DEF(0X0018,30,30),
	LFT_AIPB_SIC_readdata							                =REG16_DEF(0X0014,0,31),
	LFT_AIPB_SIC_block_sector_erase									=REG16_DEF(0X0008,1,1),
	LFT_AIPB_SIC_DataGen_Mode										=REG16_DEF(0X0008,0,0),
	LFT_AIPB_SIC_DataGen_ModeSel									=REG16_DEF(0X0024,0,0),
	LFT_AIPB_SIC_SRAM_Wrt_Stat										=REG16_DEF(0X0018,1,1),
	LFT_AIPB_SIC_SRAM_Rd_Stat										=REG16_DEF(0X0018,0,0),
	LFT_AIPB_SIC_SRAM_RD_Bulk										=REG16_DEF(0X0010,1,1),
	
	LFT_AIPB_SIC_DDR3_WriteSize										=REG16_DEF(0X0000,0,31),
	
	LFT_AIPB_SIC_DDR3_checker										=REG16_DEF(0X000C,4,4),
	LFT_AIPB_SCS_DDR3_checker										=REG16_DEF(0x0000028C,4,4),
	LFT_FPGA_SCS_DDR_SEL											=REG16_DEF(0x00000398,12,12),
	LFT_FPGA_SCS_DDR_INIT											=REG16_DEF(0x00000290,0,0),

	LFT_AIPB_SIC_DDR3_wait_init										=REG16_DEF(0X0010,0,0),
	LFT_AIPB_SIC_DDR3_writeStartAddr								=REG16_DEF(0X0100,0,31),
	LFT_AIPB_SIC_DDR3_writeEndAddr									=REG16_DEF(0X0108,0,31),
	LFT_AIPB_SIC_DDR3_writeSize										=REG16_DEF(0X0000,0,31),
	LFT_AIPB_SIC_DDR3_dataType										=REG16_DEF(0X000C,0,1),
	LFT_AIPB_SIC_DDR3_WritePulse 									=REG16_DEF(0X000C,2,2),
	LFT_AIPB_SIC_DDR3_ReadPulse 									=REG16_DEF(0X000C,3,3),
	
	LFT_AIPB_SIC_DDR3_WriteDone 									=REG16_DEF(0X011C,0,0),
	LFT_AIPB_SIC_DDR3_readStartAddr									=REG16_DEF(0X010C,0,31),
	LFT_AIPB_SIC_DDR3_readEndAddr									=REG16_DEF(0X0114,0,31),
	LFT_AIPB_SIC_DDR3_readSize										=REG16_DEF(0X0004,0,31),
	LFT_AIPB_SIC_DDR3_ReadDone 										=REG16_DEF(0X011C,2,2),
	LFT_AIPB_SIC_DDR3_CheckerResult									=REG16_DEF(0X0010,3,3),
	LFT_AIPB_SIC_DDR3_UART_SEND_WritePulse 							=REG16_DEF(0X3000,0,0),
	LFT_AIPB_SIC_DDR3_UART_SEND_ReadPulse 							=REG16_DEF(0X3000,1,1),
	LFT_AIPB_SIC_DDR3_UART_Write_DATA 								=REG16_DEF(0X4200,0,31),
	LFT_AIPB_SIC_DDR3_UART_Read_DATA 								=REG16_DEF(0X4200,0,31),


	LFT_AIPB_SIC_ETH_reg_0											=REG16_DEF(0X0000,0,31),		
	LFT_AIPB_SIC_ETH_reg_4											=REG16_DEF(0X0004,0,31),			
	LFT_AIPB_SIC_ETH_reg_fifo										=REG16_DEF(0X4200,0,31),

	LFT_CENT_EMMC_CMD_ARG											=REG16_DEF(0X04,0,31),
	LFT_CENT_EMMC_CMD_INDEX											=REG16_DEF(0X08,0,31),
	LFT_CENT_EMMC_Reset												=REG16_DEF(0X08,8,8),
	LFT_CENT_EMMC_CMD_SND_EN										=REG16_DEF(0X00,30,30),
	LFT_CENT_EMMC_CMD_FRMT											=REG16_DEF(0X00,29,29),
	LFT_CENT_EMMC_DATA_SND_EN										=REG16_DEF(0X00,31,31),
	LFT_CENT_EMMC_CMD_6												=REG16_DEF(0X00,3,3),
	LFT_CENT_EMMC_CLCK_SEL											=REG16_DEF(0X00,24,24),
	LFT_CENT_EMMC_REG_60											=REG16_DEF(0X0060,0,31),
	LFT_CENT_EMMC_REG_ADDR											=REG16_DEF(0X0008,0,31),
	LFT_CENT_EMMC_REG_ADDR1											=REG16_DEF(0X0009,0,31),
	LFT_CENT_EMMC_REG_ADDR2											=REG16_DEF(0X000A,0,31),
	LFT_CENT_EMMC_REG_ADDR_RX										=REG16_DEF(0X0018,0,31),
	LFT_CENT_EMMC_RX_DONE											=REG16_DEF(0X00,0,0),

	LFT_CENT_I2C_BUSY												=REG16_DEF(0X08,22,22),
	LFT_CENT_I2C_CMD_EXECUTE										=REG16_DEF(0X00,0,0),
	LFT_CENT_I2C_CMD_CODE											=REG16_DEF(0X00,1,8),
	LFT_CENT_I2C_DATA_SIZE											=REG16_DEF(0X00,9,16),
	LFT_CENT_I2C_SLAVE_ADDR											=REG16_DEF(0X00,17,26),
	LFT_CENT_I2C_NO_STOP											=REG16_DEF(0X00,28,28),
	LFT_CENT_I2C_DATA_IN_VALID										=REG16_DEF(0X00,29,29),
	LFT_CENT_I2C_DATA_RD_ACK										=REG16_DEF(0X00,30,30),
	LFT_CENT_I2C_REG_OFFSET											=REG16_DEF(0X04,0,15),
	LFT_CENT_I2C_SPEED 												=REG16_DEF(0X04,24,26),
	LFT_CENT_I2C_DATA_IN											=REG16_DEF(0X04,16,23),
	LFT_CENT_I2C_DATA_OUT											=REG16_DEF(0X08,8,15),
	LFT_CENT_I2C_DATA_OUT_VALID										=REG16_DEF(0X08,21,21),

	LFT_VAB_Mem_Init												=REG16_DEF(0x00,0,0),
	LFT_VAB_StartCapture											=REG16_DEF(0x00,1,1),
	LFT_VAB_StopCapture												=REG16_DEF(0x00,2,2),
	LFT_VAB_TakeSnapShot											=REG16_DEF(0x00,3,3),
	LFT_VAB_ReadFlashData											=REG16_DEF(0x00,4,4),
	LFT_VAB_MemErase												=REG16_DEF(0x00,5,5),
	LFT_VAB_RdReady													=REG16_DEF(0x00,6,6),
	LFT_VAB_ReadDone												=REG16_DEF(0x00,7,7),
	LFT_VAB_MemFull													=REG16_DEF(0x00,8,8),
	LFT_VAB_SetTime_Command											=REG16_DEF(0x00,9,9),
	LFT_VAB_GetTime_Command											=REG16_DEF(0x00,10,10),
	LFT_VAB_GetTime_RegReady										=REG16_DEF(0x00,11,11),
	LFT_VAB_Mem_ReadSize											=REG16_DEF(0x04,0,31),
	LFT_VAB_MemRead_StartAdd										=REG16_DEF(0x08,0,31),
	LFT_VAB_SetTime													=REG16_DEF(0x0C,0,31),
	LFT_VAB_GetTime													=REG16_DEF(0x10,0,31),


	LFT_VE_VideoEnhanc_AlgoSelect									=REG16_DEF(0x100,0,0),
	LFT_VE_ContrastEnhanc_AlgoSelect								=REG16_DEF(0x100,1,1),

	LFT_VE_PhotoMetric_Variance										=REG16_DEF(0x100,2,4),

	LFT_VE_GeometricVariance										=REG16_DEF(0x100,5,7),

	LFT_VE_SD_Mean													=REG16_DEF(0x104,0,10),

	LFT_VE_GainOffeset												=REG16_DEF(0x104,11,21),

	LFT_VE_SD_Gain_Limit											=REG16_DEF(0x104,22,29),
	
	LFT_VE_Color_Restoration_Alpha									=REG16_DEF(0x108,0,9),
	LFT_VE_Color_Restoration_Beta									=REG16_DEF(0x108,10,19),
	LFT_VE_Color_Gain_Compen										=REG16_DEF(0x108,20,29),
	LFT_VE_Color_Offset_Compen										=REG16_DEF(0x10C,0,9),

	LFT_VE_Small_Scale_Weight										=REG16_DEF(0x10C,10,19),
	LFT_VE_Large_Scale_Weight										=REG16_DEF(0x10C,20,29),
//******************************  ISTRAC Reg DEf **********************************************************/
	LFT_ISTRAC_LVDS_CTRL											=REG16_DEF(0x04,5,5),
	LFT_trigger_constant_active										=REG16_DEF(0x40,12,12),
	LFT_ISTRAC_DDS_CTRL												=REG16_DEF(0x04,5,5),
	LFT_ISTRAC_SnapSht_strt											=REG16_DEF(0x2F8,0,0),
	LFT_ISTRAC_SnapSht_stop											=REG16_DEF(0x2F8,1,1),
	LFT_ISTRAC_CH_sel												=REG16_DEF(0x2F8,12,15),
	LFT_ISTRAC_WND_sz												=REG16_DEF(0x2F8,16,31),
	LFT_ISTRAC_SSD_Sel												=REG16_DEF(0x004,8,11),
	LFT_ISTRAC_start_mem_acc										=REG16_DEF(0x0200,0,0),
	LFT_ISTRAC_stop_mem_acc											=REG16_DEF(0x0200,1,1),
	LFT_ISTRAC_SSD_start_Pulse										=REG16_DEF(0x022C,0,0),
	LFT_ISTRAC_memory_access_top_SSD_0								=REG16_DEF(0x0200,4,4),
	LFT_ISTRAC_memory_access_top_SSD_1								=REG16_DEF(0x0200,5,5),
	LFT_ISTRAC_memory_access_top_SSD_2								=REG16_DEF(0x0200,6,6),
	LFT_ISTRAC_memory_access_top_SSD_3								=REG16_DEF(0x0200,7,7),
	LFT_ISTRAC_RD_start_mem_acc										=REG16_DEF(0x22c,1,1),	
	/* playback setting (vaibhav) */
	LFT_ISTRAC_PB_Data_SRC_DAC_INTERFACE                            =REG16_DEF(0x000C,7,7),
	LFT_ISTRAC_PB_0x0140_BIT_NO_0                                   =REG16_DEF(0x0140,0,0),
	LFT_ISTRAC_PB_Trigger_Enabe                                     =REG16_DEF(0x00C8,5,5),
	LFT_ISTRAC_PB_TGR_SOURCE_PB                                     =REG16_DEF(0x00C8,4,4),
	LFT_ISTRAC_PB_sw_trigger_start_pulse_pb                         =REG16_DEF(0x00C8,5,5),
	LFT_ISTRAC_PB_SSD_DDR_SELECT                                    =REG16_DEF(0x0c,7,7),

	LFT_VS_Input_Video_Type											=REG16_DEF(0x200,0,0),
	LFT_VS_Enable_Stablization										=REG16_DEF(0x200,1,1),
	LFT_VS_Input_X1_Coordinate										=REG16_DEF(0x200,10,19),
	LFT_VS_Input_Y1_Coordinate										=REG16_DEF(0x200,20,29),
	LFT_VS_Input_X2_Coordinate										=REG16_DEF(0x204,0,9),
	LFT_VS_Input_Y2_Coordinate										=REG16_DEF(0x204,10,19),

	LFT_VO_Input_Video_Type											=REG16_DEF(0x300,0,0),
	LFT_VO_Enable_Tracking											=REG16_DEF(0x300,1,1),
	LFT_VO_Algo_Type												=REG16_DEF(0x300,2,2),
	LFT_VO_Input_X1_Coordinate										=REG16_DEF(0x300,10,19),
	LFT_VO_Input_Y1_Coordinate										=REG16_DEF(0x300,20,29),
	LFT_VO_Input_X2_Coordinate										=REG16_DEF(0x304,0,9),
	LFT_VO_Input_Y2_Coordinate										=REG16_DEF(0x304,10,19),

	LFT_MP_Rd_Enable												=REG16_DEF(0x004,0,0),
	LFT_MP_Rd_Chk													=REG16_DEF(0x004,1,1),
	LFT_MP_Rd_data													=REG16_DEF(0x000,8,15),

	LFT_ISTRAC_ADC_Data_Size_Read           						= REG16_DEF(0X3000,0,12),

	LFT_FPGA_window_Size											= REG16_DEF(0x2F4, 0, 31),
    LFT_FPGA_STRMN_Debug_Cnt_Enamble								= REG16_DEF(0x2F8, 2, 2),
    LFT_FPGA_STRMN_Mux_enabl										= REG16_DEF(0x0C, 0, 1),
    LFT_FPGA_STRMN_Strt												= REG16_DEF(0x2F8, 0, 0),
    LFT_FPGA_STRMN_Stop												= REG16_DEF(0x2F8, 1, 1),
    LFT_FPGA_STRMN_Ch_Sl											= REG16_DEF(0x2F8, 12, 15),
    LFT_FPGA_STRMN_FIFO_LVL											= REG16_DEF(0x2FC, 0, 15),

	LFT_FPGA_RAW_STRMN_FIFO_LVL											= REG16_DEF(0x304, 0, 15),

	ISTRAC_FPGA_WRITE_START_ADDRESS							= REG16_DEF(0x1100,0,31),
    ISTRAC_FPGA_WRITE_START_ADDRESS_MSB						= REG16_DEF(0x1104,0,15),
    ISTRAC_FPGA_WRITE_SIZE									= REG16_DEF(0x1108,0,31),
    ISTRAC_FPGA_WRITE_SIZE_MSB                              = REG16_DEF(0x1104,16,31),
    ISTRAC_FPGA_WRITE_DATA_PULSE							= REG16_DEF(0x1118,10,10),
    ISTRAC_FPGA_WRITE_COMPLETE								= REG16_DEF(0x111C,0,0),
	ISTRAC_FPGA_WRITE_Done									= REG16_DEF(0x111C,1,1),
    ISTRAC_FPGA_read_path_sel_ddr                           = REG16_DEF(0x0140,3,3),
    ISTRAC_FPGA_READ_START_ADDRESS_CH2						= REG16_DEF(0x110C,0,31),
    ISTRAC_FPGA_READ_START_ADDRESS_MSB_CH2					= REG16_DEF(0x1110,0,15),
    ISTRAC_FPGA_READ_SIZE_CH2								= REG16_DEF(0x1114,0,31),
    ISTRAC_FPGA_READ_SIZE_MSB_CH2							= REG16_DEF(0x1110,16,31),
    ISTRAC_FPGA_READ_INDEFINITE_CH2							= REG16_DEF(0x1118,9,9),
    ISTRAC_reading_from_DAC                                 = REG16_DEF(0x200C,0,0),
    ISTRAC_trigger_pulse_width                              = REG16_DEF(0x00CC,0,31),
    ISTRAC_trigger_pulse_gap                                = REG16_DEF(0x00D0,0,31),
    ISTRAC_dac_data_count_per_trig                          = REG16_DEF(0x2008,0,31),
    ISTRAC_trigger_source_pb                                = REG16_DEF(0x00C8,4,4),
    ISTRAC_sw_trigger_start_pulse_pb                        = REG16_DEF(0x00C8,5,5),
	ISTRAC_sw_trigger_stop_pulse_pb                         = REG16_DEF(0x00C8,8,8),
    ISTRAC_PlayBAck_Memory_Slect                            = REG16_DEF(0x0140,4,4),
    ISTRAC_init_DDR                                         = REG16_DEF(0x111c,0,0),
    ISTRAC_RAW_Strming_FPGA1                                = REG16_DEF(0x5250,0,0),
    ISTRAC_RAW_Strming_FPGA2                                = REG16_DEF(0x10250,0,0),
    ISTRAC_DDC_RAW_Strmin_DDC_Enb                           = REG16_DEF(0x300,8,8),

	ISTRAC_PLYBK_COFIG_REG1_SW_TRIG_EN					    = REG16_DEF(0x00C8, 6, 6),
	 ISTRAC_PLBK_COFIG_REG1_TM			                    = REG16_DEF(0x00C8, 1, 1),//Tigger Mode
	 ISTRAC_DDR_RESET										= REG16_DEF(0x2500,3,3),
	 ISTRAC_AXI_RESET										= REG16_DEF(0x2500,4,4),


};