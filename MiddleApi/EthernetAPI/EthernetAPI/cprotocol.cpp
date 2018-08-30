#include "cprotocol.h"

CProtocol::CProtocol()
{
    m_nPacketLength     =   0;
    m_nRegisterAddress  =   0;
    m_nRegisterData     =   0;
    m_chCommand         =   '\0';
    m_nMagicBytes       =   0;
    m_nStatus           =   0;
}

ushort CProtocol::mPktBulkWrite(uint a_nRegisterAddress, char *a_byBuff, uint a_nBuffLen, char** a_byArrPacket)
{
	int nPacketInitialLen	=	12	+	a_nBuffLen;
	*a_byArrPacket	=	new char[nPacketInitialLen];

    m_nPacketLength =   0;
	char *byArrPacket;
	byArrPacket	=	*a_byArrPacket;

	memset(byArrPacket,'\0',nPacketInitialLen);

    ushort nMagicByte =   SEND_MAGIC_BYTE;
    uchar *pchMagicByte;
    pchMagicByte =  (uchar *) &nMagicByte;
	mMemCpy(byArrPacket,pchMagicByte,2);
    m_nPacketLength +=  2;

    //length bytes (2 bytes)
	ushort nLen	=	nPacketInitialLen;
	uchar *pchPktLen	=	(uchar *) &nLen;
	mMemCpy(byArrPacket	+	m_nPacketLength,pchPktLen,2);
    m_nPacketLength +=  2;

    //cmnd bytes (4 bytes)
	char chCommand[4];
	chCommand[0]	=	'\0';
	chCommand[1]	=	CMD_REG_WRITE; //0x1:RW, 0x2:RR, 0x3:Action
	chCommand[2]	=	'\0';
	chCommand[3]	=	'\0';

	memcpy(byArrPacket	+	m_nPacketLength, chCommand,4);

    m_nPacketLength +=  4;

    uchar *pchRegisterAddress;
    pchRegisterAddress  =   (uchar *)&a_nRegisterAddress;
	mMemCpy(byArrPacket	+	m_nPacketLength,pchRegisterAddress,4);
    m_nPacketLength +=  4;

	memcpy(byArrPacket	+	m_nPacketLength, a_byBuff, a_nBuffLen);

	m_nPacketLength	+=	a_nBuffLen;

	return m_nPacketLength;
}

ushort CProtocol::mPktRegWrite(uint a_nRegisterAddress, uint a_nRegisterData, char** a_byArrPacket)
{
	*a_byArrPacket	=	new char[16];

    m_nPacketLength =   0;
	char *byArrPacket;
	byArrPacket	=	*a_byArrPacket;

	memset(byArrPacket,'\0',16);

    ushort nMagicByte =   SEND_MAGIC_BYTE;
    uchar *pchMagicByte;
    pchMagicByte =  (uchar *) &nMagicByte;
	mMemCpy(byArrPacket,pchMagicByte,2);
    m_nPacketLength +=  2;

    //length bytes (2 bytes)


	ushort nLen	=	16;
	uchar *pchPktLen	=	(uchar *) &nLen;
	mMemCpy(byArrPacket	+	m_nPacketLength,pchPktLen,2);
    m_nPacketLength +=  2;

    //cmnd bytes (4 bytes)
	char chCommand[4];
	chCommand[0]	=	'\0';
	chCommand[1]	=	CMD_REG_WRITE; //0x1:RW, 0x2:RR, 0x3:Action
	chCommand[2]	=	'\0';
	chCommand[3]	=	'\0';

	memcpy(byArrPacket	+	m_nPacketLength, chCommand,4);

    m_nPacketLength +=  4;

    uchar *pchRegisterAddress;
    pchRegisterAddress  =   (uchar *)&a_nRegisterAddress;
	mMemCpy(byArrPacket	+	m_nPacketLength,pchRegisterAddress,4);
    m_nPacketLength +=  4;

    uchar *pchRegisterData;
    pchRegisterData  =   (uchar *)&a_nRegisterData;
	mMemCpy(byArrPacket	+	m_nPacketLength,pchRegisterData,4);
    m_nPacketLength +=  4;

    return m_nPacketLength;
}

