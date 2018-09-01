#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include "EthernetAPI.h"
#include "linuxdefines.h"

using namespace MiddleEthernetAPI;

#define FPGA_DDR_ACCESS_ADDR				0x00004200	//TODO : Mohit
#define FPGA_SPI_FLASH_ACCESS_ADDR			0x00004204 
#define MAX_BULK_READ_PACKET_SIZE			65532//64 * 1024	
#define MAX_BULK_READ_DATA_SIZE			    65532-12//64 * 1024	

//#define MAX_BULK_READ_PACKET_SIZE			12 * 1460 - 12	
//#define MAX_BULK_READ_DATA_SIZE			    12 * 1460 - 12	


#define DEBUG_STR_LEN						200

EthernetAPI::EthernetAPI(void)
{
    objSocketTransmit	=	INVALID_SOCKET;
    objSocketReceive	=	INVALID_SOCKET;
    objSocketCommand	=	INVALID_SOCKET;
}
int EthernetAPI::FileWrite_10GB(SPPUDeviceTypeEtherent devType, unsigned long long startAddress, unsigned long long size,  char *pchFilePath)
{

#if 0
#define BUFFERED_PACKETS_SIZE  0x100000  //1 MB
#else
#define BUFFERED_PACKETS_SIZE  0x10A000  //1MB & 40 kB
#endif

    //__HP__2; Adding support : if File Size is not multiple of 64 bytes then append 0s to make it multiple of 64 bytes.
    unsigned long long SizeDifference = 0, SizeModify = 0;
    FILE * pFile;
    errno_t err;

    mPrintDebug((char *)"==========================================================================\n");
    {
        char strDebug[DEBUG_STR_LEN]	=	{'\0'};
        snprintf(strDebug, DEBUG_STR_LEN,"FileWrite:: startAddress:%lld size:%lld Filename:%s", startAddress, size, pchFilePath);
        mPrintDebug(strDebug);
    }
    mPrintDebug((char *)"==========================================================================\n");

    if((access(pchFilePath, 2)) != -1)
    {
        err	=	fopen_s(&pFile, pchFilePath, "rb");
        if(err	==	0)
        {
            bool bInfiniteLoopFlag	=	true;
            while(bInfiniteLoopFlag)
            {
                char *pchPacketBuffer = new char[BUFFERED_PACKETS_SIZE];
                int nPacketBufferSize = 0;

                while(nPacketBufferSize < (BUFFERED_PACKETS_SIZE - (MAX_BYTES_WRITE_AT_ONCE + 12))) //buffer packets, till we have 1 MB of (16K + 12 size packets)
                {
                    char buffer[MAX_BYTES_WRITE_AT_ONCE] = {'\0'};
                    int count = 0;
                    mPrintDebug((char *)"==========================================================================\n");
                    {
                        char strDebug[DEBUG_STR_LEN]	=	{'\0'};
                        snprintf(strDebug, DEBUG_STR_LEN,"FileWrite:: startAddress:%lld size:%lld Filename:%s", startAddress, size, pchFilePath);
                        mPrintDebug(strDebug);
                    }
                    mPrintDebug((char *)"==========================================================================\n");

                    if(size < MAX_BYTES_WRITE_AT_ONCE)
                    {
#if 1
                        if(size	>	0)
                            count = fread(buffer, sizeof(char), size, pFile);
#else
                        count = size;
#endif
                    }
                    else
                    {
#if 1
                        count = fread(buffer, sizeof(char), MAX_BYTES_WRITE_AT_ONCE, pFile);
#else
                        count =	MAX_BYTES_WRITE_AT_ONCE;
#endif
                    }
#if 1
                    //__HP__6: Adding logic to append zeros in Buffer if data is not multiple of 4096
                    if((SizeDifference = (count % FPGA_DDR_RESOLUTION)) != 0)
                    {
                        SizeModify = (FPGA_DDR_RESOLUTION - SizeDifference);
                        memset(buffer + count, '\0', SizeModify);
                        count += SizeModify;
                    }
                    //__HP__6 : Till here.
#endif
                    //__HP__6: Remove this line
                    //fwrite(buffer, 1, count, Eth_Wr);
#if 1
                    if(ferror(pFile))
                    {
                        fclose(pFile);

#ifdef DEBUG_PRINTS_ON
                        perror( "Read error" );
#endif
                        if(pchPacketBuffer != NULL)
                            delete pchPacketBuffer;
                        return -3;
                    }
#endif

#ifdef ONE_SOCKET
                    CProtocol objPktProtocol;
#if 1
                    char *byArrPkt = NULL;
                    int nPktLen = objPktProtocol.mPktBulkWrite(startAddress, buffer, count, &byArrPkt);
#else
                    char *byArrPkt = buffer;
                    int nPktLen     = count;
#endif
                    if(byArrPkt == NULL)
                    {
                        fclose(pFile);
                        if(pchPacketBuffer != NULL)
                            delete pchPacketBuffer;
                        return -4;
                    }

                    memcpy(pchPacketBuffer + nPacketBufferSize, byArrPkt, nPktLen);
                    nPacketBufferSize += nPktLen;

                    delete byArrPkt; //packet has been buffered, freeing up memory

                    if(size <= MAX_BYTES_WRITE_AT_ONCE)
                    {
                        bInfiniteLoopFlag = false; //for exiting the infinte while loop
                        break;
                    }

                    size = size - MAX_BYTES_WRITE_AT_ONCE;
                } //Ending of Buffering of packets

                //fwrite(pchPacketBuffer, 1, nPacketBufferSize, Eth_Wr);
                //__HP__5: remove this
                //fclose(Eth_Wr);

                //write 1Mb of buffer
                int ret	= TransmitData(pchPacketBuffer, nPacketBufferSize);

#else
                    int ret	= TransmitData(buffer, count);
#endif

                    if(ret != 0)
                    {
                        //data was not sent
                        if(pchPacketBuffer != NULL)
                            delete pchPacketBuffer;
                        fclose(pFile);
                        return ret	*	1000;
                    }
                    else
                    {
                        //data sent
                        if(pchPacketBuffer	!=	NULL)
                            delete pchPacketBuffer;
                    }
                } //ending of infinite while loop
                fclose(pFile);
            }
            else
            {
                // unable to open file
#ifdef DEBUG_PRINTS_ON
                printf("FileWrite, File access denied \n");
#endif
                return -2;
            }
        }
        else
        {
            //file not found
#ifdef DEBUG_PRINTS_ON
            printf("File not found \n");
#endif
            return -1;
        }

        return 0;
    }

    int EthernetAPI::FileWrite(SPPUDeviceTypeEtherent devType, unsigned int startAddress, unsigned int size,  char *pchFilePath)
    {

#if 0
#define BUFFERED_PACKETS_SIZE  0x100000  //1 MB
#else
#define BUFFERED_PACKETS_SIZE  0x10A000  //1MB & 40 kB
#endif

        FILE * pFile;
        errno_t err;

        mPrintDebug((char *)"==========================================================================");
        {
            char strDebug[DEBUG_STR_LEN]	=	{'\0'};
            snprintf(strDebug, DEBUG_STR_LEN,"FileWrite:: startAddress:%d size:%d Filename:%s", startAddress, size, pchFilePath);
            mPrintDebug(strDebug);
        }
        mPrintDebug((char *)"==========================================================================");

        if((access(pchFilePath, 2)) != -1)
        {
            err	=	fopen_s(&pFile, pchFilePath, "rb");

            if(err	==	0)
            {
                //To do:
                //register access calls
                //programming startAddress, size & devType

                bool bInfiniteLoopFlag	=	true;

                while(bInfiniteLoopFlag)
                {
                    char *pchPacketBuffer					=  new char[BUFFERED_PACKETS_SIZE];
                    int nPacketBufferSize					=  0;


                    while(nPacketBufferSize	<	(BUFFERED_PACKETS_SIZE	-	(MAX_BYTES_WRITE_AT_ONCE	+	12))) //buffer packets, till we have 1 MB of (16K + 12 size packets)
                    {
                        char buffer[MAX_BYTES_WRITE_AT_ONCE]	=	{'\0'};
                        int count								=	0;

                        if(size	<	MAX_BYTES_WRITE_AT_ONCE)
                        {
#if 1
                            if(size	>	0)
                                count	=	fread(buffer, sizeof(char), size, pFile);
#else
                            count = size;
#endif
                        }
                        else
                        {
#if 1
                            count	=	fread(buffer, sizeof(char), MAX_BYTES_WRITE_AT_ONCE, pFile);
#else
                            count =	MAX_BYTES_WRITE_AT_ONCE;
#endif
                        }

#if 1
                        if(ferror(pFile))
                        {
                            fclose(pFile);

#ifdef DEBUG_PRINTS_ON
                            perror( "Read error" );
#endif
                            if(pchPacketBuffer	!=	NULL)
                                delete pchPacketBuffer;

                            return -3;
                        }
#endif

#ifdef ONE_SOCKET
                        CProtocol objPktProtocol;

#if 1
                        char *byArrPkt	=	NULL;
                        int nPktLen	=	objPktProtocol.mPktBulkWrite(startAddress, buffer, count, &byArrPkt);
#else
                        char *byArrPkt = buffer;
                        int nPktLen     = count;
#endif
                        if(byArrPkt	==	NULL)
                        {
                            fclose(pFile);

                            if(pchPacketBuffer	!=	NULL)
                                delete pchPacketBuffer;

                            return -4;
                        }
                        memcpy(pchPacketBuffer	+	nPacketBufferSize, byArrPkt, nPktLen);
                        nPacketBufferSize	+=	nPktLen;

                        delete byArrPkt; //packet has been buffered, freeing up memory

                        if( size <= MAX_BYTES_WRITE_AT_ONCE)
                        {
                            bInfiniteLoopFlag	=	false; //for exiting the infinte while loop
                            break;
                        }

                        size	=	size	-	MAX_BYTES_WRITE_AT_ONCE;

                        //	Sleep(10);
                    } //Ending of Buffering of packets


                    //write 1Mb of buffer
                    int ret	=	TransmitData(pchPacketBuffer, nPacketBufferSize);

#else
                        int ret	=	TransmitData(buffer, count);
#endif
                        if(ret	!=	0)
                        {
                            //data was not sent
                            if(pchPacketBuffer	!=	NULL)
                                delete pchPacketBuffer;

                            fclose(pFile);
                            return ret	*	1000;
                        }
                        else
                        {
                            //data sent
                            if(pchPacketBuffer	!=	NULL)
                                delete pchPacketBuffer;
                        }
                    } //ending of infinite while loop

                    fclose(pFile);
                }
                else
                {
                    // unable to open file
#ifdef DEBUG_PRINTS_ON
                    printf("FileWrite, File access denied \n");
#endif
                    return -2;
                }
            }
            else
            {
#ifdef DEBUG_PRINTS_ON
                printf("File not found \n");
#endif
                //file not found
                return -1;
            }

            return 0;
        }



        int EthernetAPI::MemWrite(SPPUDeviceTypeEtherent devType, unsigned int startAddress, unsigned int size,  char *pchData)
        {

#ifdef ONE_SOCKET
            while(size	>	0)
            {
                if(size	<	MAX_BYTES_WRITE_AT_ONCE)
                {
                    CProtocol objPktProtocol;
                    char *byArrPkt	=	NULL;
                    int nPktLen	=	objPktProtocol.mPktBulkWrite(startAddress, pchData, size, &byArrPkt);

                    if(byArrPkt	==	NULL)
                        return -4;


                    int ret	=	TransmitData(byArrPkt, nPktLen);

                    if(ret	!=	0)
                        return ret	*	100;

                    break;
                }
                else
                {
                    CProtocol objPktProtocol;
                    char *byArrPkt	=	NULL;
                    int nPktLen	=	objPktProtocol.mPktBulkWrite(startAddress, pchData, MAX_BYTES_WRITE_AT_ONCE, &byArrPkt);

                    if(byArrPkt	==	NULL)
                        return -4;


                    int ret	=	TransmitData(byArrPkt, nPktLen);

                    if(ret	!=	0)
                        return ret	*	100;

                    char byArrPktResp[16];
                    int iResult	=	-100000;

                    iResult = recv(objSocketCommand, byArrPktResp, 16, 0);
                    if ( iResult > 0 )
                    {

#ifdef DEBUG_PRINTS_ON
                        printf("Bytes received: %d\n", iResult);
#endif
                    }
                    else if ( iResult == 0 )
                    {

#ifdef DEBUG_PRINTS_ON
                        printf("Connection closed\n");
#endif

                        delete byArrPkt;
                        return -3;
                    }
                    else
                    {

#ifdef DEBUG_PRINTS_ON
                        printf("recv failed: %d\n", WSAGetLastError());
#endif

                        delete byArrPkt;
                        return -3;
                    }

                    CProtocol objProtoRespPkt;
                    ret	=	objProtoRespPkt.mPktParse(byArrPktResp);
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
                        return -5;
                    }


                }

                pchData	+=	MAX_BYTES_WRITE_AT_ONCE;
                size	-=	MAX_BYTES_WRITE_AT_ONCE;
                //startAddress	+=	MAX_BYTES_WRITE_AT_ONCE;
            }

            return 0;

