#pragma once
#include <windows.h>
#include <io.h>

#define PREFIX_SERIAL __declspec(dllexport)

namespace MiddleSerialAPI
{
	struct SerialInfo
	{
		char *pchPortName;

		//Only set the following properties of the DCB structure:
		//BaudRate, ByteSize, Parity, StopBits, fBinary, fParity (rest would be ignored anyway)
		DCB	dcbConfig;

		COMMTIMEOUTS commTimeout;
	};

	typedef struct SerialInfo SerialInfo;

	class SerialAPI
	{
	private:
		HANDLE hSerialComm;
		
	public:
		
		PREFIX_SERIAL SerialAPI(void);

		// Return integer
		//  0		-	Successful
		// -1		-	Conversion of port name from char * to WCHAR* failed
		// -2		-	Invalid Handle Value 
		// -3		-	Setup serial buffer failed
		// -4		-	Getting DCB general configuration setting failed
		// -5		-	Setting DCB Configuration failed
		// -6		-	Getting COMMTIMEOUTS settings failed
		// -7		-	Setting COMMTIMEOUTS settings failed
		PREFIX_SERIAL int ConnectSerialPort(SerialInfo a_SerialInfo);

		
		// Return integer
		//  0		-	Successful
		// -1		-	Unable to form packet
		// -2		-	Invalid Handle
		// -3		-	Serial Write failed partially (partially data written)
		// -4		-	Serial Write failed completely
		// -5		-	Serial Read failed
		// -6		-	Invalid Response Packet Status
		// -10		-	Invalid Magic Byte Received
		// -20		-   Invalid Packet Length
		PREFIX_SERIAL int RegRead(unsigned int address, unsigned int &data);

		// Return integer
		//  0		-	Successful
		// -1		-	Unable to form packet
		// -2		-	Invalid Handle
		// -3		-	Serial Write failed partially (partially data written)
		// -4		-	Serial Write failed completely
		// -5		-	Serial Read failed
		// -6		-	Invalid Response Packet Status
		// -10		-	Invalid Magic Byte Received
		// -20		-   Invalid Packet Length
		PREFIX_SERIAL int RegWrite(unsigned int address, unsigned int data);

		PREFIX_SERIAL void DisconnectSerialPort();

		PREFIX_SERIAL int SendBuffer(char * dataBuf, unsigned int bufLen, unsigned int &sentBufLen);
		PREFIX_SERIAL int RecvBuffer(char * dataBuf, unsigned int bufLen, unsigned int &recvBufLen);

		PREFIX_SERIAL int FileWrite(unsigned int startAddress, unsigned int size,  char *pchFilePath,  unsigned int *numBytesWrSuccess);
		PREFIX_SERIAL int FileRead(unsigned int startAddress, unsigned int size,  char *pchFilePath,  unsigned int *numBytesRdSuccess);


		PREFIX_SERIAL ~SerialAPI(void);

		void mPrintDebug(char *a_strDebug);
		PREFIX_SERIAL int MemReadInternal(unsigned int startAddress, unsigned int size, char *pchData, unsigned int *numBytesRdSuccess);
		PREFIX_SERIAL int MemWriteInternal(unsigned int startAddress, unsigned int size, char *pchData, unsigned int *numBytesWrSuccess);
	};
}