ushort CProtocol::mPktBulkRead(uint a_nRegisterAddress, uint a_nPacketLen, char **a_byArrPacket)
{
    *a_byArrPacket	=	new char[16];

    m_nPacketLength =   0;
	char *byArrPacket;
	byArrPacket	=	*a_byArrPacket;

	memset(byArrPacket,'\0',16);

    ushort nMagicByte =   SEND_MAGIC_BYTE;
    uchar *pchMagicByte;
    pchMagicByte =  (uchar *) &nMagicByte;
	mMemCpy(byArrPacket,pchMagicByte,2);
    m_nPacketLength +=  2;

    //length bytes (2 bytes)
	ushort nLen	=	(ushort) a_nPacketLen;
	uchar *pchPktLen	=	(uchar *) &nLen;
	mMemCpy(byArrPacket	+	m_nPacketLength,pchPktLen,2);
    m_nPacketLength +=  2;

    //cmnd bytes (4 bytes)
	char chCommand[4];
	chCommand[0]	=	'\0';
	chCommand[1]	=	CMD_REG_READ; //0x1:RW, 0x2:RR, 0x3:Action
	chCommand[2]	=	'\0';
	chCommand[3]	=	'\0';

	memcpy(byArrPacket	+	m_nPacketLength, chCommand,4);
    m_nPacketLength +=  4;

    uchar *pchRegisterAddress;
    pchRegisterAddress  =   (uchar *)&a_nRegisterAddress;
	mMemCpy(byArrPacket	+	m_nPacketLength,pchRegisterAddress,4);
    m_nPacketLength +=  4;

	memset(byArrPacket	+	m_nPacketLength,'\0',4);
    m_nPacketLength +=  4;

    return m_nPacketLength;
}

ushort CProtocol::mPktRegRead(uint a_nRegisterAddress, char **a_byArrPacket)
{
    *a_byArrPacket	=	new char[16];

    m_nPacketLength =   0;
	char *byArrPacket;
	byArrPacket	=	*a_byArrPacket;

	memset(byArrPacket,'\0',16);

    ushort nMagicByte =   SEND_MAGIC_BYTE;
    uchar *pchMagicByte;
    pchMagicByte =  (uchar *) &nMagicByte;
	mMemCpy(byArrPacket,pchMagicByte,2);
    m_nPacketLength +=  2;

    //length bytes (2 bytes)
	ushort nLen	=	16;
	uchar *pchPktLen	=	(uchar *) &nLen;
	mMemCpy(byArrPacket	+	m_nPacketLength,pchPktLen,2);
    m_nPacketLength +=  2;

    //cmnd bytes (4 bytes)
	char chCommand[4];
	chCommand[0]	=	'\0';
	chCommand[1]	=	CMD_REG_READ; //0x1:RW, 0x2:RR, 0x3:Action
	chCommand[2]	=	'\0';
	chCommand[3]	=	'\0';

	memcpy(byArrPacket	+	m_nPacketLength, chCommand,4);
    m_nPacketLength +=  4;

    uchar *pchRegisterAddress;
    pchRegisterAddress  =   (uchar *)&a_nRegisterAddress;
	mMemCpy(byArrPacket	+	m_nPacketLength,pchRegisterAddress,4);
    m_nPacketLength +=  4;

	memset(byArrPacket	+	m_nPacketLength,'\0',4);
    m_nPacketLength +=  4;

    return m_nPacketLength;
}

ushort CProtocol::mPktBulkReadUART(uint a_nRegisterAddress, uint a_nRegData, uint a_nPacketLen, char **a_byArrPacket)
{
	*a_byArrPacket	=	new char[16];

	m_nPacketLength =   0;
	char *byArrPacket;
	byArrPacket	=	*a_byArrPacket;

	memset(byArrPacket,'\0',16);

	ushort nMagicByte =   SEND_MAGIC_BYTE;
	uchar *pchMagicByte;
	pchMagicByte =  (uchar *) &nMagicByte;
	mMemCpy(byArrPacket,pchMagicByte,2);
	m_nPacketLength +=  2;

	//length bytes (2 bytes)
	ushort nLen	=	(ushort) a_nPacketLen;
	uchar *pchPktLen	=	(uchar *) &nLen;
	mMemCpy(byArrPacket	+	m_nPacketLength,pchPktLen,2);
	m_nPacketLength +=  2;

	//cmnd bytes (4 bytes)
	char chCommand[4];
	chCommand[0]	=	'\0';
	chCommand[1]	=	CMD_REG_READ; //0x1:RW, 0x2:RR, 0x3:Action
	chCommand[2]	=	'\0';
	chCommand[3]	=	'\0';

	memcpy(byArrPacket	+	m_nPacketLength, chCommand,4);
	m_nPacketLength +=  4;

	uchar *pchRegisterAddress;
	pchRegisterAddress  =   (uchar *)&a_nRegisterAddress;
	mMemCpy(byArrPacket	+	m_nPacketLength,pchRegisterAddress,4);
	m_nPacketLength +=  4;

	uchar *pchRegisterData;
	pchRegisterData  =   (uchar *)&a_nRegData;
	mMemCpy(byArrPacket	+	m_nPacketLength,pchRegisterData,4);
	m_nPacketLength +=  4;

	return m_nPacketLength;
}