#else

            //To do:
            //register access calls

            return TransmitData(pchData, size);
#endif



        }




        //HP : modified this function to check response packet for every 16 KiB data.
#if 1
        int EthernetAPI::TransmitData(char *pchData, int len)
        {
            unsigned int a_nLen = len, a_nTotLen = len, a_nSent = 0x0;
            {
                char strDebug[DEBUG_STR_LEN]	=	{'\0'};
                snprintf(strDebug, DEBUG_STR_LEN,"TransmitData:: len:%d \n", len);
                mPrintDebug(strDebug);
            }

#ifdef ONE_SOCKET
            if(objSocketCommand	==	INVALID_SOCKET)
            {

#ifdef DEBUG_PRINTS_ON
                printf("Transmit socket not initialized\n");
#endif
                return -1;
            }
            else
            {
                while(a_nLen)
                {
                    if(a_nLen > (MAX_BYTES_WRITE_AT_ONCE + 0xC))
                        a_nLen = (MAX_BYTES_WRITE_AT_ONCE + 0xC);

                    int iResult	= send(objSocketCommand, pchData + a_nSent, a_nLen, 0);
                    if (iResult == SOCKET_ERROR)
                    {
#ifdef DEBUG_PRINTS_ON
                        {
                            char strDebug[DEBUG_STR_LEN]	=	{'\0'};
                            snprintf(strDebug, DEBUG_STR_LEN,"send Failure:: len:%d \n", a_nLen);
                            mPrintDebug(strDebug);
                        }
                        printf("send failed: %d\n", WSAGetLastError());
#endif
                        return -2;
                    }

                    a_nSent += a_nLen;
                    a_nLen = a_nTotLen - a_nSent;
                    //{
                    //	char strDebug[DEBUG_STR_LEN]	=	{'\0'};
                    //	sprintf_s(strDebug, DEBUG_STR_LEN,"a_nLen = %d, a_nTotLen = %d, a_nSent = %d\n", a_nLen, a_nTotLen, a_nSent);
                    //	mPrintDebug(strDebug);
                    //}


#if 0
                    //Logic to check response packet
                    {
                        char *byArrPkt  =   0;
                        char byArrPktResp[16];

                        iResult = recv(objSocketCommand, byArrPktResp, 16, 0);
                        if ( iResult > 0 )
                        {
#ifdef DEBUG_PRINTS_ON
                            {
                                char strDebug[DEBUG_STR_LEN]	=	{'\0'};
                                sprintf_s(strDebug, DEBUG_STR_LEN,"Response : Bytes read = %d\n", iResult);
                                mPrintDebug(strDebug);
                            }

                            printf("Bytes received: %d\n", iResult);
#endif
                        }
                        else if ( iResult == 0 )
                        {
#ifdef DEBUG_PRINTS_ON
                            {
                                char strDebug[DEBUG_STR_LEN]	=	{'\0'};
                                sprintf_s(strDebug, DEBUG_STR_LEN,"Error : Response : Zero Bytes.\n");
                                mPrintDebug(strDebug);
                            }

                            printf("Connection closed\n");
#endif

                            delete byArrPkt;
                            return -3;
                        }
                        else
                        {
#ifdef DEBUG_PRINTS_ON
                            {
                                char strDebug[DEBUG_STR_LEN]	=	{'\0'};
                                sprintf_s(strDebug, DEBUG_STR_LEN,"Response : Error : Bytes read = %d\n", iResult);
                                mPrintDebug(strDebug);
                            }

                            printf("recv failed: %d\n", WSAGetLastError());
#endif

                            delete byArrPkt;
                            return -3;
                        }

                        CProtocol objProtoRespPkt;
                        int ret	=	objProtoRespPkt.mPktParse(byArrPktResp);
                        ret     *=  10;
                        if(ret < 0)
                        {
                            {
                                char strDebug[DEBUG_STR_LEN]	=	{'\0'};
                                sprintf_s(strDebug, DEBUG_STR_LEN,"Error : Response : Error Parse 1.\n");
                                mPrintDebug(strDebug);
                            }
                            delete byArrPkt;
                            return  ret;
                        }

                        if(objProtoRespPkt.mGetStatus()   ==  0)
                        {
                            delete byArrPkt;
                            //break;
                            //return 0;
                        }
                        else
                        {
                            {
                                char strDebug[DEBUG_STR_LEN]	=	{'\0'};
                                sprintf_s(strDebug, DEBUG_STR_LEN,"Error : Response : Error Parse 2.\n");
                                mPrintDebug(strDebug);
                            }
                            delete byArrPkt;
                            return -5;
                        }
                    }
#endif

                }
            }

            return 0;
#else
            if(objSocketTransmit	==	INVALID_SOCKET)
            {

#ifdef DEBUG_PRINTS_ON
                printf("Transmit socket not initialized\n");
#endif
                return -1;
            }
            else
            {
                int iResult	= send(objSocketTransmit, pchData, len, 0);

                if (iResult == SOCKET_ERROR)
                {

#ifdef DEBUG_PRINTS_ON
                    printf("send failed: %d\n", WSAGetLastError());
#endif

                    return -2;
                }
            }

            return 0;
#endif
        }

