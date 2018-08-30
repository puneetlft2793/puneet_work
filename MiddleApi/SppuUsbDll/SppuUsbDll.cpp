// SppuUsbDll.cpp : Defines the exported functions for the DLL application.

//Changing code to suppport data and address size between 0 to 4 GiB on SD Card
//############################################################################# for ctrl+z

#include "stdafx.h"

#include "SppuUsbDll.h"
#include <iostream>
#include <cyioctl.h>
#include <fstream>
#include <sys/stat.h>
#include <time.h>			//for time()

//__HP__6:
#ifndef FPGA_DDR_RESOLUTION
#define FPGA_DDR_RESOLUTION		0x8
#endif


//#include <atlstr.h>			// for non MFC string Objects

#define MAX_NUM_BYTES_SD_CARD_ONE_TIME		33553920	//4294967296//					//(61440 * 512)		//This many bytes(s) will be programed in one go 
/*change the following buf for performance in SlaveFIFO case */

#define MAX_NUM_BYTES_DDR_ONE_TIME			0x7FFF4		//// 0xC8000 - 0xc//(512KiB - 0xc)// 65523 //(65525 - )xc for 0xffff)	//12 Bytes Header + 16 Kib Data
#define LFT_SPPU_SLAVE_FIFO_HEADER_SIZE		0xC

#define LFT_SPPU_SLAVE_FIFO_XFER_BUF_SIZE	0x3FF4		////0xC7FF4//0x3FF4//(0x40000 - 0xc)//4097//1024
#define MAX_NUM_BYTES_DDR_REG_ACCESS		16			//12 header and 4 bytes vale 
#define FPGA_DDR_ACCESS_ADDR				0x00004200	//TODO : Mohit
#define FPGA_SPI_FLASH_ACCESS_ADDR			0x00004204 
#define FPGA_REG_ACCESS_ADDR				0x00000001	//TODO : Mohit (not used though)

/*change the following buf for performance in SD Card case */
#define DMA_RD_SIZE							4096		//524288//65536//16384//4096
#define DMA_WR_SIZE							4096		//524288//65536//16384//4096
#define MIN_DMA_XFER_SIZE					512
#define DMA_SD_CARD_WR_RELATION				(DMA_WR_SIZE / SD_CARD_PAGE_SIZE)	// Means (8 * SD_CARD_PAGE_SIZE) = DMA_xx_SIZE

#define DEFAULT_NUM_BY_RD_EP0				4

// SPI Flash related Macros
#define SPI_FLASH_PAGE_SIZE					256
#define SPI_FLASH_WR_BUF_SIZE				4096
#define SPI_FLASH_NUM_SECTORS				8
#define SPI_FLASH_SECTOR_SIZE				65536		//64 * 1024		//64 KiB
#define SPI_FLASH_SIZE						(SPI_FLASH_SECTOR_SIZE * SPI_FLASH_NUM_SECTORS)
#define SPI_FLASH_WR_RELATION				(SPI_FLASH_WR_BUF_SIZE / SPI_FLASH_PAGE_SIZE)

#define SPI_FLASH_REQ_WR					0xC2
#define SPI_FLASH_REQ_RD					0xC3
#define SPI_FLASH_REQ_ERASE_POLL			0xC4

#define LFT_SPPU_REQ_REG_WRITE				0xF2
#define LFT_SPPU_REQ_REG_READ				0xF3
#define LFT_SPPU_RQT_GET_EP0				0xF4

#define LFT_SPPU_FW_ID_CHECK				0xB0		//TODO Fw Id Check
#define ENABLE_FW_DEBUGGING					0xB1
#define DISABLE_FW_DEBUGGING				0xB1

#define LFT_SPPU_SLAVE_FIFO_DMA_INIT		0xD5


unsigned char lftSppuPacketFormatRecv[16] = 
{
	0xAA,
	0x88,		/* 2 bytes for Magic Number */

	0x00,
	0x00,		/* 2 bytes for length of data + this header */

	0x00,		/* Reserver */
	0x02,		/* 0x01 = Reg Write; 0x02 = Reg Read */
	0x00,		/* Reserver */
	0x00,		/* 4 CMD */

	0x00,
	0x00,
	0x00,
	0x00,		/* 4 bytes address */

	0x00,
	0x00,
	0x00,
	0x00,		/* 4 bytes value */
};

unsigned char lftSppuPacketFormatSend[16] = 
{
	0xCC,
	0x77,		/* 2 bytes for Magic Number */

	0x00,
	0x00,		/* 2 bytes for length of data + this header */

	0x00,		/* Reserver */
	0x01,		/* 0x01 = Reg Write; 0x02 = Reg Read */
	0x00,		/* Reserver */
	0x00,		/* 4 CMD */

	0x00,
	0x00,
	0x00,
	0x00,		/* 4 address */
	
	0x00,
	0x00,
	0x00,
	0x00,		/* 4 bytes value */
};

//#define BLOCKS_TO_BYTES(NumBlocks, BlkSize)	(NumBlocks * BlkSize) 

//BOOL UsbApis::c_UsbApis::m_bBulkLoopCompleted = TRUE;

HRESULT UsbApis::c_UsbApis::SppuFwVersion()
{
	unsigned char FwID[32] = {0};
	BOOL ret;
	if(OpenDevice())
		return -1;

	ret = SendCommandEP0(FwID, 1, LFT_SPPU_FW_ID_CHECK, DO_NOT_CARE, DO_NOT_CARE, 8);
	if(0 == ret)
	{
		if(0 == strncmp((const char *)FwID, "LFT", 3))
		{
			#if DEBUG
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug << "SUCCESS: Firmware Recognized. FW Id = "<< 
				FwID[3] << "." << FwID[4] << "." << FwID[5] << FwID[6] << endl;
			SppuUsbDllDebug.close();
			#endif
		}
		else
		{
			#if DEBUG
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug << "ERROR : Unknown FirmWare! Aborting..." << endl;
			SppuUsbDllDebug.close();
			#endif
			return -1;
		}
	}
	else
	{
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
	//	SppuUsbDllDebug << "ERROR : RegRead unable to value read at EP0" << endl;
		SppuUsbDllDebug.close();
		return -1;
	}
	return S_OK;
}

//This API can be used for testing with little modification as per case under test
#pragma region Testing
HRESULT UsbApis::c_UsbApis::Testing(void *p)
{

#if 1 // FW Version
	#if DEBUG
	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
	SppuUsbDllDebug << "\t\t" << "____TESTING____ Firmware Id "<< endl;
	SppuUsbDllDebug.close();
	#endif
	SppuFwVersion();
#endif			//FPGA Verison


#if 0
	if(OpenDevice())
		return -1;
	else
		return S_OK;
#endif


#if 0			//End Points
	int ret = 1;
	unsigned char buf[32] = {0};
	
	if(OpenDevice())
		return -1;
	
	ret = SendCommandEP0(buf, 1, ENABLE_FW_DEBUGGING, DO_NOT_CARE, DO_NOT_CARE, 8);
	if(0 == ret)
	{
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "SUCCESS : Testing SUCCESS" << endl;
		SppuUsbDllDebug.close();
	}
	else
	{
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "ERROR : Testing Failure" << endl;
		SppuUsbDllDebug.close();
		return -1;
	}

#pragma region NumBulkEPs
	CCyUSBDevice *USBDevice = new CCyUSBDevice(NULL);
	int  eptCount = USBDevice->EndPointCount();
	int i,NumBulkInEPs = 0, NumBulkOutEPs = 0, lpCounter = 0;
	for  ( i=1 ; i<eptCount; i++) 
	{	lpCounter++;
		bool  bIn1 = ((USBDevice->EndPoints[i]->Address & 0xFF) == UsbEpAddr::LFT_SPPU_FPGA_BULK_RD_EP);			//End Point Address
		bool  bIn3 = ((USBDevice->EndPoints[i]->Address & 0xFF) == UsbEpAddr::LFT_SPPU_SDCARD_BULK_RD_EP) ;
		bool  bOut1 = ((USBDevice->EndPoints[i]->Address & 0xFF) == UsbEpAddr::LFT_SPPU_FPGA_BULK_WR_EP);			//End Point Address
		bool  bOut3 = ((USBDevice->EndPoints[i]->Address & 0xFF) == UsbEpAddr::LFT_SPPU_SDCARD_BULK_WR_EP) ;
		bool  bBulk = (USBDevice->EndPoints[i]->Attributes == 2 );				//Type of End Point 0=control, 1= Iso, 2= Bulk, 3= Interrupt
		if (bBulk && (bIn1 || bIn3)) 
		{
			if(bIn1)
			{
				usbEp.fpgaBulkIn = (CCyBulkEndPoint *) USBDevice->EndPoints[i];
				cout << "bIn1  : i = " << i << endl;
			}
			else if(bIn3)
			{
				usbEp.sdCardBulkIn = (CCyBulkEndPoint *) USBDevice->EndPoints[i];
				cout << "bIn3  : i = " << i << endl;
			}
			else break;
			NumBulkInEPs++;
		}
		if  (bBulk && (bOut1 || bOut3)) 
		{
			if(bOut1)
			{
				usbEp.fpgaBulkOut = (CCyBulkEndPoint *) USBDevice->EndPoints[i];
				cout << "bOut1 : i = " << i << endl;
			}
			else if(bOut3)
			{	
				usbEp.sdCardBulkOut = (CCyBulkEndPoint *) USBDevice->EndPoints[i];
				cout << "bOut1 : i = " << i << endl;
			}
			else break;
			NumBulkOutEPs++;
		}
	}
	delete USBDevice;
	USBDevice = NULL;
	cout << "Loop Counter is = " << lpCounter << endl;
	cout << "Number of Bulk Endpoints are = " << (NumBulkInEPs + NumBulkOutEPs) << endl;
	cout << "Number of Bulk In  Endpoints are = " << NumBulkInEPs << endl;
	cout << "Number of Bulk OUT Endpoints are = " << NumBulkOutEPs << endl;
	
	return S_OK;
#pragma endregion NumBulkEPs
#endif			//End Points


#if 0	//FW Update
	int ret;
	if(OpenDevice())
		return -1;
	unsigned char *pBuf = (unsigned char *)p;
	unsigned char spiStatus;
	//Erase First sector
	SendCommandEP0(pBuf, 0, 0xC4, 0x0001, 0x0000, 0x0000);
	
	//Poll for erase to complete
	do{
		ret = SendCommandEP0(&spiStatus, 1, 0xC4, 0x0000, 0x0000, 0x0001);
		if(ret != 0)
		{
			#if DEBUG
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug << "ERROR: Erase POLL Error" << endl;
			SppuUsbDllDebug.close();
			#endif
			return -1;
		}
	}while(0 != spiStatus);
		
	//Write First sector
	SendCommandEP0(pBuf, 0, 0xC2, 0x0000, 0x0000, 0x1000);

	//Poll for write to complete
	do{
		ret = SendCommandEP0(&spiStatus, 1, 0xC4, 0x0000, 0x0000, 0x0001);
		if(ret != 0)
		{
			#if DEBUG
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug << "ERROR: SendCommandEP0 Write POLL Error" << endl;
			SppuUsbDllDebug.close();
			#endif
			return -1;
		}
	}while(0 != spiStatus);
#endif			//FW Update in SPI Flash of FX3S.

	return S_OK;
}
#pragma endregion Testing

#pragma region UsbCommands

HRESULT UsbApis::c_UsbApis::SendCommandEP0(unsigned char *buf, BYTE dir, UINT8 bRequest, UINT16 wValue, UINT16 wIndex, UINT16 wLength)
{
	#if DEBUG
	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
//	SppuUsbDllDebug << "============================ Send Command EP 0 ============================" << endl;
	SppuUsbDllDebug.close();
	#endif
	if(UsbApis::c_UsbApis::thParams.flag == TRUE)
	{
		BOOL ret = S_FALSE;
		LONG bytesToRead = wLength;

		OVERLAPPED OvLap;
		OvLap.hEvent = CreateEvent(NULL, false, false, L"CYUSB_CTL");

		// Just for typing efficiency
		CCyControlEndPoint *ept = thParams.USBDevice->ControlEndPt;
		ept->Target = TGT_DEVICE;
		ept->ReqType = REQ_VENDOR;
		if(0 == dir)
			ept->Direction = DIR_TO_DEVICE;
		if(1 == dir)
			ept->Direction = DIR_FROM_DEVICE;
		
		ept->ReqCode = bRequest;		//C0: Status; C1: read; C2: write (SD Card Related)
		ept->Value = wValue;
		ept->Index = wIndex;
		
		//TODO :  use xfer instead of this
		PUCHAR Context = ept->BeginDataXfer(buf, bytesToRead, &OvLap);		
		ept->WaitForXfer(&OvLap, 100);
		ept->FinishDataXfer(buf, bytesToRead, &OvLap, Context);
		CloseHandle(OvLap.hEvent);
		
		if(1 == dir)
		{
			if(bytesToRead > 0)
				return S_OK;
			else
				return -1;
		}
	}
	else
	{
		#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "ERROR: Device Not Opened!" << endl;
		SppuUsbDllDebug.close();
		#endif
		return -1;
	}
	return S_OK;
}

HRESULT UsbApis::c_UsbApis::RdEP0(UINT8 devType, BYTE cmd, unsigned char *buf, LONG numBytes)
{
	#if STATUS_DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "======================= RdEP0 =======================" << endl;
	#endif
	if(UsbApis::c_UsbApis::thParams.flag == TRUE)
	{
		BOOL ret = S_FALSE;
		CCyControlEndPoint *ept = thParams.USBDevice->ControlEndPt;
		buf[8] = (devType & 0xFF);
		//buf[9] = '\0';

		ept->Target = TGT_DEVICE;
		ept->ReqType = REQ_VENDOR;
		ept->ReqCode = cmd;								//C0: Status; C1: read; C2: write (SD Card Related)
		
		ret = ept->Read(buf, numBytes);
		if(1 == ret)
		{
			if(numBytes > 0)
			{
			#if STATUS_DEBUG
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
//			SppuUsbDllDebug << "STATUS: CP read() returned = " << ret << endl;
//			SppuUsbDllDebug << "STATUS: No of bytes wrote  = " << numBytes << endl;
			SppuUsbDllDebug.close();
			#endif
			}
		}
		else
		{
			#if STATUS_DEBUG
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug << "ERROR: CP read() returned = " << ret << endl;
			SppuUsbDllDebug << "ERROR: No of bytes wrote  = " << numBytes << endl;
			SppuUsbDllDebug.close();
			#endif
			return -1;
		}
	}
	else
	{
	#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "ERROR : Device Not Opened!" << endl;
		SppuUsbDllDebug.close();
	#endif
		return -1;
	}
	return S_OK;
}

HRESULT UsbApis::c_UsbApis::WrEP0(UINT8 devType, BYTE cmd, DWORD addr, DWORD numSdBlks)
{
	if(UsbApis::c_UsbApis::thParams.flag == TRUE)
	{
		BOOL ret = S_FALSE;
		unsigned char buf[9] = {0};
		LONG bytesToRead = 9;
		CCyControlEndPoint *ept = thParams.USBDevice->ControlEndPt;

		buf[0] = (addr & 0xFF) >> 0;
		buf[1] = (addr & 0xFF00) >> 8;
		buf[2] = (addr & 0xFF0000) >> 16;
		buf[3] = (addr & 0xFF000000) >> 24;

		buf[4] = (numSdBlks & 0xFF) >> 0;
		buf[5] = (numSdBlks & 0xFF00) >> 8;
		buf[6] = (numSdBlks & 0xFF0000) >> 16;
		buf[7] = (numSdBlks & 0xFF000000) >> 24;

		buf[8] = (devType & 0xFF);
		//buf[9] = '\0';

		// Just for typing efficiency
		ept->Target = TGT_DEVICE;
		ept->ReqType = REQ_VENDOR;
		ept->ReqCode = cmd;								//C0: Status; C1: read; C2: write (SD Card Related)
		
		ret = ept->Write(buf, bytesToRead);
		if(1 == ret)
		{
			if(bytesToRead > 0)
			{
				#if STATUS_DEBUG
				SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
//				SppuUsbDllDebug << "STATUS: CP write() returned = " << ret << endl;
//				SppuUsbDllDebug << "STATUS: No of bytes write   = " << bytesToRead << endl;
				SppuUsbDllDebug.close();
				#endif
			}
		}
		else
		{
			#if STATUS_DEBUG
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug << "ERROR: CP write() returned = " << ret << endl;
			SppuUsbDllDebug << "ERROR: No of bytes wrote  = " << bytesToRead << endl;
			SppuUsbDllDebug.close();
			#endif
			return -1;
		}
	}
	else
	{
		#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "ERROR : Device Not Opened!" << endl;
		SppuUsbDllDebug.close();
		#endif
		return -1;
	}
	return S_OK;
}
#pragma endregion UsbCommands

//APIs to access various Device Registers
#pragma region RegAccess


HRESULT UsbApis::c_UsbApis::__RdRegFrDdr(unsigned char *buf, DWORD bufSize)
{
	LONG length = bufSize;
	if(usbEp.fpgaBulkIn)
	{
		if(usbEp.fpgaBulkIn->XferData(buf, length))
		{
			if(length > 0)
			{
				return S_OK;
			}
			else
			{
				#if DEBUG_ERROR
				SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
				SppuUsbDllDebug << "ERROR: Read Zero Bytes from fpgaBulkIn EndPoint!" << endl;
				SppuUsbDllDebug.close();
				#endif
			}
		}
		else
		{
			#if DEBUG_ERROR
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug << "ERROR: fpgaBulkIn->XferData failure" << endl;
			SppuUsbDllDebug.close();
			#endif
			return -1;
		}
	}
	else
	{
		#if DEBUG_ERROR
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "ERROR: No BulkIn Endpoint found on Device" << endl;
		SppuUsbDllDebug.close();
		#endif
		return -1;
	}
#if 0
	#if DEBUG_STATUS
	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
	SppuUsbDllDebug << "STATUS: Number of bytes READ from fpgaBulkIn EndPoint = 0x" << std::hex << length << std::dec << endl;
	SppuUsbDllDebug.close();
	#endif
#endif

	return S_OK;
}


