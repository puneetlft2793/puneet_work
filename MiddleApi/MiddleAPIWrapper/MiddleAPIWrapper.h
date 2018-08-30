#pragma once

/********************* Global Macros *********************************************/
//#define EXPORT_TO_GUI

#define LFT_SPPU_SD_CARD_RF_CH_1_OFFSET			0x200000
#define LFT_SPPU_SD_CARD_RF_CH_2_OFFSET			0x100000
#define LFT_SPPU_SD_CARD_IF_OFFSET				0x100000
#define LFT_SPPU_SDCARD_RUNTEST_OFFSET			0x100000

#define LFT_SPPU_IQ_WRITE_INDEFINITE						0x0
#define LFT_SPPU_IQ_WRITE_AXIS_BURST_LENGTH 				0x40
#define LFT_SPPU_IQ_READ_INDEFINITE							0x1

#define LFT_SPPU_DATA_TYPE_IQ_DC1_OFFSET					0 
#define LFT_SPPU_DATA_TYPE_IQ_DC2_OFFSET					0x3FF8000   //64 byte
#define LFT_SPPU_DATA_TYPE_IF_OFFSET						LFT_SPPU_DATA_TYPE_IQ_DC1_OFFSET	//same as in IQ Chan 1 offset

#define LFT_SPPU_IQ_WRITE_WRAP_ADDR_IQ_CHAN_1				0x3FF8000 
#define LFT_SPPU_IQ_READ_WRAP_ADDR_IQ_CHAN_1(arg_ReadSize)	(arg_ReadSize	/	0x40)	

#define LFT_SPPU_IQ_WRITE_WRAP_ADDR_IQ_CHAN_2				0x3FFC000
#define LFT_SPPU_IQ_READ_WRAP_ADDR_IQ_CHAN_2(arg_ReadSize)	(LFT_SPPU_DATA_TYPE_IQ_DC2_OFFSET	+	(arg_ReadSize	/	0x40))

#define LFT_SPPU_IQ_WRITE_WRAP_ADDR_IF_CHAN					LFT_SPPU_IQ_WRITE_WRAP_ADDR_IQ_CHAN_1
#define LFT_SPPU_IQ_READ_WRAP_ADDR_IF_CHAN(arg_ReadSize)	(arg_ReadSize	/	0x40)

#define LFT_SPPU_FIXED_ADDRESS_FOR_IQ_PROGRAMMING			0x4200

//__MODIFY__ : Hp : 17 Aug 2015
#define LFT_SPPU_DEV_REG_SAVE_HEADER						0x0000
#define LFT_SPPU_DAC_1_REG_SAVE_OFFSET						0x1000
#define LFT_SPPU_DAC_2_REG_SAVE_OFFSET						0x2000
#define LFT_SPPU_DAC_3_REG_SAVE_OFFSET						0x3000
#define LFT_SPPU_LMK_REG_SAVE_OFFSET						0x4000
#define LFT_SPPU_ATTENUATOR_1_REG_SAVE_OFFSET				0x5000
#define LFT_SPPU_FPGA_REG_SAVE_OFFSET						0x10000
//#define LFT_SPPU_ATTENUATOR_1_REG_SAVE_OFFSET				0x1000

#define LFT_SPPU_DAC_1_REG_MAP_BUF_SIZE						0x0200
#define LFT_SPPU_DAC_2_REG_MAP_BUF_SIZE						0x0200
#define LFT_SPPU_DAC_3_REG_MAP_BUF_SIZE						0x0200
#define LFT_SPPU_LMK_REG_MAP_BUF_SIZE						0x0200
#define LFT_SPPU_ATTENUATOR_REG_MAP_BUF_SIZE				0x0200
#define LFT_SPPU_FPGA_REG_MAP_BUF_SIZE						0x0200

#ifndef __CHANGES_PCIE__
#define __CHANGES_PCIE__	1
#endif

#ifndef FAST_CENTROID_DEBUG
#define FAST_CENTROID_DEBUG		1
#endif

#ifndef CENTROID_DDR_SIZE
#define CENTROID_DDR_SIZE	0x20000000				//4 Gib of DDR.
#endif
#define SPPU_DDR_MAX_SIZE_SUPPORT_4GB	0
#define SPPU_DDR_MAX_SIZE_SUPPORT_8GB	1
#if FAST_CENTROID_DEBUG
#define FAST_CENTROID_DEBUG_FILE	".\\FastCentroid_Debug.log"
#endif