#else

        int EthernetAPI::TransmitData(char *pchData, int len)
        {
            {
                char strDebug[DEBUG_STR_LEN]	=	{'\0'};
                sprintf_s(strDebug, DEBUG_STR_LEN,"TransmitData:: len:%d \n", len);
                mPrintDebug(strDebug);
            }

#ifdef ONE_SOCKET
            if(objSocketCommand	==	INVALID_SOCKET)
            {

#ifdef DEBUG_PRINTS_ON
                printf("Transmit socket not initialized\n");
#endif
                return -1;
            }
            else
            {
                int iResult	= send(objSocketCommand, pchData, len, 0);

                if (iResult == SOCKET_ERROR)
                {

#ifdef DEBUG_PRINTS_ON
                    printf("send failed: %d\n", WSAGetLastError());
#endif

                    return -2;
                }
            }

            return 0;
#else
            if(objSocketTransmit	==	INVALID_SOCKET)
            {

#ifdef DEBUG_PRINTS_ON
                printf("Transmit socket not initialized\n");
#endif
                return -1;
            }
            else
            {
                int iResult	= send(objSocketTransmit, pchData, len, 0);

                if (iResult == SOCKET_ERROR)
                {

#ifdef DEBUG_PRINTS_ON
                    printf("send failed: %d\n", WSAGetLastError());
#endif

                    return -2;
                }
            }

            return 0;
#endif
        }

