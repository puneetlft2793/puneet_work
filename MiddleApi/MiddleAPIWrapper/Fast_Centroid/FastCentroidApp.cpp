#include "../MiddleAPIWrapper.h"
#include <iostream>
#include <fstream>

#define		DEBUG_FILE_NAME				".\\centroid.txt"//"C:\\SppuUsbLog\\LogFile.txt"
#define		SAMPLE_DATA_FILE_NAME       ".\\samPledata.bin"
#define		VIDEO_FILE_SAMPLE           ".\\Wildlife.wmv"

#define DEBUG_FILE_EXIST	(-1 != _access(FAST_CENTROID_DEBUG_FILE, 0x0))

#include <stdio.h>
#include <iostream>
#include<fstream>
#include <math.h>


using namespace MiddleAPIWrapper;

//Api to get frames
//void * (future enhancement)
//This API checks available frames and reads only 1 frame at a time.
long MiddleAPIWrapper::MiddleAPI::GetFrame(
				SPPUHostConnectionType a_enConnectionType, 
				unsigned int a_nModuleID, 
				SPPUDeviceType a_enDeviceType,
				char *buffer,
				unsigned int a_nReadSizeReq,
				unsigned int *a_nSizeRead,
				LftFrameFormat a_enFrameFormat,
				void *dummy)
{
	mPrintDebug("********** Get Frame Entry ************************************ \n");

	if(DEBUG_FILE_EXIST)
	{
	FC_Debug.open(FAST_CENTROID_DEBUG_FILE, std::ios_base::app);
	FC_Debug << "******  Get Frame Entry ***** " <<  endl;
	FC_Debug.close();
	}
	unsigned int numVidFramesAvail = 0x0, FrameSize = 0x0;
	unsigned int frameCount =0;
	unsigned int byteCount =0;
	unsigned int time_count =0;
	unsigned int SizeRead = 0x0, SizeWrote = 0x0;
	unsigned int numRemaningBytes = 0x0;
	long ret = S_OK;

	time_t seconds_begin, seconds_end, seconds;
	unsigned long long ms_begin, ms_end, ms;
	seconds_begin = time(NULL);
	ms_begin = GetTickCount64();

	//Clearing the status info variable.
	*a_nSizeRead = 0x0;

//	if(a_nReadSizeReq)
		//Got a request 
/*
	if(DEBUG_FILE_EXIST)
	{
		FC_Debug.open(FAST_CENTROID_DEBUG_FILE, std::ios_base::app);
		FC_Debug << "STATUS: Starting Video Stream. Inside GetFrame()" << endl;
		FC_Debug << "\tGetFrame(" << a_enConnectionType << "," << a_nModuleID << "," << 
			a_enDeviceType << "," << *buffer << "," << a_nReadSizeReq<< "," << *a_nSizeRead << "," << 
			a_enFrameFormat << "," << dummy << ");" << endl;
		FC_Debug.close();
	}
*/

	//Get current frame size.
	FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_Cam_Frame_Rate, &FrameSize);

	//Calculate actual Frame Size in bytes.
	switch(FrameSize)
	{
		case 0:
			FrameSize = 0x10000;				//256*256
			
			break;

		case 1:
			FrameSize = 0x1000;					//64*64
			break;

		case 2:
			FrameSize = 0x4000;					//128*128
			break;

		case 3:
			FrameSize = 0x1000;			//This case is for testing purpose.  
			break;
	}


	//Get number of frames available to read.
	FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_Num_Frame_Data_Size_Read, &numVidFramesAvail);
	FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_Frame_Count, &frameCount);
	FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_Byte_Count, &byteCount);
	FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_Time_Count, &time_count);

	

	//FC_Debug << "\tCentroid Data Available x 8 = 0x" << std::hex << numCentroidFramesAvail << std::dec  << " Bytes;" << endl;
	

		if(DEBUG_FILE_EXIST)
		{

			FC_Debug.open(FAST_CENTROID_DEBUG_FILE, std::ios_base::app);
		FC_Debug << "INFO :\t valid frame ::"<<numVidFramesAvail<<" FC. :: " <<  frameCount<<" Byt Cnt. ::"<<byteCount<<"  TC:: "<<time_count<<" FS"<<FrameSize<< endl;//"T"<<" : "<<st.wMinute<<" : "<<st.wSecond<<":"<<st.wMilliseconds<<endl;//<< std::dec << " DWords;";

		FC_Debug.close();
	}
	//Since depth of FIFO having frames is 4 bytes.
	numVidFramesAvail *= 0x4;

	//if available bytes are less the FrameSize, return the call without reading anything. (this will mean we are waiting for more data to come in the FIFO)
	if(numVidFramesAvail < FrameSize)
	{
		if(DEBUG_FILE_EXIST)
		{FC_Debug.open(FAST_CENTROID_DEBUG_FILE, std::ios_base::app);
		FC_Debug << "INFO : \tVideo Frame data Available = 0x" << std::hex << numVidFramesAvail << std::dec << " .Waiting for more data." << endl;
		FC_Debug.close();
		}
		return -1;
	}

	//To read only multiples of FrameSize.
	
	numRemaningBytes = (numVidFramesAvail % FrameSize);
	if(numRemaningBytes != 0)
		numVidFramesAvail -= numRemaningBytes;
	
	/*numRemaningBytes = (numVidFramesAvail /FrameSize);
	numVidFramesAvail = numRemaningBytes*FrameSize;*/

	if(DEBUG_FILE_EXIST)
	{
		FC_Debug.open(FAST_CENTROID_DEBUG_FILE, std::ios_base::app);
		FC_Debug << "INFO : \tVideo Frames Available = 0x" << std::hex << (numVidFramesAvail / 0x4) << std::dec << " DWords;";
		FC_Debug << "\tVideo Frames Available x 4 = 0x" << std::hex << numVidFramesAvail << std::dec  << " Bytes;";
		FC_Debug << "\tVideo Frame Size = 0x" << std::hex << FrameSize << std::dec << " Bytes.";
		FC_Debug << "\tVideo Frames To Read = 0x" << std::hex << (numVidFramesAvail / FrameSize) << " ;" << endl;
		FC_Debug.close();
	}


	//Set the current stream
	RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, 0x0, 0x2);
	//RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, 0x10000000, 0x4208);
	ret = MemoryRead(a_enConnectionType, a_nModuleID, a_enDeviceType, 0x0, numVidFramesAvail, &SizeRead, buffer);
	
	if(ret)
	{
		if(DEBUG_FILE_EXIST)
		{
			FC_Debug.open(FAST_CENTROID_DEBUG_FILE, std::ios_base::app);
			FC_Debug << "ERROR: MemoryRead(). Returned = " << ret << "Size read = 0x" << std::hex << *a_nSizeRead << std::dec << endl;
			FC_Debug.close();
		}
	}


	//if(DEBUG_FILE_EXIST)
	//{
	//	ms_end = GetTickCount64();
	//	ms = ms_end - ms_begin;
	//	char strDebug[DEBUG_STR_LEN]	=	{'\0'};
	//	seconds_end = time (NULL);
	//	seconds = (seconds_end - seconds_begin);
	//	SYSTEMTIME st;
	//	GetLocalTime(&st);

	//	FC_Debug.open("fast_CentroidTimeLog.log", std::ios_base::app);
	//	FC_Debug << "INFO :\t Time Elapsed   " <<  ms<<"mS  "<<" No. of Frame Read "<<SizeRead/FrameSize<<" System Time ::"<<st.wHour<<" : "<<st.wMinute<<" : "<<st.wSecond<<":"<<st.wMilliseconds<<endl;//<< std::dec << " DWords;";
	//	//FC_Debug << "\tCentroid Data Available x 8 = 0x" << std::hex << numCentroidFramesAvail << std::dec  << " Bytes;" << endl;
	//	FC_Debug.close();
	//}

	*a_nSizeRead = SizeRead;

	/*
	if(!ret)
	{
		if(DEBUG_FILE_EXIST)
		{
			FC_Debug.open(FAST_CENTROID_DEBUG_FILE, std::ios_base::app);
			FC_Debug << "SUCCESS: MemoryRead(). Returned = " << ret << " Size read = 0x" << std::hex << *a_nSizeRead << std::dec << endl;
			FC_Debug.close();
		}
	}
	*/
	if(DEBUG_FILE_EXIST)
	{
	FC_Debug.open(FAST_CENTROID_DEBUG_FILE, std::ios_base::app);
	FC_Debug << "******  Get Frame Exit ***** " <<  endl;
	FC_Debug.close();
	}
	mPrintDebug("********** Get Frame Exit ************************************\n");
	return ret;
	
}

