#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <io.h>
#include <stdio.h>
#include "cprotocol.h"

//#define DEBUG_PRINTS_ON
//#define RCV_BULK_PKT_STS
#define ONE_SOCKET

#pragma comment(lib, "Ws2_32.lib")

#define PREFIX_ETHERNET __declspec(dllexport)

#ifdef ONE_SOCKET
// SD 
// this was old one 
#define MAX_BYTES_WRITE_AT_ONCE			    16384
#define FPGA_DDR_RESOLUTION		4096
// this was modified as per shashanks requet 
//#define MAX_BYTES_WRITE_AT_ONCE			    17508
#define FPGA_DDR_ACCESS_ADDR				0x00004200	//TODO : Mohit
#define FPGA_SPI_FLASH_ACCESS_ADDR			0x00004204 
#define MAX_BULK_READ_PACKET_SIZE			65504 //16* 1024	
#define MAX_BULK_READ_DATA_SIZE			    65504 -12//16* 1024 - 12	
#define DEBUG_STR_LEN						512//200
#define DEBUG_PRINTS_ON 1

#else
#define MAX_BYTES_WRITE_AT_ONCE			 700
#endif

namespace MiddleEthernetAPI
{
	struct SocketInfo
	{
		char* pcIpAddress;
		char* pcPort;
	};

	typedef struct SocketInfo SocktInfo;

	struct Sockets
	{
		
		SocketInfo objSocketInfoTransmit;
		SocketInfo objSocketInfoReceive;
		SocketInfo objSocketInfoCommand;
		DWORD	   nTimeOut;
	};

	typedef struct Sockets Sockets;

	class EthernetAPI
	{
		
	private:
		
		SOCKET objSocketTransmit;
		SOCKET objSocketReceive;
		SOCKET objSocketCommand;

		int TransmitData(char *pchData, int len);

	public:

		enum SPPUDeviceTypeEtherent
		{
			LFT_SPPU_DEV_ETH_DAC1				=   0,
			LFT_SPPU_DEV_ETH_DAC2				=   1,
			LFT_SPPU_DEV_ETH_DAC3				=   2,
			LFT_SPPU_DEV_ETH_LMK04806			=   3,
			LFT_SPPU_DEV_ETH_FPGA				=   4,
			LFT_SPPU_DEV_ETH_FPGA_SPI_FLASH     =	5,
			LFT_SPPU_DEV_ETH_DDR				=   6,
			LFT_SPPU_DEV_ETH_FX3_RAM			=   7,
			LFT_SPPU_DEV_ETH_FX3_SPI_FLASH		=	8,
			LFT_SPPU_DEV_ETH_FX3_SDCARD			=   9,
			LFT_SPPU_DEV_ETH_ATTENUATOR			=   10,
			LFT_SPPU_DEV_ETH_DAC_COMM           =   11
		};

		PREFIX_ETHERNET EthernetAPI(void);

		PREFIX_ETHERNET int FileWrite(SPPUDeviceTypeEtherent devType, unsigned int startAddress, unsigned int size,  char *pchFilePath);

		PREFIX_ETHERNET int FileRead(SPPUDeviceTypeEtherent devType, unsigned int startAddress, unsigned int size,  char *pchFilePath, unsigned int *numBytesRdSuccess);
		PREFIX_ETHERNET int FileRead_10GB(SPPUDeviceTypeEtherent devType, unsigned long long startAddress, unsigned long long size,  char *pchFilePath, unsigned long long *numBytesRdSuccess);

		PREFIX_ETHERNET int MemWrite(SPPUDeviceTypeEtherent devType, unsigned int startAddress, unsigned int size,  char *pchData);
		PREFIX_ETHERNET int FileWrite_10GB(SPPUDeviceTypeEtherent devType, unsigned long long startAddress, unsigned long long size,  char *pchFilePath);

		PREFIX_ETHERNET int MemRead(SPPUDeviceTypeEtherent devType, unsigned int startAddress, unsigned int size, char *pchData);

		PREFIX_ETHERNET int MemReadInternal(SPPUDeviceTypeEtherent devType, unsigned int startAddress, unsigned int size, char *pchData, unsigned int *numBytesRdSuccess);

		//Return integer
		//  0		-	Successful
		// -1		-	Invalid Socket
		// -2		-	Send Failed
		// -3		-	Receive Failed
		// -4		-	Unable to form the Packet
		// -5		-	Invalid Response
		// -10		-	Invalid Magic Byte Received
		// -20		-   Invalid Packet Length
		PREFIX_ETHERNET int RegWrite(unsigned int address, unsigned int data);

		//Return integer
		//  0		-	Successful
		// -1		-	Invalid Socket
		// -2		-	Send Failed
		// -3		-	Receive Failed
		// -4		-	Unable to form the Packet
		// -5		-	Invalid Response
		// -10		-	Invalid Magic Byte Received
		// -20		-   Invalid Packet Length
		PREFIX_ETHERNET int RegRead(unsigned int address, unsigned int &data);

		// Return integer
		//  0		-	Successful
		// -1		-	Winsock Initialization failed	
		// -2		-	Sockets structure not initialized
		// -3		-	Get Address Info failed
		// -4		-	Creating socket failed
		// -5		-   Connecting to socket failed
		PREFIX_ETHERNET int ConnectSockets(Sockets a_objSockets);

		PREFIX_ETHERNET void DisconnectSockets();

		PREFIX_ETHERNET ~EthernetAPI(void);

		void EthernetAPI::mPrintDebug(char *a_strDebug);
	};

}
