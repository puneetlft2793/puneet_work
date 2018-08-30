#include "Pcie.h"
#include <time.h>

/* Handle to device information struct */
typedef void *WDC_DEVICE_HANDLE;
typedef UINT64 DMA_ADDR;
typedef UINT64 PHYS_ADDR;


enum 
{
    BIT0  = 0x00000001,
    BIT1  = 0x00000002,
    BIT2  = 0x00000004,
    BIT3  = 0x00000008,
    BIT4  = 0x00000010,
    BIT5  = 0x00000020,
    BIT6  = 0x00000040,
    BIT7  = 0x00000080,
    BIT8  = 0x00000100,
    BIT9  = 0x00000200,
    BIT10 = 0x00000400,
    BIT11 = 0x00000800,
    BIT12 = 0x00001000,
    BIT13 = 0x00002000,
    BIT14 = 0x00004000,
    BIT15 = 0x00008000,
    BIT16 = 0x00010000,
    BIT17 = 0x00020000,
    BIT18 = 0x00040000,
    BIT19 = 0x00080000,
    BIT20 = 0x00100000,
    BIT21 = 0x00200000,
    BIT22 = 0x00400000,
    BIT23 = 0x00800000,
    BIT24 = 0x01000000,
    BIT25 = 0x02000000,
    BIT26 = 0x04000000,
    BIT27 = 0x08000000,
    BIT28 = 0x10000000,
    BIT29 = 0x20000000,
    BIT30 = 0x40000000,
    BIT31 = (int)0x80000000
};

/* XBMD_MEMORY registers offsets */
enum {
	XBMD_MEMORY_DSCR_OFFSET = 0x0,
	XBMD_MEMORY_DDMACR_OFFSET = 0x4,
	XBMD_MEMORY_WDMATLPA_OFFSET = 0x8,
	XBMD_MEMORY_WDMATLPS_OFFSET = 0xc,
	XBMD_MEMORY_WDMATLPC_OFFSET = 0x10,
	XBMD_MEMORY_WDMATLPP_OFFSET = 0x14,
	XBMD_MEMORY_RDMATLPP_OFFSET = 0x18,
	XBMD_MEMORY_RDMATLPA_OFFSET = 0x1c,
	XBMD_MEMORY_RDMATLPS_OFFSET = 0x20,
	XBMD_MEMORY_RDMATLPC_OFFSET = 0x24,
	XBMD_MEMORY_WDMAPERF_OFFSET = 0x28,
	XBMD_MEMORY_RDMAPERF_OFFSET = 0x2c,
	XBMD_MEMORY_RDMASTAT_OFFSET = 0x30,
	XBMD_MEMORY_NRDCOMP_OFFSET = 0x34,
	XBMD_MEMORY_RCOMPDSIZE_OFFSET = 0x38,
	XBMD_MEMORY_DLWSTAT_OFFSET = 0x3c,
	XBMD_MEMORY_DLTRSSTAT_OFFSET = 0x40,
	XBMD_MEMORY_DMISCCONT_OFFSET = 0x44,
	WR0 = 0,
	WR48 = 0x48,
	WR4C = 0x4C,
	WR50 = 0x50,
	WR54 = 0x54,
	WR58 = 0x58,
	WR5C = 0x5c,
	WR60 = 0x60,
	WR64 = 0x64,
	WR68 = 0x68,
	WR6C = 0x6c,
	WR70 = 0x70,
	WR74 = 0x74,
	WR78 = 0x78,
	WR7C = 0x7c,
	WR80 = 0x80,
	WR84 = 0x84,
	WR88 = 0x88,
	WR8C = 0x8c,
};


#define MYFILE_BUFF_SIZE 4096