//Api to get data
//void * (future enhancement)
long MiddleAPIWrapper::MiddleAPI::GetData(
				SPPUHostConnectionType a_enConnectionType, 
				unsigned int a_nModuleID, 
				SPPUDeviceType a_enDeviceType,
				char *buffer,
				unsigned int a_nNumFrames,
				unsigned int *a_nSizeRead,
				LftDataFormat a_enDataFormat,
				void *dummy)
{

	if(DEBUG_FILE_EXIST)
	{
		FC_Debug.open(FAST_CENTROID_DEBUG_FILE, std::ios_base::app);
		FC_Debug << "******  Get Data Entry ***** /n" <<  endl;
		FC_Debug.close();
	} 
	unsigned int numCentroidFramesAvail = 0x0;
	unsigned char numRemaningBytes = 0x0;							//remaining bytes will never me more than 0x13, so using unsigned char for this purpose.
	unsigned int SizeRead = 0x0;
	long ret = S_OK;

	mPrintDebug("********** Get Data Entry ************************************");
	
/*	
	if(DEBUG_FILE_EXIST)
	{
		FC_Debug.open(FAST_CENTROID_DEBUG_FILE, std::ios_base::app);
		FC_Debug << "STATUS: Starting Centroid Stream." << endl ;
		FC_Debug << "\tGetData(" << a_enConnectionType << "," << a_nModuleID << "," << 
			a_enDeviceType << "," << *buffer << "," << a_nNumFrames << "," << *a_nSizeRead << "," << 
			a_enDataFormat << "," << dummy << ");" << endl;
		FC_Debug.close();
	}
*/
	//Get number of frames available to read.
	FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_Num_Centroid_Data_Size_Read, &numCentroidFramesAvail);
	if(DEBUG_FILE_EXIST)
	{
		FC_Debug.open(FAST_CENTROID_DEBUG_FILE, std::ios_base::app);
		FC_Debug << "STATUS: \tCentroid data Available = 0x" << std::hex << numCentroidFramesAvail <<  endl;
		FC_Debug.close();
	}
	
	//Since depth of FIFO having frames is 8 bytes.
	numCentroidFramesAvail *= 0x8;

	//if available bytes are less the 0x14, return the call without reading anything. (this will mean we are waiting for more data to come in the FIFO)
	if(numCentroidFramesAvail < 0x28)
	
	{
		if(DEBUG_FILE_EXIST)
		{
			FC_Debug.open(FAST_CENTROID_DEBUG_FILE, std::ios_base::app);
			FC_Debug << "STATUS: \tCentroid data Available = 0x" << std::hex << numCentroidFramesAvail << std::dec << " .Waiting for more data." << endl;
			FC_Debug.close();
		}
		return -1;
	}

	//To read only multiples of 0x14.
	numRemaningBytes = (numCentroidFramesAvail % 0x28);

	////To read only multiples of 0x8.
	//numRemaningBytes = (numCentroidFramesAvail % 0x08);
	if(numRemaningBytes != 0)
		numCentroidFramesAvail -= numRemaningBytes;


	if(DEBUG_FILE_EXIST)
	{
		FC_Debug.open(FAST_CENTROID_DEBUG_FILE, std::ios_base::app);
		FC_Debug << "INFO :\tCentroid Data Available = 0x" << std::hex << (numCentroidFramesAvail / 0x8) << std::dec << " DWords;";
		FC_Debug << "\tCentroid Data Available x 8 = 0x" << std::hex << numCentroidFramesAvail << std::dec  << " Bytes;" << endl;
		FC_Debug.close();
	}

	//bulk_read_data_centroid
	RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, 0x0, 0x1);

	//ret = MemoryReadFileInternal(a_enConnectionType, a_nModuleID, a_enDeviceType, 0x0, numCentroidFramesAvail, &SizeRead, "HelloCentroid.bin");
	ret = MemoryRead(a_enConnectionType, a_nModuleID, a_enDeviceType, 0x0, numCentroidFramesAvail, &SizeRead, buffer);
	if(ret)
	{
		if(DEBUG_FILE_EXIST)
		{
			FC_Debug.open(FAST_CENTROID_DEBUG_FILE, std::ios_base::app);
			FC_Debug << "ERROR: MemoryRead(). Returned = " << ret << "Size read = 0x" << std::hex << *a_nSizeRead << std::dec << endl;
			FC_Debug.close();
		}
	}


	
	
	//sprintf_s(strDebug,DEBUG_STR_LEN,"\n Time elapsed:: %d sec", seconds);
	//mPrintSelfTestLog(strDebug);
	//sprintf_s(strDebug, DEBUG_STR_LEN, "\n Time elapsed:: %d ms", ms);
	//mPrintSelfTestLog(strDebug);

	*a_nSizeRead = SizeRead;

	if(!ret)
	{
		if(DEBUG_FILE_EXIST)
		{
			FC_Debug.open(FAST_CENTROID_DEBUG_FILE, std::ios_base::app);
			FC_Debug << "SUCCESS: MemoryRead(). Returned = " << ret << " Size read = 0x" << std::hex << *a_nSizeRead << std::dec << endl;
			FC_Debug.close();
		}
	}

	
	if(DEBUG_FILE_EXIST)
	{
		FC_Debug.open(FAST_CENTROID_DEBUG_FILE, std::ios_base::app);
		FC_Debug << "******  Get Data Exit ***** " <<  endl;
		FC_Debug.close();
	} 
	mPrintDebug("********** Get Data Exit ************************************\nn");
	return ret;
}


