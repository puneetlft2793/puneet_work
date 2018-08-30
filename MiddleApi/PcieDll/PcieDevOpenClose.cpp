#include "Pcie.h"

#include "PcieIoctrl.h"
#include <SetupAPI.h>

using namespace Pcie;


void Pcie::c_Pcie::InitializeRegInfo()
{
	RegInfo[2].offset = WRITE_ADDR_OFFSET;
	RegInfo[2].writeControlCode = IOCTL_SET_DMA_WRITE_ADDR;
	RegInfo[2].readControlCode = IOCTL_GET_DMA_WRITE_ADDR;
	RegInfo[2].name = "DMA Write Address Register";

	RegInfo[3].offset = WRITE_SIZE_OFFSET;
	RegInfo[3].writeControlCode = IOCTL_SET_DMA_WRITE_SIZE;
	RegInfo[3].readControlCode = IOCTL_GET_DMA_WRITE_SIZE;
	RegInfo[3].name = "DMA Write Size Register";

	RegInfo[4].offset = WRITE_COUNT_OFFSET;
	RegInfo[4].writeControlCode = IOCTL_SET_DMA_WRITE_COUNT;
	RegInfo[4].readControlCode = IOCTL_GET_DMA_WRITE_COUNT;
	RegInfo[4].name = "DMA Write Count Register";

	RegInfo[5].offset = WRITE_PATTERN_OFFSET;
	RegInfo[5].writeControlCode = IOCTL_SET_DMA_WRITE_PATTERN;
	RegInfo[5].readControlCode = IOCTL_GET_DMA_WRITE_PATTERN;
	RegInfo[5].name = "DMA Write Pattern Register";

	RegInfo[6].offset = READ_PATTERN_OFFSET;
	RegInfo[6].writeControlCode = IOCTL_SET_DMA_READ_PATTERN;
	RegInfo[6].readControlCode = IOCTL_GET_DMA_READ_PATTERN;
	RegInfo[6].name = "DMA Read Pattern Register";

	RegInfo[7].offset = READ_ADDR_OFFSET;
	RegInfo[7].writeControlCode = IOCTL_SET_DMA_READ_ADDR;
	RegInfo[7].readControlCode = IOCTL_GET_DMA_READ_ADDR;
	RegInfo[7].name = "DMA Read Address Register";

	RegInfo[8].offset = READ_SIZE_OFFSET;
	RegInfo[8].writeControlCode = IOCTL_SET_DMA_READ_SIZE;
	RegInfo[8].readControlCode = IOCTL_GET_DMA_READ_SIZE;
	RegInfo[8].name = "DMA Read Size Register";

	RegInfo[9].offset = READ_COUNT_OFFSET;
	RegInfo[9].writeControlCode = IOCTL_SET_DMA_READ_COUNT;
	RegInfo[9].readControlCode = IOCTL_GET_DMA_READ_COUNT;
	RegInfo[9].name = "DMA Read Count Register";
}


