#include "SerialAPI.h"

#include "../EthernetAPI/EthernetAPI/cprotocol.h"
#define DEBUG_STR_LEN					200
#define MAX_BULK_READ_PACKET_SIZE		256+12
#define MAX_BULK_READ_DATA_SIZE			256
using namespace MiddleSerialAPI;

SerialAPI::SerialAPI(void)
{
	hSerialComm	=	INVALID_HANDLE_VALUE;
	
}

int SerialAPI::ConnectSerialPort(SerialInfo a_serialInfo)
{
	WCHAR wchSerialPortName[20];

	int size	=	MultiByteToWideChar(CP_ACP,0,a_serialInfo.pchPortName,-1,NULL,0);

	if(size	==	0)
		return -1;

	size	=	MultiByteToWideChar(CP_ACP,0,a_serialInfo.pchPortName,-1,wchSerialPortName,size);

	hSerialComm = CreateFile(wchSerialPortName, /* Port Name */ 
							   GENERIC_READ | GENERIC_WRITE, /* Desired Access */ 
							   0, /* Shared Mode */
							   NULL, /* Security */
							   OPEN_EXISTING, /* Creation Disposition */
							   0,
							   NULL); /* Non Overlapped */

	if(hSerialComm == INVALID_HANDLE_VALUE)
	{
//		unsigned long error = ::GetLastError();
		return -2;
	}

	if(!SetupComm(hSerialComm, 1024, 1024))
		return -3;

	DCB dcbConfig;

	if(GetCommState(hSerialComm, &dcbConfig)) /* Configuring Serial Port Settings */
	{
		dcbConfig.BaudRate = a_serialInfo.dcbConfig.BaudRate;
		dcbConfig.ByteSize = a_serialInfo.dcbConfig.ByteSize;
		dcbConfig.Parity = a_serialInfo.dcbConfig.Parity;
		dcbConfig.StopBits = a_serialInfo.dcbConfig.StopBits;
		dcbConfig.fBinary = a_serialInfo.dcbConfig.fBinary;
		dcbConfig.fParity = a_serialInfo.dcbConfig.fParity;
	}
	else
		return -4;

	if(!SetCommState(hSerialComm, &dcbConfig))
		return -5;

	COMMTIMEOUTS commTimeout;
				
	if(GetCommTimeouts(hSerialComm, &commTimeout)) /* Configuring Read & Write Time Outs */
	{
		commTimeout = a_serialInfo.commTimeout;
	}
	else
		return -6;

	if(!SetCommTimeouts(hSerialComm, &commTimeout))
		return -7;
	
	return 0;
}

int SerialAPI::RegWrite(unsigned int address, unsigned int data)
{
	char *byArrPkt  =   0;
	int pktLen	=	0;
	CProtocol objProtocol;
	pktLen	=	objProtocol.mPktRegWrite(address,data,&byArrPkt);

	if(byArrPkt	==	0)
	{
		printf("Unable to form Reg Write Packet\n");
		return -1;
	}

	if(hSerialComm	==	INVALID_HANDLE_VALUE)
	{
		printf("Invalid Handle \n");
		delete byArrPkt;
		return -2;
	}
	else
	{
		DWORD nBytesWritten	=	0;
		if(WriteFile(hSerialComm,byArrPkt,pktLen,&nBytesWritten,NULL))
		{
			if(nBytesWritten !=	pktLen)
			{
				delete byArrPkt;
				return -3;
			}
		}
		else
		{
			delete byArrPkt;
			return -4;
		}

		char byArrPktResp[16];

		char szBuf;
		DWORD dwIncommingReadSize	=	0;
		DWORD dwSize	=	0;

		do
		{
			if(ReadFile(hSerialComm, &szBuf, 1, &dwIncommingReadSize, NULL) != 0)
			{
				if(dwIncommingReadSize > 0)
				{
					byArrPktResp[dwSize]	=	szBuf;
					dwSize += dwIncommingReadSize;
				}
			}

			else
			{
				delete byArrPkt;
				return -5;
			}

		} while(dwIncommingReadSize > 0);


		CProtocol objProtoRespPkt;
		int ret	=	objProtoRespPkt.mPktParse(byArrPktResp);
		ret     *=  10;
		if(ret < 0)
		{
			delete byArrPkt;
			return  ret;
		}

		if(objProtoRespPkt.mGetStatus()   ==  0)
		{
			delete byArrPkt;
			return 0;
		}
		else
		{
			delete byArrPkt;
			return -6;
		}
	}

	return 0;
}

