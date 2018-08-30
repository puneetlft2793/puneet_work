#include "../MiddleAPIWrapper.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include<fstream>
#include <math.h>
#define		DEBUG_FILE_NAME				".\\ISTRAC_debug.log"//"C:\\SppuUsbLog\\LogFile.txt"
#define DEBUG_FILE_EXIST	(-1 != _access(DEBUG_FILE_NAME, 0x0))

using namespace MiddleAPIWrapper;


long MiddleAPI::ProgramIQData_ISTRAC(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,SPPUDeviceType a_enDeviceType, SPPUDataType a_enDataType, unsigned long long a_nSize, unsigned long long *a_nSizeWritten, char *a_strFileName)
{


	int ret					=	0;
	unsigned int nOffset	=	0;		//since no register is supported to hold value larger than 32 bit, hence no need to change it for 8 GiB support.

	unsigned int nWriteIndefinite = LFT_SPPU_IQ_WRITE_INDEFINITE;
	unsigned int nAxisBurstLength = LFT_SPPU_IQ_WRITE_AXIS_BURST_LENGTH;
	unsigned int nReadIndefininte = LFT_SPPU_IQ_READ_INDEFINITE;

	unsigned int nWriteWrapAddr	= 0x0;

	unsigned int nWriteStartAddrMsb	= 0x0;
	unsigned int nReadStartAddrMsb	= 0x0;

	unsigned int nReadWrapAddr = 0x0;
	unsigned long long nWriteEndAddressCh2 = 0x0;

	unsigned int trigger_pulse_width = 5;
	unsigned int trigger_pulse_gap = 0xF00;
	unsigned int dac_data_count_per_trig = 0x190;
	unsigned int trgrSrc = 0x1;
	unsigned int memorySlect =1;
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};



	{

		unsigned long *pnSizeWritten;

		sprintf_s(strDebug, DEBUG_STR_LEN,"\nIn ProgramIQData(%d, %d, %d, 0x%llx, %lld, 0x%llx, %s)", a_enConnectionType, a_nModuleID, a_enDeviceType, a_enDataType, a_nSize, a_nSizeWritten, a_strFileName);
		mPrintDebug(strDebug);
	}

	int timeout = 10;
	unsigned int initStat	=	5;
	while(timeout)
	{
		FPGARegAccessRead(a_enConnectionType, a_nModuleID, a_enDeviceType, ISTRAC_FPGA_WRITE_COMPLETE, &initStat);

		if(initStat	!=	0)
			break;
		Sleep(100);
		timeout--;
	}
	if(timeout==0)
	{

		sprintf_s(strDebug, DEBUG_STR_LEN,"\n DDR INIT Time Out");
		mPrintDebug(strDebug);
		return 1;
	}

	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType,ISTRAC_DDR_RESET,1);
	Sleep(1);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType,ISTRAC_DDR_RESET,0);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType,ISTRAC_AXI_RESET,1);
	Sleep(1);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType,ISTRAC_AXI_RESET,0);

	if(SPPUDeviceType::LFT_SPPU_DEV_DDR == a_enDeviceType)
	{
		switch(a_enDataType)
		{
		case LFT_SPPU_DATA_TYPE_IQ_DC1:
			nOffset	= LFT_SPPU_DATA_TYPE_IQ_DC1_OFFSET;
			nWriteStartAddrMsb = 0x0;
			nReadStartAddrMsb = 0x0;
			//nWriteWrapAddr = LFT_SPPU_IQ_WRITE_WRAP_ADDR_IQ_CHAN_1;
			//nReadWrapAddr = LFT_SPPU_IQ_READ_WRAP_ADDR_IQ_CHAN_1(a_nSize);
			break;

		case LFT_SPPU_DATA_TYPE_IQ_DC2:
			nOffset	= LFT_SPPU_DATA_TYPE_IQ_DC2_OFFSET;
			nWriteStartAddrMsb = 0x0;						//__HARD__
			nReadStartAddrMsb = 0x0;
			//nWriteWrapAddr = LFT_SPPU_IQ_WRITE_WRAP_ADDR_IQ_CHAN_2;
			//nReadWrapAddr = LFT_SPPU_IQ_READ_WRAP_ADDR_IQ_CHAN_2(a_nSize);
			break;

		case LFT_SPPU_DATA_TYPE_RF:
			/*nOffset	= 0x40000000;
			nWriteStartAddrMsb = 0x0;
			nReadStartAddrMsb = 0x0;
			*/
			nOffset	= LFT_SPPU_DATA_TYPE_IF_OFFSET;
			nWriteStartAddrMsb = 0x0;
			nReadStartAddrMsb = 0x0;
			break;

		default:
			ret	=	-100;
		}

		//int SizeModify = 0, SizeDiff = 0;
		unsigned long long SizeModify = 0, SizeDiff = 0;

		//FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_AXIS_BURST_LENGTH, nAxisBurstLength);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, ISTRAC_FPGA_WRITE_START_ADDRESS, nOffset);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType,ISTRAC_FPGA_WRITE_START_ADDRESS_MSB, nWriteStartAddrMsb/*nWriteWrapAddr*/);
		sprintf_s(strDebug, DEBUG_STR_LEN,"\n Start Add programed");
		mPrintDebug(strDebug);
		//__HP__4 ; Adding support : if File Size is not multiple of 4096 bytes then append 0s to make it multiple of 64 bytes.
		SizeModify = a_nSize;
		if(SizeModify < FPGA_DDR_RESOLUTION)
			SizeModify = FPGA_DDR_RESOLUTION;

		if((SizeDiff = (SizeModify % FPGA_DDR_RESOLUTION)) != 0)
			SizeModify += (FPGA_DDR_RESOLUTION - SizeDiff);
		//__HP__4 : end;

		//__HP__8; initializing with valid value
		nWriteEndAddressCh2 = SizeModify;

		//__HP__7:
		if(a_enDataType == LFT_SPPU_DATA_TYPE_IQ_DC2)
			nWriteEndAddressCh2 = SizeModify + 0x3FF8000;

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType,ISTRAC_FPGA_WRITE_SIZE, nWriteEndAddressCh2/*SizeModify*//*a_nSize*/);
#if SPPU_DDR_MAX_SIZE_SUPPORT_8GB
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType,ISTRAC_FPGA_WRITE_SIZE_MSB, nWriteEndAddressCh2 >> 32);
#elif SPPU_DDR_MAX_SIZE_SUPPORT_4GB
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_SIZE_MSB, 0x0);		//__HARD__
#endif
		sprintf_s(strDebug, DEBUG_STR_LEN,"\n Size Programed");
		mPrintDebug(strDebug);
		//FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_INDEFINITE, nWriteIndefinite);

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, ISTRAC_FPGA_WRITE_DATA_PULSE, 1);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, ISTRAC_FPGA_WRITE_DATA_PULSE, 0);

		//__HP__2; Adding support : if File Size is not multiple of 64 bytes then append 0s to make it multiple of 64 bytes.