/*********************************************************************************/


/*********************** Header Files ***************************/

#ifndef EXPORT_TO_GUI

#define PREFIX_MIDDLEAPIWRAPPER __declspec(dllexport)

#include <io.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <sstream>
#include "../EthernetAPI/EthernetAPI/EthernetAPI.h"
#include "../SerialAPI/SerialAPI.h"
#include "../USBAPI/SppuUsbDll.h"
#include "enums.h"
#include "../RegPropMap/lft_dac.h"
#include "../RegPropMap/lft_fpga.h"
#include "../RegPropMap/lft_lmk.h"
#include <math.h>
#include <windows.h>
#include "FTD2xx.h"


//#include <opencv2/opencv.hpp>
//#include <opencv/cv.h>
//#include <opencv2/core/core.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/video/video.hpp>
//#include <opencv2/objdetect/objdetect.hpp>


#if __CHANGES_PCIE__
#include "../PcieDll/Pcie.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#if __CHANGES_PCIE__
#else
#include "../PCIeAPI/SppuPciLib.h"
#endif
#ifdef __cplusplus
}
#endif
#else

#define PREFIX_MIDDLEAPIWRAPPER __declspec(dllimport)

#include <io.h>

#include "EthernetAPI.h"
#include "SerialAPI.h"
#include "SppuUsbDll.h"
#include "../enums.h"
#include "lft_dac.h"
#include "lft_fpga.h"
#include "lft_lmk.h"
#include "SppuPciLib.h"
#include <math.h>
#include <windows.h>
#include "FTD2xx.h"

#if __CHANGES_PCIE__
#include "Pcie.h"
#endif
#endif

/*****************************************************************/

namespace MiddleAPIWrapper
{
	//const int DEBUG_STR_LEN	= 2000;

	/*struct SavePrevInfo
	{
	unsigned int rfCh_1_Size;		// IQ data size forRF  channel 1
	unsigned int rfCh_2_Size;		// IQ data size for RF channel 2
	unsigned int if_Size;			// IQ data size for IF channel.

	unsigned int dac_1_Size;		// DAC 1 Register Map Size
	unsigned int dac_2_Size;		// DAC 2 Register Map Size
	unsigned int dac_3_Size;		// DAC 3 Register Map Size

	unsigned int lmk_Size;			// LMK Register Map size

	unsigned int fpga_Size;			// Fpga Register Map Size

	}prevInfo = {0};*/


	class MiddleAPI
	{
	public:
		struct SavePrevInfo
		{
			unsigned int rfCh_1_Size;		// IQ data size forRF  channel 1
			unsigned int rfCh_2_Size;		// IQ data size for RF channel 2
			unsigned int if_Size;			// IQ data size for IF channel.

			unsigned int dac_1_Size;		// DAC 1 Register Map Size
			unsigned int dac_2_Size;		// DAC 2 Register Map Size
			unsigned int dac_3_Size;		// DAC 3 Register Map Size

			unsigned int lmk_Size;			// LMK Register Map size

			unsigned int fpga_Size;			// Fpga Register Map Size

		}prevInfo ;


		struct VAB_File_Info
		{
			char *File_Name;
			unsigned int *File_Size;
			char *File_Time;
			char *File_Type;
		};


		PREFIX_MIDDLEAPIWRAPPER MiddleAPI();



		PREFIX_MIDDLEAPIWRAPPER void disconnect(SPPUHostConnectionType a_enConnectionType);
		PREFIX_MIDDLEAPIWRAPPER int connect(MiddleEthernetAPI::Sockets a_sockets);
		PREFIX_MIDDLEAPIWRAPPER int connect(MiddleSerialAPI::SerialInfo a_serialInfo);
		PREFIX_MIDDLEAPIWRAPPER int connect(SPPUHostConnectionType a_enConnectionType, int a_nConnectionParam);   //eth : IP addr, (0x0A000050) == 10.0.0.80 , USB( device no.), UART( B0: COM Port#, B1: BaudRate)
		PREFIX_MIDDLEAPIWRAPPER int USB_Detect(void);