//API to read device register.
HRESULT UsbApis::c_UsbApis::RegisterRead(UINT32 addr, UINT32 *val)
{
	BOOL ret = S_FALSE;
	UINT32 lVal = 0;
	*val = 0;
//	unsigned char wDevRegBuf[MAX_NUM_BYTES_DDR_REG_ACCESS + 1] = {'\0'};	// 12 bytes for Header + 4 bytes value
//	unsigned char rDevRegBuf[MAX_NUM_BYTES_DDR_REG_ACCESS + 1] = {'\0'};
	
	lftSppuPacketFormatSend[2] = ((MAX_NUM_BYTES_DDR_REG_ACCESS & 0xFF00) >> 8);
	lftSppuPacketFormatSend[3] = (MAX_NUM_BYTES_DDR_REG_ACCESS & 0xFF);

	lftSppuPacketFormatSend[5] = 0x02;							//Write command

	lftSppuPacketFormatSend[8] = ((addr & 0xFF000000) >> 24);
	lftSppuPacketFormatSend[9] = ((addr & 0x00FF0000) >> 16);
	lftSppuPacketFormatSend[10] = ((addr & 0x0000FF00) >> 8);
	lftSppuPacketFormatSend[11] = (addr & 0x000000FF);

	if(OpenDevice())
		return -1;

		unsigned char dummyBuf = '\0';

#if 0
	SendCommandEP0(&dummyBuf, 0, LFT_SPPU_SLAVE_FIFO_DMA_INIT, 0x0000, 0x0000, 0x0001);	//wLength = (0x0001 = DMA Init, 0x0000 = DMA Un-Init)) 
	do{
			ret = SendCommandEP0(&dummyBuf, 1, LFT_SPPU_SLAVE_FIFO_DMA_INIT, DO_NOT_CARE, DO_NOT_CARE, 0x0001);
	}while(0 != dummyBuf);
#endif


#if 0
			#if DEBUG_STATUS
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug << "\t\tBUFFER     SENT is :" << std::hex <<
				lftSppuPacketFormatSend[0] <<  std::hex <<
				lftSppuPacketFormatSend[1] <<  std::hex <<
				lftSppuPacketFormatSend[2] <<  std::hex <<
				lftSppuPacketFormatSend[3] <<  std::hex <<
				lftSppuPacketFormatSend[4] <<  std::hex <<
				lftSppuPacketFormatSend[5] <<  std::hex << 
				lftSppuPacketFormatSend[6] <<  std::hex <<
				lftSppuPacketFormatSend[7] <<  std::hex <<
				lftSppuPacketFormatSend[8] <<  std::hex <<
				lftSppuPacketFormatSend[9] <<  std::hex <<
				lftSppuPacketFormatSend[10] << std::hex <<
				lftSppuPacketFormatSend[11] << std::hex <<
				lftSppuPacketFormatSend[12] << std::hex <<
				lftSppuPacketFormatSend[13] << std::hex <<
				lftSppuPacketFormatSend[14] << std::hex <<
				lftSppuPacketFormatSend[15] << std::dec << "end" << endl << endl;
			SppuUsbDllDebug.close();
			#endif
#endif


	ret = __WrRegToDdr(lftSppuPacketFormatSend, MAX_NUM_BYTES_DDR_REG_ACCESS);
	if(ret == S_OK)
	{
#if 0
		#if DEBUG_STATUS
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "SUCCESS: SENT INFO : Value Read at Reg 0x"<< std::hex << addr << endl;
		SppuUsbDllDebug.close();
		#endif
#endif
		//Get Response
		ret = __RdRegFrDdr(lftSppuPacketFormatRecv, MAX_NUM_BYTES_DDR_REG_ACCESS);
		if(ret == S_OK)
		{
#if 0
			#if DEBUG_STATUS
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug << "\t\tBUFFER Recieved is :" << std::hex <<
				lftSppuPacketFormatRecv[0] <<  std::hex <<
				lftSppuPacketFormatRecv[1] <<  std::hex <<
				lftSppuPacketFormatRecv[2] <<  std::hex <<
				lftSppuPacketFormatRecv[3] <<  std::hex <<
				lftSppuPacketFormatRecv[4] <<  std::hex <<
				lftSppuPacketFormatRecv[5] <<  std::hex << 
				lftSppuPacketFormatRecv[6] <<  std::hex <<
				lftSppuPacketFormatRecv[7] <<  std::hex <<
				lftSppuPacketFormatRecv[8] <<  std::hex <<
				lftSppuPacketFormatRecv[9] <<  std::hex <<
				lftSppuPacketFormatRecv[10] << std::hex <<
				lftSppuPacketFormatRecv[11] << std::hex <<
				lftSppuPacketFormatRecv[12] << std::hex <<
				lftSppuPacketFormatRecv[13] << std::hex <<
				lftSppuPacketFormatRecv[14] << std::hex <<
				lftSppuPacketFormatRecv[15] << std::dec << "end" << endl << endl;
			SppuUsbDllDebug.close();
			#endif
#endif

			/*if((*(lftSppuPacketFormatRecv + 0)) == (*(lftSppuPacketFormatRecv + 0)) && \
				(*(lftSppuPacketFormatRecv + 1)) == (*(lftSppuPacketFormatRecv + 1)))*/
			if((*(lftSppuPacketFormatRecv + 0)) == (0xAA) && \
				(*(lftSppuPacketFormatRecv + 1)) == (0x88))
			{
				if((*(lftSppuPacketFormatRecv + 11)) == 0x00)
				{
					lVal = (lftSppuPacketFormatRecv[15] & 0xFF);
					lVal |= ((lftSppuPacketFormatRecv[14] & 0xFF) << 8);
					lVal |= ((lftSppuPacketFormatRecv[13] & 0xFF) << 16);
					lVal |= ((lftSppuPacketFormatRecv[12] & 0xFF) << 24);
					*val = lVal;
					#if DEBUG_INFO
					SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
//					SppuUsbDllDebug << "SUCCESS: Valid Response Status! = "<< *(lftSppuPacketFormatRecv + 11) << endl;
					SppuUsbDllDebug << "\nSUCCESS: Value Read at Reg 0x"<< std::hex << addr << std::dec << 
						" = 0x" << std::hex << *val << std::dec << endl << endl;
					SppuUsbDllDebug.close();
					#endif
				}
				else
				{
					#if DEBUG_ERROR
					SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
					SppuUsbDllDebug << "ERROR : Invalid Respponse Status! = " << *(lftSppuPacketFormatRecv + 11) << endl;
					SppuUsbDllDebug.close();
					#endif
					goto OUT_ERR;
				}
			}
			else
			{
				#if DEBUG_ERROR
				SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
				SppuUsbDllDebug << "ERROR : Invalid Response packet! = 0x" << std::hex << 
					(*(lftSppuPacketFormatRecv + 0)) << (*(lftSppuPacketFormatRecv + 1)) << std::dec << endl;
				SppuUsbDllDebug.close();
				#endif
				goto OUT_ERR;
			}
		}
		else
		{
			#if DEBUG_ERROR
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug << "ERROR : RegRead unable to value read at FPGA_EP" << endl;
			SppuUsbDllDebug.close();
			#endif
			goto OUT_ERR;
		}
	}
	else
	{
		#if DEBUG_ERROR
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "ERROR : RegWrite unable to Write at FPGW_EP" << endl;
		SppuUsbDllDebug.close();
		#endif
		goto OUT_ERR;
	}
	//Success
#if 0
	SendCommandEP0(&dummyBuf, 0, LFT_SPPU_SLAVE_FIFO_DMA_INIT, 0x0000, 0x0000, 0x0000);
	do{
			ret = SendCommandEP0(&dummyBuf, 1, LFT_SPPU_SLAVE_FIFO_DMA_INIT, DO_NOT_CARE, DO_NOT_CARE, 0x0000);
	}while(0 != dummyBuf);
	//Wait for valid status
#endif
	return S_OK;
OUT_ERR:	//Error
#if 0
	SendCommandEP0(&dummyBuf, 0, LFT_SPPU_SLAVE_FIFO_DMA_INIT, 0x0000, 0x0000, 0x0000);
	do{
			ret = SendCommandEP0(&dummyBuf, 1, LFT_SPPU_SLAVE_FIFO_DMA_INIT, DO_NOT_CARE, DO_NOT_CARE, 0x0000);
	}while(0 != dummyBuf);
#endif
	return -1;
}

HRESULT UsbApis::c_UsbApis::__WrRegToDdr(unsigned char *buf, DWORD numBytes)
{
	LONG length = numBytes;

	//Remove till first return statement
//	*numBytesWrSuccess = bufSize;
//	return S_OK;
	
#if 0
//	#if DEBUG_STATUS
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "STATUS: __WrFileToDdr__ :: Request of: 0x" << std::hex << bufSize << std::dec << " transfer" << endl;
		SppuUsbDllDebug.close();
	#endif

	if(usbEp.fpgaBulkOut)
	{
		if(usbEp.fpgaBulkOut->XferData(buf, length))
		{
			if(length > 0)
			{
					return S_OK;
			}
			else
			{
				#if DEBUG_ERROR
				SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
				SppuUsbDllDebug << "ERROR: Wrote Zero Bytes to fpgaBulkIn EndPoint!" << endl;
				SppuUsbDllDebug.close();
				#endif
				return -1;
			}
		}
		else
		{
			#if DEBUG_ERROR
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug << "ERROR : fpgaBulkOut->XferData failure" << endl;
			SppuUsbDllDebug.close();
			#endif
			return -1;				//Error while reading from BulkOut End Point
		}
	}
	else
	{
		#if DEBUG_ERROR
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "ERROR : No BulkOut Endpoint found on Device" << endl;
		SppuUsbDllDebug.close();
		#endif
		return -1;
	}
#if 0
//#if DEBUG_STATUS
SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
SppuUsbDllDebug << "STATUS: __WrFileToDdr : Number of bytes SENT to FPGA = 0x" << std::hex << NumByWrSuccess << std::dec << endl;
SppuUsbDllDebug.close();
#endif
	return S_OK;
}

//API to write device register.
HRESULT UsbApis::c_UsbApis::RegisterWrite(UINT32 addr, UINT32 val)
{
	BOOL ret = S_FALSE;
	DWORD dummy = DO_NOT_CARE;

	//HACK to add support for multiple stream addresses for multiple channels in FPGA (DDR, FIFO, STREAM, etc), HP, 16 May 2016
	if(addr == 0x10000000)
	{
		m_nBulkStreamType = val;
#if DEBUG_STATUS
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "STATUS : **Current Stream** =" << std::hex << m_nBulkStreamType << std::dec << endl;
		SppuUsbDllDebug.close();
#endif
		return 0;
	}

	lftSppuPacketFormatSend[2] = ((MAX_NUM_BYTES_DDR_REG_ACCESS & 0xFF00) >> 8);
	lftSppuPacketFormatSend[3] = (MAX_NUM_BYTES_DDR_REG_ACCESS & 0xFF);

	lftSppuPacketFormatSend[5] = 0x01;							//Write command
	
	lftSppuPacketFormatSend[8] = ((addr & 0xFF000000) >> 24);
	lftSppuPacketFormatSend[9] = ((addr & 0x00FF0000) >> 16);
	lftSppuPacketFormatSend[10] = ((addr & 0x0000FF00) >> 8);
	lftSppuPacketFormatSend[11] = (addr & 0x000000FF);
	
	lftSppuPacketFormatSend[12] = ((val & 0xFF000000) >> 24);
	lftSppuPacketFormatSend[13] = ((val & 0x00FF0000) >> 16);
	lftSppuPacketFormatSend[14] = ((val & 0x0000FF00) >> 8);
	lftSppuPacketFormatSend[15] = ((val & 0x000000FF) >> 0);

	if(OpenDevice())
		return -1;
#if 0
	#if DEBUG_STATUS
	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
	SppuUsbDllDebug << "============================ Reg Write ============================" << endl;
	SppuUsbDllDebug.close();
	#endif
#endif

#if 0	
	//Send Write command
	SendCommandEP0(&dummyBuf, 0, LFT_SPPU_SLAVE_FIFO_DMA_INIT, 0x0000, 0x0000, 0x0001);	//wLength = (0x0001 = DMA Init, 0x0000 = DMA Un-Init)) 
	//Wait for valid status
	do{
			ret = SendCommandEP0(&dummyBuf, 1, LFT_SPPU_SLAVE_FIFO_DMA_INIT, DO_NOT_CARE, DO_NOT_CARE, 0x0001);
	}while(0 != dummyBuf);
#endif

	ret = __WrRegToDdr(lftSppuPacketFormatSend, MAX_NUM_BYTES_DDR_REG_ACCESS);
	if(ret == S_OK)
	{
#if 0
		#if STATUS_DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "SUCCESS: SENT INFO : Value Write at Reg 0x" << std::hex << addr << " is 0x" << std :: hex << val 
			<< std::dec << endl;
		SppuUsbDllDebug.close();
		#endif
#endif
		//Get Response
		ret = __RdRegFrDdr(lftSppuPacketFormatRecv, MAX_NUM_BYTES_DDR_REG_ACCESS);
		if(ret == S_OK)
		{
#if 0
			#if DEBUG_STATUS
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug << "\t\tBUFFER Recieved is -" << std::hex <<
				lftSppuPacketFormatRecv[0] <<  std::hex <<
				lftSppuPacketFormatRecv[1] <<  std::hex <<
				lftSppuPacketFormatRecv[2] <<  std::hex <<
				lftSppuPacketFormatRecv[3] <<  std::hex <<
				lftSppuPacketFormatRecv[4] <<  std::hex <<
				lftSppuPacketFormatRecv[5] <<  std::hex << 
				lftSppuPacketFormatRecv[6] <<  std::hex <<
				lftSppuPacketFormatRecv[7] <<  std::hex <<
				lftSppuPacketFormatRecv[8] <<  std::hex <<
				lftSppuPacketFormatRecv[9] <<  std::hex <<
				lftSppuPacketFormatRecv[10] << std::hex <<
				lftSppuPacketFormatRecv[11] << std::hex <<
				lftSppuPacketFormatRecv[12] << std::hex <<
				lftSppuPacketFormatRecv[13] << std::hex <<
				lftSppuPacketFormatRecv[14] << std::hex <<
				lftSppuPacketFormatRecv[15] << std::dec  << "end" << endl << endl;
			SppuUsbDllDebug.close();
			#endif
#endif

			if((*(lftSppuPacketFormatRecv + 0)) == (0xAA) && \
				(*(lftSppuPacketFormatRecv + 1)) == (0x88))
			{
				if((*(lftSppuPacketFormatRecv + 11)) == 0x00)
				{
					#if DEBUG_INFO
					SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
					//SppuUsbDllDebug << "SUCCESS: Valid Response Status! = "<< *(lftSppuPacketFormatRecv + 11) << endl;
					SppuUsbDllDebug << "\nSUCCESS: Value Written at Reg 0x"<< std::hex << addr << std::dec << 
						" = 0x" << std::hex << val << std::dec << endl << endl;
					SppuUsbDllDebug.close();
					#endif
				}
				else
				{
					#if DEBUG_ERROR
					SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
					SppuUsbDllDebug << "ERROR : Invalid response status! = " << *(lftSppuPacketFormatRecv + 11) << endl;
					SppuUsbDllDebug.close();
					#endif
					goto OUT_ERR;
				}
			}
			else
			{
				#if DEBUG_ERROR
				SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
				SppuUsbDllDebug << "ERROR : Invalid Response packet! = 0x" << std::hex << 
					(*(lftSppuPacketFormatRecv + 0)) << (*(lftSppuPacketFormatRecv + 1)) << std::dec << endl;
				SppuUsbDllDebug.close();
				#endif
				goto OUT_ERR;
			}
		}
		else
		{
			#if DEBUG_ERROR
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug << "ERROR : RegRead unable to read value at FPGA_EP" << endl;
			SppuUsbDllDebug.close();
			#endif
			goto OUT_ERR;
		}
	}
	else
	{
		#if DEBUG_ERROR
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "ERROR : RegWrite unable to Write at FPGA_EP0" << endl;
		SppuUsbDllDebug.close();
		#endif
		goto OUT_ERR;
	}	
#if 0
	//Success
	//Wait for valid status
	SendCommandEP0(&dummyBuf, 0, LFT_SPPU_SLAVE_FIFO_DMA_INIT, 0x0000, 0x0000, 0x0000);	//wLength = (0x0001 = DMA Init, 0x0000 = DMA Un-Init)) 
	//Wait for valid status
	do{
			ret = SendCommandEP0(&dummyBuf, 1, LFT_SPPU_SLAVE_FIFO_DMA_INIT, DO_NOT_CARE, DO_NOT_CARE, 0x0000);
	}while(0 != dummyBuf);
#endif
	return S_OK;
OUT_ERR:	//Error
#if 0
	SendCommandEP0(&dummyBuf, 0, LFT_SPPU_SLAVE_FIFO_DMA_INIT, 0x0000, 0x0000, 0x0000);
	do{
			ret = SendCommandEP0(&dummyBuf, 1, LFT_SPPU_SLAVE_FIFO_DMA_INIT, DO_NOT_CARE, DO_NOT_CARE, 0x0000);
	}while(0 != dummyBuf);
#endif
	return -1;
}
#pragma endregion RegAccess


#pragma region WriteToDDR

HRESULT UsbApis::c_UsbApis::__WrToDdr(DeviceTypes devType, unsigned char *buf, DWORD bufSize, DWORD *numBytesWrSuccess)
{
	LONG length = 0;
	DWORD lBufSize = bufSize;
	DWORD NumByWrSuccess = 0;

	//DWORD address  = FPGA_DDR_ACCESS_ADDR;
	DWORD address  = m_nBulkStreamType;
#if 0
#if DEBUG_ERROR
	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
	SppuUsbDllDebug << "INFO: address __WrToDdr() m_nBulkStreamType = " << std::hex << address << std::dec << endl;
	SppuUsbDllDebug.close();
#endif
#endif


	unsigned char buffer[LFT_SPPU_SLAVE_FIFO_XFER_BUF_SIZE + LFT_SPPU_SLAVE_FIFO_HEADER_SIZE] = {'\0'};

	*(buffer + 0) = *(lftSppuPacketFormatSend + 0);
	*(buffer + 1) = *(lftSppuPacketFormatSend + 1);

	*(buffer + 4) = *(lftSppuPacketFormatSend + 4);
	*(buffer + 5) = 0x01;							//Write command
	*(buffer + 6) = *(lftSppuPacketFormatSend + 6);
	*(buffer + 7) = *(lftSppuPacketFormatSend + 7);

	if(devType == DeviceTypes::LFT_SPPU_DEV_FPGA_SPI_FLASH)
	{
		address = FPGA_SPI_FLASH_ACCESS_ADDR;
	}

	*(buffer + 8) = ((address & 0xFF000000) >> 24);
	*(buffer + 9) = ((address & 0x00FF0000) >> 16);
	*(buffer + 10) = ((address & 0x0000FF00) >> 8);
	*(buffer + 11) = (address & 0x000000FF);


	//Remove till first return statement for Tsting without HW
	//*numBytesWrSuccess = bufSize;
	//return S_OK;
	
#if 0
//	#if DEBUG_STATUS
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "STATUS: __WrFileToDdr__ :: Request of: 0x" << std::hex << bufSize << std::dec << " transfer" << endl;
		SppuUsbDllDebug.close();
#endif
	
	while(lBufSize)
	{
		if(lBufSize > LFT_SPPU_SLAVE_FIFO_XFER_BUF_SIZE)
			lBufSize = LFT_SPPU_SLAVE_FIFO_XFER_BUF_SIZE;

		if(usbEp.fpgaBulkOut)
		{
			if(NULL == memcpy((buffer + LFT_SPPU_SLAVE_FIFO_HEADER_SIZE), (buf + NumByWrSuccess), lBufSize))
			{
				#if DEBUG_ERROR
				SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
				SppuUsbDllDebug << "ERROR: MemCopy FAILURE!" << endl;
				SppuUsbDllDebug.close();
				#endif
				return -1;
			}
			
			length = (lBufSize + LFT_SPPU_SLAVE_FIFO_HEADER_SIZE);
			*(buffer + 2) = ((length & 0xFF00) >> 8);
			*(buffer + 3) = (length & 0xFF);
#if 0
			//#if DEBUG_STATUS
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug << "\t\tBUFFER SENT is -" << std::hex <<
				buf[0] <<  std::hex <<
				buf[1] <<  std::hex <<
				buf[2] <<  std::hex <<
				buf[3] <<  std::hex <<
				buf[4] <<  std::hex <<
				buf[5] <<  std::hex << 
				buf[6] <<  std::hex <<
				buf[7] <<  std::hex <<
				buf[8] <<  std::hex <<
				buf[9] <<  std::hex <<
				buf[10] << std::hex <<
				buf[11] << std::hex <<
				buf[12] << std::hex <<
				buf[13] << std::hex <<
				buf[14] << std::hex <<
				buf[15] << std::dec  << "end" << endl << endl;
			SppuUsbDllDebug << "NumByToSend = 0x" << std::hex << length << std::dec << endl;
			SppuUsbDllDebug << "NumByWrSuccess = 0x" << std::hex << NumByWrSuccess << std::dec << endl;
			SppuUsbDllDebug.close();
#endif

			if(usbEp.fpgaBulkOut->XferData(buffer, length))
			{
				if(length > 0)
				{
					NumByWrSuccess += (length - 12);
					lBufSize = bufSize - NumByWrSuccess;
					if(NumByWrSuccess == bufSize)
					{
						(*numBytesWrSuccess) = NumByWrSuccess;
						break;
					}
				}
				else
				{
					#if DEBUG_ERROR
					SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
					SppuUsbDllDebug << "ERROR: Wrote Zero Bytes to fpgaBulkIn EndPoint!" << endl;
					SppuUsbDllDebug.close();
					#endif
				}
			}
			else
			{
				#if DEBUG_ERROR
				SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
				SppuUsbDllDebug << "ERROR : fpgaBulkOut->XferData failure" << endl;
				SppuUsbDllDebug.close();
				#endif
				return -1;				//Error while reading from BulkOut End Point
			}
		}
		else
		{
			#if DEBUG_ERROR
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug << "ERROR : No BulkOut Endpoint found on Device" << endl;
			SppuUsbDllDebug.close();
			#endif
			return -1;
		}
	}

#if 0
//#if DEBUG_STATUS
SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
SppuUsbDllDebug << "STATUS: __WrFileToDdr : Number of bytes SENT to FPGA = 0x" << std::hex << NumByWrSuccess << std::dec << endl;
SppuUsbDllDebug.close();
#endif
	return S_OK;
}