#if 0
		int SizeModify = 0;

		if(a_nSize < 64)
			a_nSize = 64;

		if((SizeModify = (a_nSize % 64)) != 0)
			a_nSize += (64 - SizeModify);
#endif
		//__HP__5; sending modified file size.

		sprintf_s(strDebug, DEBUG_STR_LEN,"\n Writting file to DDR");
		mPrintDebug(strDebug);
		ret	=	MemoryWriteFileInternal_10Gb(a_enConnectionType, a_nModuleID, a_enDeviceType, 0x4210, SizeModify/*a_nSize*/, a_nSizeWritten, a_strFileName);

		timeout = 10;
		unsigned int val	=	5;
		while(timeout)
		{
			FPGARegAccessRead(a_enConnectionType, a_nModuleID, a_enDeviceType, ISTRAC_FPGA_WRITE_Done, &val);
			if(val	==	1)
				break;
			Sleep(100);
			timeout--;
		}
		if(timeout==0)
		{
			sprintf_s(strDebug, DEBUG_STR_LEN,"\n Write Done Time Out");
			mPrintDebug(strDebug);
			return 1;
		}
		/// path select ///// ISTRAC_FPGA_read_path_sel_ddr
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType,ISTRAC_FPGA_read_path_sel_ddr, 1);

		///// configure_ddr3_read_user_interface_for_dac_0_link


		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType,ISTRAC_FPGA_READ_START_ADDRESS_CH2, nOffset);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, ISTRAC_FPGA_READ_START_ADDRESS_MSB_CH2, nReadStartAddrMsb);

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, ISTRAC_FPGA_READ_SIZE_CH2, a_nSize);
#if SPPU_DDR_MAX_SIZE_SUPPORT_8GB
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, ISTRAC_FPGA_READ_SIZE_MSB_CH2, a_nSize >> 32);
#elif SPPU_DDR_MAX_SIZE_SUPPORT_4GB
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_SIZE_MSB_CH2, 0x0);
#endif

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, ISTRAC_FPGA_READ_INDEFINITE_CH2, nReadIndefininte);
		return ret =0;

		///// read_data_from_dac_0_interface_module//// ISTRAC_reading_from_DAC


		//  FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType,ISTRAC_trigger_pulse_width, trigger_pulse_width);
		//  FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, ISTRAC_trigger_pulse_gap, trigger_pulse_gap);//dac_data_count_per_trig
		//  FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType,ISTRAC_dac_data_count_per_trig, dac_data_count_per_trig);

		// ///// trigger_source_pb src ISTRAC_trigger_source_pb trgrSrc
		// if(trgrSrc==1)
		// FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, ISTRAC_trigger_source_pb, 1);
		// else
		//     FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, ISTRAC_trigger_source_pb, 0);

		// ///// ISTRAC_sw_trigger_start_pulse_pb
		// ///
		// FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, ISTRAC_sw_trigger_start_pulse_pb, 1);
		//FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType,ISTRAC_sw_trigger_start_pulse_pb, 0);



	}
	else
	{
		//Un recognized device
		ret = -100;
	}

}