#endif

        int EthernetAPI::RegWrite(unsigned int address, unsigned int data)
        {
            char *byArrPkt  =   0;
            int pktLen	=	0;
            CProtocol objProtocol;
            pktLen	=	objProtocol.mPktRegWrite(address,data,&byArrPkt);

            if(byArrPkt	==	0)
            {

#ifdef DEBUG_PRINTS_ON
                printf("Unable to form Reg Write Packet\n");
#endif
                return -4;
            }

            if(objSocketCommand	==	INVALID_SOCKET)
            {

#ifdef DEBUG_PRINTS_ON
                printf("Command socket not initialized\n");
#endif
                delete byArrPkt;
                return -1;
            }
            else
            {
                int iResult	= send(objSocketCommand, byArrPkt, pktLen, 0);

                if (iResult == SOCKET_ERROR)
                {

#ifdef DEBUG_PRINTS_ON
                    printf("send failed: %d\n", WSAGetLastError());
#endif
                    delete byArrPkt;
                    return -2;
                }
                if(address == 16896)
                {

                    return 0;
                }
                char byArrPktResp[16];

                iResult = recv(objSocketCommand, byArrPktResp, 16, 0);
                if ( iResult > 0 )
                {

#ifdef DEBUG_PRINTS_ON
                    printf("Bytes received: %d\n", iResult);
#endif
                }
                else if ( iResult == 0 )
                {

#ifdef DEBUG_PRINTS_ON
                    printf("Connection closed\n");
#endif

                    delete byArrPkt;
                    return -3;
                }
                else
                {

#ifdef DEBUG_PRINTS_ON
                    printf("recv failed: %d\n", WSAGetLastError());
#endif

                    delete byArrPkt;
                    return -3;
                }

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
                    return -5;
                }
            }

            return 0;
        }


        int EthernetAPI::RegRead(unsigned int address, unsigned int &data)
        {

            char *byArrPkt  =   NULL;
            int pktLen	=	0;
            CProtocol objProtocol;
            char strDebug[DEBUG_STR_LEN]	=	{'\0'};
            snprintf(strDebug, DEBUG_STR_LEN,"address = %d, data = %d\n", address, data);
            mPrintDebug(strDebug);
            pktLen	=	objProtocol.mPktRegRead(address,&byArrPkt);

            if(byArrPkt	==	0)
            {

#ifdef DEBUG_PRINTS_ON
                printf("Unable to form Reg Write Packet\n");
#endif
                return -4;
            }

            if(objSocketCommand	==	INVALID_SOCKET)
            {

#ifdef DEBUG_PRINTS_ON
                printf("Command socket not initialized\n");
#endif

                delete byArrPkt;
                return -1;
            }
            else
            {
                int iResult	= send(objSocketCommand, byArrPkt, pktLen, 0);

                if (iResult == SOCKET_ERROR)
                {

#ifdef DEBUG_PRINTS_ON
                    printf("send failed: %d\n", WSAGetLastError());
#endif
                    delete byArrPkt;
                    return -2;
                }

                char byArrPktResp[16];

                iResult = recv(objSocketCommand, byArrPktResp, 16, 0);
                if ( iResult > 0 )
                {

#ifdef DEBUG_PRINTS_ON
                    printf("Bytes received: %d\n", iResult);
#endif
                }
                else if ( iResult == 0 )
                {

#ifdef DEBUG_PRINTS_ON
                    printf("Connection closed\n");
#endif
                    delete byArrPkt;
                    return -3;
                }
                else
                {

#ifdef DEBUG_PRINTS_ON
                    printf("recv failed: %d\n", WSAGetLastError());
#endif
                    delete byArrPkt;
                    return -3;
                }

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
                    return  -5;
                }
            }

            return 0;
        }

        int EthernetAPI::ConnectSockets(Sockets a_objSockets)
        {
            WSADATA wsaData;
            int iResult;

            DWORD nRecvTimeOut	=	a_objSockets.nTimeOut;

            // Initialize Winsock
            iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
            if (iResult != 0) {

#ifdef DEBUG_PRINTS_ON
                printf("WSAStartup failed: %d\n", iResult);
#endif
                return -1;
            }

            struct addrinfo *result = NULL,
                    *ptr = NULL,
                    hints;

            ZeroMemory( &hints, sizeof(hints) );
            hints.ai_family = AF_UNSPEC;
            hints.ai_socktype = SOCK_STREAM;
            hints.ai_protocol = IPPROTO_TCP;

#ifndef ONE_SOCKET
            if(a_objSockets.objSocketInfoTransmit.pcIpAddress	==	0)
                return -2;

            if(a_objSockets.objSocketInfoTransmit.pcPort	==	0)
                return -2;

            if(a_objSockets.objSocketInfoReceive.pcIpAddress	==	0)
                return -2;

            if(a_objSockets.objSocketInfoReceive.pcPort	==	0)
                return -2;
#endif

            if(a_objSockets.objSocketInfoCommand.pcIpAddress	==	0)
                return -2;

            if(a_objSockets.objSocketInfoCommand.pcPort	==	0)
                return -2;

#ifndef ONE_SOCKET
            /*********************************************** Creating Transmit Socket ***************************************************************/
            if(objSocketTransmit	!=	INVALID_SOCKET)
            {
                closesocket(objSocketTransmit);
                objSocketTransmit	=	INVALID_SOCKET;
            }

            iResult = getaddrinfo(a_objSockets.objSocketInfoTransmit.pcIpAddress, a_objSockets.objSocketInfoTransmit.pcPort, &hints, &result);

            if (iResult != 0)
            {

#ifdef DEBUG_PRINTS_ON
                printf("getaddrinfo failed: %d\n", iResult);
#endif
                WSACleanup();
                return -3;
            }

            // Attempt to connect to the first address returned by
            // the call to getaddrinfo
            ptr = result;

            // Create a SOCKET for connecting to server
            objSocketTransmit = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

            if (objSocketTransmit == INVALID_SOCKET)
            {

#ifdef DEBUG_PRINTS_ON
                printf("Error at socket(): %ld\n", WSAGetLastError());
#endif
                freeaddrinfo(result);
                WSACleanup();
                return -4;
            }

            iResult	=	connect(objSocketTransmit, ptr->ai_addr, (int)ptr->ai_addrlen);
            if(iResult	==	SOCKET_ERROR)
            {
                closesocket(objSocketTransmit);
                objSocketTransmit	=	INVALID_SOCKET;
            }

            freeaddrinfo(result);

            if (objSocketTransmit == INVALID_SOCKET)
            {

#ifdef DEBUG_PRINTS_ON
                printf("Unable to connect to server!\n");
#endif
                WSACleanup();
                return -5;
            }

            setsockopt(objSocketTransmit,SOL_SOCKET, SO_RCVTIMEO,(char *) &nRecvTimeOut,sizeof(DWORD));
            /***************************************************************************************************************************************/


            /*********************************************** Creating Receive Socket ***************************************************************/
            if(objSocketReceive	!=	INVALID_SOCKET)
            {
                closesocket(objSocketReceive);
                objSocketReceive	=	INVALID_SOCKET;
            }

            iResult = getaddrinfo(a_objSockets.objSocketInfoReceive.pcIpAddress, a_objSockets.objSocketInfoReceive.pcPort, &hints, &result);

            if (iResult != 0)
            {

#ifdef DEBUG_PRINTS_ON
                printf("getaddrinfo failed: %d\n", iResult);
#endif
                WSACleanup();
                return -3;
            }

            // Attempt to connect to the first address returned by
            // the call to getaddrinfo
            ptr=result;

            // Create a SOCKET for connecting to server
            objSocketReceive = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

            if (objSocketReceive == INVALID_SOCKET)
            {

#ifdef DEBUG_PRINTS_ON
                printf("Error at socket(): %ld\n", WSAGetLastError());
#endif
                freeaddrinfo(result);
                WSACleanup();
                return -4;
            }

            iResult	=	connect(objSocketReceive, ptr->ai_addr, (int)ptr->ai_addrlen);
            if(iResult	==	SOCKET_ERROR)
            {
                closesocket(objSocketReceive);
                objSocketReceive	=	INVALID_SOCKET;
            }

            freeaddrinfo(result);

            if (objSocketReceive == INVALID_SOCKET)
            {
#ifdef DEBUG_PRINTS_ON
                printf("Unable to connect to server!\n");
#endif
                WSACleanup();
                return -5;
            }

            setsockopt(objSocketReceive,SOL_SOCKET, SO_RCVTIMEO,(char *) &nRecvTimeOut,sizeof(DWORD));
            /***************************************************************************************************************************************/
#endif

            /*********************************************** Creating Command Socket ***************************************************************/
            if(objSocketCommand	!=	INVALID_SOCKET)
            {
                closesocket(objSocketCommand);
                objSocketCommand	=	INVALID_SOCKET;
            }

            iResult = getaddrinfo(a_objSockets.objSocketInfoCommand.pcIpAddress, a_objSockets.objSocketInfoCommand.pcPort, &hints, &result);

            if (iResult != 0)
            {
#ifdef DEBUG_PRINTS_ON
                printf("getaddrinfo failed: %d\n", iResult);
#endif
                WSACleanup();
                return -3;
            }

            // Attempt to connect to the first address returned by
            // the call to getaddrinfo
            ptr=result;

            // Create a SOCKET for connecting to server
            objSocketCommand = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

            if (objSocketCommand == INVALID_SOCKET)
            {

#ifdef DEBUG_PRINTS_ON
                printf("Error at socket(): %ld\n", WSAGetLastError());
#endif
                freeaddrinfo(result);
                WSACleanup();
                return -4;
            }

            iResult	=	connect(objSocketCommand, ptr->ai_addr, (int)ptr->ai_addrlen);
            if(iResult	==	SOCKET_ERROR)
            {
                closesocket(objSocketCommand);
                objSocketCommand	=	INVALID_SOCKET;
            }

            freeaddrinfo(result);

            if (objSocketCommand == INVALID_SOCKET)
            {

#ifdef DEBUG_PRINTS_ON
                printf("Unable to connect to server!\n");
#endif
                WSACleanup();
                return -5;
            }

            setsockopt(objSocketCommand,SOL_SOCKET, SO_RCVTIMEO,(char *) &nRecvTimeOut,sizeof(DWORD));
            bool bTCPNoDelayFlag	=	true;
            setsockopt(objSocketCommand, IPPROTO_TCP, TCP_NODELAY,(char *) &bTCPNoDelayFlag,sizeof(bool));
            /***************************************************************************************************************************************/

            return 0;
        }

        void EthernetAPI::DisconnectSockets()
        {
#ifndef ONE_SOCKET
            closesocket(objSocketTransmit);
            objSocketTransmit	=	INVALID_SOCKET;

            closesocket(objSocketReceive);
            objSocketReceive	=	INVALID_SOCKET;

#endif

            closesocket(objSocketCommand);
            objSocketCommand	=	INVALID_SOCKET;
        }

        //Used to read data from ethernet.

        int EthernetAPI::FileRead(SPPUDeviceTypeEtherent devType, unsigned int startAddress, unsigned int size,  char *pchFilePath,  unsigned int *numBytesRdSuccess)
        {
            FILE * pFile;
            errno_t err;

            mPrintDebug((char *)"==========================================================================");
            {
                char strDebug[DEBUG_STR_LEN]	=	{'\0'};
                snprintf(strDebug, DEBUG_STR_LEN,"FileRead:: startAddress:%d size:%d Filename:%s", startAddress, size, pchFilePath);
                mPrintDebug(strDebug);
            }
            mPrintDebug((char *)"==========================================================================");

            err	=	fopen_s(&pFile, pchFilePath, "wb");

            if( err != 0)
            {
                mPrintDebug((char *)"Unable to open file\n");
                return -2;
            }

            char rDevBuf[MAX_BULK_READ_PACKET_SIZE];
            unsigned int numByRdSuccess=0;
            unsigned int numByToRd = size;
            unsigned int numByReadDone = 0;

            while(numByToRd)
            {
                if(numByToRd > MAX_BULK_READ_DATA_SIZE)
                    numByToRd = MAX_BULK_READ_DATA_SIZE;

                err = MemReadInternal(devType, startAddress, numByToRd, rDevBuf, &numByRdSuccess);
                if(err)
                {
                    mPrintDebug((char *)"==========================================================================");
                    {
                        char strDebug[DEBUG_STR_LEN]	=	{'\0'};
                        snprintf(strDebug, DEBUG_STR_LEN,"Ethernet DEBUG :: numByRdSuccess :%d\n", numByRdSuccess);
                        mPrintDebug(strDebug);
                    }
                    mPrintDebug((char *)"==========================================================================");

                    numByRdSuccess = 0;
                    break;
                }
                numByReadDone += numByRdSuccess;
                fwrite(rDevBuf, 1, numByRdSuccess, pFile);

                if(numByReadDone >= size)
                    break;

                numByToRd = size - numByReadDone;
            }

            *numBytesRdSuccess = numByReadDone;

            fclose(pFile);

            return 0;
        }

        int EthernetAPI::FileRead_10GB(SPPUDeviceTypeEtherent devType, unsigned long long startAddress, unsigned long long size,  char *pchFilePath,  unsigned long long *numBytesRdSuccess)
        {
            FILE * pFile;
            errno_t err;

            mPrintDebug((char *)"==========================================================================\n");
            {
                char strDebug[DEBUG_STR_LEN]	=	{'\0'};
                snprintf(strDebug, DEBUG_STR_LEN,"FileRead:: startAddress:%lld size:%lld Filename:%s", startAddress, size, pchFilePath);
                mPrintDebug(strDebug);
            }
            mPrintDebug((char *)"==========================================================================\n");

            err	=	fopen_s(&pFile, pchFilePath, "wb");
            if( err != 0)
            {
                mPrintDebug((char *)"Unable to open file\n");
                return -2;
            }

            char rDevBuf[MAX_BULK_READ_PACKET_SIZE];
            unsigned int numByRdSuccess=0;
            unsigned long long numByToRd = size;
            unsigned long long numByReadDone = 0;

            while(numByToRd)
            {
                if(numByToRd > MAX_BULK_READ_DATA_SIZE)
                    numByToRd = MAX_BULK_READ_DATA_SIZE;


                err = MemReadInternal(devType, startAddress, numByToRd, rDevBuf, &numByRdSuccess);

                if(err)
                {
                    numByRdSuccess = 0;
                    break;
                }

                numByReadDone += (unsigned long long)numByRdSuccess;

                fwrite(rDevBuf, 1, numByRdSuccess, pFile);
				fflush(pFile);
                if(numByReadDone >= size)
                    break;

                numByToRd = size - numByReadDone;
                *numBytesRdSuccess = numByReadDone;
            }

            *numBytesRdSuccess = numByReadDone;
			fflush(pFile);
            fclose(pFile);

            return 0;
        }



        int EthernetAPI::MemRead(SPPUDeviceTypeEtherent devType, unsigned int startAddress, unsigned int size, char *pchData)
        {
            unsigned int numBytesRdSuccess=0;
            return MemReadInternal(devType, startAddress, size, pchData , &numBytesRdSuccess);
        }


        int EthernetAPI::MemReadInternal(SPPUDeviceTypeEtherent devType, unsigned int startAddress, unsigned int size, char *pchData, unsigned int *numBytesRdSuccess)
        {
            char *byArrPkt  =   NULL;
            int pktLen	=	0;
            int respSizeExp = 0;
            int respSize = 0;
            CProtocol objProtocol;
            char strDebug[DEBUG_STR_LEN]	=	{'\0'};
            {
                snprintf(strDebug, DEBUG_STR_LEN,"MemReadInternal:: startAddress:%x size:%x \n", startAddress, size);
                mPrintDebug(strDebug);
            }

            //Create DDR Read comamnd packet
            pktLen	=	objProtocol.mPktBulkRead(startAddress, (size + 12) , &byArrPkt);//mPktBulkRead(FPGA_DDR_ACCESS_ADDR, (size + 12) , &byArrPkt);

            if(byArrPkt	==	0)
            {
                mPrintDebug((char *)"Error: Unable to form Bulk Read Packet \n");
                return -4;
            }

            if(objSocketCommand	==	INVALID_SOCKET)
            {
                mPrintDebug((char *)"Error: Command socket not initialized \n");
                delete byArrPkt;
                return -1;
            }

            int iResult	= send(objSocketCommand, byArrPkt, pktLen, 0);

            if (iResult == SOCKET_ERROR)
            {
                mPrintDebug((char *)"Error: send failed \n");
                delete byArrPkt;
                return -2;
            }

            char byArrPktResp[MAX_BULK_READ_PACKET_SIZE+12] =	{'\0'};	;
            respSizeExp = (size + 12);
            respSize = 0;

            int i=0;
            for(i=0 ;  (respSize < respSizeExp) && (i < 5000); i++)
            {
                iResult = recv(objSocketCommand, (byArrPktResp + respSize), (respSizeExp-respSize) , 0);

                if ( iResult > 0 )
                {
                    //sprintf_s(strDebug, DEBUG_STR_LEN,"	socket_rx::  Req:%d  response:%d\n",  (respSizeExp-respSize), iResult);

                    //mPrintDebug(strDebug);
                    //Sleep(1);

                    respSize += iResult;

                }
                else if ( iResult == 0 )
                {
                    mPrintDebug((char *)"Error: Connection Closed \n");
                    delete byArrPkt;
                    return -3;
                }
                else
                {
                    mPrintDebug((char *)"Error: Return zero size \n");
                    delete byArrPkt;
                    return -3;
                }
            }

            if(i == 5000)
            {
                mPrintDebug((char *)"Error: Timeout\n");
                delete byArrPkt;
                return -4;
            }

            CProtocol objProtoRespPkt;
            int ret	=	objProtoRespPkt.mPktParseBulkRead(byArrPktResp);
            ret     *=  10;
            if(ret < 0)
            {
                if(ret == -1)
                    mPrintDebug((char *)"Error: wrong magic byte \n");
                else
                    mPrintDebug((char *)"Error: mPktParseBulkRead \n");
                delete byArrPkt;
                return  ret;
            }

            if(objProtoRespPkt.mGetStatus()   !=  0)
            {
                mPrintDebug((char *)"Error: Wrong Status \n");
                delete byArrPkt;
                return  -5;
            }

            unsigned int data	=	objProtoRespPkt.mGetRegisterData();


            //for(i=16372;i<=16396;i++)
            //{
            //	sprintf_s(strDebug, DEBUG_STR_LEN,"byArrPktResp :  %c\n",  byArrPktResp[i]);
            //	mPrintDebug(strDebug);
            //}


            memcpy(pchData, byArrPktResp+12, respSize-12);
            *numBytesRdSuccess = respSize-12;

            {
                char strDebug[DEBUG_STR_LEN]	=	{'\0'};
                snprintf(strDebug, DEBUG_STR_LEN,"MemReadInternal Done::  startAddress:%d size:%d  numByRdSuccess:%d", startAddress, size, *numBytesRdSuccess);
                mPrintDebug(strDebug);
            }

            //Shiv
            //recv(objSocketCommand, (byArrPktResp + respSize), (respSizeExp-respSize) , 0);

            delete byArrPkt;
            return 0;
        }

        EthernetAPI::~EthernetAPI(void)
        {
        }

        void EthernetAPI::mPrintDebug(char *a_strDebug)
        {
            FILE * pFile;
            errno_t err;

            if((access("debug_eth.log", 2)) != -1)
            {
                err	=	fopen_s(&pFile,"debug_eth.log","a");
                if(err	==	0)
                {
                    fputs(a_strDebug, pFile);
                    fputs("\n",pFile);
                    fclose(pFile);
                }
                else
                {
                    printf("debug_eth.log access denied \n");
                }
            }
        }