HRESULT UsbApis::c_UsbApis::_WrFileToDdr(char *fname, DWORD faddr, DWORD numBytes, DWORD *numBytesWrSuccess)
{
	HRESULT hRes = S_OK;
	DWORD lNumBytes = numBytes;
	DWORD numByWrSuccess = 0;
	DWORD laddr = faddr;
	//__HP__6; Adding support : if File Size is not multiple of 4096 bytes then append 0s to make it multiple of 4096 bytes.< FPGA_DDR_RESOLUTION >
	int SizeDifference = 0, SizeModify = 0;
	//unsigned char IsFileSizeMul_64 = 1;		//Flag to chech whether 0s need to be append.
	unsigned char IsFileSizeMul_4096 = 1;		//Flag to chech whether 0s need to be append.
	FILE *rdBinFile;
	*numBytesWrSuccess = 0;
	unsigned char dummyBuf = '\0';
	/* Check file existance */
	if(!ifstream (fname))
	{	
#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "ERROR : File does not Exist!" << endl;
		SppuUsbDllDebug.close();
#endif
		return -1;
	}

	/* opening the file */
	if(!(rdBinFile = fopen(fname, "rb")))
	{
#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "ERROR : Can not Open File." << endl;
		SppuUsbDllDebug.close();
#endif
		return -1;
	}

	/* Get file size */
	fseek(rdBinFile, 0, SEEK_END);
	DWORD dwFileSize = ftell(rdBinFile);
	fseek(rdBinFile, 0, SEEK_SET);

	/* Check for valid data to program */
	if((lNumBytes == 0) || (lNumBytes > dwFileSize))
	{
#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "STATUS: Request of: " << lNumBytes << " byte transfer! Writing File Size: " << dwFileSize << endl;
		SppuUsbDllDebug.close();
#endif
		lNumBytes = dwFileSize;
		
		//__HP__2; Adding support : if File Size is not multiple of 64 bytes then append 0s to make it multiple of 64 bytes.
		if((SizeDifference = (lNumBytes % FPGA_DDR_RESOLUTION)) != 0)
		{
			IsFileSizeMul_4096 = 0;								//Flag update;
			SizeModify = (FPGA_DDR_RESOLUTION - SizeDifference);
			lNumBytes += SizeModify;
		}
	}
	
	int rcount = 1;
	DWORD numByToWr = lNumBytes;
	unsigned char wDevBuf[MAX_NUM_BYTES_DDR_ONE_TIME + 1] = {'\0'};	

	DWORD outerLpCounter = 0;

	//	SendCommandEP0(&dummyBuf, 0, LFT_SPPU_SLAVE_FIFO_DMA_INIT, 0x0000, 0x0000, 0x0001);	//wLength = (0x0001 = DMA Init, 0x0000 = DMA Un-Init)) 
	time_t seconds_begin, seconds_end, seconds;
	seconds_begin = time (NULL);

	while(numByToWr)
	{
		if(numByToWr > MAX_NUM_BYTES_DDR_ONE_TIME)
			numByToWr = MAX_NUM_BYTES_DDR_ONE_TIME;

		rcount = fread(wDevBuf, 1, numByToWr, rdBinFile);
		if(rcount < 0)
		{
			#if DEBUG
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug << "ERROR : Unable to read from File! API Returned = " << rcount << endl;
			SppuUsbDllDebug.close();
			#endif
			break;
		}
		else
		{
			memset((wDevBuf + rcount), '\0', (MAX_NUM_BYTES_DDR_ONE_TIME - rcount));
			//Handling of data when it is not a multiple of 64 bytes.
			if((numByToWr <= FPGA_DDR_RESOLUTION) && (!IsFileSizeMul_4096))
		
				rcount += SizeModify;
		}

		outerLpCounter++;		//Increment counter only when data is available

		if(S_OK != __WrToDdr(DeviceTypes::LFT_SPPU_DEV_DDR, wDevBuf, rcount, &numByWrSuccess))
		{
			#if DEBUG
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug << "ERROR : Write to DDR Failure" << endl;
			SppuUsbDllDebug.close();
			#endif
			break;
		}
//		numByWrSuccess -= LFT_SPPU_SLAVE_FIFO_HEADER_SIZE;
		(*numBytesWrSuccess) += numByWrSuccess;
		numByToWr = lNumBytes - (*numBytesWrSuccess);
		if(lNumBytes == (*numBytesWrSuccess))
		{
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			
			SppuUsbDllDebug.close();
			break;
		}
	}
	
	seconds_end = time (NULL);
	seconds = (seconds_end - seconds_begin);
	if(0 == seconds)
		seconds++;
	#if DEBUG
	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
	SppuUsbDllDebug << std::dec << "PERFORMANCE : DDR Write (FILE) : " << endl;
	SppuUsbDllDebug << "\t" << *numBytesWrSuccess << " Bytes in " << seconds << " Seconds; ";
	SppuUsbDllDebug << "\t" << (*numBytesWrSuccess / seconds) << " Bytes/Sec; " ;
	SppuUsbDllDebug << "\t" << ((*numBytesWrSuccess / seconds) >> 10) << " (KBps); ";
	SppuUsbDllDebug << "\t" << ((((*numBytesWrSuccess / seconds) >> 10)) >> 10) << " (MBps); " << endl;
	SppuUsbDllDebug << "STATUS: In Outer loop : " << outerLpCounter << " times" << endl;
	SppuUsbDllDebug.close();

	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
	SppuUsbDllDebug << "STATUS: Wrote in DDR : " << *numBytesWrSuccess << " Bytes, at address : "<< faddr << endl;
	SppuUsbDllDebug.close();
#endif
	fclose(rdBinFile);
	return S_OK;
}


HRESULT UsbApis::c_UsbApis::_WrBufToDdr(char *buf, DWORD faddr, DWORD numBytes, DWORD *numBytesWrSuccess)
{
	HRESULT hRes = S_OK;
	DWORD lNumBytes = numBytes;
	DWORD numByWrSuccess = 0;
	DWORD laddr = faddr;
	//__HP__6; Adding support : if File Size is not multiple of 4096 bytes then append 0s to make it multiple of 4096 bytes.< FPGA_DDR_RESOLUTION >
	int SizeDifference = 0, SizeModify = 0;
	//unsigned char IsFileSizeMul_64 = 1;		//Flag to chech whether 0s need to be append.
	unsigned char IsFileSizeMul_4096 = 1;		//Flag to chech whether 0s need to be append.
	FILE *rdBinFile;
	*numBytesWrSuccess = 0;
	unsigned char dummyBuf = '\0';
	/* Check file existance */
	if(!buf)
	{	
#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "ERROR : File does not Exist!" << endl;
		SppuUsbDllDebug.close();
#endif
		return -1;
	}

	/* Check for valid data to program */
	if((lNumBytes == 0))
	{
#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "STATUS: Request of: " << lNumBytes << " byte transfer!" << endl;
		SppuUsbDllDebug.close();
#endif
		
		//__HP__2; Adding support : if File Size is not multiple of 64 bytes then append 0s to make it multiple of 64 bytes.
		if((SizeDifference = (lNumBytes % FPGA_DDR_RESOLUTION)) != 0)
		{
			IsFileSizeMul_4096 = 0;								//Flag update;
			SizeModify = (FPGA_DDR_RESOLUTION - SizeDifference);
			lNumBytes += SizeModify;
		}
	}
	
	int rcount = 1;
	DWORD numByToWr = lNumBytes;
	unsigned char wDevBuf[MAX_NUM_BYTES_DDR_ONE_TIME + 1] = {'\0'};	

	DWORD outerLpCounter = 0;

	time_t seconds_begin, seconds_end, seconds;
	seconds_begin = time (NULL);

	while(numByToWr)
	{
		if(numByToWr > MAX_NUM_BYTES_DDR_ONE_TIME)
			numByToWr = MAX_NUM_BYTES_DDR_ONE_TIME;

		rcount = numByToWr;
		memcpy(wDevBuf, buf, rcount);
		/*rcount = fread(wDevBuf, 1, numByToWr, rdBinFile);
		if(rcount < 0)
		{
			#if DEBUG
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug << "ERROR : Unable to read from File! API Returned = " << rcount << endl;
			SppuUsbDllDebug.close();
			#endif
			break;
		}
		else
		{*/
			
			memset((wDevBuf + rcount), '\0', (MAX_NUM_BYTES_DDR_ONE_TIME - rcount));
			//Handling of data when it is not a multiple of 64 bytes.
			if((numByToWr <= FPGA_DDR_RESOLUTION) && (!IsFileSizeMul_4096))
				rcount += SizeModify;
		/*}*/

		outerLpCounter++;		//Increment counter only when data is available

		if(S_OK != __WrToDdr(DeviceTypes::LFT_SPPU_DEV_DDR, wDevBuf, rcount, &numByWrSuccess))
		{
			#if DEBUG
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug << "ERROR : Write to DDR Failure" << endl;
			SppuUsbDllDebug.close();
			#endif
			break;
		}
//		numByWrSuccess -= LFT_SPPU_SLAVE_FIFO_HEADER_SIZE;
		(*numBytesWrSuccess) += numByWrSuccess;
		numByToWr = lNumBytes - (*numBytesWrSuccess);
		if(lNumBytes == (*numBytesWrSuccess))
		{
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug.close();
			break;
		}
	}
	
	seconds_end = time (NULL);
	seconds = (seconds_end - seconds_begin);
	if(0 == seconds)
		seconds++;
	#if DEBUG
	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
	SppuUsbDllDebug << std::dec << "PERFORMANCE : DDR Write (FILE) : " << endl;
	SppuUsbDllDebug << "\t" << *numBytesWrSuccess << " Bytes in " << seconds << " Seconds; ";
	SppuUsbDllDebug << "\t" << (*numBytesWrSuccess / seconds) << " Bytes/Sec; " ;
	SppuUsbDllDebug << "\t" << ((*numBytesWrSuccess / seconds) >> 10) << " (KBps); ";
	SppuUsbDllDebug << "\t" << ((((*numBytesWrSuccess / seconds) >> 10)) >> 10) << " (MBps); " << endl;
	SppuUsbDllDebug << "STATUS: In Outer loop : " << outerLpCounter << " times" << endl;
	SppuUsbDllDebug.close();

	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
	SppuUsbDllDebug << "STATUS: Wrote in DDR : " << *numBytesWrSuccess << " Bytes, at address : "<< faddr << endl;
	SppuUsbDllDebug.close();
#endif

	return S_OK;
}

#pragma endregion WriteToDDR


#pragma region ReadFromDDR

HRESULT UsbApis::c_UsbApis::__RdFrDdr(unsigned char *buf, DWORD bufSize, DWORD *numBytesRdSuccess)
{
	BOOL ret = S_FALSE;
	LONG length = 0;
	DWORD lBufSize = bufSize;
	DWORD numByRdSuccess = 0;

	//DWORD address  = FPGA_DDR_ACCESS_ADDR;
	DWORD address  = m_nBulkStreamType;

#if 0
#if DEBUG_ERROR
	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
	SppuUsbDllDebug << "INFO: address __RdFrDdr() m_nBulkStreamType = " << std::hex << address << std::dec << endl;
	SppuUsbDllDebug.close();
#endif
#endif

	
	unsigned char buffer[LFT_SPPU_SLAVE_FIFO_XFER_BUF_SIZE + LFT_SPPU_SLAVE_FIFO_HEADER_SIZE] = {'\0'};
	unsigned char reqBuffer[MAX_NUM_BYTES_DDR_REG_ACCESS + 1] = {'\0'};

	*(reqBuffer + 0) = *(lftSppuPacketFormatSend + 0);
	*(reqBuffer + 1) = *(lftSppuPacketFormatSend + 1);

	*(reqBuffer + 4) = *(lftSppuPacketFormatSend + 4);
	*(reqBuffer + 5) = 0x02;							//Read command
	*(reqBuffer + 6) = *(lftSppuPacketFormatSend + 6);
	*(reqBuffer + 7) = *(lftSppuPacketFormatSend + 7);

	/*
	*(reqBuffer + 8) = ((FPGA_DDR_ACCESS_ADDR & 0xFF000000) >> 24);
	*(reqBuffer + 9) = ((FPGA_DDR_ACCESS_ADDR & 0x00FF0000) >> 16);
	*(reqBuffer + 10) = ((FPGA_DDR_ACCESS_ADDR & 0x0000FF00) >> 8);
	*(reqBuffer + 11) = (FPGA_DDR_ACCESS_ADDR & 0x000000FF);
	*/
	*(reqBuffer + 8) = ((address & 0xFF000000) >> 24);
	*(reqBuffer + 9) = ((address & 0x00FF0000) >> 16);
	*(reqBuffer + 10) = ((address & 0x0000FF00) >> 8);
	*(reqBuffer + 11) = (address & 0x000000FF);

	*(reqBuffer + 12) = ((DO_NOT_CARE & 0xFF000000) >> 24);
	*(reqBuffer + 13) = ((DO_NOT_CARE & 0x00FF0000) >> 16);
	*(reqBuffer + 14) = ((DO_NOT_CARE & 0x0000FF00) >> 8);
	*(reqBuffer + 15) = (DO_NOT_CARE & 0x000000FF);
	
	//Loop to read data from Slave FIFO interface
	while(lBufSize)
	{
		if(lBufSize > LFT_SPPU_SLAVE_FIFO_XFER_BUF_SIZE)
			lBufSize = LFT_SPPU_SLAVE_FIFO_XFER_BUF_SIZE;

		length = (lBufSize + LFT_SPPU_SLAVE_FIFO_HEADER_SIZE);
		*(reqBuffer + 2) = ((length & 0xFF00) >> 8);
		*(reqBuffer + 3) = (length & 0xFF);

		//Request for transfer of Data (length field th request packet is size of data to be read)
		ret = __WrRegToDdr(reqBuffer, MAX_NUM_BYTES_DDR_REG_ACCESS);
		if(ret == S_OK)
		{
#if 0
			#if STATUS_DEBUG
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug << "SUCCESS: SENT INFO : Read Bulk Data! Waiting for response..." << endl;
			SppuUsbDllDebug.close();
			#endif
#endif
			//In Bulk In End point exists
			if(usbEp.fpgaBulkIn)
			{
				if(usbEp.fpgaBulkIn->XferData(buffer, length))
				{
					if((length - LFT_SPPU_SLAVE_FIFO_HEADER_SIZE) > 0)
					{
						//Check for valid responce packet
						if((*(buffer + 0)) == (0xAA) && \
							(*(buffer + 1)) == (0x88))
						{
							//Check for status
							if((*(buffer + 11)) == 0x00)
							{
								if(NULL == memcpy((buf + numByRdSuccess), (buffer + LFT_SPPU_SLAVE_FIFO_HEADER_SIZE),\
										(length - LFT_SPPU_SLAVE_FIFO_HEADER_SIZE)))
								{
									#if DEBUG_ERROR
									SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
									SppuUsbDllDebug << "ERROR: MemCopy FAILURE!" << endl;
									SppuUsbDllDebug.close();
									#endif
									goto OUT_ERR;
								}
								numByRdSuccess += (length - LFT_SPPU_SLAVE_FIFO_HEADER_SIZE);
								lBufSize = bufSize - numByRdSuccess;
								if(numByRdSuccess == bufSize)
								{
									//Everything good proceed...
									(*numBytesRdSuccess) = numByRdSuccess;
									break;	//successfully out of this function.
								}
							}
							else
							{	//Invalid Status
								#if DEBUG_ERROR
								SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
								SppuUsbDllDebug << "ERROR : Invalid response status! = " << *(lftSppuPacketFormatRecv + 11) << endl;
								SppuUsbDllDebug.close();
								#endif
								goto OUT_ERR;
							}
						}
						else
						{	//Invalid Magic Packet
							#if DEBUG_ERROR
							SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
							SppuUsbDllDebug << "ERROR : Invalid Response packet! = 0x" << std::hex << 
								(*(buffer + 0)) << (*(buffer + 1)) << std::dec << endl;
							SppuUsbDllDebug.close();
							#endif
							goto OUT_ERR;
						}
					}
					else
					{
						//Invalid length
						#if DEBUG_ERROR
						SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
						SppuUsbDllDebug << "ERROR: Read Zero Bytes from fpgaBulkIn EndPoint!" << endl;
						SppuUsbDllDebug.close();
						#endif
						goto OUT_ERR;
					}
				}
				else
				{
					//XFER failure
					#if DEBUG_ERROR
					SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
					SppuUsbDllDebug << "ERROR: fpgaBulkIn->XferData failure" << endl;
					SppuUsbDllDebug.close();
					#endif
					goto OUT_ERR;
				}
			}
			else
			{
				//No Bulk-In End Ponit
				#if DEBUG_ERROR
				SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
				SppuUsbDllDebug << "ERROR: No BulkIn Endpoint found on Device" << endl;
				SppuUsbDllDebug.close();
				#endif
				goto OUT_ERR;
			}
		}
		else
		{
			//Fail to send request
			#if DEBUG_ERROR
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug << "ERROR : FAILUED to send INFO : Read Bulk Data." << endl;
			SppuUsbDllDebug.close();
			#endif
			goto OUT_ERR;
		}
	}
#if 0
	if(usbEp.fpgaBulkIn)
	{
		if(usbEp.fpgaBulkIn->XferData(buf, length))
		{
			if(length > 0)
			{
				(*numBytesRdSuccess) += length;
				#if DEBUG_STATUS
				SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
				SppuUsbDllDebug << "STATUS: Number of bytes READ from fpgaBulkIn EndPoint = 0x" << std::hex << length << std::dec << endl;
				SppuUsbDllDebug.close();
				#endif
			}
			else
			{
				#if DEBUG_ERROR
				SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
				SppuUsbDllDebug << "ERROR: Read Zero Bytes from fpgaBulkIn EndPoint!" << endl;
				SppuUsbDllDebug.close();
				#endif
			}
		}
		else
		{
			#if DEBUG_ERROR
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug << "ERROR: fpgaBulkIn->XferData failure" << endl;
			SppuUsbDllDebug.close();
			#endif
			return -1;
		}
	}
	else
	{
		#if DEBUG_ERROR
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "ERROR: No BulkIn Endpoint found on Device" << endl;
		SppuUsbDllDebug.close();
		#endif
		return -1;
	}
#endif
	return S_OK;
OUT_ERR:
	return -1;
}

