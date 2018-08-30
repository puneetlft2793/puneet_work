#include "Pcie.h"
#include "PcieIoctrl.h"

#ifndef DO_NOT_CARE
#define DO_NOT_CARE			0x0
#endif

#define LFT_SPPU_SLAVE_FIFO_XFER_BUF_SIZE	0x40//0x3FF4		////0xC7FF4//0x3FF4//(0x40000 - 0xc)//4097//1024
#define LFT_SPPU_SLAVE_FIFO_HEADER_SIZE		0xC
#define FPGA_SPI_FLASH_ACCESS_ADDR			0x00004204 

#define PCI_CONTROL_REG_ADDR	0x0108
#define PCI_READ_REG_ADDR		0x0104
#define PCI_WRITE_REG_ADDR		0x0100

UINT32 lftSppuPacketFormatRecv[2] = 
{
	0xAA880010,		/* 2 bytes for Magic Number */ /* 2 bytes for length of data + this header */
	0x00020000,		/* 0x01 = Reg Write; 0x02 = Reg Read */
};

UINT32 lftSppuPacketFormatSend[2] = 
{
	0xCC770010,		/* 2 bytes for Magic Number */ /* 2 bytes for length of data + this header */
	0x00010000,		/* 0x01 = Reg Write; 0x02 = Reg Read */
};

#pragma region Lowest_Reg_interface

/*
Lowest level API that interacts with Driver for communication with driver.
Must be called directly, only to program BMD registers (0x00 to 0x44)
*/
int Pcie::c_Pcie::__RegisterRead(UINT32 Address, UINT32 *Value)
{
	ULONG	nOutput;				// bytes returned from IO ctrl call
	UINT32 regValue = 0x00;
	PCI_REGISTER_ACCESS io = {Address, 0x0};

	if((Address < 0x0) || (Address > 0x3FF))
	{
		#if DEBUG_FILE
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "ERROR: Invalid Offset : 0x" << std::hex << Address << std::dec << endl;
		SppuUsbDllDebug << "INFO : Valid offset   : 0x0 - 0x3FF" << endl;
		SppuUsbDllDebug.close();
		#endif
		return -1;
	}

	if(OpenDevice())
		return -1;

	if (PcieDev.hs3_1000 && (PcieDev.hs3_1000 != INVALID_HANDLE_VALUE))
	{
		if(!DeviceIoControl(PcieDev.hs3_1000, 
							IOCTL_LFT_SPPU_REG_RD, 
							&io,
							sizeof(io),
							&io,
							sizeof(io),
							&nOutput,
							NULL))
		{
			#if DEBUG_FILE
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug << "FAILURE DeviceIoControl(). Error = " << GetLastError() << endl;
			SppuUsbDllDebug.close();
			#endif
			return -2;
		}
		*Value = io.Value;
	}
	else
	{
		#if DEBUG_FILE
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "FAILURE Cannot read Register when the Device Driver is not running." << endl;
		SppuUsbDllDebug.close();
		#endif
	}
#if DEBUG_PRINT_SUCCESS_IN_FILE
	else
	{
		#if DEBUG_FILE
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "Success : Register Read (BMD): Address = 0x" << std::hex << Address << "; Vlaue = 0x" << *Value << std::dec << endl;
		SppuUsbDllDebug.close();
		#endif
	}
#endif
	return S_OK;
}

/*
Lowest level API that interacts with Driver for communication with driver.
Must be called directly, only to program BMD registers (0x00 to 0x44)
*/
int Pcie::c_Pcie::__RegisterWrite(UINT32 Address, UINT32 Value)
{
	ULONG	nOutput;				// bytes returned from IO ctrl call
	UINT32 regValue = 0x00;
	PCI_REGISTER_ACCESS io = {Address, Value};

	if((Address < 0x0) || (Address > 0x3FF))
	{
		#if DEBUG_FILE
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "ERROR: Invalid Offset : 0x" << std::hex << Address << std::dec << endl;
		SppuUsbDllDebug << "INFO : Valid offset   : 0x0 - 0x3FF" << endl;
		SppuUsbDllDebug.close();
		#endif
		return -1;
	}

	if(OpenDevice())
		return -1;

	if (PcieDev.hs3_1000 && (PcieDev.hs3_1000 != INVALID_HANDLE_VALUE))
	{
		if(!DeviceIoControl(PcieDev.hs3_1000, 
							IOCTL_LFT_SPPU_REG_WR, 
							&io,
							sizeof(io),
							&io,
							sizeof(io),
							&nOutput,
							NULL))
		{
			#if DEBUG_FILE
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug << "FAILURE DeviceIoControl(). Error = " << GetLastError() << endl;
			SppuUsbDllDebug.close();
			#endif
			return -2;
		}
	}
#if DEBUG_PRINT_SUCCESS_IN_FILE
	else
	{
		#if DEBUG_FILE
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "Success : Register Write (BMD): Address = 0x" << std::hex << Address << "; Value = 0x" << Value << std::dec << endl;
		SppuUsbDllDebug.close();
		#endif
	}
#endif
	return S_OK;
}
#pragma endregion Lowest_Reg_interface


