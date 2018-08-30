/* Header file for UPPU USB_Dll*/

#include "stdafx.h"
#include "CyAPI.h"

#include <string>
#include <fstream>
#include <BaseTsd.h>


#ifndef DEBUG
#define DEBUG	1
#define RELEASE ~DEBUG
#endif

#if DEBUG
#define DEBUG_ERROR		1
#define STATUS_DEBUG	1
#define DEBUG_STATUS	1
#define DEBUG_INFO		1
#endif

#define ENABLE_LOGGING 1			//DO NOT CHANGE

using namespace std;

#define		LESS(x,y)	((x < y) ? x : y)

#define		FPGA_PAGE_SIZE				512				// FPGA read/write page size
#define		SD_CARD_PAGE_SIZE			512				// SD Card read/write page size
#define		DEBUG_BUF_SIZE				4096			// Buffer to return debug data

#define		DEVICE_PAGE_SIZE		LESS(SD_CARD_PAGE_SIZE, FPGA_PAGE_SIZE)		//Final page size
#define		FILE_PAGE_SIZE			512											//8 for testing one of the cases

/* SD Card Commands and related parameters */
#define		GET_SD_CARD_STATUS			0xA6
#define		SD_CARD_WRITE				0xA2
#define		SD_CARD_READ				0xA3
//#define		GET_SD_CARD_GRANULARITY		0xA4
//#define		SET_SD_CARD_GRANULARITY		0xA5


/* APIs defaults */
#define		DO_NOT_CARE					0x00
#define		SD_CARD_READ_FILENAME		"SdReadFile.bin"
#define		DEFAULT_SD_READ_ADDR		0x00
#define		SD_CARD_WRITE_FILENAME		"SdWriteFile.bin"
#define		DEFAULT_SD_WRITE_ADDR		0x00
#define		DEFAULT_NUM_OF_BYTES		0x200
#define		DEBUF_FILE_NAME				".\\LogFile.txt"//"C:\\SppuUsbLog\\LogFile.txt"
#define		USB_DLL_DEBUF_FILE_NAME		".\\SppuUsbDllLogFile.txt"//"C:\\SppuUsbLog\\SppuUsbDllLogFile.txt"//

/* USB Endpoint Addressed*/
#define LFT_SPPU_USB_EP0_IN		0x80
#define LFT_SPPU_USB_EP0_OUT	0x00

#define LFT_SPPU_USB_EP1_OUT	0x01
#define LFT_SPPU_USB_EP1_IN		0x81

#define LFT_SPPU_USB_EP2_IN		0x82

#define LFT_SPPU_USB_EP3_OUT	0x03
#define LFT_SPPU_USB_EP3_IN		0x83


namespace UsbApis
{
	typedef enum SD_CARD_OFFSETS
	{
#if 0
		LFT_SPPU_USB_SD_CARD_START	= 0,
		LFT_SPPU_USB_SD_CARD_1GB	= (1024 *1024 * 1024),
		LFT_SPPU_USB_SD_CARD_2GB	= (2 * 1024 *1024 * 1024),
		LFT_SPPU_USB_SD_CARD_3GB	= (3 * 1024 *1024 * 1024),
		LFT_SPPU_USB_SD_CARD_4GB	= (4 * 1024 *1024 * 1024),
		LFT_SPPU_USB_SD_CARD_5GB	= (5 * 1024 *1024 * 1024),
		LFT_SPPU_USB_SD_CARD_6GB	= (6 * 1024 *1024 * 1024),
		LFT_SPPU_USB_SD_CARD_7GB	= (7 * 1024 *1024 * 1024),
		LFT_SPPU_USB_SD_CARD_END	= (8 * 1024 * 1024 * 1024)
#endif
	}SdCardOffsets;

