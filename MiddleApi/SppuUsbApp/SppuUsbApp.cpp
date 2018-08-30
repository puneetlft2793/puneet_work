// SppuUsbApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SppuUsbDll.h"
#include <iostream>

#include<conio.h>
using namespace UsbApis;

//HOME
//#define READ_DATA_FILE		"D:\\lft\\projects\\sppu\\SPPU_PROJECT\\sppu\\fx3\\src\\lft\\release\\rtest.bin"
//#define WRITE_DATA_FILE		"D:\\lft\\projects\\sppu\\SPPU_PROJECT\\sppu\\fx3\\src\\lft\\release\\stest.bin"
////#define WRITE_SPI_FILENAME	"D:\\lft\\projects\\SPPU_PROJECT\\sppu\\fx3\\src\\lft\\release\\Dummy_spi_test.bin"
//#define WRITE_SPI_FILENAME	"D:\\lft\\projects\\sppu\\SPPU_PROJECT\\sppu\\fx3\\src\\lft\\release\\SPI_LFT_FW.img"



//OFFICE
#define READ_DATA_FILE			".\\rtest.bin"
#define WRITE_DATA_FILE			".\\stest.bin"
//#define WRITE_DATA_FILE		".\\stest.bin"
//#define WRITE_SPI_FILENAME	"D:\\hp\\Projects\\SPPU_PROJECT\\sppu\\fx3\\src\\lft\\release\\Dummy_spi_test.bin"
#define WRITE_SPI_FILENAME		".\\FW.img"
//#define WRITE_SPI_FILENAME		"D:\\hp\\Projects\\SPPU_PROJECT\\sppu\\SVN\\MiddleAPIWrapper\\Release\\FW.img"


#define ARRAY_SIZE_MEM 4096

using namespace std;