		PREFIX_MIDDLEAPIWRAPPER int RegWrite(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, 
			SPPUDeviceType a_enDeviceType, unsigned int address, unsigned int data);


		PREFIX_MIDDLEAPIWRAPPER int RegRead(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, 
			SPPUDeviceType a_enDeviceType, unsigned int address, unsigned int *data);


		PREFIX_MIDDLEAPIWRAPPER long MemoryReadFileInternal(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, 
			SPPUDeviceType a_enDeviceType, unsigned int a_nStartAddress, unsigned int a_nSize, unsigned int *a_nSizeRead,
			char *a_strFileName);

		PREFIX_MIDDLEAPIWRAPPER long MemoryReadFileInternal_10GB(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, 
			SPPUDeviceType a_enDeviceType, unsigned long long a_nStartAddress, unsigned long long a_nSize, unsigned long long *a_nSizeRead,
			char *a_strFileName);
		PREFIX_MIDDLEAPIWRAPPER long ProgramIQData_ISTRAC(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,SPPUDeviceType a_enDeviceType, SPPUDataType a_enDataType, unsigned long long a_nSize, unsigned long long *a_nSizeWritten, char *a_strFileName);

		PREFIX_MIDDLEAPIWRAPPER long MemoryReadFile(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, 
			SPPUDeviceType a_enDeviceType, unsigned int a_nStartAddress, unsigned int a_nSize, unsigned int *a_nSizeRead,
			char *a_strFileName);

		PREFIX_MIDDLEAPIWRAPPER long MemoryWriteFileInternal(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, 
			SPPUDeviceType a_enDeviceType, unsigned int a_nStartAddress, unsigned int a_nSize, unsigned int *a_nSizeWritten,
			char *a_strFileName);
			PREFIX_MIDDLEAPIWRAPPER long MemoryWriteFileInternal_10Gb(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType, unsigned long long a_nStartAddress, unsigned long long a_nSize, unsigned long long *a_nSizeWritten, char *a_strFileName);

		PREFIX_MIDDLEAPIWRAPPER long MemoryWriteFile(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, 
			SPPUDeviceType a_enDeviceType, unsigned int a_nStartAddress, unsigned int a_nSize, unsigned int *a_nSizeWritten,
			char *a_strFileName);

		PREFIX_MIDDLEAPIWRAPPER long MemoryRead(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, 
			SPPUDeviceType a_enDeviceType, unsigned int a_nStartAddress, unsigned int a_nSize, unsigned int *a_nSizeRead,
			char *a_pchRdBuff);

		PREFIX_MIDDLEAPIWRAPPER long MemoryWrite(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, 
			SPPUDeviceType a_enDeviceType, unsigned int a_nStartAddress, unsigned int a_nSize, unsigned int *a_nSizeWritten,
			char *a_pchWrBuff);

		PREFIX_MIDDLEAPIWRAPPER long ProgramIQData(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,
			SPPUDeviceType a_enDeviceType, SPPUDataType a_enDataType, unsigned int a_nSize, unsigned int *a_nSizeWritten, 
			char *a_strFileName);

		PREFIX_MIDDLEAPIWRAPPER long UpdateFirmware(SPPUHostConnectionType a_enConnectionType, SPPUDeviceType a_enDeviceType, char *a_strFileName);

		PREFIX_MIDDLEAPIWRAPPER long SetProperty(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,
			SPPUDeviceType a_enDeviceType, unsigned int a_nProp, unsigned int a_nPropValue);

		PREFIX_MIDDLEAPIWRAPPER long GetProperty(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,
			SPPUDeviceType a_enDeviceType, unsigned int a_nProp, unsigned int *a_nPropValue);


		PREFIX_MIDDLEAPIWRAPPER long RunTest(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,
			SPPUDeviceType a_enDeviceType, SPPUTestTypes a_enTestType, unsigned int *a_nPropValue);

		PREFIX_MIDDLEAPIWRAPPER long TriggerSetupStart(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,
			SPPUDeviceType a_enDeviceType);

		PREFIX_MIDDLEAPIWRAPPER long TriggerSetupStop(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,
			SPPUDeviceType a_enDeviceType);