HRESULT UsbApis::c_UsbApis::_RdFileFrDdr(char *fname, DWORD faddr, DWORD numBytes, DWORD *numBytesRdSuccess)
{
	HRESULT hRes = S_OK;
	DWORD lNumBytes = numBytes;
	DWORD numByRdSuccess = 0;
	DWORD laddr = faddr;
	FILE *wrBinFile;
	*numBytesRdSuccess = 0;

#if DEBUG
	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
	SppuUsbDllDebug << "STATUS: In _RdFileFrDdr()" << endl;
	SppuUsbDllDebug.close();
#endif


	if(lNumBytes == 0)
	{
#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "STATUS: Request of 0 byte transfer!" << endl;
		SppuUsbDllDebug.close();
#endif
		return 0;
	}

	/* Check file existance */
	if(!ifstream (fname))
	{
#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "ERROR : File does not Exist! (FIXING...)" << endl;
		SppuUsbDllDebug << "STATUS: Previous ERROR FIXED" << endl;
		SppuUsbDllDebug.close();
#endif
	}

	/* opening the file */
	if(!(wrBinFile = fopen(fname, "wb")))
	{
#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "Error : Can not Open File." << endl;
		SppuUsbDllDebug.close();
#endif
		return -1;
	}

	int wcount = 1;
	DWORD numByToRd = lNumBytes;
	unsigned char rDevBuf[MAX_NUM_BYTES_DDR_ONE_TIME + 1] = {0};

	DWORD outerLpCounter = 0;

	time_t seconds_begin, seconds_end, seconds;
	seconds_begin = time (NULL);

	while(numByToRd)
	{
		if(numByToRd > MAX_NUM_BYTES_DDR_ONE_TIME)
			numByToRd = MAX_NUM_BYTES_DDR_ONE_TIME;

		if(S_OK != __RdFrDdr(rDevBuf, numByToRd, &numByRdSuccess))
		{
			#if DEBUG_ERROR
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug << "ERROR : Read from DDR Failure" << endl;
			SppuUsbDllDebug.close();
			#endif
			break;
		}
		else
		{
			wcount = fwrite(rDevBuf, 1, numByRdSuccess, wrBinFile);
			if(wcount < 1)
			{
				#if DEBUG_ERROR
				SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
				SppuUsbDllDebug << "ERROR: Unable to Write to File! API Returned = " << wcount << endl;
				SppuUsbDllDebug.close();
				#endif
				break;
			}
		}
		outerLpCounter++;
		(*numBytesRdSuccess) += numByRdSuccess;
		numByToRd = lNumBytes - (*numBytesRdSuccess);
		if(numBytes == (*numBytesRdSuccess))
		{
			break;
		}
	}

	seconds_end = time (NULL);
	seconds = (seconds_end - seconds_begin);
	if(0 == seconds)
		seconds++;
	#if DEBUG
	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
	SppuUsbDllDebug << std::dec << "PERFORMANCE : DDR Read (FILE) : " << endl;
	SppuUsbDllDebug << "\t" << *numBytesRdSuccess << " Bytes in " << seconds << " Seconds; ";
	SppuUsbDllDebug << "\t" << (*numBytesRdSuccess / seconds) << " Bytes/Sec; " ;
	SppuUsbDllDebug << "\t" << ((*numBytesRdSuccess / seconds) >> 10) << " (KBps); ";
	SppuUsbDllDebug << "\t" << ((((*numBytesRdSuccess / seconds) >> 10)) >> 10) << " (MBps); " << endl;
	SppuUsbDllDebug << "STATUS: In Outer loop : " << outerLpCounter << " times" << endl;
	SppuUsbDllDebug.close();


	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
	SppuUsbDllDebug << "STATUS: Read from DDR : " << *numBytesRdSuccess << " Bytes, from address : "<< faddr << endl;
	SppuUsbDllDebug.close();
#endif
	fclose(wrBinFile);
	return S_OK;
	return S_OK;
}


HRESULT UsbApis::c_UsbApis::_RdBufFrDdr(char *buf, DWORD faddr, DWORD numBytes, DWORD *numBytesRdSuccess)
{
	HRESULT hRes = S_OK;
	DWORD lNumBytes = numBytes;
	DWORD numByRdSuccess = 0;
	DWORD laddr = faddr;
	FILE *wrBinFile;
	*numBytesRdSuccess = 0;

	if(lNumBytes == 0)
	{
#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "STATUS: Request of 0 byte transfer!" << endl;
		SppuUsbDllDebug.close();
#endif
		return 0;
	}

	/* Check valid buffer */
	if(!buf)
	{
#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "ERROR : Invalid buffer! (NULL)" << endl;
		SppuUsbDllDebug.close();
#endif
		return -1;
	}


	int wcount = 1;
	DWORD numByToRd = lNumBytes;
	unsigned char rDevBuf[MAX_NUM_BYTES_DDR_ONE_TIME + 1] = {0};

	DWORD outerLpCounter = 0;

	time_t seconds_begin, seconds_end, seconds;
	seconds_begin = time (NULL);

	while(numByToRd)
	{
		if(numByToRd > MAX_NUM_BYTES_DDR_ONE_TIME)
			numByToRd = MAX_NUM_BYTES_DDR_ONE_TIME;

		if(S_OK != __RdFrDdr(rDevBuf, numByToRd, &numByRdSuccess))
		{
			#if DEBUG_ERROR
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug << "ERROR : Read from DDR Failure" << endl;
			SppuUsbDllDebug.close();
			#endif
			break;
		}
		else
		{
			memcpy(buf, rDevBuf, numByRdSuccess);
			{
				#if DEBUG
				SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
				SppuUsbDllDebug << "ERROR : Invalid buffer! (NULL)" << endl;
				SppuUsbDllDebug.close();
				#endif
			}

		/*	wcount = fwrite(rDevBuf, 1, numByRdSuccess, wrBinFile);
			if(wcount < 1)
			{
				#if DEBUG_ERROR
				SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
				SppuUsbDllDebug << "ERROR: Unable to Write to File! API Returned = " << wcount << endl;
				SppuUsbDllDebug.close();
				#endif
				break;
			}*/
		}
		outerLpCounter++;
		(*numBytesRdSuccess) += numByRdSuccess;
		numByToRd = lNumBytes - (*numBytesRdSuccess);
		if(numBytes == (*numBytesRdSuccess))
		{
			break;
		}
	}

	seconds_end = time (NULL);
	seconds = (seconds_end - seconds_begin);
	if(0 == seconds)
		seconds++;
	#if DEBUG
	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
	SppuUsbDllDebug << std::dec << "PERFORMANCE : DDR Read (Buffer) : " << endl;
	SppuUsbDllDebug << "\t" << *numBytesRdSuccess << " Bytes in " << seconds << " Seconds; ";
	SppuUsbDllDebug << "\t" << (*numBytesRdSuccess / seconds) << " Bytes/Sec; " ;
	SppuUsbDllDebug << "\t" << ((*numBytesRdSuccess / seconds) >> 10) << " (KBps); ";
	SppuUsbDllDebug << "\t" << ((((*numBytesRdSuccess / seconds) >> 10)) >> 10) << " (MBps); " << endl;
	SppuUsbDllDebug << "STATUS: In Outer loop : " << outerLpCounter << " times" << endl;
	SppuUsbDllDebug.close();


	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
	SppuUsbDllDebug << "STATUS: Read from DDR : " << *numBytesRdSuccess << " Bytes, from address : "<< faddr << endl;
	SppuUsbDllDebug.close();
#endif
	
	return S_OK;
	return S_OK;
}

#pragma endregion ReadFromDDR 


#if 1			//New Read in sync with latest write for any num of bytes requested
/* This function is to read from SD Card to a File */
HRESULT UsbApis::c_UsbApis::RdFileFromSdCard0(DeviceTypes devType, char *fname, DWORD faddr, DWORD numBytes, DWORD *numBytesRdSuccess)
{
	*numBytesRdSuccess = 0;

	if(OpenDevice())
		return -1;

	if(devType == UsbApis::DEVICE_TYPES::LFT_SPPU_DEV_FX3_SDCARD)
	{
		#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "STATUS: Got request for Reading Sd Card" << devType << endl;
		SppuUsbDllDebug.close();
		#endif
	}
	else if(devType == UsbApis::DEVICE_TYPES::LFT_SPPU_DEV_DDR)
	{
		#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "STATUS: Got request for Reading DDR : " << devType << endl;
		SppuUsbDllDebug.close();
		#endif

		if(S_OK == _RdFileFrDdr(fname, faddr, numBytes, numBytesRdSuccess))
			return S_OK;
		else
			return -1;
	}
	else
	{
		#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "ERROR : Unknown device selected for SD Card Read = " << devType << endl;
		SppuUsbDllDebug.close();
		#endif
		return -1;
	}

	HRESULT hRes = S_OK;
	
	DWORD lNumBytes = numBytes;
	DWORD lNumSdBlocks, lNumDmaBlocks, laddr = faddr;

	if(lNumBytes == 0)
	{
#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
		SppuUsbDllDebug << "STATUS: Request of 0 byte transfer!" << endl;
		SppuUsbDllDebug.close();
#endif
		return 0;
	}
	FILE *wrBinFile;
	/* Check file existance */
	if(!ifstream (fname))
	{
#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
		SppuUsbDllDebug << "ERROR : File does not Exist! (FIXING...)" << endl;
		SppuUsbDllDebug << "STATUS: Created New File. (FIXED)" << endl;
		SppuUsbDllDebug.close();
#endif
	}

	/* opening the file */
	if(!(wrBinFile = fopen(fname, "wb")))
	{
#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
		SppuUsbDllDebug << "Error : Can not Open File." << endl;
		SppuUsbDllDebug.close();
#endif
		return -1;
	}

	DWORD wcount = 1, numByToRd = lNumBytes, numByRdSuccess = 0;
	unsigned char rDevBuf[DMA_RD_SIZE + 1] = {'\0'};
	LONG length = DMA_RD_SIZE;


	DWORD numSdBlksToRd = 0/*lNumSdBlocks*/, numSdBlksToRecv = 0;
	DWORD numDmaBlksToRd, numDmaBlksRdSuccess = 0, totDmaBlksRdSuccess = 0;
	ULONG lFilePageSize = DMA_RD_SIZE;		//Modify : if we give this Facility to user as argument in this API to give file access size.
	int lv;
	DWORD outerLpCounter = 0;

	laddr = faddr / SD_CARD_PAGE_SIZE;
	if((faddr % SD_CARD_PAGE_SIZE) != 0)
		laddr++;
	
	if((laddr < 0) || (laddr > 0xECE000))
	{
		#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "ERROR : Out of range address provided for read access. " << endl;
		SppuUsbDllDebug.close();
		#endif
		fclose(wrBinFile);
		return -1;
	}//TODO: address range checkinh for modified data as well

	time_t seconds_begin, seconds_end, seconds;
	seconds_begin = time (NULL);

	while(numByToRd)
	{
		if(numByToRd > MAX_NUM_BYTES_SD_CARD_ONE_TIME)
			numByToRd = MAX_NUM_BYTES_SD_CARD_ONE_TIME;

		lNumSdBlocks = (numByToRd / SD_CARD_PAGE_SIZE);
		if((numByToRd % SD_CARD_PAGE_SIZE) != 0)
			lNumSdBlocks++;
		numSdBlksToRd = lNumSdBlocks;
		 
		lNumDmaBlocks = (numSdBlksToRd / DMA_SD_CARD_WR_RELATION);
		if((numSdBlksToRd % DMA_SD_CARD_WR_RELATION) != 0)
			lNumDmaBlocks++;
		numDmaBlksToRd = lNumDmaBlocks;

		WrEP0(devType, SD_CARD_READ, laddr, numSdBlksToRd);
		
		while(numDmaBlksToRd)
		{
			if(usbEp.sdCardBulkIn)
			{
				length = LESS(numByToRd, DMA_RD_SIZE);
				if(length <= SD_CARD_PAGE_SIZE)
					numSdBlksToRecv = 1;
				else if(length <= DMA_RD_SIZE)
				{
					numSdBlksToRecv = (length / SD_CARD_PAGE_SIZE);
					if((length % SD_CARD_PAGE_SIZE) != 0)
						numSdBlksToRecv++;
				}
				length = (numSdBlksToRecv * SD_CARD_PAGE_SIZE);

				if(usbEp.sdCardBulkIn->XferData(rDevBuf, length))
				{
					if(length > 0)
					{
						wcount = fwrite(rDevBuf, 1, LESS(numByToRd, length), wrBinFile);
						if(wcount == 0)
						{
							#if DEBUG
							SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
							//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
							SppuUsbDllDebug << "ERROR: Unable to Write to File!" << endl;
							SppuUsbDllDebug.close();
							#endif
							break;
						}
						numByRdSuccess += LESS(numByToRd, length);
						numDmaBlksToRd--;
						totDmaBlksRdSuccess++;
						numByToRd -= LESS(numByRdSuccess, length);
					}
					else
					{
						#if DEBUG
						SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
						//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
						SppuUsbDllDebug << "ERROR: Read Zero Bytes from SD Card" << endl;
						SppuUsbDllDebug << "Wrote : " << numByRdSuccess << "Bytes" << endl;
						SppuUsbDllDebug.close();
						#endif
						break;
					}
				}
				else
				{
					#if DEBUG
					SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
					//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
					SppuUsbDllDebug << "ERROR: BulkInEndPt->XferData failure" << endl;
					SppuUsbDllDebug << "read : " << numByRdSuccess << "Bytes" << endl;
					SppuUsbDllDebug.close();
					#endif
					fclose(wrBinFile);
					return -1;
				}
			}
			else
			{
				#if DEBUG
				SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
				//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
				SppuUsbDllDebug << "ERROR: No BulkIn Endpoint found on Device" << endl;
				SppuUsbDllDebug.close();
				#endif
				fclose(wrBinFile);
				return -1;
			}
		}
		outerLpCounter++;
		numByToRd = numBytes - numByRdSuccess;
		if(numBytes == numByRdSuccess)
		{
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug << "STATUS: Num of bytes success = " << numByRdSuccess << endl;
			SppuUsbDllDebug.close();
			break;
		}
		laddr += numSdBlksToRd;
	}

	seconds_end = time (NULL);
	seconds = (seconds_end - seconds_begin);
	if(0 == seconds)
		seconds++;
	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
	SppuUsbDllDebug << std::dec << "PERFORMANCE : SD_card Read (FILE) : " << endl;
	SppuUsbDllDebug << "\t" << numByRdSuccess << " Bytes in " << seconds << " Seconds; ";
	SppuUsbDllDebug << "\t" << (numByRdSuccess / seconds) << " Bytes/Sec; " ;
	SppuUsbDllDebug << "\t" << ((numByRdSuccess / seconds) >> 10) << " (KBps); ";
	SppuUsbDllDebug << "\t" << ((((numByRdSuccess / seconds) >> 10)) >> 10) << " (MBps); " << endl;
//	SppuUsbDllDebug << "STATUS: In Inner loop : " << totDmaBlksRdSuccess << " times" << endl;
//	SppuUsbDllDebug << "STATUS: In Outer loop : " << outerLpCounter << " times" << endl;
	SppuUsbDllDebug.close();

	*numBytesRdSuccess = numByRdSuccess;			//modifying value and not address

#if DEBUG
	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
	SppuUsbDllDebug << "STATUS: Read : " << numByRdSuccess << " Bytes, from address : "<< faddr << endl;
	SppuUsbDllDebug.close();
#endif
	fclose(wrBinFile);
	return S_OK;
}
#endif


#if 1
//__HP__9 : 5 Nov 2015
// Only multiple of 4096 shall be written on SD Card. Makng compatible with DDR functionality.
HRESULT UsbApis::c_UsbApis::WrFileToSdCard0(DeviceTypes devType, char *fname, DWORD faddr, DWORD numBytes, DWORD *numBytesWrSuccess)
{
	int ret = S_OK;
	*numBytesWrSuccess = 0;
	if(OpenDevice())
		return -1;

	int SizeDifference = 0, SizeModify = 0;
	unsigned char IsFileSizeMul_4096 = 1;		//Flag to chech whether 0s need to be append.

	if(devType == UsbApis::DEVICE_TYPES::LFT_SPPU_DEV_FX3_SDCARD)
	{
		#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
		SppuUsbDllDebug << "STATUS: Got request for Writing Sd Card" << devType << endl;
		SppuUsbDllDebug.close();
		#endif
	}
	else if(devType == UsbApis::DEVICE_TYPES::LFT_SPPU_DEV_DDR)
	{
		#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "STATUS: Got request for Writing DDR" << devType << endl;
		SppuUsbDllDebug.close();
		#endif

		//Sent command to set infinite transfer size
//		WrEP0(devType, SD_CARD_WRITE, DO_NOT_CARE, DO_NOT_CARE);

		if(S_OK == _WrFileToDdr(fname, faddr, numBytes, numBytesWrSuccess))
			return S_OK;
		else
			return -1;
	}
	else
	{
		#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
		SppuUsbDllDebug << "ERROR : Unknown device selected for SD Card Write = " << devType << endl;
		SppuUsbDllDebug.close();
		#endif
		return -1;
	}

	HRESULT hRes = S_OK;
	DWORD lNumBytes = numBytes;
	DWORD lNumSdBlocks, lNumDmaBlocks;
	DWORD laddr = faddr;
	FILE *rdBinFile;

	/* Check file existance */
	if(!ifstream (fname))
	{	
#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "ERROR : File does not Exist!" << endl;
		SppuUsbDllDebug.close();
#endif
		return -1;
	}

	/* opening the file */
	if(!(rdBinFile = fopen(fname, "rb")))
	{
#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "ERROR : Can not Open File." << endl;
		SppuUsbDllDebug.close();
#endif
		return -1;
	}

	/* Get file size */
	fseek(rdBinFile, 0, SEEK_END);
    DWORD dwFileSize = ftell(rdBinFile);
    fseek(rdBinFile, 0, SEEK_SET);

	if((lNumBytes == 0) || (lNumBytes > dwFileSize))
	{
#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "STATUS: Request of: " << lNumBytes << " byte transfer! Writing File Size: " << dwFileSize << endl;
		SppuUsbDllDebug.close();
#endif
		lNumBytes = dwFileSize;
	}

	//__HP__9
	if((SizeDifference = (lNumBytes % FPGA_DDR_RESOLUTION)) != 0)
	{
		IsFileSizeMul_4096 = 0;								//Flag update;
		SizeModify = (FPGA_DDR_RESOLUTION - SizeDifference);
		lNumBytes += SizeModify;
	}
	
	int rcount = 1;
	DWORD numByToWr = lNumBytes, numByWrSuccess = 0;
	unsigned char wDevBuf[DMA_WR_SIZE + 1] = {'\0'};
	LONG length = DMA_WR_SIZE;

	DWORD numSdBlksToWr = 0, numSdBlksWrSuccess = 0, totSdBlkWrSuccess = 0, numSdBlksToSend = 0;
	DWORD numDmaBlksToWr = 0, numDmaBlksWrSuccess = 0, totDmaBlksSuccess = 0;
	//ULONG lFilePageSize = DMA_WR_SIZE;		//Modify : if we give this Facility to user as argument in this API to give file access size.
	int lv, tmpBufMod;
	DWORD outerLpCounter = 0;
	

	laddr = faddr / SD_CARD_PAGE_SIZE;
	if((faddr % SD_CARD_PAGE_SIZE) != 0)
		laddr++;
	
	if((laddr < 0) || (laddr > 0xECE000))
	{
		#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "ERROR : Out of range address provided for write access. " << endl;
		SppuUsbDllDebug.close();
		#endif
		fclose(rdBinFile);
		return -1;
	}//TODO: address range checkinh for modified data as well

	time_t seconds_begin, seconds_end, seconds;
	seconds_begin = time (NULL);

	while(numByToWr)
	{
		if(numByToWr > MAX_NUM_BYTES_SD_CARD_ONE_TIME)
			numByToWr = MAX_NUM_BYTES_SD_CARD_ONE_TIME;

		lNumSdBlocks = (numByToWr / SD_CARD_PAGE_SIZE);
		if((numByToWr % SD_CARD_PAGE_SIZE) != 0)
			lNumSdBlocks++;
		numSdBlksToWr = lNumSdBlocks;

		lNumDmaBlocks = (numSdBlksToWr / DMA_SD_CARD_WR_RELATION);
		if((numSdBlksToWr % DMA_SD_CARD_WR_RELATION) != 0)
			lNumDmaBlocks++;
		numDmaBlksToWr = lNumDmaBlocks;

		WrEP0(devType, SD_CARD_WRITE, laddr, numSdBlksToWr);

		while(numDmaBlksToWr)
		{
			rcount = fread(wDevBuf, 1, LESS(numByToWr, DMA_WR_SIZE), rdBinFile);
			if(rcount < 0)
			{
				#if DEBUG
				SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
				//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << " ]" << endl;
				SppuUsbDllDebug << "ERROR: Unable to read from File!" << endl;
				SppuUsbDllDebug.close();
				#endif
				break;
			}
#if 0
			else if(rcount < SD_CARD_PAGE_SIZE)
			{
				memset(wDevBuf + rcount, '\0', (DMA_WR_SIZE - rcount));
				numSdBlksToSend = 1;
			}
#endif
			else if(rcount <= DMA_WR_SIZE)
			{
				memset(wDevBuf + rcount, '\0', (DMA_WR_SIZE - rcount));
				numSdBlksToSend = (rcount / SD_CARD_PAGE_SIZE);
				if((rcount % SD_CARD_PAGE_SIZE) != 0)
					numSdBlksToSend++;

				if(numSdBlksToSend < 8)
					numSdBlksToSend = 8;

			}
			if(usbEp.sdCardBulkOut)
			{
				length = (numSdBlksToSend * SD_CARD_PAGE_SIZE);
				if(usbEp.sdCardBulkOut->XferData(wDevBuf, length))
				{
					if(length > 0)
					{
						numByWrSuccess += LESS(numByToWr, length);
						numDmaBlksToWr--;
						totDmaBlksSuccess++;
						numByToWr -= LESS(numByWrSuccess, length);
					}
					else
					{
						#if DEBUG
						SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
						//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
						SppuUsbDllDebug << "Wrote : " << numByWrSuccess << "Bytes" << endl;
						SppuUsbDllDebug.close();
						#endif
						break;
					}
				}
				else
				{
					#if DEBUG
					SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
					//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
					SppuUsbDllDebug << "ERROR: BulkOutEndPt->XferData failure" << endl;
					SppuUsbDllDebug << "Wrote : " << numByWrSuccess << "Bytes" << endl;
					SppuUsbDllDebug.close();
					#endif
					fclose(rdBinFile);
					return -1;				//Error while reading from BulkOut End Point
				}
				
			}
			else
			{
				#if DEBUG
				SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
				//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
				SppuUsbDllDebug << "ERROR: No BulkOut Endpoint found on Device" << endl;
				SppuUsbDllDebug.close();
				#endif
				fclose(rdBinFile);
				return -1;
			}
		}
		outerLpCounter++;
		numByToWr = lNumBytes - numByWrSuccess;
		if(lNumBytes == numByWrSuccess)
		{
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug << "STATUS: Num of bytes success = " << numByWrSuccess << endl;
			SppuUsbDllDebug.close();
			break;
		}
		laddr += numSdBlksToWr;
	}
	seconds_end = time (NULL);
	seconds = (seconds_end - seconds_begin);
	if(0 == seconds)
		seconds++;
	#if DEBUG
	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
	SppuUsbDllDebug << std::dec << "PERFORMANCE : SD_card Write (FILE) : " << endl;
	SppuUsbDllDebug << "\t" << numByWrSuccess << " Bytes in " << seconds << " Seconds; ";
	SppuUsbDllDebug << "\t" << (numByWrSuccess / seconds) << " Bytes/Sec; " ;
	SppuUsbDllDebug << "\t" << ((numByWrSuccess / seconds) >> 10) << " (KBps); ";
	SppuUsbDllDebug << "\t" << ((((numByWrSuccess / seconds) >> 10)) >> 10) << " (MBps); " << endl;
//	SppuUsbDllDebug << "STATUS: In Inner loop : " << totDmaBlksSuccess << " times" << endl;
//	SppuUsbDllDebug << "STATUS: In Outer loop : " << outerLpCounter << " times" << endl;
	SppuUsbDllDebug.close();

	*numBytesWrSuccess = numByWrSuccess;			//modifying value and not address



	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
	//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
	SppuUsbDllDebug << "STATUS: Wrote : " << numByWrSuccess << " Bytes, at address : "<< faddr << endl;
	SppuUsbDllDebug.close();
#endif
	fclose(rdBinFile);
	return ret;
}