int main(int argc, char*argv[])
{
	unsigned char inBufDbg[DEBUG_BUF_SIZE];
//	unsigned char *temp;
//	unsigned char outBufSd[512] = {'h','e', 'l', 'l', 'o'};
//	unsigned char inBufSd[512] = {0};
	string rdFileName, wrFileName;
	DWORD rdStartAddr, wrStartAddr;
	DWORD rdNumBlocks, wrNumBlocks;
	DWORD numByRdSuccess, numByWrSuccess;
	UINT32 regAddr = 0;
	
	UsbApis::c_UsbApis obj;
	int choice = 0, ret = 0, choice_read = 0, choice_write = 0;
	int testChoice;
	void *dummy = NULL;

	char rdMemArr[ARRAY_SIZE_MEM];
	char wrMemArr[ARRAY_SIZE_MEM];
	unsigned char spiBuf[ARRAY_SIZE_MEM + 1];
	UINT32 regRdVal = 0, regWrVal = 0;

	int rcount, wcount;
	FILE *rdBinFile, *wrSpiBinFile;
	FILE *wrBinFile;
	int devType = 0;
	int spiDevType =100;

#if 1
	while(1)
	{
//		system("cls");
		cout << "+==================================+" << endl;
		cout << "|          SPPU USB DEMO           |" << endl;
		cout << "|  Version 0.00.001 (Release)      |" << endl;
		cout << "+==================================+" << endl;
		cout << "    USB MAIN MENU" << endl;
		cout << "    -------------" << endl;
		cout << "1. Open Device" << endl;
//		cout << "2. Get Device Status" << endl;
//		cout << "3. Get SD Card Status" << endl;
		cout << "4. Read From Device" << endl;
		cout << "5. Write to Device" << endl;
//		cout << "6. Get granularity for SIB Port" << endl;
		//cout << "7. Set granularity for SIB Port" << endl;
//		cout << "7. SD Card Read Write LoopBack test" << endl;
		cout << "8. Close" << endl;
//		cout << "9. Reset Device to power on configuration" << endl;
		cout << "10. Testing" << endl;
		cout << "11. Memory Read" << endl;
		cout << "12. Memory Write" << endl;
		cout << "13. Update Firmware" << endl;
		cout << "14. Reg Read" << endl;
		cout << "15. Reg Write" << endl;
//		cout << "16. Enable FW Debug" << endl;
//		cout << "17. Disable FW Debug" << endl;
		cout << "0. Exit" << endl;
		cout << "Enter your choice" << endl;
		//cin >> choice;
		scanf("%d", &choice);
//		cout << "You entered = " << choice << endl;
		int lc = 0;
		switch(choice)
		{
			case 1:				//Open device
			cout << "Open returned = " << obj.OpenDevice() << endl;
				//obj.OpenDevice();
				break;
			case 2:				//Get Device status
	//			cout << "End Points (other then control end Point) = " << obj.GetNumEndPoints() << endl;		//IOCTL interface used to get total number of End Points used in device.
				break;
			case 3:				//Get SD Card Status
		//		obj.GetSDCardStatus();
				break;
			case 4:				//Read From SD Card
				cout << "__READ MENU__" << endl;
				cout << "1. Read from Device" << endl;
				cout << "2. Read Device Test (will read 512 bytes from 0x8000)" << endl;
				cout << "3. Return to MAIN MENU" << endl;
				cout << "Enter your choice." << endl;
				cin >> choice_read;
				switch(choice_read)
				{
					case 1:
						cout << "Enter Start Address" << endl ;//<< "0x";
						scanf("%lu", &rdStartAddr);
						cout << "Enter Number of Bytes to read" << endl;
						scanf("%lu", &rdNumBlocks);
						cout << "Enter Device Type (6 = DDR, 9 = SD Card)" << endl; 
						scanf("%d", &devType);
						if (S_OK == obj.RdFileFromSdCard0((UsbApis::DEVICE_TYPES)devType, READ_DATA_FILE , rdStartAddr, rdNumBlocks, &numByRdSuccess))
							cout << "Successfully read " << numByRdSuccess << " bytes" << endl;
						break;
					case 2:
	//					obj.RdFileFromSdCard0(DeviceTypes::LFT_SPPU_USB_DEV_SDCARD, READ_DATA_FILE , 0x8000, 1);
						break;
					case 3:
							cout << "Enter Start Address" << endl ;//<< "0x";
							scanf("%lu", &wrStartAddr);
							cout << "Enter Number of Bytes to write" << endl;
							scanf("%lu", &wrNumBlocks);
						while(1)
						{
							lc++;
							obj.RdFileFromSdCard0(DeviceTypes::LFT_SPPU_DEV_FX3_SDCARD, READ_DATA_FILE , wrStartAddr, wrNumBlocks, &numByRdSuccess);
							cout << "\r" << lc << endl;
						}
						break;
					default:
						cout << "Choice not recognized!" << endl;
				}
				break;
			case 5:				//write to SD Card

				cout << "__WRITE MENU__" << endl;
				cout << "1. Write to Device" << endl;
				cout << "2. Write Device Test (will read 512 bytes at 0x8000)" << endl;
				cout << "3. Return to MAIN MENU" << endl;
				cout << "Enter your choice." << endl;
				cin >> choice_read;
				switch(choice_read)
				{
					case 1:
						cout << "Enter Start Address" << endl ;//<< "0x";
						scanf("%lu", &wrStartAddr);
						cout << "Enter Number of Bytes to write" << endl;
						scanf("%lu", &wrNumBlocks);
						cout << "Enter Device Type (6 = DDR, 9 = SD Card)" << endl; 
						scanf("%d", &devType);
						obj.WrFileToSdCard0((UsbApis::DEVICE_TYPES)devType, WRITE_DATA_FILE, wrStartAddr, wrNumBlocks, &numByWrSuccess);
						cout << "Successfully Wrote " << numByWrSuccess << " bytes" << endl;
						
						break;
					case 2:
						obj.WrFileToSdCard0(DeviceTypes::LFT_SPPU_DEV_FX3_SDCARD, WRITE_DATA_FILE, 0x8000, 1);
						break;
					case 3:

						lc = 0;
						cout << "Enter Start Address" << endl ;//<< "0x";
						scanf("%lu", &wrStartAddr);
						cout << "Enter Number of Bytes to write" << endl;
						scanf("%lu", &wrNumBlocks);
						while(1)
						{
							lc++;
							obj.WrFileToSdCard0(DeviceTypes::LFT_SPPU_DEV_FX3_SDCARD, WRITE_DATA_FILE, wrStartAddr, wrNumBlocks, &numByWrSuccess);
							cout << "\r" << lc << endl;

							//getch();
						}
						break;
					default:
						cout << "Choice not recognized!" << endl;
				}
				break;
			case 6:				//Get granularity
				break;
			case 7:				//Set granularity
				while(1)
				{
					lc++;
					cout << "Enter Start Address" << endl ;//<< "0x";
					scanf("%lu", &wrStartAddr);
					cout << "Enter Number of Bytes to write" << endl;
					scanf("%lu", &wrNumBlocks);

					obj.WrFileToSdCard0(DeviceTypes::LFT_SPPU_DEV_FX3_SDCARD, "D:\\hp\\Projects\\SPPU_PROJECT\\sppu\\fx3\\src\\lft\\release\\stest.bin", wrStartAddr, wrNumBlocks, &numByWrSuccess);
					obj.RdFileFromSdCard0(DeviceTypes::LFT_SPPU_DEV_FX3_SDCARD, "D:\\hp\\Projects\\SPPU_PROJECT\\sppu\\fx3\\src\\lft\\release\\rtest.bin" , wrStartAddr, wrNumBlocks, &numByRdSuccess);
					cout << "\r" << lc << endl;
					cout << "Enter any character to repear" << endl;
					getch();
				}

				break;
		case 8:				//Close device
				cout << "Close returned = " << obj.CloseDevice() << endl;
				break;
			case 9:				//Reset the device to power-on configuration	
	//				obj.UsbDevReset();		
				break;
			case 10:
				cout << "######## T E S T #########" << endl;
				cout << "Device Open Test" << endl;
#if 0
				wrSpiBinFile = fopen(WRITE_SPI_FILENAME, "rb");
				wcount = fread(spiBuf, 1, 4096, wrSpiBinFile);
				fclose(wrSpiBinFile);
				obj.Testing((void *)spiBuf);
#endif
				if(S_OK == obj.Testing(NULL))
					cout << "Device OPEN test: SUCCESS" << endl;
				else
					cout << "Device OPEN test: FAILURE" << endl;
				break;
			
			case 11:
				cout << "##### Memory Read #####" << endl;
				cout << "Enter Start Address" << endl;
				scanf("%lu", &wrStartAddr);
				cout << "Enter Number of Bytes to read" << endl;
				scanf("%lu", &wrNumBlocks);

				obj.RdMemFromSdCard0(DeviceTypes::LFT_SPPU_DEV_FX3_SDCARD, rdMemArr, wrStartAddr, wrNumBlocks, &numByWrSuccess);
				cout << "Successfully read " << numByWrSuccess << " bytes" << endl;

				wrBinFile = fopen(READ_DATA_FILE, "ab");
				rcount = fwrite(rdMemArr, 1, numByWrSuccess, wrBinFile);
				fclose(wrBinFile);
				break;
			case 12:
				cout << "##### Memory Write #####" << endl;
				cout << "Enter Start Address" << endl;
				scanf("%lu", &wrStartAddr);
				cout << "Enter Number of Bytes to write" << endl;
				scanf("%lu", &wrNumBlocks);

				rdBinFile = fopen(WRITE_DATA_FILE, "rb");
				wcount = fread(wrMemArr, 1, wrNumBlocks, rdBinFile);
				fclose(rdBinFile);

				obj.WrMemToSdCard0(DeviceTypes::LFT_SPPU_DEV_FX3_SDCARD, wrMemArr, wrStartAddr, wrNumBlocks, &numByWrSuccess);
				cout << "Successfully wrote " << numByWrSuccess << " bytes" << endl;
				break;
			case 13:
				cout << "    Update Firmware" << endl;
				cout << "    ---------------" << endl;
				cout << "Enter Device Type (5 = FX3 Flash, 8 = Fpga Flash)" << endl; 
				scanf("%d", &devType);
				obj.UpdateFirmWare((UsbApis::DEVICE_TYPES)devType, WRITE_SPI_FILENAME);
				break;
			case 14:
				cout << "    Reg Read" << endl;
				cout << "    --------" << endl;
				cout << "Enter register Address" << endl << "0x";
				cin >> std::hex >> regAddr;
				cout << "RegAddr = " << regAddr << endl;
				if(S_OK == obj.RegisterRead(regAddr, &regRdVal))
					cout << "Value Read at addr = 0x" << std::hex << regAddr << " is = 0x" << std::hex << regRdVal << endl;
				else
					cout << "Reg Read Error!" << endl;
				break;
			case 15:
				cout << "    Reg Write" << endl;
				cout << "    ---------" << endl;
				cout << "Enter register Address" << endl << "0x";
				cin >> std::hex >> regAddr;
				//scanf("%u", &regAddr);
				cout << "Enter value to Write" << endl << "0x";
				cin >> std::hex >> regWrVal;
				//scanf("%u", &regWrVal);
				cout << "RegAddr = " << regAddr << endl;
				cout << "RegVal  = " << regWrVal << endl;
				if(S_OK == obj.RegisterWrite(regAddr, regWrVal))
					cout << "Value Wrote at addr = 0x" << std::hex << regAddr << " is = 0x" << std::hex << regWrVal << std::dec << endl;
				else
					cout << "Reg Write Error" << endl;
				break;
			case 16:
				cout << "FW Debugging Enabled" << endl;
				break;
			case 17:
				cout << "FW Debugging Disabled" << endl;
				break;
			case 0:
	//			obj.CloseDevice();
				exit(0);
				break;
			default:
				cout << "Choice not recognized!" << endl;
		}
	}
#endif
	return 0;
}