#if 0
#include "EthernetAPI.h"

        //__HP__6
#ifndef FPGA_DDR_RESOLUTION
#define FPGA_DDR_RESOLUTION		4096
#endif

        //#include <iostream>
        //#include <fstream>
        //using namespace std;

        using namespace MiddleEthernetAPI;


#define FPGA_DDR_ACCESS_ADDR				0x00004200	//TODO : Mohit
#define FPGA_SPI_FLASH_ACCESS_ADDR			0x00004204 
#define MAX_BULK_READ_PACKET_SIZE			16 * 1024	
#define MAX_BULK_READ_DATA_SIZE			    16 * 1024 - 12	
#define DEBUG_STR_LEN						200

        EthernetAPI::EthernetAPI(void)
        {
            objSocketTransmit	=	INVALID_SOCKET;
            objSocketReceive	=	INVALID_SOCKET;
            objSocketCommand	=	INVALID_SOCKET;
        }

        //__HP__6:
#if 1
        int EthernetAPI::FileWrite(SPPUDeviceTypeEtherent devType, unsigned int startAddress, unsigned int size,  char *pchFilePath)
        {

#if 0
#define BUFFERED_PACKETS_SIZE  0x100000  //1 MB
#else
#define BUFFERED_PACKETS_SIZE  0x10A000  //1MB & 40 kB
#endif

            //__HP__2; Adding support : if File Size is not multiple of 64 bytes then append 0s to make it multiple of 64 bytes.
            int SizeDifference = 0, SizeModify = 0;
            FILE * pFile;
            errno_t err;

            mPrintDebug("==========================================================================\n");
            {
                char strDebug[DEBUG_STR_LEN]	=	{'\0'};
                sprintf_s(strDebug, DEBUG_STR_LEN,"FileWrite:: startAddress:%d size:%d Filename:%s", startAddress, size, pchFilePath);
                mPrintDebug(strDebug);
            }
            mPrintDebug("==========================================================================\n");

            if((_access(pchFilePath, 2)) != -1)
            {
                err	=	fopen_s(&pFile, pchFilePath, "rb");
                if(err	==	0)
                {
                    bool bInfiniteLoopFlag	=	true;
                    while(bInfiniteLoopFlag)
                    {
                        char *pchPacketBuffer = new char[BUFFERED_PACKETS_SIZE];
                        int nPacketBufferSize = 0;
                        //__HP__5; remove this

                        //FILE * Eth_Wr;
                        //fopen_s(&Eth_Wr, "C:\\Program Files (x86)\\LOGIC-FRUIT\\SPPU_LRDE\\bin\\Eth_Wr.bin", "wb+");

                        while(nPacketBufferSize < (BUFFERED_PACKETS_SIZE - (MAX_BYTES_WRITE_AT_ONCE + 12))) //buffer packets, till we have 1 MB of (16K + 12 size packets)
                        {
                            char buffer[MAX_BYTES_WRITE_AT_ONCE] = {'\0'};
                            int count = 0;

                            if(size < MAX_BYTES_WRITE_AT_ONCE)
                            {
#if 1
                                if(size	>	0)
                                    count = fread(buffer, sizeof(char), size, pFile);
#else
                                count = size;
#endif
                            }
                            else
                            {
#if 1
                                count = fread(buffer, sizeof(char), MAX_BYTES_WRITE_AT_ONCE, pFile);
#else
                                count =	MAX_BYTES_WRITE_AT_ONCE;
#endif
                            }
#if 1
                            //__HP__6: Adding logic to append zeros in Buffer if data is not multiple of 4096
                            if((SizeDifference = (count % FPGA_DDR_RESOLUTION)) != 0)
                            {
                                SizeModify = (FPGA_DDR_RESOLUTION - SizeDifference);
                                memset(buffer + count, '\0', SizeModify);
                                count += SizeModify;
                            }
                            //__HP__6 : Till here.
#endif
                            //__HP__6: Remove this line
                            //fwrite(buffer, 1, count, Eth_Wr);
#if 1
                            if(ferror(pFile))
                            {
                                fclose(pFile);

#ifdef DEBUG_PRINTS_ON
                                perror( "Read error" );
#endif
                                if(pchPacketBuffer != NULL)
                                    delete pchPacketBuffer;
                                return -3;
                            }
#endif

#ifdef ONE_SOCKET
                            CProtocol objPktProtocol;
#if 1
                            char *byArrPkt = NULL;
                            int nPktLen = objPktProtocol.mPktBulkWrite(startAddress, buffer, count, &byArrPkt);
#else
                            char *byArrPkt = buffer;
                            int nPktLen     = count;
#endif
                            if(byArrPkt == NULL)
                            {
                                fclose(pFile);
                                if(pchPacketBuffer != NULL)
                                    delete pchPacketBuffer;
                                return -4;
                            }

                            memcpy(pchPacketBuffer + nPacketBufferSize, byArrPkt, nPktLen);
                            nPacketBufferSize += nPktLen;

                            delete byArrPkt; //packet has been buffered, freeing up memory

                            if(size <= MAX_BYTES_WRITE_AT_ONCE)
                            {
                                bInfiniteLoopFlag = false; //for exiting the infinte while loop
                                break;
                            }

                            size = size - MAX_BYTES_WRITE_AT_ONCE;
                        } //Ending of Buffering of packets

                        //fwrite(pchPacketBuffer, 1, nPacketBufferSize, Eth_Wr);
                        //__HP__5: remove this
                        //fclose(Eth_Wr);

                        //write 1Mb of buffer
                        int ret	= TransmitData(pchPacketBuffer, nPacketBufferSize);

#else
                            int ret	= TransmitData(buffer, count);
#endif

                            if(ret != 0)
                            {
                                //data was not sent
                                if(pchPacketBuffer != NULL)
                                    delete pchPacketBuffer;
                                fclose(pFile);
                                return ret	*	1000;
                            }
                            else
                            {
                                //data sent
                                if(pchPacketBuffer	!=	NULL)
                                    delete pchPacketBuffer;
                            }
                        } //ending of infinite while loop
                        fclose(pFile);
                    }
                    else
                    {
                        // unable to open file
#ifdef DEBUG_PRINTS_ON
                        printf("FileWrite, File access denied \n");
#endif
                        return -2;
                    }
                }
                else
                {
                    //file not found
#ifdef DEBUG_PRINTS_ON
                    printf("File not found \n");
#endif
                    return -1;
                }

                return 0;
            }