//Api to record and retrieve video
//void * (future enhancement)
long MiddleAPIWrapper::MiddleAPI::SaveVideo(
				SPPUHostConnectionType a_enConnectionType, 
				unsigned int a_nModuleID, 
				SPPUDeviceType a_enDeviceType,
				unsigned int a_nNumFrames,
				unsigned int *a_nSizeRead,
				LftFrameFormat a_enFrameFormat,
				char *FileName,
				void *dummy)
{

	unsigned int capture_done = 0x0;
	unsigned int numVideoBytesToRead = 0x0;
	unsigned int SizeRead = 0x0;
	long ret = S_OK;
	mPrintDebug("********** Save Video Entry ************************************");
#if 0
	//TODO: remove this '#if 0' code in final release
	unsigned int  fps = 0x0, FrameSize = 0x0;
	//if(DEBUG_FILE_EXIST)
	//{
	//	FC_Debug.open(FAST_CENTROID_DEBUG_FILE, std::ios_base::app);
	//	FC_Debug << "STATUS: Starting to Record and Retrieve Video." << endl;
	//	FC_Debug << "\tSaveVideo(" << a_enConnectionType << "," << a_nModuleID << "," << 
	//		a_enDeviceType << "," << a_nNumFrames << "," << *a_nSizeRead << "," << 
	//		a_enFrameFormat << "," << *FileName << ","<< dummy << ");" << endl;
	//	FC_Debug.close();
	//}

	//Get current frame size.
	FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_Cam_Frame_Rate, &FrameSize);

	//Calculate actual Frame Size in bytes.
	switch(FrameSize)
	{
	case 0:
		FrameSize = 0x10000;				//256*256
		fps = 2200;
		break;

	case 1:
		FrameSize = 0x1000;					//64*64
		fps = 5000;
		break;

	case 2:
		FrameSize = 0x4000;					//128*128
		fps = 5000;
		break;

	case 3:
		FrameSize = 0x1000;			//This case is for testing purpose. Since we can not test at 256x256 without actual camera, so using 64x64 frame size settings.
		fps = 5000;
		break;
	}

	numVideoBytesToRead = FrameSize * fps;


	if(DEBUG_FILE_EXIST)
	{
		FC_Debug.open(FAST_CENTROID_DEBUG_FILE, std::ios_base::app);
		FC_Debug << "INFO :\tVideo Bytes to read = 0x" << std::hex << numVideoBytesToRead << std::dec << " Bytes;" << endl;
		FC_Debug.close();
	}


	//Get number Video bytes available to read.
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_DDR_Rd_WR_end_Address, numVideoBytesToRead);


	//centroid_calculation_disable
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_Stream_Enable, 0x0);

	//ddr_write_data_pulse
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_Ddr_Start_Record, 0x1);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_Ddr_Start_Record, 0x0);
#else

	//Get number Video bytes available to read. Fpga does not modify this reg.
	FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_DDR_Rd_WR_end_Address, &numVideoBytesToRead);
	if(DEBUG_FILE_EXIST)
	{
		FC_Debug.open(FAST_CENTROID_DEBUG_FILE, std::ios_base::app);
		FC_Debug << "INFO :\tVideo Bytes to read = 0x" << std::hex << numVideoBytesToRead << std::dec << " Bytes;" << endl;
		FC_Debug.close();
	}