#if 0			//not_so_good, DDR Write Middle function logic
	while(numByToWr)
	{
		
		if(numByToWr > MAX_NUM_BYTES_DDR_ONE_TIME)
			numByToWr = MAX_NUM_BYTES_DDR_ONE_TIME;

		rcount = fread((wDevBuf + 12), 1, LESS(numByToWr, (numByToWr - 12)), rdBinFile);
		if(rcount < 1)
		{
			#if DEBUG
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug << "ERROR : Unable to read from File! API Returned = " << rcount << endl;
			SppuUsbDllDebug.close();
			#endif
			break;
		}
		else /*if(rcount <= numByToWr)*/
		{
			memset((wDevBuf + 12 + rcount), '\0', ((MAX_NUM_BYTES_DDR_ONE_TIME - 12) - rcount));
		}
		outerLpCounter++;		//Increment counter only when data is available
		*(wDevBuf + 2) = ((numByToWr & 0xFF00) >> 8);
		*(wDevBuf + 3) = (numByToWr & 0xFF);


		#if DEBUG
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "ERROR : RCOUNT = " << rcount << endl;
		SppuUsbDllDebug.close();
		#endif

		if(S_OK != __WrFileToDdr(wDevBuf, (rcount /*numByToWr HP 201588*/ + 12), &numByWrSuccess))
		{
			#if DEBUG
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug << "ERROR : Write to DDR Failure" << endl;
			SppuUsbDllDebug.close();
			#endif
			break;
		}
		(*numBytesWrSuccess) += numByWrSuccess;
		numByToWr = lNumBytes - (*numBytesWrSuccess);
		if(lNumBytes == (*numBytesWrSuccess))
		{
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			
			SppuUsbDllDebug.close();
			break;
		}
	}