#else
        int EthernetAPI::FileWrite(SPPUDeviceTypeEtherent devType, unsigned int startAddress, unsigned int size,  char *pchFilePath)
        {

#if 0
#define BUFFERED_PACKETS_SIZE  0x100000  //1 MB
#else
#define BUFFERED_PACKETS_SIZE  0x10A000  //1MB & 40 kB
#endif

            //__HP__2; Adding support : if File Size is not multiple of 64 bytes then append 0s to make it multiple of 64 bytes.
            int SizeDifference = 0, SizeModify = 0;
            FILE * pFile;
            errno_t err;

            mPrintDebug("==========================================================================\n");
            {
                char strDebug[DEBUG_STR_LEN]	=	{'\0'};
                sprintf_s(strDebug, DEBUG_STR_LEN,"FileWrite:: startAddress:%d size:%d Filename:%s", startAddress, size, pchFilePath);
                mPrintDebug(strDebug);
            }
            mPrintDebug("==========================================================================\n");

            if((_access(pchFilePath, 2)) != -1)
            {
                err	=	fopen_s(&pFile, pchFilePath, "rb");
                if(err	==	0)
                {
                    bool bInfiniteLoopFlag	=	true;
                    while(bInfiniteLoopFlag)
                    {
                        char *pchPacketBuffer = new char[BUFFERED_PACKETS_SIZE];
                        int nPacketBufferSize = 0;
                        //__HP__5; remove this

                        //FILE * Eth_Wr;
                        //fopen_s(&Eth_Wr, "C:\\Program Files (x86)\\LOGIC-FRUIT\\SPPU_LRDE\\bin\\Eth_Wr.bin", "wb+");

                        while(nPacketBufferSize < (BUFFERED_PACKETS_SIZE - (MAX_BYTES_WRITE_AT_ONCE + 12))) //buffer packets, till we have 1 MB of (16K + 12 size packets)
                        {
                            char buffer[MAX_BYTES_WRITE_AT_ONCE] = {'\0'};
                            int count = 0;

                            if(size < MAX_BYTES_WRITE_AT_ONCE)
                            {
#if 1
                                if(size	>	0)
                                    count = fread(buffer, sizeof(char), size, pFile);
#if 0
                                //__HP__2: Adding logic to append zeros in Buffer if data is not multiple of 64
                                if((SizeDifference = (count % 64)) != 0)
                                {
                                    SizeModify = (64 - SizeDifference);
                                    memset(buffer + count, '\0', SizeModify);
                                    count += SizeModify;
                                }
                                //__HP__2 : Till here.
#endif
#else
                                count = size;
#endif
                            }
                            else
                            {
#if 1
                                count = fread(buffer, sizeof(char), MAX_BYTES_WRITE_AT_ONCE, pFile);
#else
                                count =	MAX_BYTES_WRITE_AT_ONCE;
#endif
                            }
#if 1
                            //__HP__2: Adding logic to append zeros in Buffer if data is not multiple of 64
                            if((SizeDifference = (count % 64)) != 0)
                            {
                                SizeModify = (64 - SizeDifference);
                                memset(buffer + count, '\0', SizeModify);
                                count += SizeModify;
                            }
                            //__HP__2 : Till here.
#endif
                            //__HP__5: Remove this line
                            //fwrite(buffer, 1, count, Eth_Wr);
#if 1
                            if(ferror(pFile))
                            {
                                fclose(pFile);

#ifdef DEBUG_PRINTS_ON
                                perror( "Read error" );
#endif
                                if(pchPacketBuffer != NULL)
                                    delete pchPacketBuffer;
                                return -3;
                            }
#endif

#ifdef ONE_SOCKET
                            CProtocol objPktProtocol;
#if 1
                            char *byArrPkt = NULL;
                            int nPktLen = objPktProtocol.mPktBulkWrite(startAddress, buffer, count, &byArrPkt);
#else
                            char *byArrPkt = buffer;
                            int nPktLen     = count;
#endif
                            if(byArrPkt == NULL)
                            {
                                fclose(pFile);
                                if(pchPacketBuffer != NULL)
                                    delete pchPacketBuffer;
                                return -4;
                            }

                            memcpy(pchPacketBuffer + nPacketBufferSize, byArrPkt, nPktLen);
                            nPacketBufferSize += nPktLen;

                            delete byArrPkt; //packet has been buffered, freeing up memory

                            if(size <= MAX_BYTES_WRITE_AT_ONCE)
                            {
                                bInfiniteLoopFlag = false; //for exiting the infinte while loop
                                break;
                            }

                            size = size - MAX_BYTES_WRITE_AT_ONCE;
                        } //Ending of Buffering of packets

                        //fwrite(pchPacketBuffer, 1, nPacketBufferSize, Eth_Wr);
                        //__HP__5: remove this
                        //fclose(Eth_Wr);

                        //write 1Mb of buffer
                        int ret	= TransmitData(pchPacketBuffer, nPacketBufferSize);

#else
                            int ret	= TransmitData(buffer, count);
#endif

                            if(ret != 0)
                            {
                                //data was not sent
                                if(pchPacketBuffer != NULL)
                                    delete pchPacketBuffer;
                                fclose(pFile);
                                return ret	*	1000;
                            }
                            else
                            {
                                //data sent
                                if(pchPacketBuffer	!=	NULL)
                                    delete pchPacketBuffer;
                            }
                        } //ending of infinite while loop
                        fclose(pFile);
                    }
                    else
                    {
                        // unable to open file
#ifdef DEBUG_PRINTS_ON
                        printf("FileWrite, File access denied \n");
#endif
                        return -2;
                    }
                }
                else
                {
                    //file not found
#ifdef DEBUG_PRINTS_ON
                    printf("File not found \n");
#endif
                    return -1;
                }

                return 0;
            }
#endif



            int EthernetAPI::MemWrite(SPPUDeviceTypeEtherent devType, unsigned int startAddress, unsigned int size,  char *pchData)
            {

#ifdef ONE_SOCKET
                while(size	>	0)
                {
                    if(size	<	MAX_BYTES_WRITE_AT_ONCE)
                    {
                        CProtocol objPktProtocol;
                        char *byArrPkt	=	NULL;
                        int nPktLen	=	objPktProtocol.mPktBulkWrite(startAddress, pchData, size, &byArrPkt);

                        if(byArrPkt	==	NULL)
                            return -4;


                        int ret	=	TransmitData(byArrPkt, nPktLen);

                        if(ret	!=	0)
                            return ret	*	100;

                        break;
                    }
                    else
                    {
                        CProtocol objPktProtocol;
                        char *byArrPkt	=	NULL;
                        int nPktLen	=	objPktProtocol.mPktBulkWrite(startAddress, pchData, MAX_BYTES_WRITE_AT_ONCE, &byArrPkt);

                        if(byArrPkt	==	NULL)
                            return -4;


                        int ret	=	TransmitData(byArrPkt, nPktLen);

                        if(ret	!=	0)
                            return ret	*	100;

                        char byArrPktResp[16];
                        int iResult	=	-100000;

                        iResult = recv(objSocketCommand, byArrPktResp, 16, 0);
                        if ( iResult > 0 )
                        {

#ifdef DEBUG_PRINTS_ON
                            printf("Bytes received: %d\n", iResult);
#endif
                        }
                        else if ( iResult == 0 )
                        {

#ifdef DEBUG_PRINTS_ON
                            printf("Connection closed\n");
#endif

                            delete byArrPkt;
                            return -3;
                        }
                        else
                        {

#ifdef DEBUG_PRINTS_ON
                            printf("recv failed: %d\n", WSAGetLastError());
#endif

                            delete byArrPkt;
                            return -3;
                        }

                        CProtocol objProtoRespPkt;
                        ret	=	objProtoRespPkt.mPktParse(byArrPktResp);
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
                            return -5;
                        }
                    }

                    pchData	+=	MAX_BYTES_WRITE_AT_ONCE;
                    size	-=	MAX_BYTES_WRITE_AT_ONCE;
                    //startAddress	+=	MAX_BYTES_WRITE_AT_ONCE;
                }
                return 0;