#else		
//olser. Tested. Writes data to SD Card.
// This function is to write to SD Card from a File
HRESULT UsbApis::c_UsbApis::WrFileToSdCard0(DeviceTypes devType, char *fname, DWORD faddr, DWORD numBytes, DWORD *numBytesWrSuccess)
{
	int ret = S_OK;
	*numBytesWrSuccess = 0;
	if(OpenDevice())
		return -1;

	if(devType == UsbApis::DEVICE_TYPES::LFT_SPPU_DEV_FX3_SDCARD)
	{
		#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
		SppuUsbDllDebug << "STATUS: Got request for Writing Sd Card" << devType << endl;
		SppuUsbDllDebug.close();
		#endif
	}
	else if(devType == UsbApis::DEVICE_TYPES::LFT_SPPU_DEV_DDR)
	{
		#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "STATUS: Got request for Writing DDR" << devType << endl;
		SppuUsbDllDebug.close();
		#endif

		//Sent command to set infinite transfer size
//		WrEP0(devType, SD_CARD_WRITE, DO_NOT_CARE, DO_NOT_CARE);

		if(S_OK == _WrFileToDdr(fname, faddr, numBytes, numBytesWrSuccess))
			return S_OK;
		else
			return -1;
	}
	else
	{
		#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
		SppuUsbDllDebug << "ERROR : Unknown device selected for SD Card Write = " << devType << endl;
		SppuUsbDllDebug.close();
		#endif
		return -1;
	}

	HRESULT hRes = S_OK;
	DWORD lNumBytes = numBytes;
	DWORD lNumSdBlocks, lNumDmaBlocks;
	DWORD laddr = faddr;
	FILE *rdBinFile;

	/* Check file existance */
	if(!ifstream (fname))
	{	
#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "ERROR : File does not Exist!" << endl;
		SppuUsbDllDebug.close();
#endif
		return -1;
	}

	/* opening the file */
	if(!(rdBinFile = fopen(fname, "rb")))
	{
#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "ERROR : Can not Open File." << endl;
		SppuUsbDllDebug.close();
#endif
		return -1;
	}

	/* Get file size */
	fseek(rdBinFile, 0, SEEK_END);
    DWORD dwFileSize = ftell(rdBinFile);
    fseek(rdBinFile, 0, SEEK_SET);

	if((lNumBytes == 0) || (lNumBytes > dwFileSize))
	{
#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "STATUS: Request of: " << lNumBytes << " byte transfer! Writing File Size: " << dwFileSize << endl;
		SppuUsbDllDebug.close();
#endif
		lNumBytes = dwFileSize;
	}
	
	int rcount = 1;
	DWORD numByToWr = lNumBytes, numByWrSuccess = 0;
	unsigned char wDevBuf[DMA_WR_SIZE + 1] = {'\0'};
	LONG length = DMA_WR_SIZE;

	DWORD numSdBlksToWr = 0, numSdBlksWrSuccess = 0, totSdBlkWrSuccess = 0, numSdBlksToSend = 0;
	DWORD numDmaBlksToWr = 0, numDmaBlksWrSuccess = 0, totDmaBlksSuccess = 0;
	//ULONG lFilePageSize = DMA_WR_SIZE;		//Modify : if we give this Facility to user as argument in this API to give file access size.
	int lv, tmpBufMod;
	DWORD outerLpCounter = 0;
	

	laddr = faddr / SD_CARD_PAGE_SIZE;
	if((faddr % SD_CARD_PAGE_SIZE) != 0)
		laddr++;
	
	if((laddr < 0) || (laddr > 0xECE000))
	{
		#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "ERROR : Out of range address provided for write access. " << endl;
		SppuUsbDllDebug.close();
		#endif
		fclose(rdBinFile);
		return -1;
	}//TODO: address range checkinh for modified data as well

	time_t seconds_begin, seconds_end, seconds;
	seconds_begin = time (NULL);

	while(numByToWr)
	{
		if(numByToWr > MAX_NUM_BYTES_SD_CARD_ONE_TIME)
			numByToWr = MAX_NUM_BYTES_SD_CARD_ONE_TIME;

		lNumSdBlocks = (numByToWr / SD_CARD_PAGE_SIZE);
		if((numByToWr % SD_CARD_PAGE_SIZE) != 0)
			lNumSdBlocks++;
		numSdBlksToWr = lNumSdBlocks;

		lNumDmaBlocks = (numSdBlksToWr / DMA_SD_CARD_WR_RELATION);
		if((numSdBlksToWr % DMA_SD_CARD_WR_RELATION) != 0)
			lNumDmaBlocks++;
		numDmaBlksToWr = lNumDmaBlocks;

		WrEP0(devType, SD_CARD_WRITE, laddr, numSdBlksToWr);

		while(numDmaBlksToWr)
		{
			rcount = fread(wDevBuf, 1, LESS(numByToWr, DMA_WR_SIZE), rdBinFile);
			if(rcount == 0)
			{
				#if DEBUG
				SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
				//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << " ]" << endl;
				SppuUsbDllDebug << "ERROR: Unable to read from File!" << endl;
				SppuUsbDllDebug.close();
				#endif
				break;
			}
			else if(rcount < SD_CARD_PAGE_SIZE)
			{
				memset(wDevBuf + rcount, '\0', (DMA_WR_SIZE - rcount));
				numSdBlksToSend = 1;
			}
			else if(rcount <= DMA_WR_SIZE)
			{
				memset(wDevBuf + rcount, '\0', (DMA_WR_SIZE - rcount));
				numSdBlksToSend = (rcount / SD_CARD_PAGE_SIZE);
				if((rcount % SD_CARD_PAGE_SIZE) != 0)
					numSdBlksToSend++;
			}
			if(usbEp.sdCardBulkOut)
			{
				length = (numSdBlksToSend * SD_CARD_PAGE_SIZE);
				if(usbEp.sdCardBulkOut->XferData(wDevBuf, length))
				{
					if(length > 0)
					{
						numByWrSuccess += LESS(numByToWr, length);
						numDmaBlksToWr--;
						totDmaBlksSuccess++;
						numByToWr -= LESS(numByWrSuccess, length);
					}
					else
					{
						#if DEBUG
						SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
						//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
						SppuUsbDllDebug << "Wrote : " << numByWrSuccess << "Bytes" << endl;
						SppuUsbDllDebug.close();
						#endif
						break;
					}
				}
				else
				{
					#if DEBUG
					SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
					//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
					SppuUsbDllDebug << "ERROR: BulkOutEndPt->XferData failure" << endl;
					SppuUsbDllDebug << "Wrote : " << numByWrSuccess << "Bytes" << endl;
					SppuUsbDllDebug.close();
					#endif
					fclose(rdBinFile);
					return -1;				//Error while reading from BulkOut End Point
				}
				
			}
			else
			{
				#if DEBUG
				SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
				//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
				SppuUsbDllDebug << "ERROR: No BulkOut Endpoint found on Device" << endl;
				SppuUsbDllDebug.close();
				#endif
				fclose(rdBinFile);
				return -1;
			}
		}
		outerLpCounter++;
		numByToWr = lNumBytes - numByWrSuccess;
		if(lNumBytes == numByWrSuccess)
		{
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug << "STATUS: Num of bytes success = " << numByWrSuccess << endl;
			SppuUsbDllDebug.close();
			break;
		}
		laddr += numSdBlksToWr;
	}
	seconds_end = time (NULL);
	seconds = (seconds_end - seconds_begin);
	if(0 == seconds)
		seconds++;
	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
	SppuUsbDllDebug << std::dec << "PERFORMANCE : SD_card Write (FILE) : " << endl;
	SppuUsbDllDebug << "\t" << numByWrSuccess << " Bytes in " << seconds << " Seconds; ";
	SppuUsbDllDebug << "\t" << (numByWrSuccess / seconds) << " Bytes/Sec; " ;
	SppuUsbDllDebug << "\t" << ((numByWrSuccess / seconds) >> 10) << " (KBps); ";
	SppuUsbDllDebug << "\t" << ((((numByWrSuccess / seconds) >> 10)) >> 10) << " (MBps); " << endl;
//	SppuUsbDllDebug << "STATUS: In Inner loop : " << totDmaBlksSuccess << " times" << endl;
//	SppuUsbDllDebug << "STATUS: In Outer loop : " << outerLpCounter << " times" << endl;
	SppuUsbDllDebug.close();

	*numBytesWrSuccess = numByWrSuccess;			//modifying value and not address


#if DEBUG
	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
	//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
	SppuUsbDllDebug << "STATUS: Wrote : " << numByWrSuccess << " Bytes, at address : "<< faddr << endl;
	SppuUsbDllDebug.close();
#endif
	fclose(rdBinFile);
	return ret;
}

#endif


#if 1
/* This function is to read from SD Card to memory */
HRESULT UsbApis::c_UsbApis::RdMemFromSdCard0(DeviceTypes devType, char *fMemBuf, DWORD faddr, DWORD numBytes, DWORD *numBytesRdSuccess)
{

	*numBytesRdSuccess = 0;
	if(OpenDevice())
		return -1;

	if(devType == UsbApis::DEVICE_TYPES::LFT_SPPU_DEV_FX3_SDCARD)
	{
		#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
		SppuUsbDllDebug << "STATUS: Got request for Reading Sd Card" << devType << endl;
		SppuUsbDllDebug.close();
		#endif
	}
	else if(devType == UsbApis::DEVICE_TYPES::LFT_SPPU_DEV_DDR)
	{
		#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "STATUS: Got request for Reading DDR" << devType << endl;
		SppuUsbDllDebug.close();
		#endif

		if(S_OK == _RdBufFrDdr(fMemBuf, faddr, numBytes, numBytesRdSuccess))
			return S_OK;
		else
			return -1;
	}
	else
	{
		#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
		SppuUsbDllDebug << "ERROR : Unknown device selected for SD Card read = " << devType << endl;
		SppuUsbDllDebug.close();
		#endif
		return -1;
	}

	HRESULT hRes = S_OK;	
	DWORD lNumBytes = numBytes;
	DWORD lNumSdBlocks, lNumDmaBlocks, laddr = faddr;

	if(fMemBuf == NULL)
	{
#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
		SppuUsbDllDebug << "ERROR : INVALID Memory Address of Buffer! = 0x0 (NULL)" << endl;
		SppuUsbDllDebug.close();
#endif	
		return -1;
	}

	if(lNumBytes == 0)
	{
#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
		SppuUsbDllDebug << "STATUS: Request of 0 byte transfer!" << endl;
		SppuUsbDllDebug.close();
#endif
		return 0;
	}
	
	int wcount = 1;
	DWORD numByToRd = lNumBytes, numByRdSuccess = 0;
	unsigned char rDevBuf[DMA_RD_SIZE + 1] = {0};
	LONG length = DMA_RD_SIZE;

	DWORD numSdBlksToRd = 0/*lNumSdBlocks*/, numSdBlksToRecv = 0;
	DWORD numDmaBlksToRd, numDmaBlksRdSuccess = 0, totDmaBlksRdSuccess = 0;
	ULONG lFilePageSize = DMA_RD_SIZE;		//Modify : if we give this Facility to user as argument in this API to give file access size.
	int lv, ret;
	DWORD outerLpCounter = 0;

	laddr = faddr / SD_CARD_PAGE_SIZE;
	if((faddr % SD_CARD_PAGE_SIZE) != 0)
		laddr++;
	
	if((laddr < 0) || (laddr > 0xECE000))
	{
		#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "ERROR: Out of range address provided for read access. " << endl;
		SppuUsbDllDebug.close();
		#endif
		return -1;
	}//TODO: address range checkinh for modified data as well

	time_t seconds_begin, seconds_end, seconds;
	seconds_begin = time (NULL);

	while(numByToRd)
	{
		if(numByToRd > MAX_NUM_BYTES_SD_CARD_ONE_TIME)
			numByToRd = MAX_NUM_BYTES_SD_CARD_ONE_TIME;

		lNumSdBlocks = (numByToRd / SD_CARD_PAGE_SIZE);
		if((numByToRd % SD_CARD_PAGE_SIZE) != 0)
			lNumSdBlocks++;
		numSdBlksToRd = lNumSdBlocks;
		 
		lNumDmaBlocks = (numSdBlksToRd / DMA_SD_CARD_WR_RELATION);
		if((numSdBlksToRd % DMA_SD_CARD_WR_RELATION) != 0)
			lNumDmaBlocks++;
		numDmaBlksToRd = lNumDmaBlocks;

		WrEP0(devType, SD_CARD_READ, laddr, numSdBlksToRd);
		
		while(numDmaBlksToRd)
		{		
			if(usbEp.sdCardBulkIn)
			{
				length = LESS(numByToRd, DMA_RD_SIZE);
				if(length <= SD_CARD_PAGE_SIZE)
					numSdBlksToRecv = 1;
				else if(length <= DMA_RD_SIZE)
				{
					numSdBlksToRecv = (length / SD_CARD_PAGE_SIZE);
					if((length % SD_CARD_PAGE_SIZE) != 0)
						numSdBlksToRecv++;
				}
				length = (numSdBlksToRecv * SD_CARD_PAGE_SIZE);

				if(usbEp.sdCardBulkIn->XferData(rDevBuf, length))
				{
					if(length > 0)
					{
						ret = memcpy_s((fMemBuf + numByRdSuccess), (DMA_RD_SIZE + 1), rDevBuf, LESS(numByToRd, length));
						if(0 == ret)
						{
							numByRdSuccess += LESS(numByToRd, length);
							numDmaBlksToRd--;
							totDmaBlksRdSuccess++;
							numByToRd -= LESS(numByRdSuccess, length);
						}
						else
						{
							#if DEBUG
							SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
							//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
							SppuUsbDllDebug << "ERROR: Unable to Write to File!" << endl;
							SppuUsbDllDebug.close();
							#endif
							break;
						}
					}
					else
					{
						#if DEBUG
						SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
						//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
						SppuUsbDllDebug << "ERROR: Read Zero Bytes from SD Card" << endl;
						SppuUsbDllDebug << "Wrote : " << numByRdSuccess << "Bytes" << endl;
						SppuUsbDllDebug.close();
						#endif
						break;
					}
				}
				else
				{
					#if DEBUG
					SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
					//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
					SppuUsbDllDebug << "ERROR: BulkInEndPt->XferData failure" << endl;
					SppuUsbDllDebug << "read : " << numByRdSuccess << "Bytes" << endl;
					SppuUsbDllDebug.close();
					#endif
					return -1;
				}
			}
			else
			{
				#if DEBUG
				SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
				//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
				SppuUsbDllDebug << "ERROR: No BulkIn Endpoint found on Device" << endl;
				SppuUsbDllDebug.close();
				#endif
				return -1;
			}
		}
		outerLpCounter++;
		numByToRd = numBytes - numByRdSuccess;
		if(numBytes == numByRdSuccess)
		{
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug << "STATUS: Num of bytes success = " << numByRdSuccess << endl;
			SppuUsbDllDebug.close();
			break;
		}
		laddr += numSdBlksToRd;
	}
	seconds_end = time (NULL);
	seconds = (seconds_end - seconds_begin);
	if(0 == seconds)
		seconds++;
	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
	SppuUsbDllDebug << std::dec << "PERFORMANCE : SD_card Read (FILE) : " << endl;
	SppuUsbDllDebug << "\t" << numByRdSuccess << " Bytes in " << seconds << " Seconds; ";
	SppuUsbDllDebug << "\t" << (numByRdSuccess / seconds) << " Bytes/Sec; " ;
	SppuUsbDllDebug << "\t" << ((numByRdSuccess / seconds) >> 10) << " (KBps); ";
	SppuUsbDllDebug << "\t" << ((((numByRdSuccess / seconds) >> 10)) >> 10) << " (MBps); " << endl;
//	SppuUsbDllDebug << "STATUS: In Inner loop : " << totDmaBlksRdSuccess << " times" << endl;
//	SppuUsbDllDebug << "STATUS: In Outer loop : " << outerLpCounter << " times" << endl;
	SppuUsbDllDebug.close();

	*numBytesRdSuccess = numByRdSuccess;			//modifying value and not address

	

#if DEBUG
	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
	//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
	SppuUsbDllDebug << "STATUS: Read : " << numByRdSuccess << " Bytes, from address : "<< faddr << endl;
	SppuUsbDllDebug.close();
#endif
	return S_OK;
}
#endif