	typedef enum DEVICE_TYPES
	{
		LFT_SPPU_DEV_DAC1 = 0,
		LFT_SPPU_DEV_DAC2,
		LFT_SPPU_DEV_DAC3,
		LFT_SPPU_DEV_LMK04806,
		LFT_SPPU_DEV_FPGA,
		LFT_SPPU_DEV_FPGA_SPI_FLASH,
		LFT_SPPU_DEV_DDR,
		LFT_SPPU_DEV_FX3_RAM,
		LFT_SPPU_DEV_FX3_SPI_FLASH,
		LFT_SPPU_DEV_FX3_SDCARD,
		LFT_SPPU_DEV_ATTENUATOR,
		LFT_SPPU_DEVICE_COUNT
	}DeviceTypes;

	typedef enum USB_ENDPOINTS
	{
		LFT_SPPU_FPGA_BULK_WR_EP = LFT_SPPU_USB_EP1_OUT,
		LFT_SPPU_FPGA_BULK_RD_EP = LFT_SPPU_USB_EP1_IN,
		LFT_SPPU_USB_FW_LOGS_IN_EP = LFT_SPPU_USB_EP2_IN,
		LFT_SPPU_SDCARD_BULK_WR_EP = LFT_SPPU_USB_EP3_OUT,
		LFT_SPPU_SDCARD_BULK_RD_EP = LFT_SPPU_USB_EP3_IN
	} UsbEpAddr;

	class c_UsbApis
	{
	private:
		CCyUSBDevice	*m_selectedUSBDevice;
		static BOOL     m_bBulkLoopCompleted;

	public:
		__declspec(dllimport) HRESULT OpenDevice();					//to open the device
		__declspec(dllimport) HRESULT CloseDevice();					//to close the usb device
		//Sd card read write functoins
		__declspec(dllimport) HRESULT RdFileFromSdCard0(
			DeviceTypes sppuUsbDeviceTypes,
			char *fname = SD_CARD_READ_FILENAME, 
			DWORD addr = DEFAULT_SD_READ_ADDR, 
			DWORD numBytes = DEFAULT_NUM_OF_BYTES,
			DWORD *numByRdSuccess = NULL);

		__declspec(dllimport) HRESULT WrFileToSdCard0(
			DeviceTypes sppuUsbDeviceTypes,
			char *fname = SD_CARD_WRITE_FILENAME, 
			DWORD addr = DEFAULT_SD_WRITE_ADDR, 
			DWORD numBytes = DEFAULT_NUM_OF_BYTES, 
			DWORD *numByRdSuccess = NULL);		//Function to send binary file in the firmware

		__declspec(dllimport) HRESULT RdMemFromSdCard0(
			DeviceTypes sppuUsbDeviceTypes,
			char *fname = NULL, 
			DWORD addr = DEFAULT_SD_READ_ADDR, 
			DWORD numBytes = DEFAULT_NUM_OF_BYTES,
			DWORD *numByRdSuccess = NULL);

		__declspec(dllimport) HRESULT WrMemToSdCard0(
			DeviceTypes sppuUsbDeviceTypes,
			char *fname = NULL, 
			DWORD addr = DEFAULT_SD_WRITE_ADDR, 
			DWORD numBytes = DEFAULT_NUM_OF_BYTES, 
			DWORD *numByRdSuccess = NULL);

		__declspec(dllimport) HRESULT UpdateFirmWare(
			DeviceTypes Dev,
			char *fname);

		__declspec(dllimport) HRESULT RegisterRead(
			UINT32 addr,
			UINT32 *val);

		__declspec(dllimport) HRESULT RegisterWrite(
			UINT32 addr,
			UINT32 val);

		__declspec(dllimport) HRESULT RegisterRead_V2(
			UINT32 addr,
			UINT32 *val);

		__declspec(dllimport) HRESULT RegisterWrite_V2(
			UINT32 addr,
			UINT32 val);

		//Lowest level function to write FPGA register(s).
		HRESULT __WrRegToDdr(unsigned char *buf, DWORD numBytes);