int SerialAPI::RegRead(unsigned int address, unsigned int &data)
{
	char *byArrPkt  =   0;
	int pktLen	=	0;
	CProtocol objProtocol;
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};	
	pktLen	=	objProtocol.mPktRegRead(address,&byArrPkt);

	if(byArrPkt	==	0)
	{
		printf("Unable to form Reg Read Packet\n");
		
		return -1;
	}

	if(hSerialComm	==	INVALID_HANDLE_VALUE)
	{
		printf("Invalid Handle \n");
	
		delete byArrPkt;
		return -2;
	}
	else
	{
		DWORD nBytesWritten	=	0;
		if(WriteFile(hSerialComm,byArrPkt,pktLen,&nBytesWritten,NULL))
		{
			if(nBytesWritten !=	pktLen)
			{
				delete byArrPkt;
				
				return -3;
			}
			
		}
		else
		{
			delete byArrPkt;
			
			return -4;
		}

		char byArrPktResp[16];

		char szBuf;
		DWORD dwIncommingReadSize	=	0;
		DWORD dwSize	=	0;

		do
		{
			if(ReadFile(hSerialComm, &szBuf, 1, &dwIncommingReadSize, NULL) != 0)
			{
				if(dwIncommingReadSize > 0)
				{
					byArrPktResp[dwSize]	=	szBuf;
					//sprintf_s(strDebug, DEBUG_STR_LEN,"\n dwSize %d byt array pkt %x",dwSize, byArrPktResp[dwSize]);
					//mPrintDebug(strDebug);
					dwSize += dwIncommingReadSize;
					
				}
			}

			else
			{
				delete byArrPkt;
				
				return -5;
			}

		} while(dwIncommingReadSize > 0);


		CProtocol objProtoRespPkt;
		int ret	=	objProtoRespPkt.mPktParse(byArrPktResp);
		ret     *=  10;
		if(ret < 0)
		{
			delete byArrPkt;
			
			return  ret;
		}

		if(objProtoRespPkt.mGetStatus()   ==  0)
		{
			data	=	objProtoRespPkt.mGetRegisterData();
			delete byArrPkt;
			
			return 0;
		}
		else
		{
			delete byArrPkt;
			
			return -6;
		}
	}
	
	return 0;
}

int SerialAPI::SendBuffer(char * dataBuf, unsigned int bufLen, unsigned int &sentBufLen)
{
	int retValue = 0;
	DWORD nBytesWritten	=	0;
	if(WriteFile(hSerialComm,dataBuf,bufLen,&nBytesWritten,NULL))
	{
			char strDebug[DEBUG_STR_LEN]	=	{'\0'};	
			sprintf_s(strDebug, DEBUG_STR_LEN," nBytesWritten  : %d  bufLen :%d byte",nBytesWritten,bufLen);
			mPrintDebug(strDebug);
		if(nBytesWritten !=	bufLen)
		{mPrintDebug("Condition 1");
			retValue = -3;
		}

		mPrintDebug("Condition 2");
	}
	else
		retValue = -1;

	sentBufLen = nBytesWritten;

	return retValue;
}

int SerialAPI::RecvBuffer(char * dataBuf, unsigned int bufLen, unsigned int &recvBufLen)
{
	int retValue = 0;
	unsigned char szBuf;
	DWORD dwIncommingReadSize	=	0;
	DWORD dwSize	=	0;
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};	
	//  int timeout = 200;    //5 sec timeout
	int timeout = 100;    //45 sec timeout
	int loopCounter=0;

	do
	{
		if(ReadFile(hSerialComm, &szBuf, 1, &dwIncommingReadSize, NULL) != 0)
		{
			if(dwIncommingReadSize > 0)
			{
				dataBuf[dwSize]	=	szBuf;
				dwSize += dwIncommingReadSize;
			}
			else
			{
				timeout--;
			}
		}
		else
		{
			retValue = -5;
			break;
		}

		if(timeout == 0) 
		{
			retValue = -6;
			break;
		}
		loopCounter++;
	}while((dwSize < bufLen)); // while((dwIncommingReadSize > 0) || (dwSize < bufLen)); //while((dwSize < bufLen)); 

	sprintf_s(strDebug, DEBUG_STR_LEN,"\n RecvBuffer: ReqLen: %d  Recieved : %d  timeout:%d  loopCounter:%d ", bufLen, dwSize, timeout, loopCounter);
	mPrintDebug(strDebug);
	recvBufLen = dwSize;
	return retValue;
}