long MiddleAPIWrapper::MiddleAPI::ISTRAC_SSD_Sel(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue)
{
	//unsigned int SSD_Sel = *a_nPropValue;
	if(DEBUG_FILE_EXIST)
	{
	FC_Debug.open(DEBUG_FILE_NAME, std::ios_base::app);
	FC_Debug << "******   /* SSD Sel ***** " <<*a_nPropValue<<  endl;
	FC_Debug.close();
	}
	switch(*a_nPropValue)
	{
	case 0:
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_ISTRAC_SSD_Sel,0x1);
		break;
	case 1:
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_ISTRAC_SSD_Sel,0x2);
		break;
	case 2:
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_ISTRAC_SSD_Sel,0x4);
		break;
	case 3:
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_ISTRAC_SSD_Sel,0x8);
		break;
	}
	return 0;
}

long MiddleAPIWrapper::MiddleAPI::ISTRAC_SSD_Write(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,
													unsigned int ssd_sel,unsigned int wr_addr_1,unsigned int wr_addr_0, unsigned int wr_size_1, unsigned int wr_size_0,
													unsigned long long a_nSize, unsigned long long *a_nSizeWritten, char *a_strFileName,unsigned int *a_nPropValue)
{
	if(DEBUG_FILE_EXIST)
	{
	FC_Debug.open(DEBUG_FILE_NAME, std::ios_base::app);
	FC_Debug << "ssd_sel " <<ssd_sel<<  endl;
	FC_Debug << "wr_addr_1 " <<wr_addr_1<<  endl;
	FC_Debug << "wr_addr_0 " <<wr_addr_0<<  endl;
	FC_Debug << "wr_size_1 " <<wr_size_1<<  endl;
	FC_Debug << "wr_size_0 " <<wr_size_0<<  endl;
	FC_Debug << "a_nSize " <<a_nSize<<  endl;
	FC_Debug << "a_strFileName " <<a_strFileName<<  endl;
	FC_Debug.close();
	}
#if 0
	ISTRAC_SSD_Sel(a_enConnectionType,a_nModuleID,a_enDeviceType,&ssd_sel);
#endif
  /* Step 1
   Set Memory_access_top source as Register/stream data
   wr1 0x0200 0x00000004*/
	if(DEBUG_FILE_EXIST)
	{
	FC_Debug.open(DEBUG_FILE_NAME, std::ios_base::app);
	FC_Debug << "******   /* Step 1 ***** " <<  endl;
	FC_Debug.close();
	}
	RegWrite(a_enConnectionType,  a_nModuleID, LFT_SPPU_DEV_FPGA, 0x0200, 0x00000004) ;

	/* #Step 2
   #Set start address
   wr1 0x020C $wr_addr_0
   wr1 0x0210 $wr_addr_1*/
	if(DEBUG_FILE_EXIST)
	{
	FC_Debug.open(DEBUG_FILE_NAME, std::ios_base::app);
	FC_Debug << "******   /* Step 2 ***** " <<  endl;
	FC_Debug.close();
	}

	RegWrite(a_enConnectionType,  a_nModuleID, LFT_SPPU_DEV_FPGA, 0x020C, wr_addr_0) ;
	RegWrite(a_enConnectionType,  a_nModuleID, LFT_SPPU_DEV_FPGA, 0x0210, wr_addr_1) ;

	/*#Step 3
   #Set Write Size
   wr1 0x0214 $wr_size_0
   wr1 0x0218 $wr_size_1*/
	if(DEBUG_FILE_EXIST)
	{
	FC_Debug.open(DEBUG_FILE_NAME, std::ios_base::app);
	FC_Debug << "******   /* Step 3 ***** " <<  endl;
	FC_Debug.close();
	}

	RegWrite(a_enConnectionType,  a_nModuleID, LFT_SPPU_DEV_FPGA, 0x0214, wr_size_0) ;
	RegWrite(a_enConnectionType,  a_nModuleID, LFT_SPPU_DEV_FPGA, 0x0218, wr_size_1) ;

	/*#Step 4 
   #Give start command to memory_access_top
   start_mem_acc_top*/
	if(DEBUG_FILE_EXIST)
	{
	FC_Debug.open(DEBUG_FILE_NAME, std::ios_base::app);
	FC_Debug << "******   /* Step 4 ***** " <<  endl;
	FC_Debug.close();
	}

	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_ISTRAC_start_mem_acc,1);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_ISTRAC_start_mem_acc,0);
		
	//#Step 5
 //  #Give start command for write through 1G <- register command
 //  wr1 0x022C [expr 0x[rd1 0x022C] | 0x00000001]
 //  wr1 0x022C [expr 0x[rd1 0x022C] & 0xFFFFFFFE]
	if(DEBUG_FILE_EXIST)
	{
	FC_Debug.open(DEBUG_FILE_NAME, std::ios_base::app);
	FC_Debug << "******   /* Step 5 ***** " <<  endl;
	FC_Debug.close();
	}

	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_ISTRAC_SSD_start_Pulse,1);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_ISTRAC_SSD_start_Pulse,0);

	if(DEBUG_FILE_EXIST)
	{
	FC_Debug.open(DEBUG_FILE_NAME, std::ios_base::app);
	FC_Debug << "******   /* Step 6 ***** " <<  endl;
	FC_Debug.close();
	}

	unsigned long long sizeWritten =0;
	MemoryWriteFileInternal_10Gb(a_enConnectionType,a_nModuleID,a_enDeviceType,0x420C,a_nSize,&sizeWritten,a_strFileName);
	
	if(DEBUG_FILE_EXIST)
	{
	FC_Debug.open(DEBUG_FILE_NAME, std::ios_base::app);
	FC_Debug << "****** after wrirint  Size Written***** " <<sizeWritten<<  endl;
	FC_Debug.close();
	}
	//#Step 6 LFT_ISTRAC_memory_access_top
 //  #Check memory_access_top status
	unsigned int rd_data =0;
	unsigned int timeout=10;
	rd_data=0;
    if(ssd_sel == 0)
	{
		timeout=10;
		FPGARegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_ISTRAC_memory_access_top_SSD_0,&rd_data);
		if(DEBUG_FILE_EXIST)
		{
			FC_Debug.open(DEBUG_FILE_NAME, std::ios_base::app);
			FC_Debug << "******   Check memory_access_top status SSD 0  Stat***** " <<rd_data<<  endl;
			FC_Debug.close();
		}
		while (rd_data == 0)
		{
			FPGARegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_ISTRAC_memory_access_top_SSD_0,&rd_data);
			if(rd_data!=0)
			{
				rd_data=0;
				if(DEBUG_FILE_EXIST)
				{
					FC_Debug.open(DEBUG_FILE_NAME, std::ios_base::app);
					FC_Debug << "******   Check memory_access_top status SSD 0  Stat***** " <<rd_data<<  endl;
					FC_Debug.close();
				}
			break;
			}
			if(timeout==0)
			{
				return 10;
			}
		timeout--;
		Sleep(1);
		}
	} 
	else if (ssd_sel == 1)
    {
	  timeout=10;
      FPGARegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_ISTRAC_memory_access_top_SSD_1,&rd_data);
      while (rd_data == 0)
	  {
          FPGARegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_ISTRAC_memory_access_top_SSD_1,&rd_data);
		  if(rd_data!=0)
		  {
			  rd_data=0;
			  break;
		  }
		   if(timeout==0)
		  {
			  return 10;
		  }
		  timeout--;
		  Sleep(1);
      }
    } 
	else if (ssd_sel == 2)
    {
	    timeout=10;
       FPGARegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_ISTRAC_memory_access_top_SSD_2,&rd_data);
      while (rd_data == 0)
	  {
          FPGARegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_ISTRAC_memory_access_top_SSD_2,&rd_data);
		  if(rd_data!=0)
		  {
			  rd_data=0;
			  break;
		  }
		   if(timeout==0)
		  {
			  return 10;
		  }
		  timeout--;
		  Sleep(1);
      }
    } 
    else if (ssd_sel == 3)
    {
		FPGARegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_ISTRAC_memory_access_top_SSD_3,&rd_data);
		while (rd_data == 0)
		{
			timeout=10;
			FPGARegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_ISTRAC_memory_access_top_SSD_3,&rd_data);
			if(rd_data!=0)
			{ 
			  rd_data=0;
			  break;
		  }
		   if(timeout==0)
		  {
			  return 10;
		  }
		  timeout--;
		  Sleep(1);
      }
   } 
   FC_Debug.open(DEBUG_FILE_NAME, std::ios_base::app);
	FC_Debug << "******   /* end ***** " <<  endl;
	FC_Debug.close();

   FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_ISTRAC_stop_mem_acc,1);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_ISTRAC_stop_mem_acc,0);
	return 0;

}