HANDLE Pcie::c_Pcie::OpenDeviceByGuid(LPGUID pGuid)
{
	SP_DEVICE_INTERFACE_DATA			data;
	PSP_DEVICE_INTERFACE_DETAIL_DATA	detail;	
	DWORD								error;
	HANDLE								hDevice;
	DWORD								i;
	HDEVINFO							info;
	DWORD								reqSize;
	SP_DEVINFO_DATA						DevInfoData;

	int success_counter = 0;

	// get handle to relevant device information set

	//First
	info = SetupDiGetClassDevs(pGuid, NULL, NULL, DIGCF_PRESENT | DIGCF_INTERFACEDEVICE);
	if (info == INVALID_HANDLE_VALUE)
	{
		error = GetLastError();
		
		#if DEBUG_FILE
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "FAILURE SetupDiGetClassDevs() : ERROR Code : 0x" << std::hex << error << std::dec << endl;
		SppuUsbDllDebug.close();
		#endif
		
		return INVALID_HANDLE_VALUE;
	}
#if DEBUG_PRINT_SUCCESS_IN_FILE
	else
	{
		#if DEBUG_FILE
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "SUCCESS SetupDiGetClassDevs()" << endl;
		SppuUsbDllDebug.close();
		#endif
	}
#endif

	// get interface data
	data.cbSize = sizeof (data);

	for (i = 0, error = 0; error != ERROR_NO_MORE_ITEMS; i++)
	{
		if (!SetupDiEnumDeviceInterfaces (info, NULL, pGuid, i, &data))
		{
			error = GetLastError();
			if (error != ERROR_NO_MORE_ITEMS)
			{
				SetLastError(error);
				#if DEBUG_FILE
				SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
				SppuUsbDllDebug << "FAILURE SetupDiEnumDeviceInterfaces() : ERROR Code : 0x" << std::hex << error << std::dec << endl;
				SppuUsbDllDebug.close();
				#endif
				SetupDiDestroyDeviceInfoList (info);
				return INVALID_HANDLE_VALUE;
			}
			else
			{
				//printf("FAILURE SetupDiEnumDeviceInterfaces(). No More Items.\n");
			}
		}//TODO : remove this else statement.
		else
		{
			success_counter++;
		}
	}
#if DEBUG_PRINT_SUCCESS_IN_FILE
	#if DEBUG_FILE
	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
	SppuUsbDllDebug << "Devices :success_counter = " << success_counter << endl;
	SppuUsbDllDebug.close();
	#endif
#endif

#if 1
	// get size of symbolic link name
	//SetupDiGetDeviceInterfaceDetail (info, &data, NULL, 0, &reqSize, NULL);

	DevInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
	SetupDiGetDeviceInterfaceDetail (info, &data, NULL, 0, &reqSize, &DevInfoData);
	error = GetLastError();

	if (error != ERROR_INSUFFICIENT_BUFFER)
	{
		SetLastError(error);
		#if DEBUG_FILE
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "FAILURE SetupDiEnumDeviceInterfaces() : ERROR Code : 0x" << std::hex << error << std::dec << endl;
		SppuUsbDllDebug.close();
		#endif
		SetupDiDestroyDeviceInfoList (info);
		return INVALID_HANDLE_VALUE;
	}
#endif

#if DEBUG_PRINT_SUCCESS_IN_FILE
	#if DEBUG_FILE
	SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
	SppuUsbDllDebug << "GUID = " << DevInfoData.ClassGuid.Data1 <<
		"-" << DevInfoData.ClassGuid.Data2 <<
		"-" << DevInfoData.ClassGuid.Data3 <<
		"-" << DevInfoData.ClassGuid.Data4[0] << DevInfoData.ClassGuid.Data4[1] <<
		"-" << DevInfoData.ClassGuid.Data4[2] << DevInfoData.ClassGuid.Data4[3] <<
		DevInfoData.ClassGuid.Data4[4] << DevInfoData.ClassGuid.Data4[5] <<
		DevInfoData.ClassGuid.Data4[6] << DevInfoData.ClassGuid.Data4[7] <<
		std::dec << endl;
	SppuUsbDllDebug.close();
	#endif
#endif

	// get symbolic link name
	detail = PSP_INTERFACE_DEVICE_DETAIL_DATA(new char[reqSize]);

	if (!detail)
	{
		#if DEBUG_FILE
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "FFAILURE PSP_INTERFACE_DEVICE_DETAIL_DATA()" << endl;
		SppuUsbDllDebug.close();
		#endif
		SetupDiDestroyDeviceInfoList (info);
		return INVALID_HANDLE_VALUE;
	}
#if DEBUG_PRINT_SUCCESS_IN_FILE
	else
	{
		#if DEBUG_FILE
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "SUCCESS PSP_INTERFACE_DEVICE_DETAIL_DATA()" << endl;
		SppuUsbDllDebug.close();
		#endif
	}
#endif

	detail->cbSize = sizeof (SP_DEVICE_INTERFACE_DETAIL_DATA);

	if(!SetupDiGetDeviceInterfaceDetail (info, &data, detail, reqSize, &reqSize, &DevInfoData))
	{
		error = GetLastError();
		#if DEBUG_FILE
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "FAILURE SetupDiGetDeviceInterfaceDetail() : ERROR Code : 0x" << std::hex << error << std::dec << endl;
		SppuUsbDllDebug.close();
		#endif
		SetupDiDestroyDeviceInfoList (info);
		delete detail;
		return INVALID_HANDLE_VALUE;
	}
#if DEBUG_PRINT_SUCCESS_IN_FILE
	else
	{
		#if DEBUG_FILE
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "SUCCESS SetupDiGetDeviceInterfaceDetail()" << endl;
		SppuUsbDllDebug.close();
		#endif

		
		#if DEBUG_FILE
		{
			int i = 0;
			#if DEBUG_FILE
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			#endif
			for(i = 0; i < 106; i++)
			{
			//	printf("%c", detail->DevicePath[i]);
				#if DEBUG_FILE
				SppuUsbDllDebug.write((const char *)(detail->DevicePath + i), 1);
				#endif
			}
			#if DEBUG_FILE
			SppuUsbDllDebug.close();
			#endif
		}
		

		#if DEBUG_FILE
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << std::dec << endl;
		SppuUsbDllDebug.close();
		#endif
		#endif			//DEBUG_FILE

		//printf("\n");
	}
#endif
   
	// Open a "File", which in this context means that we are receiving a
	// handle to a Device Object.  This handle is used in subsequent calls
	// to identify the Device Object, and ultimately interact with the
	// physical device it represents.

	// Take note of the attribute "FILE_FLAG_OVERLAPPED".  If your physical
	// device supports simultaneous operations (for example, a DMA device
	// that can perform 1 read and 1 write operation at the same time), you
	// MUST specify this attribute.  If you do not, when your application
	// attempts to perform a read (ReadFile) or write (WriteFile) on the device
	// the CALL WILL BLOCK in the I/O Manager, and your application will freeze.
	// This obviously prevents you from programming any simultaneous operations.
	// The complication with specifying the overlapped attribute is that you
	// now must provide an Overlapped structure in your Writefile and Readfile
	// calls.  When your operation starts at the device driver level, it will
	// eventually return STATUS_PENDING to the I/O Manager.  The I/O Manager 
	// will then return an ERROR_IO_PENDING status to the calling function, 
	// allowing your application to proceed.  This makes use of the Overlapped
	// structure, and is not really an error at all (assuming that your I/O
	// operation is supposed to be pending, of course!).

	hDevice = CreateFile (
	  detail->DevicePath,
      GENERIC_READ | GENERIC_WRITE,
      FILE_SHARE_READ | FILE_SHARE_WRITE,
      NULL,
      OPEN_EXISTING,
	  //FILE_ATTRIBUTE_NORMAL,
	  FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
      NULL);

	if (hDevice == INVALID_HANDLE_VALUE)
	{
		error = GetLastError();
		#if DEBUG_FILE
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "FAILURE CreateFile() : ERROR Code : 0x" << std::hex << error << std::dec << endl;
		SppuUsbDllDebug.close();
		#endif
		SetupDiDestroyDeviceInfoList (info);
		delete detail;
		return INVALID_HANDLE_VALUE;
	}

	SetupDiDestroyDeviceInfoList (info);
	delete detail;
	return (PcieDev.hs3_1000 = hDevice);
}