		PREFIX_MIDDLEAPIWRAPPER long DACSetupStart(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,
			SPPUDeviceType a_enDeviceType);

		PREFIX_MIDDLEAPIWRAPPER long DACSetupStop(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,
			SPPUDeviceType a_enDeviceType);

		PREFIX_MIDDLEAPIWRAPPER long DACSetupRestart(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,
			SPPUDeviceType a_enDeviceType);

		PREFIX_MIDDLEAPIWRAPPER long ResetFPGA(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,
			SPPUDeviceType a_enDeviceType);

		PREFIX_MIDDLEAPIWRAPPER long UpdateFPGADACDataClockFrequency(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,
			unsigned int  *);
		PREFIX_MIDDLEAPIWRAPPER long UpdateFPGAOutClockFrequency(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,
			unsigned int *);

		PREFIX_MIDDLEAPIWRAPPER void ClearDACS(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID);

		PREFIX_MIDDLEAPIWRAPPER void DefaultSettings(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID);
		PREFIX_MIDDLEAPIWRAPPER void DAC_DefaultSettings(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,SPPUDACType enDactype);

		PREFIX_MIDDLEAPIWRAPPER void StartPattern(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID);

		PREFIX_MIDDLEAPIWRAPPER void StopPattern(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID);

		long ProgramDefaultInLMKRegisters(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID);

		long ProgramDefaultInDACRegisters(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,SPPUDACType enDactype);

		void DefaultInDACRegisters(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDACType enDactype );

		void DAC1Reset(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID);
		void DAC2Reset(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID);
		void DAC3Reset(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID);
		void InitFPGA(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID);

		PREFIX_MIDDLEAPIWRAPPER long sensor_calibration(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue);
		PREFIX_MIDDLEAPIWRAPPER ~MiddleAPI();

		//=======		PULKIT		========
		PREFIX_MIDDLEAPIWRAPPER long DDRWriteConfig(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, 
			SPPUDeviceType a_enDeviceType, unsigned int a_nStartAddress, unsigned int a_nSize, unsigned int *a_nSizeWritten,
			char *a_strFileName);
		PREFIX_MIDDLEAPIWRAPPER long DDRWriteFinalize(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, 
			SPPUDeviceType a_enDeviceType, unsigned int a_nStartAddress, unsigned int a_nSize, unsigned int *a_nSizeWritten,
			char *a_strFileName);

		PREFIX_MIDDLEAPIWRAPPER long DDRReadConfig(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, 
			SPPUDeviceType a_enDeviceType, unsigned int a_nStartAddress, unsigned int a_nSize, unsigned int *a_nSizeRead,
			char *a_strFileName);
		PREFIX_MIDDLEAPIWRAPPER long DDRReadFinalize(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, 
			SPPUDeviceType a_enDeviceType, unsigned int a_nStartAddress, unsigned int a_nSize, unsigned int *a_nSizeRead,
			char *a_strFileName);
		PREFIX_MIDDLEAPIWRAPPER long ISTRAC_GetADC_Data(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, 
			SPPUDeviceType a_enDeviceType, unsigned int a_nWindowSize, unsigned int *a_nSizeRead,char*buff,unsigned int  *a_nPropValue);
		PREFIX_MIDDLEAPIWRAPPER long ISTRAC_GeRAW_STREM_Data(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, 
			SPPUDeviceType a_enDeviceType, unsigned int a_nWindowSize, unsigned int *a_nSizeRead,char*buff,unsigned int  *a_dataLoss,unsigned int  *a_nPropValue);

			//=======	========	========	========

		PREFIX_MIDDLEAPIWRAPPER long MiddleAPI::VAB_File_List(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,vector<MiddleAPIWrapper::MiddleAPI::VAB_File_Info> File_Info,unsigned int *a_nPropValue);
		PREFIX_MIDDLEAPIWRAPPER long MiddleAPI::VAB_File_Delete(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue);
		PREFIX_MIDDLEAPIWRAPPER long MiddleAPI::VAB_File_Save(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int * file_Index,unsigned int *a_nPropValue);
		PREFIX_MIDDLEAPIWRAPPER long MiddleAPI::VAB_File_Run(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int * file_Index,unsigned int *a_nPropValue);
		