		//Lowest level function to read FPGA register(s).
		HRESULT __RdRegFrDdr(unsigned char *buf, DWORD bufSize);

		HRESULT _RdFileFrDdr(char *fname, DWORD faddr, DWORD numBytes, DWORD *numBytesRdSuccess);
		HRESULT _RdBufFrDdr(char *fname, DWORD faddr, DWORD numBytes, DWORD *numBytesRdSuccess);
		HRESULT __RdFrDdr(unsigned char *buf, DWORD numBytes, DWORD *numBytesRdSuccess);

		HRESULT _WrFileToDdr(char *fname, DWORD faddr, DWORD numBytes, DWORD *numBytesWrSuccess);
		HRESULT _WrBufToDdr(char *fname, DWORD faddr, DWORD numBytes, DWORD *numBytesWrSuccess);
		HRESULT __WrToDdr(DeviceTypes devType, unsigned char *buf, DWORD numBytes, DWORD *numBytesWrSuccess);

		HRESULT SppuFwVersion();

		HRESULT UsbApis::c_UsbApis::SendCommandEP0(
			unsigned char *buf,
			BYTE dir, 
			UINT8 bRequest, 
			UINT16 mValue, 
			UINT16 mIndex, 
			UINT16 mLength);

		HRESULT UsbApis::c_UsbApis::RdEP0(		//Old function used in SD Read and Write
			UINT8 devType, 
			BYTE cmd, 
			unsigned char *buf, 
			LONG numBytes);

		HRESULT UsbApis::c_UsbApis::WrEP0(		//Old function used in SD Read and Write
			UINT8 devType,
			BYTE cmd = GET_SD_CARD_STATUS, 
			DWORD addr = DO_NOT_CARE, 
			DWORD numBlocks = DO_NOT_CARE);

		HRESULT UsbApis::c_UsbApis::spiFlashErase(
			DWORD numSpiSecToErase);

		HRESULT UsbApis::c_UsbApis::spiFlashWrite(
			unsigned char *pBuf,
			UINT16 spiWrPgAddr,
			UINT16 numSpiPgsToWr,
			UINT16 *numByWrSuccess);

		HRESULT UsbApis::c_UsbApis::FpgaSpiProgram(char *fname);			//API to program SPI Flash connected to FPGA.
		HRESULT UsbApis::c_UsbApis::ResetDesign(void);
		HRESULT UsbApis::c_UsbApis::spiFlashInstrType(unsigned long instr_type);
		HRESULT UsbApis::c_UsbApis::BusyCheck(void);
		HRESULT UsbApis::c_UsbApis::spiFlashStartAdd(unsigned long data);
		HRESULT UsbApis::c_UsbApis::spiFlashFileSize(unsigned long data);
		HRESULT UsbApis::c_UsbApis::WriteModeEnable(void);
		HRESULT UsbApis::c_UsbApis::EmptyCheck(void);
		HRESULT UsbApis::c_UsbApis::ReadModeEnable(void);
		int  UsbApis::c_UsbApis::burstwritemode(PUCHAR buf , long numbytes);

		__declspec(dllimport) HRESULT Testing(void *);

	public:
		ofstream SppuUsbDllDebug;
		ULONG m_nStartValue;
		static BOOL m_bOpenFlag;
		DWORD m_nBulkStreamType;			//initialized in open() with default value of 0x4200, in constructor it was not being initialized.

		struct threadParams
		{
			BOOL flag;
			CCyUSBDevice *USBDevice;
		}thParams;

		struct UsbEp
		{
			CCyBulkEndPoint *fpgaBulkIn;
			CCyBulkEndPoint *fpgaBulkOut;
			CCyBulkEndPoint *sdCardBulkIn;
			CCyBulkEndPoint *sdCardBulkOut;
		}usbEp;