#if 1	
/* This function is to write to SD Card from memory */ 
HRESULT UsbApis::c_UsbApis::WrMemToSdCard0(DeviceTypes devType, char *fMemBuf, DWORD faddr, DWORD numBytes, DWORD *numBytesWrSuccess)
{
	int ret = S_OK;
	*numBytesWrSuccess = 0;
	
	if(OpenDevice())
		return -1;

	if(devType == UsbApis::DEVICE_TYPES::LFT_SPPU_DEV_FX3_SDCARD)
	{
		#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
		SppuUsbDllDebug << "STATUS: Got request for Writing Sd Card" << devType << endl;
		SppuUsbDllDebug.close();
		#endif
	}
	else if(devType == UsbApis::DEVICE_TYPES::LFT_SPPU_DEV_DDR)
	{
		#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "STATUS: Got request for Writing DDR" << devType << endl;
		SppuUsbDllDebug.close();
		#endif

		if(S_OK == _WrBufToDdr(fMemBuf, faddr, numBytes, numBytesWrSuccess))
			return S_OK;
		else
			return -1;
	}
	else
	{
		#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
		SppuUsbDllDebug << "ERROR : Unknown device selected for SD Card Write = " << devType << endl;
		SppuUsbDllDebug.close();
		#endif
		return -1;
	}

	HRESULT hRes = S_OK;
	
	DWORD lNumBytes = numBytes;
	DWORD lNumSdBlocks, lNumDmaBlocks, laddr = faddr;

	if(fMemBuf == NULL)
	{
#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
		SppuUsbDllDebug << "ERROR : INVALID Memory Address of Buffer! = 0x0 (NULL)" << endl;
		SppuUsbDllDebug.close();
#endif	
		return -1;
	}

	if(lNumBytes == 0)
	{
#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
		SppuUsbDllDebug << "STATUS: Request of 0 byte transfer!" << endl;
		SppuUsbDllDebug.close();
#endif
		return 0;
	}

	int rcount = 1;
	DWORD numByToWr = lNumBytes, numByWrSuccess = 0;
	unsigned char wDevBuf[DMA_WR_SIZE + 1] = {0};
	LONG length = DMA_WR_SIZE;

	DWORD numSdBlksToWr = 0, numSdBlksWrSuccess = 0, totSdBlkWrSuccess = 0, numSdBlksToSend = 0;
	DWORD numDmaBlksToWr = 0, numDmaBlksWrSuccess = 0, totDmaBlksSuccess = 0;
	//ULONG lFilePageSize = DMA_WR_SIZE;		//Modify : if we give this Facility to user as argument in this API to give file access size.
	int lv, tmpBufMod;
	DWORD outerLpCounter = 0;
	
	laddr = faddr / SD_CARD_PAGE_SIZE;
	if((faddr % SD_CARD_PAGE_SIZE) != 0)
		laddr++;
	
	if((laddr < 0) || (laddr > 0xECE000))
	{
		#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "ERROR : Out of range address provided for write access. " << endl;
		SppuUsbDllDebug.close();
		#endif
		return -1;
	}//TODO: address range checkinh for modified data as well

	time_t seconds_begin, seconds_end, seconds;
	seconds_begin = time (NULL);

	while(numByToWr)
	{
		if(numByToWr > MAX_NUM_BYTES_SD_CARD_ONE_TIME)
			numByToWr = MAX_NUM_BYTES_SD_CARD_ONE_TIME;

		lNumSdBlocks = (numByToWr / SD_CARD_PAGE_SIZE);
		if((numByToWr % SD_CARD_PAGE_SIZE) != 0)
			lNumSdBlocks++;
		numSdBlksToWr = lNumSdBlocks;

		lNumDmaBlocks = (numSdBlksToWr / DMA_SD_CARD_WR_RELATION);
		if((numSdBlksToWr % DMA_SD_CARD_WR_RELATION) != 0)
			lNumDmaBlocks++;
		numDmaBlksToWr = lNumDmaBlocks;

		WrEP0(devType, SD_CARD_WRITE, laddr, numSdBlksToWr);

		while(numDmaBlksToWr)
		{
			rcount = LESS(numByToWr, DMA_WR_SIZE);
			ret = memcpy_s(wDevBuf, (DMA_WR_SIZE + 1), (fMemBuf + numByWrSuccess), rcount);
			if(0 == ret)
			{
				if(rcount < SD_CARD_PAGE_SIZE)
				{
					memset(wDevBuf + rcount, '\0', (DMA_WR_SIZE - rcount));
					numSdBlksToSend = 1;
				}
				else if(rcount <= DMA_WR_SIZE)
				{
					memset(wDevBuf + rcount, '\0', (DMA_WR_SIZE - rcount));
					numSdBlksToSend = (rcount / SD_CARD_PAGE_SIZE);
					if((rcount % SD_CARD_PAGE_SIZE) != 0)
						numSdBlksToSend++;
				}
			}
			else
			{
				#if DEBUG
				SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
				//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << " ]" << endl;
				SppuUsbDllDebug << "ERROR: memcpy_s() Failure!" << endl;
				SppuUsbDllDebug.close();
				#endif
				break;
			}
			//if(thParams.USBDevice->BulkOutEndPt)
			if(usbEp.sdCardBulkOut)
			{
				length = (numSdBlksToSend * SD_CARD_PAGE_SIZE);
				if(usbEp.sdCardBulkOut->XferData(wDevBuf, length))
				{
					if(length > 0)
					{
						numByWrSuccess += LESS(numByToWr, length);
						numDmaBlksToWr--;
						totDmaBlksSuccess++;
						numByToWr -= LESS(numByWrSuccess, length);
					}
					else
					{
						#if DEBUG
						SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
						SppuUsbDllDebug << "Wrote : " << numByWrSuccess << "Bytes" << endl;
						SppuUsbDllDebug.close();
						#endif
						break;
					}
				}
				else
				{
					#if DEBUG
					SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
					SppuUsbDllDebug << "ERROR: BulkOutEndPt->XferData failure" << endl;
					SppuUsbDllDebug << "Wrote : " << numByWrSuccess << "Bytes" << endl;
					SppuUsbDllDebug.close();
					#endif
					return -1;				//Error while reading from BulkOut End Point
				}
			}
			else
			{
				#if DEBUG
				SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
				SppuUsbDllDebug << "ERROR: No BulkOut Endpoint found on Device" << endl;
				SppuUsbDllDebug.close();
				#endif
				return -1;
			}
		}

		outerLpCounter++;
		numByToWr = lNumBytes - numByWrSuccess;
		if(lNumBytes == numByWrSuccess)
		{
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug << "STATUS: Num of bytes success = " << numByWrSuccess << endl;
			SppuUsbDllDebug.close();
			break;
		}
		laddr += numSdBlksToWr;
	}
	seconds_end = time (NULL);
	seconds = (seconds_end - seconds_begin);
	if(0 == seconds)
		seconds++;
	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
	SppuUsbDllDebug << std::dec << "PERFORMANCE : SD_card Read (FILE) : " << endl;
	SppuUsbDllDebug << "\t" << numByWrSuccess << " Bytes in " << seconds << " Seconds; ";
	SppuUsbDllDebug << "\t" << (numByWrSuccess / seconds) << " Bytes/Sec; " ;
	SppuUsbDllDebug << "\t" << ((numByWrSuccess / seconds) >> 10) << " (KBps); ";
	SppuUsbDllDebug << "\t" << ((((numByWrSuccess / seconds) >> 10)) >> 10) << " (MBps); " << endl;
//	SppuUsbDllDebug << "STATUS: In Inner loop : " << numDmaBlksToWr << " times" << endl;
//	SppuUsbDllDebug << "STATUS: In Outer loop : " << outerLpCounter << " times" << endl;
	SppuUsbDllDebug.close();
	*numBytesWrSuccess = numByWrSuccess;			//modifying value and not address

	

#if DEBUG
	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
	SppuUsbDllDebug << "STATUS: Wrote : " << numByWrSuccess << " Bytes, at address : "<< faddr << endl;
	SppuUsbDllDebug.close();
#endif
	return ret;
}
#endif

// This API writes Firmware logs into a file
#pragma region UsbFwDebugLogs
DWORD WINAPI USBDebug( LPVOID lpParam ) 
{
	struct UsbApis::c_UsbApis::threadParams *lParams = (struct UsbApis::c_UsbApis::threadParams *)lpParam;
	int ret;
	FILE *wrLogFile;

	unsigned char fInBuf[DEBUG_BUF_SIZE] = {'\0'};			//2015May27 initialized from '\0'
	unsigned int lsize = DEBUG_BUF_SIZE;
	BOOL m_bLogFileOpenFlag = FALSE;

	if (lsize < 1024)					/* require atleast 128 bytes to read from Interrupt End Point */
		lsize = 1024;

	LONG length = lsize - 1;
	OVERLAPPED inOvLap;
	memset(fInBuf, '\0', lsize);
	
	while(1)
	{
//		cout << "In Thread" << endl;
		if((lParams->USBDevice->IsOpen() == TRUE) && ENABLE_LOGGING)
		{		
			if (lParams->USBDevice->InterruptInEndPt)
			{
				length = lsize - 1;
				if((lParams->USBDevice->InterruptInEndPt->XferData(fInBuf, length) == FALSE))
				{
//					Sleep(100);
//					cout << "InterruptInEndPt->XferData Failure!" << endl;
				}
				else
				{
//					cout << "RD= " << length << endl;
					if (length == 0)
					{	
////						cout << "IN THREAD LENGTH_0" << endl;
#if 0
						if((m_bLogFileOpenFlag == TRUE))
						{
							fclose(wrLogFile);
							m_bLogFileOpenFlag = FALSE;
						}
#endif
//						Sleep(100);
					}
					else
					{
////						cout << "IN THREAD LENGTH_NON_0" << endl;
						fInBuf[length + 1] = '\0';
#if 0
						if(m_bLogFileOpenFlag == FALSE)
						{
							wrLogFile = fopen(DEBUF_FILE_NAME, "a+");		//TODO FIle check
							m_bLogFileOpenFlag = TRUE;
						}
#endif
//						Sleep(100);
						wrLogFile = fopen(DEBUF_FILE_NAME, "a+");
						fwrite((fInBuf /*+ 8*/), 1, length, wrLogFile);
						fclose(wrLogFile);
					}
				}
			}
			else
			{
				cout << "No Interrupt Endpoint on Device" << endl;
				break;
			}
		}
		else
		{
			//tempFile << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
			//tempFile << "STATUS: Device Opened Successfully!" << endl;
			//tempFile.close();
			cout << "############THREAD IN SLEEP" << endl;
			Sleep(2000);
		}
	}				//while
	cout << "THREAD ENDING....." << endl;
	return 0;
}
#pragma endregion UsbFwDebugLogs

//This API is to open the device
#pragma region OpenDevice
//Function that checks if device is already opened and opens it otherwise.
HRESULT UsbApis::c_UsbApis::OpenDevice()
{
	//#if DEBUG
	//SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
	//SppuUsbDllDebug << "============================ Open USB Device ============================" << endl;
	//SppuUsbDllDebug.close();
	//#endif
	if(thParams.flag == FALSE)
	{
		thParams.USBDevice = new CCyUSBDevice();
		//TODO : Check FW Version then proceed.
		if (thParams.USBDevice->IsOpen())
		{
			SYSTEMTIME st;
			GetLocalTime(&st);
			#if DEBUG
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out);
			SppuUsbDllDebug << "\n############################################################\nLogging Started :" <<
				st.wDay << "/" << st.wMonth << "/" << st.wYear << "\t" << 
				st.wHour << ":" << st.wMinute  << ":" << st.wSecond << endl << endl;
			SppuUsbDllDebug.close();
			#endif

#pragma region DevEndPoints
			int  eptCount = thParams.USBDevice->EndPointCount();
			int i,NumBulkInEPs = 0, NumBulkOutEPs = 0, lpCounter = 0;
			for  ( i=1 ; i<eptCount; i++) 
			{
				lpCounter++;
				bool  bIn1 = ((thParams.USBDevice->EndPoints[i]->Address & 0xFF) == UsbEpAddr::LFT_SPPU_FPGA_BULK_RD_EP);			//End Point Address
				bool  bIn3 = ((thParams.USBDevice->EndPoints[i]->Address & 0xFF) == UsbEpAddr::LFT_SPPU_SDCARD_BULK_RD_EP) ;
				bool  bOut1 = ((thParams.USBDevice->EndPoints[i]->Address & 0xFF) == UsbEpAddr::LFT_SPPU_FPGA_BULK_WR_EP);			//End Point Address
				bool  bOut3 = ((thParams.USBDevice->EndPoints[i]->Address & 0xFF) == UsbEpAddr::LFT_SPPU_SDCARD_BULK_WR_EP) ;
				bool  bBulk = (thParams.USBDevice->EndPoints[i]->Attributes == 2 );				//Type of End Point 0=control, 1= Iso, 2= Bulk, 3= Interrupt
				if (bBulk && (bIn1 || bIn3)) 
				{
					if(bIn1)
					{
						usbEp.fpgaBulkIn = (CCyBulkEndPoint *) thParams.USBDevice->EndPoints[i];
//						cout << "bIn1  : i = " << i << endl;
					}
					else if(bIn3)
					{
						usbEp.sdCardBulkIn = (CCyBulkEndPoint *) thParams.USBDevice->EndPoints[i];
//						cout << "bIn3  : i = " << i << endl;
					}
					else break;
					NumBulkInEPs++;
				}
				if  (bBulk && (bOut1 || bOut3)) 
				{
					if(bOut1)
					{
						usbEp.fpgaBulkOut = (CCyBulkEndPoint *) thParams.USBDevice->EndPoints[i];
//						cout << "bOut1 : i = " << i << endl;
					}
					else if(bOut3)
					{	
						usbEp.sdCardBulkOut = (CCyBulkEndPoint *) thParams.USBDevice->EndPoints[i];
//						cout << "bOut1 : i = " << i << endl;
					}
					else break;
					NumBulkOutEPs++;
				}
			}
			#if DEBUG
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug << "STATUS: Loop Counter is = " << lpCounter << endl;
			SppuUsbDllDebug << "STATUS: Number of Bulk Endpoints are = " << (NumBulkInEPs + NumBulkOutEPs) << endl;
			SppuUsbDllDebug << "STATUS: Number of Bulk In  Endpoints are = " << NumBulkInEPs << endl;
			SppuUsbDllDebug << "STATUS: Number of Bulk OUT Endpoints are = " << NumBulkOutEPs << endl;
			SppuUsbDllDebug.close();
			#endif
#pragma endregion DevEndPoints

			thParams.flag = TRUE;
			if(ENABLE_LOGGING)
			{
				CreateThread( NULL, 0, USBDebug, &thParams, 0, NULL); 
			}
			#if DEBUG
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug <<  std::dec << "STATUS: Device Opened Successfully!" << endl;
			SppuUsbDllDebug.close();
			#endif

			//HACK
			//For TCL, 
			m_nBulkStreamType = 0x4200;

			return S_OK;
		}
		else
		{
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug << "ERROR : Unable to open Device!" << endl;
			SppuUsbDllDebug.close();
			return S_FALSE;
		}
	}
	else
	{
//		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
//		SppuUsbDllDebug << "STATUS: Device already Opened!" << endl;
//		SppuUsbDllDebug.close();
		return S_OK;
	}
	#if DEBUG
	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
	SppuUsbDllDebug << "STATUS: Device can not be Opened! No Device Found!" << endl;
	SppuUsbDllDebug.close();
	#endif
	return S_FALSE;
}
#pragma endregion OpenDevice

//This API is to close the opened device
#pragma region CloseDevice
HRESULT UsbApis::c_UsbApis::CloseDevice()
{
	//	HRESULT ret = S_OK;
	if(thParams.flag == TRUE)
	{
		thParams.USBDevice->Close();
		delete thParams.USBDevice;
		thParams.USBDevice = NULL;
		thParams.flag = FALSE;
	}
#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "STATUS: Device Closed!" << endl;
		SppuUsbDllDebug.close();
#endif
	return S_OK;
}
#pragma endregion CloseDevice

//This API updates the Firmware. 
#pragma region UpdateFW
HRESULT UsbApis::c_UsbApis::UpdateFirmWare(DeviceTypes devType, char *fname)
{
	#if DEBUG
	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
	SppuUsbDllDebug << "============================ FW Update ============================" <<  devType << endl;
	SppuUsbDllDebug.close();
	#endif
	if(OpenDevice())
		return -1;

	if(devType == UsbApis::DEVICE_TYPES::LFT_SPPU_DEV_FX3_SPI_FLASH)
	{
		FILE *rdSpiBinFile;
		/* Check file existance */
		if(!ifstream (fname))
		{	
			#if DEBUG
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug << "ERROR: File does not Exist!" << endl;
			SppuUsbDllDebug.close();
			#endif
			return -1;
		}

		/* opening the file */
		if(!(rdSpiBinFile = fopen(fname, "rb")))
		{
			#if DEBUG
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug << "Error: Can not Open File." << endl;
			SppuUsbDllDebug.close();
			#endif
			return -1;
		}

		/* Get file size */
		fseek(rdSpiBinFile, 0, SEEK_END);
		DWORD fNumByToWr = ftell(rdSpiBinFile);
		fseek(rdSpiBinFile, 0, SEEK_SET);

		DWORD numByToWr = fNumByToWr;

		if(0 == numByToWr)
		{
			#if DEBUG
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
			SppuUsbDllDebug << "ERROR: No Data in File! = " << numByToWr << endl;
			SppuUsbDllDebug.close();
			#endif
			return -1;
		}
		else if(numByToWr > SPI_FLASH_SIZE)
		{
			#if DEBUG
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
			SppuUsbDllDebug << "ERROR: Data size greater than Spi Flash Size. = " << numByToWr << endl;
			SppuUsbDllDebug.close();
			#endif
			return -1;
		}
		//numByToWr : Should be a multiple of 256 and less than or equal to 4096

		long ret;
		int rcount = 0;
		DWORD numByWrSuccess = 0;
		DWORD numPgToWr = 0, numPgWrSuccess = 0, numSpiPgsToSend = 0;
		DWORD lNumSpiPgs, lNumSpiBufs;
		DWORD numSpiSecToErase = 0;
		UINT16 spiPgAddr = 0;
		UINT16 spiWrLength = 0;
		UINT16 numSpiByWrSuccess = 0;
		unsigned char wrSpiBuf[SPI_FLASH_WR_BUF_SIZE + 1] = {0};

		numSpiSecToErase = (numByToWr / SPI_FLASH_SECTOR_SIZE);
		if((numByToWr % SPI_FLASH_SECTOR_SIZE) != 0)
			numSpiSecToErase++;

		ret = spiFlashErase(numSpiSecToErase);
		if(0 == ret)
		{
			#if DEBUG
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug << "STATUS: SPI Flash Erase SUCCESS" << endl;
			SppuUsbDllDebug.close();
			#endif
		}
		else
		{
			#if DEBUG
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug << "ERROR: SPI Flash Erase FAILURE" << endl;
			SppuUsbDllDebug.close();
			#endif
			return -1;
		}
		int lp_counter = 0;
		while(numByToWr)
		{
			rcount = fread(wrSpiBuf, 1, LESS(numByToWr, SPI_FLASH_WR_BUF_SIZE), rdSpiBinFile);
			if(0 == rcount)
			{
				#if DEBUG
				SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
				SppuUsbDllDebug << "ERROR: Unable to read from File!" << endl;
				SppuUsbDllDebug.close();
				#endif
				break;
			}
			else if(rcount < SPI_FLASH_PAGE_SIZE)
			{
				memset((wrSpiBuf + rcount), '\0', (SPI_FLASH_WR_BUF_SIZE - rcount));
				numSpiPgsToSend = 1;
			}
			else if(rcount <= SPI_FLASH_WR_BUF_SIZE)
			{
				memset((wrSpiBuf + rcount), '\0', (SPI_FLASH_WR_BUF_SIZE - rcount));
				numSpiPgsToSend = (rcount / SPI_FLASH_PAGE_SIZE);
				if((rcount % SPI_FLASH_PAGE_SIZE) != 0)
					numSpiPgsToSend++;
			}
			if(0 == spiFlashWrite(wrSpiBuf, spiPgAddr, numSpiPgsToSend, &numSpiByWrSuccess))
			{
				if(numSpiByWrSuccess > 0)
				{
					numByWrSuccess += LESS(numByToWr, numSpiByWrSuccess);
					numByToWr -= LESS(numByWrSuccess, numSpiByWrSuccess);
					spiPgAddr += (numSpiPgsToSend) ;					//* SPI_FLASH_PAGE_SIZE);
					lp_counter++;
				}
			}
			else
			{
				#if DEBUG
				SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
				SppuUsbDllDebug << "Wrote : " << numByWrSuccess << "Bytes" << endl;
				SppuUsbDllDebug.close();
				#endif
				break;
			}
		}			//while pending bytes to write
		#if DEBUG_ERROR
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "STATUS: SPI Flash : Wrote : " << numByWrSuccess << " Bytes, at address : "<< 0 << endl;
		SppuUsbDllDebug << "STATUS: LOOP COUNTER " << lp_counter << endl;
		SppuUsbDllDebug.close();
		#endif
	}
	else if(devType == UsbApis::DEVICE_TYPES::LFT_SPPU_DEV_FPGA_SPI_FLASH)
	{
	//TODO : refer pavo code

		if(S_OK == FpgaSpiProgram(fname))
		{
			#if DEBUG_ERROR
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug << "ERROR: Unable to program SPI Flash." << endl;
			SppuUsbDllDebug.close();
			#endif
			return -1;
		}
	}
	else		//Unknown device 
	{
		#if DEBUG_ERROR
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "ERROR: Unknown device selected for Firmware Update" << endl;
		SppuUsbDllDebug.close();
		#endif
		return -1;
	}
	return S_OK;
}