#endif

#if 0
	HRESULT UsbApis::c_UsbApis::_WrFileToDdr(char *fname, DWORD faddr, DWORD numBytes, DWORD *numBytesWrSuccess)
{
	HRESULT hRes = S_OK;
	DWORD lNumBytes = numBytes;
	DWORD numByWrSuccess = 0;
	DWORD laddr = faddr;
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
	}
	
	int rcount = 1;
	DWORD numByToWr = lNumBytes;
	unsigned char wDevBuf[MAX_NUM_BYTES_DDR_ONE_TIME + 1] = {'\0'};	
#if 0
	*(wDevBuf + 0) = *(lftSppuPacketFormatSend + 0);
	*(wDevBuf + 1) = *(lftSppuPacketFormatSend + 1);

	*(wDevBuf + 4) = *(lftSppuPacketFormatSend + 4);
	*(wDevBuf + 5) = 0x01;							//Write command
	*(wDevBuf + 6) = *(lftSppuPacketFormatSend + 6);
	*(wDevBuf + 7) = *(lftSppuPacketFormatSend + 7);

	*(wDevBuf + 8) = ((FPGA_DDR_ACCESS_ADDR & 0xFF000000) >> 24);
	*(wDevBuf + 9) = ((FPGA_DDR_ACCESS_ADDR & 0x00FF0000) >> 16);
	*(wDevBuf + 10) = ((FPGA_DDR_ACCESS_ADDR & 0x0000FF00) >> 8);
	*(wDevBuf + 11) = (FPGA_DDR_ACCESS_ADDR & 0x000000FF);
#endif
	DWORD outerLpCounter = 0;
#if 0
	#if DEBUG_STATUS
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "STATUS: Request of: " << numBytes << " byte transfer! Writing File Size: " << numByToWr << endl;
		SppuUsbDllDebug.close();
	#endif