#endif				//Recoed Video

	//----------------------------------------------Retrive---------------------------------


	if(DEBUG_FILE_EXIST)
	{
		FC_Debug.open(FAST_CENTROID_DEBUG_FILE, std::ios_base::app);
		FC_Debug << "INFO :\tPolling for Write Done." << endl;
		FC_Debug.close();
	}


	//check_ddr_write_done
	do
	{
		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_Capture_Done, &capture_done);
	}while(capture_done == 0);

	if(DEBUG_FILE_EXIST)
	{
		FC_Debug.open(FAST_CENTROID_DEBUG_FILE, std::ios_base::app);
		FC_Debug << "INFO :\t________Done." << endl;
		FC_Debug.close();
	}

	//ddr_read_data_pulse
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_Ddr_Start_Retrive, 0x1);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_Ddr_Start_Retrive, 0x0);


	//bulk_read_data_ddr
	RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, 0x0, 0x0);
	ret = MemoryReadFileInternal(a_enConnectionType, a_nModuleID, a_enDeviceType, 0x0, numVideoBytesToRead, &SizeRead, ".\\Video.bin");
	if(ret)
	{
		if(DEBUG_FILE_EXIST)
		{
			FC_Debug.open(FAST_CENTROID_DEBUG_FILE, std::ios_base::app);
			FC_Debug << "ERROR: MemoryReadFileInternal(). Returned = " << ret << "Size read = 0x" << std::hex << *a_nSizeRead << std::dec << endl;
			FC_Debug.close();
		}
	}
	*a_nSizeRead = SizeRead;

	if(DEBUG_FILE_EXIST)
	{
		FC_Debug.open(FAST_CENTROID_DEBUG_FILE, std::ios_base::app);
		FC_Debug << "INFO :\tPolling for Read Done." << endl;
		FC_Debug.close();
	}

	//check_ddr_read_done
	do
	{
		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_Read_Done, &capture_done);
	}while(capture_done == 0);


	if(DEBUG_FILE_EXIST)
	{
		FC_Debug.open(FAST_CENTROID_DEBUG_FILE, std::ios_base::app);
		FC_Debug << "INFO :\t________Done." << endl;
		FC_Debug.close();
	}
	mPrintDebug("********** Save Video Exit ************************************");

	return ret;
}