		PREFIX_MIDDLEAPIWRAPPER long MiddleAPI::FT_Detect(FT_DEVICE_LIST_INFO_NODE *devInfo,DWORD *Devs,unsigned int *a_nPropValue);
		PREFIX_MIDDLEAPIWRAPPER long MiddleAPI::FT_Init(int Device_No,unsigned int *a_nPropValue);
		PREFIX_MIDDLEAPIWRAPPER long MiddleAPI::FT_DeInit(unsigned int *a_nPropValue);

		PREFIX_MIDDLEAPIWRAPPER long MiddleAPI::FT_RegWrite(DWORD address, DWORD *data);
		PREFIX_MIDDLEAPIWRAPPER long MiddleAPI::FT_RegWriteBulk(DWORD address,unsigned int len,char *data);
		PREFIX_MIDDLEAPIWRAPPER long MiddleAPI::FT_RegRead(DWORD address,DWORD * data);
		PREFIX_MIDDLEAPIWRAPPER long MiddleAPI::FT_RegReadBulk(DWORD address,unsigned int len,char *data);




		PREFIX_MIDDLEAPIWRAPPER long RegWriteBulk(FT_HANDLE ftHandle, unsigned int address,unsigned int len,unsigned char *data,unsigned int *numBytesWr);
		PREFIX_MIDDLEAPIWRAPPER long RegReadBulk(FT_HANDLE ftHandle, unsigned int address,unsigned int len,unsigned char *data,unsigned int *numBytesRd);
		PREFIX_MIDDLEAPIWRAPPER long MiddleAPI::FT_FileRead(FT_HANDLE ftHandle,unsigned int startAddress, unsigned int size,  char *pchFilePath,  unsigned int *numBytesRdSuccess);
		PREFIX_MIDDLEAPIWRAPPER long MiddleAPI::FT_FileWrite(FT_HANDLE ftHandle,unsigned int startAddress, unsigned int size,  char *pchFilePath,  unsigned int *numBytesWrSuccess);


		PREFIX_MIDDLEAPIWRAPPER long MiddleAPI::sensorCalib_Frame_RdWr(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,SPPUDeviceType a_enDeviceType, SPPUTestTypes rd_wr_operation,char *fileName, unsigned int *a_nPropValue);
	// __FC__
		//PREFIX_MIDDLEAPIWRAPPER void ReadAllBytes(char const* filename,vector<double> &data);
//		PREFIX_MIDDLEAPIWRAPPER void getFramesFromFile(cv::VideoCapture &capture);
		/*
		PREFIX_MIDDLEAPIWRAPPER long GetVideoStream(
				SPPUHostConnectionType a_enConnectionType, 
				unsigned int a_nModuleID, 
				SPPUDeviceType a_enDeviceType, 
				MAT *frame,
				unsigned int resolution, 
				unsigned int *a_nSizeRead,
				void *dummy = NULL);

		PREFIX_MIDDLEAPIWRAPPER long GetCentroid(
				SPPUHostConnectionType a_enConnectionType, 
				unsigned int a_nModuleID, 
				SPPUDeviceType a_enDeviceType, 
				MAT *frame,
				unsigned int *a_nSizeRead,
				void *dummy = NULL);

		PREFIX_MIDDLEAPIWRAPPER long SaveVideo(
				SPPUHostConnectionType a_enConnectionType, 
				unsigned int a_nModuleID, 
				SPPUDeviceType a_enDeviceType, 
				unsigned int *a_nSizeRead,
				void *dummy = NULL);
		*/

		PREFIX_MIDDLEAPIWRAPPER long GetFrame(
				SPPUHostConnectionType a_enConnectionType, 
				unsigned int a_nModuleID, 
				SPPUDeviceType a_enDeviceType,
				char *buffer,
				unsigned int a_nReadSizeReq,
				unsigned int *a_nSizeRead,
				LftFrameFormat a_enFrameFormat,
				void *dummy);

		PREFIX_MIDDLEAPIWRAPPER long GetData(
				SPPUHostConnectionType a_enConnectionType, 
				unsigned int a_nModuleID, 
				SPPUDeviceType a_enDeviceType,
				char *buffer,
				unsigned int a_nNumFrames,
				unsigned int *a_nSizeRead,
				LftDataFormat a_enDataFormat,
				void *dummy);

