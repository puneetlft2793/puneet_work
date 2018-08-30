#ifndef _LFT_PCI_H_
#define _LFT_PCI_H_

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdio.h>
#include <BaseTsd.h>
#include<stdlib.h>		//for exit
#include<Windows.h>

#include <InitGuid.h>

using namespace std;

#define EXPORT	__declspec(dllexport)
#define USB_DLL_DEBUF_FILE_NAME ".\\PcieDebug.log"

#ifndef DEBUG_FILE
#define DEBUG_FILE	0
#define DEBUG_ERROR	0
#define DEBUG_INFO	0
#define DEBUG_PRINT_SUCCESS_IN_FILE	0
#endif

#define TLP_MAX_SIZE		32				// RRW - workaround until this value can be determined dynamically
#define MAX_DMA_TRANSFER	32768 / 4		// Maximum DMA transfer size in Words

namespace Pcie
{
	// Identifies the driver by its GUID in the WDM Model
	// {1E7A9C6F-8B14-4621-9F90-18F8ECA8DF56}
	static const GUID GuidDriver = 
	{ 0x1E7A9C6F, 0x8B14, 0x4621, { 0x9F, 0x90, 0x18, 0xF8, 0xEC, 0xA8, 0xDF, 0x56 } };

	typedef struct 
	{
		long	offset;
		long	writeControlCode;
		long	readControlCode;
		char  *	name;
	} RegisterInfo;


	// The structure used to hold data transfer information
	typedef struct _PCI_REGISTER_ACCESS {
		UINT32					Address;
		UINT32					Value;
	}PCI_REGISTER_ACCESS;

	typedef enum DEVICE_TYPES_PCI
	{
		LFT_SPPU_DEV_PCI_DAC1 = 0,
		LFT_SPPU_DEV_PCI_DAC2,
		LFT_SPPU_DEV_PCI_DAC3,
		LFT_SPPU_DEV_PCI_LMK04806,
		LFT_SPPU_DEV_PCI_FPGA,
		LFT_SPPU_DEV_PCI_FPGA_SPI_FLASH,
		LFT_SPPU_DEV_PCI_DDR,
		LFT_SPPU_DEV_PCI_FX3_RAM,
		LFT_SPPU_DEV_PCI_FX3_SPI_FLASH,
		LFT_SPPU_DEV_PCI_FX3_SDCARD,
		LFT_SPPU_DEV_PCI_ATTENUATOR,
		LFT_SPPU_DEVICE_PCI_COUNT
	}DeviceTypesPci;

	class c_Pcie
	{
	private:
		
		// Allocate user buffer space large enough to accomodate a 4K aligned starting point within the field.
		unsigned long	TLPReadBufferArea[MAX_DMA_TRANSFER + 4096];		// Buffer space for maximum DMA Read size
		unsigned long  *TLPReadBuffer;									// 4K aligned starting point (see constructor)
		unsigned long	TLPWriteBufferArea[MAX_DMA_TRANSFER + 4096];	// Buffer space for maximum DMA Write size
		unsigned long  *TLPWriteBuffer;									// 4K aligned starting point (see constructor)
		RegisterInfo	RegInfo[11];
		void			InitializeRegInfo();

	public:
		//Function Decelarations
		struct _PcieDev
		{
			BOOL IsOpen;				/* Flag to check Device open Status. */
			HANDLE hs3_1000;
		}PcieDev;
		ofstream SppuUsbDllDebug;

		EXPORT int OpenDevice();
		EXPORT HANDLE OpenDeviceByGuid(LPGUID pGuid);
		EXPORT int CloseDevice();

		EXPORT int RegisterRead(UINT32, UINT32 *);
		EXPORT int RegisterWrite(UINT32, UINT32);

		EXPORT int __RegisterRead(UINT32, UINT32 *);
		EXPORT int __RegisterWrite(UINT32, UINT32);

		EXPORT HRESULT FileRecv(
						DeviceTypesPci sppuDeviceTypes,
						char *fname, 
						DWORD addr, 
						DWORD numBytes,
						DWORD *numByRdSuccess);

		EXPORT HRESULT FileSend(
						DeviceTypesPci sppuDeviceTypes,
						char *fname, 
						DWORD addr, 
						DWORD numBytes, 
						DWORD *numByWrSuccess);

		EXPORT int DmaOpen(BOOL fPolling, char *fname, DWORD addr, DWORD numBy, DWORD *numBySuccess);
		EXPORT void DmaClose();
		
		int DmaWritePrepare();
		int DmaReadPrepare();

		c_Pcie()
		{
			unsigned long *pBuf;

			PcieDev.hs3_1000 = INVALID_HANDLE_VALUE;
			//InitializeRegInfo();

			// Calculate 4K aligned starting point within the read/write buffer areas
			// to use as our data starting point.  The DMA hardware requires that the
			// logical address of our map buffers be aligned on a 4K byte boundary, so
			// this is a compiler independent way of ensuring that.  Note that the 
			// HAL will ensure that when it allocates map buffers for System Scatter/Gather,
			// the alignment of these buffers will be the same as the user buffers
			// containing the original data (otherwise, we would have no way to force a 
			// particular alignment in the system-allocated map buffers).
			//
			// Note that the buffer areas were created as the maximum size required plus 4K bytes,
			// which is wasteful of memory but ensures that we will have an area 4K aligned within
			// each buffer area sufficiently large to contain the maximum amount of data.
			pBuf = TLPReadBufferArea;

			while ((unsigned long)pBuf % 0x1000 != 0)
				pBuf++;

			TLPReadBuffer = pBuf;

			pBuf = TLPWriteBufferArea;

			while ((unsigned long)pBuf % 0x1000 != 0)
				pBuf++;

			TLPWriteBuffer = pBuf;
		}

	};
}


#endif //_LFT_PCI_H_