long MiddleAPIWrapper::MiddleAPI::Init_Write_DDR_Cent(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int size)
{

	
	unsigned int writeStartAddr = 0;
	unsigned int readStartAddr  = 0;
	unsigned int writeEndAddr  =  size;
	unsigned int readEndAddr   =  size;
	unsigned int dataType      = 1;
	unsigned int rw_status;
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_checker,0);
	int timeout=5;
	while(timeout)
	{
		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_wait_init,&rw_status);
		if(rw_status == 0)
		{
		mPrintDebug("\n ============================= wait_ddr_init_complete =================================");
		}
		else
		{
		break;
		}
		timeout--;
		Sleep(10);
	}
	if(timeout == 0)
	{
		mPrintDebug("\n =============================Time Out =================================");
		return  1;
	}
	mPrintDebug("\n ============================= DDR3 Initialization Completed =================================");
	
	mPrintDebug("\n ============================= uart_configure_ddr3_write =================================");

	mPrintDebug("\n ============================= LFT_AIPB_SIC_DDR3_writeStartAddr =================================");
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_writeStartAddr,writeStartAddr);

	mPrintDebug("\n ============================= LFT_AIPB_SIC_DDR3_writeEndAddr =================================");
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_writeEndAddr,writeEndAddr);

	mPrintDebug("\n ============================= DDR3 configuration completes for Writing data =================================");

	mPrintDebug("\n ============================= Give Start Pulse for writing data =================================");
	
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_UART_SEND_WritePulse,1);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_UART_SEND_WritePulse,0);
	
	return 0;
}