#endif

	//	SendCommandEP0(&dummyBuf, 0, LFT_SPPU_SLAVE_FIFO_DMA_INIT, 0x0000, 0x0000, 0x0001);	//wLength = (0x0001 = DMA Init, 0x0000 = DMA Un-Init)) 
	time_t seconds_begin, seconds_end, seconds;
	seconds_begin = time (NULL);

	while(numByToWr)
	{
		if(numByToWr > MAX_NUM_BYTES_DDR_ONE_TIME)
			numByToWr = MAX_NUM_BYTES_DDR_ONE_TIME;

		rcount = fread(wDevBuf, 1, numByToWr, rdBinFile);
		if(rcount < 1)
		{
			#if DEBUG
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug << "ERROR : Unable to read from File! API Returned = " << rcount << endl;
			SppuUsbDllDebug.close();
			#endif
			break;
		}
		else /*if(rcount <= numByToWr)*/
		{
			memset((wDevBuf + rcount), '\0', (MAX_NUM_BYTES_DDR_ONE_TIME - rcount));
		}
		outerLpCounter++;		//Increment counter only when data is available
#if 0
		*(wDevBuf + 2) = (((numByToWr + LFT_SPPU_SLAVE_FIFO_HEADER_SIZE) & 0xFF00) >> 8);
		*(wDevBuf + 3) = ((numByToWr + LFT_SPPU_SLAVE_FIFO_HEADER_SIZE) & 0xFF);
#endif
		if(S_OK != __WrFileToDdr(wDevBuf, rcount, &numByWrSuccess))
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
	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
	SppuUsbDllDebug << std::dec << "PERFORMANCE : DDR Write (FILE) : " << endl;
	SppuUsbDllDebug << "\t" << *numBytesWrSuccess << " Bytes in " << seconds << " Seconds; ";
	SppuUsbDllDebug << "\t" << (*numBytesWrSuccess / seconds) << " Bytes/Sec; " ;
	SppuUsbDllDebug << "\t" << ((*numBytesWrSuccess / seconds) >> 10) << " (KBps); ";
	SppuUsbDllDebug << "\t" << ((((*numBytesWrSuccess / seconds) >> 10)) >> 10) << " (MBps); " << endl;
	SppuUsbDllDebug << "STATUS: In Outer loop : " << outerLpCounter << " times" << endl;
	SppuUsbDllDebug.close();
//	SendCommandEP0(&dummyBuf, 0, LFT_SPPU_SLAVE_FIFO_DMA_INIT, 0x0000, 0x0000, 0x0000);
#if DEBUG
	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
	SppuUsbDllDebug << "STATUS: Wrote in DDR : " << *numBytesWrSuccess << " Bytes, at address : "<< faddr << endl;
	SppuUsbDllDebug.close();
#endif
	fclose(rdBinFile);
	return S_OK;
}













HRESULT UsbApis::c_UsbApis::__WrFileToDdr(unsigned char *buf, DWORD bufSize, DWORD *numBytesWrSuccess)
{
	LONG length = 0;
	DWORD lBufSize = bufSize;
	DWORD NumByWrSuccess = 0;

	unsigned char buffer[LFT_SPPU_SLAVE_FIFO_XFER_BUF_SIZE + LFT_SPPU_SLAVE_FIFO_HEADER_SIZE] = {'\0'};

	*(buffer + 0) = *(lftSppuPacketFormatSend + 0);
	*(buffer + 1) = *(lftSppuPacketFormatSend + 1);

	*(buffer + 4) = *(lftSppuPacketFormatSend + 4);
	*(buffer + 5) = 0x01;							//Write command
	*(buffer + 6) = *(lftSppuPacketFormatSend + 6);
	*(buffer + 7) = *(lftSppuPacketFormatSend + 7);

	*(buffer + 8) = ((FPGA_DDR_ACCESS_ADDR & 0xFF000000) >> 24);
	*(buffer + 9) = ((FPGA_DDR_ACCESS_ADDR & 0x00FF0000) >> 16);
	*(buffer + 10) = ((FPGA_DDR_ACCESS_ADDR & 0x0000FF00) >> 8);
	*(buffer + 11) = (FPGA_DDR_ACCESS_ADDR & 0x000000FF);

	//Remove till first return statement
//	*numBytesWrSuccess = bufSize;
//	return S_OK;
	
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


#endif


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

#if 0
	if((*(lftSppuPacketFormatRecv + 0)) == (0xAA) && \
				(*(lftSppuPacketFormatRecv + 1)) == (0x88))
			{
				if((*(lftSppuPacketFormatRecv + 11)) == 0x00)
				{
					#if DEBUG_INFO
					SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
					SppuUsbDllDebug << "SUCCESS: Valid Response Status! = "<< *(lftSppuPacketFormatRecv + 11) << endl;
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
#endif