long MiddleAPIWrapper::MiddleAPI::ISTRAC_SSD_Read(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,
													unsigned int ssd_sel,unsigned int rd_addr_1,unsigned int rd_addr_0, unsigned int rd_size_1, unsigned int rd_size_0,
													unsigned long long a_nSize, unsigned long long *a_nSizeRead, char *a_strFileName,unsigned int *a_nPropValue)
{
	if(DEBUG_FILE_EXIST)
	{
	FC_Debug.open(DEBUG_FILE_NAME, std::ios_base::app);
	FC_Debug << "ssd_sel " <<ssd_sel<<  endl;
	FC_Debug << "wr_addr_1 " <<std::hex<<rd_addr_1<<  endl;
	FC_Debug << "wr_addr_0 " <<std::hex<<rd_addr_0<<  endl;
	FC_Debug << "wr_size_1 " <<std::hex<<rd_size_1<<  endl;
	FC_Debug << "wr_size_0 " <<std::hex<<rd_size_0<<  endl;
	FC_Debug << "a_nSize " <<std::hex<<a_nSize<<  endl;
	
	FC_Debug.close();
	}
	//ISTRAC_SSD_Sel(a_enConnectionType,a_nModuleID,a_enDeviceType,&ssd_sel);

  /* Step 1
   Set Memory_access_top source as Register/stream data
   wr1 0x0200 0x00000004*/
	if(DEBUG_FILE_EXIST)
	{
	FC_Debug.open(DEBUG_FILE_NAME, std::ios_base::app);
	FC_Debug << "******   /* Step 1 ***** " <<  endl;
	FC_Debug.close();
	}
	RegWrite(a_enConnectionType,  a_nModuleID, LFT_SPPU_DEV_FPGA, 0x0200, 0x00000004) ;

	/* #Step 2
   #Set start address
   wr1 0x020C $wr_addr_0
   wr1 0x0210 $wr_addr_1*/
	if(DEBUG_FILE_EXIST)
	{
	FC_Debug.open(DEBUG_FILE_NAME, std::ios_base::app);
	FC_Debug << "******   /* Step 2 ***** " <<  endl;
	FC_Debug.close();
	}
	RegWrite(a_enConnectionType,  a_nModuleID, LFT_SPPU_DEV_FPGA, 0x021C, rd_addr_0) ;
	RegWrite(a_enConnectionType,  a_nModuleID, LFT_SPPU_DEV_FPGA, 0x0220, rd_addr_1) ;

	/*#Step 3
   #Set Write Size
   wr1 0x0214 $wr_size_0
   wr1 0x0218 $wr_size_1*/
	if(DEBUG_FILE_EXIST)
	{
	FC_Debug.open(DEBUG_FILE_NAME, std::ios_base::app);
	FC_Debug << "******   /* Step 3 ***** " <<  endl;
	FC_Debug.close();
	}
	RegWrite(a_enConnectionType,  a_nModuleID, LFT_SPPU_DEV_FPGA, 0x0224, rd_size_0) ;
	RegWrite(a_enConnectionType,  a_nModuleID, LFT_SPPU_DEV_FPGA, 0x0228, rd_size_1) ;

	/*#Step 4 
   #Give start command to memory_access_top
   start_mem_acc_top*/
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_ISTRAC_start_mem_acc,1);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_ISTRAC_start_mem_acc,0);

	//#Step 4 
 //  #Give start command for write through 1G <- register command
 //  wr1 0x022C [expr 0x[rd1 0x022C] | 0x00000001]
 //  wr1 0x022C [expr 0x[rd1 0x022C] & 0xFFFFFFFE]
	if(DEBUG_FILE_EXIST)
	{
	FC_Debug.open(DEBUG_FILE_NAME, std::ios_base::app);
	FC_Debug << "******   /* Step 4 ***** " <<  endl;
	FC_Debug.close();
	}

	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_ISTRAC_RD_start_mem_acc,1);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_ISTRAC_RD_start_mem_acc,0);
	unsigned long long sizeWritten =0;


	MemoryReadFileInternal_10GB(a_enConnectionType,a_nModuleID,a_enDeviceType,0x420c,a_nSize,&sizeWritten,a_strFileName);
		if(DEBUG_FILE_EXIST)
	{
	FC_Debug.open(DEBUG_FILE_NAME, std::ios_base::app);
	FC_Debug << "******   Size read***** " <<sizeWritten<<  endl;
	FC_Debug.close();
	}
	//#Step 6 LFT_ISTRAC_memory_access_top
 //  #Check memory_access_top status
	if(DEBUG_FILE_EXIST)
	{
	FC_Debug.open(DEBUG_FILE_NAME, std::ios_base::app);
	FC_Debug << "******   /* Step 6 ***** " <<  endl;
	FC_Debug.close();
	}
	unsigned int rd_data =0;
	unsigned int timeout=10;
   if (ssd_sel == 0)
   {
	   FPGARegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_ISTRAC_memory_access_top_SSD_0,&rd_data);
      while (rd_data == 0)
	  {
          FPGARegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_ISTRAC_memory_access_top_SSD_0,&rd_data);
		 if(DEBUG_FILE_EXIST)
			{
			FC_Debug.open(DEBUG_FILE_NAME, std::ios_base::app);
			FC_Debug <<timeout<< "******   /* read value ***** " <<rd_data<<  endl;
			FC_Debug.close();
			}
		  if(rd_data!=0)
		  {
			  rd_data=0;
			  break;
		  }
		  if(timeout==0)
		  {
			  return 10;
		  }
		  timeout--;
		  Sleep(1);
      }
   } else if (ssd_sel == 1)
   {
	   timeout=10;
      FPGARegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_ISTRAC_memory_access_top_SSD_1,&rd_data);
      while (rd_data == 0)
	  {
          FPGARegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_ISTRAC_memory_access_top_SSD_1,&rd_data);
		  if(rd_data!=0)
		  {
			  rd_data=0;
			  break;
		  }
		   if(timeout==0)
		  {
			  return 10;
		  }
		  timeout--;
		  Sleep(1);
      }
   } else if (ssd_sel == 2)
   {
	    timeout=10;
       FPGARegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_ISTRAC_memory_access_top_SSD_2,&rd_data);
      while (rd_data == 0)
	  {
          FPGARegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_ISTRAC_memory_access_top_SSD_2,&rd_data);
		  if(rd_data!=0)
		  {
			  rd_data=0;
			  break;
		  }
		   if(timeout==0)
		  {
			  return 10;
		  }
		  timeout--;
		  Sleep(1);

      }
   } else if (ssd_sel == 3)
   {
     FPGARegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_ISTRAC_memory_access_top_SSD_3,&rd_data);
      while (rd_data == 0)
	  {
		  timeout=10;
          FPGARegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_ISTRAC_memory_access_top_SSD_3,&rd_data);
		  if(rd_data!=0)
		  {
			  rd_data=0;
			  break;
		  }
		    if(timeout==0)
		  {
			  return 10;
		  }
		  timeout--;
		  Sleep(1);
      }
   } 

   FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_ISTRAC_stop_mem_acc,1);
   FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_ISTRAC_stop_mem_acc,0);
   return 0;
}