#pragma region FileDdrAccess
HRESULT Pcie::c_Pcie::FileRecv(DeviceTypesPci devType, char *fname, DWORD faddr, DWORD numBytes, DWORD *numByRdSuccess)
{
	unsigned long long begin_ms = 0x0, end_ms = 0x0, milliSeconds = 0x0, ByPerMilliSec = 0x0, ByPerSec = 0x0;
	
	if(OpenDevice())
		return -1;

	if(devType == 6/*DEVICE_TYPES_PCI::LFT_SPPU_DEV_PCI_DDR*/)
	{
		#if DEBUG_FILE
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "STATUS: Got a request for DDR Access" << endl;
		SppuUsbDllDebug.close();
		#endif
	}
	else
	{
		#if DEBUG_ERROR
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "ERROR : Unknown device selected. Device = " << devType << endl;
		SppuUsbDllDebug.close();
		#endif
		return -1;
	}

	begin_ms = GetTickCount64();

	if(S_OK != DmaOpen(FALSE, fname, faddr, numBytes, numByRdSuccess))
	{
		#if DEBUG_ERROR
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "ERROR : DMA Open and Transfer Failure!" << endl;
		SppuUsbDllDebug.close();
		#endif
	}
	end_ms = GetTickCount64();

	DmaClose();
	milliSeconds = end_ms - begin_ms;

	ByPerMilliSec = ((*numByRdSuccess) / milliSeconds);
	ByPerSec = ByPerMilliSec * 1000;

	//
	#if DEBUG_FILE
	

	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
	SppuUsbDllDebug << std::dec << "PERFORMANCE : DDR Read (FILE) : " << endl;
	SppuUsbDllDebug << "\t" << (*numByRdSuccess) << " Bytes in " << milliSeconds << " milli Seconds; ";
	SppuUsbDllDebug << "\t" << ByPerMilliSec << " B/ms; " ;
	SppuUsbDllDebug << "\t" << ByPerSec << " B/s; " ;
	SppuUsbDllDebug << "\t" << (ByPerSec >> 10) << " (KB/s); ";
	SppuUsbDllDebug << "\t" << ((ByPerSec >> 10) >> 10) << " (MB/s); " << endl;
	SppuUsbDllDebug.close();
	#endif

/*	ClosePciDevice();*/

	return S_OK;
}

HRESULT Pcie::c_Pcie::FileSend(DeviceTypesPci devType, char *fname, DWORD faddr, DWORD numBytes, DWORD *numByWrSuccess)
{
	unsigned long long begin_ms = 0x0, end_ms = 0x0, milliSeconds = 0x0, ByPerMilliSec = 0x0, ByPerSec = 0x0;
	DWORD numByRead = 0x0;
	*numByWrSuccess = 0x0;

	if(OpenDevice())
		return -1;

	if(devType == 6/*DEVICE_TYPES_PCI::LFT_SPPU_DEV_PCI_DDR*/)
	{
		#if DEBUG_FILE
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "STATUS: Got a request for DDR Access" << endl;
		SppuUsbDllDebug.close();
		#endif
	}
	else
	{
		#if DEBUG_ERROR
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "ERROR : Unknown device selected. Device = " << devType << endl;
		SppuUsbDllDebug.close();
		#endif
		return -1;
	}

	begin_ms = GetTickCount64();
	
	if(S_OK != DmaOpen(TRUE, fname, faddr, numBytes, &numByRead))
	{
		#if DEBUG_ERROR
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "ERROR : DMA Open and Transfer Failure!" << endl;
		SppuUsbDllDebug.close();
		#endif
	}
	end_ms = GetTickCount64();
	DmaClose();
	
	*numByWrSuccess = numByRead;

	milliSeconds = end_ms - begin_ms;

	//We have to add 900ms delay before sending any other file.
	//milliSeconds -= 900;

	#if DEBUG_FILE
	ByPerMilliSec = (numByRead / milliSeconds);
	ByPerSec = ByPerMilliSec * 1000;

	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
	SppuUsbDllDebug << std::dec << "PERFORMANCE : DDR Write (FILE) : " << endl;
	SppuUsbDllDebug << "\t" << numByRead << " Bytes in " << milliSeconds << " milli Seconds; ";
	SppuUsbDllDebug << "\t" << ByPerMilliSec << " B/ms; " ;
	SppuUsbDllDebug << "\t" << ByPerSec << " B/s; " ;
	SppuUsbDllDebug << "\t" << (ByPerSec >> 10) << " (KB/s); ";
	SppuUsbDllDebug << "\t" << ((ByPerSec >> 10) >> 10) << " (MB/s); " << endl;
	SppuUsbDllDebug.close();
	#endif

/*	ClosePciDevice(); */
//	CloseDevice();

	return S_OK;
}
#pragma endregion FileDdrAccess