void SerialAPI::DisconnectSerialPort()
{
	if(hSerialComm	!=	INVALID_HANDLE_VALUE)
	{
		CloseHandle(hSerialComm);
		hSerialComm	=	INVALID_HANDLE_VALUE;
	}
}

SerialAPI::~SerialAPI(void)
{
}

int SerialAPI::FileWrite(unsigned int startAddress, unsigned int size,  char *pchFilePath,  unsigned int *numBytesWrSuccess)
{
	FILE * pFile;
	errno_t err;
	//mPrintDebug("In FileWrite\n");
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};	
	//mPrintDebug("==========================================================================\n");
	//{

	//	sprintf_s(strDebug, DEBUG_STR_LEN,"FileWrite:: startAddress:%d size:%d Filename:%s", startAddress, size, pchFilePath);
	//	mPrintDebug(strDebug);
	//}
	//mPrintDebug("==========================================================================\n");

	err	=	fopen_s(&pFile, pchFilePath, "rb");
	if( err != 0)
	{
	//	mPrintDebug("Unable to open file\n");
		return -2; 
	}

	char rDevBuf[MAX_BULK_READ_PACKET_SIZE];
	unsigned int numByWrSuccess=0;
	unsigned int numByToWr = size;
	unsigned int numByWriteDone = 0;
	rDevBuf[0] = NULL;
	while(numByToWr)
	{
		if(numByToWr > MAX_BULK_READ_DATA_SIZE)
			numByToWr = MAX_BULK_READ_DATA_SIZE;

		fread(rDevBuf, 1, numByToWr, pFile);
		
		err = MemWriteInternal(startAddress, numByToWr, rDevBuf, &numByWrSuccess);

		if(err)
		{
			numByWrSuccess = 0;

			break;
		}

		numByWriteDone += numByWrSuccess;
		//startAddress += numByWrSuccess;	// ------------------  As we are not changing the address in test files or we are working on FIFO

		if(numByWriteDone >= size)
		{
			break;
		}
		numByToWr = size - numByWriteDone;
	}

	//sprintf_s(strDebug, DEBUG_STR_LEN,"FileWrite:: numByWriteDone : %d  ", numByWriteDone);
	//mPrintDebug(strDebug);

	*numBytesWrSuccess = numByWriteDone;
	fclose(pFile);
	return 0;
}

int SerialAPI::MemWriteInternal(unsigned int startAddress, unsigned int size,  char *pchData,  unsigned int *numBytesWrSuccess)
{
	char byArrPkt[16];
	int pktLen	=	0;
	int respSizeExp = 0;
	int respSize = 0;
	CProtocol objProtocol;
	unsigned int sentBufLen = 0;

	{
		char strDebug[DEBUG_STR_LEN]	=	{'\0'};	
		sprintf_s(strDebug, DEBUG_STR_LEN,"MemWriteInternal:: startAddress:%d size:%d \n", startAddress, size);
		mPrintDebug("-----------------------------------------------\n");
		mPrintDebug(strDebug);
	}

	*numBytesWrSuccess = 0;

	//Create DDR Write comamnd packet
	pktLen	=	objProtocol.mPktBulkWriteUART(startAddress, 0, 12 + size  , byArrPkt);
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};	
	printf_s(strDebug, DEBUG_STR_LEN,"MemWriteInternal:: pktLen:%d  \n",  pktLen);
	mPrintDebug("-----------------------------------------------\n");
	mPrintDebug(strDebug);
	int iResult = SendBuffer(byArrPkt, 12, sentBufLen);

	if (iResult != 0) 
	{
		mPrintDebug("Error: SendBuffer Header\n");
		return -2;
	}

	iResult = SendBuffer(pchData, size, sentBufLen);
	if (iResult != 0) 
	{
		mPrintDebug("Error: SendBuffer Data\n");
		return -3;
	}

	//{
	//	char strDebug[DEBUG_STR_LEN]	=	{'\0'};	
	//	sprintf_s(strDebug, DEBUG_STR_LEN,"SendBuffer Data %d\n", sentBufLen);
	//	mPrintDebug(strDebug);
	//}

	*numBytesWrSuccess = size;
	return 0;

}