		PREFIX_MIDDLEAPIWRAPPER long SaveVideo(
				SPPUHostConnectionType a_enConnectionType, 
				unsigned int a_nModuleID, 
				SPPUDeviceType a_enDeviceType,
				unsigned int a_nNumFrames,
				unsigned int *a_nSizeRead,
				LftFrameFormat a_enFrameFormat,
				char *FileName,
				void *dummy);
		PREFIX_MIDDLEAPIWRAPPER long Init_Write_DDR_Cent(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int size);
		PREFIX_MIDDLEAPIWRAPPER long Init_Read_DDR_Cent(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int size);

		PREFIX_MIDDLEAPIWRAPPER long Init_Sram_Write_Cent(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int size);
		PREFIX_MIDDLEAPIWRAPPER long Init_Sram_Read_Cent(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int size);

		PREFIX_MIDDLEAPIWRAPPER long Init_Sram_Write_Stat(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue);
		PREFIX_MIDDLEAPIWRAPPER long Init_Sram_Read_Stat(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue);
		
		
		
		/*****************************ISTRAC Releted Functions **********************************************/	
		PREFIX_MIDDLEAPIWRAPPER long ISTRAC_SSD_Sel(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue);	
		
		PREFIX_MIDDLEAPIWRAPPER long ISTRAC_SSD_Write(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,
														unsigned int ssd_sel,unsigned int wr_addr_1,unsigned int wr_addr_0, unsigned int wr_size_1, unsigned int wr_size_0,unsigned long long a_nSize, unsigned long long *a_nSizeWritten, char *a_strFileName,unsigned int *a_nPropValue);
        
		PREFIX_MIDDLEAPIWRAPPER long ISTRAC_SSD_Read(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,
														unsigned int ssd_sel,unsigned int rd_addr_1,unsigned int rd_addr_0, unsigned int rd_size_1, unsigned int rd_size_0,unsigned long long a_nSize, unsigned long long *a_nSizeRead, char *a_strFileName,unsigned int *a_nPropValue);
		PREFIX_MIDDLEAPIWRAPPER long ISTRAC_SettingPlayBack(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,
	UINT32 ActualFIleSize_1,UINT32 ActualFIleSize_0,UINT32 modifiedfilesieze_1,UINT32 modifiedfilesieze_0,unsigned long long ActualFIleSize,unsigned long long modifiedfilesieze);


		 PREFIX_MIDDLEAPIWRAPPER long ISTRAC_StartPlayBack(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,
	unsigned int trigger_pulse_width,unsigned int trigger_pulse_gap,unsigned int dac_data_count_per_trig);
		PREFIX_MIDDLEAPIWRAPPER  long ISTRAC_SelectSSD(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType);
		 PREFIX_MIDDLEAPIWRAPPER long ISTRAC_SelectDDR(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType);
		//=======	========	========	========
	private:



		long SimRegWrite(unsigned int a_nAddress, unsigned int a_nValue, unsigned int a_nDeviceType);

		long SimRegRead(unsigned int a_nAddress, unsigned int *a_nValue, unsigned int a_nDeviceType);

		long SetFPGAProperty(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, 
			SPPUFPGAProp a_enFPGAProp, unsigned int a_nPropValue);

		long SetDACProperty(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,
			SPPUDACProp a_enDACProp, unsigned int a_nPropValue);

		long SetLMKProperty(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,
			SPPULMKProp a_enLMKProp, unsigned int a_nPropValue);

		long SetAttenuatorProperty(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,
			SPPUAttenuatorProp a_enAttenuatorProp, unsigned int a_nPropValue);


		long GetFPGAProperty(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,
			SPPUFPGAProp a_enFPGAProp, unsigned int *a_nPropValue);

		long GetDACProperty(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,
			SPPUDACProp a_enDACProp, unsigned int *a_nPropValue);

		long GetLMKProperty(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,
			SPPULMKProp a_enLMKProp, unsigned int *a_nPropValue);

		long GetAttenuatorProperty(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,
			SPPUAttenuatorProp a_enAttenuatorProp, unsigned int *a_nPropValue);