/* -----------------------------------------------
	LFT defined Function : Prints time in milliseconds
	----------------------------------------------- */
void PrintTime()
{
#if 0
	SYSTEMTIME st;
	GetSystemTime(&st);
	printf("Current Time Sec Milli = %llu  %llu \n", (long long unsigned int)st.wSecond, (long long unsigned int)st.wMilliseconds);
	return;
#endif
}


/* Open DMA */
int Pcie::c_Pcie::DmaOpen(BOOL fPolling, char *fname, DWORD addr, DWORD numBy, DWORD *numBySuccess)
{
#if 1
	DWORD dwStatus, dwOptions, dwNumItems, i;
	WORD wTLPNumItems, wNumTLPs;
	UINT32 u32Pattern;
	BOOL fIsRead;
//	BOOL fIsRead, fEnable64bit;
//	BYTE bTrafficClass;
	FILE *MyFile, *MyFileOut, *XbmdLog;
	unsigned int MyFileSize, FileSize;
	struct stat st;
	DWORD lv;
	int lv2, ret, rcount, wcount, LoopCount;
//	char rbuff[MYFILE_BUFF_SIZE];
//	char wbuff[MYFILE_BUFF_SIZE];

	char LogBuffer[100];
	UINT32 RegValue;
	unsigned int FileSizeRoundOff = 0;
	
	// BMD Register Variables
	unsigned int DmaCrRegWr = 0x00000000;   // contains lower 16 bits of DMACR reg used to verify success WR DMA trans
	unsigned int DmaCrRegRd = 0x00000000;   // contains lower 16 bits of DMACR reg used to verify success RD DMA trans
	unsigned int DmaCrReg = 0x00000000;      // contains all 32 bits of DMACR reg
	int ch = 0;

	wNumTLPs = 65535;
	u32Pattern = 0xbabebabe;
	dwOptions = fPolling;

	/* HP */
	MyFileSize = numBy;

	if(fPolling == TRUE)
			fIsRead = TRUE;
	else if(fPolling == FALSE)
			fIsRead = FALSE;
	else
	{
		#if DEBUG_FILE____
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "STATUS: Got a request for DDR Access" << endl;
		SppuUsbDllDebug.close();
		#endif
		#if DEBUG_ERROR
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "ERROR : Un-supported request. Req = " << fPolling << endl;
		SppuUsbDllDebug.close();
		#endif
		//printf("Request neither for Read or Write\n");
		return -1;
	}
	
	#if DEBUG_FILE
	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
	SppuUsbDllDebug << "STATUS: fIsRead = " << fIsRead << endl;
	SppuUsbDllDebug.close();
	#endif
	
	/* The BMD reference design does not support Scatter/Gather DMA, so we use
	 * contiguous buffer DMA */
	
	// __HP__ dwOptions |= DMA_KERNEL_BUFFER_ALLOC;
	dwOptions |= 0x1;

	__RegisterWrite(XBMD_MEMORY_WDMATLPC_OFFSET, 32);
	__RegisterWrite(XBMD_MEMORY_WDMATLPS_OFFSET, 32);
	__RegisterWrite(XBMD_MEMORY_RDMATLPC_OFFSET, 32);
	__RegisterWrite(XBMD_MEMORY_RDMATLPS_OFFSET, 32);


	/* Calculate the DMA TLP (payload packet) size, in units of UINT32 */
	wTLPNumItems = 32;// Hack rohit

	/* Calculate the total DMA transfer size, in units of UINT32 */
	dwNumItems = (DWORD)wNumTLPs * (DWORD)wTLPNumItems;

	//LFT bin file write hook
	//TODO : Check if file does not exists then create it.
	if(1 == fIsRead)
	{
		/* if (!(MyFile = fopen(MyFileName, "rb"))) {		HP */
		if (!(MyFile = fopen(fname, "rb"))) {
			#if DEBUG_ERROR
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug << "ERROR : Unable To Open File. FileName = " << fname << endl;
			SppuUsbDllDebug.close();
			#endif
			//__HP__ DmaClose(pciDev.hDev, &pciDev.hDma);
			DmaClose();
			return -1;
		}

		/* Get file size */
		fseek(MyFile, 0, SEEK_END);
		FileSize = ftell(MyFile);
		fseek(MyFile, 0, SEEK_SET);

		/* If asked to write 0 Bytes or more data than present in file, write available data; HP 12/7/2015. */
		if((0 == numBy) || (numBy > FileSize))
			MyFileSize = FileSize;
	}

	LoopCount = MyFileSize / MYFILE_BUFF_SIZE;
	FileSizeRoundOff = MyFileSize % MYFILE_BUFF_SIZE;

	if (FileSizeRoundOff != 0) MyFileSize += (MYFILE_BUFF_SIZE - FileSizeRoundOff);

	//	printf("File Size = %d\n", MyFileSize);
	#if DEBUG_FILE
	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
	SppuUsbDllDebug << "STATUS: File Size = " << FileSize << ". Request for bytes xfer = " << numBy << ". Transferring  bytes = " << MyFileSize << endl;
	SppuUsbDllDebug.close();
	#endif

	DmaCrReg = DmaCrRegRd | 65536;

	/* Disable DMA interrupts for our Driver*/
	//__HP__ XBMD_MEMORY_DmaIntDisable(hDev, fIsRead);
	{
		 UINT32 ddmacr = 0x0;
		__RegisterRead(XBMD_MEMORY_DDMACR_OFFSET, &ddmacr);

		ddmacr |= fIsRead ? BIT23 : BIT7;
		__RegisterWrite(XBMD_MEMORY_DDMACR_OFFSET, ddmacr);
	}
	__RegisterWrite(0x48, 0x100);

	if(fIsRead)
		DmaWritePrepare();
	else
		DmaReadPrepare();

	__RegisterWrite(XBMD_MEMORY_DSCR_OFFSET, 3);
	__RegisterWrite(XBMD_MEMORY_DSCR_OFFSET, 0);
	__RegisterWrite(0x50, 4 | (1 << 11));
	__RegisterRead(0x50, &RegValue);
	__RegisterWrite(0x6c, 0);
	__RegisterWrite(0x70, 0x01000000);
	__RegisterWrite(0x74, MyFileSize);


	__RegisterWrite(0x48, 0x100);
	__RegisterRead(0x48, &RegValue);

	#if DEBUG_FILE
	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
	SppuUsbDllDebug << "STATUS: WriteBuf Addr = 0x" << std::hex << TLPWriteBuffer << ". ReadBuf Addr = 0x" << TLPReadBuffer << std::dec << endl;
	SppuUsbDllDebug.close();
	#endif

	PrintTime();
	//for loop here to get data from file in chunks of 4096
	if (fIsRead)	// Write to DDR DILEEP
	{

		Sleep(900);				//HP this is a work-around. seems some logical bug that needed to be taken care of.
		__RegisterWrite(0x84, 0x00000210);
		__RegisterWrite(0x84, 0x00000010);

		for (lv = 0; lv < MyFileSize; lv += 4096)
		{
			//__HP__4: Sleep(1);
		
			/* Prepare the device registers for DMA transfer */
			__RegisterWrite(0, 3);
			__RegisterWrite(0, 0);
				
			if ((rcount = fread((char *)(TLPWriteBuffer), 1, MYFILE_BUFF_SIZE, MyFile)) != MYFILE_BUFF_SIZE)
			{
				//break;				
			}

			__RegisterWrite(XBMD_MEMORY_DDMACR_OFFSET, fIsRead ? 0x10000 : 0x1);

			__RegisterRead(0x50, &RegValue);
			while (((RegValue & 0x02000000) == 0x00000000) || (RegValue == 0xFFFFFFFF))
			{
				__RegisterRead(0x50, &RegValue);
			}
			__RegisterWrite(0x50, (4 | (1 << 11) | (0x1 << 5)));
			__RegisterWrite(0x50, (4 | (1 << 11)));
			__RegisterWrite(XBMD_MEMORY_DDMACR_OFFSET, 0);
		}//End of DMA for loop
		PrintTime();
		//Close File when done
		fclose(MyFile);
#if 0
		#if !DEBUG_STATUS
		{
			int i = 0;
			SppuPciLogFile = fopen(SPPU_PCI_DEBUG_FILE_PATH, "a+");
			for (i = 0; i < 0x88; i += 4)
			{
				RegValue = XBMD_MEMORY_ReadReg32(hDev, i);
				sprintf(glLogBuff, "STATUS: Reg = %2i,0x%2x = 0x%8x\n", i / 4, i, RegValue);
				fwrite(glLogBuff, 1, strlen(glLogBuff), SppuPciLogFile);
				memset(glLogBuff, '\0', MYFILE_BUFF_SIZE);
				printf(" Reg = %2i,0x%2x = 0x%8x\n", i / 4, i, RegValue);
			}
			fclose(SppuPciLogFile);
		}
#		endif
#endif
	}
	else // READ FROM DDR DILEEP
	{
		if (!(MyFileOut = fopen(fname, "wb"))) {
			#if DEBUG_ERROR_
			SppuPciLogFile = fopen(SPPU_PCI_DEBUG_FILE_PATH, "a+");
			sprintf(glLogBuff, "ERROR : OPEN Binary TO Write Failure.\n");
			fwrite(glLogBuff, 1, strlen(glLogBuff), SppuPciLogFile);
			memset(glLogBuff, '\0', MYFILE_BUFF_SIZE);
			fclose(SppuPciLogFile);
			#endif
			//__HP__ DmaClose(pciDev.hDev, &pciDev.hDma);
			DmaClose();
			return -1;
		}

		memset(LogBuffer, '\0', 100);
		__RegisterWrite(0x78, 0);
		__RegisterRead(0x78, &RegValue);
		#if DEBUG_DEBUG_
		SppuPciLogFile = fopen(SPPU_PCI_DEBUG_FILE_PATH, "a+");
		sprintf(glLogBuff, "STATUS: Reg 0x78 = %x\n", RegValue);
		fwrite(glLogBuff, 1, strlen(glLogBuff), SppuPciLogFile);
		memset(glLogBuff, '\0', MYFILE_BUFF_SIZE);
		fclose(SppuPciLogFile);
		#endif

		__RegisterWrite(0x7c, 0x01000000);
		__RegisterRead(0x7c, &RegValue);
		#if DEBUG_DEBUG_
		SppuPciLogFile = fopen(SPPU_PCI_DEBUG_FILE_PATH, "a+");
		sprintf(glLogBuff, "STATUS: Reg 0x7c = %x\n", RegValue);
		fwrite(glLogBuff, 1, strlen(glLogBuff), SppuPciLogFile);
		memset(glLogBuff, '\0', MYFILE_BUFF_SIZE);
		fclose(SppuPciLogFile);
		#endif

		__RegisterWrite(0x80, MyFileSize);
		__RegisterRead(0x80, &RegValue);
		#if DEBUG_DEBUG_
		SppuPciLogFile = fopen(SPPU_PCI_DEBUG_FILE_PATH, "a+");
		sprintf(glLogBuff, "STATUS: Reg 0x80 = %x\n", RegValue);
		fwrite(glLogBuff, 1, strlen(glLogBuff), SppuPciLogFile);
		memset(glLogBuff, '\0', MYFILE_BUFF_SIZE);
		fclose(SppuPciLogFile);
		#endif

		__RegisterWrite(0x84, 0x00000810);
		__RegisterWrite(0x84, 0x00000010);

		DmaCrReg = 1;	//xbmd_descriptors.wr_enable

		for (lv2 = 0; lv2 < MyFileSize; lv2 += MYFILE_BUFF_SIZE)
		{
			/* Prepare the device registers for DMA transfer */
			__RegisterWrite(0, 3);
			__RegisterWrite(0, 0);

			__RegisterWrite(0x88, 1);
			__RegisterWrite(0x88, 0);

//__HP__	XBMD_MEMORY_DmaSyncCpu(pDma->hDma);
			__RegisterWrite(XBMD_MEMORY_DDMACR_OFFSET, DmaCrReg);

			__RegisterRead(0x50, &RegValue);
			while (((RegValue & 0x01000000) == 0x00000000) || (RegValue == 0xFFFFFFFF))
			{
				__RegisterRead(0x50, &RegValue);
			}
			__RegisterWrite(0x50, (4 | (1 << 11) | (0x1 << 4)));
			__RegisterWrite(0x50, (4 | (1 << 11)));
			
			__RegisterWrite(XBMD_MEMORY_DDMACR_OFFSET, 0);
			if (lv2 == (MyFileSize - MYFILE_BUFF_SIZE))
			{
				if (FileSizeRoundOff == 0) FileSizeRoundOff = MYFILE_BUFF_SIZE;
				if ((wcount = fwrite((char *)(TLPReadBuffer), 1, FileSizeRoundOff, MyFileOut)) != FileSizeRoundOff)
				{
					break;
				}
			}
			else
			{
				if ((wcount = fwrite((char *)(TLPReadBuffer), 1, MYFILE_BUFF_SIZE, MyFileOut)) != MYFILE_BUFF_SIZE)
				{
					break;
				}
			}
		}

		__RegisterWrite(XBMD_MEMORY_DDMACR_OFFSET, 0);
		fclose(MyFileOut);
		PrintTime();
	}
	*numBySuccess = MyFileSize;

	#if DEBUG_FILE
	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
	SppuUsbDllDebug << "STATUS: lv = 0x" << std::hex << lv << ". lv/4096 = 0x" << (lv/MYFILE_BUFF_SIZE) << std::dec << endl;
	SppuUsbDllDebug.close();
	#endif

#endif
	return S_OK;

Error:
	DmaClose();
}