int Pcie::c_Pcie::CloseDevice()
{
	//If device is open proceed to close it.
	if(PcieDev.IsOpen == TRUE)
	{
		//If handle to device is valid, proceed to release it.
		if (PcieDev.hs3_1000 != INVALID_HANDLE_VALUE)
		{
			//Close the handle.
			if(CloseHandle(PcieDev.hs3_1000))			//Returns non-zero on success.
			{
				//Success
				PcieDev.hs3_1000 = INVALID_HANDLE_VALUE;
	#if DEBUG_PRINT_SUCCESS_IN_FILE
				#if DEBUG_FILE
				SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
				SppuUsbDllDebug << "SUCCESS CloseHandle()" << endl;
				SppuUsbDllDebug.close();
				#endif
	#endif
				PcieDev.IsOpen = FALSE;
			}
			else
			{
				#if DEBUG_FILE
				SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
				SppuUsbDllDebug << "FAILURE CloseHandle() : Invalid Handel, Error code = 0x" << std::hex << GetLastError() << std::dec << endl;
				SppuUsbDllDebug.close();
				#endif
			}
		}
		else
		{
			#if DEBUG_FILE
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug << "FAILURE CloseDevice() : Invalid Handel" << endl;
			SppuUsbDllDebug.close();
			#endif
		}
	}

	return S_OK;
}

/*if(OpenDevice())
		return -1;
		*/
#pragma region DeviceOpenClose
int Pcie::c_Pcie::OpenDevice()
{
	if(PcieDev.IsOpen == FALSE)
	{
		#if DEBUG_FILE
		SYSTEMTIME st;
		GetLocalTime(&st);
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out);
		SppuUsbDllDebug << "\n############################################################\nLogging Started :" <<
			st.wDay << "/" << st.wMonth << "/" << st.wYear << "\t" << 
			st.wHour << ":" << st.wMinute  << ":" << st.wSecond << endl << endl;
		SppuUsbDllDebug.close();
		#endif

		/* Find and open a XBMD_MEMORY device (by default ID) */
		PcieDev.hs3_1000 = OpenDeviceByGuid((LPGUID) &GuidDriver);
		if (PcieDev.hs3_1000 && PcieDev.hs3_1000 != INVALID_HANDLE_VALUE)
		{
#if DEBUG_PRINT_SUCCESS_IN_FILE
			#if DEBUG_FILE
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug << "SUCCESS OpenDeviceByGuid()" << endl;
			SppuUsbDllDebug.close();
			#endif
#endif
			PcieDev.IsOpen = TRUE;
			return S_OK;
		}
		else
		{
			#if DEBUG_FILE
			SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
			SppuUsbDllDebug << "FAILURE OpenDeviceByGuid() : Invalid Handel, Error code = 0x" << std::hex << GetLastError() << std::dec << endl;
			SppuUsbDllDebug.close();
			#endif
			return -1;
		}
	}
	else
	{
#if DEBUG_PRINT_SUCCESS_IN_FILE
		#if DEBUG_FILE
		SppuUsbDllDebug.open(USB_DLL_DEBUF_FILE_NAME, ios_base::out | ios_base::app);
		SppuUsbDllDebug << "Info : Device already opened!" << endl;
		SppuUsbDllDebug.close();
		#endif
#endif
		return S_OK;
	}

	return -1;
}


#pragma endregion DeviceOpenClose