HRESULT UsbApis::c_UsbApis::spiFlashErase(DWORD numSpiSecToErase)
{
	int lv, ret;
	unsigned char spiStatus = 0x1;
	UINT16 spiSecErAddr = 0;
	for(lv = 0; lv < numSpiSecToErase; lv++)
	{
		//Erase sectors
		SendCommandEP0(&spiStatus, 0, SPI_FLASH_REQ_ERASE_POLL, 0x0001, spiSecErAddr, DO_NOT_CARE);
	
		#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
//		SppuUsbDllDebug << "In Iteration no. = " << lv << ", Sector addr = " << spiSecErAddr << endl;
//		SppuUsbDllDebug << "STATUS: Polling for SPI Flash ERASE" << endl;
		SppuUsbDllDebug.close();
		#endif
		//Poll for erase to complete
		do{
			ret = SendCommandEP0(&spiStatus, 1, 0xC4, DO_NOT_CARE, DO_NOT_CARE, 0x0001);
		}while(0 != spiStatus);

		#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
//		SppuUsbDllDebug << "STATUS: Polling for SPI Flash ERASE - Done" << endl;
		SppuUsbDllDebug.close();
		#endif
		spiSecErAddr ++;//= 65536;
	}
	return S_OK;
}

HRESULT UsbApis::c_UsbApis::spiFlashWrite(unsigned char *pBuf, UINT16 spiWrPgAddr, UINT16 numSpiPgsToWr, UINT16 *numByWrSuccess)
{
	int lv, ret;
	unsigned char spiStatus = 0x1;
	UINT16 spiPgAddr = spiWrPgAddr;
	UINT16 spiWrLength = (numSpiPgsToWr * SPI_FLASH_PAGE_SIZE);

	//Write First sector
	SendCommandEP0(pBuf, 0, SPI_FLASH_REQ_WR, 0x0000, spiPgAddr, spiWrLength);

	#if DEBUG
	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
//	SppuUsbDllDebug << "Page addr = " << spiPgAddr << ", Length = " << spiWrLength << endl;
//	SppuUsbDllDebug << "STATUS: Polling for SPI Flash WRITE" << endl;
	SppuUsbDllDebug.close();
	#endif
	//Poll for write to complete
	do{
		ret = SendCommandEP0(&spiStatus, 1, SPI_FLASH_REQ_ERASE_POLL, 0x0000, 0x0000, 0x0001);
	}while(0 != spiStatus);
	#if DEBUG
	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
//	SppuUsbDllDebug << "STATUS: Polling for SPI Flash WRITE - Done" << endl;
	SppuUsbDllDebug.close();
	#endif

	*numByWrSuccess = spiWrLength;
	return S_OK;
}


HRESULT UsbApis::c_UsbApis::FpgaSpiProgram(char *fName)
{
	FILE *fp;
	UINT32 pollBeforeWr = 0xFFFFFFFF;
	time_t start = time(0);
	FILE *fp_log ;//= ;fopen("PavoUsbDriver.log","a");
	char *point = fName + strlen(fName);
	DWORD dummy;

#if 1
	fp_log = fopen("PavoUsbDriver.log","a");
	if(fp_log)
	{
		fprintf(fp_log,"=======================================================\n");
		fprintf(fp_log,"FPGAUpdate: %s\n",fName) ;
		fclose(fp_log);
	}
#endif
	unsigned long version=0 ;
	//RegReadFPGA(0x0 , &version);

	if((point = strrchr(fName,'.')) != NULL ) 
	{
		if(strcmp(point,".bit")== 0)
		{
			fp = fopen (fName , "rb" );				//Opened the bit file
			if(NULL == fp)
			{
#if 1
				fp_log = fopen("PavoUsbDriver.log","a");
				if(fp_log)
				{
					fprintf(fp_log,"FPPG Flash Config Error: File not found\n");
					fclose(fp_log);
				}
#endif
				return 1;
			}

			fseek(fp, 0, SEEK_END);
			long fsize = ftell(fp);
			fseek(fp, 0, SEEK_SET);
#if 1
			fp_log = fopen("PavoUsbDriver.log","a");
			if(fp_log)
			{
				fprintf(fp_log,"==========================================================\n");
				fprintf(fp_log,"FPPG Config Started File:%s  FileSize:0x%08X\n", fName, fsize);
				fclose(fp_log);
			}
#endif
//////////////////// BULK ERASE MODE STARTS HERE ///////////////////////////////////

			//ResetDesign() ;					//Not required:Mohit
			spiFlashInstrType ( 8 ) ;			//Sending instruction to SPI
			spiFlashInstrType ( 0 ) ;			//Toggling

			Sleep(10) ;
			BusyCheck() ;

			//ResetDesign() ;					//Not required:Mohit
			spiFlashInstrType ( 8 ) ;
			spiFlashInstrType ( 0 ) ;
			Sleep(10) ;
			BusyCheck() ;

			//ResetDesign() ;					//Not required:Mohit

//////////////////// BULK ERASE MODE ENDS HERE ///////////////////////////////////
///////////////////  FPGA ROUTINE STARTS HERE/////////////////////////////////////

			int numPages = fsize / 256 ;

			if(fsize % 256 != 0)
				numPages++ ;
#if 1
			if(fp_log)
			{
				fprintf(fp_log,"==========================================================\n");
				fprintf(fp_log,"NUMBER OF PAGES  :   %08x\n" , numPages);
				fclose(fp_log);
			}
#endif
			spiFlashStartAdd(0x0) ;
			spiFlashFileSize(numPages);
			WriteModeEnable() ;

			unsigned char *string = (unsigned char *) calloc(256 * numPages,sizeof(char));
			fread(string, fsize , 1, fp);
			fclose(fp) ;			//closed the bit file



			// Looping Through The File Structure And Extracting One Page Frame Of 256 Data Bytes 
			for(int cur_pgFrm =0 ; cur_pgFrm < numPages ; cur_pgFrm++)
			{
				// pageFrame consist of page frame to be written to the Flash
				unsigned char *pageFrame = (unsigned char *) calloc(256,sizeof(char));
				// copying data form the file structure to the pageFrame Structure 
				for(int curr_data =0 ; curr_data < 256 ; curr_data++) 
				{
					pageFrame[curr_data] = string[cur_pgFrm * 256 + curr_data ];
				}
#if 1
////			CString strUsbDriver = m_strCurrentWorkingDir + _T("\\PavoUsbDriver.bit");
				fp_log = fopen("PavoUsbDriver.bit","wb");
				if(fp_log)
				{
					for(int d =0 ; d < 256 ; d = d++ )
						fprintf(fp_log,"%c",pageFrame[d]); 
				}
				fclose(fp_log);
#endif
				// one page frame will be written in terms of 8 pageblocks
				for(int blockNo =0 ; blockNo < 4; blockNo++)
				{
					int c = 0;
					const int size = 64 ;
					UCHAR str[size] ;
#if 1
					for(int n = 0 ; n < size ; n++)
					{
						str[n] = pageFrame[(blockNo * 64) + n];
						//str[2*n] = 0x01 ;
						//str[2*n + 1] = pageFrame[(blockNo*32) + n] ;
					} 
#endif
#if 0
////					CString strUsbDriverData = m_strCurrentWorkingDir + _T("\\PavoUsbDriver_DATA.bit");
					fp_log = fopen("PavoUsbDriver_DATA.bit","ab");
					//fp_log = fopen(strUsbDriverData,"ab");
					if(fp_log)
					{
					for(int d =1 ; d < 64 ; d = d+2 )
						fprintf(fp_log,"%c",str[d] );
					} 
					fclose(fp_log);
#endif

					fp_log = fopen("PavoUsbDriver.log","a");
					if(fp_log)
					{
						fprintf(fp_log," Polling for SPI Access Ready...\n");
						fclose(fp_log);
					}

					do {										//Poll check from Mohit, 12 Aug 2015
						RegisterRead(0x0250, &pollBeforeWr);
					}while(0 != (pollBeforeWr & 0x2));

					//burstwritemode(str,size);
					__WrToDdr(DeviceTypes::LFT_SPPU_DEV_FPGA_SPI_FLASH, str, size, &dummy);			//__CHANGED__ : HP, 28 july 2015
				}
#if 1
				fp_log = fopen("PavoUsbDriver.log","a");
				if(fp_log)
				{
					fprintf(fp_log," Bytes Written  From %08xth-%08xth \n",cur_pgFrm * 256 , (cur_pgFrm * 256) + 256);
					fclose(fp_log);
				}
#endif
				free(pageFrame) ;
				pageFrame = NULL ;
			}

			BusyCheck();						//TODO: Mohit, Do we need this
#if 1
			fp_log = fopen("PavoUsbDriver.log","a");
			if(fp_log)
			{
				fprintf(fp_log,"Bytes Written:0x%08X\n",numPages * 256 );
				fprintf(fp_log,"FPPG Config Done\n");
				fclose(fp_log);
			}
#endif
			free(string);
			string = NULL;

		}
////////////////////// FPGA ROUTINE ENDS HERE ///////////////////////////////////////
///////////////////// SPI FLASH READ ROUTINE STARTS HERE ///////////////////////////
#if 0
		else if(strcmp(point,".bit1")== 0)
		{
////			CString strOutputBit = m_strCurrentWorkingDir + _T("\\Output.bit");
			FILE * fp_readData = fopen ("Output.bit" , "ab" );

			//FILE * fp_readData = fopen (strOutputBit, "ab" );
			if(NULL == fp_readData)
			{
				fp_log = fopen("PavoUsbDriver.log","a");
				if(fp_log)
				{
					fprintf(fp_log,"FPPG Flash Config Error: File not found\n");
					fclose(fp_log);
				}
				return 1;
			}
			unsigned long pageFrameCnt =  5 ;
			ResetDesign() ;
			spiFlashStartAdd(0x00);
			spiFlashFileSize (pageFrameCnt);
			ReadModeEnable();	
			Sleep( 10 ) ;

			ResetDesign() ;
			spiFlashStartAdd(0x00);
			spiFlashFileSize (pageFrameCnt);
			ReadModeEnable();	
			Sleep( 10 ) ;

			//unsigned long readData;
			UINT32 readData;
			unsigned long byteAddress = 0x0254 ;
			RegisterRead(byteAddress , &readData);

			for(int i =0 ; i< pageFrameCnt ; i++ )
			{
				//unsigned long readData;
				UINT32 readData;
				unsigned long byteAddress = 0x0254 ;
				Sleep(10) ;
				for(int j =0 ; j< 256 ; j++ ) 
				{
					EmptyCheck() ;
					//readFpga( &readData, 1, byteAddress, 0);
					RegisterRead(byteAddress , &readData);
					readData = readData & 0x000ff;
					fprintf(fp_log,"%c",readData );
				}
			}
			fclose(fp_readData);
		}
#endif
	}
///////////////////// SPI FLASH READ ROUTINE ENDS HERE /////////////////////////////
	
	double seconds_since_start = difftime( time(0), start);
#if 1
	fp_log = fopen("PavoUsbDriver.log","a");
	if(fp_log)
	{
		fprintf(fp_log,"time taken for writing n bytes without read : %f \n",seconds_since_start) ;
		fprintf(fp_log,"=====================================================================\n");
		fclose(fp_log);
	}
	fclose(fp_log);
#endif
	return S_OK;
}

HRESULT UsbApis::c_UsbApis::ResetDesign(void)
{
	HRESULT hRes = S_OK;
	//unsigned long val = 0;
	UINT32 val = 0;
	unsigned long addr = 0x5000;//	0x0004; //rd1		//Mohit, 12 Aug 2015

	//#read current setting and then writing reset to reg
	//hRes = m_ptrIODriver->GetRegisterbyAddress(portHandle, 0, 1, addr, 0, &val, false); // 0x[rd1 0x0004]
	RegisterRead(addr , &val);
	
	//val = val & 0xFFFFFFFD;			//[expr 0x[rd1 0x0004] & 0xFFFFFFFD]
	//val = val | 0x00000002;			//set val [expr [expr 0x[rd1 0x0004] & 0xFFFFFFFD] | 0x00000002]
	val = val & 0xFFFFF7FF;			///Mohit 12 Aug 2015: 11 bit to be toggled
	val = val | 0x00000800;

	//hRes = m_ptrIODriver->SetRegisterbyAddress(portHandle, 0, 1, addr, 0, val, false); //wr1 0x0004 $val
	RegisterWrite(addr , val );

	//hRes = m_ptrIODriver->GetRegisterbyAddress(portHandle, 0, 1, addr, 0, &val, false); // 0x[rd1 0x0004]
	RegisterRead(addr , &val);
	//val = val & 0xFFFFFFFD; //set val [expr 0x[rd1 0x0004] & 0xFFFFFFFD]
	val = val & 0xFFFFF7FF; //Mohit, 22 Aug 2015

	//hRes = m_ptrIODriver->SetRegisterbyAddress(portHandle, 0, 1, addr, 0, val, false); //wr1 0x0004 $val
	RegisterWrite(addr , val );
	Sleep(1); // after 1
	return S_OK;
}

HRESULT UsbApis::c_UsbApis::spiFlashInstrType(unsigned long instr_type)
{
	//unsigned long data_read = 0 ;
	UINT32 data_read = 0 ;
	//RegisterRead(0x0 , &data_read);
	RegisterRead(0x0240 , &data_read);				//__MODIFY__ : Mohit 12 Aug 2015
	data_read = (( data_read & 0xFFFFFFE0 ) | instr_type ) ;

	FILE *fp_log = fopen("PavoUsbDriver.log","a");
		if(fp_log)
		{
			fprintf(fp_log,"spiFlashInstrType FUNCTION value Written at 0x0240 is %d\n" , data_read) ;
			fclose(fp_log);
		}

	RegisterWrite(0x0240 , data_read );
	return S_OK;
}

HRESULT UsbApis::c_UsbApis::BusyCheck()
{
	//unsigned long test = 0 ;
	UINT32 test = 0 ;
	RegisterRead(0x250 , &test);
	int i =0 ;
	// while ((test & 1 ) == 1 ) 
	for(int j = 0 ; j < 100 ; j++ )
	{
		Sleep(30000) ;
			RegisterRead(0x250 , &test);
		if((test & 1 ) == 1 )
		{
#if 1
			FILE *fp_log = fopen("PavoUsbDriver.log","a");
			if(fp_log)
			{
				fprintf(fp_log,"BusyCheck %d \n",j) ;
				fclose(fp_log);
			}
#endif
		}
		else
		{
			break ;
		}
	}
	return S_OK;
}

HRESULT UsbApis::c_UsbApis::spiFlashStartAdd(unsigned long data)
{
#if 1
	FILE *fp_log = fopen("PavoUsbDriver.log","a");
	if(fp_log)
	{
		fprintf(fp_log,"spiFlashStartAdd FUNCTION value Written at 0x0244 is %d\n" , data) ;
		fclose(fp_log);
	}   
#endif
	RegisterWrite(0x0244 , data ); 
	return S_OK;
}

HRESULT UsbApis::c_UsbApis::spiFlashFileSize(unsigned long data)
{
#if 1
	FILE *fp_log = fopen("PavoUsbDriver.log","a");
	if(fp_log)
	{
		fprintf(fp_log,"spiFlashFileSize FUNCTION value Written at 0x024C is %d\n" , data) ;
		fclose(fp_log);
	}
#endif
	RegisterWrite(0x024C , data );
	return S_OK;
}

HRESULT UsbApis::c_UsbApis::WriteModeEnable()
{
	spiFlashInstrType (2);
	spiFlashInstrType (0);
	return S_OK;
}

#if 0
HRESULT UsbApis::c_UsbApis::spiFlashInstrType(unsigned long instr_type)
{
	unsigned long data_read = 0 ;
	RegReadFPGA(0x0 , &data_read);
	data_read = (( data_read & 0xFFFFFFE0 ) | instr_type ) ;
	FILE *fp_log = fopen("PavoUsbDriver.log","a");
	if(fp_log)
	{
		fprintf(fp_log,"spiFlashInstrType FUNCTION value Written at 0x0240 is %d\n" , data_read) ;
		fclose(fp_log);
	}   
	RegisterWrite(0x0240 , data_read );
	return S_OK;
}
#endif

HRESULT UsbApis::c_UsbApis::EmptyCheck()
{
	//unsigned long test = 0 ;
	UINT32 test = 0 ;
	RegisterRead(0x0250 , &test);
	
	for(int j = 0 ; j < 1000 ; j++ )
	{
		RegisterRead(0x250 , &test);
		if((test >> 2 & 1) == 1  )  
		{
#if 1
			FILE *fp_log = fopen("PavoUsbDriver.log","a");
			if(fp_log)
			{
				fprintf(fp_log,"EmptyCheck %d \n",j) ;
				fclose(fp_log);
			}
#endif
		}
		else
		{
			break ;
		}
	}
	return S_OK;
}

HRESULT UsbApis::c_UsbApis::ReadModeEnable()
{
	spiFlashInstrType( 1 ) ;
	spiFlashInstrType( 0 ) ;
	return S_OK;
}


/** write 250 bytes in burst mode */
int  UsbApis::c_UsbApis::burstwritemode(PUCHAR buf , long numbytes)
{

#if 0			//Call __WrFileToDdr();
    bool success ; 
    long numBytesTx=0;
    numBytesTx = numbytes;
        
    if (EndPoints[1]->Attributes==2 /* Bulk EP */ && EndPoints[1]->Address==0x02 /* EP and direction: EP2OUT */)
    {
      success=EndPoints[1]->XferData(buf,numBytesTx);
    }
    else
    {
      // Check EP numeration
      return ERR_CONFIG;
    }


    if ((!success  ) || (numBytesTx!=numbytes))
    {
      // Something went wrong with the transfer
      return ERR_XFER;
    }

    unsigned char data[2];
    data[0]=1;
    data[1]=1;
    err=ctrlReadWrite(TGT_DEVICE,REQ_VENDOR,DIR_TO_DEVICE,0xBB,2,numbytes,2,data);
    ERRCHK;
#endif
    return 0;
}


#pragma endregion UpdateFW