/* Close DMA */
void Pcie::c_Pcie::DmaClose()
{

#if 0
	DWORD dwStatus;

	if (!pDma)
		return;

	/* Disable DMA interrupts */
	if (XBMD_MEMORY_IntIsEnabled(hDev))
	{
		dwStatus = XBMD_MEMORY_IntDisable(hDev);
		printf("DMA interrupts disable%s\n",
			(WD_STATUS_SUCCESS == dwStatus) ? "d" : " failed");
	}

	if (pDma->hDma)
	{
		/* Close the device's DMA handle */
		XBMD_MEMORY_DmaClose(pDma->hDma);
		printf("DMA closed (handle 0x%p)\n", pDma->hDma);
	}

	BZERO(*pDma);
#endif
}


int Pcie::c_Pcie::DmaWritePrepare(/*long size, long count, long pattern, long *status*/)
{
	UINT32			addr;				// Address of memory buffer
	
	ULONG			nTransfer;				// bytes read/written
	OVERLAPPED		asyncRead;				// Required structure for asynchronous file operations
	DWORD			lastError;			// Error code returned from Read File operation
	 /* Assert Initiator Reset */
    __RegisterWrite(XBMD_MEMORY_DSCR_OFFSET, 0x3);

    /* De-assert Initiator Reset */
    __RegisterWrite(XBMD_MEMORY_DSCR_OFFSET, 0x0);

	#if DEBUG_FILE
	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
	SppuUsbDllDebug << "<==== In DmaWritePrepare() ====>" << endl;
	SppuUsbDllDebug.close();
	#endif


	memset(TLPWriteBuffer, 0, sizeof(TLPWriteBuffer));		// Clear our target buffer on the host

	// Set the host address register to the Virtual Address of our user buffer.  This is NOT the
	// actual address that will be used by the DMA Device - it requires a logical address (this is
	// actually the address of a set of contiguous memory locations set up by the OS to hold a 
	// copy of the user buffer, translated to the device address space).  The value set in this
	// register will be accessed later by the driver and converted to the logical address required.
	addr = (unsigned long) TLPWriteBuffer;

	__RegisterWrite(XBMD_MEMORY_RDMATLPA_OFFSET, addr);


	//__HP__2 : 
	//Initialize the read DMA,
	{
		// Set up a contiguous area (System Scatter/Gather) for our user buffer.  This relieves us from the
		// responsibility of gathering up all the different pieces of physical memory which comprise our
		// user buffer in virtual memory, and then programming the DMA engine multiple times to transfer each
		// segment.
		// Note that this does NOT actually kick off the DMA engine - because we have a Bus Master device,
		// that is done later via the StartDMA function.
		asyncRead.Offset = 0;				// Start transfer at the beginning of the file
		asyncRead.OffsetHigh = 0;			// We don't need this, and I don't understand it anyway
		asyncRead.hEvent = 0;				// We don't need a signal event, the device will signal us

		if (!ReadFile(PcieDev.hs3_1000, TLPWriteBuffer, MYFILE_BUFF_SIZE, &nTransfer, &asyncRead))
		{
			lastError = GetLastError();
			if(lastError != ERROR_IO_PENDING)
			{
				#if DEBUG_ERROR
				SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
				SppuUsbDllDebug << "ERROR : ReadFile(). BytesReadSuccessfully = " << nTransfer << "ERROR CODE = 0x" << std::hex << GetLastError() << std::dec << endl;
				SppuUsbDllDebug.close();
				#endif
				return -1;
			}
		}
		else
		{
			#if DEBUG_FILE
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug << "SUCCESS: ReadFile()" << endl;
			SppuUsbDllDebug.close();
			#endif
		}

	}

	return S_OK;
}