/*
Lowest level API that interacts with Driver for communication with driver.
Must be called to program SPPU registers (0x100, 0x014, 0x108)
*/
int Pcie::c_Pcie::RegisterRead(UINT32 Address, UINT32 *Value)
{
	UINT32 lVal = 0;
	UINT32 readValue = 0x0;
	unsigned char lv = 0x0, successFlag = 0x0;

	*Value = 0;
	
/*	if(OpenPciDevice())
		return -1;
		*/
	//Send command
	__RegisterWrite(PCI_WRITE_REG_ADDR, lftSppuPacketFormatSend[0]);
	__RegisterWrite(PCI_WRITE_REG_ADDR, lftSppuPacketFormatRecv[1]);
	__RegisterWrite(PCI_WRITE_REG_ADDR, Address);
	__RegisterWrite(PCI_WRITE_REG_ADDR, DO_NOT_CARE);

	readValue = 0;

	for(lv = 0; lv < 4; lv++)
	{
		//Poll till value in control register = 0x1;
		if(lv < 3)
		{
			do
			{
				__RegisterRead(PCI_CONTROL_REG_ADDR, &readValue);
				readValue &= 0x1;
				//Sleep(1);
			}while(0x1 != readValue);
		}

		//Read the FPGA_Read register for status.
		 __RegisterRead(PCI_READ_REG_ADDR, &readValue);

		//printf("Reg val = 0x%x\n", readValue);
		if((0x2 == lv) && (0x0 == readValue))
			successFlag = 0x1;

//		printf("LV = %d, regval = 0x%x\n", lv, readValue);
/*		#if DEBUG_FILE
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "LV = " << lv << " Address = 0x" << std::hex << Address << " Value = 0x" << readValue << std::dec << endl;
		SppuUsbDllDebug.close();
		#endif
		*/

		//Clear the control register.
		__RegisterWrite(PCI_CONTROL_REG_ADDR, 0x0);
		__RegisterWrite(PCI_CONTROL_REG_ADDR, 0x1);

		if(0x3 == lv)
		{
			//dileep harpreet dummy read
			//readValue = XBMD_MEMORY_ReadReg32(pciDev.hDev, PCI_READ_REG_ADDR);
			*Value = readValue;
		}
	}

/*	ClosePciDevice(); */

	//Error checking
	if(!successFlag)
	{
		#if DEBUG_ERROR
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "ERROR : Register Read() : Invalid response Status" << endl;
		SppuUsbDllDebug.close();
		#endif
		return -2;
	}
	
	// Success Case
	#if DEBUG_INFO
	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
	SppuUsbDllDebug << "Success : Register Read (SPPU) Address = 0x" << std::hex << Address << "; Value = 0x" << *Value << std::dec << endl;
	SppuUsbDllDebug.close();
	#endif

	return S_OK;
}


/*
Lowest level API that interacts with Driver for communication with driver.
Must be called to program SPPU registers (0x100, 0x014, 0x108)
*/
int Pcie::c_Pcie::RegisterWrite(UINT32 Address, UINT32 Value)
{
	UINT32 readValue = 0x0;
	unsigned char lv = 0x0, successFlag = 0x0;

/*	if(OpenPciDevice())
		return -1;
		*/
	//Send command
	__RegisterWrite(PCI_WRITE_REG_ADDR, lftSppuPacketFormatSend[0]);
	__RegisterWrite(PCI_WRITE_REG_ADDR, lftSppuPacketFormatSend[1]);
	__RegisterWrite(PCI_WRITE_REG_ADDR, Address);
	__RegisterWrite(PCI_WRITE_REG_ADDR, Value);

	readValue = 0;

	for(lv = 0; lv < 4; lv++)
	{
		//Poll till value in control register = 0x1;
		if(lv < 3)
		{
			do
			{
				__RegisterRead(PCI_CONTROL_REG_ADDR, &readValue);
				readValue &= 0x1;
				//Sleep(10);
			}while(0x1 != readValue);
		}

		//Read the FPGA_Read register for status.
		__RegisterRead(PCI_READ_REG_ADDR, &readValue);
		if((0x2 == lv) && (0x0 == readValue))
			successFlag = 0x1;

		//Clear the control register.
		__RegisterWrite(PCI_CONTROL_REG_ADDR, 0x0);
		__RegisterWrite(PCI_CONTROL_REG_ADDR, 0x1);
	}

/*	ClosePciDevice();*/
	
	//Error checking
	if(!successFlag)
	{
		#if DEBUG_ERROR
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "ERROR : Register Write() : Invalid response Status" << endl;
		SppuUsbDllDebug.close();
		#endif
		return -2;
	}

	//Success Case
	#if DEBUG_INFO
	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
	SppuUsbDllDebug << "Success : Register Write (SPPU) Address = 0x" << std::hex << Address << "; Value = 0x" << Value << std::dec << endl;
	SppuUsbDllDebug.close();
	#endif
	return S_OK;
}