ushort CProtocol::mPktBulkWriteUART(uint a_nRegisterAddress, uint a_nRegData, uint a_nPacketLen, char *byArrPacket)
{
	m_nPacketLength =   0;
	memset(byArrPacket,'\0',16);

	ushort nMagicByte =   SEND_MAGIC_BYTE;
	uchar *pchMagicByte;
	pchMagicByte =  (uchar *) &nMagicByte;
	mMemCpy(byArrPacket,pchMagicByte,2);
	m_nPacketLength +=  2;

	//length bytes (2 bytes)
	ushort nLen	=	(ushort) a_nPacketLen;
	uchar *pchPktLen	=	(uchar *) &nLen;
	mMemCpy(byArrPacket	+	m_nPacketLength,pchPktLen,2);
	m_nPacketLength +=  2;

	//cmnd bytes (4 bytes)
	char chCommand[4];
	chCommand[0]	=	'\0';
	chCommand[1]	=	CMD_REG_WRITE; //0x1:RW, 0x2:RR, 0x3:Action
	chCommand[2]	=	'\0';
	chCommand[3]	=	'\0';

	memcpy(byArrPacket	+	m_nPacketLength, chCommand,4);
	m_nPacketLength +=  4;

	uchar *pchRegisterAddress;
	pchRegisterAddress  =   (uchar *)&a_nRegisterAddress;
	mMemCpy(byArrPacket	+	m_nPacketLength,pchRegisterAddress,4);
	m_nPacketLength +=  4;

	uchar *pchRegisterData;
	pchRegisterData  =   (uchar *)&a_nRegData;
	mMemCpy(byArrPacket	+	m_nPacketLength,pchRegisterData,4);
	m_nPacketLength +=  4;

	return m_nPacketLength;
}

/*ushort CProtocol::mPktAction(CProtocol::ACTION_TYPE a_enActionType, QByteArray &byArrPacket)
{
    m_nPacketLength =   0;

    ushort nMagicByte =   SEND_MAGIC_BYTE;
    uchar *pchMagicByte;
    pchMagicByte =  (uchar *) &nMagicByte;

    //send magic bytes (2 bytes)
    byArrPacket.append(pchMagicByte[0]);
    byArrPacket.append(pchMagicByte[1]);
    m_nPacketLength +=  2;

    //length bytes (2 bytes)
    byArrPacket.append('\0');
    byArrPacket.append('\0');
    m_nPacketLength +=  2;

    //cmnd bytes (4 bytes)
    byArrPacket.append('\0');
    byArrPacket.append(CMD_ACTION);     //0x1:RW, 0x2:RR, 0x3:Action
    byArrPacket.append('\0');
    byArrPacket.append('\0');
    m_nPacketLength +=  4;

    unsigned char chActionType  =   0x01    <<  (int)a_enActionType;
    byArrPacket.append(chActionType);
    byArrPacket.append('\0');
    byArrPacket.append('\0');
    byArrPacket.append('\0');
    m_nPacketLength +=  4;

    byArrPacket.append('\0');
    byArrPacket.append('\0');
    byArrPacket.append('\0');
    byArrPacket.append('\0');
    m_nPacketLength +=  4;

    uchar *pchPktLen;
    pchPktLen   =   (uchar *)&m_nPacketLength;
    byArrPacket[2]  =   pchPktLen[0];
    byArrPacket[3]  =   pchPktLen[1];

    return m_nPacketLength;
}

ushort CProtocol::mPktSetProp(CProtocol::SET_PROP a_enProp, uint a_nValue, QByteArray &byArrPacket)
{
    m_nPacketLength =   0;

    ushort nMagicByte =   SEND_MAGIC_BYTE;
    uchar *pchMagicByte;
    pchMagicByte =  (uchar *) &nMagicByte;

    //send magic bytes (2 bytes)
    byArrPacket.append(pchMagicByte[0]);
    byArrPacket.append(pchMagicByte[1]);
    m_nPacketLength +=  2;

    //length bytes (2 bytes)
    byArrPacket.append('\0');
    byArrPacket.append('\0');
    m_nPacketLength +=  2;

    //cmnd bytes (4 bytes)
    byArrPacket.append('\0');
    byArrPacket.append(CMD_GET_PROP);     //0x1:RW, 0x2:RR, 0x3:Action
    byArrPacket.append('\0');
    byArrPacket.append('\0');
    m_nPacketLength +=  4;

    uchar *pchPropType;
    uint nPropType      =   (int)a_enProp;
    pchPropType  =   (uchar *)&nPropType;
    byArrPacket.append(pchPropType[0]);
    byArrPacket.append(pchPropType[1]);
    byArrPacket.append(pchPropType[2]);
    byArrPacket.append(pchPropType[3]);
    m_nPacketLength +=  4;

    uchar *pchData;
    pchData  =   (uchar *)&a_nValue;
    byArrPacket.append(pchData[0]);
    byArrPacket.append(pchData[1]);
    byArrPacket.append(pchData[2]);
    byArrPacket.append(pchData[3]);
    m_nPacketLength +=  4;

    uchar *pchPktLen;
    pchPktLen   =   (uchar *)&m_nPacketLength;
    byArrPacket[2]  =   pchPktLen[0];
    byArrPacket[3]  =   pchPktLen[1];

    return m_nPacketLength;
}

ushort CProtocol::mPktReset(QByteArray &byArrPacket)
{

}*/