		int DACRegAccessRead(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType, SPPUDACRegsDefs a_enSPPUDACRegsDefs , unsigned int *a_nPropValue);
		int DACRegAccessWrite(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType, SPPUDACRegsDefs a_enSPPUDACRegsDefs, unsigned int a_nPropValue);


		int FPGARegAccessRead(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType, SPPUFPGARegsDefs a_enSPPUFPGARegsDefs , unsigned int *a_nPropValue);
		int FPGARegAccessWrite(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType, SPPUFPGARegsDefs a_enSPPUFPGARegsDefs, unsigned int a_nPropValue);


		int LMKRegAccessRead(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,SPPUDeviceType a_enDeviceType, SPPULMKRegsDefs a_enSPPULMKRegsDefs , unsigned int *a_nPropValue);
		int LMKRegAccessWrite(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,SPPUDeviceType a_enDeviceType, SPPULMKRegsDefs a_enSPPULMKRegsDefs, unsigned int a_nPropValue);

		//__MODIFY__ : Hp : 4 Aug 2015
		HRESULT MiddleAPI::FillBuf(char *dest, unsigned int src);
		HRESULT SaveDevRegs(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType);
		HRESULT SaveFpgaRegs(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType);
		HRESULT SaveLmk04806Regs(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType);
		HRESULT SaveDacRegs(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType);
		HRESULT SaveMetaData(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType);

		long RunTestFPGA(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType, unsigned int a_nPropValue);	

		long RunTestFPGA(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue);

		//__MODIFY__ : PG : 4 Feb 2016
		long RunTestFPGAPerf(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue);

		long RunTestDAC_FPGA(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue);
		long RunTestDAC(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue);
		long RunTestLMK(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue);
		long RunTestUSB(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue);
		long RunTestAttunator(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue);
		long RunTestNORFLASH(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue);
		long RunTest_temp(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue);
		long RunTest_trigger(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue);
		long RunTest_DDRMEMORY(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID,SPPUDeviceType a_enDeviceType ,unsigned int *a_nPropValue);
		long RunTest_Sdcard(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType, unsigned int *a_nPropValue);
		long RunTestEthernet(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue);
		long RunTestuart_RS232(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue);
		long RunTestuart_RS422(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue);
		long RunTestrtc(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue);
		long RunTestsram(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue);
		long RunTesti2ceprom(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue);
		long RunTestSpiflash(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue);
		long RunTestBpiflash(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue);
		long RunTestuart_USB_UART(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue);
		
		long RunTest_usb(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue);
		long I2CWrite(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, unsigned int a_nDevAddress, unsigned int a_nRegAddress, unsigned int a_nRegValue);
		long I2CRead(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, unsigned int msgcode,unsigned int msgsize,unsigned int a_nDevAddress, unsigned int a_nRegAddress, unsigned int *a_nRegValue);
		long RunTest_Parallelnorflash(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue);
		long RunTest_Parallelnorflash_SIC(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue);
		long RunTest_DDR3(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue);
		long RunTest_DDR3_test_case_2(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue);
		long RunTest_ethernet(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue);
		long RunTest_EMMC(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue);
		long RunTest_i2ceeprom(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue);
		long sensor_calibration_MATLAB(char *infile_L,char *infile_H,char *infile_M,unsigned int *a_nPropValue);
		long sensor_calibration_HIGH(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue);
		long sensor_calibration_LOW(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue);
		float MiddleAPI::round_f(float x);
		long MiddleAPI::tic(void);
		long MiddleAPI::toc(void);
		long RunTest_usb_fx3(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue);
	//To do Sudeshna : Add, lft_att.h (separate file), define your enums SPPUATTRegsDefs	

		MiddleEthernetAPI::EthernetAPI objEthernetAPI;
		MiddleSerialAPI::SerialAPI objSerialAPI;
		UsbApis::c_UsbApis objUsbApi;
#if __CHANGES_PCIE__
		Pcie::c_Pcie objPcieAPI;
#endif
		//PciApis::c_PciApis	objPCIeAPI;

		//__FC__
		ofstream FC_Debug;

		void mPrintDebug(char *a_strDebug);
		void mPrintSelfTestLog(char *a_strDebug);
	};
}