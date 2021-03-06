/* This file contains  */

#ifndef _SPPU_PCI_LIB_H_
#define _SPPU_PCI_LIB_H_

#include <stdio.h>
#include <Windows.h>


#ifndef ENABLE_LOGGING
#define ENABLE_LOGGING		1			// Enable dissable logging from this dll.
#endif

#ifdef ENABLE_LOGGING
#define DEBUG_ERROR			1			// To print error in the log file.
#endif

#ifdef ENABLE_LOGGING
#define DEBUG_STATUS		1			// To print status in the log file.
#endif

#ifdef ENABLE_LOGGING
#define DEBUG_INFO			1			//Prints necessary info in Log File,
#endif

#if ENABLE_LOGGING
#define SPPU_PCI_DEBUG_FILE_PATH	"C:\\SppuPciLog\\SppuPciLib.log" //".\\SppuPciLib.log" //"C:\\SppuPciLog\\SppuPciLib.log" 
#endif

#ifdef __cplusplus
	extern "C" {
#endif

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


	HRESULT RegisterRead(
					UINT32 addr,
					UINT32 *val);

	HRESULT RegisterWrite(
					UINT32 addr,
					UINT32 val);

	HRESULT Testing(void *);
	HRESULT FileRecv(
					DeviceTypesPci sppuDeviceTypes,
					char *fname, 
					DWORD addr, 
					DWORD numBytes,
					DWORD *numByRdSuccess);

	HRESULT FileSend(
					DeviceTypesPci sppuDeviceTypes,
					char *fname, 
					DWORD addr, 
					DWORD numBytes, 
					DWORD *numByWrSuccess);


	HRESULT BufRecv(
					DeviceTypesPci sppuPciDeviceTypes,
					char *fname, 
					DWORD addr, 
					DWORD numBytes,
					DWORD *numByRdSuccess);

	 HRESULT BufSend(
					DeviceTypesPci sppuPciDeviceTypes,
					char *fname, 
					DWORD addr, 
					DWORD numBytes, 
					DWORD *numByRdSuccess);

	 HRESULT UpdateFirmWare(
					DeviceTypesPci Dev,
					char *fname);


	HRESULT OpenPciDevice();

	HRESULT ClosePciDevice();

	extern int test_main();

#ifdef	__cplusplus
}
#endif

#endif _SPPU_PCI_LIB_H_