int Pcie::c_Pcie::DmaReadPrepare(/*long size, long count, long pattern, long *status*/)
{
	UINT32			addr;				// Address of memory buffer
	ULONG			nTransfer;			// bytes read/written
	OVERLAPPED		asyncWrite;			// Required structure for asynchronous file operations
	DWORD			lastError;			// Error code returned from Write File operation
	 
	/* Assert Initiator Reset */
    __RegisterWrite(XBMD_MEMORY_DSCR_OFFSET, 0x3);

    /* De-assert Initiator Reset */
    __RegisterWrite(XBMD_MEMORY_DSCR_OFFSET, 0x0);

	// Set the host address register to the Virtual Address of our user buffer.  This is NOT the
	// actual address that will be used by the DMA Device - it requires a logical address (this is
	// actually the address of a set of contiguous memory locations set up by the OS to hold a 
	// copy of the user buffer, translated to the device address space).  The value set in this
	// register will be accessed later by the driver and converted to the logical address required.
	addr = (unsigned long) TLPReadBuffer;

	__RegisterWrite(XBMD_MEMORY_WDMATLPA_OFFSET, addr);

	{
		asyncWrite.Offset = 0;				// Start transfer at the beginning of the file
		asyncWrite.OffsetHigh = 0;			// We don't need this, and I don't understand it anyway
		asyncWrite.hEvent = 0;				// We don't need a signal event, the device will signal us

		// The DMA device we are ultimately communicating with in this call is capable of simultaneous
		// reads and writes.  On success, this function will return an error code indicating that the
		// requested operation is PENDING.  This allows the application to continue and program another
		// file operation.  This is possible because when we created the device object with CreateFile, 
		// the FILE_FLAG_OVERLAPPED attribute was specified.  That forces us to provide the asyncWrite
		// structure on the file operation call, but has the distinct advantage that it DOES NOT BLOCK
		// as it would if we did not specify overlapped operation.
		if (!WriteFile(PcieDev.hs3_1000, TLPReadBuffer, MYFILE_BUFF_SIZE, &nTransfer, &asyncWrite))
		{
			lastError = GetLastError();
			if(lastError != ERROR_IO_PENDING)
			{
				#if DEBUG_ERROR
				SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
				SppuUsbDllDebug << "ERROR : WriteFile(). BytesWrittenSuccessfully = " << nTransfer << "ERROR CODE = 0x" << std::hex << GetLastError() << std::dec << endl;
				SppuUsbDllDebug.close();
				#endif
				return -1;
			}
		}
	}

#if 0
	ULONG			addr;				// Address of memory buffer
	unsigned long *	idx;				// pointer into read buffer
	ULONG			nTransfer;			// bytes read/written
	OVERLAPPED		asyncRead;			// Required structure for asynchronous file operations
	DWORD			lastError;			// Error code returned from Read File operation

	if (PcieDev.hs3_1000 && PcieDev.hs3_1000 != INVALID_HANDLE_VALUE)
	{
		*status = 0;											// Assume success for now

		// Set the host address register to the Virtual Address of our user buffer.  This is NOT the
		// actual address that will be used by the DMA Device - it requires a logical address (this is
		// actually the address of a set of contiguous memory locations set up by the OS to hold a 
		// copy of the user buffer, translated to the device address space).  The value set in this
		// register will be accessed later by the driver and converted to the logical address required.
		addr = (unsigned long) TLPReadBuffer;

		// Set the host address register to the Virtual Address of our user buffer.  This is NOT the
		// actual address that will be used by the DMA Device - it requires a logical address (this is
		// actually the address of a set of contiguous memory locations set up by the OS to hold a 
		// copy of the user buffer, translated to the device address space).  The value set in this
		// register will be accessed later by the driver and converted to the logical address required.
		*status = SetRegister(READ_ADDR_OFFSET, addr);

		if (*status != 0)
			return S_OK;		// Failure to set and verify register

		// Set the DMA Read TLP size register with the value specified in the GUI.  Return if the
		// register cannot be written and verified.  
		*status = SetRegister(READ_SIZE_OFFSET, size);

		if (*status != 0)
			return S_OK;		// Failure to set and verify register

		// Set the DMA Read count register with the the value specified in the GUI.  Return if the
		// register cannot be written and verified.
		*status = SetRegister(READ_COUNT_OFFSET, count);

		if (*status != 0)
			return S_OK;		// Failure to set and verify register

		// Set the DMA Read pattern register with the value specified in the GUI.  Return if the
		// register cannot be written and verified.
		*status = SetRegister(READ_PATTERN_OFFSET, pattern);

		if (*status != 0)
			return S_OK;		// Failure to set and verify register

		// Fill our Read buffer on the host with the expected pattern.
		for (idx = TLPReadBuffer; idx < TLPReadBuffer + MAX_DMA_TRANSFER; idx++)
			*idx = (unsigned long)pattern;

		Operation = (Operation == write) ? readwrite : read;

		// Set up a contiguous area (System Scatter/Gather) for our user buffer.  This relieves us from the
		// responsibility of gathering up all the different pieces of physical memory which comprise our
		// user buffer in virtual memory, and then programming the DMA engine multiple times to transfer each
		// segment.
		// Note that this does NOT actually kick off the DMA engine - because we have a Bus Master device,
		// that is done later via the StartDMA function.
		asyncRead.Offset = 0;				// Start transfer at the beginning of the file
		asyncRead.OffsetHigh = 0;			// We don't need this, and I don't understand it anyway
		asyncRead.hEvent = 0;				// We don't need a signal event, the device will signal us

		// The DMA device we are ultimately communicating with in this call is capable of simultaneous
		// reads and writes.  On success, this function will return an error code indicating that the
		// requested operation is PENDING.  This allows the application to continue and program another
		// file operation.  This is possible because when we created the device object with CreateFile, 
		// the FILE_FLAG_OVERLAPPED attribute was specified.  That forces us to provide the asyncWrite
		// structure on the file operation call, but has the distinct advantage that it DOES NOT BLOCK
		// as it would if we did not specify overlapped operation.
		if (ReadFile(hs3_1000, TLPReadBuffer, size * count * sizeof(ULONG), &nTransfer, &asyncRead) == 0)
		{
			lastError = GetLastError();

			if (lastError != ERROR_IO_PENDING)
			{
				SetLastError(lastError);
				GetSystemMessage();
				Fire_DisplayMessage(_bstr_t("Cannot perform BMDMA Read System Scatter/Gather.  Press OK for OS info."), MY_NAME);
				Fire_DisplayMessage(_bstr_t((LPCTSTR)SystemMessage), MY_NAME);
				*status = 1;

				return S_OK;
			}
		}
	}

	else
	{
		Fire_DisplayMessage(_bstr_t("Cannot perform DMA Read set up.  PCIe Device Driver has been stopped."), MY_NAME);
		*status = 1;
	}
#endif
	return S_OK;
}