long MiddleAPIWrapper::MiddleAPI::Init_Read_DDR_Cent(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int size)
{
	unsigned int writeStartAddr = 0;
	unsigned int readStartAddr  = 0;
	unsigned int writeEndAddr  =  size;
	unsigned int readEndAddr   =  size;
	unsigned int dataType      = 1;
	unsigned int rw_status;

	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_checker,0);
	int timeout=5;
	while(timeout)
	{
		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_wait_init,&rw_status);
		if(rw_status == 0)
		{
		mPrintDebug("\n ============================= wait_ddr_init_complete =================================");
		}
		else
		{
		break;
		}
		timeout--;
		Sleep(10);
	}
	if(timeout == 0)
	{
		mPrintDebug("\n =============================Time Out =================================");
		return  1;
	}
	mPrintDebug("\n ============================= DDR3 Reading Configuration Starts =================================");

	mPrintDebug("\n ============================= LFT_AIPB_SIC_DDR3_readStartAddr =================================");
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_readStartAddr,readStartAddr);

	mPrintDebug("\n ============================= LFT_AIPB_SIC_DDR3_readEndAddr =================================");
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_readEndAddr,readEndAddr);

	mPrintDebug("\n ============================= DDR3 configuration completes for Reading data =================================");
		
	mPrintDebug("\n ============================= Give Start Pulse for Reading data pulse =================================");
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_UART_SEND_ReadPulse,1);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_UART_SEND_ReadPulse,0);
	return 0;
}

long MiddleAPIWrapper::MiddleAPI::Init_Sram_Write_Cent(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int size)
{
	unsigned int writeEndAddr  =  size;

	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_readdata,writeEndAddr);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_blockreadready,1);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_SRAM_Wrt_Pulse,1);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_SRAM_Wrt_Pulse,0);
	return 0;
}

long MiddleAPIWrapper::MiddleAPI::Init_Sram_Read_Cent(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int size)
{
	unsigned int writeEndAddr  =  size;
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_readdata,writeEndAddr);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_blockreadready,1);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_SRAM_RD_Bulk,1);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_SRAM_RD_Bulk,0);
	return 0;
}

long MiddleAPIWrapper::MiddleAPI::Init_Sram_Write_Stat(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue)
{
	int timeout =10;
	unsigned int Block_write_ready=0;
	while(timeout)
	{
		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_SRAM_Wrt_Stat,&Block_write_ready);
		if(Block_write_ready == 1)
		{
			mPrintDebug("\n ============================= Block_write_ done  =================================");	
				FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_blockreadready,0);
			break;
		}

		timeout--;
		Sleep(100);
	}