#else

                //To do:
                //register access calls

                return TransmitData(pchData, size);
#endif
            }

            int EthernetAPI::TransmitData(char *pchData, int len)
            {
                {
                    char strDebug[DEBUG_STR_LEN]	=	{'\0'};
                    sprintf_s(strDebug, DEBUG_STR_LEN,"TransmitData:: len:%d \n", len);
                    mPrintDebug(strDebug);
                }

#ifdef ONE_SOCKET
                if(objSocketCommand	==	INVALID_SOCKET)
                {

#ifdef DEBUG_PRINTS_ON
                    printf("Transmit socket not initialized\n");
#endif
                    return -1;
                }
                else
                {
                    int iResult	= send(objSocketCommand, pchData, len, 0);

                    if (iResult == SOCKET_ERROR)
                    {

#ifdef DEBUG_PRINTS_ON
                        printf("send failed: %d\n", WSAGetLastError());
#endif

                        return -2;
                    }
                }

                return 0;
#else
                if(objSocketTransmit	==	INVALID_SOCKET)
                {

#ifdef DEBUG_PRINTS_ON
                    printf("Transmit socket not initialized\n");
#endif
                    return -1;
                }
                else
                {
                    int iResult	= send(objSocketTransmit, pchData, len, 0);

                    if (iResult == SOCKET_ERROR)
                    {

#ifdef DEBUG_PRINTS_ON
                        printf("send failed: %d\n", WSAGetLastError());
#endif

                        return -2;
                    }
                }

                return 0;
#endif
            }

            int EthernetAPI::RegWrite(unsigned int address, unsigned int data)
            {
                char *byArrPkt  =   0;
                int pktLen	=	0;
                CProtocol objProtocol;
                pktLen	=	objProtocol.mPktRegWrite(address,data,&byArrPkt);

                if(byArrPkt	==	0)
                {

#ifdef DEBUG_PRINTS_ON
                    printf("Unable to form Reg Write Packet\n");
#endif
                    return -4;
                }

                if(objSocketCommand	==	INVALID_SOCKET)
                {

#ifdef DEBUG_PRINTS_ON
                    printf("Command socket not initialized\n");
#endif
                    delete byArrPkt;
                    return -1;
                }
                else
                {
                    int iResult	= send(objSocketCommand, byArrPkt, pktLen, 0);

                    if (iResult == SOCKET_ERROR)
                    {

#ifdef DEBUG_PRINTS_ON
                        printf("send failed: %d\n", WSAGetLastError());
#endif
                        delete byArrPkt;
                        return -2;
                    }
                    if(address == 16896)
                    {

                        return 0;
                    }
                    char byArrPktResp[16];

                    iResult = recv(objSocketCommand, byArrPktResp, 16, 0);
                    if ( iResult > 0 )
                    {

#ifdef DEBUG_PRINTS_ON
                        printf("Bytes received: %d\n", iResult);
#endif
                    }
                    else if ( iResult == 0 )
                    {

#ifdef DEBUG_PRINTS_ON
                        printf("Connection closed\n");
#endif

                        delete byArrPkt;
                        return -3;
                    }
                    else
                    {

#ifdef DEBUG_PRINTS_ON
                        printf("recv failed: %d\n", WSAGetLastError());
#endif

                        delete byArrPkt;
                        return -3;
                    }

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
                        return -5;
                    }
                }

                return 0;
            }


            int EthernetAPI::RegRead(unsigned int address, unsigned int &data)
            {
                char *byArrPkt  =   NULL;
                int pktLen	=	0;
                CProtocol objProtocol;
                pktLen	=	objProtocol.mPktRegRead(address,&byArrPkt);

                if(byArrPkt	==	0)
                {

#ifdef DEBUG_PRINTS_ON
                    printf("Unable to form Reg Write Packet\n");
#endif
                    return -4;
                }

                if(objSocketCommand	==	INVALID_SOCKET)
                {

#ifdef DEBUG_PRINTS_ON
                    printf("Command socket not initialized\n");
#endif

                    delete byArrPkt;
                    return -1;
                }
                else
                {
                    int iResult	= send(objSocketCommand, byArrPkt, pktLen, 0);

                    if (iResult == SOCKET_ERROR)
                    {

#ifdef DEBUG_PRINTS_ON
                        printf("send failed: %d\n", WSAGetLastError());
#endif
                        delete byArrPkt;
                        return -2;
                    }

                    char byArrPktResp[16];

                    iResult = recv(objSocketCommand, byArrPktResp, 16, 0);
                    if ( iResult > 0 )
                    {

#ifdef DEBUG_PRINTS_ON
                        printf("Bytes received: %d\n", iResult);
#endif
                    }
                    else if ( iResult == 0 )
                    {

#ifdef DEBUG_PRINTS_ON
                        printf("Connection closed\n");
#endif
                        delete byArrPkt;
                        return -3;
                    }
                    else
                    {

#ifdef DEBUG_PRINTS_ON
                        printf("recv failed: %d\n", WSAGetLastError());
#endif
                        delete byArrPkt;
                        return -3;
                    }

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
                        return  -5;
                    }
                }

                return 0;
            }

            int EthernetAPI::ConnectSockets(Sockets a_objSockets)
            {
                WSADATA wsaData;
                int iResult;

                DWORD nRecvTimeOut	=	a_objSockets.nTimeOut;

                // Initialize Winsock
                iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
                if (iResult != 0) {

#ifdef DEBUG_PRINTS_ON
                    printf("WSAStartup failed: %d\n", iResult);
#endif
                    return -1;
                }

                struct addrinfo *result = NULL,
                        *ptr = NULL,
                        hints;

                ZeroMemory( &hints, sizeof(hints) );
                hints.ai_family = AF_UNSPEC;
                hints.ai_socktype = SOCK_STREAM;
                hints.ai_protocol = IPPROTO_TCP;

#ifndef ONE_SOCKET
                if(a_objSockets.objSocketInfoTransmit.pcIpAddress	==	0)
                    return -2;

                if(a_objSockets.objSocketInfoTransmit.pcPort	==	0)
                    return -2;

                if(a_objSockets.objSocketInfoReceive.pcIpAddress	==	0)
                    return -2;

                if(a_objSockets.objSocketInfoReceive.pcPort	==	0)
                    return -2;
#endif

                if(a_objSockets.objSocketInfoCommand.pcIpAddress	==	0)
                    return -2;

                if(a_objSockets.objSocketInfoCommand.pcPort	==	0)
                    return -2;

#ifndef ONE_SOCKET
                /*********************************************** Creating Transmit Socket ***************************************************************/
                if(objSocketTransmit	!=	INVALID_SOCKET)
                {
                    closesocket(objSocketTransmit);
                    objSocketTransmit	=	INVALID_SOCKET;
                }

                iResult = getaddrinfo(a_objSockets.objSocketInfoTransmit.pcIpAddress, a_objSockets.objSocketInfoTransmit.pcPort, &hints, &result);

                if (iResult != 0)
                {

#ifdef DEBUG_PRINTS_ON
                    printf("getaddrinfo failed: %d\n", iResult);
#endif
                    WSACleanup();
                    return -3;
                }

                // Attempt to connect to the first address returned by
                // the call to getaddrinfo
                ptr = result;

                // Create a SOCKET for connecting to server
                objSocketTransmit = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

                if (objSocketTransmit == INVALID_SOCKET)
                {

#ifdef DEBUG_PRINTS_ON
                    printf("Error at socket(): %ld\n", WSAGetLastError());
#endif
                    freeaddrinfo(result);
                    WSACleanup();
                    return -4;
                }

                iResult	=	connect(objSocketTransmit, ptr->ai_addr, (int)ptr->ai_addrlen);
                if(iResult	==	SOCKET_ERROR)
                {
                    closesocket(objSocketTransmit);
                    objSocketTransmit	=	INVALID_SOCKET;
                }

                freeaddrinfo(result);

                if (objSocketTransmit == INVALID_SOCKET)
                {

#ifdef DEBUG_PRINTS_ON
                    printf("Unable to connect to server!\n");
#endif
                    WSACleanup();
                    return -5;
                }

                setsockopt(objSocketTransmit,SOL_SOCKET, SO_RCVTIMEO,(char *) &nRecvTimeOut,sizeof(DWORD));
                /***************************************************************************************************************************************/


                /*********************************************** Creating Receive Socket ***************************************************************/
                if(objSocketReceive	!=	INVALID_SOCKET)
                {
                    closesocket(objSocketReceive);
                    objSocketReceive	=	INVALID_SOCKET;
                }

                iResult = getaddrinfo(a_objSockets.objSocketInfoReceive.pcIpAddress, a_objSockets.objSocketInfoReceive.pcPort, &hints, &result);

                if (iResult != 0)
                {

#ifdef DEBUG_PRINTS_ON
                    printf("getaddrinfo failed: %d\n", iResult);
#endif
                    WSACleanup();
                    return -3;
                }

                // Attempt to connect to the first address returned by
                // the call to getaddrinfo
                ptr=result;

                // Create a SOCKET for connecting to server
                objSocketReceive = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

                if (objSocketReceive == INVALID_SOCKET)
                {

#ifdef DEBUG_PRINTS_ON
                    printf("Error at socket(): %ld\n", WSAGetLastError());
#endif
                    freeaddrinfo(result);
                    WSACleanup();
                    return -4;
                }

                iResult	=	connect(objSocketReceive, ptr->ai_addr, (int)ptr->ai_addrlen);
                if(iResult	==	SOCKET_ERROR)
                {
                    closesocket(objSocketReceive);
                    objSocketReceive	=	INVALID_SOCKET;
                }

                freeaddrinfo(result);

                if (objSocketReceive == INVALID_SOCKET)
                {
#ifdef DEBUG_PRINTS_ON
                    printf("Unable to connect to server!\n");
#endif
                    WSACleanup();
                    return -5;
                }

                setsockopt(objSocketReceive,SOL_SOCKET, SO_RCVTIMEO,(char *) &nRecvTimeOut,sizeof(DWORD));
                /***************************************************************************************************************************************/
#endif

                /*********************************************** Creating Command Socket ***************************************************************/
                if(objSocketCommand	!=	INVALID_SOCKET)
                {
                    closesocket(objSocketCommand);
                    objSocketCommand	=	INVALID_SOCKET;
                }

                iResult = getaddrinfo(a_objSockets.objSocketInfoCommand.pcIpAddress, a_objSockets.objSocketInfoCommand.pcPort, &hints, &result);

                if (iResult != 0)
                {
#ifdef DEBUG_PRINTS_ON
                    printf("getaddrinfo failed: %d\n", iResult);
#endif
                    WSACleanup();
                    return -3;
                }

                // Attempt to connect to the first address returned by
                // the call to getaddrinfo
                ptr=result;

                // Create a SOCKET for connecting to server
                objSocketCommand = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

                if (objSocketCommand == INVALID_SOCKET)
                {

#ifdef DEBUG_PRINTS_ON
                    printf("Error at socket(): %ld\n", WSAGetLastError());
#endif
                    freeaddrinfo(result);
                    WSACleanup();
                    return -4;
                }

                iResult	=	connect(objSocketCommand, ptr->ai_addr, (int)ptr->ai_addrlen);
                if(iResult	==	SOCKET_ERROR)
                {
                    closesocket(objSocketCommand);
                    objSocketCommand	=	INVALID_SOCKET;
                }

                freeaddrinfo(result);

                if (objSocketCommand == INVALID_SOCKET)
                {

#ifdef DEBUG_PRINTS_ON
                    printf("Unable to connect to server!\n");
#endif
                    WSACleanup();
                    return -5;
                }

                setsockopt(objSocketCommand,SOL_SOCKET, SO_RCVTIMEO,(char *) &nRecvTimeOut,sizeof(DWORD));
                bool bTCPNoDelayFlag	=	true;
                setsockopt(objSocketCommand, IPPROTO_TCP, TCP_NODELAY,(char *) &bTCPNoDelayFlag,sizeof(bool));
                /***************************************************************************************************************************************/

                return 0;
            }

            void EthernetAPI::DisconnectSockets()
            {
#ifndef ONE_SOCKET
                closesocket(objSocketTransmit);
                objSocketTransmit	=	INVALID_SOCKET;

                closesocket(objSocketReceive);
                objSocketReceive	=	INVALID_SOCKET;

#endif

                closesocket(objSocketCommand);
                objSocketCommand	=	INVALID_SOCKET;
            }

            int EthernetAPI::FileRead(SPPUDeviceTypeEtherent devType, unsigned int startAddress, unsigned int size,  char *pchFilePath,  unsigned int *numBytesRdSuccess)
            {
                FILE * pFile;
                errno_t err;

                mPrintDebug("==========================================================================\n");
                {
                    char strDebug[DEBUG_STR_LEN]	=	{'\0'};
                    sprintf_s(strDebug, DEBUG_STR_LEN,"FileRead:: startAddress:%d size:%d Filename:%s", startAddress, size, pchFilePath);
                    mPrintDebug(strDebug);
                }
                mPrintDebug("==========================================================================\n");

                err	=	fopen_s(&pFile, pchFilePath, "wb");
                if( err != 0)
                {
                    mPrintDebug("Unable to open file\n");
                    return -2;
                }

                char rDevBuf[MAX_BULK_READ_PACKET_SIZE];
                unsigned int numByRdSuccess=0;
                unsigned int numByToRd = size;
                unsigned int numByReadDone = 0;

                while(numByToRd)
                {
                    if(numByToRd > MAX_BULK_READ_DATA_SIZE)
                        numByToRd = MAX_BULK_READ_DATA_SIZE;


                    err = MemReadInternal(devType, startAddress, numByToRd, rDevBuf, &numByRdSuccess);

                    if(err)
                    {
                        numByRdSuccess = 0;
                        break;
                    }

                    numByReadDone += numByRdSuccess;

                    fwrite(rDevBuf, 1, numByRdSuccess, pFile);

                    if(numByReadDone >= size)
                        break;

                    numByToRd = size - numByReadDone;
                }

                *numBytesRdSuccess = numByReadDone;

                fclose(pFile);

                return 0;
            }



            int EthernetAPI::MemRead(SPPUDeviceTypeEtherent devType, unsigned int startAddress, unsigned int size, char *pchData)
            {
                unsigned int numBytesRdSuccess=0;
                return MemReadInternal(devType, startAddress, size, pchData , &numBytesRdSuccess);
            }


            int EthernetAPI::MemReadInternal(SPPUDeviceTypeEtherent devType, unsigned int startAddress, unsigned int size, char *pchData, unsigned int *numBytesRdSuccess)
            {
                char *byArrPkt  =   NULL;
                int pktLen	=	0;
                int respSizeExp = 0;
                int respSize = 0;
                CProtocol objProtocol;

                {
                    char strDebug[DEBUG_STR_LEN]	=	{'\0'};
                    sprintf_s(strDebug, DEBUG_STR_LEN,"MemReadInternal:: startAddress:%d size:%d \n", startAddress, size);
                    mPrintDebug("-----------------------------------------------\n");
                    mPrintDebug(strDebug);
                }

                //Create DDR Read comamnd packet
                pktLen	=	objProtocol.mPktBulkRead(FPGA_DDR_ACCESS_ADDR, (size + 12) , &byArrPkt);

                if(byArrPkt	==	0)
                {
                    mPrintDebug("Error: Unable to form Bulk Read Packet \n");
                    return -4;
                }

                if(objSocketCommand	==	INVALID_SOCKET)
                {
                    mPrintDebug("Error: Command socket not initialized \n");
                    delete byArrPkt;
                    return -1;
                }

                int iResult	= send(objSocketCommand, byArrPkt, pktLen, 0);

                if (iResult == SOCKET_ERROR)
                {
                    mPrintDebug("Error: send failed \n");
                    delete byArrPkt;
                    return -2;
                }

                char byArrPktResp[MAX_BULK_READ_PACKET_SIZE];

                respSizeExp = (size + 12);
                respSize = 0;

                int i=0;
                for(i=0 ;  (respSize < respSizeExp) && (i < 10); i++)
                {
                    iResult = recv(objSocketCommand, (byArrPktResp + respSize), (respSizeExp-respSize) , 0);

                    if ( iResult > 0 )
                    {
                        char strDebug[DEBUG_STR_LEN]	=	{'\0'};
                        sprintf_s(strDebug, DEBUG_STR_LEN,"	socket_rx::  Req:%d  response:%d\n",  (respSizeExp-respSize), iResult);
                        mPrintDebug(strDebug);
                        respSize += iResult;
                    }
                    else if ( iResult == 0 )
                    {
                        mPrintDebug("Error: Connection Closed \n");
                        delete byArrPkt;
                        return -3;
                    }
                    else
                    {
                        mPrintDebug("Error: Return zero size \n");
                        delete byArrPkt;
                        return -3;
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

                {
                    char strDebug[DEBUG_STR_LEN]	=	{'\0'};
                    sprintf_s(strDebug, DEBUG_STR_LEN,"MemReadInternal Done::  startAddress:%d size:%d  numByRdSuccess:%d", startAddress, size, *numBytesRdSuccess);
                    mPrintDebug(strDebug);
                }

                delete byArrPkt;
                return 0;
            }

            EthernetAPI::~EthernetAPI(void)
            {
            }

            void EthernetAPI::mPrintDebug(char *a_strDebug)
            {
                FILE * pFile;
                errno_t err;

                if((_access("debug_eth.log", 2)) != -1)
                {
                    err	=	fopen_s(&pFile,"debug_eth.log","a");
                    if(err	==	0)
                    {
                        fputs(a_strDebug, pFile);
                        fputs("\n",pFile);
                        fclose(pFile);
                    }
                    else
                    {
                        printf("debug_eth.log access denied \n");
                    }
                }
            }
#endif