		c_UsbApis()
		{
			usbEp.fpgaBulkIn = NULL;
			usbEp.fpgaBulkOut = NULL;
			usbEp.sdCardBulkIn = NULL;
			usbEp.sdCardBulkOut = NULL;
			thParams.flag = FALSE;
		}
	};
}

DWORD WINAPI USBDebug(LPVOID lpParam);




#if 0
#include "CyAPI.h"

#include <string>
#include <fstream>
#include <BaseTsd.h>


#ifndef DEBUG
#define DEBUG	1
#define RELEASE ~DEBUG
#endif

#if DEBUG
#define ERROR_DEBUG		1
#define STATUS_DEBUG	1
#endif

#define ENABLE_LOGGING 1			//DO NOT CHANGE

using namespace std;

#define		LESS(x,y)	((x < y) ? x : y)

#define		FPGA_PAGE_SIZE				512				// FPGA read/write page size
#define		SD_CARD_PAGE_SIZE			512				// SD Card read/write page size
#define		DEBUG_BUF_SIZE				4096			// Buffer to return debug data

#define		DEVICE_PAGE_SIZE		LESS(SD_CARD_PAGE_SIZE, FPGA_PAGE_SIZE)		//Final page size
#define		FILE_PAGE_SIZE			512											//8 for testing one of the cases

/* SD Card Commands and related parameters */
#define		GET_SD_CARD_STATUS			0xA6
#define		SD_CARD_WRITE				0xA2
#define		SD_CARD_READ				0xA3
//#define		GET_SD_CARD_GRANULARITY		0xA4
//#define		SET_SD_CARD_GRANULARITY		0xA5


/* APIs defaults */
#define		DO_NOT_CARE					0x00
#define		SD_CARD_READ_FILENAME		"SdReadFile.bin"
#define		DEFAULT_SD_READ_ADDR		0x00
#define		SD_CARD_WRITE_FILENAME		"SdWriteFile.bin"
#define		DEFAULT_SD_WRITE_ADDR		0x00
#define		DEFAULT_NUM_OF_BYTES		0x200
#define		DEBUF_FILE_NAME				"C:\\SppuUsbLog\\LogFile.txt"
#define		USB_DLL_DEBUF_FILE_NAME		"C:\\SppuUsbLog\\SppuUsbDllLogFile.txt"

namespace UsbApis
{
	typedef enum SD_CARD_OFFSETS
	{
#if 0
		LFT_SPPU_USB_SD_CARD_START	= 0,
		LFT_SPPU_USB_SD_CARD_1GB	= (1024 *1024 * 1024),
		LFT_SPPU_USB_SD_CARD_2GB	= (2 * 1024 *1024 * 1024),
		LFT_SPPU_USB_SD_CARD_3GB	= (3 * 1024 *1024 * 1024),
		LFT_SPPU_USB_SD_CARD_4GB	= (4 * 1024 *1024 * 1024),
		LFT_SPPU_USB_SD_CARD_5GB	= (5 * 1024 *1024 * 1024),
		LFT_SPPU_USB_SD_CARD_6GB	= (6 * 1024 *1024 * 1024),
		LFT_SPPU_USB_SD_CARD_7GB	= (7 * 1024 *1024 * 1024),
		LFT_SPPU_USB_SD_CARD_END	= (8 * 1024 * 1024 * 1024)
#endif
	}SdCardOffsets;

	typedef enum DEVICE_TYPES
	{
		LFT_SPPU_DEV_DAC1 = 0,
		LFT_SPPU_DEV_DAC2,
		LFT_SPPU_DEV_DAC3,
		LFT_SPPU_DEV_LMK04806,
		LFT_SPPU_DEV_FPGA,
		LFT_SPPU_DEV_FPGA_SPI_FLASH,
		LFT_SPPU_DEV_DDR,
		LFT_SPPU_DEV_FX3_RAM,
		LFT_SPPU_DEV_FX3_SPI_FLASH,
		LFT_SPPU_DEV_FX3_SDCARD,
		LFT_SPPU_DEV_ATTENUATOR,
		LFT_SPPU_DEV_STREAM,				//Added for TCL, 16 May 2016
		LFT_SPPU_DEVICE_COUNT
	}DeviceTypes;