int SerialAPI::FileRead(unsigned int startAddress, unsigned int size,  char *pchFilePath,  unsigned int *numBytesRdSuccess)
{
	FILE * pFile;
	errno_t err;
	char rDevBuf[MAX_BULK_READ_PACKET_SIZE];
	unsigned int numByRdSuccess=0;
	unsigned int numByToRd = size;
	unsigned int numByReadDone = 0;
	rDevBuf[0] = NULL;
/*	mPrintDebug("==========================================================================\n");
	{
		char strDebug[DEBUG_STR_LEN]	=	{'\0'};	
		sprintf_s(strDebug, DEBUG_STR_LEN,"FileRead:: startAddress:%d size:%d Filename:%s", startAddress, size, pchFilePath);
		mPrintDebug(strDebug);
	}
	mPrintDebug("==========================================================================\n");	*/	

	err	=	fopen_s(&pFile, pchFilePath, "wb");
	if( err != 0)
	{
		mPrintDebug("Unable to open file\n");
		return -2; 
	}

	while(numByToRd)
	{
		if(numByToRd > MAX_BULK_READ_DATA_SIZE)
			numByToRd = MAX_BULK_READ_DATA_SIZE;

		err = MemReadInternal(startAddress, numByToRd, rDevBuf, &numByRdSuccess);

		if(err)
		{numByRdSuccess = 0;
		break;}

		numByReadDone += numByRdSuccess;
		// startAddress += numByRdSuccess;     // ------------------  As we are not changing the address in test files or we are working on FIFO

		fwrite(rDevBuf, 1, numByRdSuccess, pFile);

		if(numByReadDone >= size)
		{break;}
		numByToRd = size - numByReadDone;
	}
	*numBytesRdSuccess = numByReadDone;
	fclose(pFile);
	return 0;
}

int SerialAPI::MemReadInternal(unsigned int startAddress, unsigned int size, char *pchData, unsigned int *numBytesRdSuccess)
{
	char *byArrPkt  =   NULL;
	int pktLen	=	0;
	int respSizeExp = 0;
	int respSize = 0;
	CProtocol objProtocol;
	unsigned int rcvdLen;
	unsigned int sentBufLen = 0;
	char byArrPktResp[MAX_BULK_READ_PACKET_SIZE];
	int i=0;

	{
		char strDebug[DEBUG_STR_LEN]	=	{'\0'};	
		sprintf_s(strDebug, DEBUG_STR_LEN,"MemReadInternal:: startAddress:%d size:%d \n", startAddress, size);
		mPrintDebug("-----------------------------------------------\n");
		mPrintDebug(strDebug);
	}

	//Create DDR Read comamnd packet
	pktLen	=	objProtocol.mPktBulkReadUART(startAddress, 0, size + 12 , &byArrPkt);

	if(byArrPkt	==	0)
	{
		mPrintDebug("Error: Unable to form Bulk Read Packet \n");
		return -4;
	}


	int iResult = SendBuffer(byArrPkt, pktLen, sentBufLen);

	if (iResult != 0) 
	{
		mPrintDebug("Error: SendBuffer\n");
		delete byArrPkt;
		return -2;
	}

	respSizeExp = (size + 12);
	respSize = 0;


	for(i=0 ;  (respSize < respSizeExp) && (i < 10); i++)
	{
		RecvBuffer(byArrPktResp, size+12, rcvdLen);

		if ( iResult == 0 )
		{
			if(rcvdLen == 0)
			{
				mPrintDebug("Error: Return zero size \n");
				delete byArrPkt;
				return -3;
			}
			else
			{
				respSize += rcvdLen;
			}
		}
		else if ( iResult != 0 )
		{
			mPrintDebug("Error: RecvBuffer\n");
			delete byArrPkt;
			return -4;
		}
	}

	CProtocol objProtoRespPkt;
	int ret	=	objProtoRespPkt.mPktParseBulkRead(byArrPktResp);
	ret     *=  10;
	if(ret < 0)
	{
		if(ret == -1)
			mPrintDebug("Error: wrong magic byte \n");
		else			
			mPrintDebug("Error: mPktParseBulkRead \n");
		delete byArrPkt;
		return  ret;
	}

	if(objProtoRespPkt.mGetStatus()   !=  0)
	{
		mPrintDebug("Error: Wrong Status \n");
		delete byArrPkt;
		return  -5;
	}

	unsigned int data	=	objProtoRespPkt.mGetRegisterData();
	memcpy(pchData, byArrPktResp+12, respSize-12);
	*numBytesRdSuccess = respSize-12;

	delete byArrPkt;
	return 0;
}

void SerialAPI::mPrintDebug(char *a_strDebug)
{
	FILE * pFile;
	errno_t err;

	if((_access("debug_serial.log", 2)) != -1)
	{
		err	=	fopen_s(&pFile,"debug_serial.log","a");
		if(err	==	0)
		{
			fputs(a_strDebug, pFile);
			fputs("\n",pFile);
			fclose(pFile);
		}
		else
		{			
			printf("debug_serial.log access denied \n");
		}
	} 
}