#pragma region RegAccess
//API to read device register.
HRESULT UsbApis::c_UsbApis::RegisterRead_V2(UINT32 addr, UINT32 *val)
{
	BOOL ret = S_FALSE;
	UINT32 lVal;
	LONG numBy = DEFAULT_NUM_BY_RD_EP0;
	unsigned char buf[512] = {0};

	if(OpenDevice())
		return -1;

	#if DEBUG
	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
	SppuUsbDllDebug << "============================ Reg Read V2 ============================" << endl;
	SppuUsbDllDebug.close();
	#endif
	ret = WrEP0(DO_NOT_CARE, LFT_SPPU_REQ_REG_READ, addr, DO_NOT_CARE);
	if(ret != S_OK)
	{
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "ERROR : RegRead unable to Write at EP0" << endl;
		SppuUsbDllDebug.close();
		return -1;
	}
	ret = S_FALSE;
	ret = RdEP0(DO_NOT_CARE, LFT_SPPU_RQT_GET_EP0, buf, numBy);
	if(ret == S_OK)
	{
		lVal = (buf[0] & 0xFF);
		lVal |= ((buf[1] & 0xFF) << 8);
		lVal |= ((buf[2] & 0xFF) << 16);
		lVal |= ((buf[3] & 0xFF) << 24);

		*val = lVal;

		#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "SUCCESS : Value Read at Reg 0x" << std::hex << addr << " is 0x" << std::hex << *val << std::dec << endl;
		SppuUsbDllDebug.close();
		#endif
	}
	else
	{
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "ERROR : RegRead unable to value read at EP0" << endl;
		SppuUsbDllDebug.close();
		return -1;
	}
	return S_OK;
}

//API to write device register.
HRESULT UsbApis::c_UsbApis::RegisterWrite_V2(UINT32 addr, UINT32 val)
{
	BOOL ret = S_FALSE;
	
	if(OpenDevice())
		return -1;

	#if DEBUG
	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
	SppuUsbDllDebug << "============================ Reg Write ============================" << endl;
	SppuUsbDllDebug.close();
	#endif
	
	ret = WrEP0(DO_NOT_CARE, LFT_SPPU_REQ_REG_WRITE, addr, val);
	if(ret == S_OK)
	{
		#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "SUCCESS : Value Wrote at Reg 0x"<< std::hex << addr << " is 0x" << std::hex << val << std::dec << endl;
		SppuUsbDllDebug.close();
		#endif
	}
	else
	{
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "ERROR : RegWrite unable to Write at EP0" << endl;
		SppuUsbDllDebug.close();
		return -1;
	}
	return S_OK;
}
#pragma endregion RegAccess

#if 0
#pragma region ThirtyMibRead
 HRESULT UsbApis::c_UsbApis::RdSdCard0(char *fname, DWORD addr, DWORD numBytes, DWORD *numBytesRdSuccess)
{
	OpenDevice();
	if(thParams.flag == FALSE)
	{
#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
		SppuUsbDllDebug << "ERROR: Device Not Opened!" << endl;
		SppuUsbDllDebug.close();
#endif
		return -1;
	}
	HRESULT hRes = S_OK;
	//const char *fileStat;
	
	DWORD lNumBytes = numBytes;
	DWORD lNumBlocks;

	if(lNumBytes == 0)
	{
#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
		SppuUsbDllDebug << "STATUS: Request of 0 byte transfer!" << endl;
		SppuUsbDllDebug.close();
#endif
		return 0;
	}

	lNumBlocks = (lNumBytes / SD_CARD_PAGE_SIZE);

	if((lNumBytes % SD_CARD_PAGE_SIZE) != 0)
		lNumBlocks++;

	if(lNumBlocks < 1)
	{
#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
		SppuUsbDllDebug << "STATUS: Invalid No. of Blocls to read = " <<lNumBlocks << endl;
		SppuUsbDllDebug.close();
#endif
		return -1;
	}

	FILE *wrBinFile;
	/* Check file existance */
	if(!ifstream (fname))
	{
#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
		SppuUsbDllDebug << "ERROR: File does not Exist!" << endl;
		SppuUsbDllDebug << "STATUS : creating New File!" << endl;
		SppuUsbDllDebug.close();
#endif
	}

	/* opening the file */
	if(!(wrBinFile = fopen(fname, "ab")))
	{
#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
		SppuUsbDllDebug << "Error: Can not Open File." << endl;
		SppuUsbDllDebug.close();
#endif
		return -1;
	}

	DWORD wcount = 1, numBytesToRead = lNumBytes, numBytesReadSuccess = 0;
	unsigned char rDevBuf[SD_CARD_PAGE_SIZE + 1] = {0};
	LONG length = SD_CARD_PAGE_SIZE;

	SYSTEMTIME st;
	GetSystemTime(&st);
	cout << "Read Start Time : ";
	cout << st.wHour << ":" << st.wMinute << ":" << st.wSecond << ":" << st.wMilliseconds << endl;

	DWORD numBlocksToRead = lNumBlocks, numBlocksReadSuccess = 0, totBlkRdSuccess = 0;

	while(numBytesToRead)
	{
		if(numBytesToRead > MAX_NUM_BYTES_SD_CARD_ONE_TIME)
			numBytesToRead = MAX_NUM_BYTES_SD_CARD_ONE_TIME;

		lNumBlocks = (numBytesToRead / SD_CARD_PAGE_SIZE);
		if((numBytesToRead % SD_CARD_PAGE_SIZE) != 0)
			lNumBlocks++;

		numBlocksToRead = lNumBlocks;

		SendCommandEP0(SD_CARD_READ, addr, numBlocksToRead);
		
		while(numBlocksToRead)
		{		
			if(thParams.USBDevice->BulkInEndPt)
			{
				if(thParams.USBDevice->BulkInEndPt->XferData(rDevBuf, length))
				{
					if(length > 0)
					{
						wcount = fwrite(rDevBuf, 1, LESS(numBytesToRead, SD_CARD_PAGE_SIZE), wrBinFile);
						if(wcount == 0)
						{
							#if DEBUG
							SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
							//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
							SppuUsbDllDebug << "ERROR: Unable to Write to File!" << endl;
							SppuUsbDllDebug.close();
							#endif
							break;
						}
						numBytesReadSuccess += LESS(numBytesToRead, SD_CARD_PAGE_SIZE);
						numBlocksToRead--;
						totBlkRdSuccess++;
						numBytesToRead -= LESS(numBytesReadSuccess, SD_CARD_PAGE_SIZE);
					}
					else
					{
						#if DEBUG
						SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
						//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
						SppuUsbDllDebug << "ERROR: Read Zero Bytes from SD Card" << endl;
						SppuUsbDllDebug << "Wrote : " << numBytesReadSuccess << "Bytes" << endl;
						SppuUsbDllDebug.close();
						#endif
						break;
					}
				}
				else
				{
					#if DEBUG
					SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
					//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
					SppuUsbDllDebug << "ERROR: BulkInEndPt->XferData failure" << endl;
					SppuUsbDllDebug << "read : " << numBytesReadSuccess << "Bytes" << endl;
					SppuUsbDllDebug.close();
					#endif
					break;
				}
			}
			else
			{
				#if DEBUG
				SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
				//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
				SppuUsbDllDebug << "ERROR: No BulkIn Endpoint found on Device" << endl;
				SppuUsbDllDebug.close();
				#endif
				return -1;
			}
		}
		numBytesToRead = numBytes - numBytesReadSuccess;
		if(numBytes == numBytesReadSuccess)
		{
			break;
		}
	}

	GetSystemTime(&st);
	cout << "Read End Time : ";
	cout << st.wHour << ":" << st.wMinute << ":" << st.wSecond << ":" << st.wMilliseconds << endl;

	*numBytesRdSuccess = numBytesReadSuccess;			//modifying value and not address
#if DEBUG
	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
	//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
	SppuUsbDllDebug << "STATUS: Read : " << numBytesReadSuccess << " Bytes, from address : "<< addr << endl;
	SppuUsbDllDebug.close();
#endif
	fclose(wrBinFile);
	return S_OK;
}
#pragma endregion ThirtyMibRead


#pragma region ThirtyMibWrite
/* This function is to write to SD Card from a File */ 
HRESULT UsbApis::c_UsbApis::WrSdCard0(char *fname, DWORD addr, DWORD numBytes, DWORD *numBytesWrSuccess, ULONG fFilePageSize, ULONG fDevPageSize)
{

	OpenDevice();
	if(thParams.flag == FALSE)
	{
	#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
		SppuUsbDllDebug << "ERROR: Device Not Opened!" << endl;
		SppuUsbDllDebug.close();
#endif
		return 1;
	}
	HRESULT hRes = S_OK;
	
	DWORD lNumBytes = numBytes;
	DWORD lNumBlocks;

	if(lNumBytes == 0)
	{
#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
		SppuUsbDllDebug << "STATUS: Request of 0 byte transfer!" << endl;
		SppuUsbDllDebug.close();
#endif
		return -1;
	}

	FILE *rdBinFile;
	/* Check file existance */
	if(!ifstream (fname))
	{	
#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
		SppuUsbDllDebug << "ERROR: File does not Exist!" << endl;
		SppuUsbDllDebug.close();
#endif
		return -1;
	}

	/* opening the file */
	if(!(rdBinFile = fopen(fname, "rb")))
	{
#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
		SppuUsbDllDebug << "Error: Can not Open File." << endl;
		SppuUsbDllDebug.close();
#endif
		return -1;
	}

	/* Get file size */
	fseek(rdBinFile, 0, SEEK_END);
    DWORD dwFileSize = ftell(rdBinFile);
	ULONG lDataSize = dwFileSize;
    fseek(rdBinFile, 0, SEEK_SET);

	int ret = S_OK;
	if(lNumBytes > dwFileSize)
	{
#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
		SppuUsbDllDebug << "STATUS: Requested more data to be written on device then present in File. Using file size!" << endl;
		SppuUsbDllDebug.close();
#endif
		lNumBytes = dwFileSize;
	}

	lNumBlocks = (lNumBytes / SD_CARD_PAGE_SIZE);

	if((lNumBytes % SD_CARD_PAGE_SIZE) != 0)
		lNumBlocks++;

	DWORD rcount = 1, numBytesToWrite = lNumBytes, numBytesWriteSuccess = 0;
	unsigned char wDevBuf[SD_CARD_PAGE_SIZE + 1] = {0};
	LONG length = SD_CARD_PAGE_SIZE;

	SYSTEMTIME st;
	GetSystemTime(&st);
	cout << "Write Start Time : ";
	cout << st.wHour << ":" << st.wMinute << ":" << st.wSecond << ":" << st.wMilliseconds << endl;

	DWORD numBlocksToWrite = lNumBlocks, numBlocksWrSuccess = 0, totBlkWrSuccess = 0;;

	while(numBytesToWrite)
	{
		if(numBytesToWrite > MAX_NUM_BYTES_SD_CARD_ONE_TIME)
			numBytesToWrite = MAX_NUM_BYTES_SD_CARD_ONE_TIME;

		lNumBlocks = (numBytesToWrite / SD_CARD_PAGE_SIZE);
		if((numBytesToWrite % SD_CARD_PAGE_SIZE) != 0)
			lNumBlocks++;

		numBlocksToWrite = lNumBlocks;

		SendCommandEP0(SD_CARD_WRITE, (addr/* + numBytesWriteSuccess*/), numBlocksToWrite);
		
		while(numBlocksToWrite)
		{		
			rcount = fread(wDevBuf, 1, LESS(numBytesToWrite, SD_CARD_PAGE_SIZE), rdBinFile);
			if(rcount == 0)
			{
				#if DEBUG
				SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
				//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
				SppuUsbDllDebug << "ERROR: Unable to read from File!" << endl;
				SppuUsbDllDebug.close();
				#endif
				break;
			}
			if(rcount < SD_CARD_PAGE_SIZE)
				memset(wDevBuf + rcount, '\0', (SD_CARD_PAGE_SIZE - rcount));
			if(thParams.USBDevice->BulkOutEndPt)
			{
				if(thParams.USBDevice->BulkOutEndPt->XferData(wDevBuf, length))
				{
					if(length > 0)
					{
						numBytesWriteSuccess += LESS(numBytesToWrite, SD_CARD_PAGE_SIZE);
						numBlocksToWrite--;
						totBlkWrSuccess++;
						numBytesToWrite -= LESS(numBytesWriteSuccess, SD_CARD_PAGE_SIZE);
					}
					else
					{
						#if DEBUG
						SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
						//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
						SppuUsbDllDebug << "ERROR: Wrote Zero Bytes" << endl;
						SppuUsbDllDebug << "Wrote : " << numBytesWriteSuccess << "Bytes" << endl;
						SppuUsbDllDebug.close();
						#endif
						break;
					}
				}
				else
				{
					#if DEBUG
					SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
					//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
					SppuUsbDllDebug << "ERROR: BulkOutEndPt->XferData failure" << endl;
					SppuUsbDllDebug << "Wrote : " << numBytesWriteSuccess << "Bytes" << endl;
					SppuUsbDllDebug.close();
					#endif
					break;
				}
			}
			else
			{
				#if DEBUG
				SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
				//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
				SppuUsbDllDebug << "ERROR: No BulkOut Endpoint found on Device" << endl;
				SppuUsbDllDebug.close();
				fclose(rdBinFile);
				#endif
				return -1;
			}
		}
		numBytesToWrite = lNumBytes - numBytesWriteSuccess;
		if(lNumBytes == numBytesWriteSuccess)
		{
			cout << "STATUS: Num of bytes success = " << numBytesWriteSuccess << endl;
			break;
		}
	}

	GetSystemTime(&st);
	cout << "Write End Time : ";
	cout << st.wHour << ":" << st.wMinute << ":" << st.wSecond << ":" << st.wMilliseconds << endl;
	*numBytesWrSuccess = numBytesWriteSuccess;			//modifying value and not address

#if DEBUG
	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
	//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
	SppuUsbDllDebug << "STATUS: Wrote : " << numBytesWriteSuccess << " Bytes, at address : "<< addr << endl;
	SppuUsbDllDebug.close();
#endif
	fclose(rdBinFile);

	return ret;
}
#pragma endregion ThirtyMibWrite

#endif

#if 0 //Old read working good only when requested bytes are multiple of 512.
/* This function is to read from SD Card to a File */
HRESULT UsbApis::c_UsbApis::RdFileFromSdCard0(char *fname, DWORD addr, DWORD numBytes, DWORD *numBytesRdSuccess)
{
	OpenDevice();

	HRESULT hRes = S_OK;
	//const char *fileStat;
	
	DWORD lNumBytes = numBytes;
	DWORD lNumSdBlocks, lNumDmaBlocks;

	if(lNumBytes == 0)
	{
#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
		SppuUsbDllDebug << "STATUS: Request of 0 byte transfer!" << endl;
		SppuUsbDllDebug.close();
#endif
		return 0;
	}
	FILE *wrBinFile;
	/* Check file existance */
	if(!ifstream (fname))
	{
#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
		SppuUsbDllDebug << "ERROR: File does not Exist!" << endl;
		SppuUsbDllDebug << "STATUS : creating New File!" << endl;
		SppuUsbDllDebug.close();
#endif
	}

	/* opening the file */
	if(!(wrBinFile = fopen(fname, "ab")))
	{
#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
		SppuUsbDllDebug << "Error: Can not Open File." << endl;
		SppuUsbDllDebug.close();
#endif
		return -1;
	}

	DWORD wcount = 1, numBytesToRead = lNumBytes, numBytesReadSuccess = 0;
	unsigned char rDevBuf[DMA_RD_SIZE + 1] = {0};
	LONG length = DMA_RD_SIZE;

	SYSTEMTIME st;
	GetSystemTime(&st);
	cout << "Read Start Time : ";
	cout << st.wHour << ":" << st.wMinute << ":" << st.wSecond << ":" << st.wMilliseconds << endl;

	/*DWORD numBlocksToRead = lNumBlocks, numBlocksReadSuccess = 0, totBlkRdSuccess = 0;*/

	DWORD numSdBlocksToRead = 0/*lNumSdBlocks*/;
	DWORD numDmaBlksToRd, numDmaBlksRdSuccess = 0, totDmaBlksRdSuccess = 0;
	ULONG lFilePageSize = DMA_RD_SIZE;		//Modify : if we give this Facility to user as argument in this API to give file access size.
	int lv;
	DWORD outerLpCounter = 0;

	while(numBytesToRead)
	{
		if(numBytesToRead > MAX_NUM_BYTES_SD_CARD_ONE_TIME)
			numBytesToRead = MAX_NUM_BYTES_SD_CARD_ONE_TIME;

		lNumSdBlocks = (numBytesToRead / SD_CARD_PAGE_SIZE);
		if((numBytesToRead % SD_CARD_PAGE_SIZE) != 0)
			lNumSdBlocks++;

		numSdBlocksToRead = lNumSdBlocks;
		 
		lNumDmaBlocks = (numBytesToRead / DMA_RD_SIZE);
		if((numBytesToRead % DMA_RD_SIZE) != 0)
			lNumDmaBlocks++;
		numDmaBlksToRd = lNumDmaBlocks;

		//WrEP0(SD_CARD_READ, addr, numSdBlocksToRead);
		WrEP0(SD_CARD_READ, addr, numSdBlocksToRead);
		
		while(numDmaBlksToRd)
		{		//Continue Here
			if(thParams.USBDevice->BulkInEndPt)
			{
				length = LESS(numBytesToRead, DMA_RD_SIZE);
				if(thParams.USBDevice->BulkInEndPt->XferData(rDevBuf, length))
				{
					if(length > 0)
					{
						wcount = fwrite(rDevBuf, 1, LESS(length, DMA_RD_SIZE), wrBinFile);
						if(wcount == 0)
						{
							#if DEBUG
							SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
							//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
							SppuUsbDllDebug << "ERROR: Unable to Write to File!" << endl;
							SppuUsbDllDebug.close();
							#endif
							break;
						}
						numBytesReadSuccess += LESS(length, DMA_RD_SIZE);
						numDmaBlksToRd--;
						totDmaBlksRdSuccess++;
						numBytesToRead -= LESS(numBytesReadSuccess, DMA_RD_SIZE);
					}
					else
					{
						#if DEBUG
						SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
						//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
						SppuUsbDllDebug << "ERROR: Read Zero Bytes from SD Card" << endl;
						SppuUsbDllDebug << "Wrote : " << numBytesReadSuccess << "Bytes" << endl;
						SppuUsbDllDebug.close();
						#endif
						break;
					}
				}
				else
				{
					#if DEBUG
					SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
					//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
					SppuUsbDllDebug << "ERROR: BulkInEndPt->XferData failure" << endl;
					SppuUsbDllDebug << "read : " << numBytesReadSuccess << "Bytes" << endl;
					SppuUsbDllDebug.close();
					#endif
					return -1;
				}
			}
			else
			{
				#if DEBUG
				SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
				//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
				SppuUsbDllDebug << "ERROR: No BulkIn Endpoint found on Device" << endl;
				SppuUsbDllDebug.close();
				#endif
				return -1;
			}
		}
		outerLpCounter++;
		numBytesToRead = numBytes - numBytesReadSuccess;
		if(numBytes == numBytesReadSuccess)
		{
			cout << "STATUS: Num of bytes success = " << numBytesReadSuccess << endl;
			break;
		}
		addr += numSdBlocksToRead;
	}

	GetSystemTime(&st);
	cout << "Read End Time : ";
	cout << st.wHour << ":" << st.wMinute << ":" << st.wSecond << ":" << st.wMilliseconds << endl;
	*numBytesRdSuccess = numBytesReadSuccess;			//modifying value and not address

	cout << "In Inner loop : " << totDmaBlksRdSuccess << " times" << endl;
	cout << "In Outer loop : " << outerLpCounter << " times" << endl;

#if DEBUG
	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
	//SppuUsbDllDebug << "[ " << __FILE__ << " : " << __LINE__ << " : " << __FUNCTIONW__ << "]" << endl;
	SppuUsbDllDebug << "STATUS: Read : " << numBytesReadSuccess << " Bytes, from address : "<< addr << endl;
	SppuUsbDllDebug.close();
#endif
	fclose(wrBinFile);
	return S_OK;
}
#endif