long MiddleAPIWrapper::MiddleAPI::ISTRAC_SettingPlayBack(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,
	UINT32 ActualFIleSize_1,UINT32 ActualFIleSize_0,UINT32 modifiedfilesieze_1,UINT32 modifiedfilesieze_0,unsigned long long ActualFIleSize,unsigned long long modifiedfilesieze)
{
	
	if(DEBUG_FILE_EXIST)
	{
	FC_Debug.open(DEBUG_FILE_NAME, std::ios_base::app);
	FC_Debug << "ActualFIleSize " <<ActualFIleSize<<  endl;
	FC_Debug << "modifiedfilesieze " <<modifiedfilesieze<<  endl;	
	FC_Debug.close();
	}
	/*
	Set playback module as the data source to dac_interface
	wr1 0x000C [expr 0x[rd1 0x000C] | 0x00000080]
	*/
	//FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_ISTRAC_PB_Data_SRC_DAC_INTERFACE,1);

	/*
	Set Memory_access_top source as Upload=> Playback in this case
	wr1 0x0200 0x00000000
	*/
	RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,   0x0200 ,0x00000000);	

	/*
	Configure the playback module so that it can read data for playback.
	Playback Address
	wr1 0x144 0x0  
	*/
	RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,   0x144 ,0x00000000);	
	/*
	Playback Count
	Point to be noted here is that each value of count equlas 1MB. This logic is seprate from
	recording/uploading logic where each value of count equals 32MB.
	wr1 0x14C $filesize/32   [filesize divided by 32]
	*/
	if(DEBUG_FILE_EXIST)
	{
	FC_Debug.open(DEBUG_FILE_NAME, std::ios_base::app);
	FC_Debug << "modifiedfilesieze/33554432 " <<modifiedfilesieze/33554432<<  endl;	
	FC_Debug.close();
	}
	RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, 0x14C ,modifiedfilesieze/33554432);	

	/*
	 Playback filesize - Total filesize in bytes
     wr1 0x154 $filesize
	 */
	RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, 0x154 ,modifiedfilesieze_0);	
	RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, 0x15C ,modifiedfilesieze_1);	
	/*
	Playback actual waveform size in bytes
	wr1 0x158 $filesize - $redundant_sample
	*/
	RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, 0x158 ,ActualFIleSize_0);
	RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, 0x160 ,ActualFIleSize_1);

	/*
	write sw trigger start pulse
	wr1 0x0140 [expr 0x[rd1 0x0140] | 0x00000001]
	after 2000
	wr1 0x0140 [expr 0x[rd1 0x0140] & 0xFFFFFFFE]   
	*/
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_ISTRAC_PB_0x0140_BIT_NO_0,1);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_ISTRAC_PB_0x0140_BIT_NO_0,0);
	return 0;
}
long MiddleAPIWrapper::MiddleAPI::ISTRAC_StartPlayBack(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,
	unsigned int trigger_pulse_width,unsigned int trigger_pulse_gap,unsigned int dac_data_count_per_trig)
{
	
	/*
	Configure trigger for playback module
	issue read command(do_ddr_reading_for_dac) for user_interface module for ddr3 read
	wr1 0x200C 0x1 
	*/
	RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, 0x200C ,0x01);
	
	/*
	write Trigger_In_check pulse 
	wr1 0x00C8 [expr 0x[rd1 0x00C8] | 0x00000040]
	*/
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_ISTRAC_PB_Trigger_Enabe,1);

	/*
	if {$src == 1} 
	{
	   wr1 0x00C8 [expr 0x[rd1 0x00C8] & 0xFFFFFFEF]
	   wr1 0x00C8 [expr 0x[rd1 0x00C8] | 0x00000010]
	} 
	else
	{
      wr1 0x00C8 [expr 0x[rd1 0x00C8] & 0xFFFFFFEF]
      wr1 0x00C8 [expr 0x[rd1 0x00C8] | 0x00000000]
	}
	*/
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_ISTRAC_PB_TGR_SOURCE_PB,1);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_ISTRAC_PB_TGR_SOURCE_PB,0);
	
	/*
	wr1 0x00CC $pulse_width
	*/
	RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, 0x00CC ,trigger_pulse_width);

	/*
	trigger_pulse_gap
	wr1 0x00D0 $pulse_gap
	*/
	RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, 0x00D0 ,trigger_pulse_gap);

	/*
	wr1 0x2008 $dac_data_count_per_trig
	*/
	RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, 0x2008 ,dac_data_count_per_trig);

	/*
	write sw trigger start pulse
	wr1 0x00C8 [expr 0x[rd1 0x00C8] | 0x00000020]
	after 2000
	wr1 0x00C8 [expr 0x[rd1 0x00C8] & 0xFFFFFFDF]  
	*/
   	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_ISTRAC_PB_sw_trigger_start_pulse_pb,1);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_ISTRAC_PB_sw_trigger_start_pulse_pb,0);
	return 0;
}
long MiddleAPIWrapper::MiddleAPI::ISTRAC_SelectSSD(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType)
{
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_ISTRAC_PB_SSD_DDR_SELECT,0);
	return 0;
}
long MiddleAPIWrapper::MiddleAPI::ISTRAC_SelectDDR(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType)
{
 	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_ISTRAC_PB_SSD_DDR_SELECT,1);
	return 0;
}