int CProtocol::mPktParse(char *a_byArrData)
{
    if(a_byArrData  ==  NULL)
        return -5;

    m_nPacketLength             =   0;
    int nParser                 =   -1;
    uchar chArrMagicBytes[2]    =   {'\0'};
    nParser++;
    chArrMagicBytes[0]          =   a_byArrData[nParser];
    nParser++;
    chArrMagicBytes[1]          =   a_byArrData[nParser];

#ifdef BIG_ENDIAN
	mRevStr(chArrMagicBytes, 2);
#endif

    m_nMagicBytes               =   *((uint *)chArrMagicBytes);

    if((m_nMagicBytes    ==  SEND_MAGIC_BYTE) |   (m_nMagicBytes   ==  RECV_MAGIC_BYTE))
    {
        uchar chArrLength[2]    =   {'\0'};
        nParser++;
        chArrLength[0]    =   a_byArrData[nParser];
        nParser++;
        chArrLength[1]    =   a_byArrData[nParser];

#ifdef BIG_ENDIAN
		mRevStr(chArrLength,2);
#endif

        m_nPacketLength         =   *((uint *)chArrLength);

        if(m_nPacketLength  !=  16)
            return -2;

        nParser++;  //NULL Byte

        nParser++;
        m_chCommand =   a_byArrData[nParser];

        nParser+=2;

        uchar chArrStatus[4]    =   {'\0'};
        nParser++;
        chArrStatus[0]          =   a_byArrData[nParser];
        nParser++;
        chArrStatus[1]          =   a_byArrData[nParser];
        nParser++;
        chArrStatus[2]          =   a_byArrData[nParser];
        nParser++;
        chArrStatus[3]          =   a_byArrData[nParser];

#ifdef BIG_ENDIAN
		mRevStr(chArrStatus, 4);
#endif

        m_nStatus               =   *((uint *)chArrStatus);

        uchar chArrValue[4]     =   {'\0'};
        nParser++;
        chArrValue[0]           =   a_byArrData[nParser];
        nParser++;
        chArrValue[1]           =   a_byArrData[nParser];
        nParser++;
        chArrValue[2]           =   a_byArrData[nParser];
        nParser++;
        chArrValue[3]           =   a_byArrData[nParser];

#ifdef BIG_ENDIAN
		mRevStr(chArrValue, 4);
#endif

        m_nRegisterData         =   *((uint *)chArrValue);

    }
    else
    {
        return -1;  // wrong magic byte
    }

    return 0; //successful
}