return 0;
}

long MiddleAPIWrapper::MiddleAPI::Init_Sram_Read_Stat(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue)
{
int timeout =10;
unsigned int Block_write_ready=0;
while(timeout)
{
	FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_SRAM_Rd_Stat,&Block_write_ready);
	if(Block_write_ready == 1)
	{
		mPrintDebug("\n ============================= Read done   =================================");	
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_blockreadready,0);
		return 0;
			break;
	}
	
	timeout--;
	Sleep(100);
}
if(timeout==0)

	return 0;
}


long MiddleAPIWrapper::MiddleAPI::ISTRAC_GetADC_Data(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, 
	SPPUDeviceType a_enDeviceType, unsigned int a_nWindowSize, unsigned int *a_nSizeRead,char*buff,unsigned int  *a_nPropValue)
{
	mPrintDebug("****************************\n");
	mPrintDebug("  GET ADC DATA: START       \n");
	mPrintDebug("****************************\n");
	unsigned int adcSamples_count=0;
//	unsigned int a_nSizeRead =0;
	objEthernetAPI.MemReadInternal((MiddleEthernetAPI::EthernetAPI::SPPUDeviceTypeEtherent) a_enDeviceType, 0x4204,a_nWindowSize*4,buff,a_nSizeRead);
	//FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, GEN_REG_STRMN_FIFO_LVL, &adcSamples_count);
	
	/*if(adcSamples_count<a_nWindowSize)
	{
		
		return 0;
	}
	if(adcSamples_count>a_nWindowSize)
	{
		objEthernetAPI.MemReadInternal((MiddleEthernetAPI::EthernetAPI::SPPUDeviceTypeEtherent) a_enDeviceType, 0x4204,a_nWindowSize*4,buff,a_nSizeRead);
		//MemoryReadFileInternal(a_enConnectionType, a_nModuleID, a_enDeviceType, 0x4200, a_nWindowSize, a_nSizeRead, "ADC_Data.hex");
	}
	else
	{
		objEthernetAPI.MemReadInternal((MiddleEthernetAPI::EthernetAPI::SPPUDeviceTypeEtherent) a_enDeviceType, 0x4204,adcSamples_count*4,buff,a_nSizeRead);
		//MemoryRead(a_enConnectionType, a_nModuleID, a_enDeviceType, 0x4200,adcSamples_count*4,a_nSizeRead,buff);
		//MemoryReadFileInternal(a_enConnectionType, a_nModuleID, a_enDeviceType, 0x4200, adcSamples_count, a_nSizeRead, "ADC_Data.hex");
	}
	*/

	mPrintDebug("****************************\n");
	mPrintDebug("  GET ADC DATA: END       \n");
	mPrintDebug("****************************\n");
	return 0;//*a_nPropValue
}