	class c_UsbApis
	{
	private:
		CCyUSBDevice	*m_selectedUSBDevice;
		static BOOL     m_bBulkLoopCompleted;

	public:
		HRESULT OpenDevice();					//to open the device
		HRESULT CloseDevice();					//to close the usb device
		//Sd card read write functoins
		__declspec(dllimport) HRESULT RdFileFromSdCard0(
								DeviceTypes sppuUsbDeviceTypes,
								char *fname = SD_CARD_READ_FILENAME, 
								DWORD addr = DEFAULT_SD_READ_ADDR, 
								DWORD numBytes = DEFAULT_NUM_OF_BYTES,
								DWORD *numByRdSuccess = NULL);

		__declspec(dllimport) HRESULT WrFileToSdCard0(
								DeviceTypes sppuUsbDeviceTypes,
								char *fname = SD_CARD_WRITE_FILENAME, 
								DWORD addr = DEFAULT_SD_WRITE_ADDR, 
								DWORD numBytes = DEFAULT_NUM_OF_BYTES, 
								DWORD *numByRdSuccess = NULL);		//Function to send binary file in the firmware

		__declspec(dllimport) HRESULT RdMemFromSdCard0(
								DeviceTypes sppuUsbDeviceTypes,
								char *fname = NULL, 
								DWORD addr = DEFAULT_SD_READ_ADDR, 
								DWORD numBytes = DEFAULT_NUM_OF_BYTES,
								DWORD *numByRdSuccess = NULL);

		__declspec(dllimport) HRESULT WrMemToSdCard0(
								DeviceTypes sppuUsbDeviceTypes,
								char *fname = NULL, 
								DWORD addr = DEFAULT_SD_WRITE_ADDR, 
								DWORD numBytes = DEFAULT_NUM_OF_BYTES, 
								DWORD *numByRdSuccess = NULL);

		__declspec(dllimport) HRESULT UpdateFirmWare(
								DeviceTypes Dev,
								char *fname);

		__declspec(dllimport) HRESULT RegisterRead(
								UINT32 addr,
								UINT32 *val);

		__declspec(dllimport) HRESULT RegisterWrite(
								UINT32 addr,
								UINT32 val);

		HRESULT UsbApis::c_UsbApis::SendCommandEP0(
					unsigned char *buf,
					BYTE dir, 
					UINT8 bRequest, 
					UINT16 mValue, 
					UINT16 mIndex, 
					UINT16 mLength);

		HRESULT UsbApis::c_UsbApis::RdEP0(
					UINT8 devType, 
					BYTE cmd, 
					unsigned char *buf, 
					LONG numBytes);

		HRESULT UsbApis::c_UsbApis::WrEP0(
					UINT8 devType,
					BYTE cmd = GET_SD_CARD_STATUS, 
					DWORD addr = DO_NOT_CARE, 
					DWORD numBlocks = DO_NOT_CARE);

		HRESULT UsbApis::c_UsbApis::spiFlashErase(
					DWORD numSpiSecToErase); 

		HRESULT UsbApis::c_UsbApis::spiFlashWrite(
					unsigned char *pBuf,
					UINT16 spiWrPgAddr,
					UINT16 numSpiPgsToWr,
					UINT16 *numByWrSuccess);

		__declspec(dllimport) HRESULT Testing(void *);

	public:
		ofstream SppuUsbDllDebug;
		ULONG m_nStartValue;
		static BOOL m_bOpenFlag;
		struct threadParams
		{
			BOOL flag;
			CCyUSBDevice *USBDevice;
		}thParams;

		c_UsbApis()
		{
			thParams.flag = FALSE;
		}
	};
}

DWORD WINAPI USBDebug(LPVOID lpParam);
#endif