int CProtocol::mPktParseBulkRead(char *a_byArrData)
{
    if(a_byArrData  ==  NULL)
        return -5;

    m_nPacketLength             =   0;
    int nParser                 =   -1;
    uchar chArrMagicBytes[2]    =   {'\0'};
    nParser++;
    chArrMagicBytes[0]          =   a_byArrData[nParser];
    nParser++;
    chArrMagicBytes[1]          =   a_byArrData[nParser];

#ifdef BIG_ENDIAN
	mRevStr(chArrMagicBytes, 2);
#endif

    m_nMagicBytes               =   *((uint *)chArrMagicBytes);

    if((m_nMagicBytes    ==  SEND_MAGIC_BYTE) |   (m_nMagicBytes   ==  RECV_MAGIC_BYTE))
    {
        uchar chArrLength[2]    =   {'\0'};
        nParser++;
        chArrLength[0]    =   a_byArrData[nParser];
        nParser++;
        chArrLength[1]    =   a_byArrData[nParser];

#ifdef BIG_ENDIAN
		mRevStr(chArrLength,2);
#endif

        m_nPacketLength         =   *((uint *)chArrLength);

		//TBD: Lenght could be any size
        //if(m_nPacketLength  !=  16)
        //    return -2;

        nParser++;  //NULL Byte

        nParser++;
        m_chCommand =   a_byArrData[nParser];

        nParser+=2;

        uchar chArrStatus[4]    =   {'\0'};
        nParser++;
        chArrStatus[0]          =   a_byArrData[nParser];
        nParser++;
        chArrStatus[1]          =   a_byArrData[nParser];
        nParser++;
        chArrStatus[2]          =   a_byArrData[nParser];
        nParser++;
        chArrStatus[3]          =   a_byArrData[nParser];

#ifdef BIG_ENDIAN
		mRevStr(chArrStatus, 4);
#endif

        m_nStatus               =   *((uint *)chArrStatus);

        uchar chArrValue[4]     =   {'\0'};
        nParser++;
        chArrValue[0]           =   a_byArrData[nParser];
        nParser++;
        chArrValue[1]           =   a_byArrData[nParser];
        nParser++;
        chArrValue[2]           =   a_byArrData[nParser];
        nParser++;
        chArrValue[3]           =   a_byArrData[nParser];

#ifdef BIG_ENDIAN
		mRevStr(chArrValue, 4);
#endif

        m_nRegisterData         =   *((uint *)chArrValue);

    }
    else
    {
        return -1;  // wrong magic byte
    }

    return 0; //successful
}

void CProtocol::mRevStr(char *src, size_t n)
{
	char *temp	=	new char[n];

	for(int i	=	0;	i	<	n; i++)
	{
		temp[i]	=	src[n	-	i	-	1];
	}

	delete src;
	src	=	temp;
}

void CProtocol::mRevStr(uchar *src, size_t n)
{
	uchar *temp	=	new uchar[n];

	for(int i	=	0;	i	<	n; i++)
	{
		temp[i]	=	src[n	-	i	-	1];
	}

	memcpy(src,temp,n);
	//delete src;
	delete temp;
}

void CProtocol::mMemCpy(char *dst,	uchar *src, size_t n)
{
#ifdef LIL_ENDIAN
	memcpy(dst,src,n);
#else
	for(int i	=	0;	i	<	n;	i++)
	{
		dst[n	-	i	-	1]	=	src[i];
	}
#endif
}

void CProtocol::mMemCpy(char *dst,	char *src, size_t n)
{
#ifdef LIL_ENDIAN
	memcpy(dst,src,n);
#else
	for(int i	=	0;	i	<	n;	i++)
	{
		dst[n	-	i	-	1]	=	src[i];
	}
#endif
}

void CProtocol::mMemCpy(uchar *dst,	uchar *src, size_t n)
{
#ifdef LIL_ENDIAN
	memcpy(dst,src,n);
#else
	for(int i	=	0;	i	<	n;	i++)
	{
		dst[n	-	i	-	1]	=	src[i];
	}
#endif
}

void CProtocol::mMemCpy(uchar *dst,	char *src, size_t n)
{
#ifdef LIL_ENDIAN
	memcpy(dst,src,n);
#else
	for(int i	=	0;	i	<	n;	i++)
	{
		dst[n	-	i	-	1]	=	src[i];
	}
#endif
}


ushort CProtocol::mGetPacketLength()
{
    return m_nPacketLength;
}

uchar CProtocol::mGetCommand()
{
    return m_chCommand;
}

uint CProtocol::mGetStatus()
{
    return m_nStatus;
}

uint CProtocol::mGetRegisterData()
{
    return m_nRegisterData;
}