long MiddleAPIWrapper::MiddleAPI::ISTRAC_GeRAW_STREM_Data(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, 
	SPPUDeviceType a_enDeviceType, unsigned int a_nWindowSize, unsigned int *a_nSizeRead,char*buff,unsigned int  *a_dataLoss,unsigned int  *a_nPropValue)
{
	mPrintDebug("****************************\n");
	mPrintDebug("  GET RAW DATA: START       \n");
	mPrintDebug("****************************\n");
	unsigned int adcSamples_count=0;
	unsigned int sizeRequest =0;
//	unsigned int a_nSizeRead =0;
	FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_FPGA_RAW_STRMN_FIFO_LVL, &adcSamples_count);
		sizeRequest = adcSamples_count*4;
	FC_Debug.open(FAST_CENTROID_DEBUG_FILE, std::ios_base::app);
		FC_Debug << "adcSamples_count=" <<adcSamples_count<<"sizeRequest == "<<sizeRequest<< endl;
		FC_Debug.close();
		if(adcSamples_count==0)
		{
			a_nSizeRead=0;
			return 1;
		}
	unsigned long *pnSizeRead	=	new unsigned long(0);
			objEthernetAPI.MemReadInternal((MiddleEthernetAPI::EthernetAPI::SPPUDeviceTypeEtherent) a_enDeviceType, 0x4208, 16384, buff, (unsigned int *) pnSizeRead);
		*a_nSizeRead	=	(unsigned int) *pnSizeRead;
		delete pnSizeRead;
	
	
	/*if(adcSamples_count<a_nWindowSize)
	{
		
		return 0;
	}
	if(adcSamples_count>a_nWindowSize)
	{
		objEthernetAPI.MemReadInternal((MiddleEthernetAPI::EthernetAPI::SPPUDeviceTypeEtherent) a_enDeviceType, 0x4204,a_nWindowSize*4,buff,a_nSizeRead);
		//MemoryReadFileInternal(a_enConnectionType, a_nModuleID, a_enDeviceType, 0x4200, a_nWindowSize, a_nSizeRead, "ADC_Data.hex");
	}
	else
	{
		objEthernetAPI.MemReadInternal((MiddleEthernetAPI::EthernetAPI::SPPUDeviceTypeEtherent) a_enDeviceType, 0x4204,adcSamples_count*4,buff,a_nSizeRead);
		//MemoryRead(a_enConnectionType, a_nModuleID, a_enDeviceType, 0x4200,adcSamples_count*4,a_nSizeRead,buff);
		//MemoryReadFileInternal(a_enConnectionType, a_nModuleID, a_enDeviceType, 0x4200, adcSamples_count, a_nSizeRead, "ADC_Data.hex");
	}
	*/

	mPrintDebug("****************************\n");
	mPrintDebug("  GET RAW DATA: END       \n");
	mPrintDebug("****************************\n");
	return 0;//*a_nPropValue
}























#pragma region UnUsed
//void MiddleAPIWrapper::MiddleAPI::getSampleData()
//{
//	///  Open file to write debug log ///////////
//	ofstream centroidDll;
//	centroidDll.open(DEBUG_FILE_NAME, ios_base::out | ios_base::app);
//			centroidDll << "SUCCESS: dll hit "<<  endl;
//			centroidDll.close();
//			
//     
//
///
//}

//// Function to read a binary file in vector of doubles
// param :: filename, vector of doubles
//Centroid
//void MiddleAPIWrapper::MiddleAPI::ReadAllBytes(char const* filename,vector<double> &data)
//{
//	/// Log file to check if dll is hit or not
//	ofstream centroidDll;
//	centroidDll.open(DEBUG_FILE_NAME, ios_base::out | ios_base::app);
//	centroidDll << "SUCCESS: dll hit new data clear "<< data.size()<< endl;
//	centroidDll.close();
//			
//        std::streampos fileSize;
//        double *fileBuffer;
//        size_t sizeOfBuffer;
//
//        // Check whether the parameter is already full
//		data.clear();
//
//  ifstream ifs(filename, ios::in | ios::binary);
//  if (ifs) {
//        // Get the size of the file
//        ifs.seekg(0, std::ios::end);
//        fileSize = ifs.tellg();
//        ifs.seekg(0, std::ios::beg);
//
//        sizeOfBuffer = fileSize / sizeof(double);
//        fileBuffer = new double[sizeOfBuffer];
//
//        ifs.read(reinterpret_cast<char*>(fileBuffer), fileSize);
//
//        // Now convert the double array into vector
//        data =  vector<double>(fileBuffer, fileBuffer + sizeOfBuffer);
//
//        free(fileBuffer);
//    }
//
// 
//}
//
////Video 30 FPS
////Resolution, Mat, void * (future enhancement)
////
//void MiddleAPIWrapper::MiddleAPI::getFramesFromFile(cv::VideoCapture &capture)
//{
//	capture.open(VIDEO_FILE_SAMPLE);
//}
#pragma endregion UnUsed