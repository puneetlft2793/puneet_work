#include "stdafx.h"
#include "MiddleAPIWrapper.h"
#include <string> 
//Following definiftion for USB chips used in the produce, must be confuigured.
//Only one must be active at one time.
#ifndef USB_FX3
#define USB_FX3		1
#define USB_FTDI	0
#endif

#ifndef FPGA_DDR_RESOLUTION
#define FPGA_DDR_RESOLUTION		0x8
#endif
#define ARRAY_SIZE_MEM       16
#define ARRAY_SIZE_MEM_SPI       1024
//#define WRITE_DATA_FILE	     "D:\\latest_centroied\\xml2_22.12.15bck\\release\\selftestw.bin"
//#define READ_DATA_FILE       "D:\\latest_centroied\\xml2_22.12.15bck\\release\\selftestw.bin"
using namespace MiddleAPIWrapper;

MiddleAPI::MiddleAPI()
{

}

void MiddleAPI::DefaultSettings(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID)
{
	ProgramDefaultInLMKRegisters(a_enConnectionType, a_nModuleID);
	//ProgramDefaultInDACRegisters(a_enConnectionType, a_nModuleID);
}
void MiddleAPI::DAC_DefaultSettings(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,SPPUDACType enDactype)
{

	ProgramDefaultInDACRegisters(a_enConnectionType, a_nModuleID,enDactype);
}

void MiddleAPI::StartPattern(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID)
{
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_TRAINING_PATTERN1,0xB6B67A7A);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_TRAINING_PATTERN2,0x4545EAEA);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_TRAINING_PATTERN3,0x16161A1A);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_TRAINING_PATTERN4,0xC6C6AAAA);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_TRAINING_PATTERN5,0x00);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_TRAINING_PATTERN_ENABLE,0x1);
}

void MiddleAPI::StopPattern(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID)
{
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_TRAINING_PATTERN_ENABLE,0x0);
}

/*void MiddleAPI::InitFPGA(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID)
{

unsigned int intLMK;
unsigned int intDAC;


FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_GENERAL_PURPOSE_LMK_IN, &intLMK);

if( intLMK == 0)
{
ProgramDefaultInLMKRegisters(a_enConnectionType, a_nModuleID,enDactype);
FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_GENERAL_PURPOSE_LMK_IN,1);
}
FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_GENERAL_PURPOSE_DAC_IN, &intDAC);


if( intDAC == 0)
{
ProgramDefaultInDACRegisters(a_enConnectionType, a_nModuleID,e);
FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_GENERAL_PURPOSE_DAC_IN,1);
}

}*/


long MiddleAPI::ProgramDefaultInLMKRegisters(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID)
{
	mPrintDebug("********************************************DEFAULT SETTINGS FOR LMK APPLIED********************************************************");
	LMKRegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_ADDR1,0x0000010);
	LMKRegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_ADDR2,0x0000010);
	LMKRegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_ADDR3,0x0000010);
	LMKRegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_ADDR4,0x0000010);
	LMKRegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_ADDR5,0x0000010);
	LMKRegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_ADDR6,0x0000010);
	LMKRegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_ADDR7,0x2808800);
	LMKRegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_ADDR8,0x0408800);
	LMKRegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_ADDR9,0x48E0210);
	//LMKRegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_ADDR10,0x0888800);
	LMKRegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_ADDR11,0x48E0210);
	LMKRegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_ADDR12,0x1BF8880);
	LMKRegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_ADDR13,0x098600D);
	LMKRegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_ADDR14,0x1D81033);
	LMKRegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_ADDR15,0x0900000);
	LMKRegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_ADDR16,0x4000400);
	LMKRegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_ADDR17,0x00AA820);

	LMKRegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_ADDR18,0x0000006);
	LMKRegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_ADDR19,0x0080800);
	LMKRegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_ADDR20,0x47D18E0);
	LMKRegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_ADDR21,0x08000C1);
	LMKRegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_ADDR22,0x2EE0180);
	LMKRegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_ADDR23,0x0000EA6);
	LMKRegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_ADDR24,0x0000EA6);

	//Set Init bit in the FPGA
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_GENERAL_PURPOSE_LMK_IN,1);
	return 0;
}

long MiddleAPI::ProgramDefaultInDACRegisters(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID,SPPUDACType enDactype)
{

	mPrintDebug("ProgramDefaultInDACRegisters");
	//DACReset(a_enConnectionType, a_nModuleID);

	//for(int i	=	0;	i	<	3;	i++)
	//	{
	//mPrintDebug("ProgramDefaultInDACRegisters Loop");
	//	DACRegAccessWrite(a_enConnectionType, a_nModuleID, (SPPUDeviceType) i, LFT_SPPU_DAC_WIRE_MODE, 0xF080);
	DefaultInDACRegisters(a_enConnectionType, a_nModuleID, enDactype);


	//DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR0,0x819C);
	//DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR9,0x006F);
	//DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR8,0x1BF);

	// DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR0,0x819C);
	//DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR9,0x9FA0);
	//DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR8,0x6A);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_GENERAL_PURPOSE_DAC_IN,1);
	return 0;
}

void MiddleAPI::DefaultInDACRegisters(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,SPPUDACType enDactype)
{
	unsigned int rd_value = 0;
	switch((SPPUDACType)enDactype)
	{
	case LFT_SPPU_DAC_1:
		mPrintDebug("******************************************************Reset DAC1 *****************************************************************");
		DAC1Reset(a_enConnectionType, a_nModuleID);

		mPrintDebug("********************************************DEFAULT SETTINGS FOR DAC1 APPLIED********************************************************");
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR0,0x019C);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR1,0x100E);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR2,0xF080);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR3,0xF000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR4,0xFDFD);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR5,0x3E40);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR6,0x2E00);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR7,0x0000);

		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR8,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR9,0x8000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR10,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR11,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR12,0x0400);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR13,0x0400);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR14,0x0400);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR15,0x0400);

		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR16,0x3000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR17,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR18,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR19,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR20,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR21,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR22,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR23,0x0000);

		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR24,0x245C);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR25,0x0804);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR26,0x7000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR27,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR28,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR29,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR30,0x1111);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR31,0x1140);

		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR32,0x2201);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR33,0x1B1B);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR34,0xFFFF);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR35,0x0800);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR36,0x7A7A);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR37,0xB6B6);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR38,0xEAEA);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR39,0x4545);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR40,0x1A1A);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR41,0x1616);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR42,0xAAAA);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR43,0xC6C6);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR44,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR45,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR46,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR47,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR48,0x0004);

		//__HP__2; Ask Sudeshna but commenting for now.
		//FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_VERSION_REG, 0x01);

		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_VERSION_REG, &rd_value);
		if(rd_value == 0x01)
		{
			mPrintDebug("**************************Set_IO_LEAKEGE_FOR_BOARD_1**************************");
			DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR0,0x819C);
			DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR9,0x806F);
			DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR8,0x01BF);
		}
		else if(rd_value == 0x02)
		{
			mPrintDebug("**************************Set_IO_LEAKEGE_FOR_BOARD_1**************************");
			DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR0,0x819C);
			DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR9,0x9F8C);
			DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_ADDR8,0x006A);

		}
		break;

	case LFT_SPPU_DAC_2:
		mPrintDebug("******************************************************Reset DAC2 *****************************************************************");
		DAC2Reset(a_enConnectionType, a_nModuleID);

		mPrintDebug("***********************************************************DEFAULT SETTINGS FOR DAC2 APPLIED*******************************************************");
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR0,0x019C);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR1,0x100E);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR2,0xF080);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR3,0xF000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR4,0xFDFD);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR5,0x3E40);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR6,0x2E00);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR7,0x0000);

		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR8,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR9,0x8000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR10,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR11,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR12,0x0400);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR13,0x0400);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR14,0x0400);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR15,0x0400);

		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR16,0x3000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR17,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR18,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR19,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR20,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR21,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR22,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR23,0x0000);

		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR24,0x245C);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR25,0x0804);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR26,0x7000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR27,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR28,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR29,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR30,0x1111);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR31,0x1140);

		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR32,0x2201);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR33,0x1B1B);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR34,0xFFFF);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR35,0x0800);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR36,0x7A7A);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR37,0xB6B6);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR38,0xEAEA);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR39,0x4545);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR40,0x1A1A);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR41,0x1616);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR42,0xAAAA);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR43,0xC6C6);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR44,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR45,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR46,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR47,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR48,0x0004);

		//__HP__2; Ask Sudeshna but commenting for now.
		//FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_VERSION_REG, 0x01);
		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_VERSION_REG, &rd_value);
		if(rd_value == 0x01)
		{
			mPrintDebug("**************************Set_IO_LEAKEGE_FOR_BOARD_1**************************");
			DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR0,0x819C);
			DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR9,0x9FA0);
			DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR8,0x006A);
		}
		else if(rd_value == 0x02)
		{
			mPrintDebug("**************************Set_IO_LEAKEGE_FOR_BOARD_1**************************");
			DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR0,0x819C);
			DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR9,0x9FB0);
			DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_ADDR8,0x004F);

		}
		break;

	case LFT_SPPU_DAC_3:

		mPrintDebug("******************************************************Reset DAC3 *****************************************************************");
		DAC3Reset(a_enConnectionType, a_nModuleID);

		mPrintDebug("********************************************DEFAULT SETTINGS FOR DAC3 APPLIED************************************************************");
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR0,0x019C);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR1,0x100E);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR2,0xF080);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR3,0xF000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR4,0xFDFD);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR5,0x3E40);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR6,0x2E00);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR7,0x0000);

		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR8,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR9,0x8000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR10,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR11,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR12,0x0400);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR13,0x0400);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR14,0x0400);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR15,0x0400);

		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR16,0x3000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR17,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR18,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR19,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR20,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR21,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR22,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR23,0x0000);

		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR24,0x245C);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR25,0x0804);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR26,0x7000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR27,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR28,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR29,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR30,0x1111);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR31,0x1140);

		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR32,0x2201);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR33,0x1B1B);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR34,0xFFFF);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR35,0x0800);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR36,0x7A7A);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR37,0xB6B6);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR38,0xEAEA);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR39,0x4545);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR40,0x1A1A);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR41,0x1616);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR42,0xAAAA);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR43,0xC6C6);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR44,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR45,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR46,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR47,0x0000);
		DACRegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_ADDR48,0x0004);

		break;
	}
	//FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_GENERAL_PURPOSE_DAC_IN,1);
}

void MiddleAPI::DAC1Reset(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID)
{

	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DAC_RESET_set0,0);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DAC_RESET_set3,0);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DAC_RESET_set6,0);

	//__HP__1; Replaced the followinf line.
	//FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DAC_RESET_set8,0);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DAC_RESET_set9,0);


	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DAC_RESET_set0,1);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DAC_RESET_set6,1);
}

void MiddleAPI::DAC2Reset(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID)
{

	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DAC_RESET_set1,0);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DAC_RESET_set4,0);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DAC_RESET_set7,0);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DAC_RESET_set10,0);

	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DAC_RESET_set1,1);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DAC_RESET_set7,1);
}

void MiddleAPI::DAC3Reset(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID)
{
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DAC_RESET_set2,0);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DAC_RESET_set5,0);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DAC_RESET_set8,0);

	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DAC_RESET_set2,1);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DAC_RESET_set8,1);
}

void MiddleAPI::ClearDACS(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID)
{
	for(int i	=	0;	i	<	3; i++)
		DACRegAccessWrite(a_enConnectionType,a_nModuleID, (SPPUDeviceType) i,LFT_SPPU_DAC_IO_TEST_RESULT_CLEAR ,0);
}

long MiddleAPI::UpdateFPGADACDataClockFrequency(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,unsigned int  *FPGADACDataClockFrequency)
{
	int nTimingWindow	=	0xF000;
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_RESET_CLOCK_COUNTER,1);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_RESET_CLOCK_COUNTER,0);

	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_SET_TIMING_WINDOW,nTimingWindow);

	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_START_CLOCK_COUNTER,1);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_START_CLOCK_COUNTER,0);


	unsigned int dataFreq	=	0;
	FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DAC_DATA_CLOCK_FREQUENCY, &dataFreq);

	*FPGADACDataClockFrequency	=	((dataFreq	*	200)  *4)/	nTimingWindow;

	if(dataFreq	==	0)
		return	-1;
	else
		return 0;
}

long MiddleAPI::UpdateFPGAOutClockFrequency(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,unsigned int  *FPGAOutClockFrequency)
{
	int nTimingWindow	=	0xF000;
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_RESET_CLOCK_COUNTER,1);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_RESET_CLOCK_COUNTER,0);

	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_SET_TIMING_WINDOW,nTimingWindow);

	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_START_CLOCK_COUNTER,1);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_START_CLOCK_COUNTER,0);

	unsigned int clockFreq	=	0;
	FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_OUT_CLOCK_FREQUENCY,&clockFreq);


	*FPGAOutClockFrequency		=	(clockFreq	*	200)	/	nTimingWindow;

	if(clockFreq	==	0)
		return	-1;
	else
		return 0;
}

int MiddleAPI::connect(MiddleEthernetAPI::Sockets a_sockets)
{
	mPrintDebug("\nIn connect(SOCKET_CONN)");	

	char strDebug[DEBUG_STR_LEN]	=	{'\0'};

	sprintf_s(strDebug,DEBUG_STR_LEN,"Transmit(%s,%s)",a_sockets.objSocketInfoTransmit.pcIpAddress,a_sockets.objSocketInfoTransmit.pcPort);
	mPrintDebug(strDebug);

	sprintf_s(strDebug,DEBUG_STR_LEN,"Receive(%s,%s)",a_sockets.objSocketInfoReceive.pcIpAddress,a_sockets.objSocketInfoReceive.pcPort);
	mPrintDebug(strDebug);

	sprintf_s(strDebug,DEBUG_STR_LEN,"Info(%s,%s)",a_sockets.objSocketInfoCommand.pcIpAddress,a_sockets.objSocketInfoCommand.pcPort);
	mPrintDebug(strDebug);

	int ret	=	objEthernetAPI.ConnectSockets(a_sockets);

	//if(ret == 0)
	//InitFPGA(LFT_HOST_CONNECTION_ETH, 0);  // modified on 26th aug


	//To Do Sudeshna :
	//FPGA sw read 1st bit
	//if condition(sw FPGA read 1st bit not set execute this block == 0)
	//{
	//int retLMK	=	ProgramDefaultInLMKRegisters(LFT_HOST_CONNECTION_ETH, 0);

	//if(retLMK	!=	0)
	//mPrintDebug("LMK not initialized");

	//  set sw FPGA register 1st bit
	//}




	//if condition(sw FPGA read 2nd bit not set execute this block )
	//int retDAC	=	ProgramDefaultInDACRegisters(LFT_HOST_CONNECTION_ETH, 0);

	//if(retDAC	!=	0)
	//	mPrintDebug("DAC not initialized");

	//To Do Sudeshna :  set sw FPGA register 2nd bit

	return ret;

}

int MiddleAPI::connect(MiddleSerialAPI::SerialInfo a_serialInfo)
{
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};

	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn connect(SERIAL_CONN = %s)", a_serialInfo.pchPortName);
	mPrintDebug(strDebug);

	return objSerialAPI.ConnectSerialPort(a_serialInfo);
}

int MiddleAPI::RegWrite(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType, unsigned int address, unsigned int data)
{
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};

	//sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RegWrite(%d, %d, %d, %08x, %08x)", a_enConnectionType, a_nModuleID, a_enDeviceType, address, data);
	//mPrintDebug(strDebug);

	if((_access("sim_mem.bin", 2)) != -1)
	{
		return SimRegWrite(address, data, a_enDeviceType);
	}
	else
	{

		if(a_enDeviceType	==	LFT_SPPU_DEV_FPGA)
		{
			switch(a_enConnectionType)
			{
			case LFT_HOST_CONNECTION_SER:
				return objSerialAPI.RegWrite(address,data);

			case LFT_HOST_CONNECTION_ETH:
				return objEthernetAPI.RegWrite(address,data);

			case LFT_HOST_CONNECTION_USB:
				return objUsbApi.RegisterWrite(address,data);

			case LFT_HOST_CONNECTION_PCIE:
#if __CHANGES_PCIE__
				return objPcieAPI.RegisterWrite(address, data);
#else
				return RegisterWrite(address,data);
#endif
			}
		}


		else if(a_enDeviceType == LFT_SPPU_DEV_DAC1 || a_enDeviceType == LFT_SPPU_DEV_DAC2 || a_enDeviceType == LFT_SPPU_DEV_DAC3) 
		{
			unsigned int dac_num	=	0;

			switch(a_enDeviceType)
			{
			case LFT_SPPU_DEV_DAC1:
				dac_num = 0;
				break;
			case LFT_SPPU_DEV_DAC2:
				dac_num = 1;
				break;
			case LFT_SPPU_DEV_DAC3:
				dac_num = 2;
				break;
			}

			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_SPPU_FPGA_SPI_DAC_ADR,address); //writing DAC Address
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_SPPU_FPGA_SPI_DAC_NUM,dac_num); // DAC selection
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_SPPU_FPGA_SPI_DAC_WR_VAL,data); //writing DAC data
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_SPPU_FPGA_SPI_DAC_WR, 1); //write enable 1
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_SPPU_FPGA_SPI_DAC_WR, 0); //write enable 0

			int timeout = 5;
			unsigned int val	=	5;
			while(timeout)
			{
				FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_SPI_DAC_READY_READ, &val);
				if(val	==	0)
					break;

				Sleep(1);
				timeout--;
			}
		}
		else if(a_enDeviceType == LFT_SPPU_DEV_LMK04806)
		{

			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_SPPU_FPGA_SPI_LMK_ADR,address);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_SPPU_FPGA_SPI_LMK_WR_VAL,data);

			if(address	<=	5)
			{
				FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_SPPU_FPGA_SPI_LMK_POST_CLOCK,0);
				FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_SPPU_FPGA_SPI_LMK_SYNC_EN_AUTO,0);
			}
			else
			{
				FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_SPPU_FPGA_SPI_LMK_POST_CLOCK,3);
				FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_SPPU_FPGA_SPI_LMK_SYNC_EN_AUTO,1);
			}

			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_SPPU_FPGA_SPI_LMK_WR, 1);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_SPPU_FPGA_SPI_LMK_WR, 0);	

			int timeout = 5;
			unsigned int val	=	5;
			while(timeout)
			{
				FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_SPI_LMK_READY_READ, &val);
				if(val	==	1)
					break;

				Sleep(1);
				timeout--;
			}
		}


		else if(a_enDeviceType == LFT_SPPU_DEV_ATTENUATOR)
		{
			unsigned int atten_num = 0;

			if(address == 0)
			{
				atten_num = 0;
			}
			else if(address == 1)
			{
				atten_num = 1;
			}
			else
			{
				//error handeling
			}

			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_SPPU_FPGA_SPI_ATT_ADR,address); //atten  Address
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_SPPU_FPGA_SPI_ATT_NUM,atten_num); // atten selection
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_SPPU_FPGA_SPI_ATT_WR_VAL,data); //attt  data
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_SPPU_FPGA_SPI_ATT_WR, 1); //write enable 1
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_SPPU_FPGA_SPI_ATT_WR, 0); //write enable 0


			int timeout = 5;
			unsigned int val	=	5;
			while(timeout)
			{
				FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_SPI_ATT_READY_READ, &val);
				if(val	==	1)
					break;

				Sleep(1);
				timeout--;
			}
		}

		return -100; // no switch case matched
	}
}

int MiddleAPI::RegRead(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType, unsigned int address, unsigned int *data)
{
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};
	int ret	=	-100;
	*data	=	0;


	sprintf_s(strDebug, DEBUG_STR_LEN,"\nIn FPGARegAccessWrite(SPPUHostConnectionType ::%d, a_nModuleID :: %d,a_enDeviceType:: %d,Register:: %x,PropValue %x)", a_enConnectionType, a_nModuleID, a_enDeviceType, address, data);
	mPrintDebug(strDebug);
	if((_access("sim_mem.bin", 2)) != -1)
	{
		ret = SimRegRead(address, data, a_enDeviceType);
	}
	else
	{

		if(a_enDeviceType	==	LFT_SPPU_DEV_FPGA)
		{

			switch(a_enConnectionType)
			{
			case LFT_HOST_CONNECTION_SER:
				ret = objSerialAPI.RegRead(address,*data);
				break;

			case LFT_HOST_CONNECTION_ETH:
				ret = objEthernetAPI.RegRead(address,*data);
				break;

			case LFT_HOST_CONNECTION_USB:
				ret = objUsbApi.RegisterRead(address,data);
				break;
			case LFT_HOST_CONNECTION_PCIE:
#if __CHANGES_PCIE__
				ret = objPcieAPI.RegisterRead(address, data);
#else
				ret = RegisterRead(address,data);
#endif
				break;
			}

		}
		else if((a_enDeviceType	== LFT_SPPU_DEV_DAC1) || (a_enDeviceType == LFT_SPPU_DEV_DAC2) || (a_enDeviceType == LFT_SPPU_DEV_DAC3) )
		{
			unsigned int dac_num	=	0;
			switch(a_enDeviceType)
			{
			case LFT_SPPU_DEV_DAC1:
				dac_num = 0;
				break;
			case LFT_SPPU_DEV_DAC2:
				dac_num = 1;
				break;
			case LFT_SPPU_DEV_DAC3:
				dac_num = 2;
				break;
			}

			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_SPPU_FPGA_SPI_DAC_ADR,address); //writing DAC Address
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_SPPU_FPGA_SPI_DAC_NUM,dac_num); // DAC selection

			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_SPPU_FPGA_SPI_DAC_RD, 1); //read enable 1
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_SPPU_FPGA_SPI_DAC_RD, 0); //read enable 0

			int timeout = 5;
			unsigned int val	=	5;
			while(timeout)
			{
				FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_SPI_DAC_READY_READ, &val);
				if(val	==	0)
					break;

				Sleep(1);
				timeout--;
			}

			FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_SPI_DAC_RD_VAL, data); 
		}

		else if(a_enDeviceType == LFT_SPPU_DEV_LMK04806)
		{
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_SPPU_FPGA_SPI_LMK_ADR,address);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_SPPU_FPGA_SPI_LMK_POST_CLOCK,0);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_SPPU_FPGA_SPI_LMK_SYNC_EN_AUTO,0);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_SPPU_FPGA_SPI_LMK_RD, 1);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_SPPU_FPGA_SPI_LMK_RD, 0);	

			int timeout = 5;
			unsigned int val	=	5;
			while(timeout)
			{
				FPGARegAccessRead(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_SPI_LMK_READY_READ, &val);
				if(val	==	1)
					break;

				Sleep(1);
				timeout--;
			}

			FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_SPI_LMK_RD_VAL, data); 
		}
		else if(a_enDeviceType == LFT_SPPU_DEV_ATTENUATOR)
		{
			*data = 0xAAAADEAD;
		}
	}
	//sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RegRead(%d, %d, %d, %08x, %08x)", a_enConnectionType, a_nModuleID, a_enDeviceType, address, *data);
	//mPrintDebug(strDebug);

	return ret;
}
int MiddleAPI::USB_Detect(void)
{
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};
	DWORD numDevs; 
	DWORD i;
	FT_STATUS ftStatus;
	FT_DEVICE_LIST_INFO_NODE *devInfo; 
	mPrintDebug("\n ============================= USB_Detect =================================");

	ftStatus = FT_CreateDeviceInfoList(&numDevs);

	if (ftStatus != FT_OK) 
	{
		mPrintDebug("\n FT_CreateDeviceInfoList Failed "); 
		return 1;
	}
	else
	{
		mPrintDebug("\n FT_CreateDeviceInfoList Successful ");
		if(numDevs == 0)
		{
			sprintf_s(strDebug,DEBUG_STR_LEN,"\n No device Found ");
			mPrintDebug(strDebug);
			return 1;
		}
		else if(numDevs > 0)
		{
			sprintf_s(strDebug,DEBUG_STR_LEN,"\n No. Of device Found : %d",numDevs);
			mPrintDebug(strDebug);
			devInfo = (FT_DEVICE_LIST_INFO_NODE*)malloc(sizeof(FT_DEVICE_LIST_INFO_NODE)*numDevs); // allocate storage for list based on numDevs 
			ftStatus = FT_GetDeviceInfoList(devInfo,&numDevs); // get the device information list
			return 0;
		}
	}
	return 0;
}
int MiddleAPI::connect(SPPUHostConnectionType a_enConnectionType, int a_nConnectionParam)    //eth : IP addr, (0x0A000050) == 10.0.0.80 , USB( No Par), UART( B0: COM Port#, B1: BaudRate)
{
	int ret	= 0;
	mPrintDebug("\n In connect ");	

	char strDebug[DEBUG_STR_LEN]	=	{'\0'};
	sprintf_s(strDebug,DEBUG_STR_LEN,"Info(Param: %08x)",a_nConnectionParam);
	mPrintDebug(strDebug);

	switch(a_enConnectionType)
	{
	case LFT_HOST_CONNECTION_USB:
#if USB_FX3
		ret	=	objUsbApi.OpenDevice();
#elif USB_FTDI
		ret	= MiddleAPI::USB_Detect();
#endif
		break;
#if 0
	case LFT_HOST_CONNECTION_USB_FX3:

		ret	=	objUsbApi.OpenDevice(); //USB 
		break;
#endif
	case LFT_HOST_CONNECTION_ETH:
		//TBD   call  connect(MiddleEthernetAPI::Sockets a_sockets) 
		break;
#if __CHANGES_PCIE__
	case LFT_HOST_CONNECTION_PCIE:
		ret	=	objPcieAPI.OpenDevice(); //PCIE
		break;
#endif
	default:
		break;
	}

	//if(ret == 0)
	//InitFPGA(a_enConnectionType, 0);


	return ret;


}

void MiddleAPI::disconnect(SPPUHostConnectionType a_enConnectionType)
{
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};
	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn disconnect(%d)", a_enConnectionType);
	mPrintDebug(strDebug);

	switch(a_enConnectionType)
	{
	case LFT_HOST_CONNECTION_SER:
		objSerialAPI.DisconnectSerialPort();
		break;

	case LFT_HOST_CONNECTION_ETH:
		objEthernetAPI.DisconnectSockets();
		break;
	case LFT_HOST_CONNECTION_USB:
		objUsbApi.CloseDevice(); //USB 
		break;
#if __CHANGES_PCIE__
	case LFT_HOST_CONNECTION_PCIE:
		objPcieAPI.CloseDevice(); //PCIe
		break;
#endif
	default:
		break;
	}
}

#if 1
long MiddleAPI::MemoryReadFile(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType, unsigned int a_nStartAddress, unsigned int a_nSize, unsigned int *a_nSizeRead,char *a_strFileName)
{


#if 1

	int ret	=	0;

	unsigned int nOffset	=	0;

	unsigned int nWriteIndefinite = LFT_SPPU_IQ_WRITE_INDEFINITE;
	unsigned int nAxisBurstLength = LFT_SPPU_IQ_WRITE_AXIS_BURST_LENGTH;
	unsigned int nReadIndefininte = LFT_SPPU_IQ_READ_INDEFINITE;

	unsigned int nWriteWrapAddr	= 0x0;

	unsigned int nWriteStartAddrMsb	= 0x0;
	unsigned int nReadStartAddrMsb	= 0x0;

	unsigned int nReadWrapAddr = 0x0;
	unsigned int nWriteEndAddressCh2 = 0x0;


	char strDebug[DEBUG_STR_LEN]	=	{'\0'};

	sprintf_s(strDebug, DEBUG_STR_LEN,"\nIn MemoryReadFile(%d, %d, %d, %08x, %d, %x, %s)", a_enConnectionType, a_nModuleID, a_enDeviceType, a_nStartAddress, a_nSize, a_nSizeRead, a_strFileName);
	mPrintDebug(strDebug);


	if(SPPUDeviceType::LFT_SPPU_DEV_DDR == a_enDeviceType)
	{

		nOffset	= LFT_SPPU_DATA_TYPE_IQ_DC1_OFFSET;
		nWriteStartAddrMsb = 0x0;
		nReadStartAddrMsb = 0x0;

		//int SizeModify = 0, SizeDiff = 0;
		//unsigned int SizeModify = 0, SizeDiff = 0;

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_DDR_READ_START_ADDRESS, nOffset);
		//		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_START_ADDRESS_MSB, nWriteStartAddrMsb/*nWriteWrapAddr*/);


		nWriteEndAddressCh2 = a_nSize;

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_DDR_READ_SIZE, nWriteEndAddressCh2/*SizeModify*//*a_nSize*/);
		//		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_SIZE_MSB, 0x0);		//__HARD__

		//FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_INDEFINITE, nWriteIndefinite);

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_DATA_PULSE, 1);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_DATA_PULSE, 0);


		ret	=	MemoryReadFileInternal(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FIXED_ADDRESS_FOR_IQ_PROGRAMMING, nWriteEndAddressCh2/*a_nSize*/, a_nSizeRead, a_strFileName);

		int timeout = 10;
		unsigned int val	=	5;
		while(timeout)
		{
			FPGARegAccessRead(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_DDR_BUSY_CHECK12, &val);
			if(val	==	1)
				break;
			Sleep(100);
			timeout--;
		}
	}


	else if(a_enDeviceType == SPPUDeviceType::LFT_SPPU_DEV_FX3_SDCARD)
	{
		MemoryReadFileInternal(a_enConnectionType, a_nModuleID, a_enDeviceType, a_nStartAddress, a_nSize, a_nSizeRead, a_strFileName);
	}
	return ret;

#endif
}
#else
long MiddleAPI::MemoryReadFile(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType, unsigned int a_nStartAddress, unsigned int a_nSize, unsigned int *a_nSizeRead,char *a_strFileName)
{
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};
	sprintf_s(strDebug, DEBUG_STR_LEN,"\nIn MemoryReadFile(%d, %d, %d, %08x, %d, %x, %s)", a_enConnectionType, a_nModuleID, a_enDeviceType, a_nStartAddress, a_nSize, a_nSizeRead, a_strFileName);
	mPrintDebug(strDebug);
	unsigned long *pnSizeRead;
	long ret;
	unsigned int nOffset	=	0;
	unsigned int nWriteIndefinite = LFT_SPPU_IQ_WRITE_INDEFINITE;
	unsigned int nAxisBurstLength = LFT_SPPU_IQ_WRITE_AXIS_BURST_LENGTH;
	unsigned int nReadWrapAddr	= 0x03FFFFFF;

	// Add logic to read/write some registers only for DDR access independent of Connection type.
	//Harpreet Singh : 1:30 pm, 11 aug 2015.
	if(a_enDeviceType == SPPUDeviceType::LFT_SPPU_DEV_DDR)
	{
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_AXIS_BURST_LENGTH, nAxisBurstLength);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_DDR_READ_START_ADDRESS, nOffset);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_WRAP_ADDRESS, nReadWrapAddr);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_DDR_READ_SIZE, a_nSize);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_INDEFINITE, nWriteIndefinite);

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_DATA_PULSE, 1);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_DATA_PULSE, 0);
	}

	switch(a_enConnectionType)
	{
	case LFT_HOST_CONNECTION_USB:
		pnSizeRead	=	new unsigned long(0);
		ret	=	objUsbApi.RdFileFromSdCard0((UsbApis::DEVICE_TYPES)a_enDeviceType, a_strFileName, a_nStartAddress, a_nSize, pnSizeRead);
		sprintf_s(strDebug, DEBUG_STR_LEN,"returned pnSizeRead:%d", *pnSizeRead);
		mPrintDebug(strDebug);
		*a_nSizeRead	=	(unsigned int) *pnSizeRead;
		delete pnSizeRead;
		return ret;

	case LFT_HOST_CONNECTION_ETH:
		pnSizeRead	=	new unsigned long(0);
		ret	=	objEthernetAPI.FileRead((MiddleEthernetAPI::EthernetAPI::SPPUDeviceTypeEtherent) a_enDeviceType, a_nStartAddress, a_nSize, a_strFileName, (unsigned int *) pnSizeRead);
		sprintf_s(strDebug, DEBUG_STR_LEN,"returned pnSizeRead:%d", *pnSizeRead);
		mPrintDebug(strDebug);
		*a_nSizeRead	=	(unsigned int) *pnSizeRead;
		delete pnSizeRead;
		return ret;

	case LFT_HOST_CONNECTION_PCIE:

		pnSizeRead	=	new unsigned long(0);
		ret	=	FileRecv((DeviceTypesPci) a_enDeviceType, a_strFileName, a_nStartAddress, a_nSize, pnSizeRead);
		sprintf_s(strDebug, DEBUG_STR_LEN,"returned pnSizeRead:%d", *pnSizeRead);
		mPrintDebug(strDebug);
		*a_nSizeRead	=	(unsigned int) *pnSizeRead;
		delete pnSizeRead;
		return ret;
	}
	return -100;
}
#endif

//__HP__11: changinf to write DDR via Memory access tab page.
//This is main entry point for GUI
long MiddleAPI::MemoryWriteFile(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType, unsigned int a_nStartAddress, unsigned int a_nSize, unsigned int *a_nSizeWritten,char *a_strFileName)
{
	int ret	=	0;

	unsigned int nOffset	=	0;

	unsigned int nWriteIndefinite = LFT_SPPU_IQ_WRITE_INDEFINITE;
	unsigned int nAxisBurstLength = LFT_SPPU_IQ_WRITE_AXIS_BURST_LENGTH;
	unsigned int nReadIndefininte = LFT_SPPU_IQ_READ_INDEFINITE;

	unsigned int nWriteWrapAddr	= 0x0;

	unsigned int nWriteStartAddrMsb	= 0x0;
	unsigned int nReadStartAddrMsb	= 0x0;

	unsigned int nReadWrapAddr = 0x0;
	unsigned int nWriteEndAddressCh2 = 0x0;


	char strDebug[DEBUG_STR_LEN]	=	{'\0'};

	sprintf_s(strDebug, DEBUG_STR_LEN,"\nIn MemoryWriteFile(%d, %d, %d, %08x, %d, %x, %s)", a_enConnectionType, a_nModuleID, a_enDeviceType, a_nStartAddress, a_nSize, a_nSizeWritten, a_strFileName);
	mPrintDebug(strDebug);

#if 1
	if(SPPUDeviceType::LFT_SPPU_DEV_DDR == a_enDeviceType)
	{

		nOffset	= LFT_SPPU_DATA_TYPE_IQ_DC1_OFFSET;
		nWriteStartAddrMsb = 0x0;
		nReadStartAddrMsb = 0x0;

		//int SizeModify = 0, SizeDiff = 0;
		unsigned int SizeModify = 0, SizeDiff = 0;

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_START_ADDRESS, nOffset);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_START_ADDRESS_MSB, nWriteStartAddrMsb/*nWriteWrapAddr*/);

		//__HP__4 ; Adding support : if File Size is not multiple of 4096 bytes then append 0s to make it multiple of 64 bytes.
		SizeModify = a_nSize;
		if(SizeModify < FPGA_DDR_RESOLUTION)
			SizeModify = FPGA_DDR_RESOLUTION;

		if((SizeDiff = (SizeModify % FPGA_DDR_RESOLUTION)) != 0)
			SizeModify += (FPGA_DDR_RESOLUTION - SizeDiff);
		//__HP__4 : end;

		//__HP__8; initializing with valid value
		nWriteEndAddressCh2 = SizeModify;

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_SIZE, nWriteEndAddressCh2/*SizeModify*//*a_nSize*/);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_SIZE_MSB, 0x0);		//__HARD__

		//FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_INDEFINITE, nWriteIndefinite);

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_DATA_PULSE, 1);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_DATA_PULSE, 0);


		ret	=	MemoryWriteFileInternal(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FIXED_ADDRESS_FOR_IQ_PROGRAMMING, SizeModify/*a_nSize*/, a_nSizeWritten, a_strFileName);

		int timeout = 10;
		unsigned int val	=	5;
		while(timeout)
		{
			FPGARegAccessRead(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_COMPLETE, &val);
			if(val	==	1)
				break;
			Sleep(100);
			timeout--;
		}
	}

#else
	// Add logic to read/write some registers only for DDR access independent of Connection type.
	//Harpreet Singh : 12:46 pm, 13 aug 2015.
	if(a_enDeviceType == SPPUDeviceType::LFT_SPPU_DEV_DDR)
	{
		unsigned int nOffset	=	0;
		unsigned int nWriteIndefinite = LFT_SPPU_IQ_WRITE_INDEFINITE;
		unsigned int nAxisBurstLength = LFT_SPPU_IQ_WRITE_AXIS_BURST_LENGTH;
		unsigned int nReadIndefininte = LFT_SPPU_IQ_READ_INDEFINITE;

		unsigned int nWriteWrapAddr	= 0x0;
		unsigned int nReadWrapAddr = 0x0;
		nOffset	= LFT_SPPU_DATA_TYPE_IF_OFFSET;
		nWriteWrapAddr = LFT_SPPU_IQ_WRITE_WRAP_ADDR_IF_CHAN;
		nReadWrapAddr = LFT_SPPU_IQ_READ_WRAP_ADDR_IF_CHAN(a_nSize);

		//File pointer //Hp : 12 Aug 2015
		FILE *rdBinFile;

		/* opening the file */
		if(!(rdBinFile = fopen(a_strFileName, "rb")))
		{
			return -1;
		}

		/* Get file size */
		fseek(rdBinFile, 0, SEEK_END);
		DWORD dwFileSize = ftell(rdBinFile);
		fseek(rdBinFile, 0, SEEK_SET);

		// Close the file after getting its data size
		fclose(rdBinFile);

		/* Check for valid data to program */
		if((a_nSize == 0) || (a_nSize > dwFileSize))
		{
			a_nSize = dwFileSize;
		}

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_AXIS_BURST_LENGTH, nAxisBurstLength);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_START_ADDRESS, nOffset);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_WRAP_ADDRESS, nWriteWrapAddr);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_SIZE, a_nSize);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_INDEFINITE, nWriteIndefinite);

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_DATA_PULSE, 1);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_DATA_PULSE, 0);


		ret	=	MemoryWriteFileInternal(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FIXED_ADDRESS_FOR_IQ_PROGRAMMING, a_nSize, a_nSizeWritten, a_strFileName);

		//poll in scase of DDR Access.
		int timeout = 10;
		unsigned int val	=	5;
		while(timeout)
		{
			FPGARegAccessRead(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_COMPLETE, &val);
			if(val	==	1)
				break;

			Sleep(100);
			timeout--;
		}
	}
#endif
	else if(a_enDeviceType == SPPUDeviceType::LFT_SPPU_DEV_FX3_SDCARD)
	{
		MemoryWriteFileInternal(a_enConnectionType, a_nModuleID, a_enDeviceType, a_nStartAddress, a_nSize, a_nSizeWritten, a_strFileName);
	}
	return ret;
}

long MiddleAPI::MemoryReadFileInternal_10GB(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, 
	SPPUDeviceType a_enDeviceType, unsigned long long a_nStartAddress, unsigned long long a_nSize, unsigned long long *a_nSizeRead,
	char *a_strFileName)
{
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};

	unsigned long long *pnSizeWritten;
	//unsigned long long *pnSizeRead;

	long ret	=	-10000;

	/*sprintf_s(strDebug, DEBUG_STR_LEN,"\nIn MemoryReadFileInternal( %x, %s)", a_nSize, a_strFileName);
	mPrintDebug(strDebug);*/

	unsigned long long *pnSizeRead;

	switch(a_enConnectionType)
	{
	case LFT_HOST_CONNECTION_USB:
		pnSizeRead	=	new unsigned long long(0);

		//ret	=	objUsbApi.RdFileFromSdCard0((UsbApis::DEVICE_TYPES)a_enDeviceType, a_strFileName, a_nStartAddress, a_nSize, pnSizeRead);

		*a_nSizeRead	=	(unsigned long long) *pnSizeRead;
		delete pnSizeRead;
		return ret;

	case LFT_HOST_CONNECTION_ETH:
		pnSizeRead	=	new unsigned long long(0);
		ret	=	objEthernetAPI.FileRead_10GB((MiddleEthernetAPI::EthernetAPI::SPPUDeviceTypeEtherent) a_enDeviceType, a_nStartAddress, a_nSize, a_strFileName, (unsigned long long *) pnSizeRead);
		*a_nSizeRead	=	(unsigned long long) *pnSizeRead;
		delete pnSizeRead;
		return ret;

	case LFT_HOST_CONNECTION_PCIE:

		pnSizeRead	=	new unsigned long long(0);
#if __CHANGES_PCIE__
		//ret = objPcieAPI.FileRecv((Pcie::DeviceTypesPci) a_enDeviceType, a_strFileName, a_nStartAddress, a_nSize, pnSizeRead);
#else
		ret	=	FileRecv((DeviceTypesPci) a_enDeviceType, a_strFileName, a_nStartAddress, a_nSize, pnSizeRead);
#endif
		*a_nSizeRead	=	(unsigned long long) *pnSizeRead;
		delete pnSizeRead;
		return ret;
	}

	return ret;

}
long MiddleAPI::MemoryReadFileInternal(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, 
	SPPUDeviceType a_enDeviceType, unsigned int a_nStartAddress, unsigned int a_nSize, unsigned int *a_nSizeRead,
	char *a_strFileName)
{
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};
	unsigned long *pnSizeWritten;
	long ret	=	-10000;

	sprintf_s(strDebug, DEBUG_STR_LEN,"\nIn MemoryReadFileInternal(%d, %d, %d, %08x, %d, %x, %s)", a_enConnectionType, a_nModuleID, a_enDeviceType, a_nStartAddress, a_nSize, a_nSizeRead, a_strFileName);
	mPrintDebug(strDebug);
	//Commented to give support for generic tcl functions and not only for DDR.
	//	DDRReadConfig( a_enConnectionType, a_nModuleID, a_enDeviceType, a_nStartAddress, a_nSize, a_nSizeRead, a_strFileName );
	unsigned long *pnSizeRead;

	switch(a_enConnectionType)
	{
	case LFT_HOST_CONNECTION_USB:
		pnSizeRead	=	new unsigned long(0);
		ret	=	objUsbApi.RdFileFromSdCard0((UsbApis::DEVICE_TYPES)a_enDeviceType, a_strFileName, a_nStartAddress, a_nSize, pnSizeRead);
		*a_nSizeRead	=	(unsigned int) *pnSizeRead;
		delete pnSizeRead;
		break;
		//return ret;

	case LFT_HOST_CONNECTION_ETH:
		pnSizeRead	=	new unsigned long(0);
		ret	=	objEthernetAPI.FileRead((MiddleEthernetAPI::EthernetAPI::SPPUDeviceTypeEtherent) a_enDeviceType, a_nStartAddress, a_nSize, a_strFileName, (unsigned int *) pnSizeRead);
		*a_nSizeRead	=	(unsigned int) *pnSizeRead;
		delete pnSizeRead;
		break;
		//return ret;

	case LFT_HOST_CONNECTION_PCIE:

		pnSizeRead	=	new unsigned long(0);
#if __CHANGES_PCIE__
		ret = objPcieAPI.FileRecv((Pcie::DeviceTypesPci) a_enDeviceType, a_strFileName, a_nStartAddress, a_nSize, pnSizeRead);
#else
		ret	=	FileRecv((DeviceTypesPci) a_enDeviceType, a_strFileName, a_nStartAddress, a_nSize, pnSizeRead);
#endif
		*a_nSizeRead	=	(unsigned int) *pnSizeRead;
		delete pnSizeRead;
		break;
		//return ret;

	case LFT_HOST_CONNECTION_SER:
		pnSizeRead = new unsigned long(0);
		ret = objSerialAPI.FileRead( a_nStartAddress, a_nSize, a_strFileName, (unsigned int *)pnSizeRead);
		*a_nSizeRead = (unsigned int)*pnSizeRead;
		delete pnSizeRead;
		break;
	}
	//Commented to give support for generic tcl functions and not only for DDR.
	//	DDRReadFinalize( a_enConnectionType, a_nModuleID, a_enDeviceType, a_nStartAddress, a_nSize, a_nSizeRead, a_strFileName );

	return ret;

}


long MiddleAPI::MemoryWriteFileInternal_10Gb(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType, unsigned long long a_nStartAddress, unsigned long long a_nSize, unsigned long long *a_nSizeWritten, char *a_strFileName)
{
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};
	unsigned long long *pnSizeWritten;
	long ret	=	-10000;

	sprintf_s(strDebug, DEBUG_STR_LEN,"\nIn MemoryWriteFileInternal file name = %s",a_strFileName);
	mPrintDebug(strDebug);

	switch(a_enConnectionType)
	{
		/*case LFT_HOST_CONNECTION_USB:
		pnSizeWritten	=	new unsigned long long(0);
		ret	=	objUsbApi.WrFileToSdCard0((UsbApis::DEVICE_TYPES)a_enDeviceType, a_strFileName, a_nStartAddress, a_nSize, pnSizeWritten);
		*a_nSizeWritten	=	(unsigned long long) *pnSizeWritten;
		delete pnSizeWritten;
		return ret;*/

	case LFT_HOST_CONNECTION_ETH:
		ret	=	objEthernetAPI.FileWrite_10GB((MiddleEthernetAPI::EthernetAPI::SPPUDeviceTypeEtherent) a_enDeviceType, a_nStartAddress, a_nSize, a_strFileName);
		*a_nSizeWritten=a_nSize;
		return ret;

		/*case LFT_HOST_CONNECTION_PCIE:
		pnSizeWritten	=	new unsigned long long(0);
		#if __CHANGES_PCIE__
		ret = objPcieAPI.FileSend((Pcie::DeviceTypesPci) a_enDeviceType, a_strFileName, a_nStartAddress, a_nSize, pnSizeWritten);
		#else
		ret =   FileSend((DeviceTypesPci) a_enDeviceType, a_strFileName, a_nStartAddress, a_nSize, pnSizeWritten);
		#endif
		*a_nSizeWritten	=	(unsigned long long) *pnSizeWritten;
		delete pnSizeWritten;
		return ret;*/
	}

	return ret;
}

long MiddleAPI::MemoryWriteFileInternal(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType, unsigned int a_nStartAddress, unsigned int a_nSize, unsigned int *a_nSizeWritten,char *a_strFileName)
{
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};
	unsigned long *pnSizeWritten;
	long ret	=	-10000;

	sprintf_s(strDebug, DEBUG_STR_LEN,"\nIn MemoryWriteFileInternal(%d, %d, %d, %08x, %d, %x, %s)", a_enConnectionType, a_nModuleID, a_enDeviceType, a_nStartAddress, a_nSize, a_nSizeWritten, a_strFileName);
	mPrintDebug(strDebug);

	//Commented to give support for generic tcl functions and not only for DDR.
	//DDRWriteConfig( a_enConnectionType, a_nModuleID, a_enDeviceType, a_nStartAddress, a_nSize, a_nSizeWritten, a_strFileName );

	switch(a_enConnectionType)
	{
	case LFT_HOST_CONNECTION_USB:
		pnSizeWritten	=	new unsigned long(0);
		ret	=	objUsbApi.WrFileToSdCard0((UsbApis::DEVICE_TYPES)a_enDeviceType, a_strFileName, a_nStartAddress, a_nSize, pnSizeWritten);
		*a_nSizeWritten	=	(unsigned int) *pnSizeWritten;
		delete pnSizeWritten;
		break;
		//return ret;

	case LFT_HOST_CONNECTION_ETH:
		ret	=	objEthernetAPI.FileWrite((MiddleEthernetAPI::EthernetAPI::SPPUDeviceTypeEtherent) a_enDeviceType, a_nStartAddress, a_nSize, a_strFileName);

		break;
		//return ret;

	case LFT_HOST_CONNECTION_PCIE:
		pnSizeWritten	=	new unsigned long(0);
#if __CHANGES_PCIE__
		ret = objPcieAPI.FileSend((Pcie::DeviceTypesPci) a_enDeviceType, a_strFileName, a_nStartAddress, a_nSize, pnSizeWritten);
#else
		ret =   FileSend((DeviceTypesPci) a_enDeviceType, a_strFileName, a_nStartAddress, a_nSize, pnSizeWritten);
#endif
		*a_nSizeWritten	=	(unsigned int) *pnSizeWritten;
		delete pnSizeWritten;
		break;
		//return ret;

	case LFT_HOST_CONNECTION_SER:
		pnSizeWritten = new unsigned long(0);
		ret = objSerialAPI.FileWrite(a_nStartAddress, a_nSize, a_strFileName, (unsigned int *)pnSizeWritten);
		*a_nSizeWritten = (unsigned int)*pnSizeWritten;
		delete pnSizeWritten;
		break;
	}

	//Commented to give support for generic tcl functions and not only for DDR.
	//DDRWriteFinalize( a_enConnectionType, a_nModuleID, a_enDeviceType, a_nStartAddress, a_nSize, a_nSizeWritten, a_strFileName );
	sprintf_s(strDebug, DEBUG_STR_LEN,"\nIn MemoryWriteFileInternal Returned : (%d)", ret);
	mPrintDebug(strDebug);
	return ret;
}

long MiddleAPI::MemoryRead(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType, unsigned int a_nStartAddress, unsigned int a_nSize, unsigned int *a_nSizeRead,char *a_pchRdBuff)
{
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};

	sprintf_s(strDebug, DEBUG_STR_LEN,"\nIn MemoryRead(%d, %d, %d, %08x, %d, %x, %x)", a_enConnectionType, a_nModuleID, a_enDeviceType, a_nStartAddress, a_nSize, a_nSizeRead, a_pchRdBuff);
	mPrintDebug(strDebug);

	long ret;
	unsigned long *pnSizeRead;

	switch(a_enConnectionType)
	{
	case LFT_HOST_CONNECTION_USB:
		pnSizeRead	=	new unsigned long(0);
		ret	=	objUsbApi.RdMemFromSdCard0((UsbApis::DEVICE_TYPES)a_enDeviceType, a_pchRdBuff, a_nStartAddress, a_nSize, pnSizeRead);
		*a_nSizeRead	=	(unsigned int) *pnSizeRead;
		delete pnSizeRead;
		return ret;
#if 0
	case LFT_HOST_CONNECTION_PCIE:
		pnSizeRead	=	new unsigned long(0);
		ret	=	BufRecv((DeviceTypesPci) a_enDeviceType, a_pchRdBuff, a_nStartAddress, a_nSize, pnSizeRead);
		*a_nSizeRead	=	(unsigned int) *pnSizeRead;
		delete pnSizeRead;
		return ret;
#endif
	}

	return -100;
}

long MiddleAPI::MemoryWrite(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType, unsigned int a_nStartAddress, unsigned int a_nSize, unsigned int *a_nSizeWritten,char *a_pchWrBuff)
{
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};

	sprintf_s(strDebug, DEBUG_STR_LEN,"\nIn MemoryWrite(%d, %d, %d, %08x, %d, %x, %x)", a_enConnectionType, a_nModuleID, a_enDeviceType, a_nStartAddress, a_nSize, a_nSizeWritten, a_pchWrBuff);
	mPrintDebug(strDebug);
	long ret	=	-10000;
	unsigned long *pnSizeWritten;

	switch(a_enConnectionType)
	{
	case LFT_HOST_CONNECTION_USB:
		pnSizeWritten	=	new unsigned long(0);
		ret	=	objUsbApi.WrMemToSdCard0((UsbApis::DEVICE_TYPES)a_enDeviceType, a_pchWrBuff, a_nStartAddress, a_nSize, pnSizeWritten);
		*a_nSizeWritten	=	(unsigned int) *pnSizeWritten;
		delete pnSizeWritten;
		return ret;

	case LFT_HOST_CONNECTION_ETH:
		ret	=	objEthernetAPI.MemWrite((MiddleEthernetAPI::EthernetAPI::SPPUDeviceTypeEtherent) a_enDeviceType, a_nStartAddress, a_nSize, a_pchWrBuff);
		return ret;
#if 0
	case LFT_HOST_CONNECTION_PCIE:
		pnSizeWritten	=	new unsigned long(0);
		ret	=	BufSend((DeviceTypesPci)a_enDeviceType, a_pchWrBuff, a_nStartAddress, a_nSize, pnSizeWritten);
		*a_nSizeWritten	=	(unsigned int) *pnSizeWritten;
		delete pnSizeWritten;
		return ret;
#endif
	}

	return -100;
}




//Changing for DDR Access. __HP__6:			//Modify for data size to be multiple of 4096 bytes.
#if 1
long MiddleAPI::ProgramIQData(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,SPPUDeviceType a_enDeviceType, SPPUDataType a_enDataType, unsigned int a_nSize, unsigned int *a_nSizeWritten, char *a_strFileName)
{
	int ret					=	0;
	unsigned int nOffset	=	0;

	unsigned int nWriteIndefinite = LFT_SPPU_IQ_WRITE_INDEFINITE;
	unsigned int nAxisBurstLength = LFT_SPPU_IQ_WRITE_AXIS_BURST_LENGTH;
	unsigned int nReadIndefininte = LFT_SPPU_IQ_READ_INDEFINITE;

	unsigned int nWriteWrapAddr	= 0x0;

	unsigned int nWriteStartAddrMsb	= 0x0;
	unsigned int nReadStartAddrMsb	= 0x0;

	unsigned int nReadWrapAddr = 0x0;
	unsigned int nWriteEndAddressCh2 = 0x0;

	{
		char strDebug[DEBUG_STR_LEN]	=	{'\0'};
		unsigned long *pnSizeWritten;

		sprintf_s(strDebug, DEBUG_STR_LEN,"\nIn ProgramIQData(%d, %d, %d, %08x, %d, %x, %s)", a_enConnectionType, a_nModuleID, a_enDeviceType, a_enDataType, a_nSize, a_nSizeWritten, a_strFileName);
		mPrintDebug(strDebug);
	}

	if(SPPUDeviceType::LFT_SPPU_DEV_DDR == a_enDeviceType)
	{
		switch(a_enDataType)
		{
		case LFT_SPPU_DATA_TYPE_IQ_DC1:
			nOffset	= LFT_SPPU_DATA_TYPE_IQ_DC1_OFFSET;
			nWriteStartAddrMsb = 0x0;
			nReadStartAddrMsb = 0x0;
			//nWriteWrapAddr = LFT_SPPU_IQ_WRITE_WRAP_ADDR_IQ_CHAN_1;
			//nReadWrapAddr = LFT_SPPU_IQ_READ_WRAP_ADDR_IQ_CHAN_1(a_nSize);
			break;

		case LFT_SPPU_DATA_TYPE_IQ_DC2:
			nOffset	= LFT_SPPU_DATA_TYPE_IQ_DC2_OFFSET;
			nWriteStartAddrMsb = 0x0;						//__HARD__
			nReadStartAddrMsb = 0x0;
			//nWriteWrapAddr = LFT_SPPU_IQ_WRITE_WRAP_ADDR_IQ_CHAN_2;
			//nReadWrapAddr = LFT_SPPU_IQ_READ_WRAP_ADDR_IQ_CHAN_2(a_nSize);
			break;

		case LFT_SPPU_DATA_TYPE_RF:
			nOffset	= LFT_SPPU_DATA_TYPE_IF_OFFSET;
			nWriteStartAddrMsb = 0x0;
			nReadStartAddrMsb = 0x0;
			//nWriteWrapAddr = LFT_SPPU_IQ_WRITE_WRAP_ADDR_IF_CHAN;
			//nReadWrapAddr = LFT_SPPU_IQ_READ_WRAP_ADDR_IF_CHAN(a_nSize);
			break;

		default:
			ret	=	-100;
		}

		//int SizeModify = 0, SizeDiff = 0;
		unsigned int SizeModify = 0, SizeDiff = 0;

		//		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_AXIS_BURST_LENGTH, nAxisBurstLength);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_START_ADDRESS, nOffset);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_START_ADDRESS_MSB, nWriteStartAddrMsb/*nWriteWrapAddr*/);

		//__HP__4 ; Adding support : if File Size is not multiple of 4096 bytes then append 0s to make it multiple of 64 bytes.
		SizeModify = a_nSize;
		if(SizeModify < FPGA_DDR_RESOLUTION)
			SizeModify = FPGA_DDR_RESOLUTION;

		if((SizeDiff = (SizeModify % FPGA_DDR_RESOLUTION)) != 0)
			SizeModify += (FPGA_DDR_RESOLUTION - SizeDiff);
		//__HP__4 : end;

		//__HP__8; initializing with valid value
		nWriteEndAddressCh2 = SizeModify;

		//__HP__7:
		if(a_enDataType == LFT_SPPU_DATA_TYPE_IQ_DC2)
			nWriteEndAddressCh2 = SizeModify + 0x3FF8000;

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_SIZE, nWriteEndAddressCh2/*SizeModify*//*a_nSize*/);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_SIZE_MSB, 0x0);		//__HARD__

		//FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_INDEFINITE, nWriteIndefinite);

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_DATA_PULSE, 1);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_DATA_PULSE, 0);

		//__HP__2; Adding support : if File Size is not multiple of 64 bytes then append 0s to make it multiple of 64 bytes.
#if 0
		int SizeModify = 0;

		if(a_nSize < 64)
			a_nSize = 64;

		if((SizeModify = (a_nSize % 64)) != 0)
			a_nSize += (64 - SizeModify);
#endif
		//__HP__5; sending modified file size.
		ret	=	MemoryWriteFileInternal(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FIXED_ADDRESS_FOR_IQ_PROGRAMMING, SizeModify/*a_nSize*/, a_nSizeWritten, a_strFileName);

		int timeout = 10;
		unsigned int val	=	5;
		while(timeout)
		{
			FPGARegAccessRead(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_COMPLETE, &val);
			if(val	==	1)
				break;
			Sleep(100);
			timeout--;
		}

		if(LFT_SPPU_DATA_TYPE_IQ_DC2 == a_enDataType)
		{

			a_nSize += 0x3FF8000;
			//FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_AXIS_BURST_LENGTH_CH2, nAxisBurstLength);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_START_ADDRESS_CH2, nOffset);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_START_ADDRESS_MSB_CH2, nReadStartAddrMsb);
			//FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_WRAPPER_ADDRESS_CH2, nReadWrapAddr);
			//FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_SIZE_CH2, SizeModify/*a_nSize*/);
			//__HP__6:
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_SIZE_CH2, a_nSize);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_SIZE_MSB_CH2, 0x0);

			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_INDEFINITE_CH2, nReadIndefininte);
		}
		else
		{
			//FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_AXIS_BURST_LENGTH, nAxisBurstLength);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_START_ADDRESS, nOffset);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_START_ADDRESS_MSB, nReadStartAddrMsb);
			//FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_WRAPPER_ADDRESS, nReadWrapAddr);
			//FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_SIZE, SizeModify/*a_nSize*/);
			//__HP__6: sending actual file size as data size; 27 oct 2015
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_SIZE, a_nSize);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_SIZE_MSB, 0x0);		//__HARD__

			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_INDEFINITE, nReadIndefininte);
		}
	}
	else if(SPPUDeviceType::LFT_SPPU_DEV_FX3_SDCARD == a_enDeviceType)
	{
		switch(a_enDataType)
		{
		case LFT_SPPU_DATA_TYPE_IQ_DC1:
			prevInfo.rfCh_1_Size = a_nSize;
			nOffset	= LFT_SPPU_SD_CARD_RF_CH_1_OFFSET;
			ret = MemoryWriteFileInternal(a_enConnectionType, a_nModuleID, a_enDeviceType, nOffset, a_nSize, a_nSizeWritten, a_strFileName);
			if(ret == S_OK) 
			{
				//__HP__10 : Saving Exact Data value in Regs.
				//prevInfo.rfCh_1_Size = *a_nSizeWritten;
				prevInfo.rfCh_1_Size = a_nSize;
			}
			else ret = -100;
			break;

		case LFT_SPPU_DATA_TYPE_IQ_DC2:
			prevInfo.rfCh_2_Size = a_nSize;
			nOffset	= LFT_SPPU_SD_CARD_RF_CH_2_OFFSET;
			ret = MemoryWriteFileInternal(a_enConnectionType, a_nModuleID, a_enDeviceType, nOffset, a_nSize, a_nSizeWritten, a_strFileName);
			if(ret == S_OK) 

			{
				//__HP__10:
				//prevInfo.rfCh_2_Size = *a_nSizeWritten;
				prevInfo.rfCh_2_Size = a_nSize;
			}
			else ret = -100;
			//Always call this function in last so that we get updated values in Structure SavePrevInfo.
			SaveDevRegs(a_enConnectionType, a_nModuleID, a_enDeviceType);
			//				SaveMetaData(a_enConnectionType, a_nModuleID, a_enDeviceType);
			break;

		case LFT_SPPU_DATA_TYPE_RF:
			prevInfo.if_Size = a_nSize;
			nOffset	= LFT_SPPU_SD_CARD_IF_OFFSET;
			ret = MemoryWriteFileInternal(a_enConnectionType, a_nModuleID, a_enDeviceType, nOffset, a_nSize, a_nSizeWritten, a_strFileName);
			if(ret == S_OK)
			{
				//__HP__10:
				//prevInfo.if_Size = *a_nSizeWritten;
				prevInfo.if_Size = a_nSize;
			}
			else ret = -100;
			//Always call this function in last so that we get updated values in Structure SavePrevInfo.
			SaveDevRegs(a_enConnectionType, a_nModuleID, a_enDeviceType);
			//SaveMetaData(a_enConnectionType, a_nModuleID, a_enDeviceType);
			break;

		case LFT_SPPU_SAVE_FPGA_REGS_SD_CARD:
			SaveDevRegs(a_enConnectionType, a_nModuleID, a_enDeviceType);
			//Always call this function in last so that we get updated values in Structure SavePrevInfo.
			//SaveMetaData(a_enConnectionType, a_nModuleID, a_enDeviceType);
			break;
		default:
			ret = -100;
		}
	}
	else
	{
		//Un recognized device
		ret = -100;
	}
	return ret;
}
#elif 0

long MiddleAPI::ProgramIQData(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,SPPUDeviceType a_enDeviceType, SPPUDataType a_enDataType, unsigned int a_nSize, unsigned int *a_nSizeWritten, char *a_strFileName)
{
	int ret					=	0;
	unsigned int nOffset	=	0;

	unsigned int nWriteIndefinite = LFT_SPPU_IQ_WRITE_INDEFINITE;
	unsigned int nAxisBurstLength = LFT_SPPU_IQ_WRITE_AXIS_BURST_LENGTH;
	unsigned int nReadIndefininte = LFT_SPPU_IQ_READ_INDEFINITE;

	unsigned int nWriteWrapAddr	= 0x0;

	unsigned int nWriteStartAddrMsb	= 0x0;
	unsigned int nReadStartAddrMsb	= 0x0;

	unsigned int nReadWrapAddr = 0x0;


	if(SPPUDeviceType::LFT_SPPU_DEV_DDR == a_enDeviceType)
	{
		switch(a_enDataType)
		{
		case LFT_SPPU_DATA_TYPE_IQ_DC1:
			nOffset	= LFT_SPPU_DATA_TYPE_IQ_DC1_OFFSET;
			nWriteStartAddrMsb = 0x0;
			nReadStartAddrMsb = 0x0;
			//nWriteWrapAddr = LFT_SPPU_IQ_WRITE_WRAP_ADDR_IQ_CHAN_1;
			//nReadWrapAddr = LFT_SPPU_IQ_READ_WRAP_ADDR_IQ_CHAN_1(a_nSize);
			break;

		case LFT_SPPU_DATA_TYPE_IQ_DC2:
			nOffset	= LFT_SPPU_DATA_TYPE_IQ_DC2_OFFSET;
			nWriteStartAddrMsb = 0x0;						//__HARD__
			nReadStartAddrMsb = 0x0;
			//nWriteWrapAddr = LFT_SPPU_IQ_WRITE_WRAP_ADDR_IQ_CHAN_2;
			//nReadWrapAddr = LFT_SPPU_IQ_READ_WRAP_ADDR_IQ_CHAN_2(a_nSize);
			break;

		case LFT_SPPU_DATA_TYPE_RF:
			nOffset	= LFT_SPPU_DATA_TYPE_IF_OFFSET;
			nWriteStartAddrMsb = 0x0;
			nReadStartAddrMsb = 0x0;
			//nWriteWrapAddr = LFT_SPPU_IQ_WRITE_WRAP_ADDR_IF_CHAN;
			//nReadWrapAddr = LFT_SPPU_IQ_READ_WRAP_ADDR_IF_CHAN(a_nSize);
			break;

		default:
			ret	=	-100;
		}

		int SizeModify = 0, SizeDiff = 0;

		//		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_AXIS_BURST_LENGTH, nAxisBurstLength);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_START_ADDRESS, nOffset);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_START_ADDRESS_MSB, nWriteStartAddrMsb/*nWriteWrapAddr*/);

		//__HP__4 ; Adding support : if File Size is not multiple of 64 bytes then append 0s to make it multiple of 64 bytes.

		SizeModify = a_nSize;
		if(SizeModify < 64)
			SizeModify = 64;

		if((SizeDiff = (SizeModify % 64)) != 0)
			SizeModify += (64 - SizeDiff);
		//__HP__4 : end;


		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_SIZE, SizeModify/*a_nSize*/);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_SIZE_MSB, 0x0);		//__HARD__

		//FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_INDEFINITE, nWriteIndefinite);

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_DATA_PULSE, 1);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_DATA_PULSE, 0);

		//__HP__2; Adding support : if File Size is not multiple of 64 bytes then append 0s to make it multiple of 64 bytes.
#if 0
		int SizeModify = 0;

		if(a_nSize < 64)
			a_nSize = 64;

		if((SizeModify = (a_nSize % 64)) != 0)
			a_nSize += (64 - SizeModify);
#endif
		//__HP__5; sending modified file size.
		ret	=	MemoryWriteFileInternal(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FIXED_ADDRESS_FOR_IQ_PROGRAMMING, SizeModify/*a_nSize*/, a_nSizeWritten, a_strFileName);

		int timeout = 10;
		unsigned int val	=	5;
		while(timeout)
		{
			FPGARegAccessRead(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_COMPLETE, &val);
			if(val	==	1)
				break;
			Sleep(100);
			timeout--;
		}	

		if(LFT_SPPU_DATA_TYPE_IQ_DC2 == a_enDataType)
		{
			//FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_AXIS_BURST_LENGTH_CH2, nAxisBurstLength);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_START_ADDRESS_CH2, nOffset);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_START_ADDRESS_MSB_CH2, nReadStartAddrMsb);
			//FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_WRAPPER_ADDRESS_CH2, nReadWrapAddr);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_SIZE_CH2, SizeModify/*a_nSize*/);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_SIZE_MSB_CH2, 0x0);

			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_INDEFINITE_CH2, nReadIndefininte);
		}
		else
		{
			//FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_AXIS_BURST_LENGTH, nAxisBurstLength);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_START_ADDRESS, nOffset);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_START_ADDRESS_MSB, nReadStartAddrMsb);
			//FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_WRAPPER_ADDRESS, nReadWrapAddr);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_SIZE, SizeModify/*a_nSize*/);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_SIZE_MSB, 0x0);		//__HARD__

			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_INDEFINITE, nReadIndefininte);
		}
	}
	else if(SPPUDeviceType::LFT_SPPU_DEV_FX3_SDCARD == a_enDeviceType)
	{
		switch(a_enDataType)
		{
		case LFT_SPPU_DATA_TYPE_IQ_DC1:
			prevInfo.rfCh_1_Size = a_nSize;
			nOffset	= LFT_SPPU_SD_CARD_RF_CH_1_OFFSET;
			ret = MemoryWriteFileInternal(a_enConnectionType, a_nModuleID, a_enDeviceType, nOffset, a_nSize, a_nSizeWritten, a_strFileName);
			if(ret == S_OK) 
			{
				prevInfo.rfCh_1_Size = *a_nSizeWritten;
			}
			else ret = -100;
			break;

		case LFT_SPPU_DATA_TYPE_IQ_DC2:
			prevInfo.rfCh_2_Size = a_nSize;
			nOffset	= LFT_SPPU_SD_CARD_RF_CH_2_OFFSET;
			ret = MemoryWriteFileInternal(a_enConnectionType, a_nModuleID, a_enDeviceType, nOffset, a_nSize, a_nSizeWritten, a_strFileName);
			if(ret == S_OK) 
			{
				prevInfo.rfCh_2_Size = *a_nSizeWritten;
			}
			else ret = -100;
			//Always call this function in last so that we get updated values in Structure SavePrevInfo.
			SaveDevRegs(a_enConnectionType, a_nModuleID, a_enDeviceType);
			//				SaveMetaData(a_enConnectionType, a_nModuleID, a_enDeviceType);
			break;

		case LFT_SPPU_DATA_TYPE_RF:
			prevInfo.if_Size = a_nSize;
			nOffset	= LFT_SPPU_SD_CARD_IF_OFFSET;
			ret = MemoryWriteFileInternal(a_enConnectionType, a_nModuleID, a_enDeviceType, nOffset, a_nSize, a_nSizeWritten, a_strFileName);
			if(ret == S_OK)
			{
				prevInfo.if_Size = *a_nSizeWritten;
			}
			else ret = -100;
			//Always call this function in last so that we get updated values in Structure SavePrevInfo.
			SaveDevRegs(a_enConnectionType, a_nModuleID, a_enDeviceType);
			//SaveMetaData(a_enConnectionType, a_nModuleID, a_enDeviceType);
			break;

		case LFT_SPPU_SAVE_FPGA_REGS_SD_CARD:
			SaveDevRegs(a_enConnectionType, a_nModuleID, a_enDeviceType);
			//Always call this function in last so that we get updated values in Structure SavePrevInfo.
			//SaveMetaData(a_enConnectionType, a_nModuleID, a_enDeviceType);
			break;
		default:
			ret = -100;
		}
	}
	else
	{
		//Un recognized device
		ret = -100;
	}
	return ret;
}
#else
long MiddleAPI::ProgramIQData(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,SPPUDeviceType a_enDeviceType, SPPUDataType a_enDataType, unsigned int a_nSize, unsigned int *a_nSizeWritten, char *a_strFileName)
{
	int ret					=	0;
	unsigned int nOffset	=	0;

	unsigned int nWriteIndefinite = LFT_SPPU_IQ_WRITE_INDEFINITE;
	unsigned int nAxisBurstLength = LFT_SPPU_IQ_WRITE_AXIS_BURST_LENGTH;
	unsigned int nReadIndefininte = LFT_SPPU_IQ_READ_INDEFINITE;

	unsigned int nWriteWrapAddr	= 0x0;
	unsigned int nReadWrapAddr = 0x0;


	if(SPPUDeviceType::LFT_SPPU_DEV_DDR == a_enDeviceType)
	{
		switch(a_enDataType)
		{
		case LFT_SPPU_DATA_TYPE_IQ_DC1:
			nOffset	= LFT_SPPU_DATA_TYPE_IQ_DC1_OFFSET;
			nWriteWrapAddr = LFT_SPPU_IQ_WRITE_WRAP_ADDR_IQ_CHAN_1;
			nReadWrapAddr = LFT_SPPU_IQ_READ_WRAP_ADDR_IQ_CHAN_1(a_nSize);
			break;

		case LFT_SPPU_DATA_TYPE_IQ_DC2:
			nOffset	= LFT_SPPU_DATA_TYPE_IQ_DC2_OFFSET;
			nWriteWrapAddr = LFT_SPPU_IQ_WRITE_WRAP_ADDR_IQ_CHAN_2;
			nReadWrapAddr = LFT_SPPU_IQ_READ_WRAP_ADDR_IQ_CHAN_2(a_nSize);
			break;

		case LFT_SPPU_DATA_TYPE_RF:
			nOffset	= LFT_SPPU_DATA_TYPE_IF_OFFSET;
			nWriteWrapAddr = LFT_SPPU_IQ_WRITE_WRAP_ADDR_IF_CHAN;
			nReadWrapAddr = LFT_SPPU_IQ_READ_WRAP_ADDR_IF_CHAN(a_nSize);
			break;

		default:
			ret	=	-100;
		}

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_AXIS_BURST_LENGTH, nAxisBurstLength);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_START_ADDRESS, nOffset);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_WRAP_ADDRESS, nWriteWrapAddr);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_SIZE, a_nSize);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_INDEFINITE, nWriteIndefinite);

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_DATA_PULSE, 1);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_DATA_PULSE, 0);

		//__HP__2; Adding support : if File Size is not multiple of 64 bytes then append 0s to make it multiple of 64 bytes.
#if 0
		int SizeModify = 0;

		if(a_nSize < 64)
			a_nSize = 64;

		if((SizeModify = (a_nSize % 64)) != 0)
			a_nSize += (64 - SizeModify);
#endif
		ret	=	MemoryWriteFileInternal(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FIXED_ADDRESS_FOR_IQ_PROGRAMMING, a_nSize, a_nSizeWritten, a_strFileName);

		int timeout = 10;
		unsigned int val	=	5;
		while(timeout)
		{
			FPGARegAccessRead(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_COMPLETE, &val);
			if(val	==	1)
				break;
			Sleep(100);
			timeout--;
		}	

		if(LFT_SPPU_DATA_TYPE_IQ_DC2 == a_enDataType)
		{
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_AXIS_BURST_LENGTH_CH2, nAxisBurstLength);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_START_ADDRESS_CH2, nOffset);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_WRAPPER_ADDRESS_CH2, nReadWrapAddr);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_SIZE_CH2, a_nSize);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_INDEFINITE_CH2, nReadIndefininte);
		}
		else
		{
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_AXIS_BURST_LENGTH, nAxisBurstLength);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_START_ADDRESS, nOffset);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_WRAPPER_ADDRESS, nReadWrapAddr);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_SIZE, a_nSize);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_INDEFINITE, nReadIndefininte);
		}
	}
	else if(SPPUDeviceType::LFT_SPPU_DEV_FX3_SDCARD == a_enDeviceType)
	{
		switch(a_enDataType)
		{
		case LFT_SPPU_DATA_TYPE_IQ_DC1:
			prevInfo.rfCh_1_Size = a_nSize;
			nOffset	= LFT_SPPU_SD_CARD_RF_CH_1_OFFSET;
			ret = MemoryWriteFileInternal(a_enConnectionType, a_nModuleID, a_enDeviceType, nOffset, a_nSize, a_nSizeWritten, a_strFileName);
			if(ret == S_OK) 
			{
				prevInfo.rfCh_1_Size = *a_nSizeWritten;
			}
			else ret = -100;
			break;

		case LFT_SPPU_DATA_TYPE_IQ_DC2:
			prevInfo.rfCh_2_Size = a_nSize;
			nOffset	= LFT_SPPU_SD_CARD_RF_CH_2_OFFSET;
			ret = MemoryWriteFileInternal(a_enConnectionType, a_nModuleID, a_enDeviceType, nOffset, a_nSize, a_nSizeWritten, a_strFileName);
			if(ret == S_OK) 
			{
				prevInfo.rfCh_2_Size = *a_nSizeWritten;
			}
			else ret = -100;
			//Always call this function in last so that we get updated values in Structure SavePrevInfo.
			SaveDevRegs(a_enConnectionType, a_nModuleID, a_enDeviceType);
			//				SaveMetaData(a_enConnectionType, a_nModuleID, a_enDeviceType);
			break;

		case LFT_SPPU_DATA_TYPE_RF:
			prevInfo.if_Size = a_nSize;
			nOffset	= LFT_SPPU_SD_CARD_IF_OFFSET;
			ret = MemoryWriteFileInternal(a_enConnectionType, a_nModuleID, a_enDeviceType, nOffset, a_nSize, a_nSizeWritten, a_strFileName);
			if(ret == S_OK)
			{
				prevInfo.if_Size = *a_nSizeWritten;
			}
			else ret = -100;
			//Always call this function in last so that we get updated values in Structure SavePrevInfo.
			SaveDevRegs(a_enConnectionType, a_nModuleID, a_enDeviceType);
			//SaveMetaData(a_enConnectionType, a_nModuleID, a_enDeviceType);
			break;

		case LFT_SPPU_SAVE_FPGA_REGS_SD_CARD:
			SaveDevRegs(a_enConnectionType, a_nModuleID, a_enDeviceType);
			//Always call this function in last so that we get updated values in Structure SavePrevInfo.
			//SaveMetaData(a_enConnectionType, a_nModuleID, a_enDeviceType);
			break;
		default:
			ret = -100;
		}
	}
	else
	{
		//Un recognized device
		ret = -100;
	}
	return ret;
}
#endif


#pragma region saveRegsSdCard
// This API stores various devices registers in SD Card
HRESULT MiddleAPI::SaveDevRegs(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType)
{
	SaveLmk04806Regs(a_enConnectionType, a_nModuleID, a_enDeviceType);
	SaveDacRegs(a_enConnectionType, a_nModuleID, a_enDeviceType);
	SaveFpgaRegs(a_enConnectionType, a_nModuleID, a_enDeviceType);

	//Always call this function in last so that we get updated values in Structure SavePrevInfo.
	SaveMetaData(a_enConnectionType, a_nModuleID, a_enDeviceType);

	return S_OK;
}

HRESULT MiddleAPI::FillBuf(char *dest, unsigned int src)
{
	*(dest + 0x0) = ((src & 0xFF000000) >> 24);
	*(dest + 0x1) = ((src & 0x00FF0000) >> 16);
	*(dest + 0x2) = ((src & 0x0000FF00) >> 8);
	*(dest + 0x3) = ((src & 0x000000FF) >> 0);
	return S_OK;
}

HRESULT MiddleAPI::SaveMetaData(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType)
{
	char SaveMetaDataBuf[513] = {'\0'};

	unsigned int val, lv, j = 0;
	DWORD pnSizeWritten = 0;
	unsigned int validHeaderBytes = 0x0;
	unsigned int MetaDataStartAddr = LFT_SPPU_DEV_REG_SAVE_HEADER;

	//Magic Byte 1
	FillBuf((SaveMetaDataBuf + MetaDataInfo::LFT_SPPU_SD_CARD_HEADER_MAGIC_1), 0xAA11BB22);
	validHeaderBytes += 0x4;

	//Magic Byte 2
	FillBuf((SaveMetaDataBuf + MetaDataInfo::LFT_SPPU_SD_CARD_HEADER_MAGIC_2), 0x88EE99FF);
	validHeaderBytes += 0x4;

	// Current Operation Mode
	FPGARegAccessRead(a_enConnectionType, a_nModuleID, SPPUDeviceType::LFT_SPPU_DEV_FPGA,
		LFT_SPPU_FPGA_operation_Mode_RF_IF, &val);
	FillBuf((SaveMetaDataBuf + MetaDataInfo::LFT_SPPU_SD_CARD_HEADER_OP_MODE), val);
	validHeaderBytes += 0x4;

	// RF Data Channel 1, offset
	val = LFT_SPPU_SD_CARD_RF_CH_1_OFFSET;
	FillBuf((SaveMetaDataBuf + MetaDataInfo::LFT_SPPU_SD_CARD_HEADER_RF_CH1_OFFSET), val);
	validHeaderBytes += 0x4;

	// RF Data Channel 1, size
	FillBuf((SaveMetaDataBuf + MetaDataInfo::LFT_SPPU_SD_CARD_HEADER_RF_CH1_SIZE), prevInfo.rfCh_1_Size);
	validHeaderBytes += 0x4;

	// RF Data Channel 2, offset
	val = LFT_SPPU_SD_CARD_RF_CH_2_OFFSET;
	FillBuf((SaveMetaDataBuf + MetaDataInfo::LFT_SPPU_SD_CARD_HEADER_RF_CH2_OFFSET), val);
	validHeaderBytes += 0x4;

	// RF Data Channel 2, size
	FillBuf((SaveMetaDataBuf + MetaDataInfo::LFT_SPPU_SD_CARD_HEADER_RF_CH2_SIZE), prevInfo.rfCh_2_Size);
	validHeaderBytes += 0x4;

	// IF, offset
	val = LFT_SPPU_SD_CARD_IF_OFFSET;
	FillBuf((SaveMetaDataBuf + MetaDataInfo::LFT_SPPU_SD_CARD_HEADER_IF_OFFSET), val);
	validHeaderBytes += 0x4;

	// IF, size
	FillBuf((SaveMetaDataBuf + MetaDataInfo::LFT_SPPU_SD_CARD_HEADER_IF_SIZE), prevInfo.if_Size);
	validHeaderBytes += 0x4;


	// DAC 1, offset
	val = LFT_SPPU_DAC_1_REG_SAVE_OFFSET;
	FillBuf((SaveMetaDataBuf + MetaDataInfo::LFT_SPPU_SD_CARD_HEADER_DAC_1_OFFSET), val);
	validHeaderBytes += 0x4;

	// DAC 1, size
	FillBuf((SaveMetaDataBuf + MetaDataInfo::LFT_SPPU_SD_CARD_HEADER_DAC_1_SIZE), prevInfo.dac_1_Size);
	validHeaderBytes += 0x4;


	// DAC 2, offset
	val = LFT_SPPU_DAC_2_REG_SAVE_OFFSET;
	FillBuf((SaveMetaDataBuf + MetaDataInfo::LFT_SPPU_SD_CARD_HEADER_DAC_2_OFFSET), val);
	validHeaderBytes += 0x4;

	// DAC 2, size
	FillBuf((SaveMetaDataBuf + MetaDataInfo::LFT_SPPU_SD_CARD_HEADER_DAC_2_SIZE), prevInfo.dac_2_Size);
	validHeaderBytes += 0x4;


	// DAC 3, offset
	val = LFT_SPPU_DAC_3_REG_SAVE_OFFSET;
	FillBuf((SaveMetaDataBuf + MetaDataInfo::LFT_SPPU_SD_CARD_HEADER_DAC_3_OFFSET), val);
	validHeaderBytes += 0x4;

	// DAC 3, size
	FillBuf((SaveMetaDataBuf + MetaDataInfo::LFT_SPPU_SD_CARD_HEADER_DAC_3_SIZE), prevInfo.dac_3_Size);
	validHeaderBytes += 0x4;


	// LMK, offset
	val = LFT_SPPU_LMK_REG_SAVE_OFFSET;
	FillBuf((SaveMetaDataBuf + MetaDataInfo::LFT_SPPU_SD_CARD_HEADER_LMK_OFFSET), val);
	validHeaderBytes += 0x4;

	// LMK, size
	FillBuf((SaveMetaDataBuf + MetaDataInfo::LFT_SPPU_SD_CARD_HEADER_LMK_SIZE), prevInfo.lmk_Size);
	validHeaderBytes += 0x4;


	// FPGA, offset
	val = LFT_SPPU_FPGA_REG_SAVE_OFFSET;
	FillBuf((SaveMetaDataBuf + MetaDataInfo::LFT_SPPU_SD_CARD_HEADER_FPGA_OFFSET), val);
	validHeaderBytes += 0x4;

	// FPGA , size
	FillBuf((SaveMetaDataBuf + MetaDataInfo::LFT_SPPU_SD_CARD_HEADER_FPGA_SIZE), prevInfo.fpga_Size);
	validHeaderBytes += 0x4;


	// Valid Header Length
	validHeaderBytes += 0x4;
	FillBuf((SaveMetaDataBuf + MetaDataInfo::LFT_SPPU_SD_CARD_HEADER_LENGTH), validHeaderBytes);


	// TODO: remove this 512 hard coded value
	objUsbApi.WrMemToSdCard0((UsbApis::DEVICE_TYPES)a_enDeviceType, SaveMetaDataBuf, MetaDataStartAddr,
		512, &pnSizeWritten);

	return S_OK;
}


// This API stores various DAC registers in SD Card
HRESULT MiddleAPI::SaveDacRegs(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType)
{
	unsigned int val, i, lv, j = 0;
	DWORD pnSizeWritten = 0;
	unsigned char numDacs = LFT_SPPU_NUM_DACS;
	SPPUDeviceType currentDac = SPPUDeviceType::LFT_SPPU_DEV_DAC1;
	unsigned int dacRegSaveOffset = LFT_SPPU_DAC_1_REG_SAVE_OFFSET;
	char SaveRegsBuf[513] = {'\0'};

	//Save the DAC # reg count for later use in Firmware.
	prevInfo.dac_1_Size = LFT_SPPU_TOTAL_DAC_REGS;
	prevInfo.dac_2_Size = LFT_SPPU_TOTAL_DAC_REGS;
	prevInfo.dac_3_Size = LFT_SPPU_TOTAL_DAC_REGS;

	val = 0;
	for(i = 0; i < numDacs; i++)
	{
		j = 0;
		switch(i)
		{
		case 0:
			dacRegSaveOffset = LFT_SPPU_DAC_1_REG_SAVE_OFFSET;
			currentDac = SPPUDeviceType::LFT_SPPU_DEV_DAC1;
			break;
		case 1:
			dacRegSaveOffset = LFT_SPPU_DAC_2_REG_SAVE_OFFSET;
			currentDac = SPPUDeviceType::LFT_SPPU_DEV_DAC2;
			break;
		case 2:
			dacRegSaveOffset = LFT_SPPU_DAC_3_REG_SAVE_OFFSET;
			currentDac = SPPUDeviceType::LFT_SPPU_DEV_DAC3;
			break;
		default:
			break;
		}

		for(lv = 0; lv < LFT_SPPU_TOTAL_DAC_REGS; lv++)
		{
			RegRead(a_enConnectionType, a_nModuleID, currentDac, (DAC_BASE_ADDRESS + lv), &val);
			*(SaveRegsBuf + j + 0) = (((DAC_BASE_ADDRESS + lv) & 0xFF000000) >> 24);
			*(SaveRegsBuf + j + 1) = (((DAC_BASE_ADDRESS + lv) & 0x00FF0000) >> 16);
			*(SaveRegsBuf + j + 2) = (((DAC_BASE_ADDRESS + lv) & 0x0000FF00) >> 8);
			*(SaveRegsBuf + j + 3) = (((DAC_BASE_ADDRESS + lv) & 0x000000FF) >> 0);

			*(SaveRegsBuf + j + 4) = ((val & 0xFF000000) >> 24);
			*(SaveRegsBuf + j + 5) = ((val & 0x00FF0000) >> 16);
			*(SaveRegsBuf + j + 6) = ((val & 0x0000FF00) >> 8);
			*(SaveRegsBuf + j + 7) = ((val & 0x000000FF) >> 0);
			j += 8;
		}

		//There is one extra register in each DAC
		RegRead(a_enConnectionType, a_nModuleID, currentDac, 0x7F, &val);
		*(SaveRegsBuf + j + 0) = ((0x7F & 0xFF000000) >> 24);
		*(SaveRegsBuf + j + 1) = ((0x7F & 0x00FF0000) >> 16);
		*(SaveRegsBuf + j + 2) = ((0x7F & 0x0000FF00) >> 8);
		*(SaveRegsBuf + j + 3) = ((0x7F & 0x000000FF) >> 0);

		*(SaveRegsBuf + j + 4) = ((val & 0xFF000000) >> 24);
		*(SaveRegsBuf + j + 5) = ((val & 0x00FF0000) >> 16);
		*(SaveRegsBuf + j + 6) = ((val & 0x0000FF00) >> 8);
		*(SaveRegsBuf + j + 7) = ((val & 0x000000FF) >> 0);

		//TODO: remove this 512 hard coded value
		objUsbApi.WrMemToSdCard0((UsbApis::DEVICE_TYPES)a_enDeviceType, SaveRegsBuf, dacRegSaveOffset,
			512, &pnSizeWritten);
	}
	return S_OK;
}


// This API stores various LMK registers in SD Card
HRESULT MiddleAPI::SaveLmk04806Regs(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType)
{
	unsigned int val, lv, j = 0;
	DWORD pnSizeWritten = 0;
	unsigned char numLmks = 0x1;
	unsigned int LmkRegStartAddr = 0x00;
	unsigned int LmkRegEndAddr = 0x1E;
	unsigned int numLmkRegs = LmkRegEndAddr - LmkRegStartAddr + 1;

	SPPUDeviceType currentLmk = SPPUDeviceType::LFT_SPPU_DEV_LMK04806;
	unsigned int lmkRegSaveOffset = LFT_SPPU_LMK_REG_SAVE_OFFSET;
	char SaveRegsBuf[513] = {'\0'};

	prevInfo.lmk_Size = numLmkRegs;		//save this register count for later use in header update.
	val = 0;

	for(lv = 0; lv < numLmkRegs; lv++)
	{
		if((lv >= 0x11) && (lv <= 0x17))
			continue;
		RegRead(a_enConnectionType, a_nModuleID, currentLmk, (LMK_BASE_ADDRESS + lv), &val);
		*(SaveRegsBuf + j + 0) = (((LMK_BASE_ADDRESS + lv) & 0xFF000000) >> 24);
		*(SaveRegsBuf + j + 1) = (((LMK_BASE_ADDRESS + lv) & 0x00FF0000) >> 16);
		*(SaveRegsBuf + j + 2) = (((LMK_BASE_ADDRESS + lv) & 0x0000FF00) >> 8);
		*(SaveRegsBuf + j + 3) = (((LMK_BASE_ADDRESS + lv) & 0x000000FF) >> 0);

		*(SaveRegsBuf + j + 4) = ((val & 0xFF000000) >> 24);
		*(SaveRegsBuf + j + 5) = ((val & 0x00FF0000) >> 16);
		*(SaveRegsBuf + j + 6) = ((val & 0x0000FF00) >> 8);
		*(SaveRegsBuf + j + 7) = ((val & 0x000000FF) >> 0);
		j += 8;
	}

	//TODO: remove this 512 hard coded value
	objUsbApi.WrMemToSdCard0((UsbApis::DEVICE_TYPES)a_enDeviceType, SaveRegsBuf, lmkRegSaveOffset,
		512, &pnSizeWritten);

	return S_OK;
}


// This API stores various FPGA registers in SD Card
HRESULT MiddleAPI::SaveFpgaRegs(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType)
{
	unsigned int val, j = 0;
	DWORD pnSizeWritten = 0;
	unsigned char numFpgas = 0x1;
	unsigned int addr = 0x0;
	unsigned int numFpgaRegs = 0x7;
	SPPUDeviceType currentFpga = SPPUDeviceType::LFT_SPPU_DEV_FPGA;
	unsigned int fpgaRegSaveOffset = LFT_SPPU_FPGA_REG_SAVE_OFFSET;
	char SaveRegsBuf[513] = {'\0'};
	unsigned int infoBase = 0x0;
	val = 0;

	// reg 0x2200 - OP_MODE
	addr = 0x2200;
	RegRead(a_enConnectionType, a_nModuleID, currentFpga, (FPGA_BASE_ADDRESS + addr), &val);
	FillBuf(SaveRegsBuf + infoBase, addr);
	infoBase += 0x4;
	FillBuf(SaveRegsBuf + infoBase, val);
	infoBase += 0x4;

	// reg 0x2008 - Pulse Width
	addr = 0x2008;
	RegRead(a_enConnectionType, a_nModuleID, currentFpga, (FPGA_BASE_ADDRESS + addr), &val);
	FillBuf(SaveRegsBuf + infoBase, addr);
	infoBase += 0x4;
	FillBuf(SaveRegsBuf + infoBase, val);
	infoBase += 0x4;

	// reg 0x2014
	addr = 0x2014;
	RegRead(a_enConnectionType, a_nModuleID, currentFpga, (FPGA_BASE_ADDRESS + addr), &val);
	FillBuf(SaveRegsBuf + infoBase, addr);
	infoBase += 0x4;
	FillBuf(SaveRegsBuf + infoBase, val);
	infoBase += 0x4;

	// reg 0x2004
	addr = 0x2004;
	RegRead(a_enConnectionType, a_nModuleID, currentFpga, (FPGA_BASE_ADDRESS + addr), &val);
	FillBuf(SaveRegsBuf + infoBase, addr);
	infoBase += 0x4;
	FillBuf(SaveRegsBuf + infoBase, val);
	infoBase += 0x4;

	// reg 0x2000
	addr = 0x2000;
	RegRead(a_enConnectionType, a_nModuleID, currentFpga, (FPGA_BASE_ADDRESS + addr), &val);
	FillBuf(SaveRegsBuf + infoBase, addr);
	infoBase += 0x4;
	FillBuf(SaveRegsBuf + infoBase, val);
	infoBase += 0x4;

	// reg 0x5000
	addr = 0x5000;
	RegRead(a_enConnectionType, a_nModuleID, currentFpga, (FPGA_BASE_ADDRESS + addr), &val);
	FillBuf(SaveRegsBuf + infoBase, addr);
	infoBase += 0x4;
	FillBuf(SaveRegsBuf + infoBase, val);
	infoBase += 0x4;

	// reg 0x200C
	addr = 0x200C;
	RegRead(a_enConnectionType, a_nModuleID, currentFpga, (FPGA_BASE_ADDRESS + addr), &val);
	FillBuf(SaveRegsBuf + infoBase, addr);
	infoBase += 0x4;
	FillBuf(SaveRegsBuf + infoBase, val);
	infoBase += 0x4;

	// reg 0x201C
	addr = 0x201C;
	RegRead(a_enConnectionType, a_nModuleID, currentFpga, (FPGA_BASE_ADDRESS + addr), &val);
	FillBuf(SaveRegsBuf + infoBase, addr);
	infoBase += 0x4;
	FillBuf(SaveRegsBuf + infoBase, val);
	infoBase += 0x4;

	//Preserve the fpga Reg Map size to be used in header.
	prevInfo.fpga_Size = infoBase / 0x8;			//As each reg info takes 8 bytes

	//TODO: remove this 512 hard coded value
	objUsbApi.WrMemToSdCard0((UsbApis::DEVICE_TYPES)a_enDeviceType, SaveRegsBuf, fpgaRegSaveOffset,
		512, &pnSizeWritten);
	return S_OK;
}

#pragma endregion saveRegsSdCard


long MiddleAPI::UpdateFirmware(SPPUHostConnectionType a_enConnectionType, SPPUDeviceType a_enDeviceType, char *a_strFileName)
{
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};

	sprintf_s(strDebug, DEBUG_STR_LEN,"\nIn UpdateFirmware(%d, %s)", a_enDeviceType, a_strFileName);
	mPrintDebug(strDebug);

	switch(a_enConnectionType)
	{
	case LFT_HOST_CONNECTION_USB:
		return objUsbApi.UpdateFirmWare((UsbApis::DEVICE_TYPES)a_enDeviceType, a_strFileName);
#if 0
	case LFT_HOST_CONNECTION_PCIE:
		return UpdateFirmWare((DeviceTypesPci) a_enDeviceType, a_strFileName);
#endif
	}
	return -100;
}

long MiddleAPI::RunTest(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,SPPUDeviceType a_enDeviceType,SPPUTestTypes a_enTestType, unsigned int *a_nPropValue)
{
	// TODO function call
	switch(a_enTestType)
	{
	case LFT_SPPU_TEST_FPGA	:
		RunTestFPGA(a_enConnectionType,a_nModuleID,a_enDeviceType,a_nPropValue);
		//RunTestFPGAPerf(a_enConnectionType,a_nModuleID,a_enDeviceType,a_nPropValue);
		break;
	case LFT_SPPU_TEST_DAC_FPGA_INTERFACE:
		RunTestDAC_FPGA(a_enConnectionType,a_nModuleID,a_enDeviceType,a_nPropValue);
		break;
	case   LFT_MegaPxl_USB_UART:
		RunTestuart_USB_UART(a_enConnectionType,a_nModuleID,a_enDeviceType,a_nPropValue);
		break;
	case LFT_SPPU_TEST_SPI_NOR_FLASH:
		RunTestSpiflash(a_enConnectionType,a_nModuleID,a_enDeviceType,a_nPropValue);
		//RunTestNORFLASH(a_enConnectionType,a_nModuleID,a_enDeviceType,a_nPropValue);		 
		break;
	case LFT_MegaPxl_BPI_FLASH :
		RunTestBpiflash(a_enConnectionType,a_nModuleID, a_enDeviceType ,a_nPropValue);
		break;
	case LFT_SPPU_TEST_SD_CARD:
		RunTest_Sdcard(a_enConnectionType,a_nModuleID,a_enDeviceType, a_nPropValue );
		break;
	case LFT_SPPU_TEST_DAC:
		RunTestDAC(a_enConnectionType,a_nModuleID,a_enDeviceType,a_nPropValue);
		break;
	case LFT_SPPU_TEST_CLOCK_SYNTHESIZER:
		RunTestLMK(a_enConnectionType,a_nModuleID,a_enDeviceType,a_nPropValue);
		break;
	case LFT_SPPU_TEST_DDR3:
		RunTest_DDRMEMORY(a_enConnectionType,a_nModuleID,a_enDeviceType,a_nPropValue);
		break;
	case LFT_SPPU_TEST_VOLTAGE:
		// RunTest_VOLTAGE(a_enConnectionType,a_nModuleID,a_enDeviceType,a_nPropValue);
		break;
	case LFT_SPPU_TEST_TEMPERATURE:
		RunTest_temp(a_enConnectionType,a_nModuleID,a_enDeviceType,a_nPropValue);
		break;
	case LFT_SPPU_TEST_ATTUNATOR:
		RunTestAttunator(a_enConnectionType,a_nModuleID,a_enDeviceType,a_nPropValue);
		break;
	case LFT_SPPU_TEST_PCIE_LINK_UP:
		//RunTestLMK(a_enConnectionType,a_nModuleID,a_enDeviceType,a_nPropValue);
		break;
#if 0
	case LFT_SPPU_TEST_USB:
		RunTestUSB(a_enConnectionType,a_nModuleID,a_enDeviceType,a_nPropValue);
		break;
#endif
	case LFT_SPPU_TEST_ETHERNET:
		RunTestEthernet(a_enConnectionType,a_nModuleID,a_enDeviceType,a_nPropValue);
		break;
	case LFT_SPPU_TEST_TRIGGE_IN:
		RunTest_trigger(a_enConnectionType,a_nModuleID,a_enDeviceType,a_nPropValue);
		break;
	case LFT_SPPU_TEST_UNIT_TEST:
		// RunTestLMK(a_enConnectionType,a_nModuleID,a_enDeviceType,a_nPropValue);
		break;
	case LFT_SPPU_TEST_I2C_TEST:
		RunTesti2ceprom(a_enConnectionType,a_nModuleID,a_enDeviceType,a_nPropValue);
		break;
	case LFT_SPPU_TEST_RS232_TEST:
		RunTestuart_RS232(a_enConnectionType,a_nModuleID,a_enDeviceType,a_nPropValue);
		break;
	case LFT_SPPU_TEST_RS422_TEST:
		RunTestuart_RS422(a_enConnectionType,a_nModuleID,a_enDeviceType,a_nPropValue);
		break;
	case LFT_SPPU_TEST_SRAM_TEST:
		RunTestsram(a_enConnectionType,a_nModuleID,a_enDeviceType,a_nPropValue);
		break;
	case LFT_SPPU_TEST_RTC_TEST:
		RunTestrtc(a_enConnectionType,a_nModuleID,a_enDeviceType,a_nPropValue);
		break;
	case LFT_SPPU_TEST_EMMC_TEST:
		RunTest_EMMC(a_enConnectionType,a_nModuleID,a_enDeviceType,a_nPropValue);
		break;
	case LFT_SPPU_TEST_USB:
		RunTest_usb(a_enConnectionType,a_nModuleID,a_enDeviceType,a_nPropValue);
		break;
	case LFT_SPPU_TEST_FX3_USB:
		RunTest_usb_fx3(a_enConnectionType,a_nModuleID,a_enDeviceType,a_nPropValue);
		break;
	case LFT_AIPB_SIC_PARALLELNOR_FLASH:
		RunTest_Parallelnorflash_SIC(a_enConnectionType,a_nModuleID,a_enDeviceType,a_nPropValue);
		break;
	case LFT_AIPB_SIC_DDR3:
		//	 RunTest_DDR3(a_enConnectionType,a_nModuleID,a_enDeviceType,a_nPropValue);
		RunTest_DDR3_test_case_2(a_enConnectionType,a_nModuleID,a_enDeviceType,a_nPropValue);
		break;
	case LFT_AIPB_SIC_ETHERNET:
		RunTest_ethernet(a_enConnectionType,a_nModuleID,a_enDeviceType,a_nPropValue);
		break;
	case LFT_AIPB_SIC_SENSOR:
		sensor_calibration(a_enConnectionType,a_nModuleID,a_enDeviceType,a_nPropValue);
		break;
	case LFT_AIPB_SIC_SENSOR_LOW:
		sensor_calibration_LOW(a_enConnectionType,a_nModuleID,a_enDeviceType,a_nPropValue);
		break;

	case LFT_AIPB_SIC_SENSOR_HIGH:
		sensor_calibration_HIGH(a_enConnectionType,a_nModuleID,a_enDeviceType,a_nPropValue);
		break;
	case LFT_CENT_I2C:
		RunTest_i2ceeprom(a_enConnectionType,a_nModuleID,a_enDeviceType,a_nPropValue);
		break;

	}
	return 0;
}


long MiddleAPI::SetProperty(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,
	SPPUDeviceType a_enDeviceType, unsigned int a_nProp, unsigned int a_nPropValue)
{
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};

	sprintf_s(strDebug, DEBUG_STR_LEN,"\nIn SetProperty(%d, %d, %d, %d, %d)", a_enConnectionType, a_nModuleID, a_enDeviceType, a_nProp, a_nPropValue);
	mPrintDebug(strDebug);

	switch(a_enDeviceType)
	{
	case LFT_SPPU_DEV_DAC1:
	case LFT_SPPU_DEV_DAC2:
	case LFT_SPPU_DEV_DAC3:

		//TBD::   for Dileep allow only LFT_SPPU_DAC_PROP_IO_TEST_STATE setting from GUI
		if( (SPPUDACProp) a_nProp != LFT_SPPU_DAC_PROP_IO_TEST_STATE)
			return 0;

		return SetDACProperty(a_enConnectionType, a_nModuleID, a_enDeviceType, (SPPUDACProp) a_nProp, a_nPropValue);

	case LFT_SPPU_DEV_LMK04806:
		return SetLMKProperty(a_enConnectionType, a_nModuleID,a_enDeviceType, (SPPULMKProp) a_nProp, a_nPropValue);

	case LFT_SPPU_DEV_FPGA:
		return SetFPGAProperty(a_enConnectionType, a_nModuleID,(SPPUFPGAProp) a_nProp, a_nPropValue);

	case LFT_SPPU_DEV_ATTENUATOR:
		return SetAttenuatorProperty(a_enConnectionType, a_nModuleID, (SPPUAttenuatorProp) a_nProp, a_nPropValue);

	}

	return -100;
}

long MiddleAPI::GetProperty(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,SPPUDeviceType a_enDeviceType, unsigned int a_nProp, unsigned int *a_nPropValue)
{
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};

	sprintf_s(strDebug, DEBUG_STR_LEN,"\nIn GetProperty(%d, %d, %d, %d, %x)", a_enConnectionType, a_nModuleID, a_enDeviceType, a_nProp, a_nPropValue);
	mPrintDebug(strDebug);

	switch(a_enDeviceType)
	{

	case LFT_SPPU_DEV_DAC1:
	case LFT_SPPU_DEV_DAC2:
	case LFT_SPPU_DEV_DAC3:
		return GetDACProperty(a_enConnectionType, a_nModuleID, a_enDeviceType, (SPPUDACProp) a_nProp, a_nPropValue);


	case LFT_SPPU_DEV_LMK04806:
		return GetLMKProperty(a_enConnectionType, a_nModuleID, (SPPULMKProp) a_nProp, a_nPropValue);

	case LFT_SPPU_DEV_FPGA:
		return GetFPGAProperty(a_enConnectionType, a_nModuleID, (SPPUFPGAProp) a_nProp, a_nPropValue);

	case LFT_SPPU_DEV_ATTENUATOR:
		return GetAttenuatorProperty(a_enConnectionType, a_nModuleID, (SPPUAttenuatorProp) a_nProp, a_nPropValue);

	}

	return -100;
}

long MiddleAPI::TriggerSetupStart(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,
	SPPUDeviceType a_enDeviceType)
{
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_TRIGGER_ENABLE, 1);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_TRIGGER_START, 1);
	return FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_TRIGGER_START, 0);
}

long MiddleAPI::TriggerSetupStop(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,SPPUDeviceType a_enDeviceType)
{
	return FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_TRIGGER_ENABLE, 0);
}

long MiddleAPI::DACSetupStart(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,SPPUDeviceType a_enDeviceType)
{
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_DAC_SETUP_READ_FROM_DAC0, 1);
	return FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_DAC_SETUP_READ_FROM_DAC1, 1);
}

long MiddleAPI::DACSetupStop(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,SPPUDeviceType a_enDeviceType)
{
#if 0
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_DAC_SETUP_READ_FROM_DAC0, 0);
	return FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_DAC_SETUP_READ_FROM_DAC1, 0);
#endif

	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_DAC_SETUP_READ_FROM_DAC0, 0);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_DAC_SETUP_READ_FROM_DAC1, 0);

	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_INDEFINITE, 0);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_INDEFINITE_CH2, 0);

	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_RESET_DDR, 1);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_RESET_DAC, 1);
	Sleep(10);

	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_RESET_DDR, 0);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_RESET_DAC, 0);

	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_INDEFINITE, 1);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_READ_INDEFINITE_CH2, 1);
	return 0;
}

long MiddleAPI::DACSetupRestart(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,SPPUDeviceType a_enDeviceType)
{
	return DACSetupStart(a_enConnectionType, a_nModuleID, a_enDeviceType);
}

long MiddleAPI::ResetFPGA(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,SPPUDeviceType a_enDeviceType)
{
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_RESET_FPGA, 1);
	Sleep(10);
	return FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_RESET_FPGA, 0);
}
long MiddleAPI::RunTestFPGA(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue)
{
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};
	unsigned int rdData = 0;
	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTestFPGA:RunTest FPGA before write(%d, %d, %d)", a_enConnectionType, a_nModuleID, a_enDeviceType);
	mPrintDebug(strDebug);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_RUN_TEST_FPGA, 66051);
	FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_RUN_TEST_FPGA,&rdData);
	if(rdData != 66051)
		*a_nPropValue = 1;
	else
		*a_nPropValue = 0;

	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTestFPGA:RunTest FPGA before write(%d, %d, %d)", a_enConnectionType, a_nModuleID, a_enDeviceType);
	mPrintDebug(strDebug);
	return *a_nPropValue;


}
//---------------------------	PULKIT : FPGA performance test	---------------------------------//
long MiddleAPI::RunTestFPGAPerf(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue)
{
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};
	unsigned int rdData = 0;
	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTestFPGAPerf:RunTest FPGA before write(%d, %d, %d)", a_enConnectionType, a_nModuleID, a_enDeviceType);
	mPrintDebug(strDebug);
	/*FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_RUN_TEST_FPGA, 66051);
	FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_RUN_TEST_FPGA,&rdData);
	if(rdData != 66051)
	*a_nPropValue = 1;
	else
	*a_nPropValue = 0;

	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTestFPGAPerf:RunTest FPGA before write(%d, %d, %d)", a_enConnectionType, a_nModuleID, a_enDeviceType);
	mPrintDebug(strDebug);*/

	clock_t tStart = clock();
	int testCount = 1000;
	for(int i	=	0;	i	<	testCount;	i++)
	{
		/*REGWRITE RegWrite = (REGWRITE) GetProcAddress(hinstLib, "RegWrite");
		// If the function address is valid, call the function.
		if (NULL != RegWrite) 
		{
		fRunTimeLinkSuccess = TRUE;
		RegWrite(0,16777215,0); 
		}*/
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_RUN_TEST_FPGA, 66051);
	}
	//printf("Time taken (for reg write): %.3fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
	sprintf_s(strDebug,DEBUG_STR_LEN,"\nTime taken (for reg write): %.3fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
	mPrintDebug(strDebug);

	tStart = clock();
	unsigned int dataReturned	=	0;
	for(int i	=	0;	i	<	testCount;	i++)
	{
		/*REGREAD RegRead = (REGREAD) GetProcAddress(hinstLib, "RegRead");
		// If the function address is valid, call the function.
		if (NULL != RegRead) 
		{
		fRunTimeLinkSuccess = TRUE;
		RegRead(0,&dataReturned,0); 
		}*/
		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_RUN_TEST_FPGA,&rdData);
	}
	//printf("Time taken (for reg read): %.3fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
	sprintf_s(strDebug,DEBUG_STR_LEN,"\nTime taken (for reg write): %.3fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
	mPrintDebug(strDebug);
	//printf("Data: %x",dataReturned);
	sprintf_s(strDebug,DEBUG_STR_LEN,"\nData: %x",rdData);
	mPrintDebug(strDebug);

	return *a_nPropValue;
}
//----------------------------------//---------------------------------//--------------------------------//
long MiddleAPI::RunTestDAC(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue)
{
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};
	unsigned int rdData = 0;
	unsigned int wData = 0xf080;

	*a_nPropValue = 0;

	DAC1Reset(a_enConnectionType, a_nModuleID);
	DAC2Reset(a_enConnectionType, a_nModuleID);
	DAC3Reset(a_enConnectionType, a_nModuleID);

	RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_DAC1, 2, wData);
	RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_DAC2, 2, wData);
	RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_DAC3, 2, wData);

	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTestDAC:RunTest DAC before READ(%d, %d, %d)", a_enConnectionType, a_nModuleID, a_enDeviceType);
	mPrintDebug(strDebug);
	RegRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_DAC1, 2, &rdData);
	if(rdData != wData)
	{
		*a_nPropValue = 1;
	}

	RegRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_DAC2, 2, &rdData);
	if(rdData != wData)
	{
		*a_nPropValue = 1;
	}
	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTestDAC:RunTest DAC after READ(%d, %d, %d)", a_enConnectionType, a_nModuleID, a_enDeviceType);
	mPrintDebug(strDebug);
	RegRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_DAC3, 2, &rdData);
	if(rdData != wData)
	{
		*a_nPropValue = 1;
	}

	return (*a_nPropValue);
}

long MiddleAPI::RunTestLMK(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue)
{
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};
	unsigned int rdData = 0;

	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTestLMK:RunTest LMK before READ(%d, %d, %d)", a_enConnectionType, a_nModuleID, a_enDeviceType);
	mPrintDebug(strDebug);

	LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_TEST_LMK,1); // has to chneged
	LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_TEST_LMK,&rdData);
	if (rdData!=1)
		*a_nPropValue = 1;
	else
		*a_nPropValue = 0;
	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTestLMK:RunTest LMK after READ(%d, %d, %d)", a_enConnectionType, a_nModuleID, a_enDeviceType);
	mPrintDebug(strDebug);
	return (*a_nPropValue);
}

long MiddleAPI::RunTestUSB(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType , unsigned int *a_nPropValue)
{
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};
	unsigned int rdData = 0;
	FPGARegAccessWrite(LFT_HOST_CONNECTION_USB  , a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_RUN_TEST_FPGA, 66050); // has to chenged
	FPGARegAccessRead(LFT_HOST_CONNECTION_USB  , a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_RUN_TEST_FPGA,&rdData);

	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTestUSB:RunTest USB before READ(%d, %d, %d)", a_enConnectionType, a_nModuleID, a_enDeviceType);
	mPrintDebug(strDebug);

	if(rdData != 66051)
		*a_nPropValue = 1;
	else
		*a_nPropValue = 0;

	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTestUSB:RunTest USB after READ(%d, %d, %d)", a_enConnectionType, a_nModuleID, a_enDeviceType);
	mPrintDebug(strDebug);

	return (*a_nPropValue);
}

long MiddleAPI::RunTestAttunator(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType , unsigned int *a_nPropValue)
{  
	int status = 0;
	int ret = 0;
	int ret1 = 0;
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};
	ret  = RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 0, 0);
	ret1 = RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0);

	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTestAttunator:RunTest attunator before  READ(%d, %d, %d)", a_enConnectionType, a_nModuleID, a_enDeviceType);
	mPrintDebug(strDebug);

	if (((ret == 1 ) && ( ret1 == 1)) == 1) 
		status = 0;
	else
		status = 1;
	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTestAttunator:RunTest attunator after  READ(%d, %d, %d)", a_enConnectionType, a_nModuleID, a_enDeviceType);
	mPrintDebug(strDebug);
	return status;
}

long MiddleAPI::RunTestEthernet(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType , unsigned int *a_nPropValue)
{
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};
	unsigned int rdData = 0;
	FPGARegAccessWrite(LFT_HOST_CONNECTION_ETH  , a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_RUN_TEST_FPGA, 66051); // has to chenged	
	//FPGARegAccessWrite(LFT_HOST_CONNECTION_ETH  , a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_RUN_TEST_FPGA, 66050); // has to chenged
	FPGARegAccessRead(LFT_HOST_CONNECTION_ETH  , a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_RUN_TEST_FPGA,&rdData);

	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTestEthernet:RunTest ethernet before READ(%d, %d, %d)", a_enConnectionType, a_nModuleID, a_enDeviceType);
	mPrintDebug(strDebug);

	if(rdData != 66051)
		*a_nPropValue = 1;
	else
		*a_nPropValue = 0;

	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTestUSB:RunTest ethernet after READ(%d, %d, %d)", a_enConnectionType, a_nModuleID, a_enDeviceType);
	mPrintDebug(strDebug);

	return (*a_nPropValue);
}
long MiddleAPI::RunTestuart_RS232(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue)
{
	mPrintDebug("+====================================+");
	mPrintDebug("|            RunTest_UART_232        |");
	mPrintDebug("|	               Start			  |");
	mPrintDebug("+====================================+");

	char strDebug[DEBUG_STR_LEN]	=	{'\0'};
	FILE *rdBinFile;
	FILE *wrBinFile;
	unsigned int numBytesWr;
	unsigned int numBytesRd;
	unsigned int i=0;
	char *infile = "self_test_RS232_write.bin";
	char *outfile = "self_test_RS232_read.bin";
	char *wrbuffArr;
	char *rdbuffArr;
	char *rdbuf;
	char *wrbuf;
	unsigned int bitFileType;
	unsigned int val = *a_nPropValue;
	FPGARegAccessRead(LFT_HOST_CONNECTION_SER  , a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_BitFile_Check, &bitFileType); 
	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTest uart 232:Bit file %x)",bitFileType );
	mPrintDebug(strDebug);

	if(val !=bitFileType && bitFileType!= 1)
	{
		mPrintSelfTestLog("*********************  WRONG BIT FILE *************************************");
		mPrintDebug("*******************************WRONG BIT FILE ***********************************");
		*a_nPropValue = 2;
		return *a_nPropValue;
	}


	if(!(rdBinFile = fopen(infile,"rb")))
	{
		mPrintDebug("============FILE didnt open for read===============");
		return *a_nPropValue =1;
	}
	mPrintDebug("============FILE open succesfully for read=========");	

	fseek(rdBinFile, 0, SEEK_END);
	unsigned int dwFileSize = ftell(rdBinFile);
	fseek(rdBinFile, 0, SEEK_SET);

	wrBinFile = fopen(outfile,"wb");
	wrBinFile = fopen(outfile,"ab");

	wrbuffArr = (char *)calloc(dwFileSize, sizeof(char));
	rdbuffArr = (char *)calloc(dwFileSize, sizeof(char));
	wrbuf = (char *)calloc(256, sizeof(char));
	rdbuf = (char *)calloc(256, sizeof(char));

	fread(wrbuffArr,1,dwFileSize, rdBinFile);

	mPrintDebug("\n ============================= Testcase =================================");

	mPrintDebug("\n ============================= FileWrite START =================================");
	tic();

	//objSerialAPI.MemWriteInternal(0x4200, dwFileSize, wrbuffArr, &numBytesWr);
	//Sleep(100);
	//objSerialAPI.MemReadInternal(0x4200, dwFileSize, rdbuffArr, &numBytesRd);
	if(dwFileSize >=256)
	{
		for(i=0;i<(dwFileSize/256);i++)
		{
			mPrintDebug("******************** encounter*******************************");
			if(*a_nPropValue == 20)
			{


				mPrintDebug("********************break encounter*******************************");
				fclose(wrBinFile);
				fclose(rdBinFile);
				*a_nPropValue = 1;
				return *a_nPropValue;
				//break;
			}
			memcpy(wrbuf,wrbuffArr+i*256,256);
			objSerialAPI.MemWriteInternal(0x4200, 256, wrbuf, &numBytesWr);
			objSerialAPI.MemReadInternal(0x4200, 256, rdbuf, &numBytesRd);
			//int ret = objSerialAPI.MemReadInternal(0x4200, 256, rdbuf, &numBytesRd);

			memcpy(rdbuffArr+i*256,rdbuf,256);
		}
	}
	else
	{

		objSerialAPI.MemWriteInternal(0x4200, dwFileSize, wrbuffArr, &numBytesWr);
		Sleep(100);
		objSerialAPI.MemReadInternal(0x4200, dwFileSize, rdbuffArr, &numBytesRd);
	}

	sprintf_s(strDebug, DEBUG_STR_LEN,"Write file size : %d byte",dwFileSize);
	mPrintSelfTestLog(strDebug);
	toc();
	mPrintDebug("\n ============================= FileRead Done =================================");
	fwrite(rdbuffArr, 1, dwFileSize,wrBinFile);
	fflush(wrBinFile);
	fclose(rdBinFile);
	fclose(wrBinFile);
	rdBinFile = NULL;
	wrBinFile = NULL;

	int ret = 0;
	ret = memcmp(wrbuffArr,rdbuffArr,dwFileSize);

	//if((numBytesRd == 256) && (numBytesWr == 256))
	if(ret !=0)
	{
		*a_nPropValue = 1; 
	}
	else
	{
		*a_nPropValue = 0; 
	}

	return *a_nPropValue;
}
long MiddleAPI::RunTestuart_USB_UART(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue)
{
	mPrintDebug("+====================================+");
	mPrintDebug("|            RunTest_USB_UART    |");
	mPrintDebug("|	               Start			  |");
	mPrintDebug("+====================================+");

	char strDebug[DEBUG_STR_LEN]	=	{'\0'};
	FILE *rdBinFile;
	FILE *wrBinFile;
	unsigned int numBytesWr;
	unsigned int numBytesRd;
	unsigned int i=0;
	char *infile = "self_test_RS232_write.bin";
	char *outfile = "self_test_RS232_read.bin";
	char *wrbuffArr;
	char *rdbuffArr;
	char *rdbuf;
	char *wrbuf;
	unsigned int bitFileType;
	unsigned int val = *a_nPropValue;
	FPGARegAccessRead(LFT_HOST_CONNECTION_SER  , a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_BitFile_Check, &bitFileType); 
	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTest uart 232:Bit file %d)",bitFileType );
	mPrintDebug(strDebug);

	if(bitFileType!= 13)
	{
		mPrintSelfTestLog("*********************  WRONG BIT FILE *************************************");
		mPrintDebug("*******************************WRONG BIT FILE ***********************************");
		*a_nPropValue = 2;
		return *a_nPropValue;
	}


	if(!(rdBinFile = fopen(infile,"rb")))
	{
		mPrintDebug("============FILE didnt open for read===============");
		return *a_nPropValue =1;
	}
	mPrintDebug("============FILE open succesfully for read=========");	

	fseek(rdBinFile, 0, SEEK_END);
	unsigned int dwFileSize = ftell(rdBinFile);
	fseek(rdBinFile, 0, SEEK_SET);

	wrBinFile = fopen(outfile,"wb");
	wrBinFile = fopen(outfile,"ab");

	wrbuffArr = (char *)calloc(dwFileSize, sizeof(char));
	rdbuffArr = (char *)calloc(dwFileSize, sizeof(char));
	wrbuf = (char *)calloc(256, sizeof(char));
	rdbuf = (char *)calloc(256, sizeof(char));

	fread(wrbuffArr,1,dwFileSize, rdBinFile);

	mPrintDebug("\n ============================= Testcase =================================");

	mPrintDebug("\n ============================= FileWrite START =================================");
	tic();
	for(i=0;i<(dwFileSize/256);i++)
	{
		mPrintDebug("******************** encounter*******************************");
		if(*a_nPropValue == 20)
		{


			mPrintDebug("********************break encounter*******************************");
			fclose(wrBinFile);
			fclose(rdBinFile);
			*a_nPropValue = 1;
			return *a_nPropValue;
			//break;
		}
		memcpy(wrbuf,wrbuffArr+i*256,256);
		objSerialAPI.MemWriteInternal(0x4200, 256, wrbuf, &numBytesWr);
		objSerialAPI.MemReadInternal(0x4200, 256, rdbuf, &numBytesRd);
		//int ret = objSerialAPI.MemReadInternal(0x4200, 256, rdbuf, &numBytesRd);

		memcpy(rdbuffArr+i*256,rdbuf,256);
	}
	sprintf_s(strDebug, DEBUG_STR_LEN,"Write file size : %d byte",dwFileSize);
	mPrintSelfTestLog(strDebug);
	toc();
	mPrintDebug("\n ============================= FileRead Done =================================");
	fwrite(rdbuffArr, 1, dwFileSize,wrBinFile);
	fclose(rdBinFile);
	fclose(wrBinFile);
	rdBinFile = NULL;
	wrBinFile = NULL;
	if((numBytesRd == 256) && (numBytesWr == 256))
	{
		*a_nPropValue = 0; 
	}
	else
	{
		*a_nPropValue = 1; 
	}

	return *a_nPropValue;
}

long MiddleAPI::RunTestuart_RS422(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue)
{
	mPrintDebug("+====================================+");
	mPrintDebug("|            RunTest_UART_422        |");
	mPrintDebug("|	               Start			  |");
	mPrintDebug("+====================================+");

	char strDebug[DEBUG_STR_LEN]	=	{'\0'};
	FILE *rdBinFile;
	FILE *wrBinFile;
	unsigned int numBytesWr;
	unsigned int numBytesRd;
	unsigned int i=0;
	char *infile = "self_test_RS422_write.bin";
	char *outfile = "self_test_RS422_read.bin";
	char *wrbuffArr;
	char *rdbuffArr;
	char *rdbuf;
	char *wrbuf;
	unsigned int bitFileType;
	unsigned int val = *a_nPropValue;
	FPGARegAccessRead(LFT_HOST_CONNECTION_SER  , a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_BitFile_Check, &bitFileType); 
	//RegRead(LFT_HOST_CONNECTION_SER,a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_BitFile_Check,&bitFileType);
	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTest uart 422:Bit file %x)",bitFileType );
	mPrintDebug(strDebug);

	if(val !=bitFileType && bitFileType!= 4 )
	{
		mPrintSelfTestLog("*********************  WRONG BIT FILE *************************************");
		mPrintDebug("*******************************WRONG BIT FILE ***********************************");
		*a_nPropValue = 2;
		return *a_nPropValue;

	}
	if(!(rdBinFile = fopen(infile,"rb")))
	{
		mPrintDebug("============FILE didnt open for read===============");
		return *a_nPropValue =1;
	}
	mPrintDebug("============FILE open succesfully for read=========");	

	fseek(rdBinFile, 0, SEEK_END);
	unsigned int dwFileSize = ftell(rdBinFile);
	fseek(rdBinFile, 0, SEEK_SET);

	wrBinFile = fopen(outfile,"wb");
	wrBinFile = fopen(outfile,"ab");

	wrbuffArr = (char *)calloc(dwFileSize, sizeof(char));
	rdbuffArr = (char *)calloc(dwFileSize, sizeof(char));
	wrbuf = (char *)calloc(256, sizeof(char));
	rdbuf = (char *)calloc(256, sizeof(char));

	fread(wrbuffArr,1,dwFileSize, rdBinFile);

	mPrintDebug("\n ============================= Testcase =================================");

	mPrintDebug("\n ============================= FileWrite START =================================");
	tic();

	for(i=0;i<(dwFileSize/256);i++)
	{
		mPrintDebug("******************** encounter*******************************");
		if(*a_nPropValue == 20)
		{
			mPrintDebug("********************break encounter*******************************");
			fclose(wrBinFile);
			fclose(rdBinFile);
			*a_nPropValue = 1;
			return *a_nPropValue;
			//break;
		}
		memcpy(wrbuf,wrbuffArr+i*256,256);
		objSerialAPI.MemWriteInternal(0x4200, 256, wrbuf, &numBytesWr);
		objSerialAPI.MemReadInternal(0x4200, 256, rdbuf, &numBytesRd);
		//int ret = objSerialAPI.MemReadInternal(0x4200, 256, rdbuf, &numBytesRd);

		memcpy(rdbuffArr+i*256,rdbuf,256);
	}
	sprintf_s(strDebug, DEBUG_STR_LEN,"Write file size : %d byte",dwFileSize);
	mPrintSelfTestLog(strDebug);
	toc();
	mPrintDebug("\n ============================= FileRead Done =================================");
	fwrite(rdbuffArr, 1, dwFileSize,wrBinFile);
	fclose(rdBinFile);
	fclose(wrBinFile);
	rdBinFile = NULL;
	wrBinFile = NULL;
	if((numBytesRd == 256) && (numBytesWr == 256))
	{
		*a_nPropValue = 0; 
	}
	else
	{
		*a_nPropValue = 1; 
	}

	return *a_nPropValue;
}

long MiddleAPI::RunTesti2ceprom(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue)
{
	mPrintSelfTestLog("******************************I2C EPROM Test Starts **********************************************************");
	mPrintDebug("+====================================+");
	mPrintDebug("|              RunTest_I2C           |");
	mPrintDebug("|	               Start			  |");
	mPrintDebug("+====================================+");

	unsigned int valread ,valwrite, valout, valoutdata = 1;
	unsigned int datain = 0x00;
	//unsigned int i2cdatasize = 0x400;
	unsigned int i2cdatasize = 0x10;	
	unsigned int i2cnostop = 0x0;
	unsigned int i2cdata_rd_ack = 0x00;
	unsigned int i2c_speed = 0x02;
	unsigned int i=0,j,k = 0, x = 0;
	unsigned int reg_offset;
	FILE *rdBinFile, *wrBinFile; //file for write; // file to read
	int wcount, rcount;
	unsigned char *rdbuffArr;
	unsigned char *wrbuffArr;
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};
	char *fname = "self_test_i2c_eeprom_write.bin";

	unsigned int bitFileType;
	FPGARegAccessRead(LFT_HOST_CONNECTION_SER  , a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_BitFile_Check, &bitFileType); 
	//RegRead(LFT_HOST_CONNECTION_SER,a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_BitFile_Check,&bitFileType);
	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTest uart:Bit file %n)",bitFileType );
	mPrintDebug(strDebug);

	if(bitFileType !=6)
	{
		mPrintSelfTestLog("*********************  WRONG BIT FILE *************************************");
		mPrintDebug("*******************************WRONG BIT FILE ***********************************");
		*a_nPropValue = 2;
		return *a_nPropValue;

	}

	/******************************************************muxwrite**********************************************/
	unsigned int dummy=0;
	mPrintDebug("\n ============================= Dummy read write =================================");
	int w_Stat = RegWrite(LFT_HOST_CONNECTION_SER,a_nModuleID, LFT_SPPU_DEV_FPGA, 0x4200,dummy);
	int r_stat =RegRead(LFT_HOST_CONNECTION_SER,a_nModuleID, LFT_SPPU_DEV_FPGA, 0x4200,&dummy);

	sprintf_s(strDebug, DEBUG_STR_LEN,"w_Stat:%d r_stat : %d ",w_Stat,r_stat);
	mPrintDebug(strDebug);

	mPrintDebug("+==================i2c busy check_write==================+");


	unsigned int timeout = 10;
	while(timeout)
	{
		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_CENTROIED_I2CBUSY,&valwrite);
		if(valwrite == 0)
		{
			break;
		}
		timeout--;
		Sleep(100);
	}

	if(timeout == 0)
	{
		mPrintDebug("\n =============================Time Out I2C busy check Failed =================================");
		mPrintSelfTestLog("\n =============================Time Out I2C busy check Failed =================================");
		return *a_nPropValue =1;
	}

	mPrintDebug("+====================i2c CMD_write========================+");

	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_CENTROIED_I2CCMDCODE,datain);

	mPrintDebug("+====================i2c_data_size_write==================+");

	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_CENTROIED_datasize,i2cdatasize);

	mPrintDebug("+====================i2c_no_stop_write====================+");

	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_CENTROIED_i2c_no_stop,i2cnostop);
	mPrintDebug("+====================i2c_data_rd_ack_write================+");

	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_CENTROIED_i2c_data_rdack,i2cdata_rd_ack);

	mPrintDebug("+====================i2c_Speed_write======================+");

	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_CENTROIED_i2c_speed,i2c_speed);
	mPrintDebug("+====================================+");
	mPrintDebug("|              Write Operation        |");
	mPrintDebug("|	              Start here		  |");
	mPrintDebug("+====================================+");


	if(!ifstream (fname))
	{

		mPrintDebug("================Fileisnotpresent===================");
		mPrintSelfTestLog("\n =============================Input File not found  =================================");
		return *a_nPropValue =1;
	}	


	/* opening the file */
	if(!(rdBinFile = fopen("self_test_i2c_eeprom_write.bin","rb")))
	{
		mPrintDebug("============FILE didnt open for read===============");
		mPrintSelfTestLog("\n =============================Can not open file. Run the application with admin right =================================");
		return *a_nPropValue =1;	
	}
	mPrintDebug("============FILE open succesfully for read=========");	

	fseek(rdBinFile, 0, SEEK_END);
	int dwFileSize = ftell(rdBinFile);
	fseek(rdBinFile, 0, SEEK_SET);

	sprintf_s(strDebug, DEBUG_STR_LEN,"file size:%d",dwFileSize);
	mPrintDebug(strDebug);

	if(dwFileSize > 0x400)
	{
		dwFileSize = 0x400;
	}

	wrbuffArr = (unsigned char*)calloc(dwFileSize, sizeof(char));
	rdbuffArr = (unsigned char*)calloc(dwFileSize, sizeof(char));

	wcount = fread(wrbuffArr,1,dwFileSize, rdBinFile);

	sprintf_s(strDebug, DEBUG_STR_LEN,"buffer is:%d",wcount);
	mPrintDebug(strDebug);
	x=0;
	for(i=0;i<(dwFileSize/16);i++)
	{
		reg_offset = i*16;
		sprintf_s(strDebug, DEBUG_STR_LEN,"reg_offset:%d",reg_offset);
		mPrintDebug(strDebug);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_CENTROIED_i2c_regoffset,reg_offset);
		if(i<16)
		{
			//FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_CENTROIED_i2c_slave_addr,0x54);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_CENTROIED_i2c_slave_addr,0x50); // without mux
		}
		else if(i>=16 && i< 32) // doubt
		{

			// FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_CENTROIED_i2c_slave_addr,0x55);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_CENTROIED_i2c_slave_addr,0x51);// without mux
		}
		else if(i>=32 && i< 48) // doubt
		{

			// FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_CENTROIED_i2c_slave_addr,0x56);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_CENTROIED_i2c_slave_addr,0x52); // without mux
		}
		else if(i>=48 && i< 64) // doubt
		{

			// FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_CENTROIED_i2c_slave_addr,0x57);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_CENTROIED_i2c_slave_addr,0x53); // without mux
		}


		for(j=0;j<16;j++)
		{      
			if(*a_nPropValue == 20)
			{


				mPrintDebug("********************break encounter*******************************");
				fclose(rdBinFile);
				*a_nPropValue = 1;
				return *a_nPropValue;
				//break;
			}
			mPrintDebug("===================come in  read for loop=======================");

			int tem = FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_CENTROIED_i2c_data_in,wrbuffArr[x]);
			sprintf_s(strDebug, DEBUG_STR_LEN,"tem:%d ",tem);
			mPrintDebug(strDebug);
			x++;
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_CENTROIED_i2c_data_in_valid,1);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_CENTROIED_i2c_data_in_valid,0);
		}
		mPrintDebug("===========================come out from read for loop==================");
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_CENTROIED_i2c_cmd_exe,1);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_CENTROIED_i2c_cmd_exe,0);
	}
	x = 0;
	fclose(rdBinFile);

	mPrintDebug("+====================================+");
	mPrintDebug("|              Read Operation       |");
	mPrintDebug("|	              Start here		  |");
	mPrintDebug("+====================================+");

	mPrintDebug("==================i2c busy check_write================");
	timeout=10;
	while(timeout)
	{
		mPrintDebug("=================come in  busy check==================");
		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_CENTROIED_I2CBUSY,&valread);
		if(valread	==	0)
		{
			break;		
		}	
		timeout--;
		Sleep(100);
	}

	if(timeout ==0)
	{
		mPrintDebug("\n =============================Time Out I2C busy check Failed =================================");
		mPrintSelfTestLog("\n ============================= Time Out I2C busy check Failed =================================");
		return *a_nPropValue =1;
	}


	mPrintDebug("==================i2c CMD_write=======================");
	datain = 0x02;
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_CENTROIED_I2CCMDCODE,datain);
	mPrintDebug("==================i2c_data_size_write=================");
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_CENTROIED_datasize,i2cdatasize);
	mPrintDebug("==================i2c_no_stop_write===================");
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_CENTROIED_i2c_no_stop,i2cnostop);
	mPrintDebug("==================i2c_data_rd_ack_write===============");
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_CENTROIED_i2c_data_rdack,i2cdata_rd_ack);
	mPrintDebug("==================i2c_Speed_write=====================");
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_CENTROIED_i2c_speed,i2c_speed);

	if(!(wrBinFile = fopen("self_test_i2c_eeprom_read.bin","wb")))
		//if(!(wrBinFile = fopen("D:\\latest_centroied\\xml2_22.12.15bck\\release\\selftestr.bin","wb")))
	{
		mPrintDebug("=================FILE didnt open for write================");
		mPrintSelfTestLog("\n ============================= FILE didnt open for write =================================");
		return *a_nPropValue =1;
	}
	mPrintDebug("================FILE open succesfully for write===========");	

	for(i=0;i<(dwFileSize/16);i++)
	{
		reg_offset = i*16;
		sprintf_s(strDebug, DEBUG_STR_LEN,"reg_offset:%d",reg_offset);
		mPrintDebug(strDebug);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_CENTROIED_i2c_regoffset,reg_offset);
		if(i<16)
		{
			//FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_CENTROIED_i2c_slave_addr,0x54);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_CENTROIED_i2c_slave_addr,0x50); // without mux
		}
		else if(i>=16 && i< 32) // doubt
		{

			// FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_CENTROIED_i2c_slave_addr,0x55);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_CENTROIED_i2c_slave_addr,0x51); // without mux

		}
		else if(i>=32 && i< 48) // doubt
		{

			// FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_CENTROIED_i2c_slave_addr,0x56);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_CENTROIED_i2c_slave_addr,0x52); // without mux
		}
		else if(i>=48 && i< 64) // doubt
		{

			// FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_CENTROIED_i2c_slave_addr,0x57);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_CENTROIED_i2c_slave_addr,0x53);
		}
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_CENTROIED_i2c_cmd_exe,1);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_CENTROIED_i2c_cmd_exe,0);

		for(j=0;j<16;j++)
		{
			timeout=1000;
			while(timeout)
			{
				mPrintDebug("======================come in write while loop==================");
				if(*a_nPropValue == 20)
				{


					mPrintDebug("********************break encounter*******************************");
					fclose(wrBinFile);
					*a_nPropValue = 1;
					return *a_nPropValue;
					//break;
				}
				FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_CENTROIED_I2c_data_out_valid,&valout);
				sprintf_s(strDebug, DEBUG_STR_LEN,"data_out_valid :%d",valout);
				mPrintDebug(strDebug);
				if(valout	==	1)
					break;		
				timeout--;
				Sleep(100);
			}

			if(timeout == 0)
			{
				mPrintDebug("\n =============================Time Out : write while loop =================================");
				return *a_nPropValue = 1;
			}


			sprintf_s(strDebug, DEBUG_STR_LEN,"x_value :%d",x);
			mPrintDebug(strDebug);
			if(*a_nPropValue == 20)
			{


				mPrintDebug("********************break encounter*******************************");
				fclose(wrBinFile);
				*a_nPropValue = 1;
				return *a_nPropValue;
				//break;
			}
			FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_CENTROIED_I2c_data_out,&valoutdata);
			rdbuffArr[x]= valoutdata;
			x++;
			// rcount = fwrite(rdbuffArr, 1, 1, wrBinFile);
			// rcount = fwrite(rdbuffArr, 1, 1024, rdBinFile);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_CENTROIED_i2c_data_rdack,1);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_CENTROIED_i2c_data_rdack,0);
		}
		mPrintDebug("=====================come out write for loop=====================");
	} 

	rcount = fwrite(rdbuffArr, 1, dwFileSize, wrBinFile);
	sprintf_s(strDebug, DEBUG_STR_LEN,"buffer is:%d",rcount);
	mPrintDebug(strDebug);
	fclose(wrBinFile);      
	mPrintDebug("+====================================+");
	mPrintDebug("|              File Comparison       |");
	mPrintDebug("|	              Start here		  |");
	mPrintDebug("+====================================+");

	int ret = 0;
	ret = memcmp(wrbuffArr,rdbuffArr,dwFileSize);
	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn ret::(%d)", ret);
	mPrintDebug(strDebug);
	if (ret != 0)
		*a_nPropValue = 1;
	else
		*a_nPropValue = 0;


	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn a_nPropValue::(%d)", a_nPropValue);
	mPrintDebug(strDebug);

	return *a_nPropValue;
}
long MiddleAPI::RunTestNORFLASH(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType , unsigned int *a_nPropValue)
{
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};
	unsigned int status = 0;
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA , LFT_SPPU_RUN_TEST_SPI_FLASH_STRADDER , 0x01FF0000 );//START ADDRESS
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_SPPU_RUN_TEST_SPI_FLASH_FILE_SIZE, 1 ); // FILE SIZE
	/************************erasemodeenable******************************************/
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_SPPU_RUN_TEST_SPI_FLASH_FILE_MODE_ENABLE, 4);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_SPPU_RUN_TEST_SPI_FLASH_FILE_MODE_ENABLE, 0 );
	Sleep(10);
	/**********************busycheck**********************************************************/

	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTestNORFLASH:RunTestNORFLASH Before while (%d, %d, %d)", a_enConnectionType, a_nModuleID, a_enDeviceType);
	mPrintDebug(strDebug);

	unsigned int val	=	1;
	while(1)
	{
		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_SPPU_RUN_TEST_SPI_FLASH_BUSY_CHECK,&val);
		if(val	==	0)
			break;

	}

	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTestNORFLASH:RunTestNORFLASH AFTER while (%d, %d, %d)", a_enConnectionType, a_nModuleID, a_enDeviceType);
	mPrintDebug(strDebug);

	/***************************writemodeenable*******************************************/
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_SPPU_RUN_TEST_SPI_FLASH_FILE_MODE_ENABLE, 2);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_SPPU_RUN_TEST_SPI_FLASH_FILE_MODE_ENABLE, 0 );

	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTestNORFLASH:RunTestNORFLASH Before FOR (%d, %d, %d)", a_enConnectionType, a_nModuleID, a_enDeviceType);
	mPrintDebug(strDebug);

	unsigned int i = 0;
	for(i = 0; i <= 255; i++)
	{
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_SPPU_RUN_TEST_SPI_FLASH_WRTIE_NOR, i);
	}
	Sleep(10);
	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTestNORFLASH:RunTestNORFLASH after for (%d, %d, %d)", a_enConnectionType, a_nModuleID, a_enDeviceType);
	mPrintDebug(strDebug);


	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTestNORFLASH:RunTestNORFLASH before while2 (%d, %d, %d)", a_enConnectionType, a_nModuleID, a_enDeviceType);
	mPrintDebug(strDebug);


	while(1)
	{
		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_SPPU_RUN_TEST_SPI_FLASH_BUSY_CHECK,&val);
		if(val	==	0)
			break;
	}


	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTestNORFLASH:RunTestNORFLASH after while2 (%d, %d, %d)", a_enConnectionType, a_nModuleID, a_enDeviceType);
	mPrintDebug(strDebug);

	/****************************readmodeenable*************************************/
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_SPPU_RUN_TEST_SPI_FLASH_FILE_MODE_ENABLE, 1);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_SPPU_RUN_TEST_SPI_FLASH_FILE_MODE_ENABLE, 0 );
	Sleep(10);

	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTestNORFLASH:RunTestNORFLASH before while3 (%d, %d, %d)", a_enConnectionType, a_nModuleID, a_enDeviceType);
	mPrintDebug(strDebug);

	while(1)
	{
		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_SPPU_RUN_TEST_SPI_FLASH_BUSY_CHECK,&val);
		if(val	==	0)
			break;

	}


	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTestNORFLASH:RunTestNORFLASH after while3 (%d, %d, %d)", a_enConnectionType, a_nModuleID, a_enDeviceType);
	mPrintDebug(strDebug);

	unsigned int error_count = 0;
	unsigned int value = 0;

	for(i = 0; i <= 255; i++)
	{   
		sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn i inside loop (%d)", i);
		mPrintDebug(strDebug);
		//value = 0;
		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_SPPU_RUN_TEST_SPI_FLASH_READ_NOR,&value);
		sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn value inside loop (%d)", value);
		mPrintDebug(strDebug);
		if (value != i)
		{

			sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn errorcount (%d)", error_count);
			mPrintDebug(strDebug);

			error_count++;
		}
	}

	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn value  outside loop (%d)", value);
	mPrintDebug(strDebug);


	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn value of error count outside loop (%d)", error_count);
	mPrintDebug(strDebug);
	if (error_count == 0)
		*a_nPropValue = 0;
	else
		*a_nPropValue = 1;

	return *a_nPropValue;
}

long MiddleAPI::RunTestDAC_FPGA(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue)
{
	*a_nPropValue = 0;
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};
	DAC1Reset(a_enConnectionType, a_nModuleID);
	DAC2Reset(a_enConnectionType, a_nModuleID);
	DAC3Reset(a_enConnectionType, a_nModuleID);
	ProgramDefaultInLMKRegisters(a_enConnectionType, a_nModuleID);

	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DAC_SETUP_INTERPOLATION, 1);
	Sleep(10);

	DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC1, LFT_SPPU_RUN_TEST_DAC_FPGA_INTERFACE ,61568);
	DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC2, LFT_SPPU_RUN_TEST_DAC_FPGA_INTERFACE ,61568);
	DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3, LFT_SPPU_RUN_TEST_DAC_FPGA_INTERFACE ,61568);

	DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC1, LFT_SPPU_DAC_digital_filter_interpolation_interp ,1);
	DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC2, LFT_SPPU_DAC_digital_filter_interpolation_interp ,1);
	DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3, LFT_SPPU_DAC_digital_filter_interpolation_interp ,1);


	DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC1, LFT_SPPU_DAC_IOTEST_IO_ENA  ,1);
	DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC2, LFT_SPPU_DAC_IOTEST_IO_ENA  ,1);
	DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3, LFT_SPPU_DAC_IOTEST_IO_ENA  ,1);

	//select dac 0
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_operation_Mode_RF_IF, 0);


	StartPattern( a_enConnectionType, a_nModuleID);

	DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC1, LFT_SPPU_DAC_WRITE_ALARM  ,0);
	DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC1, LFT_SPPU_DAC_IOTEST_Result  ,0);

	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTestDAC_FPGA:RunTest DAC_FPGA before read dac1 (%d, %d, %d)", a_enConnectionType, a_nModuleID, a_enDeviceType);
	mPrintDebug(strDebug);

	unsigned int rdDATA = 0;
	DACRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC1, LFT_SPPU_DAC_IOTEST_Result ,&rdDATA);
	if(rdDATA != 0)
	{
		*a_nPropValue = 1;
	}

	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTestDAC_FPGA:RunTest DAC_FPGA after read dac1 (%d, %d, %d)", a_enConnectionType, a_nModuleID, a_enDeviceType);
	mPrintDebug(strDebug);


	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTestDAC_FPGA:RunTest DAC_FPGA before read dac2 (%d, %d, %d)", a_enConnectionType, a_nModuleID, a_enDeviceType);
	mPrintDebug(strDebug);
	DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC2, LFT_SPPU_DAC_WRITE_ALARM  ,0);
	DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC2, LFT_SPPU_DAC_IOTEST_Result  ,0);	
	DACRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC2, LFT_SPPU_DAC_IOTEST_Result ,&rdDATA);
	if(rdDATA != 0)
	{
		*a_nPropValue = 1;
	}

	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTestDAC_FPGA:RunTest DAC_FPGA after read dac2 (%d, %d, %d)", a_enConnectionType, a_nModuleID, a_enDeviceType);
	mPrintDebug(strDebug);
	StopPattern( a_enConnectionType, a_nModuleID);


	//select_dac 1
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_operation_Mode_RF_IF, 1);

	StartPattern( a_enConnectionType, a_nModuleID);

	DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3, LFT_SPPU_DAC_WRITE_ALARM  ,0);
	DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3, LFT_SPPU_DAC_IOTEST_Result  ,0);

	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTestDAC_FPGA:RunTest DAC_FPGA before read dac3 (%d, %d, %d)", a_enConnectionType, a_nModuleID, a_enDeviceType);
	mPrintDebug(strDebug);

	DACRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3, LFT_SPPU_DAC_IOTEST_Result ,&rdDATA);
	if(rdDATA != 0)
	{
		*a_nPropValue = 1;
	}
	StopPattern( a_enConnectionType, a_nModuleID);
	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTestDAC_FPGA:RunTest DAC_FPGA after read dac3 (%d, %d, %d)", a_enConnectionType, a_nModuleID, a_enDeviceType);
	mPrintDebug(strDebug);

	DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC1, LFT_SPPU_DAC_IOTEST_IO_ENA  ,0);
	DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC2, LFT_SPPU_DAC_IOTEST_IO_ENA  ,0);
	DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3, LFT_SPPU_DAC_IOTEST_IO_ENA  ,0);

	return *a_nPropValue;
}
long MiddleAPI::RunTest_trigger(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue)
{
	unsigned int rdDATA = 0;
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_SPPU_RUN_TEST_TRIGGER_IN_CHECK_PLUSE, 1);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_SPPU_RUN_TEST_TRIGGER_IN_CHECK_PLUSE, 0);

	Sleep(1000);
	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTest_trigger:RunTest trigger before read(%d, %d, %d)", a_enConnectionType, a_nModuleID, a_enDeviceType);
	mPrintDebug(strDebug);
	FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_SPPU_RUN_TEST_TRIGGER_IN_CHECK,&rdDATA);

	if(rdDATA != 1)
		*a_nPropValue =1;
	else
		*a_nPropValue = 0;
	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTest_trigger:RunTest trigger after read(%d, %d, %d)", a_enConnectionType, a_nModuleID, a_enDeviceType);
	mPrintDebug(strDebug);
	return *a_nPropValue;
}
long MiddleAPI::RunTest_Sdcard(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue )
{   
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};
	DWORD pnSizeWritten = 0;
	DWORD pnSizeRead = 0;
	unsigned int deviceadd = LFT_SPPU_SDCARD_RUNTEST_OFFSET;
	char datatodesend[1024] = {"\0"};
	char datatorcv[1024]={"\0"};
	unsigned int i , j = 0;
	unsigned int errorcount = 0;
	for(i = 0;i<1024;i++)
	{
		datatodesend[i] = j;
		j++;
		if (j == 64)
			j= 0;
	}
	objUsbApi.WrMemToSdCard0((UsbApis::DEVICE_TYPES)a_enDeviceType, datatodesend, deviceadd,1024, &pnSizeWritten);
	objUsbApi.RdMemFromSdCard0((UsbApis::DEVICE_TYPES)a_enDeviceType, datatorcv, deviceadd, 1024, &pnSizeRead);
	for(i = 0 ;i<1024; i++ )
	{
		if(datatodesend[i] != datatorcv[i])
		{
			sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTest_SDCARD:error count inside loop::(%d)", errorcount);
			mPrintDebug(strDebug);
			errorcount++;
		}

	}
	if (errorcount = 0)
		return *a_nPropValue = 0;
	else
		return *a_nPropValue = 1;

	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTest_SDCARD:error count outside loop::(%d)", errorcount);
	mPrintDebug(strDebug);

}

long MiddleAPI::RunTest_DDRMEMORY(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue)
{
	char strDebug[DEBUG_STR_LEN]  = {'\0'};
	unsigned int writeindefinite  = 0;
	unsigned int axiburstlength   = 0x40;
	unsigned int writeStartAddr   = 0x0;
	unsigned int writeWrapAddr    = 0x03FFFFFF;
	unsigned int writeSize        = 0xFFFFFFC0;
	unsigned int dataPattern      = 0x00010203;
	unsigned int dataType         =  1;
	unsigned int val              = 0;
	int status                    = 0;


	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTest_DDRMEMORY: Before while LFT_SPPU_RUN_TEST_FPGA_WRITE_COMPLETE (%d, %d, %d)", a_enConnectionType, a_nModuleID, a_enDeviceType);
	mPrintDebug(strDebug);


	while(1)
	{
		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA , LFT_SPPU_RUN_TEST_FPGA_WRITE_COMPLETE, &val);
		if(val	==	1)
			break;
	}


	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTest_DDRMEMORY: After while LFT_SPPU_RUN_TEST_FPGA_WRITE_COMPLETE (%d, %d, %d)", a_enConnectionType, a_nModuleID, a_enDeviceType);
	mPrintDebug(strDebug);

	/*************************configure_ddr3_write_from_uart*****************************************************************/
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_WRITE_AXIS_BURST_LENGTH, axiburstlength);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_WRITE_START_ADDRESS, writeStartAddr);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_WRITE_WRAP_ADDRESS, writeWrapAddr);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_WRITE_SIZE, writeSize);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_WRITE_INDEFINITE, writeindefinite);


	/**************************************generate data for test module****************************************************/
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_TEST_MODULE,1 );
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DDR_DATATYPE, dataType);// DOUBT
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DDR_DATAPATTERN, dataPattern);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DDR_TEST_WRITESIZE, writeSize);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DDR_TEST1,1 );
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DDR_TEST1,0 );

	Sleep(1);

	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn generate data Before DDR Busy (%d, %d, %d)", a_enConnectionType, a_nModuleID, a_enDeviceType);
	mPrintDebug(strDebug);
	while(1)
	{
		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_SPPU_FPGA_DDR_BUSY_CHECK1,&val);

		unsigned int val1 = 0;
		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_SPPU_FPGA_DDR_BUSY_CHECK2,&val1);

		if((val	==	1 ) && (val1 == 1))
			break;		
	}

	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_TEST_MODULE,0 );



	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn generate data after DDR Busy (%d, %d, %d)", a_enConnectionType, a_nModuleID, a_enDeviceType);
	mPrintDebug(strDebug);



	/*************************configure_ddr3_Read_from_uart*****************************************************************/

	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_WRITE_AXIS_BURST_LENGTH, axiburstlength);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DDR_READ_START_ADDRESS, writeStartAddr);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_READ_WRAP_ADDRESS, writeWrapAddr);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DDR_READ_SIZE, writeSize);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DDR_READ_INDEFINITE, writeindefinite);



	/**************************************Read data for test module****************************************************/

	Sleep(1);

	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_TEST_MODULE,1 );
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DDR_DATATYPE, dataType);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DDR_DATAPATTERN, dataPattern);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DDR_TEST_WRITESIZE1, writeSize);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DDR_TEST2,1 );
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DDR_TEST2,0 );

	Sleep(1);

	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn Read data for test module: Before DDR Busy (%d, %d, %d)", a_enConnectionType, a_nModuleID, a_enDeviceType);
	mPrintDebug(strDebug);

	while(1)
	{
		unsigned int val1 = 0;
		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_SPPU_FPGA_DDR_BUSY_CHECK12,&val);		
		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_SPPU_FPGA_DDR_BUSY_CHECK22,&val1);

		if((val	==	1 ) && (val1 == 1))
			break;		
	}
	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn Read data for test module: After DDR Busy (%d, %d, %d)", a_enConnectionType, a_nModuleID, a_enDeviceType);
	mPrintDebug(strDebug);

	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_TEST_MODULE,0 );

	FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPU_FPGA_TEST_CASE_PASS,&val );
	if(val != 0)
		*a_nPropValue = 1;
	else
		*a_nPropValue = 0;

	return *a_nPropValue;

}

long MiddleAPI::I2CWrite(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, unsigned int a_nDevAddress, unsigned int a_nRegAddress, unsigned int a_nRegValue)
{   
	char strDebug[DEBUG_STR_LEN]     = {'\0'};
	unsigned int axil_slave_address  = 0x4100;
	unsigned int message_code        = 0;
	unsigned int message_size        = 0;

	unsigned int device_address      = 0X92;
	unsigned int register_address    = 0x51;
	unsigned int register_address1   = 0xAA;
	unsigned int register_data       = 0;

	/********************************************I2C WRITE**************************************************************************************/

	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_RUN_TEST_I2C_MSGCODE,0);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_RUN_TEST_I2C_MSGSIZE,0);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_RUN_TEST_I2C_DEVICE_ADD,a_nDevAddress);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_RUN_TEST_I2C_RESISTER_ADD,a_nRegAddress);


	/********************SEND DATA TO WRITE***********************************/

	for(unsigned int i = 1; i <= message_size;i++ )
	{	
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_RUN_TEST_I2C_DATA_WRITE,  (a_nRegValue >> ((message_size-i) * 8)) & 0xFF);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_RUN_TEST_I2C_DATA_WRITE_ENB,1);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_RUN_TEST_I2C_DATA_WRITE_ENB,0);	
	}

	/***************************************setmsgvalid********************************************************/
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_RUN_TEST_I2C_MSG_VALID,1);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_RUN_TEST_I2C_MSG_VALID,0);


	/**************************************waitforbusysignal****************************************************/


	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTest_TEMP: Before I2C_WRITE while (%d, %d, %d)", a_enConnectionType, a_nModuleID);
	mPrintDebug(strDebug);

	unsigned int val = 1;
	while(1)
	{
		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_SPPU_RUN_TEST_I2C_BUSY_CHECK,&val);
		if(val	==	0)
			break;		
	}

	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTest_TEMP: after I2C_WRITE while (%d, %d, %d)", a_enConnectionType, a_nModuleID);
	mPrintDebug(strDebug);
	return 0;
}

long MiddleAPI::RunTest_temp(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue) 
{
	mPrintDebug("+====================================+");
	mPrintDebug("|              Temperature 		  |");
	mPrintDebug("+====================================+");
	char strDebug[DEBUG_STR_LEN]     = {'\0'};
	unsigned int readValue = 0;
	unsigned int temp =0;
	mPrintDebug("+==================Bit File Check==================+");
	unsigned int bitFileType;
	FPGARegAccessRead(a_enConnectionType  , a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_BitFile_Check, &bitFileType); 
	if( bitFileType!= 12)
	{
		mPrintSelfTestLog("*********************  WRONG BIT FILE *************************************");
		*a_nPropValue = 2;
		return *a_nPropValue;

	}
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_MP_Rd_Enable,1);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_MP_Rd_Enable,0);
	while(readValue == 0)
	{
		if(*a_nPropValue == 20)
		{


			mPrintDebug("********************break encounter*******************************");
			*a_nPropValue = 1;
			return *a_nPropValue;
			//break;
		}
		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_MP_Rd_Chk,&readValue);
	}
	FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_MP_Rd_data,&temp);

	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTest_TEMP: temp %d", temp);
	mPrintDebug(strDebug);
	*a_nPropValue = temp;
	/*if(readValue == 0)
	*a_nPropValue = 0;
	else
	*a_nPropValue = 1;*/



	return 0;//*a_nPropValue;
}
long MiddleAPI::RunTestrtc(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue)
{
	mPrintDebug("+====================================+");
	mPrintDebug("|              RunTest_rtc           |");
	mPrintDebug("|	               Start			  |");
	mPrintDebug("+====================================+");

	unsigned int year_temp =0,mnth_temp=0,day_temp=0,date_temp =0,hour_temp =0, mnt_temp = 0 ,sec_temp =0;
	char strDebug[DEBUG_STR_LEN]    = {'\0'};
	FILE *out_fp;
	char *fname = "self_test_rtc_set_time.txt";
	int lSize= 0;
	unsigned int sec = 0;
	unsigned int mnt = 0;
	unsigned int hour= 0;
	unsigned int day = 0;
	unsigned int date = 0;
	unsigned int mnth = 0;
	unsigned int year = 0;
	unsigned int readval = 0;
	int rcountrtc=0;
	string line;
	std::string item;
	ifstream myfile;

	mPrintDebug("+==================Bit File Check==================+");
	unsigned int bitFileType;
	FPGARegAccessRead(LFT_HOST_CONNECTION_SER  , a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_BitFile_Check, &bitFileType); 
	//RegRead(LFT_HOST_CONNECTION_SER,a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_BitFile_Check,&bitFileType);
	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTest uart:Bit file %x)",bitFileType );
	mPrintDebug(strDebug);
	if( bitFileType!= 8)
	{
		mPrintSelfTestLog("*********************  WRONG BIT FILE *************************************");
		*a_nPropValue = 2;
		return *a_nPropValue;

	}

	myfile.open("self_test_rtc_set_time.txt");
	unsigned int dummy=0;
	mPrintDebug("\n ============================= Dummy read write =================================");
	int ret = RegWrite(a_enConnectionType,a_nModuleID, LFT_SPPU_DEV_FPGA, 0x00,dummy);

	RegRead(a_enConnectionType,a_nModuleID, LFT_SPPU_DEV_FPGA, 0x00,&dummy);

	std::vector<std::string> elems;
	if (myfile.is_open())
	{
		mPrintDebug("FILE OPEN SUCCESFULLY");
		while ( getline (myfile,line) )
		{
			std::stringstream ss(line);
			(strDebug,DEBUG_STR_LEN,"\nIn RunTest_RTC::line:%s", line.c_str());
			mPrintDebug(strDebug);
			while (getline(ss, item, ':'))
			{
				elems.push_back(item);
				(strDebug,DEBUG_STR_LEN,"\n\tsplitted text:%s", elems.at(elems.size()-1).c_str() );
				mPrintDebug(strDebug);
			}
		}
		char buf1[10];
		sprintf( buf1, "%s", elems.at(6).c_str());
		sec = (unsigned int)atoi(buf1);

		char buf2[10];
		sprintf( buf2, "%s", elems.at(5).c_str());
		mnt = (unsigned int)atoi(buf2);

		char buf3[10];
		sprintf( buf3, "%s", elems.at(4).c_str());
		hour = (unsigned int)atoi(buf3);

		char buf4[10];
		sprintf( buf4, "%s", elems.at(3).c_str());
		day = (unsigned int)atoi(buf4);

		char buf5[10];
		sprintf( buf5, "%s", elems.at(2).c_str());
		date = (unsigned int)atoi(buf5);

		char buf6[10];
		sprintf( buf6, "%s", elems.at(1).c_str());
		mnth = (unsigned int)atoi(buf6);

		char buf7[10];
		sprintf( buf7, "%s", elems.at(0).c_str());
		year = (unsigned int)atoi(buf7);
		myfile.close();
	}
	else
	{

		mPrintDebug("file didnt open");
		return 1;

	}

	mPrintDebug("+===============control register=====================+");

	RegWrite(a_enConnectionType,  a_nModuleID, LFT_SPPU_DEV_FPGA, 0X0a,0x20 );

	RegWrite(a_enConnectionType,  a_nModuleID, LFT_SPPU_DEV_FPGA, 0X0b,0x87 );
	mPrintDebug("+=============== Writing data to RTC =====================+");

	RegWrite(a_enConnectionType,  a_nModuleID, LFT_SPPU_DEV_FPGA, 0X00,sec );

	RegWrite(a_enConnectionType,  a_nModuleID, LFT_SPPU_DEV_FPGA, 0X02,mnt );

	RegWrite(a_enConnectionType,  a_nModuleID, LFT_SPPU_DEV_FPGA, 0X04,hour );

	RegWrite(a_enConnectionType,  a_nModuleID, LFT_SPPU_DEV_FPGA, 0X06,day );

	RegWrite(a_enConnectionType,  a_nModuleID, LFT_SPPU_DEV_FPGA, 0X07,date );

	RegWrite(a_enConnectionType,  a_nModuleID, LFT_SPPU_DEV_FPGA, 0X08,mnth );

	RegWrite(a_enConnectionType,  a_nModuleID, LFT_SPPU_DEV_FPGA, 0X09,year );

	RegWrite(a_enConnectionType,  a_nModuleID, LFT_SPPU_DEV_FPGA, 0X0b,0x07 );

	mPrintDebug("+=============== 5 Sec Delay  =====================+");

	_sleep(5000);

	mPrintDebug("+=============== Reading data from RTC =====================+");
	unsigned int readsec = 0;
	RegRead(a_enConnectionType,  a_nModuleID, LFT_SPPU_DEV_FPGA, 0X00,&readsec );

	unsigned int readmnt = 0;
	RegRead(a_enConnectionType,  a_nModuleID, LFT_SPPU_DEV_FPGA, 0X02,&readmnt );

	unsigned int readhour = 0;
	RegRead(a_enConnectionType,  a_nModuleID, LFT_SPPU_DEV_FPGA, 0X04,&readhour );

	unsigned int readday = 0;
	RegRead(a_enConnectionType,  a_nModuleID, LFT_SPPU_DEV_FPGA, 0X06,&readday );
	if(*a_nPropValue == 20)
	{


		mPrintDebug("********************break encounter*******************************");
		//fclose(wrBinFile);
		*a_nPropValue = 1;
		return *a_nPropValue;
		//break;
	}
	unsigned int readdate = 0;
	RegRead(a_enConnectionType,  a_nModuleID, LFT_SPPU_DEV_FPGA, 0X07,&readdate );

	unsigned int readmnth = 0;
	RegRead(a_enConnectionType,  a_nModuleID, LFT_SPPU_DEV_FPGA, 0X08,&readmnth );

	unsigned int readyear = 0;
	RegRead(a_enConnectionType,  a_nModuleID, LFT_SPPU_DEV_FPGA, 0X09,&readyear );

	out_fp = fopen("self_test_rtc_get_time.txt","w");
	fprintf(out_fp,"%4d:%2d:%2d:%2d:%2d:%2d:%2d",readyear,readmnth,readdate,readday,readhour,readmnt,readsec);
	fclose(out_fp);
	sprintf_s(strDebug,DEBUG_STR_LEN,"readyear %4d readmnth:%2d readdate:%2d readday:%2d:readhour%2d readmnt:%2d readsec:%2d",readyear,readmnth,readdate,readday,readhour,readmnt,readsec );
	mPrintDebug(strDebug);
	unsigned int temp_sec;

	temp_sec = sec + 5;

	if(temp_sec >= 60)
	{
		temp_sec = (temp_sec - 60);
	}

	if(temp_sec == readsec)
	{
		mPrintDebug("+=============== Matched =====================+");
		*a_nPropValue = 0;
	}
	else if((temp_sec+1) == readsec)
	{
		mPrintDebug("+=============== Matched extra 1 sec due to delay=====================+");
		*a_nPropValue = 0;
	}
	else
	{
		mPrintDebug("+=============== Not Matched =====================+");
		*a_nPropValue = 1;
	}

	return *a_nPropValue;
}
long MiddleAPI::RunTestsram(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue)
{
	mPrintSelfTestLog("Self Test SRAM ");
	mPrintSelfTestLog("*************************************************");

	mPrintDebug("+====================================+");
	mPrintDebug("|              RunTest_sram          |");
	mPrintDebug("|	               Start			  |");
	mPrintDebug("+====================================+");


	char strDebug[DEBUG_STR_LEN]	=	{'\0'};
	FILE *rdBinFilesram, *wrBinFilesram; //file for write; // file to read
	int wcountsram, rcountsram;
	char *fname = "self_test_async_sram_write.bin";
	unsigned int start_add=0x00;
	unsigned int block_size=0x200000;
	unsigned int last_add =0;
	unsigned int i =0, j = 0;
	unsigned int outdata = 0;
	unsigned char *wrbuffArrsram;
	unsigned char *rdbuffArrsram;

	mPrintDebug("+==================Bit File Check==================+");
	unsigned int bitFileType;
	FPGARegAccessRead(LFT_HOST_CONNECTION_SER  , a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_BitFile_Check, &bitFileType); 
	//RegRead(LFT_HOST_CONNECTION_SER,a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_BitFile_Check,&bitFileType);
	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTest uart:Bit file %x)",bitFileType );
	mPrintDebug(strDebug);

	if( bitFileType!= 5)
	{
		mPrintSelfTestLog("*********************  WRONG BIT FILE *************************************");
		*a_nPropValue = 2;
		return *a_nPropValue;

	}

	mPrintDebug("+==================put data select==================+");

	unsigned int dummy=0;
	mPrintDebug("\n ============================= Dummy read write =================================");
	int ret1 = RegWrite(LFT_HOST_CONNECTION_SER,a_nModuleID, LFT_SPPU_DEV_FPGA, 0x4200,dummy);


	RegRead(LFT_HOST_CONNECTION_SER,a_nModuleID, LFT_SPPU_DEV_FPGA, 0x4200,&dummy);

	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_sram_dataselect,1);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_sram_wren,1);

	if(!ifstream (fname))
	{

		mPrintDebug("=========================if file is present========================");
		return -1;
	}	
	mPrintDebug("+====================================+");
	mPrintDebug("|              Writing on device     |");
	mPrintDebug("|	               Start here		  |");
	mPrintDebug("+====================================+");


	/* opening the file */
	if(!(rdBinFilesram = fopen("self_test_async_sram_write.bin","rb")))
	{
		mPrintDebug("=======================FILE didnt open for read====================");
		*a_nPropValue = 1;

		return *a_nPropValue;

	}
	mPrintDebug("===========================FILE open succesfully for read==============");	

	fseek(rdBinFilesram, 0, SEEK_END);
	int dwFileSize = ftell(rdBinFilesram);
	fseek(rdBinFilesram, 0, SEEK_SET);


	sprintf_s(strDebug, DEBUG_STR_LEN,"file size:%d",dwFileSize);
	mPrintDebug(strDebug);

	if(dwFileSize < block_size)
	{
		block_size = dwFileSize;
	}
	last_add = (start_add + block_size);
	wrbuffArrsram = (unsigned char*)calloc(block_size, sizeof(char));
	rdbuffArrsram = (unsigned char*)calloc(block_size, sizeof(char));

	wcountsram = fread(wrbuffArrsram, 1,block_size, rdBinFilesram);
	sprintf_s(strDebug, DEBUG_STR_LEN,"buffer is:%d",wcountsram);
	mPrintDebug(strDebug);
	sprintf_s(strDebug, DEBUG_STR_LEN,"last_add:%d",last_add);
	mPrintDebug(strDebug);
	int x=0;
	tic();
	for(i=start_add;i<last_add;i++)
	{
		if(*a_nPropValue == 20)
		{


			mPrintDebug("********************break encounter*******************************");
			fclose(rdBinFilesram);
			*a_nPropValue = 1;
			return *a_nPropValue;
			//break;
		}

		x++;
		int k = FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_sram_write_add,i);
		if(k!=0)
		{
			*a_nPropValue = 1;

			return *a_nPropValue;

		}
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_sram_write_data,wrbuffArrsram[i]);	
		sprintf_s(strDebug, DEBUG_STR_LEN,"write_count:%d return value == %d",x,k);
		mPrintDebug(strDebug);
	}
	sprintf_s(strDebug, DEBUG_STR_LEN,"Write file size : %d byte",dwFileSize);
	mPrintSelfTestLog(strDebug);
	toc();
	x=0;
	fclose(rdBinFilesram);

	mPrintDebug("+====================================+");
	mPrintDebug("|          Reading from device       |");
	mPrintDebug("|	             Start here		      |");
	mPrintDebug("+====================================+");


	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_sram_wren,0);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_sram_dataselect,0);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_sram_dataselect,1);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_sram_read,1);



	if(!(wrBinFilesram = fopen("self_test_async_sram_read.bin","wb")))
	{
		mPrintDebug("===============FILE didnt open for write==============");
		*a_nPropValue = 1;

		return *a_nPropValue;

	}
	mPrintDebug("===============FILE open succesfully for write============");	

	int y =0;
	tic();
	for(j=start_add;j<last_add;j++)
	{
		if(*a_nPropValue == 20)
		{


			mPrintDebug("********************break encounter*******************************");
			fclose(wrBinFilesram);
			*a_nPropValue = 1;
			return *a_nPropValue;
			//break;
		}
		y++;
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_sram_read_add,j);
		int k = FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_sram_read_data,&outdata);
		if(k!=0)
		{
			*a_nPropValue = 1;
			mPrintDebug("=============== Connection intrupted ============");	
			return *a_nPropValue;

		}
		rdbuffArrsram[j]= outdata;
		sprintf_s(strDebug, DEBUG_STR_LEN,"read_count:%d",y);
		mPrintDebug(strDebug);
	}
	sprintf_s(strDebug, DEBUG_STR_LEN,"Write file size : %d byte",dwFileSize);
	mPrintSelfTestLog(strDebug);
	toc();
	rcountsram = fwrite(rdbuffArrsram, 1, block_size, wrBinFilesram);
	sprintf_s(strDebug, DEBUG_STR_LEN,"buffer is:%d",rcountsram);
	mPrintDebug(strDebug);
	fclose(wrBinFilesram);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_sram_dataselect,0);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_sram_read,0);

	mPrintDebug("+====================================+");
	mPrintDebug("|              file compareing       |");
	mPrintDebug("|	               Start here		  |");
	mPrintDebug("+====================================+");

	int ret = 0;
	ret = memcmp(wrbuffArrsram,rdbuffArrsram,block_size);
	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn ret::(%d)", ret);
	mPrintDebug(strDebug);


	if(ret !=0)
	{

		mPrintSelfTestLog("SRAM test case 1 status =  Fail");
	}
	else
	{

		mPrintSelfTestLog("SRAM test case 1 status =  Pass");
	}


	unsigned int errorReading=0;

	/////////////////////////////////////////////  puts_reset_sw  //////////////////////////////////
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SIC_RAM_Reset_SW,1);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SIC_RAM_Reset_SW,0);

	///////////////////////////////////////////  puts_write_complete_ram /////////////////////////////
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SIC_WriteComplet_SRAM,1);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SIC_WriteComplet_SRAM,0);
	Sleep(1000);

	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SIC_ReadComplet_SRAM,1);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SIC_ReadComplet_SRAM,0);
	if(*a_nPropValue == 20)
	{


		mPrintDebug("********************break encounter*******************************");
		fclose(wrBinFilesram);
		*a_nPropValue = 1;
		return *a_nPropValue;
		//break;
	}
	/////////  Get error reading //////////////////////////////////////
	FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SIC_ErrorReading_SRAM,&errorReading);

	if(errorReading==1)
	{

		mPrintSelfTestLog("SRAM test Case 3 Status = Fail");
	}
	else
	{

		mPrintSelfTestLog("SRAM test Case 3 Status = Pass");
	}
	mPrintSelfTestLog("*******************************************************************");

	if (ret != 0  || errorReading ==1)
		*a_nPropValue = 1;
	else
		*a_nPropValue = 0;

	return *a_nPropValue;


}
long MiddleAPI::RunTestSpiflash(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue)
{		

	mPrintDebug("+====================================+");
	mPrintDebug("|              run_test SPI          |");
	mPrintDebug("|	               Start here		  |");
	mPrintDebug("+====================================+");

	FILE *rdBinFilespi, *wrBinFilespi; //file for write; // file to read
	int wcountspi, rcountspi;
	unsigned char *wrbuffArrspiflash;
	unsigned char *rdbuffArrspiflash;
	char *fname = "self_test_spi_flash_write.bin";
	unsigned int add_in = 0;
	unsigned int data_out=0;
	unsigned int test = 0;
	int num_page =1;
	int blocksize =256;
	int desiredata =256;
	int dwFileSize= 0;
	int data_remain = 0;
	int num_page_write_device = 0;
	int num_page_write_toremain = 0;
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};
	int i =0, j= 0,k=0,count= 0;

	unsigned int dummy=0;


	unsigned int bitFileType;
	FPGARegAccessRead(LFT_HOST_CONNECTION_SER  , a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_BitFile_Check, &bitFileType); 
	//RegRead(LFT_HOST_CONNECTION_SER,a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_BitFile_Check,&bitFileType);
	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTest uart:Bit file %x)",bitFileType );
	mPrintDebug(strDebug);
	if(bitFileType !=3)
	{
		mPrintSelfTestLog("*********************  WRONG BIT FILE *************************************");
		mPrintDebug("*************************** Wrong bit file **************************************");
		*a_nPropValue = 2;
		return *a_nPropValue;

	}
	//	mPrintDebug("\n ============================= Dummy read write =================================");
	int ret1  = RegWrite(LFT_HOST_CONNECTION_SER,a_nModuleID, LFT_SPPU_DEV_FPGA, 0x4200,dummy);

	RegRead(LFT_HOST_CONNECTION_SER,a_nModuleID, LFT_SPPU_DEV_FPGA, 0x4200,&dummy);

	//	unsigned char *wrbuffArrspiflash = (unsigned char *) calloc(256*num_page,sizeof(char));
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_spiflash_inserttype,4);// flash insert type
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_spiflash_inserttype,0); 

	/************************************************busycheck*******************************************************/
	//	mPrintDebug("========================busycheck===============================");	
	unsigned int timeout = 10;
	while(timeout)
	{
		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_spiflash_busycheck,&test); 
		if(test== 0)
			break;
		timeout--;
		Sleep(100);
	}
	if(timeout ==0)
	{
		mPrintDebug("\n =============================Time Out I2C busy check Failed =================================");
		return *a_nPropValue =1;
	}
	//	mPrintDebug("========================fpgaflashwrite===============================");


	/*************************************************file prepare**************************************************/
	mPrintDebug("+====================================+");
	mPrintDebug("|              WRITING TO DEVICE     |");
	mPrintDebug("|	               Start here		  |");
	mPrintDebug("+====================================+");



	if(!ifstream (fname))
	{

		mPrintDebug("********************if file is present************************");
		*a_nPropValue = 1;

		return *a_nPropValue;

	}


	/* opening the file */
	if(!(rdBinFilespi = fopen("self_test_spi_flash_write.bin","rb")))
	{
		mPrintDebug("*********************FILE didnt open for read*****************");
		*a_nPropValue = 1;

		return *a_nPropValue;

	}
	mPrintDebug("************************FILE open succesfully for read************");	

	fseek(rdBinFilespi, 0, SEEK_END);
	dwFileSize = ftell(rdBinFilespi);
	fseek(rdBinFilespi, 0, SEEK_SET);

	sprintf_s(strDebug, DEBUG_STR_LEN,"file size:%d",dwFileSize);
	mPrintDebug(strDebug);

	wrbuffArrspiflash = (unsigned char*)calloc(dwFileSize, sizeof(char));
	rdbuffArrspiflash = (unsigned char*)calloc(dwFileSize, sizeof(char));

	//num_page = desiredata/blocksize;
	if(dwFileSize < 0x10000000)
	{
		num_page = dwFileSize/blocksize;
	}
	else
	{
		num_page = 0x100000;
	}
	sprintf_s(strDebug, DEBUG_STR_LEN,"num_page=%d",num_page);
	mPrintDebug(strDebug);
	int numByToWr = num_page*256;
	sprintf_s(strDebug, DEBUG_STR_LEN,"numByTowr=%d",numByToWr);
	mPrintDebug(strDebug);


	if(0 == numByToWr)
	{
		sprintf_s(strDebug, DEBUG_STR_LEN,"ERROR: No Data in File!=%d",numByToWr);
		mPrintDebug(strDebug);

		return -1;
	}
	bool page_increase = false;
	data_remain = (numByToWr % blocksize);
	if(data_remain!=0)
	{
		num_page++;
		page_increase = true;

	}
	sprintf_s(strDebug, DEBUG_STR_LEN,"num_page is =%d",num_page);
	mPrintDebug(strDebug);
	//unsigned char *wrbuffArrspiflash = (unsigned char *) calloc(256*num_page,sizeof(char));

	//if(page_increase == false)
	//{
	//	mPrintDebug("=================come to non append mode====================");
	//	rcountspi = fread(wrbuffArrspiflash, 1, numByToWr, rdBinFilespi); 
	//	sprintf_s(strDebug, DEBUG_STR_LEN,"buffer is =%d",rcountspi);
	//	mPrintDebug(strDebug);
	//}
	//else if(page_increase == true)
	//{
	//	mPrintDebug("=================come to  append mode====================");
	//	rcountspi = fread(wrbuffArrspiflash, 1, numByToWr, rdBinFilespi); 
	//	memset(&wrbuffArrspiflash[data_remain], '\0', blocksize - data_remain);
	//	sprintf_s(strDebug, DEBUG_STR_LEN,"buffer is =%d",rcountspi);
	//	mPrintDebug(strDebug);
	//
	//}
	//mPrintDebug("====================================================================");
	//for(k=0;k<256;k++)
	//{
	//sprintf_s(strDebug, DEBUG_STR_LEN,"%x ",wrbuffArrspiflash[k]);
	//mPrintDebug(strDebug);
	//}

	fread(wrbuffArrspiflash,1,dwFileSize, rdBinFilespi);
	/***********************************************fpgaflashwrite**************************************************/
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_spiflash_writetype,0);
	/*************************************************add_in*******************************************************/
	//	mPrintDebug("========================add_in===============================");
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_spiflash_add_in,add_in);
	//	mPrintDebug("========================flash size===============================");
	/************************************************flash size****************************************************/
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_spiflash_flash_size,num_page);
	//	mPrintDebug("========================write_mode_enable===============================");	
	/************************************************write_mode_enable**********************************************/


	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_spiflash_inserttype,2);// flash insert type
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_spiflash_inserttype,0); 
	//	mPrintDebug("====================================================================");

	/**************************************writing to device**************************/
	tic();
	for(i=0;i<num_page;i++)
	{
		for(j=0;j<=255;j++)
		{

			if(*a_nPropValue == 20)
			{


				mPrintDebug("********************break encounter*******************************");
				fclose(rdBinFilespi);
				*a_nPropValue = 1;
				return *a_nPropValue;
				//break;
			}
			sprintf_s(strDebug, DEBUG_STR_LEN,"count is:%d",count);
			mPrintDebug(strDebug);		
			timeout=10;
			while(timeout)
			{

				FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_almost_fullcheck,&test); // doubt
				if(test== 0)
					break;
				timeout--;
				Sleep(10);
			}
			if(timeout ==0)
			{
				mPrintDebug("\n =============================Time Out =================================");
				return *a_nPropValue =1;
			}
			int k;
			k = FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_CENTROIED_spiFlashFifoDataIn,wrbuffArrspiflash[count]);
			if(k!=0)
			{

				*a_nPropValue = 1;

				return *a_nPropValue;
			}
			count++;

		}
	}
	sprintf_s(strDebug, DEBUG_STR_LEN,"Write file size : %d byte",dwFileSize);
	mPrintSelfTestLog(strDebug);
	toc();
	count=0;
	fclose(rdBinFilespi);
	timeout=10;
	while(timeout)
	{
		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_spiflash_busycheck,&test); 
		if(test== 0)
			break;
		timeout--;
		Sleep(10);
	}
	if(timeout ==0)
	{
		mPrintDebug("\n =============================Time Out =================================");
		return *a_nPropValue =1;
	}

	mPrintDebug("+====================================+");
	mPrintDebug("|         READING FROM TO DEVICE     |");
	mPrintDebug("|	             Start here		      |");
	mPrintDebug("+====================================+");

	/******************************************readoperation*******************************************************/
	int l = 0;
	/*************************************************add_in*******************************************************/

	//	mPrintDebug("*************************************************add_in*******************************************************");

	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_spiflash_add_in,add_in);

	//	mPrintDebug("*************************************************num_page_write*******************************************************");

	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_spiflash_flash_size,num_page);

	//	mPrintDebug("*************************************************read_mode_enable*******************************************************");
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_spiflash_inserttype,1);// flash insert type
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_spiflash_inserttype,0); 


	Sleep(10);
	if(!(wrBinFilespi = fopen("self_test_spi_flash_read.bin","wb")))
	{
		mPrintDebug("******************************************************FILE didnt open for write*****************************************************************");
		return -1;
	}

	tic();

	for(i= 0;i<num_page;i++)
	{
		sprintf_s(strDebug, DEBUG_STR_LEN,"PAGE NUM  INSIDE LOOP:%d",num_page);
		mPrintDebug(strDebug);
		for(int j =0 ; j<= 255 ; j++ ) 
		{
			if(*a_nPropValue == 20)
			{


				mPrintDebug("********************break encounter*******************************");
				fclose(wrBinFilespi);
				*a_nPropValue = 1;
				return *a_nPropValue;
				//break;
			}
			sprintf_s(strDebug, DEBUG_STR_LEN,"count is:%d",count);
			mPrintDebug(strDebug);
			timeout=10;
			while(timeout)
			{
				FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_emtycheck,&test); 
				if(test== 0)
					break;
				timeout--;
				Sleep(10);
			}
			if(timeout ==0)
			{
				mPrintDebug("\n =============================Time Out =================================");
				return *a_nPropValue =1;
			}

			//readFpga( &readData, 1, byteAddress, 0);
			FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_spiFlashFifoDataout,&data_out);
			rdbuffArrspiflash[count]=data_out;
			count++;

		}


	}
	sprintf_s(strDebug, DEBUG_STR_LEN,"Write file size : %d byte",dwFileSize);
	mPrintSelfTestLog(strDebug);
	toc();
	//for(k=0;k<256;k++)
	//{
	//sprintf_s(strDebug, DEBUG_STR_LEN,"%x ",rdbuffArrspiflash[k]);
	//mPrintDebug(strDebug);

	//}
	rcountspi = fwrite(rdbuffArrspiflash, 1,numByToWr , wrBinFilespi);
	sprintf_s(strDebug, DEBUG_STR_LEN,"buffer is:%d",rcountspi);
	mPrintDebug(strDebug);	

	fclose(wrBinFilespi);

	int ret = 0;
	ret = memcmp(wrbuffArrspiflash,rdbuffArrspiflash,dwFileSize);
	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn ret::(%d)", ret);
	mPrintDebug(strDebug);
	if (ret != 0)
		*a_nPropValue = 1;
	else
		*a_nPropValue = 0;

	return *a_nPropValue;


}

long MiddleAPI::RunTestBpiflash(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue)
{		

	mPrintDebug("+====================================+");
	mPrintDebug("|              run_test BPI         |");
	mPrintDebug("|	               Start here		  |");
	mPrintDebug("+====================================+");
	mPrintDebug("+====================================+");
	mPrintDebug("|     RunTest_Parallelnorflash_SIC   |");
	mPrintDebug("|	               Start			  |");
	mPrintDebug("+====================================+");
	unsigned int saddr = 0;
	unsigned int readtest = 0;
	unsigned int blocksize = 1;
	unsigned int memory_busy = 0;
	unsigned int flash_busy = 0;
	unsigned int Block_write_ready = 0;
	unsigned int i = 0,j=0,k=0;
	unsigned int writefinal[256] ;
	FILE *rdBinFile, *wrBinFile; //file for write; // file to read
	int wcount, rcount;
	unsigned char *rdbuffArr;
	unsigned char *wrbuffArr;
	unsigned int write_byte;
	unsigned int read_byte;
	unsigned int word_count = 127;
	unsigned int temp1,temp2;
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};
	char *infile = "self_test__parallelnorflash_SIC_write.bin";
	char *outfile = "self_test__parallelnorflash_SIC_read.bin";

	mPrintSelfTestLog("Self Test BPI Flash ");
	mPrintSelfTestLog("*************************************************************************");

	unsigned int bitFileType;
	FPGARegAccessRead(LFT_HOST_CONNECTION_SER  , a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_BitFile_Check, &bitFileType); 
	//RegRead(LFT_HOST_CONNECTION_SER,a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_BitFile_Check,&bitFileType);
	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTest uart:Bit file %x)",bitFileType );
	mPrintDebug(strDebug);
	if(bitFileType !=11)
	{
		mPrintSelfTestLog("*********************  WRONG BIT FILE *************************************");
		mPrintDebug("*************************** Wrong bit file **************************************");
		*a_nPropValue = 2;
		return *a_nPropValue;

	}


	if(!ifstream (infile))
	{
		mPrintDebug("================File is not present===================");
		return *a_nPropValue = 1;
	}	

	/* opening the file */
	if(!(rdBinFile = fopen(infile,"rb")))
	{
		mPrintDebug("============FILE didnt open for read===============");
		return *a_nPropValue = 1;
	}
	mPrintDebug("============FILE open succesfully for read=========");	

	fseek(rdBinFile, 0, SEEK_END);
	int dwFileSize = ftell(rdBinFile);
	fseek(rdBinFile, 0, SEEK_SET);

	sprintf_s(strDebug, DEBUG_STR_LEN,"file size:%d",dwFileSize);
	mPrintDebug(strDebug);

	blocksize = (dwFileSize/256);
	word_count = ((blocksize*128)-1);

	sprintf_s(strDebug, DEBUG_STR_LEN,"\n  blocksize : %d    word_count : %d",blocksize,word_count);
	mPrintDebug(strDebug);
	unsigned int dummy=0;
	//mPrintDebug("\n ============================= Dummy read write =================================");
	//RegWrite(LFT_HOST_CONNECTION_SER,a_nModuleID, LFT_SPPU_DEV_FPGA, 0x4200,dummy);
	//RegRead(LFT_HOST_CONNECTION_SER,a_nModuleID, LFT_SPPU_DEV_FPGA, 0x4200,&dummy);

	int ret1 = RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_writedata,dummy);

	RegRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_writedata,&dummy);
	mPrintDebug("\n ============================= puts_block_sector_erase 1 =================================");

	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_AIPB_SIC_block_sector_erase,1);
	mPrintDebug("\n ============================= puts_block_sector_erase 0 =================================");
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_AIPB_SIC_block_sector_erase,0);

	mPrintDebug("\n ============================= puts_block_start_address =================================");
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_AIPB_SIC_strtadd,saddr);

	mPrintDebug("\n ============================= puts_word_count =================================");
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_AIPB_SIC_word_count,word_count);

	mPrintDebug("\n ============================= gets_controller_status =================================");
	FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_AIPB_SIC_memory_busy,&memory_busy);
	if(memory_busy == 1)
	{
		mPrintDebug("\n ============================= memory is busy =================================");
	}

	FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_AIPB_SIC_flash_busy,&flash_busy);
	if(flash_busy == 1)
	{
		mPrintDebug("\n ============================= flash is busy =================================");
	}
	FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_AIPB_SIC_Block_write_ready,&Block_write_ready);
	if(Block_write_ready == 1)
	{
		mPrintDebug("\n ============================= Block_write_ready =================================");
	}

	unsigned int memory_busy_check = 0;
	mPrintDebug("\n ============================= checking for freeing memory controller =================================");
	FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_memory_busy,&memory_busy_check);
	if(memory_busy_check == 1)
	{
		mPrintDebug("Fatal Error : Memory Controller must be free after restart/power on");
	}

	mPrintDebug("\n ============================= puts_page_write_start =================================");

	mPrintDebug("\n ============================= block_page_write 1 =================================");
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_block_page_write,1);

	mPrintDebug("\n ============================= block_page_write 0 =================================");
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_block_page_write,0);
	mPrintDebug("+====================================+");
	mPrintDebug("|              Write Operation        |");
	mPrintDebug("|	              Start here		  |");
	mPrintDebug("+====================================+");

	wrbuffArr = (unsigned char*)calloc(((word_count+1)*2), sizeof(char));
	rdbuffArr = (unsigned char*)calloc(((word_count+1)*2), sizeof(char));

	wcount = fread(wrbuffArr,1,((word_count+1)*2),rdBinFile);
	sprintf_s(strDebug, DEBUG_STR_LEN,"buffer is:%d",wcount);
	mPrintDebug(strDebug);
	int timeout = 10000;
	for(i = 0; i < (word_count+1);i++)
	{
		//if(i!=0)
		//{
		if(*a_nPropValue == 20)
		{


			mPrintDebug("********************break encounter*******************************");
			fclose(rdBinFile);
			*a_nPropValue = 1;
			return *a_nPropValue;
			//break;
		}
		while(timeout)
		{
			FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_Block_write_ready,&Block_write_ready);
			if(Block_write_ready == 0)
			{
				mPrintDebug("\n ============================= Block_write_ready  =================================");				
			}
			else
			{
				break;
			}
			timeout--;
			Sleep(100);
		}
		if(timeout==0)
		{
			mPrintDebug("\n ============================= timeout  =================================");	
			return *a_nPropValue =1;
		}
		//}

		temp1 = (unsigned int)(wrbuffArr[i*2] & 0xFF);
		temp2 = (unsigned int)((wrbuffArr[i*2+1]) & 0xFF);
		write_byte = (temp1 | (temp2 << 8));

		sprintf_s(strDebug, DEBUG_STR_LEN,"\n write count : %d    write_byte : %x  wrbuffArr : %x %x",i,write_byte,wrbuffArr[i*2+1],wrbuffArr[i*2]);
		mPrintDebug(strDebug);
		int k = FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_writedata,write_byte);
		if (k !=0)
		{
			mPrintDebug("\n ============================= Connection Intrupted =================================");
			return *a_nPropValue =1;
			break;
		}
	}


	mPrintDebug("\n ============================= Write Operation complete =================================");

	mPrintDebug("\n ============================= memory_busy_check =================================");
	timeout = 10;
	while(timeout)
	{
		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_memory_busy,&memory_busy);
		if(memory_busy != 1)
		{
			break;
		}
		timeout--;
		Sleep(100);
	}
	if(timeout == 0)
	{
		mPrintDebug("\n =============================memory_busy_check Time Out =================================");
		return *a_nPropValue =1;
	}
	if(*a_nPropValue == 20)
	{


		mPrintDebug("********************break encounter*******************************");
		//fclose(rdBinFile);
		*a_nPropValue = 1;
		return *a_nPropValue;
		//break;
	}

	mPrintDebug("\n ============================= flash_busy_check =================================");
	timeout=10;
	while(timeout)
	{
		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_flash_busy,&flash_busy);
		if(flash_busy != 1)
		{
			break;
		}
		timeout--;
		Sleep(100);
	}
	if(timeout == 0)
	{
		mPrintDebug("\n =============================Time Out =================================");
		return *a_nPropValue = 1;
	}


	mPrintDebug("\n ============================= block_read_ready =================================");
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_blockreadready,0);

	mPrintDebug("\n ============================= puts_block_start_address =================================");
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_AIPB_SIC_strtadd,saddr);

	mPrintDebug("\n ============================= puts_block_size =================================");
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_AIPB_SIC_block_size,blocksize*128);

	mPrintDebug("\n ============================= gets_controller_status =================================");
	FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_AIPB_SIC_memory_busy,&memory_busy);
	if(memory_busy == 1)
	{
		mPrintDebug("\n ============================= memory is busy =================================");
	}

	FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_AIPB_SIC_flash_busy,&flash_busy);
	if(flash_busy == 1)
	{
		mPrintDebug("\n ============================= flash is busy =================================");
	}
	FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_AIPB_SIC_Block_write_ready,&Block_write_ready);
	if(Block_write_ready == 1)
	{
		mPrintDebug("\n ============================= Block_write_ready =================================");
	}

	mPrintDebug("\n ============================= checking for freeing memory controller =================================");
	FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_memory_busy,&memory_busy_check);
	if(memory_busy_check == 1)
	{
		mPrintDebug("Fatal Error : Memory Controller must be free after restart/power on");
	}

	mPrintDebug("+====================================+");
	mPrintDebug("|              Read Operation        |");
	mPrintDebug("|	              Start here		  |");
	mPrintDebug("+====================================+");



	mPrintDebug("\n ============================= puts_block_read_start =================================");

	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_AIPB_SIC_block_read,1);

	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_AIPB_SIC_block_read,0);

	wrBinFile = fopen(outfile,"wb");

	unsigned int rw_status;
	for(i=0;i<(word_count+1);i++)
	{
		if(*a_nPropValue == 20)
		{


			mPrintDebug("********************break encounter*******************************");
			fclose(wrBinFile);
			*a_nPropValue = 1;
			return *a_nPropValue;
			//break;
		}
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_blockreadready,1);
		timeout=10;
		//while(timeout)
		do
		{
			FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_rw_status,&rw_status);
			//if((rw_status & 0x01) == 0)
			//{
			//	mPrintDebug("\n ============================= flash data valid is low =================================");
			//}
			//else
			//{
			//	break;
			//}
			//timeout--;
			//Sleep(100);
		}while((rw_status & 0x01) == 0);
		//if(timeout == 0)
		//{
		//	mPrintDebug("\n =============================Time Out =================================");
		//	return *a_nPropValue = 1;
		//}

		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_readdata,&read_byte);

		rdbuffArr[i*2] = (char)(read_byte & 0xFF);
		rdbuffArr[i*2 + 1] = (char)((read_byte >> 8) & 0xFF);

		sprintf_s(strDebug, DEBUG_STR_LEN,"\n read count : %d    read_byte : %4x wrbuffArr : %x%x",i,read_byte,rdbuffArr[i*2+1],rdbuffArr[i*2]);
		mPrintDebug(strDebug);

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_blockreadready,0);
	}

	fwrite(rdbuffArr,((word_count+1)*2),1,wrBinFile);

	fclose(wrBinFile);
	fclose(rdBinFile);

	mPrintDebug("\n ============================= Read Operation complete =================================");

	int ret = 0;
	//ret = memcmp(rdbuffArr,wrbuffArr,256);
	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn ret::(%d)", ret);
	mPrintDebug(strDebug);

	for(i=0;i<((word_count+1)*2);i++)
	{
		if(rdbuffArr[i] !=wrbuffArr[i])
		{
			ret = 1;
			sprintf_s(strDebug,DEBUG_STR_LEN,"Test fails at I = %d",i);
			mPrintDebug(strDebug);
			break;
		}

	}
	if (ret != 0)
	{
		mPrintSelfTestLog("Test Case 2 status = Fail");
	}
	else

	{
		mPrintSelfTestLog("Test Case 2 status = Pass");

	}

	////////////////////////   Puts Block Chip Erase /////////////////////////////

	unsigned int readDoneStatus=0;

	int counter =0;
	int staus   =0;
	int internalread=0;
	int dataMatchStatus =0;
	timeout=5000;
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_ChipErase,1);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_ChipErase,0);
	timeout=2000;
	mPrintDebug("\n ============================= flash_busy check =================================");
	while(timeout)
	{
		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_flash_busy,&flash_busy);
		if((flash_busy & 0x01) != 1)
		{
			break;
		}
		timeout--;
		Sleep(100);
	}
	if(timeout == 0)
	{
		mPrintDebug("\n =============================flash_busy Time Out =================================");
		return *a_nPropValue = 1;
	}

	/////////////   Data gen Model   ///////////////////////////////////////////


	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DataGen_ModeSel,1);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DataGen_ModeSel,0);



	mPrintDebug("\n =============================readDoneStatus=================================");
	timeout=5000;
	while(timeout)
	{
		if(*a_nPropValue == 20)
		{


			mPrintDebug("********************break encounter*******************************");
			//fclose(wrBinFile);
			*a_nPropValue = 1;
			return *a_nPropValue;
			//break;
		}
		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_Read_status,&readDoneStatus);
		if(counter == 1000)
		{
			counter = 0;
			staus   = 1;
			mPrintDebug("\n =============================Counter reached 1000 =================================");
			break;
		}
		if((readDoneStatus & 0x01) != 0)
		{
			break;
		}
		timeout--;
		Sleep(100);
	}
	if(timeout == 0)
	{
		mPrintDebug("\n =============================readDoneStatus Time Out =================================");
		return *a_nPropValue = 1;
	}
	unsigned int internlReadStatus=0;
	mPrintDebug("\n ============================= internal_data_rw_done status =================================");

	FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_internal_data_rw_done,&readDoneStatus);
	if(readDoneStatus == 1)
	{

		mPrintDebug("\n ============================= Write Cycle Complete =================================");

	}
	else
	{
		internalread =1;
		mPrintSelfTestLog("Internal Read Write  = Fail");

	}
	unsigned int dataMatch=0;
	FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DataMismatc_Check,&dataMatch);
	if(dataMatch == 1)
	{
		dataMatchStatus =1;
		mPrintDebug("\n =============================  Data Mis-MAtch  =================================");
		mPrintSelfTestLog("Internal Data MAtch   = Fail");

	}
	else
	{

		mPrintDebug("\n =============================Data MAtch  =================================");


	}

	//LFT_AIPB_SIC_internal_data_rw_done

	if(staus == 1)
	{
		mPrintSelfTestLog("Test Case 3 Status = Fail");
		mPrintDebug("\n Test Case 3 Status = Fail");
	}
	else
	{

		mPrintSelfTestLog("Test Case Status = Pass");
		mPrintDebug("Test Case Status = Pass");
	}

	mPrintSelfTestLog("**********************************************************************************************");
	if ( ( ret != 0 ) || ( staus==1 )|| ( dataMatchStatus ==1) || (internalread ==1) )
		*a_nPropValue = 1;
	else
		*a_nPropValue = 0;

	return *a_nPropValue;


}


long MiddleAPI::RunTest_Parallelnorflash(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue)
{
	unsigned int adder = 0;
	unsigned int readtest = 0;
	unsigned int blocksize = 1;
	unsigned int memory_busy = 0;
	unsigned int flash_busy = 0;
	unsigned int Block_write_ready = 0;
	unsigned int i = 0,j=0,k=0;
	unsigned int writefinal[256] ;
	FILE *rdBinFile, *wrBinFile; //file for write; // file to read
	int wcount, rcount;
	char rdbuffArr[256];
	char wrbuffArr[256];
	unsigned int write_byte;
	unsigned int read_byte;
	unsigned int word_count = 127;
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};

	for(i=0;i<256;i++)
	{
		rdbuffArr[i]=0;
		wrbuffArr[i]=0;
	}


	mPrintDebug("+====================================+");
	mPrintDebug("|        RunTest_Parallelnorflash    |");
	mPrintDebug("|	               Start			  |");
	mPrintDebug("+====================================+");
	unsigned int bitFileType;
	FPGARegAccessRead(LFT_HOST_CONNECTION_SER  , a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_BitFile_Check, &bitFileType); 
	//RegRead(LFT_HOST_CONNECTION_SER,a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_BitFile_Check,&bitFileType);
	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTest uart:Bit file %x)",bitFileType );
	mPrintDebug(strDebug);
	if(bitFileType !=2)
	{
		mPrintSelfTestLog("*********************  WRONG BIT FILE *************************************");
		mPrintDebug("*************************** Wrong bit file **************************************");
		*a_nPropValue = 2;
		return *a_nPropValue;

	}
	char *infile = "self_test__parallelnorflash_write.bin";
	char *outfile = "self_test__parallelnorflash_read.bin";

	unsigned int dummy=0;
	mPrintDebug("\n ============================= Dummy read write =================================");
	RegWrite(LFT_HOST_CONNECTION_SER,a_nModuleID, LFT_SPPU_DEV_FPGA, 0x4200,dummy);
	RegRead(LFT_HOST_CONNECTION_SER,a_nModuleID, LFT_SPPU_DEV_FPGA, 0x4200,&dummy);

	mPrintDebug("\n ============================= puts_block_start_address =================================");
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_PARALLELNORFLASH_strtadd,adder);

	mPrintDebug("\n ============================= puts_word_count =================================");
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_PARALLELNORFLASH_word_count,word_count);

	mPrintDebug("\n ============================= gets_controller_status =================================");
	FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_PARALLELNORFLASH_memory_busy,&memory_busy);
	if(memory_busy == 1)
	{
		mPrintDebug("\n ============================= memory is busy =================================");
	}

	FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_PARALLELNORFLASH_flash_busy,&flash_busy);
	if(flash_busy == 1)
	{
		mPrintDebug("\n ============================= flash is busy =================================");
	}
	FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_PARALLELNORFLASH_Block_write_ready,&Block_write_ready);
	if(Block_write_ready == 1)
	{
		mPrintDebug("\n ============================= Block_write_ready =================================");
	}

	unsigned int memory_busy_check = 0;
	mPrintDebug("\n ============================= checking for freeing memory controller =================================");
	FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_PARALLELNORFLASH_memory_busy,&memory_busy_check);
	if(memory_busy_check == 1)
	{
		mPrintDebug("ERROR:: memory has to be free");
	}

	mPrintDebug("+====================================+");
	mPrintDebug("|              Write Operation        |");
	mPrintDebug("|	              Start here		  |");
	mPrintDebug("+====================================+");


	if(!ifstream (infile))
	{
		mPrintDebug("================File is not present===================");
		*a_nPropValue = 1;

		return *a_nPropValue;

	}	

	/* opening the file */
	if(!(rdBinFile = fopen(infile,"rb")))
	{
		mPrintDebug("============FILE didnt open for read===============");
		*a_nPropValue = 1;

		return *a_nPropValue;

	}
	mPrintDebug("============FILE open succesfully for read=========");	

	fseek(rdBinFile, 0, SEEK_END);
	int dwFileSize = ftell(rdBinFile);
	fseek(rdBinFile, 0, SEEK_SET);

	sprintf_s(strDebug, DEBUG_STR_LEN,"file size:%d",dwFileSize);
	mPrintDebug(strDebug);

	wcount = fread(wrbuffArr, 1,256, rdBinFile);
	sprintf_s(strDebug, DEBUG_STR_LEN,"buffer is:%d",wcount);
	mPrintDebug(strDebug);

	do
	{
		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_PARALLELNORFLASH_Block_write_ready,&Block_write_ready);
	}while(Block_write_ready == 0);


	for(i = 0; i < 128;i++)
	{
		do
		{
			FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_PARALLELNORFLASH_Block_write_ready,&Block_write_ready);
		}while(Block_write_ready == 0);

		write_byte = ((wrbuffArr[i*2] & 0xFF) | ((wrbuffArr[i*2+1] << 8 ) & 0xFF));

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_PARALLELNORFLASH_writedata,write_byte);
		if(*a_nPropValue == 20)
		{


			mPrintDebug("********************break encounter*******************************");
			fclose(rdBinFile);
			*a_nPropValue = 1;
			return *a_nPropValue;
			//break;
		}
	}

	mPrintDebug("\n ============================= Write Operation complete =================================");

	mPrintDebug("\n ============================= memory_busy_check =================================");
	do
	{
		if(*a_nPropValue == 20)
		{


			mPrintDebug("********************break encounter*******************************");
			fclose(rdBinFile);
			*a_nPropValue = 1;
			return *a_nPropValue;
			//break;
		}
		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_PARALLELNORFLASH_memory_busy,&memory_busy);
	}while(memory_busy == 1);

	mPrintDebug("\n ============================= flash_busy_check =================================");
	do
	{
		if(*a_nPropValue == 20)
		{


			mPrintDebug("********************break encounter*******************************");
			fclose(rdBinFile);
			*a_nPropValue = 1;
			return *a_nPropValue;
			//break;
		}
		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_PARALLELNORFLASH_flash_busy,&flash_busy);
	}while(flash_busy == 1);

	mPrintDebug("\n ============================= block_read_ready =================================");
	unsigned int blk_rd;
	FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_PARALLELNORFLASH_blockreadready,&blk_rd);
	blk_rd = ((blk_rd & 0xFFFFFFFB) | (0 << 2));
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_PARALLELNORFLASH_blockreadready,blk_rd);

	mPrintDebug("\n ============================= puts_block_start_address =================================");
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_PARALLELNORFLASH_strtadd,adder);

	mPrintDebug("\n ============================= puts_block_size =================================");
	blocksize = 1;
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_PARALLELNORFLASH_blocksize,blocksize);

	mPrintDebug("\n ============================= gets_controller_status =================================");
	FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_PARALLELNORFLASH_memory_busy,&memory_busy);
	if(memory_busy == 1)
	{
		mPrintDebug("\n ============================= memory is busy =================================");
	}

	FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_PARALLELNORFLASH_flash_busy,&flash_busy);
	if(flash_busy == 1)
	{
		mPrintDebug("\n ============================= flash is busy =================================");
	}
	FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_PARALLELNORFLASH_Block_write_ready,&Block_write_ready);
	if(Block_write_ready == 1)
	{
		mPrintDebug("\n ============================= Block_write_ready =================================");
	}

	mPrintDebug("\n ============================= checking for freeing memory controller =================================");
	FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_PARALLELNORFLASH_memory_busy,&memory_busy_check);
	if(memory_busy_check == 1)
	{
		mPrintDebug("ERROR:: memory has to be free");

	}

	mPrintDebug("+====================================+");
	mPrintDebug("|              Read Operation        |");
	mPrintDebug("|	              Start here		  |");
	mPrintDebug("+====================================+");

	mPrintDebug("\n ============================= puts_block_read_start =================================");

	FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_PARALLELNORFLASH_blockreadready,&blk_rd);
	blk_rd = ((blk_rd & 0xFFFFFFFD) | (1 << 1));
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_PARALLELNORFLASH_blockreadready,blk_rd);

	FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_PARALLELNORFLASH_blockreadready,&blk_rd);
	blk_rd = ((blk_rd & 0xFFFFFFFD) | (0 << 1));
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_PARALLELNORFLASH_blockreadready,blk_rd);

	wrBinFile = fopen(outfile,"wb");

	unsigned int rw_status;

	for(k=1;k<=blocksize;k++)
	{
		if(*a_nPropValue == 20)
		{


			mPrintDebug("********************break encounter*******************************");
			fclose(wrBinFile);
			*a_nPropValue = 1;
			return *a_nPropValue;
			//break;
		}
		for(i=0;i<128;i++)
		{
			FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_PARALLELNORFLASH_blockreadready,&blk_rd);
			blk_rd = ((blk_rd & 0xFFFFFFFB) | (1 << 2));
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_PARALLELNORFLASH_blockreadready,blk_rd);

			do
			{
				FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_PARALLELNORFLASH_rw_status,&rw_status);
			}while((rw_status & 0x01) == 0);

			FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_PARALLELNORFLASH_readdata,&read_byte);

			rdbuffArr[i*2] = (read_byte & 0xFF);
			rdbuffArr[i*2 + 1] = ((read_byte >> 8) & 0xFF);

			FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_PARALLELNORFLASH_blockreadready,&blk_rd);
			blk_rd = ((blk_rd & 0xFFFFFFFB) | (0 << 2));
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_PARALLELNORFLASH_blockreadready,blk_rd);
		}
	}

	fwrite(rdbuffArr,256,1,wrBinFile);

	fclose(wrBinFile);
	fclose(rdBinFile);

	mPrintDebug("\n ============================= Read Operation complete =================================");

	int ret = 0;
	ret = memcmp(rdbuffArr,wrbuffArr,256);
	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn ret::(%d)", ret);
	mPrintDebug(strDebug);
	if (ret != 0)
		*a_nPropValue = 1;
	else
		*a_nPropValue = 0;

	return *a_nPropValue;
}
long MiddleAPI::RunTest_usb_fx3(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue)
{
	//#if 0
	//	unsigned int numBytesWr;
	//	unsigned int numBytesRd;
	//	char *infile = "self_test_DDR3_write.bin";
	//	char *outfile = "self_test_DDR3_read______.bin";
	//
	//	char strDebug[DEBUG_STR_LEN]	=	{'\0'};
	//
	//
	//	//SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType, unsigned int a_nStartAddress, unsigned int a_nSize, unsigned int *a_nSizeWritten,char *a_strFileName)
	//	//MemoryWriteFileInternal(a_enConnectionType, a_nModuleID, a_enDeviceType, 0x4200, 0x1000, &numBytesWr, infile);
	//	MemoryReadFileInternal(a_enConnectionType, a_nModuleID, a_enDeviceType, 0x4200, 0x1000, &numBytesRd, outfile);
	//
	//	sprintf_s(strDebug, DEBUG_STR_LEN,"number of byte read %d",numBytesRd);
	//	mPrintDebug(strDebug);
	//	sprintf_s(strDebug, DEBUG_STR_LEN,"number of byte write :%d",numBytesWr);
	//	mPrintDebug(strDebug);
	//
	//	if(numBytesRd != numBytesWr)
	//		return (*a_nPropValue = 1);
	//	else
	//		return (*a_nPropValue = 0);
	//#endif
	//
	//#if 1
	//#if 1
	//	unsigned int size = 0x00001000;
	//	unsigned int writeStartAddr = 0;
	//	unsigned int readStartAddr  = 0;
	//	unsigned int writeEndAddr  =  size;
	//	unsigned int readEndAddr   =  size;
	//	unsigned int dataType      = 1;
	//	unsigned int rw_status;
	//	char strDebug[DEBUG_STR_LEN]	=	{'\0'};
	//
	//	mPrintDebug("\n ============================= testcase_02_uart_to_ddr_write_read_test START =================================");
	//	 
	//	mPrintDebug("\n ============================= checker_enable_disable 0 =================================");
	//	int ret = FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_checker,0);
	//
	//	if(ret !=0)
	//	{
	//		mPrintDebug("\n ============================= Wrong Bit File =================================");
	//		*a_nPropValue = 1;
	//
	//		return *a_nPropValue;
	//
	//	}
	//	
	//	mPrintDebug("\n ============================= wait_ddr_init_complete =================================");
	//	
	//	do
	//	{
	//		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_wait_init,&rw_status);
	//	}while(rw_status == 0);
	//
	//	mPrintDebug("\n ============================= DDR3 Initialization Completed =================================");
	//	
	//	mPrintDebug("\n ============================= uart_configure_ddr3_write =================================");
	//
	//	mPrintDebug("\n ============================= LFT_AIPB_SIC_DDR3_writeStartAddr =================================");
	//	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_writeStartAddr,writeStartAddr);
	//
	//	mPrintDebug("\n ============================= LFT_AIPB_SIC_DDR3_writeEndAddr =================================");
	//	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_writeEndAddr,writeEndAddr);
	//
	//	mPrintDebug("\n ============================= DDR3 configuration completes for Writing data =================================");
	//
	//	mPrintDebug("\n ============================= Give Start Pulse for writing data =================================");
	//	
	//	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_UART_SEND_WritePulse,1);
	//	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_UART_SEND_WritePulse,0);
	//
	//	unsigned int numBytesWr;
	//	unsigned int numBytesRd;
	//	char *infile = "self_test_DDR3_write.bin";
	//	char *outfile = "self_test_DDR3_read.bin";
	//
	//	mPrintDebug("\n ============================= FileWrite START =================================");
	//#if 1
	//
	//	unsigned int rcvdLen;
	//	char byArrPktResp[256];
	//
	//	//objSerialAPI.FileWrite(0x4200,4096,infile,&numBytesWr);
	//	objUsbApi.WrFileToSdCard0((UsbApis::DEVICE_TYPES)a_enDeviceType, infile, 0x4200, 0x1000, (DWORD *)&numBytesWr);
	//	
	//    //objSerialAPI.RecvBuffer(byArrPktResp,16,rcvdLen);
	//
	//#else 
	//	unsigned char wrbuffArr[1024];
	//	//FILE *wrBinFile;
	//	FILE *rdBinFile;
	//	int wcount;
	//	unsigned int wr_val = 0;
	//		if(!ifstream (infile))
	//	{
	//		mPrintDebug("================File is not present===================");
	//		return -1;
	//	}	
	//
	//	/* opening the file */
	//	if(!(rdBinFile = fopen(infile,"rb")))
	//	{
	//		mPrintDebug("============FILE didnt open for read===============");
	//		return -1;	
	//	}
	//		mPrintDebug("============FILE open succesfully for read=========");	
	//
	//	fseek(rdBinFile, 0, SEEK_END);
	//	int dwFileSize = ftell(rdBinFile);
	//	fseek(rdBinFile, 0, SEEK_SET);
	//		
	//	sprintf_s(strDebug, DEBUG_STR_LEN,"file size:%d",dwFileSize);
	//	mPrintDebug(strDebug);
	//		
	//	wcount = fread(wrbuffArr,1024,1,rdBinFile);
	//	sprintf_s(strDebug, DEBUG_STR_LEN,"buffer is:%d",wcount);
	//	mPrintDebug(strDebug);
	//	mPrintDebug("\n ============================= Register Write =================================");
	//	for(int i = 0; i < 256;i++)
	//	{
	//		wr_val = (unsigned int)((wrbuffArr[i*4])|(wrbuffArr[i*4+1] << 8)|(wrbuffArr[i*4+2] <<16)|(wrbuffArr[i*4+3] << 24));
	//		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_AIPB_SIC_DDR3_UART_Write_DATA,wr_val);
	//	}
	//#endif
	//	mPrintDebug("\n ============================= Waiting for Write Done =================================");
	//	
	//	do
	//	{
	//			FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_WriteDone,&rw_status);
	//	}while(rw_status == 0);
	//
	//	mPrintDebug("\n ============================= Writing data into DDR3 Completed =================================");
	//
	//
	//	MemoryReadFileInternal(a_enConnectionType, a_nModuleID, a_enDeviceType, 0x4200, 0x1000, &numBytesRd, outfile);
	//
	//
	/////////////////
	//
	//
	//
	//	mPrintDebug("\n ============================= DDR3 Reading Configuration Starts =================================");
	//
	//	mPrintDebug("\n ============================= LFT_AIPB_SIC_DDR3_readStartAddr =================================");
	//	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_readStartAddr,readStartAddr);
	//
	//	mPrintDebug("\n ============================= LFT_AIPB_SIC_DDR3_readEndAddr =================================");
	//	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_readEndAddr,readEndAddr);
	//
	//	mPrintDebug("\n ============================= DDR3 configuration completes for Reading data =================================");
	//		
	//	mPrintDebug("\n ============================= Give Start Pulse for Reading data pulse =================================");
	//	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_UART_SEND_ReadPulse,1);
	//	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_UART_SEND_ReadPulse,0);
	//
	//	mPrintDebug("\n ============================= FileRead START =================================");
	//#if 1
	//	//objSerialAPI.FileRead(0X4200,4096,outfile,&numBytesRd);
	//	objUsbApi.RdFileFromSdCard0((UsbApis::DEVICE_TYPES)a_enDeviceType, outfile, 0x4200, 0x1000, (DWORD *)&numBytesRd);
	//	
	//	mPrintDebug("\n ============================= Waiting for Read Done =================================");
	//
	//	do
	//	{
	//			
	//			FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_ReadDone,&rw_status);
	//			
	//			
	//	}while(rw_status == 0);
	//
	//	mPrintDebug("\n ============================= Reading data from DDR3 Completed =================================");
	//
	//	mPrintDebug("\n ============================= CheckerResult =================================");
	//	// Commented by shivendra 25 -04 -2016 
	//	if((numBytesRd == 4096) && (numBytesWr == 4096))
	//	{
	//		*a_nPropValue = 0; 
	//	}
	//	else
	//	{
	//		*a_nPropValue = 1; 
	//	}
	//
	//#else
	//	unsigned char rdbuffArr[1024];
	////	unsigned char wrbuffArr[1024];
	//	
	//	FILE *wrBinFile;
	//	//FILE *rdBinFile;
	//	//int wcount;
	//	
	//	//unsigned int wr_val = 0;
	//	
	//	unsigned int rd_val = 0;
	//	unsigned int test_result = 0;
	//	int rcount;
	//	wrBinFile = fopen(outfile,"w");
	//	//wrBinFile = fopen(outfile,"a");
	//	mPrintDebug("\n ============================= Register read =================================");
	//
	//	for(int i = 0; i < 256;i++)
	//	{
	//		//wr_val = (unsigned int)((wrbuffArr[i*4])|(wrbuffArr[i*4+1] << 8)|(wrbuffArr[i*4+2] <<16)|(wrbuffArr[i*4+3] << 24));
	//		//FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_AIPB_SIC_ETH_reg_fifo,wr_val);
	//		FPGARegAccessRead(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_AIPB_SIC_DDR3_UART_Read_DATA,&rd_val);
	//		rdbuffArr[i*4]   = (rd_val & 0xFF);
	//		rdbuffArr[i*4+1] = ((rd_val >> 8) & 0xFF);
	//		rdbuffArr[i*4+2] = ((rd_val >> 16)& 0xFF);
	//		rdbuffArr[i*4+3] = ((rd_val >> 24)& 0xFF);
	//		Sleep(10);
	//		/*if(rd_val != wr_val)
	//		{
	//			test_result++;
	//			sprintf_s(strDebug, DEBUG_STR_LEN,"Test Fail at i = %d",i);
	//			mPrintDebug(strDebug);
	//			*a_nPropValue = 1;
	//			break;
	//		}
	//		else
	//		{
	//			*a_nPropValue = 0;
	//		}*/
	//
	//	}
	//	fwrite(rdbuffArr,1024,1,wrBinFile);
	//	fclose(wrBinFile);
	//
	//
	//	mPrintDebug("\n ============================= Waiting for Read Done =================================");
	//	int wait_Count =0;
	//	do
	//	{
	//			
	//			FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_ReadDone,&(unsigned int)rw_status);
	//			wait_Count++;
	//			
	//	}while(rw_status == 0);
	//
	//	mPrintDebug("\n ============================= Comparing read and write buffer  =================================");
	//		if(!ifstream (infile))
	//	{
	//		mPrintDebug("================File is not present===================");
	//		return -1;
	//	}	
	//
	//	/* opening the file */
	//	if(!(rdBinFile = fopen(infile,"rb")))
	//	{
	//		mPrintDebug("============FILE didnt open for read===============");
	//		return -1;	
	//	}
	//		mPrintDebug("============FILE open succesfully for read=========");	
	//
	//	fseek(rdBinFile, 0, SEEK_END);
	//	int dwFileSize1 = ftell(rdBinFile);
	//	fseek(rdBinFile, 0, SEEK_SET);
	//		
	//	sprintf_s(strDebug, DEBUG_STR_LEN,"file size:%d",dwFileSize1);
	//	mPrintDebug(strDebug);
	//		
	//	wcount = fread(wrbuffArr,1024,1,rdBinFile);
	//	sprintf_s(strDebug, DEBUG_STR_LEN,"buffer is:%d",wcount);
	//	mPrintDebug(strDebug);
	//		mPrintDebug("\n ============================= Comparing read and write start buffer  =================================");
	//	for(int i = 0; i < 256;i++)
	//	{
	//		wr_val = (unsigned int)((wrbuffArr[i*4])|(wrbuffArr[i*4+1] << 8)|(wrbuffArr[i*4+2] <<16)|(wrbuffArr[i*4+3] << 24));
	//		rd_val = (unsigned int)((rdbuffArr[i*4])|(rdbuffArr[i*4+1] << 8)|(rdbuffArr[i*4+2] <<16)|(rdbuffArr[i*4+3] << 24));
	//		if(rd_val != wr_val)
	//		{
	//			test_result++;
	//			sprintf_s(strDebug, DEBUG_STR_LEN,"Test Fail at i = %d",i);
	//			mPrintDebug(strDebug);
	//			*a_nPropValue = 1;
	//			break;
	//		}
	//		else
	//		{
	//			*a_nPropValue = 0;
	//		}
	//	}
	//
	//	
	//#endif
	//#if 0
	//
	//	int timeout = 10;
	//	unsigned int val	=	5;
	//	
	//	while(timeout)
	//	{
	//		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_ReadDone, &val);
	//		if(val	==	1)
	//			break;
	//		Sleep(100);
	//		timeout--;
	//		////  shivendra 
	//		if(timeout ==2)
	//		{
	//			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, (SPPUFPGARegsDefs)0x00,0x11223344);
	//		}
	//	}
	///*	
	//#else
	//
	//	do
	//	{
	//			
	//			FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_ReadDone,&(unsigned int)rw_status);
	//			
	//			
	//	}while(rw_status == 0);
	//*/	
	//	
	//#endif
	//	//do
	//	//{
	//	//		
	//	//		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_ReadDone,&(unsigned int)rw_status);
	//	//		
	//	//		
	//	//}while(rw_status == 0);
	//
	//	//mPrintDebug("\n ============================= Reading data from DDR3 Completed =================================");
	//
	//	//mPrintDebug("\n ============================= CheckerResult =================================");
	//	//// Commented by shgivendra 25 -04 -2016 
	//	//if((numBytesRd == 1024) && (numBytesWr == 1024))
	//	//{
	//	//	*a_nPropValue = 0; 
	//	//}
	//	//else
	//	//{
	//	//	*a_nPropValue = 1; 
	//	//}
	//
	//	
	// return *a_nPropValue;
	//#else
	//Fpga image has FIFO and no actual DDR connection.
	//Working
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};
	unsigned long *pnSizeWritten;
	unsigned long *pnSizeRead;
	long retWrite	=	-10000;
	FILE *wr_ptr;
	FILE *wrBinFile;
	FILE *rdBinFile;
	long retRead;
	char *outfile_L = "self_test_usb_read.bin";
	char *infile_L = "self_test_usb_write.bin";

	wr_ptr = fopen("self_test_usb_write.bin","rb");
	if(wr_ptr == NULL)
	{
		mPrintDebug("Test Data file self_test_usb_write.bin not found");
		*a_nPropValue = 1;
		return *a_nPropValue;
	}

	fseek(wr_ptr, 0L, SEEK_END);
	unsigned int dwFileSize= ftell(wr_ptr);
	fseek(wr_ptr, 0L, SEEK_SET);


	char *wrbuffArr = (char *)calloc(dwFileSize, sizeof(char));
	char *rdbuffArr = (char *)calloc(dwFileSize, sizeof(char));


	fread(wrbuffArr,1,dwFileSize, wr_ptr);
	fclose(wr_ptr);
	//sprintf_s(strDebug, DEBUG_STR_LEN,"\nIn MemoryWriteFileInternal(%d, %d, %d, %08x, %d, %x, %s)", a_enConnectionType, a_nModuleID, a_enDeviceType, a_nStartAddress, a_nSize, a_nSizeWritten, a_strFileName);
	//mPrintDebug(strDebug);
	unsigned int bitFileType;
	//objUsbApi.RegisterRead(LFT_AIPB_SIC_BitFile_Check,&bitFileType);
	FPGARegAccessRead(LFT_HOST_CONNECTION_USB  , a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_BitFile_Check, &bitFileType); 
	//RegRead(LFT_HOST_CONNECTION_SER,a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_BitFile_Check,&bitFileType);
	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTest uart:Bit file %x)",bitFileType );
	mPrintDebug(strDebug);
	if(bitFileType !=7)
	{
		mPrintSelfTestLog("*********************  WRONG BIT FILE *************************************");
		mPrintDebug("*************************** Wrong bit file **************************************");
		*a_nPropValue = 2;
		return *a_nPropValue;

	}

	mPrintDebug("\n ========================= SELF Test Process write Start===============================");
	pnSizeWritten	=	new unsigned long(0);

	retWrite 	=	objUsbApi.WrFileToSdCard0((UsbApis::DEVICE_TYPES)a_enDeviceType, infile_L, 0, dwFileSize, pnSizeWritten);
	//*a_nSizeWritten	=	(unsigned int) *pnSizeWritten;
	mPrintDebug("\n ========================= SELF Test Process Read Start===============================");

	DWORD abc = 0;

	retRead = objUsbApi.RdFileFromSdCard0((UsbApis::DEVICE_TYPES)a_enDeviceType, outfile_L, 0, dwFileSize, &abc);//pnSizeRead);


	mPrintDebug("============FILE open succesfully for read=========");

	rdBinFile = fopen("self_test_usb_read.bin","rb");
	fread(rdbuffArr,1,dwFileSize, rdBinFile);
	fclose(rdBinFile);
	int ret = 0;
	ret = memcmp(wrbuffArr,rdbuffArr,dwFileSize);
	if(ret !=0)
	{
		*a_nPropValue = 1; 
		return *a_nPropValue;
	}
	else
	{
		*a_nPropValue = 0; 
		return *a_nPropValue;
	}
	//fseek(rdBinFile, 0, SEEK_END);
	// dwFileSize = ftell(rdBinFile);
	//fseek(rdBinFile, 0, SEEK_SET);

	//
	//char *infile = "self_test_RS232_write.bin";
	//char *outfile = "self_test_RS232_read.bin";

	//wrBinFile = fopen(outfile_L,"wb");
	//rdBinFile = fopen(infile_L,"rb");

	//char *wrbuffArr = (char *)calloc(dwFileSize, sizeof(char));
	//char *rdbuffArr = (char *)calloc(dwFileSize, sizeof(char));


	//fread(wrbuffArr,1,dwFileSize, wrBinFile);

	//fread(rdbuffArr,1,dwFileSize, rdBinFile);


	//int ret = 0;
	//ret = memcmp(wrbuffArr,rdbuffArr,dwFileSize);

	////if((numBytesRd == 256) && (numBytesWr == 256))
	//if(ret !=0)
	//{
	//	*a_nPropValue = 1; 
	//}
	//else
	//{
	//	*a_nPropValue = 0; 
	//}


	mPrintDebug("\n ========================= SELF Test Process Read end===============================");
	if((retWrite==0)&&(retRead==0))
	{
		mPrintDebug("\n ========================= Read write sucess ===============================");
		return *a_nPropValue = 0;
	}
	else
	{
		if(retWrite!=0)
		{
			mPrintDebug("\n =========================write failure ===============================");
		}

		return *a_nPropValue = 1;
	}


	//#endif	
	//#endif
}

long MiddleAPI::sensor_calibration_LOW(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue)
{
	mPrintDebug("\n ============================= Sensor calib low   =================================");

	Sleep(50);
	unsigned int avg_done = 0;
	char file_read[1024];
	unsigned int i=0;
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};
	FILE * wrfile_L;
	unsigned int numBytesWr;
	unsigned int numBytesRd;
	//std::string sector = std::to_string(42);
	char outfile_L[20];// = "LOW_00.hex";
	sprintf(outfile_L,"LOW%d.hex",*a_nPropValue);
	//outfile_L[4] = ((*a_nPropValue/10) + 48);
	//outfile_L[5] = ((*a_nPropValue%10) + 48);
	//	sprintf(outfile_L,"LOW%d.hex",*a_nPropValue);
	printf_s(strDebug, DEBUG_STR_LEN,"FileWrite::  Filename:%s",   outfile_L);
	mPrintDebug(strDebug);

	mPrintDebug("*********************** Bit File Check ******************************************");
	unsigned int bitFileType;
	FPGARegAccessRead(LFT_HOST_CONNECTION_SER  , a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_BitFile_Check, &bitFileType); 
	//RegRead(LFT_HOST_CONNECTION_SER,a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_BitFile_Check,&bitFileType);
	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTest uart:Bit file %x)",bitFileType );
	mPrintDebug(strDebug);
	if( bitFileType!= 9)
	{
		mPrintSelfTestLog("*********************  WRONG BIT FILE *************************************");
		*a_nPropValue = 1;
		return *a_nPropValue;

	}
	/*mPrintDebug("\n ============================= Device Reset    =================================");
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_Device_Reset,1);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_Device_Reset,0);
	*/
	mPrintDebug("\n ============================= Write frame size    =================================");
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_write_frame_size,0x00050000);
	mPrintDebug("\n ============================= start_frame_averaging for LOW temp=================================");

	mPrintDebug("\n ============================= start_avg_enable pulse=================================");
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_start_avg_flag,1);
	Sleep(10);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_start_avg_flag,0);				

	mPrintDebug("\n ============================= waiting for avg_done =================================");
	do
	{
		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_start_avg_done,&avg_done);	
	}while(avg_done == 0);

	mPrintDebug("\n ============================= start_sram_read =================================");
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_sram_rd_flag ,1);
	Sleep(10);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_sram_rd_flag ,0);
	mPrintDebug("\n ============================= bulk_read_data_FA =================================");

	errno_t err;
	err = fopen_s(&wrfile_L, outfile_L, "wb");
	if (err == 0)
	{
		mPrintDebug("\n File open successfully ");
	}
	else
	{
		mPrintDebug("\n Can not  open successfully ");
		*a_nPropValue = 21;
		return *a_nPropValue;
	}

	for(i=0;i<2560;i++)
	{
		printf_s(strDebug, DEBUG_STR_LEN,"N prop val:%d",   *a_nPropValue);
		mPrintDebug(strDebug);
		if(*a_nPropValue == 20)
		{


			mPrintDebug("********************break encounter*******************************");
			fclose(wrfile_L);
			*a_nPropValue = 21;
			return *a_nPropValue;
			//break;
		}
		objSerialAPI.MemReadInternal(0x4200,256,file_read,&numBytesRd);
		fwrite(file_read,1,256,wrfile_L);
	}
	fclose(wrfile_L);
	mPrintDebug("\n ============================= start_frame_averaging for LOW temp Done =================================");
	//wrfile_L = NULL;
	//	free(wrfile_L);
	*a_nPropValue = 0;
	return *a_nPropValue;
}

long MiddleAPI::sensor_calibration_HIGH(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue)
{
	unsigned int avg_done = 0;
	char file_read[1024];
	unsigned int i=0;
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};
	FILE * wrfile_H;
	unsigned int numBytesWr;
	unsigned int numBytesRd;
	//char outfile_H[20];

	//sprintf(outfile_H,"HIGH%d.hex",*a_nPropValue);

	char outfile_H[20];// = "HIGH.hex";
	sprintf(outfile_H,"HIGH%d.hex",*a_nPropValue);
	/*outfile_H[6] = ((*a_nPropValue/10) + 48);
	outfile_H[7] = ((*a_nPropValue%10) + 48);*/
	//char *outfile_H = "HIGH1.hex";

	mPrintDebug("\n ============================= start_frame_averaging for HIGH temp=================================");
	Sleep(50);

	mPrintDebug("\n ============================= start_avg_enable pulse=================================");
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_start_avg_flag,1);
	Sleep(10);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_start_avg_flag,0);				

	mPrintDebug("\n ============================= waiting for avg_done =================================");
	do
	{
		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_start_avg_done,&avg_done);	
	}while(avg_done == 0);

	mPrintDebug("\n ============================= start_sram_read =================================");
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_sram_rd_flag ,1);
	Sleep(10);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_sram_rd_flag ,0);
	mPrintDebug("\n ============================= bulk_read_data_FA =================================");

	errno_t err;
	err = fopen_s(&wrfile_H,outfile_H, "wb");
	if (err == 0)
	{
		mPrintDebug("\n File open successfully ");
	}
	for(i=0;i<2560;i++)
	{
		if(*a_nPropValue == 20)
		{


			mPrintDebug("********************break encounter*******************************");
			fclose(wrfile_H);
			*a_nPropValue = 21;
			return *a_nPropValue;
			//break;
		}
		objSerialAPI.MemReadInternal(0x4200,256,file_read,&numBytesRd);
		fwrite(file_read,1,256,wrfile_H);
	}
	//std::flush(wrfile_H);
	fclose(wrfile_H);
	mPrintDebug("\n ============================= start_frame_averaging for HIGH temp Done =================================");
	//	wrfile_H = NULL;
	//	free(wrfile_H);
	*a_nPropValue = 2;
	return *a_nPropValue;
}

long MiddleAPI::sensor_calibration(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue)
{
	unsigned int avg_done = 0;
	unsigned int flash_ready_out = 0;
	unsigned int rd_data=0;
	unsigned int wr_data=0;
	unsigned int i=0,j=0;
	unsigned int sector = *a_nPropValue;
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};
	unsigned int numBytesWr;
	unsigned int numBytesRd;

	////char *outfile_L = "LOW1.hex";
	//char outfile_L[8];
	//sprintf(outfile_L,"LOW%d.hex",*a_nPropValue);

	////char *outfile_H = "HIGH1.hex";

	//char outfile_H[9];
	//sprintf(outfile_H,"HIGH%d.hex",*a_nPropValue);


	//char *outfile_L = "LOW_00.hex";
	char outfile_L[20];// = "HIGH.hex";
	sprintf(outfile_L,"LOW%d.hex",*a_nPropValue);
	/*outfile_L[4] = ((*a_nPropValue/10) + 48);
	outfile_L[5] = ((*a_nPropValue%10) + 48);*/
	/*char *outfile_H = "HIGH_00.hex";
	outfile_H[6] = ((*a_nPropValue/10) + 48);
	outfile_H[7] = ((*a_nPropValue%10) + 48);*/

	char outfile_H[20];// = "HIGH.hex";
	sprintf(outfile_H,"HIGH%d.hex",*a_nPropValue);

	char *outfile_M = "MED1.hex";
	//char *lowFile = outfile_L;
	//char *highFile =outfile_H;

	//char *outfile_L = "low.hex";
	//char *outfile_H = "high.hex";
	//char *outfile_M = "mid.hex";

	//	char *outfile_R = "final.hex";
	char outfile_R[21];
	//changed by SD to automate file name as per sector value
	/*char *outfile_R = "compensatedFrame_00.hex";
	outfile_R[16] = ((*a_nPropValue/10) + 48);
	outfile_R[17] = ((*a_nPropValue%10) + 48);*/

	mPrintDebug("\n calibrated file =================================");	
	sprintf(outfile_R,"compensatedFrame%d.hex",*a_nPropValue);

	//char strDebug[DEBUG_STR_LEN]	=	{'\0'};
	sprintf_s(strDebug, DEBUG_STR_LEN,"***********************************calibrated::  Filename:%s",   outfile_R);
	mPrintDebug(strDebug);



	int ret = sensor_calibration_MATLAB(outfile_L,outfile_H,outfile_M,a_nPropValue);

	*a_nPropValue = 3;

	return *a_nPropValue;
	if(ret ==0)
	{
		*a_nPropValue = 4;

		return *a_nPropValue;
	}

	mPrintDebug("\n ============================= Write frame size    =================================");
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_write_frame_size,0x00050000);

	mPrintDebug("\n ============================= Sensor_calibration START =================================");


	//{

	//	return *a_nPropValue = 1; 
	//}

	mPrintDebug("\n ============================= write_frames_into_flash Start =================================");

	mPrintDebug("\n ============================= puts_select_sector =================================");
	//// comented by _SD_ as per request 8/07/2016
	/*	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_puts_select_sector,sector);*/

	mPrintDebug("\n ============================= frame_wr_enable =================================");
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_frame_wr_flag ,1);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_frame_wr_flag ,0);

	mPrintDebug("\n ============================= wait_for_one =================================");
	do
	{
		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_flash_ready_out ,&flash_ready_out);
	}while(flash_ready_out == 0);

	mPrintDebug("\n ============================= bulk_write_data0 =================================");
	mPrintDebug("\n ============================= File name for bulk write  =================================");

	sprintf_s(strDebug, DEBUG_STR_LEN,"***********************************calibrated::  Filename:%s",   outfile_R);
	mPrintDebug(strDebug);
	mPrintDebug("\n =====================++++++++++++++++++++++++++++++++++ =================================");



	objSerialAPI.FileWrite(0x4204,2097152,outfile_R,&numBytesWr);	//=================================================================== write final.hex to flash

	do
	{
		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_flash_ready_out ,&flash_ready_out);
	}while(flash_ready_out == 1);

	/*mPrintDebug("\n ============================= frame_wr_disable =================================");
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_frame_wr_flag ,0);*/
	//// Comented by _SD__ as per request 
	/*mPrintDebug("\n ============================= frame_rd_enable =================================");
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_frame_rd_flag ,1);


	do
	{
	FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_flash_ready_out ,&flash_ready_out);
	}while(flash_ready_out == 1);
	*/
	*a_nPropValue = 3;

	return *a_nPropValue;


	/*
	//============================================ reading finel.hex file from flash for testing only ======================================

	mPrintDebug("\n ============================= start_sram_read =================================");
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_sram_rd_flag ,1);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_sram_rd_flag ,0);

	errno_t err;
	FILE *wrfile_F;
	char file_read[1024];
	err = fopen_s(&wrfile_F,"final_rd.hex", "wb");
	if (err == 0)
	{
	mPrintDebug("\n final_rd.hex open successfully ");
	}
	mPrintDebug("\n ============================= reading final.hex file from flash start =================================");
	for(i=0;i<8192;i++)
	{
	objSerialAPI.MemReadInternal(0x4200,256,file_read,&numBytesRd);
	fwrite(file_read,1,256,wrfile_F);
	}
	fclose(wrfile_F);

	mPrintDebug("\n ============================= reading final.hex file from flash done=================================");

	*a_nPropValue = 3;

	return *a_nPropValue;
	*/

}
long MiddleAPI::sensorCalib_Frame_RdWr(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,SPPUDeviceType a_enDeviceType,SPPUTestTypes rd_wr_operation,char *fileName, unsigned int *a_nPropValue)
{
	unsigned int avg_done = 0;
	unsigned int flash_ready_out = 0;
	unsigned int rd_data=0;
	unsigned int wr_data=0;
	unsigned int i=0,j=0;
	unsigned int sector = *a_nPropValue;

	unsigned int numBytesWr;
	unsigned int numBytesRd;
	//sprintf_s(strDebug,DEBUG_STR_LEN,"\n fileName %s ", fileName);
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};
	sprintf_s(strDebug, DEBUG_STR_LEN,"FileWrite::  Filename:%s",   fileName);
	mPrintDebug(strDebug);

	switch(rd_wr_operation)
	{
		unsigned int bitFileType;
	case LFT_SIC_File_wr	:

		FPGARegAccessRead(LFT_HOST_CONNECTION_SER  , a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_BitFile_Check, &bitFileType); 
		//RegRead(LFT_HOST_CONNECTION_SER,a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_BitFile_Check,&bitFileType);
		sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTest uart:Bit file %x)",bitFileType );
		mPrintDebug(strDebug);
		if( bitFileType!= 9)
		{
			mPrintSelfTestLog("*********************  WRONG BIT FILE *************************************");
			*a_nPropValue = 1;
			return *a_nPropValue;

		}
		mPrintDebug("\n ============================= Write frame size    =================================");
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_write_frame_size,0x00050000);
		mPrintDebug("\n ============================= write_frames_into_flash Start =================================");

		mPrintDebug("\n ============================= puts_select_sector =================================");
		bitFileType =0;
		FPGARegAccessRead(LFT_HOST_CONNECTION_SER  , a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_puts_select_sector, &bitFileType); 
		//RegRead(LFT_HOST_CONNECTION_SER,a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_BitFile_Check,&bitFileType);
		sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTest sector value ====  %x)",bitFileType );
		mPrintDebug(strDebug);
		//FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_puts_select_sector,sector);

		mPrintDebug("\n ============================= frame_wr_enable =================================");
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_frame_wr_flag ,1);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_frame_wr_flag ,0);

		mPrintDebug("\n ============================= wait_for_one =================================");
		do
		{
			FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_flash_ready_out ,&flash_ready_out);
		}while(flash_ready_out == 0);
		mPrintDebug("\n ============================= bulk_write_data0 =================================");


		sprintf_s(strDebug, DEBUG_STR_LEN,"FileWrite::  Filename:%s",   fileName);
		mPrintDebug(strDebug);
		//fileName = "compensatedFrame0.hex";
		objSerialAPI.FileWrite(0x4204,2097152,fileName,&numBytesWr);	//=================================================================== write final.hex to flash

		do
		{
			FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_flash_ready_out ,&flash_ready_out);
		}while(flash_ready_out == 1);

		//mPrintDebug("\n ============================= frame_wr_disable =================================");
		//FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_frame_wr_flag ,0);

		//// write process complete here ///////////////////////////////////////////////////////////////////////////////////



		return *a_nPropValue = 0;
		break;
	case LFT_SIC_File_rd :

		FPGARegAccessRead(LFT_HOST_CONNECTION_SER  , a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_BitFile_Check, &bitFileType); 
		//RegRead(LFT_HOST_CONNECTION_SER,a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_BitFile_Check,&bitFileType);
		sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTest uart:Bit file %x)",bitFileType );
		mPrintDebug(strDebug);
		if( bitFileType!= 9)
		{
			mPrintSelfTestLog("*********************  WRONG BIT FILE *************************************");
			*a_nPropValue = 1;
			return *a_nPropValue;

		}

		mPrintDebug("\n ============================= frame_rd_enable =================================");
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_frame_rd_flag ,1);


		do
		{
			FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_flash_ready_out ,&flash_ready_out);
		}while(flash_ready_out == 1);

		mPrintDebug("\n ============================= start_sram_read =================================");
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_sram_rd_flag ,1);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_sram_rd_flag ,0);

		errno_t err;
		FILE *wrfile_F;
		char file_read[1024];

		err = fopen_s(&wrfile_F,fileName, "wb");
		//err = fopen_s(&wrfile_F,"final_rd.hex", "wb");
		if (err == 0)
		{
			mPrintDebug("\n final_rd.hex open successfully ");
		}
		mPrintDebug("\n ============================= reading final.hex file from flash start =================================");
		for(i=0;i<8192;i++)
		{
			if(*a_nPropValue == 20)
			{


				mPrintDebug("********************break encounter*******************************");
				fclose(wrfile_F);
				*a_nPropValue = 21;
				return *a_nPropValue;
				//break;
			}
			objSerialAPI.MemReadInternal(0x4200,256,file_read,&numBytesRd);
			fwrite(file_read,1,256,wrfile_F);
		}
		fclose(wrfile_F);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_frame_rd_flag ,0);
		mPrintDebug("\n ============================= reading final.hex file from flash done=================================");
		return *a_nPropValue = 0;
		break;

	}
	//return 1;
}
float MiddleAPI::round_f(float x)
{
	return x >= 0.0f ? floorf(x + 0.5f) : ceilf(x - 0.5f);
}

time_t seconds_begin, seconds_end, seconds;
unsigned long long ms_begin, ms_end, ms;
long MiddleAPI::tic(void)
{
	seconds_begin = time(NULL);
	ms_begin = GetTickCount64();
	return 0;
}
long MiddleAPI::toc(void)
{
	ms_end = GetTickCount64();
	ms = ms_end - ms_begin;
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};
	seconds_end = time (NULL);
	seconds = (seconds_end - seconds_begin);
	sprintf_s(strDebug,DEBUG_STR_LEN,"\n Time elapsed:: %d sec", seconds);
	mPrintSelfTestLog(strDebug);
	sprintf_s(strDebug, DEBUG_STR_LEN, "\n Time elapsed:: %d ms", ms);
	mPrintSelfTestLog(strDebug);
	return 0;
}

#define ROW 512
#define COL 640
#define COL1 1024

long MiddleAPI::sensor_calibration_MATLAB(char *infile_L,char *infile_H,char *infile_M,unsigned int *a_nPropValue)
{



	static unsigned short MED1[ROW*COL];

	static unsigned short HIGH1[ROW*COL];

	static unsigned short LOW1[ROW*COL];

	static unsigned int bpr[ROW][COL1];

	unsigned int cnt1 = 0, cnt2 = 0;
	unsigned int cnt3 = 0;
	static int d[ROW][COL];

	unsigned int  lavg;//= 3005;
	unsigned int havg;// = 4283;
	unsigned int diff;// = (havg - lavg);
	static float g[ROW][COL];

	static unsigned int g_map[ROW][COL];

	static unsigned int g_o[ROW][COL1];

	unsigned int g_o_cnt = 0;
	static unsigned short high[ROW][COL];

	unsigned int m = 0;
	unsigned int max = 0;
	unsigned int i = 0, j = 0;
	unsigned long int k = 0;
	static unsigned int im_bpr[ROW][COL];
	static unsigned short im_bpr_o[ROW][COL];
	static unsigned int im_new_h[ROW][COL];
	static unsigned int im_new_l[ROW][COL];
	static unsigned short low[ROW][COL];
	double mean_high = 0;
	double mean_low = 0;
	static short med[ROW][COL];
	static float o[ROW][COL];
	static unsigned int o_map[ROW][COL];
	static unsigned int o_o[ROW][COL1];
	static unsigned int off_mem[ROW][COL1];
	static unsigned int rt[ROW][COL];
	double sum_low = 0;
	double sum_high = 0;
	double std_low = 0;
	double std_high = 0;

	static unsigned short g_o_test[ROW][COL1];
	static unsigned short o_o_test[ROW][COL1];
	static unsigned short off_mem_test[ROW][COL1];
	static unsigned int final_test_tmp[ROW][COL1];
	static unsigned int final_test[ROW][COL1];
	unsigned char dat_ptr1=0;
	unsigned char dat_ptr2=0;

	FILE *rdfile_L;
	FILE *rdfile_H;
	FILE *rdfile_M;
	FILE *wrfile_R;
	FILE *wrfile_G;
	FILE *wrfile_O;
	FILE *final_O;

	////char *infile_L = "low.hex";
	////char *infile_H = "high.hex";
	////char *infile_M = "mid.hex";
	std::ifstream infile_low(infile_L);

	std::ifstream infile_high(infile_H);
	std::ifstream infile_mid(infile_M);

	if( ! infile_low.good())
	{

		mPrintDebug("********************Low if file is not present************************");
		*a_nPropValue = 0;

		return *a_nPropValue;

	}



	if(!infile_high.good())
	{

		mPrintDebug("********************High if file is not present************************");
		*a_nPropValue = 0;

		return *a_nPropValue;

	}




	if(! infile_mid.good() )
	{

		mPrintDebug("********************Mid if file is not present************************");
		*a_nPropValue = 0;

		return *a_nPropValue;

	}



	printf("\n\n =========== sensor_calibration_MATLAB_SW START ===========");
	mPrintDebug("\n =============================sensor_calibration_MATLAB_SW START step 19 =================================");
	fopen_s(&rdfile_M,infile_M,"rb");
	fread(MED1, 2, ROW*COL, rdfile_M);
	fclose(rdfile_M);
	mPrintDebug("\n =============================sensor_calibration_MATLAB_SW START step 21 =================================");
	fopen_s(&rdfile_L,infile_L,"rb");
	fread(LOW1, 2, ROW*COL, rdfile_L);
	fclose(rdfile_L);
	mPrintDebug("\n =============================sensor_calibration_MATLAB_SW START step 20 =================================");
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};
	sprintf_s(strDebug, DEBUG_STR_LEN,"FileWrite::  Filename:%s",   infile_H);
	mPrintDebug(strDebug);
	errno_t err =fopen_s(&rdfile_H,infile_H,"rb");
	//errno_t err;
	if(err !=0)
	{
		mPrintDebug("\n ============================= Can not open file =================================");

		sprintf_s(strDebug, DEBUG_STR_LEN,"FileWrite::  error:%d",   err);
		mPrintDebug(strDebug);
		//sprintf_s(strDebug,DEBUG_STR_LEN,"file error",(char*)perror("error"));

		//return *a_nPropValue = 1;
	}
	fread(HIGH1, 2, ROW*COL, rdfile_H);
	fclose(rdfile_H);

	mPrintDebug("\n =============================sensor_calibration_MATLAB_SW START step 22 =================================");
	FILE *debug_file;
	debug_file = fopen("debug.txt", "w");
	debug_file = fopen("debug.txt", "a");

	// ==============================================================================================
	// ==============================================================================================
	//FILE *low1_file;
	//FILE *high1_file;
	//FILE *d_file;
	//low1_file = fopen("low1.txt", "w");
	//high1_file = fopen("high1.txt", "w");
	//d_file = fopen("d.txt", "w");
	//low1_file = fopen("low1.txt", "a");
	//high1_file = fopen("high1.txt", "a");
	//d_file = fopen("d.txt", "a");
	mPrintDebug("\n =============================sensor_calibration_MATLAB_SW START step 10 =================================");
	for (i = 0; i<ROW; i++)
	{
		for (j = 0; j<COL; j++)
		{
			low[i][j] = LOW1[k];
			high[i][j] = HIGH1[k];
			med[i][j] = (MED1[k] - 450);
			d[i][j] = (high[i][j] - low[i][j] + 1);
			k = k + 1;
			mean_low += (float)low[i][j];
			mean_high += (float)high[i][j];
			//fprintf(low1_file,"\n%d",low[i][j]);
			//fprintf(high1_file,"\n%d", high[i][j]);
			//fprintf(d_file,"\n%d", d[i][j]);
		}
	}
	mPrintDebug("\n =============================sensor_calibration_MATLAB_SW START step 11 =================================");
	//fclose(low1_file);
	//fclose(high1_file);
	//fclose(d_file);
	//sprintf_s(strDebug, DEBUG_STR_LEN,"\n B4 mean_low : %f     mean_high : %f",mean_low,mean_high);
	//mPrintDebug(strDebug);
	mean_low = (mean_low / (COL * ROW));
	lavg = mean_low;
	mean_high = (mean_high / (COL * ROW));
	havg = mean_high;
	diff = havg - lavg;

	fprintf(debug_file, "\n\n mean_low : %.6f     mean_high : %.6f", mean_low, mean_high);
	//sprintf_s(strDebug, DEBUG_STR_LEN,"\n mean_low : %f     mean_high : %f",mean_low,mean_high);
	//mPrintDebug(strDebug);
	sum_low = 0;
	sum_high = 0;

	for (i = 0; i<ROW; i++)
	{
		for (j = 0; j<COL; j++)
		{
			sum_low = sum_low + ((low[i][j] - mean_low)*(low[i][j] - mean_low));
			sum_high = sum_high + ((high[i][j] - mean_high)*(high[i][j] - mean_high));
		}
	}
	mPrintDebug("\n =============================sensor_calibration_MATLAB_SW START step 12 =================================");
	//sprintf_s(strDebug, DEBUG_STR_LEN,"\n sum_low : %f     sum_high : %f",sum_low,sum_high);
	//mPrintDebug(strDebug);
	fprintf(debug_file, "\nsum_low : %f     sum_high : %f", sum_low, sum_high);
	double val = 0;
	val = sum_low / (COL * ROW);
	std_low = sqrt(val);
	val = sum_high / (COL * ROW);
	std_high = sqrt(val);
	//sprintf_s(strDebug, DEBUG_STR_LEN,"\n std_low : %f     std_high : %f",std_low,std_high);
	//mPrintDebug(strDebug);
	fprintf(debug_file, "\nstd_low : %f     std_high : %f", std_low, std_high);
	mPrintDebug("\n =============================sensor_calibration_MATLAB_SW START step 13 =================================");
	// ==============================================================================================
	// ==============================================================================================
	//calculating bad pixels for low temp
	unsigned int im_new_l_1C = 0;
	unsigned int im_new_l_0C = 0;
	for (i = 0; i<ROW; i++)
	{
		for (j = 0; j<COL; j++)
		{
			if ((low[i][j]<(mean_low - 3.0 * std_low)) || ((low[i][j]>(mean_low + 3.0 * std_low))))
			{
				im_new_l[i][j] = 1;
				im_new_l_1C++;
			}
			else
			{
				im_new_l[i][j] = 0;
				im_new_l_0C++;
			}
		}
	}
	// ==============================================================================================
	// ==============================================================================================
	//calculating bad pixels for high temp
	unsigned int im_new_h_1C = 0;
	unsigned int im_new_h_0C = 0;
	for (i = 0; i<ROW; i++)
	{
		for (j = 0; j<COL; j++)
		{
			if ((high[i][j]< (mean_high - 3.0 * std_high)) || (high[i][j]>(mean_high + 3.0 * std_high)))
			{
				im_new_h[i][j] = 1;
				im_new_h_1C++;
			}
			else
			{
				im_new_h[i][j] = 0;
				im_new_h_0C++;
			}
		}
	}

	//sprintf_s(strDebug, DEBUG_STR_LEN,"\n im_new_h_1C   %d          im_new_h_0C   %d        im_new_l_1C   %d       im_new_l_0C   %d ",im_new_h_1C,im_new_h_0C,im_new_l_1C,im_new_l_0C);
	//mPrintDebug(strDebug);
	// ==============================================================================================
	// ==============================================================================================
	//FILE *g_file;
	//FILE *o_file;
	//g_file = fopen("g.txt", "w");
	//o_file = fopen("o.txt", "w");
	//g_file = fopen("g.txt", "a");
	//o_file = fopen("o.txt", "a");
	unsigned int tmp = 0;
	for (i = 0; i<ROW; i++)
	{
		for (j = 0; j<COL; j++)
		{
			if (d[i][j]>1)
			{
				g_o_cnt++;
				g[i][j] = (((float)(havg - lavg) / ((float)d[i][j])) * 2048);
				o[i][j] = (((((float)lavg * (float)high[i][j]) - ((float)havg * (float)low[i][j])) / (float)d[i][j]) + 2048);
			}
			else
			{
				g[i][j] = 0;
				o[i][j] = 0;
			}
			//fprintf(g_file, "\n%.6f", g[i][j]);
			//fprintf(o_file, "\n%.6f", o[i][j]);
		}
	}

	//fclose(g_file);
	//fclose(o_file);
	// ==============================================================================================
	// ==============================================================================================


	cnt1 = 0;
	for (i = 0; i<ROW; i++)
	{
		for (j = 0; j<COL; j++)
		{
			if ((g[i][j] < 1536) | (g[i][j] > 2560))
			{
				cnt1++;
				g_map[i][j] = 1;
			}
			else
			{
				g_map[i][j] = 0;
			}
		}
	}
	// ==============================================================================================
	// ==============================================================================================
	cnt2 = 0;
	for (i = 0; i<ROW; i++)
	{
		for (j = 0; j<COL; j++)
		{
			if ((o[i][j] < 1536) | (o[i][j] > 2560))
			{
				cnt2++;
				o_map[i][j] = 1;
			}
			else
			{
				o_map[i][j] = 0;
			}
		}
	}

	// ==============================================================================================
	// ==============================================================================================

	for (i = 0; i<ROW; i++)
	{
		for (j = 0; j<COL; j++)
		{
			im_bpr[i][j] = ((im_new_l[i][j]) | (im_new_h[i][j]) | (g_map[i][j]) | (o_map[i][j]));
			if (im_bpr[i][j] == 1)
			{
				cnt3++;
				im_bpr_o[i][j] = 32768;
			}
			else
			{
				im_bpr_o[i][j] = 0;
			}
		}
	}

	//sprintf_s(strDebug, DEBUG_STR_LEN,"\n cnt1  %d   cnt2  %d   cnt3  %d   g_o_cnt  %d",cnt1,cnt2,cnt3,g_o_cnt);
	//mPrintDebug(strDebug);
	// ==============================================================================================
	// ==============================================================================================
	for (i = 1; i <= ROW; i++)
	{
		for (j = 1; j <= COL; j++)
		{
			rt[i][j] = (unsigned int)(((med[i][j] * g[i][j]) / 2048) + o[i][j] - 2048);
		}
	}

	// ==============================================================================================
	// ==============================================================================================
	//FILE *g_o_file;
	//FILE *o_o_file;
	//g_o_file = fopen("g_o.txt", "w");
	//o_o_file = fopen("o_o.txt", "w");
	//g_o_file = fopen("g_o.txt", "a");
	//o_o_file = fopen("o_o.txt", "a");
	k = 0;
	for (i = 0; i<ROW; i++)
	{
		for (j = 0; j<COL1; j++)
		{
			if (j<(COL-1))
			{
				g_o[i][j] = (int)(round_f(g[i][j]));
				if (o[i][j] >= 0.0)
				{
					o_o[i][j] = (int)(round_f(o[i][j]));
				}
				else
				{
					o_o[i][j] = 0;
				}

				if (im_bpr[i][j] == 1)
				{
					im_bpr_o[i][j] = 32768;
					bpr[i][j] = im_bpr_o[i][j];
				}
				else
				{
					im_bpr_o[i][j] = 0;
					bpr[i][j] = im_bpr_o[i][j];
				}
			}
			else
			{
				g_o[i][j] = 0;
				o_o[i][j] = 0;
				bpr[i][j] = 0;
			}
			//sprintf_s(strDebug, DEBUG_STR_LEN,"\n g_o[i][j] : %d   o_o[i][j] : %d    bpr[i][j] : %d ",g_o[i][j],o_o[i][j],bpr[i][j]);
			//mPrintDebug(strDebug);
			//fprintf(g_o_file, "\n%d", g_o[i][j]);
			//fprintf(o_o_file, "\n%d", o_o[i][j]);
			k++;
		}
	}
	//fclose(g_o_file);
	//fclose(o_o_file);
	// ==============================================================================================
	// ==============================================================================================
	k = 0;
	for (i = 0; i<ROW; i++)
	{
		for (j = 0; j<COL1; j++)
		{
			off_mem[i][j] = (o_o[i][j] | bpr[i][j]);
		}
	}

	k = 0;
	for (i = 0; i<ROW; i++)
	{
		for (j = 0; j<COL1; j++)
		{

			g_o_test[i][j] = (unsigned short)(g_o[i][j] & 0xFFFF);

			if (g_o_test[i][j] != g_o[i][j])
			{
				printf("\n %x %x ", g_o_test[i][j], g_o[i][j]);
			}

			o_o_test[i][j] = (unsigned short)(o_o[i][j] & 0xFFFF);

			if (o_o_test[i][j] != o_o[i][j])
			{
				printf("\n %x %x ", o_o_test[i][j], o_o[i][j]);
			}

			off_mem_test[i][j] = (unsigned short)(off_mem[i][j] & 0xFFFF);
			if (off_mem_test[i][j] != off_mem[i][j])
			{
				printf("\n %x %x ", off_mem_test[i][j], off_mem[i][j]);
			}
			k++;
		}
	}

	// ==============================================================================================
	// ==============================================================================================
	fopen_s(&wrfile_R,"g_o_test_S.hex", "wb");			//   gain
	fwrite(g_o_test,1, sizeof(g_o_test), wrfile_R);
	fclose(wrfile_R);

	fopen_s(&wrfile_G,"o_o_test_S.hex", "wb");			//   off mem
	fwrite(o_o_test, sizeof(o_o_test),1, wrfile_G);
	fclose(wrfile_G);

	fopen_s(&wrfile_O,"off_mem_test_S.hex", "wb");			//  off mem with bad pixel
	fwrite(off_mem_test, sizeof(off_mem_test),1, wrfile_O);
	fclose(wrfile_O);
	FILE *wrfile_bpr;

	fopen_s(&wrfile_bpr,"i_bpr.hex", "wb");			//  off mem with bad pixel
	fwrite(im_bpr_o, sizeof(im_bpr_o),1, wrfile_bpr);
	fclose(wrfile_bpr);

	fclose(debug_file);

	// ==============================================================================================
	// ==============================================================================================


	//=================================== final file creation ===============================
	for (i = 0; i<ROW; i++)
	{
		for (j = 0; j<COL1; j++)
		{
			final_test_tmp[i][j] = ((((unsigned int)off_mem_test[i][j]) >> 15) & 0x1);
			final_test_tmp[i][j] |= ((((unsigned int)g_o_test[i][j]) & 0xfff) << 1);
			final_test_tmp[i][j] |= ((((unsigned int)o_o_test[i][j]) & 0xffff) << 13);
			final_test_tmp[i][j] &= (0x1fffffff);

			final_test[i][j] = ((final_test_tmp[i][j] & 0xFF000000) >> 24);
			final_test[i][j] |= ((final_test_tmp[i][j] & 0x00FF0000) >> 8);
			final_test[i][j] |= ((final_test_tmp[i][j] & 0x0000FF00) << 8);
			final_test[i][j] |= ((final_test_tmp[i][j] & 0x000000FF) << 24);
		}
	}


	//========================================================================================
	char outfile_R[21];
	sprintf(outfile_R,"compensatedFrame%d.hex",*a_nPropValue);
	//fopen_s(&final_O,"final.hex", "wb");			//   final 
	fopen_s(&final_O,outfile_R, "wb");			//   final 
	fwrite(final_test, sizeof(final_test),1, final_O);
	fclose(final_O);

	*a_nPropValue = 1;
	printf("\n =========== sensor_calibration_MATLAB DONE =========== ");
	return *a_nPropValue;
}

long MiddleAPI::I2CRead(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, unsigned int msgcode,unsigned int msgsize,unsigned int a_nDevAddress, unsigned int a_nRegAddress, unsigned int *a_nRegValue)	
{	
	unsigned int axil_slave_address  = 0x4100;
	unsigned int message_code        = 2;
	unsigned int message_size        = 2;
	unsigned int device_address      = 0X92;
	unsigned int register_address    = 0x51;
	unsigned int register_address1   = 0xAA;
	unsigned int register_data       = 0;
	unsigned int val = 0;

	/************************************************I2CREAD*****************************************************/
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_RUN_TEST_I2C_MSGCODE,2);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_RUN_TEST_I2C_MSGSIZE,2);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_RUN_TEST_I2C_DEVICE_ADD,device_address);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_RUN_TEST_I2C_RESISTER_ADD,register_address1);
	/*****************************************Setmsgvalid**********************************************************/
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_RUN_TEST_I2C_MSG_VALID,1);
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_RUN_TEST_I2C_MSG_VALID,0);
	/**************************************waitforbusysignal*****************************************************/

	while(1)
	{
		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_SPPU_RUN_TEST_I2C_BUSY_CHECK,&val);
		if(val	==	0)
			break;		
	}

	*a_nRegValue = 0;

	for(unsigned int i = 1; i <= message_size;i++ )
	{
		while(1)
		{
			FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_SPPU_RUN_TEST_I2C_BUSY_CHECK1,&val); //wait for data valid signal
			if(val	==	0)
				break;
		}

		unsigned int readByte= 0 ;

		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_SPPU_RUN_TEST_READ_DATA, &readByte );

		*a_nRegValue =  (*a_nRegValue << 8) || readByte;

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_RUN_TEST_I2C_DATA_READ_ENB,1);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_RUN_TEST_I2C_DATA_READ_ENB,0);
	}
	return *a_nRegValue;
}

int MiddleAPI::DACRegAccessRead(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,SPPUDeviceType a_enDeviceType,SPPUDACRegsDefs a_enSPPUDACRegsDefs , unsigned int *a_nPropValue)           // sudeshna_reg_access  
{

	char strDebug[DEBUG_STR_LEN]	=	{'\0'};
	sprintf_s(strDebug, DEBUG_STR_LEN,"\nIn DACRegAccessRead(%d, %d, %d, %x, %x)", a_enConnectionType, a_nModuleID, a_enDeviceType, a_enSPPUDACRegsDefs, a_nPropValue);
	mPrintDebug(strDebug);

	unsigned int address  = (DAC_BASE_ADDRESS + (a_enSPPUDACRegsDefs >> 16));  
	unsigned int width    = (a_enSPPUDACRegsDefs & 0xFF);
	unsigned int bitPos   = ((a_enSPPUDACRegsDefs >> 8) & 0xFF);
	unsigned int regVal   = 0;

	// GetRegisterbyAddress(portHandle, 0, 1, regAdds, 0, &regVal, false);
	int ret = RegRead(a_enConnectionType,  a_nModuleID, a_enDeviceType, address, &regVal) ;
	regVal >>= bitPos;
	if(width < 32)
		regVal &= ((1<<width)-1);
	*a_nPropValue = regVal;


	return ret;
}

int MiddleAPI::DACRegAccessWrite(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,SPPUDeviceType a_enDeviceType,SPPUDACRegsDefs a_enSPPUDACRegsDefs, unsigned int a_nPropValuep)           // sudeshna_reg_access  
{
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};

	sprintf_s(strDebug, DEBUG_STR_LEN,"\nIn DACRegAccessWrite(%d, %d, %d, %x, %x)", a_enConnectionType, a_nModuleID, a_enDeviceType, a_enSPPUDACRegsDefs, a_nPropValuep);
	mPrintDebug(strDebug);

	unsigned int address  = (DAC_BASE_ADDRESS + (a_enSPPUDACRegsDefs >> 16));  
	unsigned int width    = (a_enSPPUDACRegsDefs & 0xFF);
	unsigned int bitPos   = ((a_enSPPUDACRegsDefs >> 8) & 0xFF);
	unsigned int regVal   = 0;
	int ret=0;

	if(width < 32)
	{
		a_nPropValuep &= (1<<width)-1;
		//RegRead(portHandle,regAdds, &regVal);
		ret =  RegRead(a_enConnectionType,  a_nModuleID, a_enDeviceType, address, &regVal) ;
		regVal &= ~(((1<<width)-1) << bitPos);    
	}
	regVal |= a_nPropValuep << bitPos;
	//RegWrite( portHandle,regAdds, regVal);
	ret = RegWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, address, regVal);

	return ret;
}

int MiddleAPI::FPGARegAccessRead(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,SPPUDeviceType a_enDeviceType,SPPUFPGARegsDefs a_enSPPUFPGARegsDefs , unsigned int *a_nPropValue)           // sudeshna_reg_access  
{
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};
	unsigned int address  = (FPGA_BASE_ADDRESS + (a_enSPPUFPGARegsDefs >> 16));  
	unsigned int width    = (a_enSPPUFPGARegsDefs & 0xFF);
	unsigned int bitPos   = ((a_enSPPUFPGARegsDefs >> 8) & 0xFF);
	unsigned int regVal   = 0;

	// GetRegisterbyAddress(portHandle, 0, 1, regAdds, 0, &regVal, false);
	int ret = RegRead(a_enConnectionType,  a_nModuleID, LFT_SPPU_DEV_FPGA, address, &regVal) ;
	regVal >>= bitPos;
	if(width < 32)
		regVal &= ((1<<width)-1);
	*a_nPropValue = regVal;

	sprintf_s(strDebug, DEBUG_STR_LEN,"\nIn FPGARegAccessRead(a_enConnectionType ::%d,a_nModuleID:: %d,a_enDeviceType::  %d,Register:: %x,PropValue:: %x)", a_enConnectionType, a_nModuleID, a_enDeviceType, a_enSPPUFPGARegsDefs, *a_nPropValue);
	mPrintDebug(strDebug);

	return ret;
}

int MiddleAPI::FPGARegAccessWrite(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,SPPUDeviceType a_enDeviceType,SPPUFPGARegsDefs a_enSPPUFPGARegsDefs, unsigned int a_nPropValue)           // sudeshna_reg_access  

{

	char strDebug[DEBUG_STR_LEN]	=	{'\0'};

	sprintf_s(strDebug, DEBUG_STR_LEN,"\nIn FPGARegAccessWrite(SPPUHostConnectionType ::%d, a_nModuleID :: %d,a_enDeviceType:: %d,Register:: %x,PropValue %x)", a_enConnectionType, a_nModuleID, a_enDeviceType, a_enSPPUFPGARegsDefs, a_nPropValue);
	mPrintDebug(strDebug);

	unsigned int address  = (FPGA_BASE_ADDRESS + (a_enSPPUFPGARegsDefs >> 16));  
	unsigned int width    = (a_enSPPUFPGARegsDefs & 0xFF);
	unsigned int bitPos   = ((a_enSPPUFPGARegsDefs >> 8) & 0xFF);
	unsigned int regVal   = 0;
	int ret=0;

	if(width < 32)
	{
		a_nPropValue &= (1<<width)-1;
		//RegRead(portHandle,regAdds, &regVal);
		ret =  RegRead(a_enConnectionType,  a_nModuleID, LFT_SPPU_DEV_FPGA, address, &regVal) ;
		regVal &= ~(((1<<width)-1) << bitPos);    
	}
	regVal |= a_nPropValue << bitPos;
	//RegWrite( portHandle,regAdds, regVal);
	ret = RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, address, regVal);

	return ret;
}

int MiddleAPI::LMKRegAccessRead(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,SPPUDeviceType a_enDeviceType,SPPULMKRegsDefs a_enSPPULMKRegsDefs , unsigned int *a_nPropValue)           // sudeshna_reg_access  
{
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};

	sprintf_s(strDebug, DEBUG_STR_LEN,"\nIn DACRegAccessRead(%d, %d, %d, %x, %x)", a_enConnectionType, a_nModuleID, a_enDeviceType, a_enSPPULMKRegsDefs, a_nPropValue);
	mPrintDebug(strDebug);

	unsigned int address  = (LMK_BASE_ADDRESS + (a_enSPPULMKRegsDefs >> 16));  
	unsigned int width    = (a_enSPPULMKRegsDefs & 0xFF);
	unsigned int bitPos   = ((a_enSPPULMKRegsDefs >> 8) & 0xFF);
	unsigned int regVal   = 0;

	// GetRegisterbyAddress(portHandle, 0, 1, regAdds, 0, &regVal, false);
	int ret = RegRead(a_enConnectionType,  a_nModuleID, LFT_SPPU_DEV_LMK04806, address, &regVal) ;
	regVal >>= bitPos;
	if(width < 32)
		regVal &= ((1<<width)-1);
	*a_nPropValue = regVal;


	return ret;
}

int MiddleAPI::LMKRegAccessWrite(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,SPPUDeviceType a_enDeviceType,SPPULMKRegsDefs a_enSPPULMKRegsDefs, unsigned int a_nPropValue)           // sudeshna_reg_access  
{

	char strDebug[DEBUG_STR_LEN]	=	{'\0'};

	sprintf_s(strDebug, DEBUG_STR_LEN,"\nIn LMKRegAccessWrite(%d, %d, %d, %x, %x)", a_enConnectionType, a_nModuleID, a_enDeviceType, a_enSPPULMKRegsDefs, a_nPropValue);
	mPrintDebug(strDebug);

	unsigned int address  = (LMK_BASE_ADDRESS + (a_enSPPULMKRegsDefs >> 16));  
	unsigned int width    = (a_enSPPULMKRegsDefs & 0xFF);
	unsigned int bitPos   = ((a_enSPPULMKRegsDefs >> 8) & 0xFF);
	unsigned int regVal   = 0;
	int ret=0;

	if(width < 32)
	{
		a_nPropValue &= (1<<width)-1;
		//RegRead(portHandle,regAdds, &regVal);
		ret =  RegRead(a_enConnectionType,  a_nModuleID, LFT_SPPU_DEV_LMK04806, address, &regVal) ;
		regVal &= ~(((1<<width)-1) << bitPos);    
	}
	regVal |= a_nPropValue << bitPos;
	//RegWrite( portHandle,regAdds, regVal);
	ret = RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_LMK04806, address, regVal);

	return ret;
}

long MiddleAPI::SetFPGAProperty(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,SPPUFPGAProp a_enFPGAProp, unsigned int a_nPropValue)
{
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};
	sprintf_s(strDebug, DEBUG_STR_LEN,"\nIn SetFPGAProperty(%d, %d, %d, %d, %d)", a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA, a_enFPGAProp, a_nPropValue);
	mPrintDebug(strDebug);
	unsigned int rdval_rf1 = 0;
	unsigned int rdval_rf2 = 0;
	unsigned int rdval_if = 0;
	unsigned int val = 0;
	float read_value = 0.150;
	switch(a_enFPGAProp)
	{
		////////////////////////////////////////////////////////////////////// ISTRAC //////////////////////////////////////////

	case LFT_FPGA_PLAYBACK_TRG_PulseWdth :
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA, ISTRAC_trigger_pulse_width, a_nPropValue);
		break;
	case LFT_FPGA_PLAYBACK_TRG_PulseGap :
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, ISTRAC_trigger_pulse_gap, a_nPropValue);//dac_data_count_per_trig
		break;
	case LFT_FPGA_PLAYBACK_DataCount_per_Trg :
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,ISTRAC_dac_data_count_per_trig, a_nPropValue);
		break;
	case LFT_FPGA_PLAYBACK_Trgr_SRC:
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, ISTRAC_trigger_source_pb, a_nPropValue);
		break;
	case LFT_FPGA_trgr_start:
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, ISTRAC_sw_trigger_start_pulse_pb, 1);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,ISTRAC_sw_trigger_start_pulse_pb, 0);
		break;
	case LFT_FPGA_trgr_stop:
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, ISTRAC_sw_trigger_stop_pulse_pb, 1);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,ISTRAC_sw_trigger_stop_pulse_pb, 0);
		break;
	case LFT_FPGA_Trg_Mode:
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, ISTRAC_PLBK_COFIG_REG1_TM, a_nPropValue);
		break;
	case LFT_FPGA_PlyBK_SW_TRGR_ENB:
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, ISTRAC_PLYBK_COFIG_REG1_SW_TRIG_EN, a_nPropValue);
		break;
	case LFT_FPGA_trgr_PlyBack_Strt_stop :
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,ISTRAC_reading_from_DAC, a_nPropValue);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,ISTRAC_DDR_RESET,1);
		Sleep(1);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,ISTRAC_DDR_RESET,0);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,ISTRAC_AXI_RESET,1);
		Sleep(1);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,ISTRAC_AXI_RESET,0);
		break;
		case LFT_FPGA_trgr_PlyBack_SSD_Strt_stop :
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,ISTRAC_reading_from_DAC, a_nPropValue);		
		break;
	case LFT_FPGA_trgr_PlyBack_Strt :
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,ISTRAC_reading_from_DAC, a_nPropValue);

		break;
	case LFT_FPGA_Memory_Sel:
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, ISTRAC_PlayBAck_Memory_Slect, a_nPropValue);
		break;
	case LFT_FPGA_PROP_ISTARC_LVDS:
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_VAB_StartCapture, a_nPropValue);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_VAB_StartCapture, a_nPropValue);
		break;
	case LFT_FPGA_PROP_STRMN_strt:
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_FPGA_STRMN_Strt, 1);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_FPGA_STRMN_Strt, 0);
		break;
	case LFT_FPGA_PROP_STRMN_stop:
		mPrintDebug("case ::  Streming stop");
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_FPGA_STRMN_Stop, 1);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_FPGA_STRMN_Stop, 0);
		break;
	case LFT_FPGA_PROP_CH_sel:
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_FPGA_STRMN_Ch_Sl, a_nPropValue);

		break;
	case LFT_FPGA_PROP_window_sz:
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_FPGA_window_Size, a_nPropValue);

		break;

	case LFT_FPGA_PROP_CNT_ENB:
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_FPGA_STRMN_Debug_Cnt_Enamble, 1);

		break;

	case LFT_FPGA_PROP_VA_Start_Capture:

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_VAB_StartCapture, a_nPropValue);
		break;

	case LFT_FPGA_PROP_VA_Stop_capture:

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_VAB_StopCapture, a_nPropValue);
		break;
	case LFT_FPGA_PROP_VA_Take_SnapShot:

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_VAB_TakeSnapShot, a_nPropValue);
		break;
	case LFT_FPGA_PROP_VA_Memory_Erase :
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_VAB_MemErase, a_nPropValue);
		break;
	case LFT_FPGA_PROP_VA_GetTime_Reg:

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_VAB_GetTime, a_nPropValue);
		break;
	case LFT_FPGA_PROP_VA_SetTime_Reg:

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_VAB_SetTime, a_nPropValue);
		break;
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		///////////////////////////////////////////////// Video Enhancement ////////////////////////////////////////////////////////////////////////////

	case LFT_FPGA_PROP_VE_Video_Algo_Selction:

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_VE_VideoEnhanc_AlgoSelect, a_nPropValue);
		break;
	case LFT_FPGA_PROP_VE_Contrast_Algo_Selection:

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_VE_ContrastEnhanc_AlgoSelect, a_nPropValue);
		break;
	case LFT_FPGA_PROP_VE_PhotoMetric_Variance:

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_VE_PhotoMetric_Variance, a_nPropValue);
		break;
	case LFT_FPGA_PROP_VE_GeoMetric_Variance :
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_VE_GeometricVariance, a_nPropValue);
		break;
	case LFT_FPGA_PROP_VE_Gain_Offset:

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_VE_GainOffeset, a_nPropValue);
		break;
	case LFT_FPGA_PROP_VE_SDGain_Limit:

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_VE_SD_Gain_Limit, a_nPropValue);
		break;
	case LFT_FPGA_PROP_VE_SD_Mean:

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_VE_SD_Mean, a_nPropValue);
		break;
	case LFT_FPGA_PROP_VE_SmallScale_Weight:

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_VE_Small_Scale_Weight, a_nPropValue);
		break;
	case LFT_FPGA_PROP_VE_LargeScale_Weight:

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_VE_Large_Scale_Weight, a_nPropValue);
		break;
	case LFT_FPGA_PROP_VE_ColorRestoration_Alpha:

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_VE_Color_Restoration_Alpha, a_nPropValue);
		break;
	case LFT_FPGA_PROP_VE_ColorRestoration_Beta:

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_VE_Color_Restoration_Beta, a_nPropValue);
		break;
	case LFT_FPGA_PROP_VE_Gain_Comp:

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_VE_Color_Gain_Compen, a_nPropValue);
		break;
	case LFT_FPGA_PROP_VE_OffSet_Comp:

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_VE_Color_Offset_Compen, a_nPropValue);
		break;
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		///////////////////////////////// Video Stabilization ///////////////////////////////////////////////////////////////////////////////

	case LFT_FPGA_PROP_VS_Input_VideoType:

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_VS_Input_Video_Type, a_nPropValue);
		break;
	case LFT_FPGA_PROP_VS_Enable_Stablization:

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_VS_Enable_Stablization, a_nPropValue);
		break;
	case LFT_FPGA_PROP_VS_X1_Cordi:

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_VS_Input_X1_Coordinate, a_nPropValue);
		break;
	case LFT_FPGA_PROP_VS_Y1_Cordi:

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_VS_Input_Y1_Coordinate, a_nPropValue);
		break;
	case LFT_FPGA_PROP_VS_X2_Cordi:

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_VS_Input_X2_Coordinate, a_nPropValue);
		break;
	case LFT_FPGA_PROP_VS_Y2_Cordi:

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_VS_Input_Y2_Coordinate, a_nPropValue);
		break;
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		///////////////////////////////// Video Object Tracking  ///////////////////////////////////////////////////////////////////////////////

	case LFT_FPGA_PROP_VO_Input_VideoType:

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_VS_Input_Video_Type, a_nPropValue);
		break;
	case LFT_FPGA_PROP_VO_Enable_Tracking:

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_VS_Enable_Stablization, a_nPropValue);
		break;
	case LFT_FPGA_PROP_VO_Algo_Type:

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_VS_Input_X1_Coordinate, a_nPropValue);
		break;
	case LFT_FPGA_PROP_VO_X1_Cordi:

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_VS_Input_Y1_Coordinate, a_nPropValue);
		break;
	case LFT_FPGA_PROP_VO_Y1_Cordi:

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_VS_Input_X2_Coordinate, a_nPropValue);
		break;
	case LFT_FPGA_PROP_VO_X2_Cordi:

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_VS_Input_Y2_Coordinate, a_nPropValue);
		break;
	case LFT_FPGA_PROP_VO_Y2_Cordi:

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_VS_Input_Y2_Coordinate, a_nPropValue);
		break;
	case LFT_FPGA_PROP_SIC_SensorIntigration:

		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_senSorIntigration_TIme, a_nPropValue);
		break;
	case LFT_FPGA_PROP_SIC_CalibratedImage_OnOff:
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_CalibratedImage_OnOff, a_nPropValue);
		break;
	case LFT_FPGA_PROP_SIC_CalibratedImage_Pulse:
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_CalibratedImage_Pulse, a_nPropValue);
		break;
	case LFT_FPGA_PROP_SIC_Calibratedresult_Block :
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_puts_select_sector,a_nPropValue);
		break;
	case	LFT_FPGA_PROP_SIC_DeviceReset:
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_Device_Reset,a_nPropValue);
		break;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		// __FC__ Adding Cenroid_appplication code, __HP__ , 24 May 2016.
	case LFT_FPGA_PROP_Centroid_Frame_RateConfig:
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_DDR_Frame_RateConfig, a_nPropValue);
		break;

	case LFT_FPGA_PROP_Cam_Frame_Rate:
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_Cam_Frame_Rate, a_nPropValue);
		break;
	case LFT_FPGA_PROP_Threshold_Vlaue:
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_Threshold_Vlaue, a_nPropValue);
		break;
	case LFT_FPGA_PROP_DAC_Select:
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_DAC_Output_Range_Control, a_nPropValue);
		break;
	case LFT_FPGA_PROP_Stream_Enable:
		/// int global variable for frame count and timer .
		mPrintDebug("********************* Stream Enable ***********************");
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_Stream_Enable, a_nPropValue);
		mPrintDebug("********************* Stream Enable end ***********************");
		break;
	case LFT_FPGA_PROP_Start_Recording:
		{
			unsigned int fps = 0x0, FrameSize = 0x0;
			unsigned int numVideoBytesToRead = 0x0;
			unsigned int capture_done = 0x0;
			//Get current frame size.

			FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_Cam_Frame_Rate, &FrameSize);

			//Calculate actual Frame Size in bytes.
			switch(FrameSize)
			{
			case 0:
				FrameSize = 0x10000;				//256*256
				fps = 2200;
				break;

			case 1:
				FrameSize = 0x1000;					//64*64
				fps = 5000;
				break;

			case 2:
				FrameSize = 0x4000;					//128*128
				fps = 5000;
				break;

			case 3:
				FrameSize = 0x1000;			//This case is for testing purpose. Since we can not test at 256x256 without actual camera, so using 64x64 frame size settings.
				fps = 5000;
				break;
			}

			//numVideoBytesToRead = FrameSize * fps * 2;		//2 for 2 second of video.
			numVideoBytesToRead = CENTROID_DDR_SIZE;
			if(a_nPropValue >= CENTROID_DDR_SIZE)
			{
				a_nPropValue =CENTROID_DDR_SIZE;
			}
			numVideoBytesToRead = a_nPropValue ;//*FrameSize;
			//Set number Video bytes available to read.
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_DDR_Rd_WR_end_Address, numVideoBytesToRead);

			//centroid_calculation_disable
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_Stream_Enable, 0x0);

			//ddr_write_data_pulse
			mPrintDebug("Waiting for DDR write DOne ");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_Ddr_Start_Record, 0x1);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_Ddr_Start_Record, 0x0);	
			do
			{
				FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_Capture_Done, &capture_done);
			}while(capture_done == 0);

			mPrintDebug("write done complete ");

			return 0;
		}


		break;
	case LFT_FPGA_PROP_Retrive_Recording:
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_Ddr_Start_Retrive, a_nPropValue);
		break;
	case LFT_FPGA_PROP_Centroid_Design_Reset:
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_Stream_Design_Reset, 0x1);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_Stream_Design_Reset, 0x0);
		break ;
	case LFT_FPGA_PROP_Stream_FIFO_Reset:
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_Stream_FIFO_Reset, 0x1);
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_CENTROIED_Stream_FIFO_Reset, 0x0);
		break;

		//End All Fast_Centroid settings.

	case LFT_SPPU_FPGA_PROP_OP_MODE:
		mPrintDebug("**************************Set OP_MODE**************************");
		//RF Mode: 0,  IF Mode:1
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_operation_Mode_RF_IF, a_nPropValue);
		//InitFPGA(a_enConnectionType, a_nModuleID);
		break;

	case LFT_SPPU_FPGA_PROP_AMPLITUDE_RF_channel_1:
		mPrintDebug("**************************Set AMPLITUDE_RF_channel_1**************************");

		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_VERSION_REG, &rdval_rf1);
		if(rdval_rf1 == 0x01)
		{
			mPrintDebug("**************************Set AMPLITUDE_FOR_BOARD_1**************************");
			switch((SPPUFPGAPropAmplitude)a_nPropValue)
			{

			case LFT_SPPU_FPGA_PROP_MINUS_10:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 0, 0x45);
				break;

			case LFT_SPPU_FPGA_PROP_MINUS_9:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 0, 0x41);
				break;
			case LFT_SPPU_FPGA_PROP_MINUS_8:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 0, 0x3d);

				break;
			case LFT_SPPU_FPGA_PROP_MINUS_7:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 0, 0x39);

				break;
			case LFT_SPPU_FPGA_PROP_MINUS_6:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 0, 0x35);

				break;
			case LFT_SPPU_FPGA_PROP_MINUS_5:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 0, 0x30);

				break;
			case LFT_SPPU_FPGA_PROP_MINUS_4:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 0, 0x2d);

				break;
			case LFT_SPPU_FPGA_PROP_MINUS_3:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 0, 0x29);

				break;
			case LFT_SPPU_FPGA_PROP_MINUS_2:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 0, 0x25);

				break;
			case LFT_SPPU_FPGA_PROP_MINUS_1:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 0, 0x21);

				break;
			case LFT_SPPU_FPGA_PROP_0:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 0, 0x1d);

				break;
			case LFT_SPPU_FPGA_PROP_1:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 0, 0x18);

				break;
			case LFT_SPPU_FPGA_PROP_2:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 0, 0x14);

				break;
			case LFT_SPPU_FPGA_PROP_3:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 0, 0x10);

				break;
			case LFT_SPPU_FPGA_PROP_4:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 0, 0xc);

				break;
			case LFT_SPPU_FPGA_PROP_5:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 0, 0x8);
				break;
			}

		}
		else if(rdval_rf1 == 2)
		{
			mPrintDebug("**************************Set AMPLITUDE_FOR_BOARD_2**************************");
			switch((SPPUFPGAPropAmplitude)a_nPropValue)
			{
			case LFT_SPPU_FPGA_PROP_MINUS_10:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 0, 0x45);
				break;

			case LFT_SPPU_FPGA_PROP_MINUS_9:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 0, 0x40);
				break;
			case LFT_SPPU_FPGA_PROP_MINUS_8:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 0, 0x3d);

				break;
			case LFT_SPPU_FPGA_PROP_MINUS_7:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 0, 0x38);

				break;
			case LFT_SPPU_FPGA_PROP_MINUS_6:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 0, 0x34);

				break;
			case LFT_SPPU_FPGA_PROP_MINUS_5:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 0, 0x30);

				break;
			case LFT_SPPU_FPGA_PROP_MINUS_4:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 0, 0x2C);

				break;
			case LFT_SPPU_FPGA_PROP_MINUS_3:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 0, 0x27);

				break;
			case LFT_SPPU_FPGA_PROP_MINUS_2:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 0, 0x24);

				break;
			case LFT_SPPU_FPGA_PROP_MINUS_1:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 0, 0x20);

				break;
			case LFT_SPPU_FPGA_PROP_0:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 0, 0x1B);

				break;
			case LFT_SPPU_FPGA_PROP_1:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 0, 0x17);

				break;
			case LFT_SPPU_FPGA_PROP_2:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 0, 0x30);

				break;
			case LFT_SPPU_FPGA_PROP_3:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 0, 0x0F);

				break;
			case LFT_SPPU_FPGA_PROP_4:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 0, 0x0B);

				break;
			case LFT_SPPU_FPGA_PROP_5:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 0, 0x7);
				break;

			case LFT_SPPU_FPGA_PROP_6:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 0, 0x3);
				break;

			}

		}
		break;

	case LFT_SPPU_FPGA_PROP_AMPLITUDE_RF_channel_2:

		mPrintDebug("**************************Set AMPLITUDE_RF_channel_2**************************");

		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_VERSION_REG, &rdval_rf2);
		if(rdval_rf2 == 0x01)
		{
			mPrintDebug("**************************Set AMPLITUDE_FOR_BOARD_1**************************");
			switch((SPPUFPGAPropAmplitude)a_nPropValue)
			{

			case LFT_SPPU_FPGA_PROP_MINUS_10:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x45);
				break;
			case LFT_SPPU_FPGA_PROP_MINUS_9:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x40);
				break;
			case LFT_SPPU_FPGA_PROP_MINUS_8:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x3c);
				break;
			case LFT_SPPU_FPGA_PROP_MINUS_7:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x38);
				break;
			case LFT_SPPU_FPGA_PROP_MINUS_6:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x35);
				break;
			case LFT_SPPU_FPGA_PROP_MINUS_5:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x30);
				break;
			case LFT_SPPU_FPGA_PROP_MINUS_4:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x2d);
				break;
			case LFT_SPPU_FPGA_PROP_MINUS_3:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x29);
				break;
			case LFT_SPPU_FPGA_PROP_MINUS_2:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x25);
				break;
			case LFT_SPPU_FPGA_PROP_MINUS_1:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x21);
				break;
			case LFT_SPPU_FPGA_PROP_0:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x1d);
				break;
			case LFT_SPPU_FPGA_PROP_1:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x18);
				break;
			case LFT_SPPU_FPGA_PROP_2:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x14);
				break;
			case LFT_SPPU_FPGA_PROP_3:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x10);
				break;
			case LFT_SPPU_FPGA_PROP_4:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0xc);
				break;
			case LFT_SPPU_FPGA_PROP_5:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x8);
				break;

			}
		}
		else if(rdval_rf2 == 0x02)
		{
			mPrintDebug("**************************Set AMPLITUDE_FOR_BOARD_2**************************");
			switch((SPPUFPGAPropAmplitude)a_nPropValue)
			{

			case LFT_SPPU_FPGA_PROP_MINUS_25:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x7F);
				break;
			case LFT_SPPU_FPGA_PROP_MINUS_24:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x7C);
				break;
			case LFT_SPPU_FPGA_PROP_MINUS_23:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x78);
				break;
			case LFT_SPPU_FPGA_PROP_MINUS_22:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x74);
				break;
			case LFT_SPPU_FPGA_PROP_MINUS_21:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x70);
				break;
			case LFT_SPPU_FPGA_PROP_MINUS_20:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x6C);
				break;
			case LFT_SPPU_FPGA_PROP_MINUS_19:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x68);
				break;
			case LFT_SPPU_FPGA_PROP_MINUS_18:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x64);
				break;
			case LFT_SPPU_FPGA_PROP_MINUS_17:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x60);
				break;
			case LFT_SPPU_FPGA_PROP_MINUS_16:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x5C);
				break;
			case LFT_SPPU_FPGA_PROP_MINUS_15:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x58);
				break;
			case LFT_SPPU_FPGA_PROP_MINUS_14:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x54);
				break;
			case LFT_SPPU_FPGA_PROP_MINUS_13:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x50);
				break;
			case LFT_SPPU_FPGA_PROP_MINUS_12:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x4C);
				break;
			case LFT_SPPU_FPGA_PROP_MINUS_11:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x48);
				break;
			case LFT_SPPU_FPGA_PROP_MINUS_10:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x44);
				break;
			case LFT_SPPU_FPGA_PROP_MINUS_9:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x3F);
				break;
			case LFT_SPPU_FPGA_PROP_MINUS_8:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x3B);
				break;
			case LFT_SPPU_FPGA_PROP_MINUS_7:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x37);
				break;
			case LFT_SPPU_FPGA_PROP_MINUS_6:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x33);
				break;
			case LFT_SPPU_FPGA_PROP_MINUS_5:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x2F);
				break;
			case LFT_SPPU_FPGA_PROP_MINUS_4:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x2B);
				break;
			case LFT_SPPU_FPGA_PROP_MINUS_3:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x27);
				break;
			case LFT_SPPU_FPGA_PROP_MINUS_2:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x23);
				break;
			case LFT_SPPU_FPGA_PROP_MINUS_1:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x1F);
				break;
			case LFT_SPPU_FPGA_PROP_0:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x1B);
				break;
			case LFT_SPPU_FPGA_PROP_1:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x17);
				break;
			case LFT_SPPU_FPGA_PROP_2:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x13);
				break;
			case LFT_SPPU_FPGA_PROP_3:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x0F);
				break;
			case LFT_SPPU_FPGA_PROP_4:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x0B);
				break;
			case LFT_SPPU_FPGA_PROP_5:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x07);
				break;
			case LFT_SPPU_FPGA_PROP_6:
				RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, 0x03);
				break;
			}

		}
		break;


	case LFT_SPPU_FPGA_PROP_AMPLITUDE_IF:
		//__CHANGE__
		//FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_VERSION_REG, 0x00);
		//FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_VERSION_REG, 0x01);
		mPrintDebug("*********************************Set AMPLITUDE_IF************************************");
		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_VERSION_REG, &rdval_if);
		if(rdval_if == 0x01)
		{
			mPrintDebug("**************************Set AMPLITUDE_IF_BOARD1**************************");
			switch((SPPUFPGAPropAmplitude)a_nPropValue)
			{
			case LFT_SPPU_FPGA_PROP_IF_MINUS_27:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0X0);

			case LFT_SPPU_FPGA_PROP_IF_MINUS_26:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0X0);

				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_25:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0X0);

				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_24:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0X0);

				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_23:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0x1);

				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_22:

				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0x1);
				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_21:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0x1);
				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_20:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0x1);

				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_19:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0x1);

				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_18:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0x2);

				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_17:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0x2);

				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_16:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0x2);

				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_15:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0x3);

				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_14:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0x3);

				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_13:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0x4);

				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_12:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0x4);
				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_11:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0x5);

				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_10:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0x5);
				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_9:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0x6);

				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_8:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0x7);

				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_7:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0x8);

				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_6:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0x9);

				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_5:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0XB);

				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_4:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0XC);

				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_3:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0XE);

				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_2:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0XF);

				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_1:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0XF);
				break;
			case LFT_SPPU_FPGA_PROP_IF_0:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0XF);

				break;
			}
		}
		else if(rdval_if == 0x02)
		{

			mPrintDebug("**************************Set AMPLITUDE_IF_BOARD2**************************");
			switch((SPPUFPGAPropAmplitude)a_nPropValue)
			{
			case LFT_SPPU_FPGA_PROP_IF_MINUS_27:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0X0);

			case LFT_SPPU_FPGA_PROP_IF_MINUS_26:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0X0);

				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_25:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0X0);

				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_24:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0X0);

				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_23:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0x1);

				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_22:

				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0x1);
				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_21:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0x1);
				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_20:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0x1);

				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_19:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0x2);

				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_18:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0x2);

				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_17:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0x2);

				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_16:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0x3);

				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_15:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0x3);

				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_14:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0x3);

				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_13:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0x4);

				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_12:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0x4);
				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_11:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0x5);

				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_10:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0x6);
				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_9:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0x7);

				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_8:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0x8);

				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_7:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0x9);

				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_6:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0xA);

				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_5:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0XC);

				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_4:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0XD);

				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_3:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0XF);

				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_2:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0XF);

				break;
			case LFT_SPPU_FPGA_PROP_IF_MINUS_1:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0XF);
				break;
			case LFT_SPPU_FPGA_PROP_IF_0:
				DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_GAIN_coarse_dac_gain ,0XF);
				break;
			}
		}
		break;

	case LFT_SPPU_FPGA_PROP_INTRPLTN:
		mPrintDebug("**************************Set interpolation**************************");
		switch((SPPUFPGAPropInterpolation) a_nPropValue)
		{
		case LFT_SPPU_FPGA_PROP_INTRPLTN_ZOOM_2 :
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DAC_SETUP_INTERPOLATION, 0);
			DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_digital_filter_interpolation_interp,1);
			DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_digital_filter_interpolation_interp,1);
			DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_digital_filter_interpolation_interp,1);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DAC_SETUP_STEP_PULSE, 1);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DAC_SETUP_STEP_PULSE, 0);
			break;

		case LFT_SPPU_FPGA_PROP_INTRPLTN_ZOOM_4:
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DAC_SETUP_INTERPOLATION, 1);
			DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_digital_filter_interpolation_interp,2);
			DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_digital_filter_interpolation_interp,2);
			DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_digital_filter_interpolation_interp,2);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DAC_SETUP_STEP_PULSE, 1);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DAC_SETUP_STEP_PULSE, 0);
			break;

		case LFT_SPPU_FPGA_PROP_INTRPLTN_ZOOM_8:
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DAC_SETUP_INTERPOLATION, 2);
			DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_digital_filter_interpolation_interp,4);
			DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_digital_filter_interpolation_interp,4);
			DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_digital_filter_interpolation_interp,4);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DAC_SETUP_STEP_PULSE, 1);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DAC_SETUP_STEP_PULSE, 0);// chenge on 8th sep dileep sir
			break;
		}
		break;

	case LFT_SPPU_FPGA_PROP_PULSE_WIDTH_channel_1:
		mPrintDebug("**************************Set PULSE_WIDTH_channel_1**************************");
		//FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DAC_SETUP_PULSEWIDTH_DAC0, a_nPropValue/4);
		//__HP__6
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DAC_SETUP_PULSEWIDTH_DAC0, a_nPropValue);

		break;

	case LFT_SPPU_FPGA_PROP_PULSE_WIDTH_channel_2:

		mPrintDebug("**************************Set PULSE_WIDTH_channel_2**************************");
		//FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DAC_SETUP_PULSEWIDTH_DAC1, a_nPropValue/4);
		//__HP__6
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DAC_SETUP_PULSEWIDTH_DAC1, a_nPropValue);

		break;

	case LFT_SPPU_FPGA_PROP_SIGNAL_DELAY_channel_1: // modified on 19th aug


		mPrintDebug("**************************Set SIGNAL_DELAY_channel_1**************************");
		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DAC_SETUP_INTERPOLATION, &val);
		if(val == 0)
		{
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_SIGNAL_DELAY_DAC0, unsigned int(a_nPropValue * read_value));
			sprintf_s(strDebug, DEBUG_STR_LEN,"\nIn value( %x)", read_value);
			mPrintDebug(strDebug);
			sprintf_s(strDebug, DEBUG_STR_LEN,"\nIn value2( %f)", read_value);
			mPrintDebug(strDebug);
		}
		else if(val == 1)
		{
			read_value = 0.075;
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_SIGNAL_DELAY_DAC0, unsigned int(a_nPropValue * read_value));
			sprintf_s(strDebug, DEBUG_STR_LEN,"\nIn value1( %x)", a_nPropValue);
			mPrintDebug(strDebug);
			sprintf_s(strDebug, DEBUG_STR_LEN,"\nIn value2( %f)", read_value);
			mPrintDebug(strDebug);

		}
		else if(val == 2)
		{
			read_value = 0.0375;
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_SIGNAL_DELAY_DAC0, unsigned int(a_nPropValue * read_value));
			sprintf_s(strDebug, DEBUG_STR_LEN,"\nIn value1( %x)", a_nPropValue);
			mPrintDebug(strDebug);
			sprintf_s(strDebug, DEBUG_STR_LEN,"\nIn value2( %f)", read_value);
			mPrintDebug(strDebug);
		}
		break;

	case LFT_SPPU_FPGA_PROP_SIGNAL_DELAY_channel_2: // modified on 31st sep


		mPrintDebug("**************************Set SIGNAL_DELAY_channel_2**************************");
		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DAC_SETUP_INTERPOLATION, &val);
		if(val == 0)
		{
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_SIGNAL_DELAY_DAC1, unsigned int(a_nPropValue * read_value));
			sprintf_s(strDebug, DEBUG_STR_LEN,"\nIn value( %x)", read_value);
			mPrintDebug(strDebug);
			sprintf_s(strDebug, DEBUG_STR_LEN,"\nIn value2( %f)", read_value);
			mPrintDebug(strDebug);
		}
		else if(val == 1)
		{
			read_value = 0.075;
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_SIGNAL_DELAY_DAC1, unsigned int(a_nPropValue * read_value));
			sprintf_s(strDebug, DEBUG_STR_LEN,"\nIn value1( %x)", a_nPropValue);
			mPrintDebug(strDebug);
			sprintf_s(strDebug, DEBUG_STR_LEN,"\nIn value2( %f)", read_value);
			mPrintDebug(strDebug);

		}
		else if(val == 2)
		{
			read_value = 0.0375;
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_SIGNAL_DELAY_DAC1, unsigned int(a_nPropValue * read_value));
			sprintf_s(strDebug, DEBUG_STR_LEN,"\nIn value1( %x)", a_nPropValue);
			mPrintDebug(strDebug);
			sprintf_s(strDebug, DEBUG_STR_LEN,"\nIn value2( %f)", read_value);
			mPrintDebug(strDebug);
		}

		//FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_SIGNAL_DELAY_DAC1, a_nPropValue);

		break;


	case LFT_SPPU_FPGA_PROP_MAX_OP_TEMP: // modified on 20th aug

		mPrintDebug("**************************Set MAX_OP_TEMP**************************");
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_MAX_OP_TEMP, a_nPropValue);
		//FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_SIGNAL_DELAY_DAC1, a_nPropValue);

		break;

	case LFT_SPPU_FPGA_PROP_TRGGR_PRI:

		mPrintDebug("**************************Set TRGGR_PRI**************************");
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_TRIGGER_PRI, a_nPropValue/4);

		break;

	case LFT_SPPU_FPGA_PROP_TRGGR_WIDTH:
		mPrintDebug("**************************Set TRGGR_WIDTH**************************");
		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_TRIGGER_WIDTH, a_nPropValue);

		break;



	case LFT_SPPU_FPGA_PROP_IQ_SAMP_RATE:

		//integer value not to be typecaste
		// To do : Register Access Calls

		break;


	case LFT_SPPU_FPGA_PROP_NCO_OUT_FREQ:    // modified on 19th aug
		mPrintDebug("**************************Set NCO_OUT_FREQ**************************");
		//Apply setting on GUI Apply
		DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_mixer_ena,1);
		DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_NCO_ena,1);
		DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_NCO_START,0XF0F0); // MODIFIED ON 8TH SEP D
		//DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_mixer_ena,1);  // modified on 31st aug
		DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_NCO_DDS_AB_phase_add,0X6666);
		DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_NCO_DDS_AB_phase_add1,0X2666);
		DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_NCO_ENABLE_STATE,0x8180);
		DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_NCO_ENABLE_STATE,0x8182 );
		DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_NCO_ENABLE_STATE,0x8180);


		break;

	case LFT_SPPU_FPGA_PROP_CLOCK_SOURCE:

		switch((SPPUFPGAClockSource) a_nPropValue)
		{
		case LFT_SPPU_FPGA_PROP_CLOCK_SOURCE_INTERNAL:
			// To do : Register Access Calls
			break;

		case LFT_SPPU_FPGA_PROP_CLOCK_SOURCE_EXTERNAL:
			// To do : Register Access Calls
			break;
		}

	}

	return -100;

}

long MiddleAPI::GetFPGAProperty(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUFPGAProp a_enFPGAProp, unsigned int *a_nPropValue)
{
	long FPGAOutClockFrequency	=	0;
	long FPGADACDataClockFrequency	=	0;
	unsigned int a_enfpgamode = 0; 
	switch(a_enFPGAProp)
	{
	case LFT_SPPU_FPGA_PROP_OP_MODE:
		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_operation_Mode_RF_IF, a_nPropValue);
		break;
		//	case LFT_SPPU_FPGA_PROP_AMPLITUDE:

		//register access calls

		break;
	case LFT_FPGA_PROP_Centroid_BitFileTypeCheck:
		FPGARegAccessRead(a_enConnectionType  , a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_BitFile_Check, a_nPropValue); 
		break;
	case LFT_SPPU_FPGA_PROP_INTRPLTN:

		//register access calls

		break;

	case LFT_SPPU_FPGA_PROP_PULSE_WIDTH_channel_1:

		//register access calls

		break;

	case LFT_SPPU_FPGA_PROP_TRGGR_PRI:

		//register access calls

		break;

	case LFT_SPPU_FPGA_PROP_TRGGR_WIDTH:

		//register access calls

		break;

	case LFT_SPPU_FPGA_PROP_IQ_SAMP_RATE:

		//register access calls

		break;

	case LFT_SPPU_FPGA_PROP_NCO_OUT_FREQ:
		//register access calls

		break;

	case LFT_SPPU_FPGA_PROP_CLOCK_SOURCE:

		//register access calls

		break;

	case LFT_SPPU_FPGA_PROP_DATA_CLK:

		UpdateFPGADACDataClockFrequency(a_enConnectionType, a_nModuleID, a_nPropValue);
		break;

	case LFT_SPPU_FPGA_PROP_FPGA_OUT_CLK:

		UpdateFPGAOutClockFrequency(a_enConnectionType, a_nModuleID,  a_nPropValue);
		break;



	case LFT_SPPU_FPGA_PROP_PLL_LOCK_STS:

		FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_clock_Setup_PLL_LOCK_STATUS, a_nPropValue);
		if (*a_nPropValue == 1)
			*a_nPropValue = 1;
		else
			*a_nPropValue = 0;
		return *a_nPropValue;
		break;

	case LFT_SPPU_FPGA_PROP_DAC_FIFO_ERR:

		//TBD: Not used
		break;

	case LFT_SPPU_FPGA_PROP_DAC1_FIFO_ERR:

		DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_WRITE_ALARM, 0);
		DACRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC1,LFT_SPPU_DAC_READ_ALARM, a_nPropValue);

		if(*a_nPropValue != 0)
			*a_nPropValue = 1;
		break;

	case LFT_SPPU_FPGA_PROP_DAC2_FIFO_ERR:

		DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_WRITE_ALARM, 0);
		DACRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC2,LFT_SPPU_DAC_READ_ALARM, a_nPropValue);

		if(*a_nPropValue != 0)
			*a_nPropValue = 1;
		break;

	case LFT_SPPU_FPGA_PROP_DAC3_FIFO_ERR:

		DACRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_WRITE_ALARM, 0);
		DACRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_DAC3,LFT_SPPU_DAC_READ_ALARM, a_nPropValue);

		if(*a_nPropValue != 0)
			*a_nPropValue = 1;

		break;

	}

	return -100;
}

long MiddleAPI::SetDACProperty(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,SPPUDACProp a_enDACProp, unsigned int a_nPropValue)		
{
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};

	sprintf_s(strDebug, DEBUG_STR_LEN,"\nIn SetDACProperty(%d, %d, %d, %d, %d)", a_enConnectionType, a_nModuleID, a_enDeviceType, a_enDACProp, a_nPropValue);
	mPrintDebug(strDebug);

	switch(a_enDACProp)
	{
	case LFT_SPPU_DAC_PROP_FIFO_STATE:
		switch((SPPUState)a_nPropValue)
		{
		case LFT_SPPU_STATE_DISABLE:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID, a_enDeviceType,LFT_SPPU_DAC_FIFO_ena ,a_nPropValue);
		case LFT_SPPU_STATE_ENABLE:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID, a_enDeviceType,LFT_SPPU_DAC_FIFO_ena ,a_nPropValue);
		}
	case LFT_SPPU_DAC_PROP_FIFO_OFFSET:

		switch((SPPUDACPropFIFO) a_nPropValue)
		{ 
		case  LFT_SPPU_DAC_PROP_FIFO_OFFSET_0: 
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_FIFO_offset ,0);

		case  LFT_SPPU_DAC_PROP_FIFO_OFFSET_1:   
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_FIFO_offset ,2);

		case  LFT_SPPU_DAC_PROP_FIFO_OFFSET_2:  
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_FIFO_offset ,4);

		case  LFT_SPPU_DAC_PROP_FIFO_OFFSET_3:    
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_FIFO_offset ,6);

		case  LFT_SPPU_DAC_PROP_FIFO_OFFSET_4:    
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_FIFO_offset ,8);

		case  LFT_SPPU_DAC_PROP_FIFO_OFFSET_5:    
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_FIFO_offset ,10);

		case  LFT_SPPU_DAC_PROP_FIFO_OFFSET_6:     
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_FIFO_offset ,12);

		case  LFT_SPPU_DAC_PROP_FIFO_OFFSET_7:        
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_FIFO_offset ,14);

		}
		break;

	case LFT_SPPU_DAC_PROP_INPUT_SYNC:

		switch((SPPUDACPropFIFOInputSync)a_nPropValue)
		{
		case LFT_SPPU_DAC_PROP_FIFO_INPUT_NONE : 
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_FIFO_input_sync,4);

		case LFT_SPPU_DAC_PROP_FIFO_INPUT_SYNC : 
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_FIFO_input_sync,1);

		case LFT_SPPU_DAC_PROP_FIFO_INPUT_FRAME :  
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_FIFO_input_sync,2);

		case LFT_SPPU_DAC_PROP_FIFO_SIF_SYNC:    
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_FIFO_input_sync,8);

		}
		break;

	case	LFT_SPPU_DAC_PROP_OUTPUT_SYNC:

		switch((SPPUDACPropFIFOOutputSync)a_nPropValue)
		{
		case LFT_SPPU_DAC_PROP_FIFO_OUTPUT_SYNC: 
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_FIFO_output_sync,1);

		case LFT_SPPU_DAC_PROP_FIFO_OUTPUT_FRAME:  
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_FIFO_output_sync,2);

		case LFT_SPPU_DAC_PROP_FIFO_OUTPUT_OSTR: 
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_FIFO_output_sync,4);

		case LFT_SPPU_DAC_PROP_FIFO_OUTPUT_SIF_SYNC:    
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_FIFO_output_sync,8);

		}
		break;
	case   LFT_SPPU_DAC_PROP_DATA_FORMATTER_SYNC:

		switch((SPPUDACPropDataFormatterSync)a_nPropValue)
		{

		case LFT_SPPU_DAC_PROP_FIFO_DATA_FORMATTER_NONE:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_dataformatter,10);

		case LFT_SPPU_DAC_PROP_FIFO_DATA_FORMATTER_FRAME:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_dataformatter,2);

		case LFT_SPPU_DAC_PROP_FIFO_DATA_FORMATTER_SYNC:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_dataformatter,6); 

		}
		break;

	case  LFT_SPPU_DAC_PROP_LVDS_DELAY_DATA:

		switch((SPPUDACPropLVDSDelay)a_nPropValue)
		{
		case LFT_SPPU_DAC_PROP_LVDS_DELAY_0:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_LVDS_datadly,0);

		case LFT_SPPU_DAC_PROP_LVDS_DELAY_40:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_LVDS_datadly,2);

		case LFT_SPPU_DAC_PROP_LVDS_DELAY_80:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_LVDS_datadly,4);

		case LFT_SPPU_DAC_PROP_LVDS_DELAY_120:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_LVDS_datadly,6);

		case LFT_SPPU_DAC_PROP_LVDS_DELAY_160:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_LVDS_datadly,8);

		case LFT_SPPU_DAC_PROP_LVDS_DELAY_200:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_LVDS_datadly,10);

		case LFT_SPPU_DAC_PROP_LVDS_DELAY_240:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_LVDS_datadly,12);

		case LFT_SPPU_DAC_PROP_LVDS_DELAY_280:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_LVDS_datadly,14);
		}
		break;

	case LFT_SPPU_DAC_PROP_LVDS_DELAY_CLOCK:

		switch((SPPUDACPropLVDSDelay)a_nPropValue)
		{
		case LFT_SPPU_DAC_PROP_LVDS_DELAY_0:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_LVDS_CLKdly,0);

		case LFT_SPPU_DAC_PROP_LVDS_DELAY_40:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_LVDS_CLKdly,4);

		case LFT_SPPU_DAC_PROP_LVDS_DELAY_80:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_LVDS_CLKdly,8);

		case LFT_SPPU_DAC_PROP_LVDS_DELAY_120:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_LVDS_CLKdly,12);

		case LFT_SPPU_DAC_PROP_LVDS_DELAY_160:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_LVDS_CLKdly,16);

		case LFT_SPPU_DAC_PROP_LVDS_DELAY_200:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_LVDS_CLKdly,20);

		case LFT_SPPU_DAC_PROP_LVDS_DELAY_240:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_LVDS_CLKdly,24);

		case LFT_SPPU_DAC_PROP_LVDS_DELAY_280:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_LVDS_CLKdly,28);

		}
		break;

	case  LFT_SPPU_DAC_PROP_PLL_STATUS: // doubt

	case  LFT_SPPU_DAC_PROP_LF_VOLTAGE:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PLL_LFVOLT,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_PLL_STATE: 
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PLL_ENA,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_PLL_PRESCALER:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PLL_Prescaler,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_PLL_VCO_BIAS_TUNE:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PLL_vcoibiastune,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_PLL_CHARGE_PUMP:

		switch((SPPUDACPropChargePump) a_nPropValue)
		{
		case LFT_SPPU_DAC_PROP_CHRG_PMP_NONE:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PLL_Charge_pump ,0);

		case LFT_SPPU_DAC_PROP_CHRG_PMP_SIGNLE:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PLL_Charge_pump ,4);

		case LFT_SPPU_DAC_PROP_CHRG_PMP_DOUBLE:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PLL_Charge_pump ,12);

		}
		break;

	case LFT_SPPU_DAC_PROP_PLL_M:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PLL_m,a_nPropValue);


	case LFT_SPPU_DAC_PROP_PLL_N:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PLL_n,a_nPropValue);


	case LFT_SPPU_DAC_PROP_PLL_FREQ_TUNE:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_Freq_tune_PLL_vco,a_nPropValue);


	case LFT_SPPU_DAC_PROP_PLL_OUT_FREF:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PLL_Prescaler,a_nPropValue);// doubt


	case LFT_SPPU_DAC_PROP_PLL_OUT_FDAC:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PLL_Prescaler,a_nPropValue);// doubt

	case LFT_SPPU_DAC_PROP_PLL_OUT_FVCO:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PLL_Prescaler,a_nPropValue); // doubt

	case LFT_SPPU_DAC_PROP_PLL_OUT_PFD:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PLL_Prescaler,a_nPropValue); // doubt


	case LFT_SPPU_DAC_PROP_PLL_OUT_STABILITY:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PLL_Prescaler,a_nPropValue); // doubt

	case LFT_SPPU_DAC_PROP_PLL_RESET:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PLL_RESET,a_nPropValue);

	case LFT_SPPU_DAC_PROP_PLL_SLEEP:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PLL_sleep,a_nPropValue);

	case LFT_SPPU_DAC_PROP_PLL_SYNC_DIVIDERS:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PLL_Sync_pll_dividers_NDIVSYNC_ENA,a_nPropValue);

	case LFT_SPPU_DAC_PROP_PLL_BASE_OMPAMP_OFF:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType, LFT_SPPU_DAC_opamp_off_bias_sleep,a_nPropValue);

	case LFT_SPPU_DAC_PROP_PLL_FUSE_SLEEP:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_ATEST_FUSE_SLEEP,a_nPropValue);

		// DIGITAL TAB START FROM HERE //
	case LFT_SPPU_DAC_PROP_DIGITAL_FILTERS:

		switch((SPPUDACPropInterpolation) a_nPropValue)
		{
		case LFT_SPPU_DAC_PROP_INTRPLTN_ZOOM_1:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_digital_filter_interpolation_interp,0);

		case LFT_SPPU_DAC_PROP_INTRPLTN_ZOOM_2:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_digital_filter_interpolation_interp,1);

		case LFT_SPPU_DAC_PROP_INTRPLTN_ZOOM_4:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_digital_filter_interpolation_interp,2);

		case LFT_SPPU_DAC_PROP_INTRPLTN_ZOOM_8:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_digital_filter_interpolation_interp,4);

		case LFT_SPPU_DAC_PROP_INTRPLTN_ZOOM_16:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_digital_filter_interpolation_interp,8);
		}
		break;

	case LFT_SPPU_DAC_PROP_DIGITAL_MIXER_STATE:

		switch((SPPUState) a_nPropValue)
		{
		case LFT_SPPU_STATE_DISABLE:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_mixer_ena,0);

		case LFT_SPPU_STATE_ENABLE:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_mixer_ena,1);
		}
		break;


	case LFT_SPPU_DAC_PROP_DIGITAL_MIXER:

		switch((SPPUDACPropDigitalMixer)a_nPropValue)
		{

		case  LFT_SPPU_DAC_PROP_MIXER_BYPASS:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType, LFT_SPPU_DAC_MIXER_cmix_mode,0);

		case  LFT_SPPU_DAC_PROP_MIXER_MINUSFSBY4:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType, LFT_SPPU_DAC_MIXER_cmix_mode,1);

		case  LFT_SPPU_DAC_PROP_MIXER_FSBY2:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType, LFT_SPPU_DAC_MIXER_cmix_mode,2);

		case  LFT_SPPU_DAC_PROP_MIXER_FSBY4:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType, LFT_SPPU_DAC_MIXER_cmix_mode,4);

		case  LFT_SPPU_DAC_PROP_MIXER_FSBY8:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType, LFT_SPPU_DAC_MIXER_cmix_mode,8);

		case  LFT_SPPU_DAC_PROP_MIXER_3FSBY8:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType, LFT_SPPU_DAC_MIXER_cmix_mode,12);

		case  LFT_SPPU_DAC_PROP_MIXER_5FSBY8:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType, LFT_SPPU_DAC_MIXER_cmix_mode,10);

		case  LFT_SPPU_DAC_PROP_MIXER_7FSBY8:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType, LFT_SPPU_DAC_MIXER_cmix_mode,14);

		}
		break;

	case LFT_SPPU_DAC_PROP_COMPENSATE_IQ:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_invsinc_ena_compensate_IQ,a_nPropValue);

	case LFT_SPPU_DAC_PROP_GROUP_DELAY_I:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType, LFT_SPPU_DAC_GRP_DELAY_I_grpdelay,a_nPropValue);

	case LFT_SPPU_DAC_PROP_GROUP_DELAY_Q:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_GRP_DELAY_Q_grpdelay,a_nPropValue);

	case LFT_SPPU_DAC_PROP_CLOCK_RECEIVER_SLEEP:
		return  DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_Clock_receiver_sleep_clkrecv_sleep,a_nPropValue);

	case LFT_SPPU_DAC_PROP_CLOCK_DIVIDER_SYNC:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_clkdiv_sync_ena,a_nPropValue);

	case LFT_SPPU_DAC_PROP_CLOCK_DIV_SYNC_SOURCE:

		switch((SPPUDACPropClockDivSync) a_nPropValue)
		{
		case LFT_SPPU_DAC_PROP_CLK_DIV_SYNC_OSTR:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_SYNC_clkdiv_sync_sel,0);

		case LFT_SPPU_DAC_PROP_CLK_DIV_SYNC_FRAME:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_SYNC_clkdiv_sync_sel,1);
		}
		break;
	case  LFT_SPPU_DAC_PROP_GAIN :
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_GAIN_coarse_dac_gain,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_SIF_SYNC:
		return  DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_SIF_sync,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_QMC_CORRECT_STATE:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_Correct_corr_ena,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_QMC_GAIN_FIRST:
		return  DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_qmcgain_first,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_QMC_GAIN_SECOND:
		return  DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_qmcGain_second,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_QMC_PHASE:
		return  DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_qmc_phase,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_QMC_CORRECT_SYNC:

		switch((SPPUDACPropSync)a_nPropValue)
		{
		case LFT_SPPU_DAC_PROP_SYNC_REGWR:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_QMC_Correctsync,1);

		case LFT_SPPU_DAC_PROP_SYNC_OSTR:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_QMC_Correctsync,2);

		case LFT_SPPU_DAC_PROP_SYNC_SYNC:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_QMC_Correctsync,4);

		case LFT_SPPU_DAC_PROP_SYNC_SIFSYNC:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_QMC_Correctsync,8);
		}
		break;

	case  LFT_SPPU_DAC_PROP_QMC_SYNCAB:
		//	 return  DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,,a_nPropValue); // doubt

	case  LFT_SPPU_DAC_PROP_OFFSET_ADJUST:
		return  DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_Offset_adjust,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_OFFSET_FIRST:
		return  DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_Offset_first,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_OFFSET_SECOND:
		return  DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_OffsetB_second,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_OFFSET_SYNC:
		switch((SPPUDACPropSync)a_nPropValue)
		{
		case LFT_SPPU_DAC_PROP_SYNC_REGWR:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_QMC_Offset_Sync,1);

		case LFT_SPPU_DAC_PROP_SYNC_OSTR:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_QMC_Offset_Sync,2);

		case LFT_SPPU_DAC_PROP_SYNC_SYNC:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_QMC_Offset_Sync,4);

		case LFT_SPPU_DAC_PROP_SYNC_SIFSYNC:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_QMC_Offset_Sync,8);
		}
		break;

	case  LFT_SPPU_DAC_PROP_NCO_STATE:
		switch((SPPUState) a_nPropValue)
		{
		case LFT_SPPU_STATE_DISABLE:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_NCO_ena,0);

		case LFT_SPPU_STATE_ENABLE:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_NCO_ena,1);
		}
		break;



	case  LFT_SPPU_DAC_PROP_NCO_F_SAMPLE:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PLL_Prescaler,a_nPropValue);  // DOUBT

	case  LFT_SPPU_DAC_PROP_NCO_FREQ_AB:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PLL_Prescaler,a_nPropValue); // DOUBT

	case  LFT_SPPU_DAC_PROP_NCO_GAIN:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_NCO_Gain,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_NCO_ACC_SYNC:
		switch((SPPUDACPropNCOAccSync)a_nPropValue)
		{
		case LFT_SPPU_DAC_PROP_NCO_SYNC_BYPASS:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_NCO_Acc_SYNC,0);

		case LFT_SPPU_DAC_PROP_NCO_SYNC_FRAME:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_NCO_Acc_SYNC,1);

		case LFT_SPPU_DAC_PROP_NCO_SYNC_OSTR:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_NCO_Acc_SYNC,2);

		case LFT_SPPU_DAC_PROP_NCO_SYNC_SYNC:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_NCO_Acc_SYNC,4);

		case LFT_SPPU_DAC_PROP_NCO_SYNC_SIF_SYNC:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_NCO_Acc_SYNC,8);
		}
		break;


	case  LFT_SPPU_DAC_PROP_NCO_PHASE_OFFSET_AB:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_NCO_phase_offset_AB,a_nPropValue);// DOUBT


	case  LFT_SPPU_DAC_PROP_NCO_PHASE_OFFSET_CD:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_NCO_phase_offset_CD,a_nPropValue); // DOUBT 


	case  LFT_SPPU_DAC_PROP_NCO_DDS_AB:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_NCO_DDS_AB_phase_add,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_NCO_MIXAB_SYNC:

		switch((SPPUDACPropSync)a_nPropValue)
		{
		case  LFT_SPPU_DAC_PROP_SYNC_REGWR:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_NCO_MixAB_Sync_mixer,1);

		case  LFT_SPPU_DAC_PROP_SYNC_OSTR:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_NCO_MixAB_Sync_mixer,2);

		case  LFT_SPPU_DAC_PROP_SYNC_SYNC:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_NCO_MixAB_Sync_mixer,4);

		case LFT_SPPU_DAC_PROP_SYNC_SIFSYNC:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_NCO_MixAB_Sync_mixer,8);

		}
		break;


		/// DIGITAL TAB END HERE //

		// advance tab is start from here //
	case  LFT_SPPU_DAC_PROP_SLP_CTL_NOT_USED:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_SLEEP_CNT_notused_RESERVED1,a_nPropValue);  // DOUBT

	case  LFT_SPPU_DAC_PROP_SLP_CTL_DACI:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_SLEEP_CNT_DACI_SLP,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_SLP_CTL_DACQ:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_SLEEP_CNT_DACQ_SLP,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_SLP_CTL_NOT_USED_2:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_SLEEP_CNT_notused_RESERVED2,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_SLP_CTL_CLK_RECEIVER:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_SLEEP_CNT_CLK_RCV_SLP,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_SLP_CTL_PLL:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_SLEEP_CNT_PLL_SLEEP,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_SLP_CTL_LVDS_DATA:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_SLEEP_CNT_LVDS_DATA_SLP,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_SLP_CTL_LVDS_CONTROL:
		return  DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_SLEEP_CNT_LVDS_CNT_SLP,a_nPropValue);


	case  LFT_SPPU_DAC_PROP_SLP_CTL_TEMP_SENSOR :
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_SLEEP_CNT_temp_sensor_TMP_CNT,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_SLP_CTL_FUSES :
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_SLEEP_CNT_fuses_RESERVED,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_SLP_CTL_BIAS_OPAMP:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_SLEEP_CNT_bias_opamp_BIAS_AMP_SLP,a_nPropValue);

		// sleep control end here // 

	case  LFT_SPPU_DAC_PROP_ALARM_ZERO_CHECK:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_ALARMS_ZERO_CHECK_FROM_ZEROCLOCK,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_ALARM_NOT_USED:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_ALARMS_NOTUSED1,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_ALARM_FIFO_COLLISION:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_ALARMS_FIFO_COLLISION,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_ALARM_FIFO_1_AWAY :
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_ALARMS_FIFO_1AWAY,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_ALARM_FIFO_2_AWAY:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_ALARMS_FIFO_2WAY,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_ALARM_DACCLK_GONE:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_ALARMS_DACCLK_GONE,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_ALARM_DCLK_GONE:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_ALARMS_DATACLK_GONE,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_ALARM_CLOCK_GONE:
		return  DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_ALARMS_CLK_OUTPUT_GONE,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_ALARM_IO_TEST:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_ALARMS_IO_TEST_FROM_IOTEST,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_ALARM_OSTR_PATTERN:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_ALARMS_OSTR ,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_ALARM_PLL_LOCK:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_ALARMS_PLLLOCK_FROM_PLL,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_ALARM_PARITY_R_EDGE:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_ALARMS_PARITY_Rising_edge_RPARITY,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_ALARM_PARITY_F_EDGE:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_ALARMS_PARITY_Falling_edge_LPARITY,a_nPropValue);


	case  LFT_SPPU_DAC_PROP_ALARM_BLOCK_PARITY:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_ALARMS_Block_FRAME_PARITY,a_nPropValue);


	case  LFT_SPPU_DAC_PROP_ALARM_NOT_USED_2:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_ALARMS_NOTUSED2,a_nPropValue);


	case  LFT_SPPU_DAC_PROP_ALARM_NOT_USED_3:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_ALARMS_NOTUSED3,a_nPropValue);


	case  LFT_SPPU_DAC_PROP_IO_TEST_STATE:
		switch((SPPUState) a_nPropValue)
		{
		case LFT_SPPU_STATE_DISABLE:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_IOTEST_IO_DISA,0);

		case LFT_SPPU_STATE_ENABLE:
			return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_IOTEST_IO_ENA,1);
		}
		break;


	case  LFT_SPPU_DAC_PROP_IO_TEST_PATTERN_0:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PATTERN0,a_nPropValue);


	case  LFT_SPPU_DAC_PROP_IO_TEST_PATTERN_1:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PATTERN1,a_nPropValue);


	case  LFT_SPPU_DAC_PROP_IO_TEST_PATTERN_2:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PATTERN2,a_nPropValue);


	case  LFT_SPPU_DAC_PROP_IO_TEST_PATTERN_3:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PATTERN3,a_nPropValue);


	case  LFT_SPPU_DAC_PROP_IO_TEST_PATTERN_4:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PATTERN4,a_nPropValue);


	case  LFT_SPPU_DAC_PROP_IO_TEST_PATTERN_5:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PATTERN5,a_nPropValue);


	case  LFT_SPPU_DAC_PROP_IO_TEST_PATTERN_6:
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PATTERN6,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_IO_TEST_PATTERN_7:  
		return DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PATTERN7,a_nPropValue);


	}
	return -1009;
}

long MiddleAPI::GetDACProperty(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,SPPUDACProp a_enDACProp, unsigned int *a_nPropValue)		
{
	unsigned int a_nDACPropValue = 0; 
	switch(a_enDACProp)
	{
	case  LFT_SPPU_DAC_PROP_FIFO_STATE:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_FIFO_ena ,a_nPropValue);  // doubt

	case  LFT_SPPU_DAC_PROP_FIFO_OFFSET:

		DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_FIFO_offset , &a_nDACPropValue);

		switch(a_nDACPropValue)
		{
		case 0:
			return *a_nPropValue	= LFT_SPPU_DAC_PROP_FIFO_OFFSET_0;
		case 1:
			return *a_nPropValue	= LFT_SPPU_DAC_PROP_FIFO_OFFSET_1;
		case 2:
			return *a_nPropValue	= LFT_SPPU_DAC_PROP_FIFO_OFFSET_2;
		case 3:
			return *a_nPropValue	= LFT_SPPU_DAC_PROP_FIFO_OFFSET_3;
		case 4:
			return *a_nPropValue	= LFT_SPPU_DAC_PROP_FIFO_OFFSET_4;
		case 5:
			return *a_nPropValue	= LFT_SPPU_DAC_PROP_FIFO_OFFSET_5;
		case 6:
			return *a_nPropValue	= LFT_SPPU_DAC_PROP_FIFO_OFFSET_6;
			break;
		case 7:
			return *a_nPropValue	= LFT_SPPU_DAC_PROP_FIFO_OFFSET_7;
		}
		break;

	case  LFT_SPPU_DAC_PROP_INPUT_SYNC:

		DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_FIFO_input_sync,&a_nDACPropValue);

		switch(a_nDACPropValue)
		{
		case 1:
			return *a_nPropValue = LFT_SPPU_DAC_PROP_FIFO_INPUT_NONE ; 
		case 2:
			return *a_nPropValue = LFT_SPPU_DAC_PROP_FIFO_INPUT_SYNC;  
		case 3:
			return *a_nPropValue = LFT_SPPU_DAC_PROP_FIFO_INPUT_FRAME; 
		case 4:
			return *a_nPropValue =   LFT_SPPU_DAC_PROP_FIFO_SIF_SYNC;   
		}
		break;


	case   LFT_SPPU_DAC_PROP_OUTPUT_SYNC:

		DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_FIFO_output_sync,&a_nDACPropValue);

		switch(a_nDACPropValue)
		{
		case 1:
			return *a_nPropValue = LFT_SPPU_DAC_PROP_FIFO_OUTPUT_SYNC ; 
		case 2:
			return *a_nPropValue = LFT_SPPU_DAC_PROP_FIFO_OUTPUT_FRAME;  
		case 3:
			return *a_nPropValue = LFT_SPPU_DAC_PROP_FIFO_OUTPUT_OSTR; 
		case 4:
			return *a_nPropValue = LFT_SPPU_DAC_PROP_FIFO_OUTPUT_SIF_SYNC;   
		}
		break;


	case   LFT_SPPU_DAC_PROP_DATA_FORMATTER_SYNC:

		DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_dataformatter,&a_nDACPropValue);

		switch(a_nDACPropValue)
		{
		case 1:
			return *a_nPropValue = LFT_SPPU_DAC_PROP_FIFO_DATA_FORMATTER_NONE;
		case 2:
			return *a_nPropValue = LFT_SPPU_DAC_PROP_FIFO_DATA_FORMATTER_SYNC;
		case 3:
			return *a_nPropValue = LFT_SPPU_DAC_PROP_FIFO_DATA_FORMATTER_FRAME;
		}
		break;

	case   LFT_SPPU_DAC_PROP_LVDS_DELAY_DATA:

		DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_LVDS_datadly,&a_nDACPropValue);

		switch(a_nDACPropValue)
		{
		case 1:
			return *a_nPropValue = LFT_SPPU_DAC_PROP_LVDS_DELAY_0;
		case 2:
			return *a_nPropValue = LFT_SPPU_DAC_PROP_LVDS_DELAY_40;
		case 3:
			return *a_nPropValue = LFT_SPPU_DAC_PROP_LVDS_DELAY_80;
		case 4:
			return *a_nPropValue = LFT_SPPU_DAC_PROP_LVDS_DELAY_120;
		case 5:
			return *a_nPropValue = LFT_SPPU_DAC_PROP_LVDS_DELAY_160;
		case 6:
			return  *a_nPropValue = LFT_SPPU_DAC_PROP_LVDS_DELAY_200;
		case 7:
			return *a_nPropValue =  LFT_SPPU_DAC_PROP_LVDS_DELAY_240;
		case 8:
			return *a_nPropValue = LFT_SPPU_DAC_PROP_LVDS_DELAY_280;
		}
		break;


	case  LFT_SPPU_DAC_PROP_LVDS_DELAY_CLOCK:

		DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_LVDS_CLKdly,&a_nDACPropValue);

		switch(a_nDACPropValue)
		{
		case 1:
			return *a_nPropValue = LFT_SPPU_DAC_PROP_LVDS_DELAY_0;
		case 2:
			return *a_nPropValue = LFT_SPPU_DAC_PROP_LVDS_DELAY_40;
		case 3:
			return *a_nPropValue = LFT_SPPU_DAC_PROP_LVDS_DELAY_80;
		case 4:
			return *a_nPropValue = LFT_SPPU_DAC_PROP_LVDS_DELAY_120;
		case 5:
			return *a_nPropValue = LFT_SPPU_DAC_PROP_LVDS_DELAY_160;
		case 6:
			return *a_nPropValue =  LFT_SPPU_DAC_PROP_LVDS_DELAY_200;
		case 7:
			return *a_nPropValue = LFT_SPPU_DAC_PROP_LVDS_DELAY_240;
		case 8:
			return*a_nPropValue = LFT_SPPU_DAC_PROP_LVDS_DELAY_280;
		}
		break;

	case  LFT_SPPU_DAC_PROP_PLL_STATUS: // doubt
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PLL_STATUS_LOCK,a_nPropValue);
	case  LFT_SPPU_DAC_PROP_LF_VOLTAGE:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PLL_LFVOLT,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_PLL_STATE:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PLL_ENA,a_nPropValue);                    

	case  LFT_SPPU_DAC_PROP_PLL_PRESCALER:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PLL_Prescaler,a_nPropValue);
	case  LFT_SPPU_DAC_PROP_PLL_VCO_BIAS_TUNE:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PLL_vcoibiastune,a_nPropValue);


	case  LFT_SPPU_DAC_PROP_PLL_CHARGE_PUMP:

		DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PLL_Charge_pump ,&a_nDACPropValue);

		switch(a_nDACPropValue)
		{
		case 1:
			return *a_nPropValue = LFT_SPPU_DAC_PROP_CHRG_PMP_NONE;
		case 2:
			return *a_nPropValue = LFT_SPPU_DAC_PROP_CHRG_PMP_SIGNLE;
		case 3:
			return *a_nPropValue = LFT_SPPU_DAC_PROP_CHRG_PMP_DOUBLE;
		}
		break;

	case  LFT_SPPU_DAC_PROP_PLL_M:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PLL_m,a_nPropValue);


	case LFT_SPPU_DAC_PROP_PLL_N:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PLL_n,a_nPropValue);


	case LFT_SPPU_DAC_PROP_PLL_FREQ_TUNE:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_Freq_tune_PLL_vco,a_nPropValue);


	case LFT_SPPU_DAC_PROP_PLL_OUT_FREF:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PLL_Prescaler,a_nPropValue);// doubt


	case LFT_SPPU_DAC_PROP_PLL_OUT_FDAC:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PLL_Prescaler,a_nPropValue);// doubt

	case LFT_SPPU_DAC_PROP_PLL_OUT_FVCO:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PLL_Prescaler,a_nPropValue); // doubt

	case LFT_SPPU_DAC_PROP_PLL_OUT_PFD:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PLL_Prescaler,a_nPropValue); // doubt


	case LFT_SPPU_DAC_PROP_PLL_OUT_STABILITY :
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PLL_Prescaler,a_nPropValue); // doubt


	case LFT_SPPU_DAC_PROP_PLL_RESET:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PLL_RESET,a_nPropValue);


	case LFT_SPPU_DAC_PROP_PLL_SLEEP:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PLL_sleep,a_nPropValue);


	case LFT_SPPU_DAC_PROP_PLL_SYNC_DIVIDERS:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PLL_Sync_pll_dividers_NDIVSYNC_ENA,a_nPropValue);

	case LFT_SPPU_DAC_PROP_PLL_BASE_OMPAMP_OFF:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType, LFT_SPPU_DAC_opamp_off_bias_sleep,a_nPropValue);

	case LFT_SPPU_DAC_PROP_PLL_FUSE_SLEEP:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_ATEST_FUSE_SLEEP,a_nPropValue);

		// DIGITAL TAB START FROM HERE //
	case LFT_SPPU_DAC_PROP_DIGITAL_FILTERS:

		DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_digital_filter_interpolation_interp,&a_nDACPropValue);


		switch(a_nDACPropValue)
		{
		case 1:
			return *a_nPropValue = LFT_SPPU_DAC_PROP_INTRPLTN_ZOOM_1;
		case 2:
			return *a_nPropValue = LFT_SPPU_DAC_PROP_INTRPLTN_ZOOM_2;
		case 3:
			return *a_nPropValue = LFT_SPPU_DAC_PROP_INTRPLTN_ZOOM_4;
		case 4:
			return *a_nPropValue = LFT_SPPU_DAC_PROP_INTRPLTN_ZOOM_8;
		}
		break;

	case LFT_SPPU_DAC_PROP_DIGITAL_MIXER_STATE:

		DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_mixer_ena,&a_nDACPropValue);
		switch(a_nDACPropValue)
		{
		case 1:
			return *a_nPropValue =  LFT_SPPU_STATE_DISABLE;

		case 2:
			return *a_nPropValue  =  LFT_SPPU_STATE_ENABLE;

		}
		break;


	case LFT_SPPU_DAC_PROP_DIGITAL_MIXER:

		DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType, LFT_SPPU_DAC_MIXER_cmix_mode,&a_nDACPropValue);
		switch(a_nDACPropValue)
		{

		case 1:
			return *a_nPropValue = LFT_SPPU_DAC_PROP_MIXER_BYPASS;

		case  2:
			return *a_nPropValue = LFT_SPPU_DAC_PROP_MIXER_MINUSFSBY4;

		case  3:
			return *a_nPropValue = LFT_SPPU_DAC_PROP_MIXER_FSBY2;

		case 4:
			return *a_nPropValue = LFT_SPPU_DAC_PROP_MIXER_FSBY4;

		case 5:
			return *a_nPropValue  = LFT_SPPU_DAC_PROP_MIXER_FSBY8;

		case  6:
			return *a_nPropValue = LFT_SPPU_DAC_PROP_MIXER_3FSBY8;

		case  7:
			return *a_nPropValue = LFT_SPPU_DAC_PROP_MIXER_5FSBY8;

		case  8:
			return *a_nPropValue = LFT_SPPU_DAC_PROP_MIXER_7FSBY8;

		}
		break;

	case LFT_SPPU_DAC_PROP_COMPENSATE_IQ:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_invsinc_ena_compensate_IQ,a_nPropValue);

	case LFT_SPPU_DAC_PROP_GROUP_DELAY_I:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType, LFT_SPPU_DAC_GRP_DELAY_I_grpdelay,a_nPropValue);

	case LFT_SPPU_DAC_PROP_GROUP_DELAY_Q:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_GRP_DELAY_Q_grpdelay,a_nPropValue);

	case LFT_SPPU_DAC_PROP_CLOCK_RECEIVER_SLEEP:
		return  DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_Clock_receiver_sleep_clkrecv_sleep,a_nPropValue);

	case LFT_SPPU_DAC_PROP_CLOCK_DIVIDER_SYNC:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_clkdiv_sync_ena,a_nPropValue);

	case LFT_SPPU_DAC_PROP_CLOCK_DIV_SYNC_SOURCE:

		DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_SYNC_clkdiv_sync_sel,&a_nDACPropValue);

		switch(a_nDACPropValue)
		{
		case 1:
			return LFT_SPPU_DAC_PROP_CLK_DIV_SYNC_OSTR;

		case 2:
			return LFT_SPPU_DAC_PROP_CLK_DIV_SYNC_FRAME;

		}
		break;
	case  LFT_SPPU_DAC_PROP_GAIN :
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_GAIN_coarse_dac_gain,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_SIF_SYNC:
		return  DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_SIF_sync,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_QMC_CORRECT_STATE:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_Correct_corr_ena,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_QMC_GAIN_FIRST:
		return  DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_qmcgain_first,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_QMC_GAIN_SECOND:
		return  DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_qmcGain_second,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_QMC_PHASE:
		return  DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_qmc_phase,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_QMC_CORRECT_SYNC:

		DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_QMC_Correctsync,&a_nDACPropValue);
		switch(a_nDACPropValue)
		{
		case 1:
			return LFT_SPPU_DAC_PROP_SYNC_REGWR;

		case 2:
			return LFT_SPPU_DAC_PROP_SYNC_OSTR;

		case 3:
			return LFT_SPPU_DAC_PROP_SYNC_SYNC;

		case 4:
			return LFT_SPPU_DAC_PROP_SYNC_SIFSYNC;

		}
		break;

	case  LFT_SPPU_DAC_PROP_QMC_SYNCAB:
		//	 return  DACRegAccessWrite(a_enConnectionType,a_nModuleID,a_enDeviceType,,a_nPropValue); // doubt

	case  LFT_SPPU_DAC_PROP_OFFSET_ADJUST:
		return  DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_Offset_adjust,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_OFFSET_FIRST:
		return  DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_Offset_first,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_OFFSET_SECOND:
		return  DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_OffsetB_second,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_OFFSET_SYNC:
		DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_QMC_Offset_Sync,&a_nDACPropValue);

		switch(a_nDACPropValue)
		{
		case 1:

			return *a_nPropValue = LFT_SPPU_DAC_PROP_SYNC_REGWR;

		case 2:
			return *a_nPropValue = LFT_SPPU_DAC_PROP_SYNC_OSTR;

		case 3:
			return *a_nPropValue =LFT_SPPU_DAC_PROP_SYNC_SYNC;


		case 4:
			return *a_nPropValue= LFT_SPPU_DAC_PROP_SYNC_SIFSYNC;

		}
		break;

	case  LFT_SPPU_DAC_PROP_NCO_STATE:
		DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_NCO_ena,&a_nDACPropValue);

		switch(a_nDACPropValue)
		{
		case 1:
			return *a_nPropValue = LFT_SPPU_STATE_DISABLE;


		case 2:
			return *a_nPropValue =  LFT_SPPU_STATE_ENABLE;

		}
		break;



	case  LFT_SPPU_DAC_PROP_NCO_F_SAMPLE:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PLL_Prescaler,a_nPropValue);  // DOUBT

	case  LFT_SPPU_DAC_PROP_NCO_FREQ_AB:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PLL_Prescaler,a_nPropValue); // DOUBT

	case  LFT_SPPU_DAC_PROP_NCO_GAIN:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_NCO_Gain,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_NCO_ACC_SYNC:
		DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_NCO_Acc_SYNC,&a_nDACPropValue);

		switch(a_nDACPropValue)
		{
		case 1:
			return *a_nPropValue = LFT_SPPU_DAC_PROP_NCO_SYNC_BYPASS;

		case 2:
			return *a_nPropValue = LFT_SPPU_DAC_PROP_NCO_SYNC_FRAME;

		case 3:
			return *a_nPropValue = LFT_SPPU_DAC_PROP_NCO_SYNC_OSTR;

		case 4:
			return *a_nPropValue = LFT_SPPU_DAC_PROP_NCO_SYNC_SYNC;

		case 5:
			return *a_nPropValue = LFT_SPPU_DAC_PROP_NCO_SYNC_SIF_SYNC;
		}
		break;


	case  LFT_SPPU_DAC_PROP_NCO_PHASE_OFFSET_AB:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_NCO_phase_offset_AB,a_nPropValue);// DOUBT


	case  LFT_SPPU_DAC_PROP_NCO_PHASE_OFFSET_CD:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_NCO_phase_offset_CD,a_nPropValue); // DOUBT 


	case  LFT_SPPU_DAC_PROP_NCO_DDS_AB:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_NCO_DDS_AB_phase_add,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_NCO_MIXAB_SYNC:
		DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_NCO_MixAB_Sync_mixer,&a_nDACPropValue);

		switch(a_nDACPropValue)
		{
		case 1:  
			return *a_nPropValue = LFT_SPPU_DAC_PROP_SYNC_REGWR;


		case  2:
			return *a_nPropValue = LFT_SPPU_DAC_PROP_SYNC_OSTR;


		case  3:
			return *a_nPropValue = LFT_SPPU_DAC_PROP_SYNC_SYNC;


		case 4:
			return *a_nPropValue =LFT_SPPU_DAC_PROP_SYNC_SIFSYNC;

		}
		break;


		/// DIGITAL TAB END HERE //

		// advance tab is start from here //
	case  LFT_SPPU_DAC_PROP_SLP_CTL_NOT_USED:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_SLEEP_CNT_notused_RESERVED1,a_nPropValue);  // DOUBT

	case  LFT_SPPU_DAC_PROP_SLP_CTL_DACI:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_SLEEP_CNT_DACI_SLP,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_SLP_CTL_DACQ:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_SLEEP_CNT_DACQ_SLP,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_SLP_CTL_NOT_USED_2:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_SLEEP_CNT_notused_RESERVED2,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_SLP_CTL_CLK_RECEIVER:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_SLEEP_CNT_CLK_RCV_SLP,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_SLP_CTL_PLL:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_SLEEP_CNT_PLL_SLEEP,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_SLP_CTL_LVDS_DATA:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_SLEEP_CNT_LVDS_DATA_SLP,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_SLP_CTL_LVDS_CONTROL:
		return  DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_SLEEP_CNT_LVDS_CNT_SLP,a_nPropValue);


	case  LFT_SPPU_DAC_PROP_SLP_CTL_TEMP_SENSOR :
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_SLEEP_CNT_temp_sensor_TMP_CNT,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_SLP_CTL_FUSES :
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_SLEEP_CNT_fuses_RESERVED,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_SLP_CTL_BIAS_OPAMP:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_SLEEP_CNT_bias_opamp_BIAS_AMP_SLP,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_ALARM_ZERO_CHECK_STS:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_ALARMS_ZERO_CHECK_FROM_ZEROCLOCK,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_ALARM_NOT_USED_STS:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_ALARMS_NOTUSED1,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_ALARM_FIFO_COLLSN_STS:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_ALARMS_FIFO_COLLISION,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_ALARM_FIFO_1_AWAY_STS :
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_ALARMS_FIFO_1AWAY,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_ALARM_FIFO_2_AWAY_STS:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_ALARMS_FIFO_2WAY,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_ALARM_DACCLK_GONE_STS:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_ALARMS_DACCLK_GONE,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_ALARM_DCLK_GONE_STS:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_ALARMS_DATACLK_GONE,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_ALARM_CLOCK_GONE_STS:
		return  DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_ALARMS_CLK_OUTPUT_GONE,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_ALARM_IO_TEST_STS :
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_ALARMS_IO_TEST_FROM_IOTEST,a_nPropValue);

	case   LFT_SPPU_DAC_PROP_ALARM_OSTR_PTTRN_STS:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_ALARMS_OSTR ,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_ALARM_PLL_LOCK_STS:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_ALARMS_PLLLOCK_FROM_PLL,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_ALARM_PRTY_R_EDGE_STS:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_ALARMS_PARITY_Rising_edge_RPARITY,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_ALARM_PRTY_F_EDGE_STS:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_ALARMS_PARITY_Falling_edge_LPARITY,a_nPropValue);


	case  LFT_SPPU_DAC_PROP_ALARM_BLOCK_PRTY_STS:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_ALARMS_Block_FRAME_PARITY,a_nPropValue);


	case  LFT_SPPU_DAC_PROP_ALARM_NOT_USED_2_STS:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_ALARMS_NOTUSED2,a_nPropValue);


	case  LFT_SPPU_DAC_PROP_ALARM_NOT_USED_3_STS:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_ALARMS_NOTUSED3,a_nPropValue);


	case  LFT_SPPU_DAC_PROP_IO_TEST_STATE:
		DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_IOTEST_IO_DISA,&a_nDACPropValue);
		switch(a_nDACPropValue)
		{
		case 1:
			return *a_nPropValue = LFT_SPPU_STATE_DISABLE;


		case 2:
			return *a_nPropValue = LFT_SPPU_STATE_ENABLE;

		}
		break;


	case  LFT_SPPU_DAC_PROP_IO_TEST_PATTERN_0:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PATTERN0,a_nPropValue);


	case  LFT_SPPU_DAC_PROP_IO_TEST_PATTERN_1:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PATTERN1,a_nPropValue);


	case  LFT_SPPU_DAC_PROP_IO_TEST_PATTERN_2:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PATTERN2,a_nPropValue);


	case  LFT_SPPU_DAC_PROP_IO_TEST_PATTERN_3:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PATTERN3,a_nPropValue);


	case  LFT_SPPU_DAC_PROP_IO_TEST_PATTERN_4:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PATTERN4,a_nPropValue);


	case  LFT_SPPU_DAC_PROP_IO_TEST_PATTERN_5:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PATTERN5,a_nPropValue);


	case  LFT_SPPU_DAC_PROP_IO_TEST_PATTERN_6:
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PATTERN6,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_IO_TEST_PATTERN_7:  
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_PATTERN7,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_IO_TEST_RSLTS_LSB_1:   
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_IOTEST_RESULT1,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_IO_TEST_RSLTS_LSB_2:   
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_IOTEST_RESULT2,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_IO_TEST_RSLTS_LSB_3:   
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_IOTEST_RESULT3,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_IO_TEST_RSLTS_LSB_4:   
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_IOTEST_RESULT4,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_IO_TEST_RSLTS_LSB_5:   
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_IOTEST_RESULT5,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_IO_TEST_RSLTS_LSB_6:   
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_IOTEST_RESULT6,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_IO_TEST_RSLTS_LSB_7:   
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_IOTEST_RESULT7,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_IO_TEST_RSLTS_LSB_8:   
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_IOTEST_RESULT8,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_IO_TEST_RSLTS_LSB_9:   
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_IOTEST_RESULT9,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_IO_TEST_RSLTS_LSB_10:   
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_IOTEST_RESULT10,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_IO_TEST_RSLTS_LSB_11:   
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_IOTEST_RESULT11,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_IO_TEST_RSLTS_LSB_12:   
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_IOTEST_RESULT12,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_IO_TEST_RSLTS_LSB_13:   
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_IOTEST_RESULT13,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_IO_TEST_RSLTS_LSB_14:   
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_IOTEST_RESULT14,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_IO_TEST_RSLTS_LSB_15:   
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_IOTEST_RESULT15,a_nPropValue);

	case  LFT_SPPU_DAC_PROP_IO_TEST_RSLTS_LSB_16:   
		return DACRegAccessRead(a_enConnectionType,a_nModuleID,a_enDeviceType,LFT_SPPU_DAC_IOTEST_RESULT16,a_nPropValue);
	}
	return -1009;
}
// advance tab is end here //

long MiddleAPI::SetLMKProperty(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,SPPULMKProp a_enLMKProp, unsigned int a_nPropValue)
{
	switch((SPPULMKProp)a_enLMKProp)
	{





		//****************************************general tap***************************************************************************//
	case LFT_SPPU_LMK_PROP_FEEDBACK_MUX_SOURCE:

		switch((SPPULMKPropFeedbackMuxSource)a_nPropValue)
		{
		case LFT_SPPU_LMK_PROP_FDBCK_MUX_SOURCE_CLK_OUT_0:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_FeedbackMux_Source_CLKOUT,0);

		case LFT_SPPU_LMK_PROP_FDBCK_MUX_SOURCE_CLK_OUT_2:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_FeedbackMux_Source_CLKOUT,1);

		case LFT_SPPU_LMK_PROP_FDBCK_MUX_SOURCE_CLK_OUT_4:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_FeedbackMux_Source_CLKOUT,2);

		case LFT_SPPU_LMK_PROP_FDBCK_MUX_SOURCE_CLK_OUT_6:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_FeedbackMux_Source_CLKOUT,3);

		case LFT_SPPU_LMK_PROP_FDBCK_MUX_SOURCE_CLK_OUT_8:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_FeedbackMux_Source_CLKOUT,4);

		case LFT_SPPU_LMK_PROP_FDBCK_MUX_SOURCE_CLK_OUT_10:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_FeedbackMux_Source_CLKOUT,5);

		case LFT_SPPU_LMK_PROP_FDBCK_MUX_SOURCE_CLK:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_FeedbackMux_Source_CLKOUT,6);
		}

	case LFT_SPPU_LMK_PROP_FEEDBACK_MUX_ENABLE:

		switch((SPPUState)a_nPropValue)
		{
		case  LFT_SPPU_STATE_DISABLE:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_FeedbackMux_Enable,0);
		case  LFT_SPPU_STATE_ENABLE:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_FeedbackMux_Enable,1);
		}

	case LFT_SPPU_LMK_PROP_VCO_DIVIDER:

		switch((SPPULMKPropDivider)a_nPropValue)
		{
		case LFT_SPPU_LMK_PROP_DIVIDER_2:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_VCO_Divider,2);
		case LFT_SPPU_LMK_PROP_DIVIDER_3: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_VCO_Divider,3);
		case LFT_SPPU_LMK_PROP_DIVIDER_4:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_VCO_Divider,4);
		case LFT_SPPU_LMK_PROP_DIVIDER_5:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_VCO_Divider,5);
		case LFT_SPPU_LMK_PROP_DIVIDER_6:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_VCO_Divider,6);
		case LFT_SPPU_LMK_PROP_DIVIDER_7:                    
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_VCO_Divider,7);
		case LFT_SPPU_LMK_PROP_DIVIDER_8:                    
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_VCO_Divider,0);  // Shd be 40
		}

	case LFT_SPPU_LMK_PROP_VCO_MUX:

		switch((SPPULMKPropVCOMux)a_nPropValue)
		{   
		case LFT_SPPU_LMK_PROP_VCO_MUX_SELECTED:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_VCO_Mux,0);
		case LFT_SPPU_LMK_PROP_VCO_MUX_DIVIDER:                        
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_VCO_Mux,1);
		}

	case LFT_SPPU_LMK_PROP_SYNC_TYPE:// doubt

		switch((SPPULMKPropType)a_nPropValue)
		{   
		case LFT_SPPU_LMK_PROP_INPUT:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_SYN_Type,0);
		case LFT_SPPU_LMK_PROP_INPUT_W_PULLUP_RESISTOR:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_SYN_Type,1);
		case LFT_SPPU_LMK_PROP_INPUT_W_PULLDOWN_RESISTOR:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_SYN_Type,2);
		case LFT_SPPU_LMK_PROP_OUTPUT:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_SYN_Type,3);
		case LFT_SPPU_LMK_PROP_OUTPUT_INVERTED:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_SYN_Type,4);
		case LFT_SPPU_LMK_PROP_OUTPUT_OPEN_SOURCE:          
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_SYN_Type,5);
		case LFT_SPPU_LMK_PROP_OPEN_DRAIN:         
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_SYN_Type,6);
		}

	case LFT_SPPU_LMK_PROP_SYNC_POLARITY: 


		switch((SPPULMKPropState)a_nPropValue)
		{   
		case LFT_SPPU_LMK_PROP_ACTIVE_LOW:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_SYN_Polarity,0);
		case LFT_SPPU_LMK_PROP_ACTIVE_HIGH:                        
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_SYN_Polarity,1);
		}


	case LFT_SPPU_LMK_PROP_SYNC_MUX:


		switch((SPPULMKPropSYNCMux)a_nPropValue)
		{   
		case LFT_SPPU_LMK_PROP_SYNC_MUX_LOGIC_LOW:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_SYN_sync_mux,0);
		case LFT_SPPU_LMK_PROP_SYNC_MUX_UWIRE_READBACK:                        
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_SYN_sync_mux,3);
		}

	case LFT_SPPU_LMK_PROP_SYNC_ENABLE:

		switch((SPPULMKPropSyncEnable)a_nPropValue)
		{   
		case LFT_SPPU_LMK_PROP_SYNC_ENABLE_MANUAL:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_SYN_ena_auto,0);
		case LFT_SPPU_LMK_PROP_SYNC_ENABLE_INTERNALLY_GENERATED:                        
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_SYN_ena_auto,1);
		}

	case LFT_SPPU_LMK_PROP_SYNC_QUALIFICATION:

		switch((SPPULMKPropSYNCQualification)a_nPropValue)
		{   
		case LFT_SPPU_LMK_PROP_SYNC_QUALIFICATION_NO:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_SYN_Qualification,0);
		case LFT_SPPU_LMK_PROP_SYNC_QUALIFICATION_BY_CLOCK_OUTPUT:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_SYN_Qualification,1);
		}

	case LFT_SPPU_LMK_PROP_SYNC_ENABLE_STATE:

		switch((SPPUState)a_nPropValue)
		{
		case  LFT_SPPU_STATE_DISABLE:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_SYN_ENABLE,0);
		case  LFT_SPPU_STATE_ENABLE:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_SYN_ENABLE,1);
		}


	case LFT_SPPU_LMK_PROP_SYNC_01_STATE:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_SYN_sync_op_01_STATE,a_nPropValue);
	case LFT_SPPU_LMK_PROP_SYNC_23_STATE:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_SYN_sync_op_02_STATE,a_nPropValue);
	case LFT_SPPU_LMK_PROP_SYNC_45_STATE:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_SYN_sync_op_03_STATE,a_nPropValue);
	case LFT_SPPU_LMK_PROP_SYNC_67_STATE:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_SYN_sync_op_04_STATE,a_nPropValue);
	case LFT_SPPU_LMK_PROP_SYNC_89_STATE:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_SYN_sync_op_05_STATE,a_nPropValue);
	case LFT_SPPU_LMK_PROP_SYNC_1011_STATE:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_SYN_sync_op_06_STATE,a_nPropValue);

	case LFT_SPPU_LMK_PROP_HLDOVR_MODE:

		switch((SPPUState)a_nPropValue)
		{
		case  LFT_SPPU_STATE_DISABLE:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_Holdover_Mode,0);
		case  LFT_SPPU_STATE_ENABLE:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_Holdover_Mode,1);
		}


	case LFT_SPPU_LMK_PROP_HLDOVR_DLD1_DET:
		switch((SPPULMKPropHoldoverDisable)a_nPropValue)
		{
		case  LFT_SPPU_LMK_PROP_HOLDOVER_DISABLE_CAUSES_CLK_SWTCH_EV: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_Holdover_dld1_DET,0);
		case  LFT_SPPU_LMK_PROP_HOLDOVER_DISABLE_NO_CLK_SWTCH_EV:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_Holdover_dld1_DET,1);
		}

	case LFT_SPPU_LMK_PROP_HLDOVR_DLD_COUNT:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_Holdover_DLD_count,a_nPropValue);
	case LFT_SPPU_LMK_PROP_HLDOVR_FORCE:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_Holdover_force,a_nPropValue);
	case LFT_SPPU_LMK_PROP_STS_OUT_LD_TYPE:

		switch((SPPULMKPropTypeSubOutput)a_nPropValue)
		{
		case LFT_SPPU_LMK_PROP_SUB_OUTPUT:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_LD_TYPE ,3);

		case LFT_SPPU_LMK_PROP_SUB_OUTPUT_INVERTED:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_LD_TYPE ,4);

		case LFT_SPPU_LMK_PROP_SUB_OUTPUT_OPEN_SOURCE:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_LD_TYPE ,5);

		case LFT_SPPU_LMK_PROP_SUB_OPEN_DRAIN:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_LD_TYPE ,6);



		}

	case LFT_SPPU_LMK_PROP_STS_OUT_LD_MUX:

		switch((SPPUMLMKPropMUX)a_nPropValue)
		{

		case LFT_SPPU_LMK_PROP_LDMUX_LOGIC_LOW:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_LD_MUX,0);
		case LFT_SPPU_LMK_PROP_LDMUX_PLL1DLD:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_LD_MUX,1);
		case LFT_SPPU_LMK_PROP_LDMUX_PLL2DLD:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_LD_MUX,2);
		case LFT_SPPU_LMK_PROP_LDMUX_PLL1DLD_N_PLL2DLD:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_LD_MUX,3);
		case LFT_SPPU_LMK_PROP_LDMUX_HODLOVER_STATUS:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_LD_MUX,4);
		case LFT_SPPU_LMK_PROP_LDMUX_DAC_LOCKED:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_LD_MUX,5);
		case LFT_SPPU_LMK_PROP_LDMUX_UWIRE_READBACK:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_LD_MUX,7);
		case LFT_SPPU_LMK_PROP_LDMUX_DAC_RAIL:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_LD_MUX,8);
		case LFT_SPPU_LMK_PROP_LDMUX_DAC_LOW:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_LD_MUX,9);
		case LFT_SPPU_LMK_PROP_LDMUX_DAC_HIGH:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_LD_MUX,10);
		case LFT_SPPU_LMK_PROP_LDMUX_DAC_PLL1_N:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_LD_MUX,11);
		case LFT_SPPU_LMK_PROP_LDMUX_DAC_PLL1_N_BY_2:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_LD_MUX,12);
		case LFT_SPPU_LMK_PROP_LDMUX_DAC_PLL2_N:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_LD_MUX,13);
		case LFT_SPPU_LMK_PROP_LDMUX_DAC_PLL2_N_BY_2:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_LD_MUX,14);
		case LFT_SPPU_LMK_PROP_LDMUX_DAC_PLL1_R:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_LD_MUX,15);
		case LFT_SPPU_LMK_PROP_LDMUX_DAC_PLL1_R_BY_2:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_LD_MUX,16);
		case LFT_SPPU_LMK_PROP_LDMUX_DAC_PLL2_R:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_LD_MUX,17);
		case LFT_SPPU_LMK_PROP_LDMUX_DAC_PLL2_R_BY_2:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_LD_MUX,18);
		}
	case LFT_SPPU_LMK_PROP_STS_OUT_HLDOVR_TYPE:
		switch((SPPULMKPropTypeSubOutput)a_nPropValue)
		{
		case LFT_SPPU_LMK_PROP_SUB_OUTPUT:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_Holdover_type ,3);

		case LFT_SPPU_LMK_PROP_SUB_OUTPUT_INVERTED:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_Holdover_type ,4);

		case LFT_SPPU_LMK_PROP_SUB_OUTPUT_OPEN_SOURCE:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_Holdover_type ,5);

		case LFT_SPPU_LMK_PROP_SUB_OPEN_DRAIN:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_Holdover_type ,6);



		}	






		// doubt
	case LFT_SPPU_LMK_PROP_STS_OUT_HLDOVR_MUX:
		switch((SPPUMLMKPropMUX)a_nPropValue)
		{

		case LFT_SPPU_LMK_PROP_LDMUX_LOGIC_LOW:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_Holdover_MUX,0);
		case LFT_SPPU_LMK_PROP_LDMUX_PLL1DLD:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_Holdover_MUX,1);
		case LFT_SPPU_LMK_PROP_LDMUX_PLL2DLD:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_Holdover_MUX,2);
		case LFT_SPPU_LMK_PROP_LDMUX_PLL1DLD_N_PLL2DLD:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_Holdover_MUX,3);
		case LFT_SPPU_LMK_PROP_LDMUX_HODLOVER_STATUS:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_Holdover_MUX,4);
		case LFT_SPPU_LMK_PROP_LDMUX_DAC_LOCKED:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_Holdover_MUX,5);
		case LFT_SPPU_LMK_PROP_LDMUX_UWIRE_READBACK:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_Holdover_MUX,7);
		case LFT_SPPU_LMK_PROP_LDMUX_DAC_RAIL:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_Holdover_MUX,8);
		case LFT_SPPU_LMK_PROP_LDMUX_DAC_LOW:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_Holdover_MUX,9);
		case LFT_SPPU_LMK_PROP_LDMUX_DAC_HIGH:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_Holdover_MUX,10);
		case LFT_SPPU_LMK_PROP_LDMUX_DAC_PLL1_N:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_Holdover_MUX,11);
		case LFT_SPPU_LMK_PROP_LDMUX_DAC_PLL1_N_BY_2:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_Holdover_MUX,12);
		case LFT_SPPU_LMK_PROP_LDMUX_DAC_PLL2_N:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_Holdover_MUX,13);
		case LFT_SPPU_LMK_PROP_LDMUX_DAC_PLL2_N_BY_2:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_Holdover_MUX,14);
		case LFT_SPPU_LMK_PROP_LDMUX_DAC_PLL1_R:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_Holdover_MUX,15);
		case LFT_SPPU_LMK_PROP_LDMUX_DAC_PLL1_R_BY_2:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_Holdover_MUX,16);
		case LFT_SPPU_LMK_PROP_LDMUX_DAC_PLL2_R:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_Holdover_MUX,17);
		case LFT_SPPU_LMK_PROP_LDMUX_DAC_PLL2_R_BY_2:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_Holdover_MUX,18);
		}


	case LFT_SPPU_LMK_PROP_XTAL_LVL:
		switch((SPPULMKXTALLVL)a_nPropValue)
		{
		case LFT_SPPU_LMK_PROP_XTAL_LVL_DATA_1:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_XTAL_LVL,0);
		case LFT_SPPU_LMK_PROP_XTAL_LVL_DATA_2:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_XTAL_LVL,1);
		case LFT_SPPU_LMK_PROP_XTAL_LVL_DATA_3: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_XTAL_LVL,2);
		case LFT_SPPU_LMK_PROP_XTAL_LVL_DATA_4:            
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_XTAL_LVL,3);

		}


	case LFT_SPPU_LMK_PROP_LOS_TIMEOUT:
		switch((SPPULMKLOSTimeout)a_nPropValue)

		{
		case LFT_SPPU_LMK_PROP_LOS_TIMEOUT_DATA_1 :    
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_En_Los,0);
		case LFT_SPPU_LMK_PROP_LOS_TIMEOUT_DATA_2 : 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_En_Los,1);
		case LFT_SPPU_LMK_PROP_LOS_TIMEOUT_DATA_3 :  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_En_Los,2);
		case LFT_SPPU_LMK_PROP_LOS_TIMEOUT_DATA_4 : 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_En_Los,3);
		};

	case LFT_SPPU_LMK_PROP_EN_LOS:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_En_Los,a_nPropValue);

	case LFT_SPPU_LMK_PROP_OSCOUT_DIVIDER:



		switch((SPPULMKPropDivider)a_nPropValue)
		{
		case LFT_SPPU_LMK_PROP_DIVIDER_2:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_OSCOUT_Divider,2);
		case LFT_SPPU_LMK_PROP_DIVIDER_3:                    
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_OSCOUT_Divider,3);
		case LFT_SPPU_LMK_PROP_DIVIDER_4:                    
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_OSCOUT_Divider,4);
		case LFT_SPPU_LMK_PROP_DIVIDER_5:                    
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_OSCOUT_Divider,5);
		case LFT_SPPU_LMK_PROP_DIVIDER_6:                    
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_OSCOUT_Divider,6);
		case LFT_SPPU_LMK_PROP_DIVIDER_7:                   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_OSCOUT_Divider,7);
		case LFT_SPPU_LMK_PROP_DIVIDER_8 :                  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_OSCOUT_Divider,0);

		}

	case LFT_SPPU_LMK_PROP_OSCOUT_OSC1_AMP:

		switch((SPPULMKPropOSCoutAmp)a_nPropValue)
		{
		case LFT_SPPU_LMK_PROP_OSCOUT_AMP_700:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_OSCOUT_OSC1_Amp,0); 
		case LFT_SPPU_LMK_PROP_OSCOUT_AMP_1200:                
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_OSCOUT_OSC1_Amp,1); 
		case LFT_SPPU_LMK_PROP_OSCOUT_AMP_1600:                       
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_OSCOUT_OSC1_Amp,2); 
		case LFT_SPPU_LMK_PROP_OSCOUT_AMP_2000:                       
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_OSCOUT_OSC1_Amp,3); 
		}


	case LFT_SPPU_LMK_PROP_OSCOUT_OSC0_TYPE:

		switch((SPPULMKPropClockType)a_nPropValue)
		{
		case LFT_SPPU_LMK_PROP_CLK_TY_OFF:                    
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_OSCOUT_OSC0_Type,0);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVDS:                 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_OSCOUT_OSC0_Type,1);

		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_700:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_OSCOUT_OSC0_Type,2);

		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1200:          
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_OSCOUT_OSC0_Type,3);

		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1600:           
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_OSCOUT_OSC0_Type,4);

		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_2000:           
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_OSCOUT_OSC0_Type,5);

		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_INV:    
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_OSCOUT_OSC0_Type,6);

		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_NORM:    
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_OSCOUT_OSC0_Type,7);

		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_NORM:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_OSCOUT_OSC0_Type,8);

		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_OSCOUT_OSC0_Type,9);

		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_NORM:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_OSCOUT_OSC0_Type,10);

		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_INV: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_OSCOUT_OSC0_Type,11);

		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_LOW:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_OSCOUT_OSC0_Type,12);

		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_LOW:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_OSCOUT_OSC0_Type,13);

		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_LOW:    
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_OSCOUT_OSC0_Type,14);
		}




	case LFT_SPPU_LMK_PROP_OSCOUT_OSC0_MUX:
		switch((SPPULMKPropOSCoutMux)a_nPropValue)
		{
		case LFT_SPPU_LMK_PROP_OSCOUT_MUX_BYPASS_DIVIDER:              
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_OSCOUT_OSC0_Mux,0);
		case LFT_SPPU_LMK_PROP_OSCOUT_MUX_DIVIDE:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_OSCOUT_OSC0_Mux,1);
		}
	case LFT_SPPU_LMK_PROP_OSCOUT_OSC1_MUX:
		switch((SPPULMKPropOSCoutMux)a_nPropValue)
		{
		case LFT_SPPU_LMK_PROP_OSCOUT_MUX_BYPASS_DIVIDER:              
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_OSCOUT_OSC1_Mux,0);
		case LFT_SPPU_LMK_PROP_OSCOUT_MUX_DIVIDE:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_OSCOUT_OSC1_Mux,1);
		}

	case LFT_SPPU_LMK_PROP_OSCOUT_EN_CLKIN0:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_OSCOUT_ENABLE_OSCout0 ,a_nPropValue);
	case LFT_SPPU_LMK_PROP_OSCOUT_EN_CLKIN1:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_OSCOUT_ENABLE_OSCout1,a_nPropValue);
	case LFT_SPPU_LMK_PROP_OSCOUT_SWITCH_OFF:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_OSCOUT_Swich_off,a_nPropValue);



		/***********************************************************general tab end here**********************************************************************/


	case  LFT_SPPU_LMK_PROP_CLK_01_DIVIDER: 
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_divider,a_nPropValue);
	case LFT_SPPU_LMK_PROP_CLK_01_DELAY:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_digdelay,a_nPropValue);
	case LFT_SPPU_LMK_PROP_CLK_01_CLK0_TYPE :
		switch((SPPULMKPropClockType)a_nPropValue)
		{
		case LFT_SPPU_LMK_PROP_CLK_TY_OFF:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLKout0_TYPE,0);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVDS:                   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLKout0_TYPE,1);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_700:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLKout0_TYPE,2);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1200:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLKout0_TYPE,3);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1600: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLKout0_TYPE,4);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_2000:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLKout0_TYPE,5);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_INV:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLKout0_TYPE,6);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_NORM:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLKout0_TYPE,7);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_NORM: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLKout0_TYPE,8);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLKout0_TYPE,9);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_NORM:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLKout0_TYPE,10);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLKout0_TYPE,11);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_LOW:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLKout0_TYPE,12);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_LOW :     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLKout0_TYPE,13);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_LOW:      
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLKout0_TYPE,14);
		} 

	case LFT_SPPU_LMK_PROP_CLK_01_CLK1_TYPE:
		switch((SPPULMKPropClockType)a_nPropValue)
		{
		case LFT_SPPU_LMK_PROP_CLK_TY_OFF:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLK1out1_TYPE,0);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVDS:                   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLK1out1_TYPE,1);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_700:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLK1out1_TYPE,2);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1200:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLK1out1_TYPE,3);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1600: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLK1out1_TYPE,4);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_2000:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLK1out1_TYPE,5);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_INV:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLK1out1_TYPE,6);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_NORM:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLK1out1_TYPE,7);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_NORM: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLK1out1_TYPE,8);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLK1out1_TYPE,9);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_NORM:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLK1out1_TYPE,10);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLK1out1_TYPE,11);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_LOW:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLK1out1_TYPE,12);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_LOW :     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLK1out1_TYPE,13);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_LOW:      
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLK1out1_TYPE,14);
		}

	case LFT_SPPU_LMK_PROP_CLK_01_ANALOG_DELAY:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_AnalogDelay,a_nPropValue);
	case LFT_SPPU_LMK_PROP_CLK_01_ANALOG_DELAY_SEL:
		switch((SPPUAnalogDelaySel)a_nPropValue)
		{
		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_OFF:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_AnalogDelay_sel,0);
		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_ODD_CLK_ONLY:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_AnalogDelay_sel,1);
		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_EVEN_CLK_ONLY:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_AnalogDelay_sel,2);
		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_BOTH_CLKS :		
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_AnalogDelay_sel,3);
		}
	case LFT_SPPU_LMK_PROP_CLK_01_DD_HALF_SHIFT:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_DD_hlfshft,a_nPropValue);
	case LFT_SPPU_LMK_PROP_CLK_01_SWITCH_OFF:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806, LFT_SPPU_LMK_CLK0_CLK1_switch_off_pd,a_nPropValue);

	case LFT_SPPU_LMK_PROP_CLK_23_DIVIDER:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_divider,a_nPropValue);
	case LFT_SPPU_LMK_PROP_CLK_23_DELAY :
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_digdelay,a_nPropValue);
	case LFT_SPPU_LMK_PROP_CLK_23_CLK0_TYPE:
		switch((SPPULMKPropClockType)a_nPropValue)
		{
		case LFT_SPPU_LMK_PROP_CLK_TY_OFF:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLKout2_TYPE,0);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVDS:                   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLKout2_TYPE,1);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_700:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLKout2_TYPE,2);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1200:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLKout2_TYPE,3);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1600: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLKout2_TYPE,4);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_2000:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLKout2_TYPE,5);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_INV:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLKout2_TYPE,6);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_NORM:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLKout2_TYPE,7);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_NORM: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLKout2_TYPE,8);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLKout2_TYPE,9);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_NORM:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLKout2_TYPE,10);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLKout2_TYPE,11);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_LOW:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLKout2_TYPE,12);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_LOW :     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLKout2_TYPE,13);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_LOW:      
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLKout2_TYPE,14);
		}

	case LFT_SPPU_LMK_PROP_CLK_23_CLK1_TYPE:
		switch((SPPULMKPropClockType)a_nPropValue)
		{
		case LFT_SPPU_LMK_PROP_CLK_TY_OFF:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLK1out3_TYPE,0);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVDS:                   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLK1out3_TYPE,1);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_700:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLK1out3_TYPE,2);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1200:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLK1out3_TYPE,3);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1600: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLK1out3_TYPE,4);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_2000:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLK1out3_TYPE,5);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_INV:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLK1out3_TYPE,6);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_NORM:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLK1out3_TYPE,7);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_NORM: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLK1out3_TYPE,8);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLK1out3_TYPE,9);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_NORM:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLK1out3_TYPE,10);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLK1out3_TYPE,11);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_LOW:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLK1out3_TYPE,12);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_LOW :     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLK1out3_TYPE,13);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_LOW:      
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLK1out3_TYPE,14);
		}
	case LFT_SPPU_LMK_PROP_CLK_23_ANALOG_DELAY:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_AnalogDelay,a_nPropValue);

	case LFT_SPPU_LMK_PROP_CLK_23_ANALOG_DELAY_SEL:
		switch((SPPUAnalogDelaySel)a_nPropValue)
		{
		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_OFF:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_AnalogDelay_sel,0);
		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_ODD_CLK_ONLY :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_AnalogDelay_sel,1);
		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_EVEN_CLK_ONLY :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_AnalogDelay_sel,2);
		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_BOTH_CLKS :		
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_AnalogDelay_sel,3);
		}
	case LFT_SPPU_LMK_PROP_CLK_23_DD_HALF_SHIFT:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_DD_hlfshft,a_nPropValue);
	case LFT_SPPU_LMK_PROP_CLK_23_SWITCH_OFF:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806, LFT_SPPU_LMK_CLK2_CLK3_switch_off_pd,a_nPropValue);
	case LFT_SPPU_LMK_PROP_CLK_45_DIVIDER :
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_divider,a_nPropValue);
	case LFT_SPPU_LMK_PROP_CLK_45_DELAY:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_digdelay,a_nPropValue);
	case LFT_SPPU_LMK_PROP_CLK_45_CLK0_TYPE:
		switch((SPPULMKPropClockType)a_nPropValue)
		{
		case LFT_SPPU_LMK_PROP_CLK_TY_OFF:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,0);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVDS:                   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,1);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_700:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,2);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1200:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,3);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1600: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,4);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_2000:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,5);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_INV:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,6);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_NORM:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,7);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_NORM: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,8);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,9);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_NORM:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,10);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,11);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_LOW:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,12);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_LOW :     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,13);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_LOW:      
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,14);
		}
	case LFT_SPPU_LMK_PROP_CLK_45_CLK1_TYPE:
		switch((SPPULMKPropClockType)a_nPropValue)
		{

		case LFT_SPPU_LMK_PROP_CLK_TY_OFF:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLK1out5_TYPE,0);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVDS:                   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,1);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_700:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,2);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1200:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,3);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1600: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,4);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_2000:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,5);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_INV:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,6);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_NORM:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,7);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_NORM: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,8);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,9);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_NORM:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,10);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,11);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_LOW:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,12);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_LOW :     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,13);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_LOW:      
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,14);
		}
	case LFT_SPPU_LMK_PROP_CLK_45_ANALOG_DELAY:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_AnalogDelay,a_nPropValue);
	case LFT_SPPU_LMK_PROP_CLK_45_ANALOG_DELAY_SEL:
		switch((SPPUAnalogDelaySel)a_nPropValue)
		{
		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_OFF:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_AnalogDelay_sel,0);
		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_ODD_CLK_ONLY :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_AnalogDelay_sel,1);
		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_EVEN_CLK_ONLY :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_AnalogDelay_sel,2);
		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_BOTH_CLKS :		
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_AnalogDelay_sel,3);
		}


	case LFT_SPPU_LMK_PROP_CLK_45_DD_HALF_SHIFT:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_DD_hlfshft,a_nPropValue);
	case LFT_SPPU_LMK_PROP_CLK_45_SWITCH_OFF:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806, LFT_SPPU_LMK_CLK4_CLK5_switch_off_pd,a_nPropValue);
	case LFT_SPPU_LMK_PROP_CLK_67_DIVIDER:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_divider,a_nPropValue);

	case LFT_SPPU_LMK_PROP_CLK_67_DELAY: 
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_digdelay,a_nPropValue);

	case LFT_SPPU_LMK_PROP_CLK_67_CLK0_TYPE:
		switch((SPPULMKPropClockType)a_nPropValue)
		{

		case LFT_SPPU_LMK_PROP_CLK_TY_OFF:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLKout6_TYPE,0);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVDS:                   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLKout6_TYPE,1);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_700:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLKout6_TYPE,2);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1200:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLKout6_TYPE,3);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1600: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLKout6_TYPE,4);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_2000:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLKout6_TYPE,5);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_INV:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLKout6_TYPE,6);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_NORM:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLKout6_TYPE,7);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_NORM: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLKout6_TYPE,8);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLKout6_TYPE,9);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_NORM:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLKout6_TYPE,10);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLKout6_TYPE,11);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_LOW:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLKout6_TYPE,12);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_LOW :     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLKout6_TYPE,13);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_LOW:      
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLKout6_TYPE,14);
		}


	case LFT_SPPU_LMK_PROP_CLK_67_CLK1_TYPE:
		switch((SPPULMKPropClockType)a_nPropValue)
		{

		case LFT_SPPU_LMK_PROP_CLK_TY_OFF:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLK1out7_TYPE,0);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVDS:                   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLK1out7_TYPE,1);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_700:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLK1out7_TYPE,2);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1200:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLK1out7_TYPE,3);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1600: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLK1out7_TYPE,4);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_2000:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLK1out7_TYPE,5);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_INV:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLK1out7_TYPE,6);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_NORM:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLK1out7_TYPE,7);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_NORM: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLK1out7_TYPE,8);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLK1out7_TYPE,9);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_NORM:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLK1out7_TYPE,10);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLK1out7_TYPE,11);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_LOW:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLK1out7_TYPE,12);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_LOW :     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLK1out7_TYPE,13);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_LOW:      
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLK1out7_TYPE,14);
		}


	case LFT_SPPU_LMK_PROP_CLK_67_ANALOG_DELAY:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_AnalogDelay,a_nPropValue);
	case LFT_SPPU_LMK_PROP_CLK_67_ANALOG_DELAY_SEL:
		switch((SPPUAnalogDelaySel)a_nPropValue)
		{
		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_OFF:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_AnalogDelay_sel,0);
		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_ODD_CLK_ONLY: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_AnalogDelay_sel,1);
		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_EVEN_CLK_ONLY :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_AnalogDelay_sel,2);
		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_BOTH_CLKS :		
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_AnalogDelay_sel,3);
		}
	case LFT_SPPU_LMK_PROP_CLK_67_DD_HALF_SHIFT:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_DD_hlfshft,a_nPropValue);
	case LFT_SPPU_LMK_PROP_CLK_67_SWITCH_OFF:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806, LFT_SPPU_LMK_CLK6_CLK7_switch_off_pd,a_nPropValue);

	case LFT_SPPU_LMK_PROP_CLK_89_DIVIDER:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_divider,a_nPropValue);
	case LFT_SPPU_LMK_PROP_CLK_89_DELAY:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_digdelay,a_nPropValue);
	case LFT_SPPU_LMK_PROP_CLK_89_CLK0_TYPE:
		switch((SPPULMKPropClockType)a_nPropValue)
		{

		case LFT_SPPU_LMK_PROP_CLK_TY_OFF:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLKout8_TYPE,0);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVDS:                   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLKout8_TYPE,1);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_700:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLKout8_TYPE,2);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1200:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLKout8_TYPE,3);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1600: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLKout8_TYPE,4);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_2000:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLKout8_TYPE,5);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_INV:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLKout8_TYPE,6);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_NORM:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLKout8_TYPE,7);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_NORM: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLKout8_TYPE,8);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLKout8_TYPE,9);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_NORM:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLKout8_TYPE,10);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLKout8_TYPE,11);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_LOW:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLKout8_TYPE,12);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_LOW :     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLKout8_TYPE,13);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_LOW:      
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLKout8_TYPE,14);
		}

	case LFT_SPPU_LMK_PROP_CLK_89_CLK1_TYPE:
		switch((SPPULMKPropClockType)a_nPropValue)
		{

		case LFT_SPPU_LMK_PROP_CLK_TY_OFF:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLK1out9_TYPE,0);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVDS:                   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLK1out9_TYPE,1);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_700:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLK1out9_TYPE,2);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1200:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLK1out9_TYPE,3);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1600: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLK1out9_TYPE,4);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_2000:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLK1out9_TYPE,5);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_INV:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLK1out9_TYPE,6);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_NORM:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLK1out9_TYPE,7);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_NORM: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLK1out9_TYPE,8);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLK1out9_TYPE,9);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_NORM:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLK1out9_TYPE,10);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLK1out9_TYPE,11);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_LOW:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLK1out9_TYPE,12);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_LOW :     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLK1out9_TYPE,13);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_LOW:      
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLK1out9_TYPE,14);
		}

	case LFT_SPPU_LMK_PROP_CLK_89_ANALOG_DELAY:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_AnalogDelay,a_nPropValue);




	case LFT_SPPU_LMK_PROP_CLK_89_ANALOG_DELAY_SEL:
		switch((SPPUAnalogDelaySel)a_nPropValue)
		{
		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_OFF:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_AnalogDelay_sel,0);
		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_ODD_CLK_ONLY: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_AnalogDelay_sel,1);
		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_EVEN_CLK_ONLY :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_AnalogDelay_sel,2);
		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_BOTH_CLKS :		
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_AnalogDelay_sel,3);
		}

	case LFT_SPPU_LMK_PROP_CLK_89_DD_HALF_SHIFT:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_DD_hlfshft,a_nPropValue);
	case LFT_SPPU_LMK_PROP_CLK_89_SWITCH_OFF:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806, LFT_SPPU_LMK_CLK8_CLK9_switch_off_pd,a_nPropValue);

	case LFT_SPPU_LMK_PROP_CLK_1011_DIVIDER :
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_divider,a_nPropValue);
	case LFT_SPPU_LMK_PROP_CLK_1011_DELAY:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_digdelay,a_nPropValue);


	case LFT_SPPU_LMK_PROP_CLK_1011_CLK0_TYPE:
		switch((SPPULMKPropClockType)a_nPropValue)
		{

		case LFT_SPPU_LMK_PROP_CLK_TY_OFF:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLKout0_TYPE,0);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVDS:                   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLKout0_TYPE,1);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_700:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLKout0_TYPE,2);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1200:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLKout0_TYPE,3);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1600: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLKout0_TYPE,4);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_2000:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLKout0_TYPE,5);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_INV:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLKout0_TYPE,6);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_NORM:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLKout0_TYPE,7);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_NORM: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLKout0_TYPE,8);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLKout0_TYPE,9);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_NORM:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLKout0_TYPE,10);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLKout0_TYPE,11);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_LOW:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLKout0_TYPE,12);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_LOW :     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLKout0_TYPE,13);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_LOW:      
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLKout0_TYPE,14);
		}
	case LFT_SPPU_LMK_PROP_CLK_1011_CLK1_TYPE:
		switch((SPPULMKPropClockType)a_nPropValue)
		{

		case LFT_SPPU_LMK_PROP_CLK_TY_OFF:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLK1out1_TYPE,0);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVDS:                   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLK1out1_TYPE,1);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_700:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLK1out1_TYPE,2);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1200:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLK1out1_TYPE,3);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1600: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLK1out1_TYPE,4);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_2000:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLK1out1_TYPE,5);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_INV:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLK1out1_TYPE,6);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_NORM:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLK1out1_TYPE,7);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_NORM: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLK1out1_TYPE,8);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLK1out1_TYPE,9);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_NORM:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLK1out1_TYPE,10);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLK1out1_TYPE,11);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_LOW:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLK1out1_TYPE,12);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_LOW :     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLK1out1_TYPE,13);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_LOW:      
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLK1out1_TYPE,14);
		}
	case LFT_SPPU_LMK_PROP_CLK_1011_ANALOG_DELAY:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_AnalogDelay,a_nPropValue);

	case LFT_SPPU_LMK_PROP_CLK_1011_ANALOG_DELAY_SEL:
		switch((SPPUAnalogDelaySel)a_nPropValue)
		{

		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_OFF:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_AnalogDelay_sel,0);
		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_ODD_CLK_ONLY:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_AnalogDelay_sel,1);
		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_EVEN_CLK_ONLY:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_AnalogDelay_sel,2);
		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_BOTH_CLKS :		
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_AnalogDelay_sel,3);
		}

	case LFT_SPPU_LMK_PROP_CLK_1011_DD_HALF_SHIFT:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_DD_hlfshft,a_nPropValue);
	case LFT_SPPU_LMK_PROP_CLK_1011_SWITCH_OFF:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806, LFT_SPPU_LMK_CLK10_CLK11_switch_off_pd,a_nPropValue);

	case LFT_SPPU_LMK_PROP_PLL_EN_CLKIN0:
		switch((SPPUState)a_nPropValue)
		{
		case  LFT_SPPU_STATE_DISABLE:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_En_CLKin0,a_nPropValue);
		case  LFT_SPPU_STATE_ENABLE:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_En_CLKin1,a_nPropValue);
		}

	case LFT_SPPU_LMK_PROP_PLL_EN_CLKIN1:
		switch((SPPUState)a_nPropValue)
		{
		case  LFT_SPPU_STATE_DISABLE:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_En_CLKin1,0);
		case  LFT_SPPU_STATE_ENABLE:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_En_CLKin1,1);
		}


	case LFT_SPPU_LMK_PROP_PLL_CLIN_SEL_INV:

		switch((SPPULMKPropState)a_nPropValue)
		{
		case LFT_SPPU_LMK_PROP_ACTIVE_LOW:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLKIN_sel_INV,0);
		case LFT_SPPU_LMK_PROP_ACTIVE_HIGH: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLKIN_sel_INV,1);
		}
	case LFT_SPPU_LMK_PROP_PLL_CLKIN_SEL_MODE:
		switch((SPPULMKPropClockInSelMode)a_nPropValue)
		{		
		case LFT_SPPU_LMK_PROP_CLK_SEL_MODE_CLK_IN_0:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLKIN_SEL_Mode,0);
		case LFT_SPPU_LMK_PROP_CLK_SEL_MODE_CLK_IN_1:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLKIN_SEL_Mode,1);
		case LFT_SPPU_LMK_PROP_CLK_SEL_MODE_PIN_SEL_MODE:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLKIN_SEL_Mode,3);
		case LFT_SPPU_LMK_PROP_CLK_SEL_MODE_AUTO_MODE:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLKIN_SEL_Mode,4);
		case LFT_SPPU_LMK_PROP_CLK_SEL_MODE_AUTO_MODE_NXT_PIN:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLKIN_SEL_Mode,6);
		}

	case LFT_SPPU_LMK_PROP_PLL_CLIN0_MUX:
		switch((SPPULMKPropClockInMux)a_nPropValue)
		{	
		case  LFT_SPPU_LMK_PROP_CLK_MUX_LOGIC_LOW: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLKIN0_MUX,0);
		case  LFT_SPPU_LMK_PROP_CLK_MUX_CLK_IN_0LOS:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLKIN0_MUX,1);
		case  LFT_SPPU_LMK_PROP_CLK_MUX_CLK_IN_0_SELECTED: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLKIN0_MUX,2);
		case  LFT_SPPU_LMK_PROP_CLK_MUX_DAC_LOCKED:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLKIN0_MUX,3);
		case  LFT_SPPU_LMK_PROP_CLK_MUX_DAC_LOW:               
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLKIN0_MUX,4);
		case  LFT_SPPU_LMK_PROP_CLK_MUX_DAC_HIGH: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLKIN0_MUX,5);
		case  LFT_SPPU_LMK_PROP_CLK_MUX_UWIRE_READBACK:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLKIN0_MUX,6);
		}
	case LFT_SPPU_LMK_PROP_PLL_CLIN1_MUX:
		switch((SPPULMKPropClockInMux)a_nPropValue)
		{	
		case  LFT_SPPU_LMK_PROP_CLK_MUX_LOGIC_LOW: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLKIN1_MUX,0);
		case  LFT_SPPU_LMK_PROP_CLK_MUX_CLK_IN_0LOS:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLKIN1_MUX,1);
		case  LFT_SPPU_LMK_PROP_CLK_MUX_CLK_IN_0_SELECTED: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLKIN1_MUX,2);
		case  LFT_SPPU_LMK_PROP_CLK_MUX_DAC_LOCKED:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLKIN1_MUX,3);
		case  LFT_SPPU_LMK_PROP_CLK_MUX_DAC_LOW:               
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLKIN1_MUX,4);
		case  LFT_SPPU_LMK_PROP_CLK_MUX_DAC_HIGH: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLKIN1_MUX,5);
		case  LFT_SPPU_LMK_PROP_CLK_MUX_UWIRE_READBACK:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLKIN1_MUX,6);
		}  
	case LFT_SPPU_LMK_PROP_PLL_CLKIN0_TYPE:
		switch((SPPULMKPropType)a_nPropValue)
		{
		case LFT_SPPU_LMK_PROP_INPUT:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLKIN0_TYPE,0);
		case LFT_SPPU_LMK_PROP_INPUT_W_PULLUP_RESISTOR:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLKIN0_TYPE,1);
		case LFT_SPPU_LMK_PROP_INPUT_W_PULLDOWN_RESISTOR:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLKIN0_TYPE,2);
		case LFT_SPPU_LMK_PROP_OUTPUT:                      
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLKIN0_TYPE,3);
		case LFT_SPPU_LMK_PROP_OUTPUT_INVERTED:             
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLKIN0_TYPE,4);
		case LFT_SPPU_LMK_PROP_OUTPUT_OPEN_SOURCE:          
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLKIN0_TYPE,5);
		case LFT_SPPU_LMK_PROP_OPEN_DRAIN:                  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLKIN0_TYPE,6);
		}
	case LFT_SPPU_LMK_PROP_PLL_CKLIN0_TYPE_2:
		switch((SPPULMKPropType)a_nPropValue)
		{
		case LFT_SPPU_LMK_PROP_INPUT:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLKIN1_TYPE,0);
		case LFT_SPPU_LMK_PROP_INPUT_W_PULLUP_RESISTOR:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLKIN1_TYPE,1);
		case LFT_SPPU_LMK_PROP_INPUT_W_PULLDOWN_RESISTOR:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLKIN1_TYPE,2);
		case LFT_SPPU_LMK_PROP_OUTPUT:                      
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLKIN1_TYPE,3);
		case LFT_SPPU_LMK_PROP_OUTPUT_INVERTED:             
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLKIN1_TYPE,4);
		case LFT_SPPU_LMK_PROP_OUTPUT_OPEN_SOURCE:          
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLKIN1_TYPE,5);
		case LFT_SPPU_LMK_PROP_OPEN_DRAIN:                  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLKIN1_TYPE,6);
		}

	case LFT_SPPU_LMK_PROP_PLL_BUF_TYPE0:
		switch((SPPULMKPropBufType)a_nPropValue)
		{
		case LFT_SPPU_LMK_PROP_BUFF_TYPE_BIPOLAR :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLK0BUF_TYPE0  ,0);

		case LFT_SPPU_LMK_PROP_BUFF_TYPE_CMOS:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLK0BUF_TYPE0  ,1);

		};

	case LFT_SPPU_LMK_PROP_PLL_BUF_TYPE1:

		switch((SPPULMKPropBufType)a_nPropValue)
		{
		case LFT_SPPU_LMK_PROP_BUFF_TYPE_BIPOLAR :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLK1BUF_TYPE1  ,0);

		case LFT_SPPU_LMK_PROP_BUFF_TYPE_CMOS:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLK1BUF_TYPE1  ,1);

		};


	case LFT_SPPU_LMK_PROP_PLL_CLKIN0_DIV:
		switch( (SPPULMKPropClockInDiv)a_nPropValue)
		{
		case   LFT_SPPU_LMK_PROP_CLK_IN_DIV_1 :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLKIN0_Div,0);
		case   LFT_SPPU_LMK_PROP_CLK_IN_DIV_2 :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLKIN0_Div,1);
		case   LFT_SPPU_LMK_PROP_CLK_IN_DIV_4:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLKIN0_Div,2);
		case   LFT_SPPU_LMK_PROP_CLK_IN_DIV_8 :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLKIN0_Div,3);
		};

	case LFT_SPPU_LMK_PROP_PLL_CLKIN1_DIV:
		switch( (SPPULMKPropClockInDiv)a_nPropValue)
		{
		case   LFT_SPPU_LMK_PROP_CLK_IN_DIV_1 :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLK1N1_Div ,0);
		case   LFT_SPPU_LMK_PROP_CLK_IN_DIV_2 :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLK1N1_Div ,1);
		case   LFT_SPPU_LMK_PROP_CLK_IN_DIV_4:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLK1N1_Div,2);
		case   LFT_SPPU_LMK_PROP_CLK_IN_DIV_8 :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLK1N1_Div,3);
		};
	case LFT_SPPU_LMK_PROP_PLL_WND_SIZE:
		switch((SPPULMKPropPLLWNDSize)a_nPropValue)
		{

		case LFT_SPPU_LMK_PROP_PLL_WND_SZ_DATA1 :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806, LFT_SPPU_LMK_PLL1_wind_size,0);
		case  LFT_SPPU_LMK_PROP_PLL_WND_SZ_DATA2 :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806, LFT_SPPU_LMK_PLL1_wind_size,1);
		case LFT_SPPU_LMK_PROP_PLL_WND_SZ_DATA3:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806, LFT_SPPU_LMK_PLL1_wind_size,2);
		case LFT_SPPU_LMK_PROP_PLL_WND_SZ_DATA4  :                
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806, LFT_SPPU_LMK_PLL1_wind_size,3);
		}
	case LFT_SPPU_LMK_PROP_PLL_R_DLY:
		switch((SPPULMKPropPLLDLY)a_nPropValue)
		{
		case LFT_SPPU_LMK_PROP_PLL_DLY_0 :   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_R_DLY,0);
		case LFT_SPPU_LMK_PROP_PLL_DLY_205 :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_R_DLY,1);
		case LFT_SPPU_LMK_PROP_PLL_DLY_410  :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_R_DLY,2);
		case LFT_SPPU_LMK_PROP_PLL_DLY_615   :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_R_DLY,3);
		case LFT_SPPU_LMK_PROP_PLL_DLY_820  :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_R_DLY,4);
		case LFT_SPPU_LMK_PROP_PLL_DLY_1025 :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_R_DLY,5);
		case LFT_SPPU_LMK_PROP_PLL_DLY_1230 :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_R_DLY,6);
		case LFT_SPPU_LMK_PROP_PLL_DLY_1485:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_R_DLY,7);
		};

	case LFT_SPPU_LMK_PROP_PLL_N_DLY2:
		switch((SPPULMKPropPLLDLY)a_nPropValue)
		{
		case LFT_SPPU_LMK_PROP_PLL_DLY_0 :   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_N_DLY_2   ,0);
		case LFT_SPPU_LMK_PROP_PLL_DLY_205 :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_N_DLY_2   ,1);
		case LFT_SPPU_LMK_PROP_PLL_DLY_410  :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_N_DLY_2   ,2);
		case LFT_SPPU_LMK_PROP_PLL_DLY_615   :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_N_DLY_2   ,3);
		case LFT_SPPU_LMK_PROP_PLL_DLY_820  :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_N_DLY_2   ,4);
		case LFT_SPPU_LMK_PROP_PLL_DLY_1025 :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_N_DLY_2   ,5);
		case LFT_SPPU_LMK_PROP_PLL_DLY_1230 :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_N_DLY_2   ,6);
		case LFT_SPPU_LMK_PROP_PLL_DLY_1485:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_N_DLY_2   ,7);
		};
	case LFT_SPPU_LMK_PROP_PLL_DLD_CNT:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_DLD_CNT ,a_nPropValue);
	case  LFT_SPPU_LMK_PROP_PLL_SYNC_DLD:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_SYNC_DLD,a_nPropValue);
	case LFT_SPPU_LMK_PROP_PLL_REF_DIVIDER:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_REF_Divider,a_nPropValue);
	case LFT_SPPU_LMK_PROP_PLL_N_DIVIDER:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_N_Divider ,a_nPropValue);
	case LFT_SPPU_LMK_PROP_PLL_CHARGE_PUMP_STATE:
		switch((SPPULMKPropChargePumpState)a_nPropValue)
		{
		case  LFT_SPPU_LMK_PROP_CPS_ACTIVE :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_ChargePump_state ,0);
		case LFT_SPPU_LMK_PROP_CPS_TRISTATE :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_ChargePump_state ,1);
		}
	case LFT_SPPU_LMK_PROP_PLL_CHARGE_PUMP_GAIN:
		switch((SPPULMKPropChargePumpGain)a_nPropValue)
		{
		case LFT_SPPU_LMK_PROP_CPG_100 :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_ChargePump_Gain,0);
		case LFT_SPPU_LMK_PROP_CPG_200:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_ChargePump_Gain,1);
		case LFT_SPPU_LMK_PROP_CPG_400 :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_ChargePump_Gain,2);
		case LFT_SPPU_LMK_PROP_CPG_1600 :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_ChargePump_Gain,3);
		};


	case LFT_SPPU_LMK_PROP_PLL_CHARGE_PUMP_POLARITY:
		switch(( SPPULMKPropChargePumpPolarity)a_nPropValue)

		{
		case LFT_SPPU_LMK_PROP_CPP_NEGATIVE_SLOPE  :   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806, LFT_SPPU_LMK_PLL1_ChargePump_polarity ,a_nPropValue);
		case LFT_SPPU_LMK_PROP_CPP_POSITIVE_SLOPE     :  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806, LFT_SPPU_LMK_PLL1_ChargePump_polarity ,a_nPropValue);
		}


	case LFT_SPPU_LMK_PROP_PLL2_XTAL_OCS : 
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_XTAL_OSC  ,a_nPropValue);
	case LFT_SPPU_LMK_PROP_PLL2_SYNC_DLD :            
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806, LFT_SPPU_LMK_PLL2_SYNC_DLD  ,a_nPropValue);
	case LFT_SPPU_LMK_PROP_PLL2_DLD_CNT :            
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806, LFT_SPPU_LMK_PLL12_DLD_CNT ,a_nPropValue);
	case LFT_SPPU_LMK_PROP_PLL2_WND_SIZE: 
		switch((SPPULMKPropPLLWNDSize2)a_nPropValue)
		{
		case LFT_SPPU_LMK_PROP_PLL_WND_SZ2_DATA1  :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806, LFT_SPPU_LMK_PLL2_PLL_WIND_SIZE ,a_nPropValue); 
		}
	case LFT_SPPU_LMK_PROP_PLL2_REF_DIVIDER:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_REF_DIVIER,a_nPropValue);
	case LFT_SPPU_LMK_PROP_PLL2_N_CAL :
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_N_CALL ,a_nPropValue);
	case LFT_SPPU_LMK_PROP_PLL2_N_DIVIDER :
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806, LFT_SPPU_LMK_PLL2_N_DIVIDER ,a_nPropValue);
	case LFT_SPPU_LMK_PROP_PLL2_PRESCALAR :
		switch((SPPULMKPropDivider)a_nPropValue)

		{
		case  LFT_SPPU_LMK_PROP_DIVIDER_2:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_PRESCALAR ,2);
		case LFT_SPPU_LMK_PROP_DIVIDER_3:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_PRESCALAR ,3);
		case LFT_SPPU_LMK_PROP_DIVIDER_4:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_PRESCALAR ,4);
		case LFT_SPPU_LMK_PROP_DIVIDER_5:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_PRESCALAR ,5);
		case LFT_SPPU_LMK_PROP_DIVIDER_6:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_PRESCALAR ,6);
		case LFT_SPPU_LMK_PROP_DIVIDER_7 :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_PRESCALAR ,7);
		case LFT_SPPU_LMK_PROP_DIVIDER_8 :                     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_PRESCALAR ,0);  // doubt
		}

	case LFT_SPPU_LMK_PROP_PLL2_INPUT_FREQ  :
		switch(( SPPULMKPropInputFreq)a_nPropValue)
		{
		case LFT_SPPU_LMK_PROP_PLL2_INPUT_FREQ_DATA1:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_INPUT_FREQ  ,0);
		case LFT_SPPU_LMK_PROP_PLL2_INPUT_FREQ_DATA2     :         
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_INPUT_FREQ  ,1);
		case LFT_SPPU_LMK_PROP_PLL2_INPUT_FREQ_DATA3         :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_INPUT_FREQ  ,2);
		case LFT_SPPU_LMK_PROP_PLL2_INPUT_FREQ_DATA4             :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_INPUT_FREQ  ,4);
		};

	case LFT_SPPU_LMK_PROP_PLL2_2X_REF  :
		switch(( SPPULMKProp2XREF)a_nPropValue)
		{
		case    LFT_SPPU_LMK_PROP_PLL2_2X_REF_FREQUENCY_NORMAL :     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,  LFT_SPPU_LMK_PLL2_2X_REF  ,0);
		case    LFT_SPPU_LMK_PROP_PLL2_2X_REF_FREQUENCY_DOUBLED       :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,  LFT_SPPU_LMK_PLL2_2X_REF  ,1);
		};


	case LFT_SPPU_LMK_PROP_PLL2_FAST_PDF            :
		switch((SPPULMKPropPLL2FASTPDF)a_nPropValue)
		{
		case    LFT_SPPU_LMK_PROP_PLL2_FAST_PDF_LESS_THAN_EQ_100:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,  LFT_SPPU_LMK_PLL2_PLL2_FAST_PDF,0);
		case   LFT_SPPU_LMK_PROP_PLL2_FAST_PDF_GREATER_THAN_100:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,  LFT_SPPU_LMK_PLL2_PLL2_FAST_PDF,1);
		};

	case LFT_SPPU_LMK_PROP_PLL2_R3 :
		switch((SPPULMKPropResistance)a_nPropValue)
		{
		case LFT_SPPU_LMK_PROP_RESISTANCE_200_OHMS :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,  LFT_SPPU_LMK_PLL2_LOOP_FILTER_R3 ,0);
		case LFT_SPPU_LMK_PROP_RESISTANCE_1K_OHMS               :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,  LFT_SPPU_LMK_PLL2_LOOP_FILTER_R3 ,1);
		case LFT_SPPU_LMK_PROP_RESISTANCE_2K_OHMS:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,  LFT_SPPU_LMK_PLL2_LOOP_FILTER_R3 ,2);
		case LFT_SPPU_LMK_PROP_RESISTANCE_4K_OHMS:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,  LFT_SPPU_LMK_PLL2_LOOP_FILTER_R3 ,3);
		case LFT_SPPU_LMK_PROP_RESISTANCE_16K_OHMS:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,  LFT_SPPU_LMK_PLL2_LOOP_FILTER_R3 ,4);
		};

	case LFT_SPPU_LMK_PROP_PLL2_C3:
		switch  ((SPPULMKPropCapacitance3)a_nPropValue)
		{
		case LFT_SPPU_LMK_PROP_CAPACITANCE3_10_PF:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C3  ,0);
		case  LFT_SPPU_LMK_PROP_CAPACITANCE3_11_PF:       
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C3  ,1);
		case  LFT_SPPU_LMK_PROP_CAPACITANCE3_15_PF:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C3  ,2);
		case LFT_SPPU_LMK_PROP_CAPACITANCE3_16_PF:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C3  ,3);
		case LFT_SPPU_LMK_PROP_CAPACITANCE3_19_PF:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C3  ,4);

		case LFT_SPPU_LMK_PROP_CAPACITANCE3_20_PF :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C3  ,5);
		case LFT_SPPU_LMK_PROP_CAPACITANCE3_24_PF :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C3  ,6);
		case LFT_SPPU_LMK_PROP_CAPACITANCE3_25_PF :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C3 ,7);
		case LFT_SPPU_LMK_PROP_CAPACITANCE3_29_PF :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C3  ,8);
		case LFT_SPPU_LMK_PROP_CAPACITANCE3_30_PF :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C3  ,9);
		case LFT_SPPU_LMK_PROP_CAPACITANCE3_33_PF :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C3  ,10);
		case LFT_SPPU_LMK_PROP_CAPACITANCE3_34_PF :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C3  ,11);
		case LFT_SPPU_LMK_PROP_CAPACITANCE3_38_PF :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C3  ,12);
		case LFT_SPPU_LMK_PROP_CAPACITANCE3_39_PF:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C3  ,13);
		};
	case LFT_SPPU_LMK_PROP_PLL2_R4:
		switch((SPPULMKPropResistance)a_nPropValue)
		{
		case LFT_SPPU_LMK_PROP_RESISTANCE_200_OHMS:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,  LFT_SPPU_LMK_PLL2_LOOP_FILTER_R4 ,0);
		case LFT_SPPU_LMK_PROP_RESISTANCE_1K_OHMS:               
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,  LFT_SPPU_LMK_PLL2_LOOP_FILTER_R4 ,1);
		case LFT_SPPU_LMK_PROP_RESISTANCE_2K_OHMS:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,  LFT_SPPU_LMK_PLL2_LOOP_FILTER_R4 ,2);
		case LFT_SPPU_LMK_PROP_RESISTANCE_4K_OHMS:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,  LFT_SPPU_LMK_PLL2_LOOP_FILTER_R4 ,3);
		case LFT_SPPU_LMK_PROP_RESISTANCE_16K_OHMS:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,  LFT_SPPU_LMK_PLL2_LOOP_FILTER_R4 ,4);
		};

	case LFT_SPPU_LMK_PROP_PLL2_C4  :  // doubt 
		switch  ((SPPULMKPropCapacitance4)a_nPropValue)
		{
		case LFT_SPPU_LMK_PROP_CAPACITANCE4_10_PF:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C4  ,0);
		case  LFT_SPPU_LMK_PROP_CAPACITANCE4_15_PF:       
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C4  ,1);
		case  LFT_SPPU_LMK_PROP_CAPACITANCE4_29_PF:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C4  ,2);
		case LFT_SPPU_LMK_PROP_CAPACITANCE4_34_PF:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C4  ,3);
		case LFT_SPPU_LMK_PROP_CAPACITANCE4_47_PF:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C4  ,4);

		case LFT_SPPU_LMK_PROP_CAPACITANCE4_52_PF :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C4  ,5);
		case LFT_SPPU_LMK_PROP_CAPACITANCE4_66_PF :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C4  ,6);
		case LFT_SPPU_LMK_PROP_CAPACITANCE4_71_PF :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C4  ,7);
		case LFT_SPPU_LMK_PROP_CAPACITANCE4_103_PF :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C4  ,8);
		case LFT_SPPU_LMK_PROP_CAPACITANCE4_108_PF :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C4  ,9);
		case LFT_SPPU_LMK_PROP_CAPACITANCE4_122_PF :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C4  ,10);
		case LFT_SPPU_LMK_PROP_CAPACITANCE4_126_PF :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C4  ,11);
		case LFT_SPPU_LMK_PROP_CAPACITANCE4_141_PF :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C4  ,12);
		case LFT_SPPU_LMK_PROP_CAPACITANCE4_146_PF:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C4  ,13);
		};



	case LFT_SPPU_LMK_PROP_PLL2_CHARGE_PUMP_STATE:
		switch((SPPULMKPropChargePumpState)a_nPropValue)
		{
		case  LFT_SPPU_LMK_PROP_CPS_ACTIVE :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,  LFT_SPPU_LMK_PLL2_ChargePump_STATE   ,0);
		case LFT_SPPU_LMK_PROP_CPS_TRISTATE :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,  LFT_SPPU_LMK_PLL2_ChargePump_STATE   ,1);
		}

	case LFT_SPPU_LMK_PROP_PLL2_CHARGE_PUMP_GAIN:
		switch((SPPULMKPropChargePumpGain)a_nPropValue)
		{
		case LFT_SPPU_LMK_PROP_CPG_100 :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806, LFT_SPPU_LMK_PLL2_ChargePump_GAIN,0);
		case LFT_SPPU_LMK_PROP_CPG_200:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806, LFT_SPPU_LMK_PLL2_ChargePump_GAIN,1);
		case LFT_SPPU_LMK_PROP_CPG_400 :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806, LFT_SPPU_LMK_PLL2_ChargePump_GAIN,2);
		case LFT_SPPU_LMK_PROP_CPG_1600 :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806, LFT_SPPU_LMK_PLL2_ChargePump_GAIN,3);
		};


	case LFT_SPPU_LMK_PROP_PLL2_CHARGE_PUMP_POLARITY:
		switch(( SPPULMKPropChargePumpPolarity)a_nPropValue)

		{
		case LFT_SPPU_LMK_PROP_CPP_NEGATIVE_SLOPE  :   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,  LFT_SPPU_LMK_PLL2_ChargePump_polarity ,a_nPropValue);
		case LFT_SPPU_LMK_PROP_CPP_POSITIVE_SLOPE     :  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,  LFT_SPPU_LMK_PLL2_ChargePump_polarity ,a_nPropValue);
		}







	}










	//switch case 
	return -1009;
}

long MiddleAPI::SetAttenuatorProperty(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,SPPUAttenuatorProp a_enAttenuatorProp,unsigned int a_nPropValue)
{
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};

	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn SetAttProperty(%d,%x)",a_enAttenuatorProp,a_nPropValue);
	mPrintDebug(strDebug);

	switch(a_enAttenuatorProp)
	{
	case LFT_SPPU_ATTENUATOR_1:
		RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 0, a_nPropValue);
		break;

	case LFT_SPPU_ATTENUATOR_2:
		RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_ATTENUATOR, 1, a_nPropValue);
		break;
		return 0;
	}
	return -100;
}


long MiddleAPI::GetLMKProperty(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,SPPULMKProp a_enLMKProp, unsigned int *a_nPropValue)
{

#if 0


	//****************************************general tap***************************************************************************//
	unsigned int a_nLMKPropvalue = 0;

	switch(a_enLMKProp)
	{
	case LFT_SPPU_LMK_PROP_FEEDBACK_MUX_SOURCE:
		LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_FeedbackMux_Source_CLKOUT,&a_nLMKPropvalue);
		switch(a_nLMKPropvalue)
		{
		case 0:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_FDBCK_MUX_SOURCE_CLK_OUT_0;
		case 1: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_FDBCK_MUX_SOURCE_CLK_OUT_2;
		case 2:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_FDBCK_MUX_SOURCE_CLK_OUT_4;
		case 3:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_FDBCK_MUX_SOURCE_CLK_OUT_6;
		case 4:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_FDBCK_MUX_SOURCE_CLK_OUT_8;
		case 5:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_FDBCK_MUX_SOURCE_CLK_OUT_10;
		case 6:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_FDBCK_MUX_SOURCE_CLK;
		}

	case LFT_SPPU_LMK_PROP_FEEDBACK_MUX_ENABLE:
		LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_FeedbackMux_Enable,&a_nLMKPropvalue);
		switch(a_enLMKProp)
		{
		case  0:
			return *a_nPropValue =   LFT_SPPU_STATE_DISABLE;
		case 1:
			return *a_nPropValue =   LFT_SPPU_STATE_ENABLE;
		}

	case LFT_SPPU_LMK_PROP_VCO_DIVIDER:
		LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_VCO_Divider,&a_nLMKPropvalue);
		switch(a_nLMKPropvalue)
		{
		case 0:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_DIVIDER_2;
		case 1: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_DIVIDER_3;
		case 2:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_DIVIDER_4;
		case 3:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_DIVIDER_5;
		case 4:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_DIVIDER_6;
		case 5:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_DIVIDER_7;
		case 6:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_DIVIDER_8;
		}

	case LFT_SPPU_LMK_PROP_VCO_MUX:
		LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_VCO_Mux,&a_nLMKPropvalue);
		switch(a_nLMKPropvalue)
		{   
		case 0:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_VCO_MUX_SELECTED;
		case 1: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_VCO_MUX_DIVIDER;


		}

	case LFT_SPPU_LMK_PROP_SYNC_TYPE:// doubt
		LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_SYN_Type,&a_nLMKPropvalue);
		switch(a_nLMKPropvalue)
		{  
		case 0:
			return *a_nPropValue =    LFT_SPPU_LMK_PROP_INPUT;
		case 1: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_INPUT_W_PULLUP_RESISTOR;
		case 2:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_INPUT_W_PULLDOWN_RESISTOR;
		case 3:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_OUTPUT;
		case 4:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_OUTPUT_INVERTED;
		case 5:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_OUTPUT_OPEN_SOURCE;
		case 6:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_OPEN_DRAIN;


		}

	case LFT_SPPU_LMK_PROP_SYNC_POLARITY: 
		LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_SYN_Polarity,&a_nLMKPropvalue);

		switch(a_nLMKPropvalue)
		{   
		case 0:
			return *a_nPropValue =    LFT_SPPU_LMK_PROP_ACTIVE_LOW;
		case 1: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_ACTIVE_HIGH;

		}


	case LFT_SPPU_LMK_PROP_SYNC_MUX:
		LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_SYN_sync_mux,&a_nLMKPropvalue);

		switch(a_nLMKPropvalue)
		{   
		case 0:
			return *a_nPropValue =    LFT_SPPU_LMK_PROP_SYNC_MUX_LOGIC_LOW;
		case 1: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_SYNC_MUX_UWIRE_READBACK;


		}

	case LFT_SPPU_LMK_PROP_SYNC_ENABLE:
		LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_SYN_ena_auto,&a_nLMKPropvalue);
		switch(a_nLMKPropvalue)
		{   
		case 0:
			return *a_nPropValue =    LFT_SPPU_LMK_PROP_SYNC_ENABLE_MANUAL;
		case 1: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_SYNC_ENABLE_INTERNALLY_GENERATED;   

		}

	case LFT_SPPU_LMK_PROP_SYNC_QUALIFICATION:
		LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_SYN_Qualification,&a_nLMKPropvalue);
		switch(a_nLMKPropvalue)
		{   
		case 0:
			return *a_nPropValue =    LFT_SPPU_LMK_PROP_SYNC_QUALIFICATION_NO;
		case 1: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_SYNC_QUALIFICATION_BY_CLOCK_OUTPUT;   
		}

	case LFT_SPPU_LMK_PROP_SYNC_ENABLE_STATE:
		LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_SYN_ENABLE,&a_nLMKPropvalue);
		switch(a_nLMKPropvalue)
		{   
		case 0:
			return *a_nPropValue =    LFT_SPPU_STATE_DISABLE;
		case 1: 
			return *a_nPropValue =   LFT_SPPU_STATE_ENABLE;    





		}


	case LFT_SPPU_LMK_PROP_SYNC_01_STATE:
		return LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_SYN_sync_op_01_STATE,a_nPropValue);
	case LFT_SPPU_LMK_PROP_SYNC_23_STATE:
		return LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_SYN_sync_op_02_STATE,a_nPropValue);
	case LFT_SPPU_LMK_PROP_SYNC_45_STATE:
		return LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_SYN_sync_op_03_STATE,a_nPropValue);
	case LFT_SPPU_LMK_PROP_SYNC_67_STATE:
		return LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_SYN_sync_op_04_STATE,a_nPropValue);
	case LFT_SPPU_LMK_PROP_SYNC_89_STATE:
		return LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_SYN_sync_op_05_STATE,a_nPropValue);
	case LFT_SPPU_LMK_PROP_SYNC_1011_STATE:
		return LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_SYN_sync_op_06_STATE,a_nPropValue);

	case LFT_SPPU_LMK_PROP_HLDOVR_MODE:
		return LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_Holdover_Mode,&a_nLMKPropvalue);
		switch(a_nLMKPropvalue)
		{   
		case 0:
			return *a_nPropValue =    LFT_SPPU_STATE_DISABLE;
		case 1: 
			return *a_nPropValue =   LFT_SPPU_STATE_ENABLE;    

		}



	case LFT_SPPU_LMK_PROP_HLDOVR_DLD1_DET:
		return LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_Holdover_dld1_DET,&a_nLMKPropvalue);
		switch(a_nLMKPropvalue)
		{   
		case 0:
			return *a_nPropValue =    LFT_SPPU_LMK_PROP_HOLDOVER_DISABLE_CAUSES_CLK_SWTCH_EV;
		case 1: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_HOLDOVER_DISABLE_NO_CLK_SWTCH_EV;    

		} 


	case LFT_SPPU_LMK_PROP_HLDOVR_DLD_COUNT:
		return LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_Holdover_DLD_count,a_nPropValue);
	case LFT_SPPU_LMK_PROP_HLDOVR_FORCE:
		return LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_Holdover_force,a_nPropValue);
	case LFT_SPPU_LMK_PROP_STS_OUT_LD_TYPE:
		LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_LD_TYPE ,&a_nLMKPropvalue);
		switch(a_nLMKPropvalue)
		{  
		case 0:
			return *a_nPropValue =    LFT_SPPU_LMK_PROP_SUB_OUTPUT;
		case 1: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_SUB_OUTPUT_INVERTED;
		case 2:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_SUB_OUTPUT_OPEN_SOURCE;
		case 3:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_OUTPUT;
		case 4:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_SUB_OPEN_DRAIN;



		}

	case LFT_SPPU_LMK_PROP_STS_OUT_LD_MUX:
		return LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_LD_MUX,&a_nLMKPropvalue);
		switch(a_nLMKPropvalue)
		{  
		case 0:
			return *a_nPropValue =    LFT_SPPU_LMK_PROP_LDMUX_LOGIC_LOW;
		case 1: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_LDMUX_PLL1DLD;
		case 2:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_LDMUX_PLL2DLD;
		case 3:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_LDMUX_PLL1DLD_N_PLL2DLD;
		case 4:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_LDMUX_HODLOVER_STATUS;
		case 5:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_LDMUX_DAC_LOCKED;
		case 6:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_LDMUX_UWIRE_READBACK;
		case 7:
			return *a_nPropValue =    LFT_SPPU_LMK_PROP_LDMUX_DAC_RAIL;
		case 8: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_LDMUX_DAC_LOW;
		case 9:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_LDMUX_DAC_HIGH;
		case 10:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_LDMUX_DAC_PLL1_N;
		case 11:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_LDMUX_DAC_PLL1_N_BY_2;
		case 12:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_LDMUX_DAC_PLL2_N;
		case 13:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_LDMUX_DAC_PLL2_N_BY_2; 

		case 14:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_LDMUX_DAC_PLL1_R;
		case 15:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_LDMUX_DAC_PLL1_R_BY_2;
		case 16:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_LDMUX_DAC_PLL2_R;
		case 17:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_LDMUX_DAC_PLL2_R_BY_2;

		}
	case LFT_SPPU_LMK_PROP_STS_OUT_HLDOVR_TYPE:
		LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_Holdover_type ,&a_nLMKPropvalue);
		switch(a_nLMKPropvalue)
		{  
		case 0:
			return *a_nPropValue =    LFT_SPPU_LMK_PROP_SUB_OUTPUT;
		case 1: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_SUB_OUTPUT_INVERTED;
		case 2:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_SUB_OUTPUT_OPEN_SOURCE;
		case 3:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_SUB_OPEN_DRAIN;



		}	






		// doubt
	case LFT_SPPU_LMK_PROP_STS_OUT_HLDOVR_MUX:
		LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_status_Outputs_Holdover_MUX,a_nLMKPropvalue);
		switch(a_nLMKPropvalue)
		{  
		case 0:
			return *a_nPropValue =    LFT_SPPU_LMK_PROP_LDMUX_LOGIC_LOW;
		case 1: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_LDMUX_PLL1DLD;
		case 2:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_LDMUX_PLL2DLD;
		case 3:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_LDMUX_PLL1DLD_N_PLL2DLD;
		case 4:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_LDMUX_HODLOVER_STATUS;
		case 5:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_LDMUX_DAC_LOCKED;
		case 6:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_LDMUX_UWIRE_READBACK;
		case 7:
			return *a_nPropValue =    LFT_SPPU_LMK_PROP_LDMUX_DAC_RAIL;
		case 8: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_LDMUX_DAC_LOW;
		case 9:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_LDMUX_DAC_HIGH;
		case 10:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_LDMUX_DAC_PLL1_N;
		case 11:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_LDMUX_DAC_PLL1_N_BY_2;
		case 12:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_LDMUX_DAC_PLL2_N;
		case 13:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_LDMUX_DAC_PLL2_N_BY_2; 

		case 14:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_LDMUX_DAC_PLL1_R;
		case 15:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_LDMUX_DAC_PLL1_R_BY_2;
		case 16:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_LDMUX_DAC_PLL2_R;
		case 17:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_LDMUX_DAC_PLL2_R_BY_2;

		}




	case LFT_SPPU_LMK_PROP_LOS_TIMEOUT:
		LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_En_Los,&a_nLMKPropvalue);
		switch(a_nLMKPropvalue)

		{
		case 0:
			return *a_nPropValue =    LFT_SPPU_LMK_PROP_LOS_TIMEOUT_DATA_1;
		case 1: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_LOS_TIMEOUT_DATA_2;
		case 2:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_LOS_TIMEOUT_DATA_3;
		case 3:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_LOS_TIMEOUT_DATA_4;

		};

	case LFT_SPPU_LMK_PROP_EN_LOS:
		return LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_GEN_Setting_En_Los,a_nPropValue);

	case LFT_SPPU_LMK_PROP_OSCOUT_DIVIDER:
		LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_OSCOUT_Divider,&a_nLMKPropvalue);
		switch(a_nLMKPropvalue)
		{
		case 0:
			return *a_nPropValue =    LFT_SPPU_LMK_PROP_DIVIDER_2;
		case 1: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_DIVIDER_3;
		case 2:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_DIVIDER_4;
		case 3:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_DIVIDER_5;
		case 4:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_DIVIDER_6;
		case 5:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_DIVIDER_7;
		case 6:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_DIVIDER_8;

		}

	case LFT_SPPU_LMK_PROP_OSCOUT_OSC1_AMP:
		return LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_OSCOUT_OSC1_Amp,&a_nLMKPropvalue); 

		switch(a_nLMKPropvalue)
		{
		case 0:
			return *a_nPropValue =    LFT_SPPU_LMK_PROP_OSCOUT_AMP_700;
		case 1: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_OSCOUT_AMP_1200;
		case 2:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_OSCOUT_AMP_1600;
		case 3:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_OSCOUT_AMP_2000;

		}


	case LFT_SPPU_LMK_PROP_OSCOUT_OSC0_TYPE:
		return LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_OSCOUT_OSC0_Type,&a_nLMKPropvalue);
		switch(a_nLMKPropvalue)
		{
		case 0:
			return *a_nPropValue =    LFT_SPPU_LMK_PROP_CLK_TY_OFF;
		case 1: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_CLK_TY_LVDS;
		case 2:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_700;
		case 3:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1200;
		case 4:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1600;
		case 5:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_2000;
		case 6:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_INV;
		case 7:
			return *a_nPropValue =    LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_NORM;
		case 8: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_NORM;
		case 9:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_INV;
		case 10:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_NORM;
		case 11:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_INV;
		case 12:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_LOW;
		case 13:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_LOW;

		case 14:
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_LOW;


		}




	case LFT_SPPU_LMK_PROP_OSCOUT_OSC0_MUX:
		LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_OSCOUT_OSC0_Mux,&a_nLMKPropvalue);
		switch(a_nLMKPropvalue)
		{
		case 0:
			return *a_nPropValue =    LFT_SPPU_LMK_PROP_OSCOUT_MUX_BYPASS_DIVIDER;
		case 1: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_OSCOUT_MUX_DIVIDE;

		}
	case LFT_SPPU_LMK_PROP_OSCOUT_OSC1_MUX:
		LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_OSCOUT_OSC1_Mux,&a_nLMKPropvalue);
		switch(a_nLMKPropvalue)
		{
		case 0:
			return *a_nPropValue =    LFT_SPPU_LMK_PROP_OSCOUT_MUX_BYPASS_DIVIDER;
		case 1: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_OSCOUT_MUX_DIVIDE;

		}


	case LFT_SPPU_LMK_PROP_OSCOUT_EN_CLKIN0:
		return LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_OSCOUT_ENABLE_OSCout0 ,a_nPropValue);
	case LFT_SPPU_LMK_PROP_OSCOUT_EN_CLKIN1:
		return LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_OSCOUT_ENABLE_OSCout1,a_nPropValue);
	case LFT_SPPU_LMK_PROP_OSCOUT_SWITCH_OFF:
		return LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_OSCOUT_Swich_off,a_nPropValue);



		/***********************************************************general tab end here**********************************************************************/


	case  LFT_SPPU_LMK_PROP_CLK_01_DIVIDER: 
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_divider,a_nPropValue);
	case LFT_SPPU_LMK_PROP_CLK_01_DELAY:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_digdelay,a_nPropValue);
	case LFT_SPPU_LMK_PROP_CLK_01_CLK0_TYPE :
		switch((SPPULMKPropClockType)a_nPropValue)
		{
		case LFT_SPPU_LMK_PROP_CLK_TY_OFF:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLKout0_TYPE,0);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVDS:                   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLKout0_TYPE,1);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_700:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLKout0_TYPE,2);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1200:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLKout0_TYPE,3);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1600: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLKout0_TYPE,4);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_2000:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLKout0_TYPE,5);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_INV:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLKout0_TYPE,6);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_NORM:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLKout0_TYPE,7);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_NORM: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLKout0_TYPE,8);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLKout0_TYPE,9);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_NORM:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLKout0_TYPE,10);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLKout0_TYPE,11);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_LOW:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLKout0_TYPE,12);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_LOW :     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLKout0_TYPE,13);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_LOW:      
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLKout0_TYPE,14);
		} 

	case LFT_SPPU_LMK_PROP_CLK_01_CLK1_TYPE:
		switch((SPPULMKPropClockType)a_nPropValue)
		{
		case LFT_SPPU_LMK_PROP_CLK_TY_OFF:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLK1out1_TYPE,0);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVDS:                   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLK1out1_TYPE,1);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_700:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLK1out1_TYPE,2);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1200:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLK1out1_TYPE,3);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1600: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLK1out1_TYPE,4);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_2000:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLK1out1_TYPE,5);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_INV:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLK1out1_TYPE,6);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_NORM:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLK1out1_TYPE,7);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_NORM: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLK1out1_TYPE,8);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLK1out1_TYPE,9);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_NORM:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLK1out1_TYPE,10);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLK1out1_TYPE,11);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_LOW:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLK1out1_TYPE,12);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_LOW :     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLK1out1_TYPE,13);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_LOW:      
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_CLK1out1_TYPE,14);
		}

	case LFT_SPPU_LMK_PROP_CLK_01_ANALOG_DELAY:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_AnalogDelay,a_nPropValue);
	case LFT_SPPU_LMK_PROP_CLK_01_ANALOG_DELAY_SEL:
		switch((SPPUAnalogDelaySel)a_nPropValue)
		{
		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_OFF:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_AnalogDelay_sel,0);
		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_ODD_CLK_ONLY:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_AnalogDelay_sel,1);
		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_EVEN_CLK_ONLY:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_AnalogDelay_sel,2);
		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_BOTH_CLKS :		
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_AnalogDelay_sel,3);
		}
	case LFT_SPPU_LMK_PROP_CLK_01_DD_HALF_SHIFT:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK0_CLK1_DD_hlfshft,a_nPropValue);
	case LFT_SPPU_LMK_PROP_CLK_01_SWITCH_OFF:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806, LFT_SPPU_LMK_CLK0_CLK1_switch_off_pd,a_nPropValue);

	case LFT_SPPU_LMK_PROP_CLK_23_DIVIDER:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_divider,a_nPropValue);
	case LFT_SPPU_LMK_PROP_CLK_23_DELAY :
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_digdelay,a_nPropValue);
	case LFT_SPPU_LMK_PROP_CLK_23_CLK0_TYPE:
		switch((SPPULMKPropClockType)a_nPropValue)
		{
		case LFT_SPPU_LMK_PROP_CLK_TY_OFF:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLKout2_TYPE,0);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVDS:                   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLKout2_TYPE,1);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_700:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLKout2_TYPE,2);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1200:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLKout2_TYPE,3);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1600: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLKout2_TYPE,4);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_2000:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLKout2_TYPE,5);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_INV:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLKout2_TYPE,6);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_NORM:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLKout2_TYPE,7);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_NORM: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLKout2_TYPE,8);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLKout2_TYPE,9);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_NORM:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLKout2_TYPE,10);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLKout2_TYPE,11);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_LOW:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLKout2_TYPE,12);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_LOW :     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLKout2_TYPE,13);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_LOW:      
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLKout2_TYPE,14);
		}

	case LFT_SPPU_LMK_PROP_CLK_23_CLK1_TYPE:
		switch((SPPULMKPropClockType)a_nPropValue)
		{
		case LFT_SPPU_LMK_PROP_CLK_TY_OFF:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLK1out3_TYPE,0);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVDS:                   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLK1out3_TYPE,1);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_700:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLK1out3_TYPE,2);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1200:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLK1out3_TYPE,3);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1600: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLK1out3_TYPE,4);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_2000:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLK1out3_TYPE,5);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_INV:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLK1out3_TYPE,6);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_NORM:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLK1out3_TYPE,7);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_NORM: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLK1out3_TYPE,8);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLK1out3_TYPE,9);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_NORM:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLK1out3_TYPE,10);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLK1out3_TYPE,11);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_LOW:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLK1out3_TYPE,12);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_LOW :     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLK1out3_TYPE,13);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_LOW:      
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_CLK1out3_TYPE,14);
		}
	case LFT_SPPU_LMK_PROP_CLK_23_ANALOG_DELAY:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_AnalogDelay,a_nPropValue);

	case LFT_SPPU_LMK_PROP_CLK_23_ANALOG_DELAY_SEL:
		switch((SPPUAnalogDelaySel)a_nPropValue)
		{
		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_OFF:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_AnalogDelay_sel,0);
		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_ODD_CLK_ONLY :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_AnalogDelay_sel,1);
		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_EVEN_CLK_ONLY :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_AnalogDelay_sel,2);
		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_BOTH_CLKS :		
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_AnalogDelay_sel,3);
		}
	case LFT_SPPU_LMK_PROP_CLK_23_DD_HALF_SHIFT:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK2_CLK3_DD_hlfshft,a_nPropValue);
	case LFT_SPPU_LMK_PROP_CLK_23_SWITCH_OFF:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806, LFT_SPPU_LMK_CLK2_CLK3_switch_off_pd,a_nPropValue);
	case LFT_SPPU_LMK_PROP_CLK_45_DIVIDER :
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_divider,a_nPropValue);
	case LFT_SPPU_LMK_PROP_CLK_45_DELAY:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_digdelay,a_nPropValue);
	case LFT_SPPU_LMK_PROP_CLK_45_CLK0_TYPE:
		switch((SPPULMKPropClockType)a_nPropValue)
		{
		case LFT_SPPU_LMK_PROP_CLK_TY_OFF:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,0);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVDS:                   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,1);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_700:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,2);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1200:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,3);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1600: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,4);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_2000:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,5);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_INV:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,6);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_NORM:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,7);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_NORM: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,8);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,9);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_NORM:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,10);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,11);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_LOW:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,12);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_LOW :     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,13);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_LOW:      
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,14);
		}
	case LFT_SPPU_LMK_PROP_CLK_45_CLK1_TYPE:
		switch((SPPULMKPropClockType)a_nPropValue)
		{

		case LFT_SPPU_LMK_PROP_CLK_TY_OFF:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLK1out5_TYPE,0);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVDS:                   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,1);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_700:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,2);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1200:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,3);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1600: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,4);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_2000:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,5);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_INV:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,6);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_NORM:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,7);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_NORM: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,8);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,9);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_NORM:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,10);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,11);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_LOW:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,12);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_LOW :     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,13);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_LOW:      
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_CLKout4_TYPE,14);
		}
	case LFT_SPPU_LMK_PROP_CLK_45_ANALOG_DELAY:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_AnalogDelay,a_nPropValue);
	case LFT_SPPU_LMK_PROP_CLK_45_ANALOG_DELAY_SEL:
		switch((SPPUAnalogDelaySel)a_nPropValue)
		{
		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_OFF:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_AnalogDelay_sel,0);
		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_ODD_CLK_ONLY :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_AnalogDelay_sel,1);
		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_EVEN_CLK_ONLY :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_AnalogDelay_sel,2);
		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_BOTH_CLKS :		
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_AnalogDelay_sel,3);
		}


	case LFT_SPPU_LMK_PROP_CLK_45_DD_HALF_SHIFT:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK4_CLK5_DD_hlfshft,a_nPropValue);
	case LFT_SPPU_LMK_PROP_CLK_45_SWITCH_OFF:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806, LFT_SPPU_LMK_CLK4_CLK5_switch_off_pd,a_nPropValue);
	case LFT_SPPU_LMK_PROP_CLK_67_DIVIDER:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_divider,a_nPropValue);

	case LFT_SPPU_LMK_PROP_CLK_67_DELAY: 
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_digdelay,a_nPropValue);

	case LFT_SPPU_LMK_PROP_CLK_67_CLK0_TYPE:
		switch((SPPULMKPropClockType)a_nPropValue)
		{

		case LFT_SPPU_LMK_PROP_CLK_TY_OFF:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLKout6_TYPE,0);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVDS:                   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLKout6_TYPE,1);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_700:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLKout6_TYPE,2);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1200:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLKout6_TYPE,3);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1600: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLKout6_TYPE,4);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_2000:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLKout6_TYPE,5);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_INV:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLKout6_TYPE,6);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_NORM:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLKout6_TYPE,7);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_NORM: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLKout6_TYPE,8);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLKout6_TYPE,9);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_NORM:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLKout6_TYPE,10);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLKout6_TYPE,11);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_LOW:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLKout6_TYPE,12);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_LOW :     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLKout6_TYPE,13);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_LOW:      
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLKout6_TYPE,14);
		}


	case LFT_SPPU_LMK_PROP_CLK_67_CLK1_TYPE:
		switch((SPPULMKPropClockType)a_nPropValue)
		{

		case LFT_SPPU_LMK_PROP_CLK_TY_OFF:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLK1out7_TYPE,0);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVDS:                   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLK1out7_TYPE,1);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_700:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLK1out7_TYPE,2);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1200:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLK1out7_TYPE,3);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1600: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLK1out7_TYPE,4);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_2000:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLK1out7_TYPE,5);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_INV:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLK1out7_TYPE,6);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_NORM:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLK1out7_TYPE,7);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_NORM: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLK1out7_TYPE,8);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLK1out7_TYPE,9);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_NORM:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLK1out7_TYPE,10);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLK1out7_TYPE,11);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_LOW:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLK1out7_TYPE,12);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_LOW :     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLK1out7_TYPE,13);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_LOW:      
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_CLK1out7_TYPE,14);
		}


	case LFT_SPPU_LMK_PROP_CLK_67_ANALOG_DELAY:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_AnalogDelay,a_nPropValue);
	case LFT_SPPU_LMK_PROP_CLK_67_ANALOG_DELAY_SEL:
		switch((SPPUAnalogDelaySel)a_nPropValue)
		{
		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_OFF:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_AnalogDelay_sel,0);
		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_ODD_CLK_ONLY: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_AnalogDelay_sel,1);
		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_EVEN_CLK_ONLY :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_AnalogDelay_sel,2);
		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_BOTH_CLKS :		
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_AnalogDelay_sel,3);
		}
	case LFT_SPPU_LMK_PROP_CLK_67_DD_HALF_SHIFT:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK6_CLK7_DD_hlfshft,a_nPropValue);
	case LFT_SPPU_LMK_PROP_CLK_67_SWITCH_OFF:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806, LFT_SPPU_LMK_CLK6_CLK7_switch_off_pd,a_nPropValue);

	case LFT_SPPU_LMK_PROP_CLK_89_DIVIDER:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_divider,a_nPropValue);
	case LFT_SPPU_LMK_PROP_CLK_89_DELAY:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_digdelay,a_nPropValue);
	case LFT_SPPU_LMK_PROP_CLK_89_CLK0_TYPE:
		switch((SPPULMKPropClockType)a_nPropValue)
		{

		case LFT_SPPU_LMK_PROP_CLK_TY_OFF:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLKout8_TYPE,0);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVDS:                   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLKout8_TYPE,1);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_700:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLKout8_TYPE,2);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1200:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLKout8_TYPE,3);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1600: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLKout8_TYPE,4);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_2000:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLKout8_TYPE,5);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_INV:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLKout8_TYPE,6);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_NORM:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLKout8_TYPE,7);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_NORM: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLKout8_TYPE,8);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLKout8_TYPE,9);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_NORM:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLKout8_TYPE,10);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLKout8_TYPE,11);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_LOW:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLKout8_TYPE,12);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_LOW :     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLKout8_TYPE,13);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_LOW:      
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLKout8_TYPE,14);
		}

	case LFT_SPPU_LMK_PROP_CLK_89_CLK1_TYPE:
		switch((SPPULMKPropClockType)a_nPropValue)
		{

		case LFT_SPPU_LMK_PROP_CLK_TY_OFF:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLK1out9_TYPE,0);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVDS:                   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLK1out9_TYPE,1);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_700:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLK1out9_TYPE,2);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1200:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLK1out9_TYPE,3);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1600: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLK1out9_TYPE,4);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_2000:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLK1out9_TYPE,5);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_INV:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLK1out9_TYPE,6);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_NORM:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLK1out9_TYPE,7);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_NORM: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLK1out9_TYPE,8);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLK1out9_TYPE,9);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_NORM:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLK1out9_TYPE,10);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLK1out9_TYPE,11);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_LOW:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLK1out9_TYPE,12);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_LOW :     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLK1out9_TYPE,13);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_LOW:      
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_CLK1out9_TYPE,14);
		}

	case LFT_SPPU_LMK_PROP_CLK_89_ANALOG_DELAY:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_AnalogDelay,a_nPropValue);




	case LFT_SPPU_LMK_PROP_CLK_89_ANALOG_DELAY_SEL:
		switch((SPPUAnalogDelaySel)a_nPropValue)
		{
		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_OFF:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_AnalogDelay_sel,0);
		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_ODD_CLK_ONLY: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_AnalogDelay_sel,1);
		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_EVEN_CLK_ONLY :
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_AnalogDelay_sel,2);
		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_BOTH_CLKS :		
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_AnalogDelay_sel,3);
		}

	case LFT_SPPU_LMK_PROP_CLK_89_DD_HALF_SHIFT:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK8_CLK9_DD_hlfshft,a_nPropValue);
	case LFT_SPPU_LMK_PROP_CLK_89_SWITCH_OFF:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806, LFT_SPPU_LMK_CLK8_CLK9_switch_off_pd,a_nPropValue);

	case LFT_SPPU_LMK_PROP_CLK_1011_DIVIDER :
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_divider,a_nPropValue);
	case LFT_SPPU_LMK_PROP_CLK_1011_DELAY:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_digdelay,a_nPropValue);


	case LFT_SPPU_LMK_PROP_CLK_1011_CLK0_TYPE:
		switch((SPPULMKPropClockType)a_nPropValue)
		{

		case LFT_SPPU_LMK_PROP_CLK_TY_OFF:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLKout0_TYPE,0);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVDS:                   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLKout0_TYPE,1);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_700:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLKout0_TYPE,2);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1200:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLKout0_TYPE,3);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1600: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLKout0_TYPE,4);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_2000:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLKout0_TYPE,5);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_INV:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLKout0_TYPE,6);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_NORM:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLKout0_TYPE,7);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_NORM: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLKout0_TYPE,8);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLKout0_TYPE,9);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_NORM:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLKout0_TYPE,10);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLKout0_TYPE,11);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_LOW:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLKout0_TYPE,12);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_LOW :     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLKout0_TYPE,13);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_LOW:      
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLKout0_TYPE,14);
		}
	case LFT_SPPU_LMK_PROP_CLK_1011_CLK1_TYPE:
		switch((SPPULMKPropClockType)a_nPropValue)
		{

		case LFT_SPPU_LMK_PROP_CLK_TY_OFF:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLK1out1_TYPE,0);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVDS:                   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLK1out1_TYPE,1);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_700:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLK1out1_TYPE,2);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1200:   
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLK1out1_TYPE,3);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_1600: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLK1out1_TYPE,4);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVPECL_2000:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLK1out1_TYPE,5);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_INV:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLK1out1_TYPE,6);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_NORM:  
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLK1out1_TYPE,7);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_NORM: 
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLK1out1_TYPE,8);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLK1out1_TYPE,9);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_NORM:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLK1out1_TYPE,10);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_INV:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLK1out1_TYPE,11);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_NORM_OR_LOW:     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLK1out1_TYPE,12);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_INV_OR_LOW :     
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLK1out1_TYPE,13);
		case LFT_SPPU_LMK_PROP_CLK_TY_LVCMOS_LOW_OR_LOW:      
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_CLK1out1_TYPE,14);
		}
	case LFT_SPPU_LMK_PROP_CLK_1011_ANALOG_DELAY:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_AnalogDelay,a_nPropValue);

	case LFT_SPPU_LMK_PROP_CLK_1011_ANALOG_DELAY_SEL:
		switch((SPPUAnalogDelaySel)a_nPropValue)
		{

		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_OFF:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_AnalogDelay_sel,0);
		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_ODD_CLK_ONLY:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_AnalogDelay_sel,1);
		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_EVEN_CLK_ONLY:
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_AnalogDelay_sel,2);
		case LFT_SPPU_LMK_PROP_ANLG_DLY_SEL_BOTH_CLKS :		
			return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_AnalogDelay_sel,3);
		}

	case LFT_SPPU_LMK_PROP_CLK_1011_DD_HALF_SHIFT:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_CLK10_CLK11_DD_hlfshft,a_nPropValue);
	case LFT_SPPU_LMK_PROP_CLK_1011_SWITCH_OFF:
		return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806, LFT_SPPU_LMK_CLK10_CLK11_switch_off_pd,a_nPropValue);
		/*************************************pll******************************************************************************************************/
	case LFT_SPPU_LMK_PROP_PLL_EN_CLKIN0:
		LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_En_CLKin0,&a_nLMKPropvalue);
		switch(a_nLMKPropvalue)
		{
		case 0:
			return *a_nPropValue =    LFT_SPPU_STATE_DISABLE;
		case 1: 
			return *a_nPropValue =   LFT_SPPU_STATE_ENABLE;
		}

	case LFT_SPPU_LMK_PROP_PLL_EN_CLKIN1:
		LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_En_CLKin1,&a_nLMKPropvalue);
		switch(a_nLMKPropvalue)
		{
		case 0:
			return *a_nPropValue =    LFT_SPPU_STATE_DISABLE;
		case 1: 
			return *a_nPropValue =   LFT_SPPU_STATE_ENABLE;
		}



	case LFT_SPPU_LMK_PROP_PLL_CLIN_SEL_INV:
		LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLKIN_sel_INV,&a_nLMKPropvalue);
		switch(a_nLMKPropvalue)
		{
		case 0:
			return *a_nPropValue =    LFT_SPPU_LMK_PROP_ACTIVE_LOW;
		case 1: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_ACTIVE_HIGH;  

		}
	case LFT_SPPU_LMK_PROP_PLL_CLKIN_SEL_MODE:
		LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLKIN_SEL_Mode,&a_nLMKPropvalue);
		switch(a_nLMKPropvalue)
		{
		case 0:
			return *a_nPropValue =    LFT_SPPU_LMK_PROP_CLK_SEL_MODE_CLK_IN_0;
		case 1: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_CLK_SEL_MODE_CLK_IN_1;		
		case 2:
			return *a_nPropValue =    LFT_SPPU_LMK_PROP_CLK_SEL_MODE_PIN_SEL_MODE;
		case 3: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_CLK_SEL_MODE_AUTO_MODE;		
		case 4: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_CLK_SEL_MODE_AUTO_MODE_NXT_PIN;		


		}

	case LFT_SPPU_LMK_PROP_PLL_CLIN0_MUX:
		LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLKIN0_MUX,&a_nLMKPropvalue);
		switch(a_nLMKPropvalue)
		{
		case 0:
			return *a_nPropValue =    LFT_SPPU_LMK_PROP_CLK_MUX_LOGIC_LOW;
		case 1: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_CLK_MUX_CLK_IN_0LOS;		
		case 2:
			return *a_nPropValue =    LFT_SPPU_LMK_PROP_CLK_MUX_CLK_IN_0_SELECTED;
		case 3: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_CLK_MUX_DAC_LOCKED;		
		case 4: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_CLK_MUX_DAC_LOW;		
		case 5: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_CLK_MUX_DAC_HIGH;		
		case 6: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_CLK_MUX_UWIRE_READBACK;


		}
	case LFT_SPPU_LMK_PROP_PLL_CLIN1_MUX:
		LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLKIN1_MUX,&a_nLMKPropvalue);
		switch(a_nLMKPropvalue)
		{
		case 0:
			return *a_nPropValue =    LFT_SPPU_LMK_PROP_CLK_MUX_LOGIC_LOW;
		case 1: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_CLK_MUX_CLK_IN_0LOS;		
		case 2:
			return *a_nPropValue =    LFT_SPPU_LMK_PROP_CLK_MUX_CLK_IN_0_SELECTED;
		case 3: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_CLK_MUX_DAC_LOCKED;		
		case 4: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_CLK_MUX_DAC_LOW;		
		case 5: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_CLK_MUX_DAC_HIGH;		
		case 6: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_CLK_MUX_UWIRE_READBACK;


		}	

	case LFT_SPPU_LMK_PROP_PLL_CLKIN0_TYPE:
		LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLKIN0_TYPE,&a_nLMKPropvalue);
		switch(a_nLMKPropvalue)
		{
		case 0:
			return *a_nPropValue =    LFT_SPPU_LMK_PROP_INPUT;
		case 1: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_INPUT_W_PULLUP_RESISTOR;		
		case 2:
			return *a_nPropValue =    LFT_SPPU_LMK_PROP_INPUT_W_PULLDOWN_RESISTOR;
		case 3: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_OUTPUT;		
		case 4: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_OUTPUT_INVERTED;		
		case 5: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_OUTPUT_OPEN_SOURCE;		
		case 6: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_OPEN_DRAIN;


		}
	case LFT_SPPU_LMK_PROP_PLL_CKLIN0_TYPE_2:
		LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLKIN1_TYPE,&a_nLMKPropvalue);
		switch(a_nLMKPropvalue)
		{
		case 0:
			return *a_nPropValue =    LFT_SPPU_LMK_PROP_INPUT;
		case 1: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_INPUT_W_PULLUP_RESISTOR;		
		case 2:
			return *a_nPropValue =    LFT_SPPU_LMK_PROP_INPUT_W_PULLDOWN_RESISTOR;
		case 3: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_OUTPUT;		
		case 4: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_OUTPUT_INVERTED;		
		case 5: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_OUTPUT_OPEN_SOURCE;		
		case 6: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_OPEN_DRAIN;


		}


	case LFT_SPPU_LMK_PROP_PLL_BUF_TYPE0:
		LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLK0BUF_TYPE0,&a_nLMKPropvalue);
		switch(a_nLMKPropvalue)
		{
		case 0:
			return *a_nPropValue =    LFT_SPPU_LMK_PROP_BUFF_TYPE_BIPOLAR;
		case 1: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_BUFF_TYPE_CMOS;		
		};

	case LFT_SPPU_LMK_PROP_PLL_BUF_TYPE1:
		LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLK1BUF_TYPE1,&a_nLMKPropvalue);
		switch(a_nLMKPropvalue)
		{
		case 0:
			return *a_nPropValue =    LFT_SPPU_LMK_PROP_BUFF_TYPE_BIPOLAR;
		case 1: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_BUFF_TYPE_CMOS;		
		};




	case LFT_SPPU_LMK_PROP_PLL_CLKIN0_DIV:
		LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLKIN0_Div,&a_nLMKPropvalue);
		switch(a_nLMKPropvalue)
		{
		case 0:
			return *a_nPropValue =    LFT_SPPU_LMK_PROP_CLK_IN_DIV_1;
		case 1: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_CLK_IN_DIV_2;
		case 2:
			return *a_nPropValue =    LFT_SPPU_LMK_PROP_CLK_IN_DIV_4;
		case 3: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_CLK_IN_DIV_8;

		};


	case LFT_SPPU_LMK_PROP_PLL_CLKIN1_DIV:
		LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_Setting_CLK1N1_Div,&a_nLMKPropvalue);
		switch(a_nLMKPropvalue)
		{
		case 0:
			return *a_nPropValue =    LFT_SPPU_LMK_PROP_CLK_IN_DIV_1;
		case 1: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_CLK_IN_DIV_2;
		case 2:
			return *a_nPropValue =    LFT_SPPU_LMK_PROP_CLK_IN_DIV_4;
		case 3: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_CLK_IN_DIV_8;

		};

	case LFT_SPPU_LMK_PROP_PLL_WND_SIZE:
		LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_wind_size,&a_nLMKPropvalue);
		switch(a_nLMKPropvalue)
		{
		case 0:
			return *a_nPropValue =    LFT_SPPU_LMK_PROP_PLL_WND_SZ_DATA1;
		case 1: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_PLL_WND_SZ_DATA2;
		case 2:
			return *a_nPropValue =    LFT_SPPU_LMK_PROP_PLL_WND_SZ_DATA3;
		case 3: 
			return *a_nPropValue =   LFT_SPPU_LMK_PROP_PLL_WND_SZ_DATA4;

		case LFT_SPPU_LMK_PROP_PLL_R_DLY:
			LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_R_DLY,&a_nLMKPropvalue);
			switch(a_nLMKPropvalue)
			{
			case 0:
				return *a_nPropValue =    LFT_SPPU_LMK_PROP_PLL_DLY_0;
			case 1: 
				return *a_nPropValue =   LFT_SPPU_LMK_PROP_PLL_DLY_205;		
			case 2:
				return *a_nPropValue =    LFT_SPPU_LMK_PROP_PLL_DLY_410;
			case 3: 
				return *a_nPropValue =   LFT_SPPU_LMK_PROP_PLL_DLY_615;		
			case 4: 
				return *a_nPropValue =   LFT_SPPU_LMK_PROP_PLL_DLY_820;		
			case 5: 
				return *a_nPropValue =   LFT_SPPU_LMK_PROP_PLL_DLY_1025;		
			case 6: 
				return *a_nPropValue =   LFT_SPPU_LMK_PROP_PLL_DLY_1230;
			case 7: 
				return *a_nPropValue =   LFT_SPPU_LMK_PROP_PLL_DLY_1485;


			};

		case LFT_SPPU_LMK_PROP_PLL_N_DLY2:
			LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_N_DLY_2,&a_nLMKPropvalue);
			switch(a_nLMKPropvalue)
			{
			case 0:
				return *a_nPropValue =    LFT_SPPU_LMK_PROP_PLL_DLY_0;
			case 1: 
				return *a_nPropValue =   LFT_SPPU_LMK_PROP_PLL_DLY_205;		
			case 2:
				return *a_nPropValue =    LFT_SPPU_LMK_PROP_PLL_DLY_410;
			case 3: 
				return *a_nPropValue =   LFT_SPPU_LMK_PROP_PLL_DLY_615;		
			case 4: 
				return *a_nPropValue =   LFT_SPPU_LMK_PROP_PLL_DLY_820;		
			case 5: 
				return *a_nPropValue =   LFT_SPPU_LMK_PROP_PLL_DLY_1025;		
			case 6: 
				return *a_nPropValue =   LFT_SPPU_LMK_PROP_PLL_DLY_1230;
			case 7: 
				return *a_nPropValue =   LFT_SPPU_LMK_PROP_PLL_DLY_1485;

			};
		case LFT_SPPU_LMK_PROP_PLL_DLD_CNT:

			return LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_DLD_CNT ,a_nPropValue);
		case  LFT_SPPU_LMK_PROP_PLL_SYNC_DLD:
			return LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_SYNC_DLD,a_nPropValue);
		case LFT_SPPU_LMK_PROP_PLL_REF_DIVIDER:
			return LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_REF_Divider,a_nPropValue);
		case LFT_SPPU_LMK_PROP_PLL_N_DIVIDER:
			return LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_N_Divider ,a_nPropValue);
		case LFT_SPPU_LMK_PROP_PLL_CHARGE_PUMP_STATE:
			LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_ChargePump_state,&a_nLMKPropvalue);
			switch(a_nLMKPropvalue)
			{
			case 0:
				return *a_nPropValue =    LFT_SPPU_LMK_PROP_CPS_ACTIVE;
			case 1: 
				return *a_nPropValue =   LFT_SPPU_LMK_PROP_CPS_TRISTATE;		

			}
		case LFT_SPPU_LMK_PROP_PLL_CHARGE_PUMP_GAIN:
			LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_ChargePump_Gain,&a_nLMKPropvalue);
			switch(a_nLMKPropvalue)
			{
			case 0:
				return *a_nPropValue =    LFT_SPPU_LMK_PROP_CPG_100;
			case 1: 
				return *a_nPropValue =   LFT_SPPU_LMK_PROP_CPG_200;		
			case 2:
				return *a_nPropValue =    LFT_SPPU_LMK_PROP_CPG_400;
			case 3: 
				return *a_nPropValue =   LFT_SPPU_LMK_PROP_CPG_1600;		

			};


		case LFT_SPPU_LMK_PROP_PLL_CHARGE_PUMP_POLARITY:
			LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL1_ChargePump_polarity,&a_nLMKPropvalue);
			switch(a_nLMKPropvalue)
			{
			case 0:
				return *a_nPropValue =    LFT_SPPU_LMK_PROP_CPP_NEGATIVE_SLOPE;
			case 1: 
				return *a_nPropValue =   LFT_SPPU_LMK_PROP_CPP_POSITIVE_SLOPE;		
			}


		case LFT_SPPU_LMK_PROP_PLL2_XTAL_OCS : 
			return LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_XTAL_OSC  ,a_nPropValue);
		case LFT_SPPU_LMK_PROP_PLL2_SYNC_DLD :            
			return LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806, LFT_SPPU_LMK_PLL2_SYNC_DLD  ,a_nPropValue);
		case LFT_SPPU_LMK_PROP_PLL2_DLD_CNT :            
			return LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806, LFT_SPPU_LMK_PLL12_DLD_CNT ,a_nPropValue);
		case LFT_SPPU_LMK_PROP_PLL2_WND_SIZE: 
			LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_PLL_WIND_SIZE,&a_nLMKPropvalue);
			switch(a_nLMKPropvalue)
			{
			case 0:
				return *a_nPropValue =    LFT_SPPU_LMK_PROP_PLL_WND_SZ2_DATA1;

			}
		case LFT_SPPU_LMK_PROP_PLL2_REF_DIVIDER:
			return LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_REF_DIVIER,a_nPropValue);
		case LFT_SPPU_LMK_PROP_PLL2_N_CAL :
			return LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_N_CALL ,a_nPropValue);
		case LFT_SPPU_LMK_PROP_PLL2_N_DIVIDER :
			return LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806, LFT_SPPU_LMK_PLL2_N_DIVIDER ,a_nPropValue);
		case LFT_SPPU_LMK_PROP_PLL2_PRESCALAR :
			LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_PRESCALAR,&a_nLMKPropvalue);
			switch(a_nLMKPropvalue)
			{
			case 0:
				return *a_nPropValue =    LFT_SPPU_LMK_PROP_DIVIDER_2;
			case 1: 
				return *a_nPropValue =   LFT_SPPU_LMK_PROP_DIVIDER_3;		
			case 2:
				return *a_nPropValue =    LFT_SPPU_LMK_PROP_DIVIDER_4;
			case 3: 
				return *a_nPropValue =   LFT_SPPU_LMK_PROP_DIVIDER_5;		
			case 4: 
				return *a_nPropValue =   LFT_SPPU_LMK_PROP_DIVIDER_6;		
			case 5: 
				return *a_nPropValue =   LFT_SPPU_LMK_PROP_DIVIDER_7;		
			case 6: 
				return *a_nPropValue =   LFT_SPPU_LMK_PROP_DIVIDER_8;

			}

		case LFT_SPPU_LMK_PROP_PLL2_INPUT_FREQ  :
			LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_INPUT_FREQ,&a_nLMKPropvalue);
			switch(a_nLMKPropvalue)
			{
			case 0:
				return *a_nPropValue =    LFT_SPPU_LMK_PROP_PLL2_INPUT_FREQ_DATA1;
			case 1: 
				return *a_nPropValue =   LFT_SPPU_LMK_PROP_PLL2_INPUT_FREQ_DATA2;		
			case 2:
				return *a_nPropValue =    LFT_SPPU_LMK_PROP_PLL2_INPUT_FREQ_DATA3;
			case 3: 
				return *a_nPropValue =   LFT_SPPU_LMK_PROP_PLL2_INPUT_FREQ_DATA4;	

			};

		case LFT_SPPU_LMK_PROP_PLL2_2X_REF  :
			LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_2X_REF,&a_nLMKPropvalue);
			switch(a_nLMKPropvalue)
			{
			case 0:
				return *a_nPropValue =    LFT_SPPU_LMK_PROP_PLL2_2X_REF_FREQUENCY_NORMAL;
			case 1: 
				return *a_nPropValue =   LFT_SPPU_LMK_PROP_PLL2_2X_REF_FREQUENCY_DOUBLED;	
			}



		case LFT_SPPU_LMK_PROP_PLL2_FAST_PDF :
			LMKRegAccessRead(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_PLL2_FAST_PDF,&a_nLMKPropvalue);
			switch(a_nLMKPropvalue)
			{
			case 0:
				return *a_nPropValue =    LFT_SPPU_LMK_PROP_PLL2_FAST_PDF_LESS_THAN_EQ_100;
			case 1: 
				return *a_nPropValue =   LFT_SPPU_LMK_PROP_PLL2_FAST_PDF_GREATER_THAN_100;	
			};



		case LFT_SPPU_LMK_PROP_PLL2_R3 :
			switch((SPPULMKPropResistance)a_nPropValue)
			{
			case LFT_SPPU_LMK_PROP_RESISTANCE_200_OHMS :
				return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,  LFT_SPPU_LMK_PLL2_LOOP_FILTER_R3 ,0);
			case LFT_SPPU_LMK_PROP_RESISTANCE_1K_OHMS               :
				return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,  LFT_SPPU_LMK_PLL2_LOOP_FILTER_R3 ,1);
			case LFT_SPPU_LMK_PROP_RESISTANCE_2K_OHMS:
				return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,  LFT_SPPU_LMK_PLL2_LOOP_FILTER_R3 ,2);
			case LFT_SPPU_LMK_PROP_RESISTANCE_4K_OHMS:
				return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,  LFT_SPPU_LMK_PLL2_LOOP_FILTER_R3 ,3);
			case LFT_SPPU_LMK_PROP_RESISTANCE_16K_OHMS:
				return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,  LFT_SPPU_LMK_PLL2_LOOP_FILTER_R3 ,4);
			};

		case LFT_SPPU_LMK_PROP_PLL2_C3:
			switch  ((SPPULMKPropCapacitance3)a_nPropValue)
			{
			case LFT_SPPU_LMK_PROP_CAPACITANCE3_10_PF:  
				return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C3  ,0);
			case  LFT_SPPU_LMK_PROP_CAPACITANCE3_11_PF:       
				return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C3  ,1);
			case  LFT_SPPU_LMK_PROP_CAPACITANCE3_15_PF:     
				return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C3  ,2);
			case LFT_SPPU_LMK_PROP_CAPACITANCE3_16_PF:
				return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C3  ,3);
			case LFT_SPPU_LMK_PROP_CAPACITANCE3_19_PF:
				return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C3  ,4);

			case LFT_SPPU_LMK_PROP_CAPACITANCE3_20_PF :
				return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C3  ,5);
			case LFT_SPPU_LMK_PROP_CAPACITANCE3_24_PF :
				return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C3  ,6);
			case LFT_SPPU_LMK_PROP_CAPACITANCE3_25_PF :
				return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C3 ,7);
			case LFT_SPPU_LMK_PROP_CAPACITANCE3_29_PF :
				return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C3  ,8);
			case LFT_SPPU_LMK_PROP_CAPACITANCE3_30_PF :
				return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C3  ,9);
			case LFT_SPPU_LMK_PROP_CAPACITANCE3_33_PF :
				return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C3  ,10);
			case LFT_SPPU_LMK_PROP_CAPACITANCE3_34_PF :
				return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C3  ,11);
			case LFT_SPPU_LMK_PROP_CAPACITANCE3_38_PF :
				return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C3  ,12);
			case LFT_SPPU_LMK_PROP_CAPACITANCE3_39_PF:
				return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C3  ,13);
			};
		case LFT_SPPU_LMK_PROP_PLL2_R4:
			switch((SPPULMKPropResistance)a_nPropValue)
			{
			case LFT_SPPU_LMK_PROP_RESISTANCE_200_OHMS:
				return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,  LFT_SPPU_LMK_PLL2_LOOP_FILTER_R4 ,0);
			case LFT_SPPU_LMK_PROP_RESISTANCE_1K_OHMS:               
				return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,  LFT_SPPU_LMK_PLL2_LOOP_FILTER_R4 ,1);
			case LFT_SPPU_LMK_PROP_RESISTANCE_2K_OHMS:
				return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,  LFT_SPPU_LMK_PLL2_LOOP_FILTER_R4 ,2);
			case LFT_SPPU_LMK_PROP_RESISTANCE_4K_OHMS:
				return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,  LFT_SPPU_LMK_PLL2_LOOP_FILTER_R4 ,3);
			case LFT_SPPU_LMK_PROP_RESISTANCE_16K_OHMS:
				return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,  LFT_SPPU_LMK_PLL2_LOOP_FILTER_R4 ,4);
			};

		case LFT_SPPU_LMK_PROP_PLL2_C4  :  // doubt 
			switch  ((SPPULMKPropCapacitance4)a_nPropValue)
			{
			case LFT_SPPU_LMK_PROP_CAPACITANCE4_10_PF:  
				return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C4  ,0);
			case  LFT_SPPU_LMK_PROP_CAPACITANCE4_15_PF:       
				return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C4  ,1);
			case  LFT_SPPU_LMK_PROP_CAPACITANCE4_29_PF:     
				return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C4  ,2);
			case LFT_SPPU_LMK_PROP_CAPACITANCE4_34_PF:
				return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C4  ,3);
			case LFT_SPPU_LMK_PROP_CAPACITANCE4_47_PF:
				return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C4  ,4);

			case LFT_SPPU_LMK_PROP_CAPACITANCE4_52_PF :
				return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C4  ,5);
			case LFT_SPPU_LMK_PROP_CAPACITANCE4_66_PF :
				return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C4  ,6);
			case LFT_SPPU_LMK_PROP_CAPACITANCE4_71_PF :
				return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C4  ,7);
			case LFT_SPPU_LMK_PROP_CAPACITANCE4_103_PF :
				return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C4  ,8);
			case LFT_SPPU_LMK_PROP_CAPACITANCE4_108_PF :
				return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C4  ,9);
			case LFT_SPPU_LMK_PROP_CAPACITANCE4_122_PF :
				return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C4  ,10);
			case LFT_SPPU_LMK_PROP_CAPACITANCE4_126_PF :
				return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C4  ,11);
			case LFT_SPPU_LMK_PROP_CAPACITANCE4_141_PF :
				return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C4  ,12);
			case LFT_SPPU_LMK_PROP_CAPACITANCE4_146_PF:
				return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,LFT_SPPU_LMK_PLL2_LOOP_FILTER_C4  ,13);
			};



		case LFT_SPPU_LMK_PROP_PLL2_CHARGE_PUMP_STATE:
			switch((SPPULMKPropChargePumpState)a_nPropValue)
			{
			case  LFT_SPPU_LMK_PROP_CPS_ACTIVE :
				return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,  LFT_SPPU_LMK_PLL2_ChargePump_STATE   ,0);
			case LFT_SPPU_LMK_PROP_CPS_TRISTATE :
				return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,  LFT_SPPU_LMK_PLL2_ChargePump_STATE   ,1);
			}

		case LFT_SPPU_LMK_PROP_PLL2_CHARGE_PUMP_GAIN:
			switch((SPPULMKPropChargePumpGain)a_nPropValue)
			{
			case LFT_SPPU_LMK_PROP_CPG_100 :
				return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806, LFT_SPPU_LMK_PLL2_ChargePump_GAIN,0);
			case LFT_SPPU_LMK_PROP_CPG_200:
				return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806, LFT_SPPU_LMK_PLL2_ChargePump_GAIN,1);
			case LFT_SPPU_LMK_PROP_CPG_400 :
				return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806, LFT_SPPU_LMK_PLL2_ChargePump_GAIN,2);
			case LFT_SPPU_LMK_PROP_CPG_1600 :
				return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806, LFT_SPPU_LMK_PLL2_ChargePump_GAIN,3);
			};


		case LFT_SPPU_LMK_PROP_PLL2_CHARGE_PUMP_POLARITY:
			switch(( SPPULMKPropChargePumpPolarity)a_nPropValue)

			{
			case LFT_SPPU_LMK_PROP_CPP_NEGATIVE_SLOPE  :   
				return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,  LFT_SPPU_LMK_PLL2_ChargePump_polarity ,a_nPropValue);
			case LFT_SPPU_LMK_PROP_CPP_POSITIVE_SLOPE     :  
				return LMKRegAccessWrite(a_enConnectionType,a_nModuleID,LFT_SPPU_DEV_LMK04806,  LFT_SPPU_LMK_PLL2_ChargePump_polarity ,a_nPropValue);
			}






#endif
			return -1009;
		}

		long MiddleAPI::GetAttenuatorProperty(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,SPPUAttenuatorProp a_enAttenuatorProp,unsigned int *a_nPropValue)
		{
			//switch case 
			return -1009;
		}

		long MiddleAPI::SimRegWrite(unsigned int a_nAddress, unsigned int a_nValue, unsigned int a_nDeviceType)
		{

#define DEV_REG_MEM_SIZE_MAX 4096

			FILE * pFile;
			errno_t err;

			err	=	fopen_s(&pFile,"sim_mem.bin","r+b");
			if(err	==	0)
			{
				fseek(pFile, a_nDeviceType * DEV_REG_MEM_SIZE_MAX	+	a_nAddress, 0);
				fwrite((char *) (&a_nValue), sizeof(char), 4, pFile);
				fclose(pFile);
			}
			else
			{			
				printf("sim_mem.bin access denied \n");
				return -10001;
			}

			return 0;
		}

		long MiddleAPI::SimRegRead(unsigned int a_nAddress, unsigned int *a_nValue, unsigned int a_nDeviceType)
		{
#define DEV_REG_MEM_SIZE_MAX 4096
			FILE * pFile;
			errno_t err;

			err	=	fopen_s(&pFile,"sim_mem.bin","r+");
			if(err	==	0)
			{
				fseek(pFile, a_nAddress + a_nDeviceType * DEV_REG_MEM_SIZE_MAX, 0);
				char chArrValue[4];
				fread(chArrValue, sizeof(char), 4, pFile);
				int *pnVal	=	(int *)chArrValue;
				*a_nValue	=	*pnVal;
				fclose(pFile);
			}
			else
			{			
				printf("sim_mem.bin access denied \n");
				return -10001;
			}

			return 0;
		}

		void MiddleAPI::mPrintDebug(char *a_strDebug)
		{
			FILE * pFile;
			errno_t err;
			if((_access("debug.log", 0)) != -1)
			{
				if((_access("debug.log", 2)) != -1)
				{
					err	=	fopen_s(&pFile,"debug.log","a");
					if(err	==	0)
					{
						fputs(a_strDebug, pFile);
						fputs("\n",pFile);
						fclose(pFile);
					}
					else
					{
						printf("debug.log access denied \n");
					}
				} 
			}
		}

		void MiddleAPI::mPrintSelfTestLog(char *a_strDebug)
		{
			FILE * pFile;
			errno_t err;
			if((_access("SelfTest.log", 0)) != -1)
			{
				if((_access("SelfTest.log", 2)) != -1)
				{
					err	=	fopen_s(&pFile,"SelfTest.log","a");
					if(err	==	0)
					{
						fputs(a_strDebug, pFile);
						fputs("\n",pFile);
						fclose(pFile);
					}
					else
					{
						printf("SelfTest.log access denied \n");
					}
				} 
			}
		}

		MiddleAPI::~MiddleAPI()
		{

		}
		long MiddleAPI::RunTest_Parallelnorflash_SIC(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue)
		{
			mPrintDebug("+====================================+");
			mPrintDebug("|     RunTest_Parallelnorflash_SIC   |");
			mPrintDebug("|	               Start			  |");
			mPrintDebug("+====================================+");
			unsigned int saddr = 0;
			unsigned int readtest = 0;
			unsigned int blocksize = 1;
			unsigned int memory_busy = 0;
			unsigned int flash_busy = 0;
			unsigned int Block_write_ready = 0;
			unsigned int i = 0,j=0,k=0;
			unsigned int writefinal[256] ;
			FILE *rdBinFile, *wrBinFile; //file for write; // file to read
			int wcount, rcount;
			unsigned char *rdbuffArr;
			unsigned char *wrbuffArr;
			unsigned int write_byte;
			unsigned int read_byte;
			unsigned int word_count = 127;
			unsigned int temp1,temp2;
			char strDebug[DEBUG_STR_LEN]	=	{'\0'};
			char *infile = "self_test__parallelnorflash_SIC_write.bin";
			char *outfile = "self_test__parallelnorflash_SIC_read.bin";

			mPrintSelfTestLog("Self Test Parallelnor  Flash ");
			mPrintSelfTestLog("*************************************************************************");

			unsigned int bitFileType;
			FPGARegAccessRead(LFT_HOST_CONNECTION_SER  , a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_BitFile_Check, &bitFileType); 
			//RegRead(LFT_HOST_CONNECTION_SER,a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_BitFile_Check,&bitFileType);
			sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTest uart:Bit file %x)",bitFileType );
			mPrintDebug(strDebug);
			if(bitFileType !=2)
			{
				mPrintSelfTestLog("*********************  WRONG BIT FILE *************************************");
				mPrintDebug("*************************** Wrong bit file **************************************");
				*a_nPropValue = 2;
				return *a_nPropValue;

			}


			if(!ifstream (infile))
			{
				mPrintDebug("================File is not present===================");
				return *a_nPropValue = 1;
			}	
			
			/* opening the file */
			if(!(rdBinFile = fopen(infile,"rb")))
			{
				mPrintDebug("============FILE didnt open for read===============");
				return *a_nPropValue = 1;
			}
			mPrintDebug("============FILE open succesfully for read=========");	

			fseek(rdBinFile, 0, SEEK_END);
			int dwFileSize = ftell(rdBinFile);
			fseek(rdBinFile, 0, SEEK_SET);

			sprintf_s(strDebug, DEBUG_STR_LEN,"file size:%d",dwFileSize);
			mPrintDebug(strDebug);

			blocksize = (dwFileSize/256);
			word_count = ((blocksize*128)-1);

			sprintf_s(strDebug, DEBUG_STR_LEN,"\n  blocksize : %d    word_count : %d",blocksize,word_count);
			mPrintDebug(strDebug);
			unsigned int dummy=0;
			//mPrintDebug("\n ============================= Dummy read write =================================");
			//RegWrite(LFT_HOST_CONNECTION_SER,a_nModuleID, LFT_SPPU_DEV_FPGA, 0x4200,dummy);
			//RegRead(LFT_HOST_CONNECTION_SER,a_nModuleID, LFT_SPPU_DEV_FPGA, 0x4200,&dummy);

			int ret1 = RegWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_writedata,dummy);

			RegRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_writedata,&dummy);
			mPrintDebug("\n ============================= puts_block_sector_erase 1 =================================");

			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_AIPB_SIC_block_sector_erase,1);
			mPrintDebug("\n ============================= puts_block_sector_erase 0 =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_AIPB_SIC_block_sector_erase,0);

			mPrintDebug("\n ============================= puts_block_start_address =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_AIPB_SIC_strtadd,saddr);

			mPrintDebug("\n ============================= puts_word_count =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_AIPB_SIC_word_count,word_count);

			mPrintDebug("\n ============================= gets_controller_status =================================");
			FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_AIPB_SIC_memory_busy,&memory_busy);
			if(memory_busy == 1)
			{
				mPrintDebug("\n ============================= memory is busy =================================");
			}

			FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_AIPB_SIC_flash_busy,&flash_busy);
			if(flash_busy == 1)
			{
				mPrintDebug("\n ============================= flash is busy =================================");
			}
			FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_AIPB_SIC_Block_write_ready,&Block_write_ready);
			if(Block_write_ready == 1)
			{
				mPrintDebug("\n ============================= Block_write_ready =================================");
			}

			unsigned int memory_busy_check = 0;
			mPrintDebug("\n ============================= checking for freeing memory controller =================================");
			FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_memory_busy,&memory_busy_check);
			if(memory_busy_check == 1)
			{
				mPrintDebug("Fatal Error : Memory Controller must be free after restart/power on");
			}

			mPrintDebug("\n ============================= puts_page_write_start =================================");

			mPrintDebug("\n ============================= block_page_write 1 =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_block_page_write,1);

			mPrintDebug("\n ============================= block_page_write 0 =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_block_page_write,0);
			mPrintDebug("+====================================+");
			mPrintDebug("|              Write Operation        |");
			mPrintDebug("|	              Start here		  |");
			mPrintDebug("+====================================+");

			wrbuffArr = (unsigned char*)calloc(((word_count+1)*2), sizeof(char));
			rdbuffArr = (unsigned char*)calloc(((word_count+1)*2), sizeof(char));

			wcount = fread(wrbuffArr,1,((word_count+1)*2),rdBinFile);
			sprintf_s(strDebug, DEBUG_STR_LEN,"buffer is:%d",wcount);
			mPrintDebug(strDebug);
			int timeout = 10000;
			for(i = 0; i < (word_count+1);i++)
			{
				//if(i!=0)
				//{
				if(*a_nPropValue == 20)
				{


					mPrintDebug("********************break encounter*******************************");
					fclose(rdBinFile);
					*a_nPropValue = 1;
					return *a_nPropValue;
					//break;
				}
				while(timeout)
				{
					FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_Block_write_ready,&Block_write_ready);
					if(Block_write_ready == 0)
					{
						mPrintDebug("\n ============================= Block_write_ready  =================================");				
					}
					else
					{
						break;
					}
					timeout--;
					Sleep(100);
				}
				if(timeout==0)
				{
					mPrintDebug("\n ============================= timeout  =================================");	
					return *a_nPropValue =1;
				}
				//}

				temp1 = (unsigned int)(wrbuffArr[i*2] & 0xFF);
				temp2 = (unsigned int)((wrbuffArr[i*2+1]) & 0xFF);
				write_byte = (temp1 | (temp2 << 8));

				sprintf_s(strDebug, DEBUG_STR_LEN,"\n write count : %d    write_byte : %x  wrbuffArr : %x %x",i,write_byte,wrbuffArr[i*2+1],wrbuffArr[i*2]);
				mPrintDebug(strDebug);
				int k = FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_writedata,write_byte);
				if (k !=0)
				{
					mPrintDebug("\n ============================= Connection Intrupted =================================");
					return *a_nPropValue =1;
					break;
				}
			}


			mPrintDebug("\n ============================= Write Operation complete =================================");

			mPrintDebug("\n ============================= memory_busy_check =================================");
			timeout = 10;
			while(timeout)
			{
				FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_memory_busy,&memory_busy);
				if(memory_busy != 1)
				{
					break;
				}
				timeout--;
				Sleep(100);
			}
			if(timeout == 0)
			{
				mPrintDebug("\n =============================memory_busy_check Time Out =================================");
				return *a_nPropValue =1;
			}
			if(*a_nPropValue == 20)
			{


				mPrintDebug("********************break encounter*******************************");
				//fclose(rdBinFile);
				*a_nPropValue = 1;
				return *a_nPropValue;
				//break;
			}

			mPrintDebug("\n ============================= flash_busy_check =================================");
			timeout=10;
			while(timeout)
			{
				FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_flash_busy,&flash_busy);
				if(flash_busy != 1)
				{
					break;
				}
				timeout--;
				Sleep(100);
			}
			if(timeout == 0)
			{
				mPrintDebug("\n =============================Time Out =================================");
				return *a_nPropValue = 1;
			}


			mPrintDebug("\n ============================= block_read_ready =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_blockreadready,0);

			mPrintDebug("\n ============================= puts_block_start_address =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_AIPB_SIC_strtadd,saddr);

			mPrintDebug("\n ============================= puts_block_size =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_AIPB_SIC_block_size,blocksize*128);

			mPrintDebug("\n ============================= gets_controller_status =================================");
			FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_AIPB_SIC_memory_busy,&memory_busy);
			if(memory_busy == 1)
			{
				mPrintDebug("\n ============================= memory is busy =================================");
			}

			FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_AIPB_SIC_flash_busy,&flash_busy);
			if(flash_busy == 1)
			{
				mPrintDebug("\n ============================= flash is busy =================================");
			}
			FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_AIPB_SIC_Block_write_ready,&Block_write_ready);
			if(Block_write_ready == 1)
			{
				mPrintDebug("\n ============================= Block_write_ready =================================");
			}

			mPrintDebug("\n ============================= checking for freeing memory controller =================================");
			FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_memory_busy,&memory_busy_check);
			if(memory_busy_check == 1)
			{
				mPrintDebug("Fatal Error : Memory Controller must be free after restart/power on");
			}

			mPrintDebug("+====================================+");
			mPrintDebug("|              Read Operation        |");
			mPrintDebug("|	              Start here		  |");
			mPrintDebug("+====================================+");



			mPrintDebug("\n ============================= puts_block_read_start =================================");

			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_AIPB_SIC_block_read,1);

			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_AIPB_SIC_block_read,0);

			wrBinFile = fopen(outfile,"wb");

			unsigned int rw_status;
			for(i=0;i<(word_count+1);i++)
			{
				if(*a_nPropValue == 20)
				{


					mPrintDebug("********************break encounter*******************************");
					fclose(wrBinFile);
					*a_nPropValue = 1;
					return *a_nPropValue;
					//break;
				}
				FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_blockreadready,1);
				timeout=10;
				//while(timeout)
				do
				{
					FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_rw_status,&rw_status);
					//if((rw_status & 0x01) == 0)
					//{
					//	mPrintDebug("\n ============================= flash data valid is low =================================");
					//}
					//else
					//{
					//	break;
					//}
					//timeout--;
					//Sleep(100);
				}while((rw_status & 0x01) == 0);
				//if(timeout == 0)
				//{
				//	mPrintDebug("\n =============================Time Out =================================");
				//	return *a_nPropValue = 1;
				//}

				FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_readdata,&read_byte);

				rdbuffArr[i*2] = (char)(read_byte & 0xFF);
				rdbuffArr[i*2 + 1] = (char)((read_byte >> 8) & 0xFF);

				sprintf_s(strDebug, DEBUG_STR_LEN,"\n read count : %d    read_byte : %4x wrbuffArr : %x%x",i,read_byte,rdbuffArr[i*2+1],rdbuffArr[i*2]);
				mPrintDebug(strDebug);

				FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_blockreadready,0);
			}

			fwrite(rdbuffArr,((word_count+1)*2),1,wrBinFile);

			fclose(wrBinFile);
			fclose(rdBinFile);

			mPrintDebug("\n ============================= Read Operation complete =================================");

			int ret = 0;
			//ret = memcmp(rdbuffArr,wrbuffArr,256);
			sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn ret::(%d)", ret);
			mPrintDebug(strDebug);

			for(i=0;i<((word_count+1)*2);i++)
			{
				if(rdbuffArr[i] !=wrbuffArr[i])
				{
					ret = 1;
					sprintf_s(strDebug,DEBUG_STR_LEN,"Test fails at I = %d",i);
					mPrintDebug(strDebug);
					break;
				}

			}
			if (ret != 0)
			{
				mPrintSelfTestLog("Test Case 2 status = Fail");
			}
			else

			{
				mPrintSelfTestLog("Test Case 2 status = Pass");

			}

			////////////////////////   Puts Block Chip Erase /////////////////////////////

			unsigned int readDoneStatus=0;

			int counter =0;
			int staus   =0;
			int internalread=0;
			int dataMatchStatus =0;
			timeout=5000;
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_ChipErase,1);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_ChipErase,0);
			timeout=2000;
			mPrintDebug("\n ============================= flash_busy check =================================");
			while(timeout)
			{
				FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_flash_busy,&flash_busy);
				if((flash_busy & 0x01) != 1)
				{
					break;
				}
				timeout--;
				Sleep(100);
			}
			if(timeout == 0)
			{
				mPrintDebug("\n =============================flash_busy Time Out =================================");
				return *a_nPropValue = 1;
			}

			/////////////   Data gen Model   ///////////////////////////////////////////


			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DataGen_ModeSel,1);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DataGen_ModeSel,0);



			mPrintDebug("\n =============================readDoneStatus=================================");
			timeout=5000;
			while(timeout)
			{
				if(*a_nPropValue == 20)
				{


					mPrintDebug("********************break encounter*******************************");
					//fclose(wrBinFile);
					*a_nPropValue = 1;
					return *a_nPropValue;
					//break;
				}
				FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_Read_status,&readDoneStatus);
				if(counter == 1000)
				{
					counter = 0;
					staus   = 1;
					mPrintDebug("\n =============================Counter reached 1000 =================================");
					break;
				}
				if((readDoneStatus & 0x01) != 0)
				{
					break;
				}
				timeout--;
				Sleep(100);
			}
			if(timeout == 0)
			{
				mPrintDebug("\n =============================readDoneStatus Time Out =================================");
				return *a_nPropValue = 1;
			}
			unsigned int internlReadStatus=0;
			mPrintDebug("\n ============================= internal_data_rw_done status =================================");

			FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_internal_data_rw_done,&readDoneStatus);
			if(readDoneStatus == 1)
			{

				mPrintDebug("\n ============================= Write Cycle Complete =================================");

			}
			else
			{
				internalread =1;
				mPrintSelfTestLog("Internal Read Write  = Fail");

			}
			unsigned int dataMatch=0;
			FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DataMismatc_Check,&dataMatch);
			if(dataMatch == 1)
			{
				dataMatchStatus =1;
				mPrintDebug("\n =============================  Data Mis-MAtch  =================================");
				mPrintSelfTestLog("Internal Data MAtch   = Fail");

			}
			else
			{

				mPrintDebug("\n =============================Data MAtch  =================================");


			}

			//LFT_AIPB_SIC_internal_data_rw_done

			if(staus == 1)
			{
				mPrintSelfTestLog("Test Case 3 Status = Fail");
				mPrintDebug("\n Test Case 3 Status = Fail");
			}
			else
			{

				mPrintSelfTestLog("Test Case Status = Pass");
				mPrintDebug("Test Case Status = Pass");
			}

			mPrintSelfTestLog("**********************************************************************************************");
			if ( ( ret != 0 ) || ( staus==1 )|| ( dataMatchStatus ==1) || (internalread ==1) )
				*a_nPropValue = 1;
			else
				*a_nPropValue = 0;

			return *a_nPropValue;


		}

		long MiddleAPI::RunTest_DDR3(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue)
		{
			unsigned int size = 0x20000000; // changed for 512 MB size
			unsigned int writeStartAddr = 0;
			unsigned int readStartAddr  = 0;
			unsigned int writeEndAddr  =  size;
			unsigned int readEndAddr   =  size;
			unsigned int dataType      = 1;
			unsigned int rw_status;

			/// Chekar enable disable //// 0x0000028C 4 bit
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SCS_DDR3_checker,0);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SCS_DDR3_checker,1);

			///// DDR Sel 0x00000398 12th bit
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_FPGA_SCS_DDR_SEL,1);
			int timeout =10;
			while(timeout!=0)
			{
				FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_FPGA_SCS_DDR_INIT,&rw_status);
				if(rw_status!=0)
					break;
				Sleep(1);
				timeout--;
			}
			if(timeout==0)
			{
				return 1;
			}



		}
		/*
		long MiddleAPI::RunTest_DDR3(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue)
		{
			unsigned int size = 0x20000000; // changed for 512 MB size
			unsigned int writeStartAddr = 0;
			unsigned int readStartAddr  = 0;
			unsigned int writeEndAddr  =  size;
			unsigned int readEndAddr   =  size;
			unsigned int dataType      = 1;
			unsigned int rw_status;

			mPrintDebug("\n ============================= testcase_01_checker_to_ddr_write_read_test START =================================");

			mPrintDebug("\n ============================= checker_enable_disable 0 =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_checker,0);

			mPrintDebug("\n ============================= checker_enable_disable 1 =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_checker,1);


			mPrintDebug("\n ============================= wait_ddr_init_complete =================================");

			do
			{
				FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_wait_init,&rw_status);
			}while(rw_status == 0);

			mPrintDebug("\n ============================= DDR3 Initialization Completed =================================");

			mPrintDebug("\n ============================= configure_ddr3_write =================================");

			mPrintDebug("\n ============================= LFT_AIPB_SIC_DDR3_writeStartAddr =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_writeStartAddr,writeStartAddr);

			mPrintDebug("\n ============================= LFT_AIPB_SIC_DDR3_writeEndAddr =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_writeEndAddr,writeEndAddr);

			mPrintDebug("\n ============================= LFT_AIPB_SIC_DDR3_writeSize =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_writeSize,size);

			mPrintDebug("\n ============================= LFT_AIPB_SIC_DDR3_dataType =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_dataType,dataType);

			mPrintDebug("\n ============================= DDR3 configuration completes for Writing data =================================");

			mPrintDebug("\n ============================= Give Start Pulse for writing data pulse 1=================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_WritePulse,1);

			mPrintDebug("\n ============================= Give Start Pulse for writing data pulse 0=================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_WritePulse,0);

			mPrintDebug("\n ============================= Waiting for Write Done =================================");

			do
			{
				FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_WriteDone,&rw_status);
			}while(rw_status == 0);

			mPrintDebug("\n ============================= Writing data into DDR3 Completed =================================");

			mPrintDebug("\n ============================= DDR3 Reading Configuration Starts =================================");

			mPrintDebug("\n ============================= LFT_AIPB_SIC_DDR3_readStartAddr =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_readStartAddr,readStartAddr);

			mPrintDebug("\n ============================= LFT_AIPB_SIC_DDR3_readEndAddr =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_readEndAddr,readEndAddr);

			mPrintDebug("\n ============================= LFT_AIPB_SIC_DDR3_readSize =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_readSize,size);

			mPrintDebug("\n ============================= LFT_AIPB_SIC_DDR3_dataType =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_dataType,dataType);

			mPrintDebug("\n ============================= DDR3 configuration completes for Reading data =================================");

			mPrintDebug("\n ============================= Give Start Pulse for Reading data pulse 1=================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_ReadPulse,1);

			mPrintDebug("\n ============================= Give Start Pulse for Reading data pulse 0=================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_ReadPulse,0);

			mPrintDebug("\n ============================= Waiting for Read Done =================================");

			do
			{
				FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_ReadDone,&rw_status);
			}while(rw_status == 0);

			mPrintDebug("\n ============================= Reading data from DDR3 Completed =================================");

			mPrintDebug("\n ============================= CheckerResult =================================");

			FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_CheckerResult,&rw_status);
			if((rw_status & 0x1) == 1)
			{
				mPrintDebug("\n ============================= DATA MISMATCH FOUND WHILE READING DDR3 =================================");
				*a_nPropValue = 1;
			}
			else
			{
				mPrintDebug("\n ============================= NO ERROR FOUND WHILE READING DATA FROM DDR3 =================================");
				*a_nPropValue = 0;
			}

			return *a_nPropValue;
		}
		*/
		long MiddleAPI::RunTest_DDR3_test_case_2(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue)
		{
			mPrintSelfTestLog("DDR3 Self Test Start");
			mPrintSelfTestLog("********************************************************************************");
			unsigned int size = 0x00001000;
			unsigned int writeStartAddr = 0;
			unsigned int readStartAddr  = 0;
			unsigned int writeEndAddr  =  size;
			unsigned int readEndAddr   =  size;
			unsigned int dataType      = 1;
			unsigned int rw_status;

			FILE *rdBinFile;
			FILE *wrBinFile;

			char strDebug[DEBUG_STR_LEN]	=	{'\0'};


			unsigned int numBytesWr;
			unsigned int numBytesRd;
			char *infile = "self_test_DDR3_write.bin";
			char *outfile = "self_test_DDR3_read.bin";

			unsigned int bitFileType;
			FPGARegAccessRead(LFT_HOST_CONNECTION_SER  , a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_BitFile_Check, &bitFileType); 
			//RegRead(LFT_HOST_CONNECTION_SER,a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_BitFile_Check,&bitFileType);
			sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTest uart:Bit file %x)",bitFileType );
			mPrintDebug(strDebug);

			if(bitFileType !=11)
			{
				mPrintSelfTestLog("*********************  WRONG BIT FILE *************************************");
				mPrintDebug("*******************************WRONG BIT FILE ***********************************");
				*a_nPropValue = 2;
				return *a_nPropValue;

			}

			if(!(rdBinFile = fopen(infile,"rb")))
			{
				mPrintDebug("============FILE didnt open for read===============");
				return 1;	
			}
			mPrintDebug("============FILE open succesfully for read=========");	

			fseek(rdBinFile, 0, SEEK_END);
			int dwFileSize = ftell(rdBinFile);
			fseek(rdBinFile, 0, SEEK_SET);


			if(dwFileSize < 0x20000000)
			{
				writeEndAddr = dwFileSize;
				readEndAddr = dwFileSize;
			}
			else
			{
				writeEndAddr = 0x20000000;
				readEndAddr = 0x20000000;
			}

			fclose(rdBinFile);



			mPrintDebug("\n ============================= testcase_02_uart_to_ddr_write_read_test START =================================");

			mPrintDebug("\n ============================= checker_enable_disable 0 =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_checker,0);


			int timeout=5;
			while(timeout)
			{
				FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_wait_init,&rw_status);
				if(rw_status == 0)
				{
					mPrintDebug("\n ============================= wait_ddr_init_complete =================================");
				}
				else
				{
					break;
				}
				timeout--;
				Sleep(10);
			}
			if(timeout == 0)
			{
				mPrintDebug("\n =============================Time Out =================================");
				return *a_nPropValue = 1;
			}

			mPrintDebug("\n ============================= DDR3 Initialization Completed =================================");

			mPrintDebug("\n ============================= uart_configure_ddr3_write =================================");

			mPrintDebug("\n ============================= LFT_AIPB_SIC_DDR3_writeStartAddr =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_writeStartAddr,writeStartAddr);

			mPrintDebug("\n ============================= LFT_AIPB_SIC_DDR3_writeEndAddr =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_writeEndAddr,writeEndAddr);

			mPrintDebug("\n ============================= DDR3 configuration completes for Writing data =================================");

			mPrintDebug("\n ============================= Give Start Pulse for writing data =================================");

			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_UART_SEND_WritePulse,1);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_UART_SEND_WritePulse,0);

			mPrintDebug("\n ============================= FileWrite START =================================");

			unsigned int rcvdLen;
			char byArrPktResp[256];

			objSerialAPI.FileWrite(0x4200,writeEndAddr,infile,&numBytesWr);


			timeout=10;
			while(timeout)
			{
				FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_WriteDone,&rw_status);
				if(rw_status == 0)
				{
					mPrintDebug("\n ============================= Waiting for Write Done =================================");
				}
				else
				{
					break;
				}
				timeout--;
				Sleep(10);
			}
			if(timeout == 0)
			{
				mPrintDebug("\n =============================Time Out =================================");
				return *a_nPropValue = 1;
			}

			mPrintDebug("\n ============================= Writing data into DDR3 Completed =================================");

			mPrintDebug("\n ============================= DDR3 Reading Configuration Starts =================================");

			mPrintDebug("\n ============================= LFT_AIPB_SIC_DDR3_readStartAddr =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_readStartAddr,readStartAddr);

			mPrintDebug("\n ============================= LFT_AIPB_SIC_DDR3_readEndAddr =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_readEndAddr,readEndAddr);

			mPrintDebug("\n ============================= DDR3 configuration completes for Reading data =================================");

			mPrintDebug("\n ============================= Give Start Pulse for Reading data pulse =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_UART_SEND_ReadPulse,1);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_UART_SEND_ReadPulse,0);

			mPrintDebug("\n ============================= FileRead START =================================");

			objSerialAPI.FileRead(0X4200,writeEndAddr,outfile,&numBytesRd);

			timeout=10;
			while(timeout)
			{
				FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_ReadDone,&rw_status);
				if(rw_status == 0)	
				{
					mPrintDebug("\n ============================= Waiting for Read Done =================================");	
				}
				else
				{
					break;
				}
				timeout--;
				Sleep(10);
			}
			if(timeout == 0)
			{
				mPrintDebug("\n =============================Time Out =================================");
				return *a_nPropValue = 1;
			}

			mPrintDebug("\n ============================= Reading data from DDR3 Completed =================================");

			mPrintDebug("\n ============================= CheckerResult =================================");


			char *wrbuffArr = (char *)calloc(dwFileSize, sizeof(char));
			char *rdbuffArr = (char *)calloc(dwFileSize, sizeof(char));

			if(!(rdBinFile = fopen(infile,"rb")))
			{
				mPrintDebug("============FILE didnt open for read===============");
				return *a_nPropValue =1;
			}
			fread(wrbuffArr,1,dwFileSize, rdBinFile);


			fclose(rdBinFile);

			if(!(wrBinFile = fopen(outfile,"rb")))
			{
				mPrintDebug("============FILE didnt open for read===============");
				return *a_nPropValue =1;
			}
			fread(rdbuffArr,1,dwFileSize, wrBinFile);
			fclose(wrBinFile);

			int ret = 0;
			int fileReadWrite_Result =0;
			ret = memcmp(wrbuffArr,rdbuffArr,dwFileSize);

			//if((numBytesRd == 256) && (numBytesWr == 256))
			if(ret !=0)
			{
				fileReadWrite_Result =1;
				mPrintSelfTestLog("DDR3 test case 2 Status =     Fail ");
				//*a_nPropValue = 1; 
			}
			else
			{
				fileReadWrite_Result = 0;

				mPrintSelfTestLog("DDR3 test case 2 Status =     Pass ");
				//*a_nPropValue = 0; 
			}


			//if((numBytesRd == 4096) && (numBytesWr == 4096))
			//{

			//	mPrintSelfTestLog("DDR3 test case 2 Status =     Pass ");
			//}
			//else
			//{

			//	mPrintSelfTestLog("DDR3 test case 2 Status =     Fail ");
			//}
			// Commented by shivendra 25 -04 -2016 



			mPrintDebug("\n ============================= DDR3 Test Case 1  =================================");


			size = 0x00000800;
			writeStartAddr = 0;
			readStartAddr  = 0;
			writeEndAddr  =  size;
			readEndAddr   =  size;
			dataType      = 1;
			rw_status;
			mPrintDebug("\n ============================= checker_enable_disable 0 =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_checker,0);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_checker,1);

			mPrintDebug("\n ============================= wait_ddr_init_complete =================================");
			timeout=10;
			while(timeout)
			{
				FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_wait_init,&rw_status);
				if(rw_status == 0)	
				{
					mPrintDebug("\n ============================= Waiting for Read Done =================================");	
				}
				else
				{
					break;
				}
				timeout--;
				Sleep(10);
			}
			if(timeout == 0)
			{
				mPrintDebug("\n =============================Time Out =================================");
				return *a_nPropValue = 1;
			}

			mPrintDebug("\n ============================= LFT_AIPB_SIC_DDR3_writeStartAddr =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_writeStartAddr,writeStartAddr);

			mPrintDebug("\n ============================= LFT_AIPB_SIC_DDR3_writeEndAddr =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_writeEndAddr,writeEndAddr);

			mPrintDebug("\n ============================= Write size value at register 0x0000 =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_WriteSize,writeEndAddr);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_dataType, dataType);

			mPrintDebug("\n ============================= Give Start Pulse for writing data =================================");

			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_UART_SEND_WritePulse,1);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_UART_SEND_WritePulse,0);

			mPrintDebug("\n ============================= Waiting for Write Done =================================");
			timeout=10;
			while(timeout)
			{
				FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_WriteDone,&rw_status);
				if(rw_status == 0)	
				{
					mPrintDebug("\n ============================= Waiting for Read Done =================================");	
				}
				else
				{
					break;
				}
				timeout--;
				Sleep(10);
			}
			if(timeout == 0)
			{
				mPrintDebug("\n =============================Time Out =================================");
				return *a_nPropValue = 1;
			}

			mPrintDebug("\n ============================= Writing data into DDR3 Completed =================================");

			mPrintDebug("\n ============================= DDR3 Reading Configuration Starts =================================");



			mPrintDebug("\n ============================= LFT_AIPB_SIC_DDR3_readStartAddr =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_readStartAddr,readStartAddr);

			mPrintDebug("\n ============================= LFT_AIPB_SIC_DDR3_readEndAddr =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_readEndAddr,readEndAddr);

			mPrintDebug("\n ============================= Read Size     =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_readSize,size);

			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_dataType, dataType);

			mPrintDebug("\n ============================= Give Start Pulse for Reading data pulse =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_UART_SEND_ReadPulse,1);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_UART_SEND_ReadPulse,0);

			mPrintDebug("\n ============================= Waiting for Read Done =================================");
			timeout=10;
			while(timeout)
			{

				FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_ReadDone,&rw_status);
				if(rw_status == 0)	
				{
					mPrintDebug("\n ============================= Waiting for Read Done =================================");	
				}
				else
				{
					break;
				}
				timeout--;
				Sleep(10);
			}
			if(timeout == 0)
			{
				mPrintDebug("\n =============================Time Out =================================");
				return *a_nPropValue = 1;
			}

			mPrintDebug("\n ============================= CheckResult  =================================");

			unsigned int resultStat =0;
			FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_CheckerResult,&resultStat);

			if(resultStat !=1)
			{

				mPrintSelfTestLog("DDR3 Test Case 1 Status =   Pass");
			}
			else
			{

				mPrintSelfTestLog("DDR3 Test Case 1 Status =   Fail");
			}

			if(fileReadWrite_Result == 0 && (resultStat !=1))
			{
				*a_nPropValue = 0; 
			}
			else
			{
				*a_nPropValue = 1; 
			}
			return *a_nPropValue;
		}
		long MiddleAPI::RunTest_ethernet(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue)
		{

			mPrintSelfTestLog("*********************  Ethernet Self test start *************************************");
			mPrintDebug("*************************    Ethernet Self test start ***********************************");


			unsigned int i = 0;
			unsigned int test_result = 0;
			unsigned int wr_val = 0;
			unsigned int rd_val = 0;
			char strDebug[DEBUG_STR_LEN]	=	{'\0'};
			unsigned int numBytesWr;
			unsigned int numBytesRd;
			FILE *rdBinFile, *wrBinFile; //file for write; // file to read
			int wcount, rcount;
			unsigned int write_byte;
			unsigned int read_byte;
			unsigned char *wrbuffArr;
			unsigned char *rdbuffArr;
			char *infile = "self_test_eth_write.bin";
			char *outfile = "self_test_eth_read.bin";

			unsigned int bitFileType;
			FPGARegAccessRead(LFT_HOST_CONNECTION_ETH  , a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_BitFile_Check, &bitFileType); 
			//RegRead(LFT_HOST_CONNECTION_SER,a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_BitFile_Check,&bitFileType);
			sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTest uart:Bit file %x)",bitFileType );
			mPrintDebug(strDebug);

			if(bitFileType !=12)
			{
				mPrintSelfTestLog("*********************  WRONG BIT FILE *************************************");
				mPrintDebug("*******************************WRONG BIT FILE ***********************************");
				/*	*a_nPropValue = 2;
				return *a_nPropValue;*/

			}

			mPrintDebug("\n ============================= register address 0x00 write read 1000 time  START=================================");
			test_result = 0;
			for(i=0;i<100;i++)
			{
				wr_val = i & 0xFFFFFFFF;
				FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_AIPB_SIC_ETH_reg_0,wr_val);
				FPGARegAccessRead(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_AIPB_SIC_ETH_reg_0,&rd_val);
				if(*a_nPropValue == 20)
				{
					mPrintDebug("********************break encounter*******************************");
					*a_nPropValue = 1;
					return *a_nPropValue;
					//break;
				} 

				if(wr_val != rd_val)
				{
					test_result++;
					sprintf_s(strDebug, DEBUG_STR_LEN,"Test Fail at i = %d",i);
					mPrintDebug(strDebug);
					*a_nPropValue = 1;
					break;
				}
				else
				{
					*a_nPropValue = 0;
				}
			}

			mPrintDebug("\n ============================= register address 0x00 write read 1000 time Done=================================");


			mPrintDebug("\n ============================= register address 0x4 write read 1000 time  START=================================");
			test_result = 0;
			for(i=0;i<100;i++)
			{
				wr_val = i & 0xFFFFFFFF;
				FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_AIPB_SIC_ETH_reg_4,wr_val);
				FPGARegAccessRead(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_AIPB_SIC_ETH_reg_4,&rd_val);
				sprintf_s(strDebug, DEBUG_STR_LEN," i = %d    rd_val : %d",i,rd_val);
				mPrintDebug(strDebug);

				if(*a_nPropValue == 20)
				{
					mPrintDebug("********************break encounter*******************************");
					*a_nPropValue = 1;
					return *a_nPropValue;
					//break;
				} 
				if(rd_val != 0x12345678)
				{
					test_result++;
					sprintf_s(strDebug, DEBUG_STR_LEN,"Test Fail at i = %d",i);
					mPrintDebug(strDebug);
					*a_nPropValue = 1;
					break;
				}
				else
				{
					*a_nPropValue = 0;
				}
			}

			mPrintDebug("\n ============================= register address 0x4 write read 1000 time Done=================================");

			if(!ifstream (infile))
			{
				mPrintDebug("================File is not present===================");
				return -1;
			}	

			/* opening the file */
			if(!(rdBinFile = fopen(infile,"rb")))
			{
				mPrintDebug("============FILE didnt open for read===============");
				return -1;	
			}
			mPrintDebug("============FILE open succesfully for read=========");	

			fseek(rdBinFile, 0, SEEK_END);
			int dwFileSize = ftell(rdBinFile);
			fseek(rdBinFile, 0, SEEK_SET);

			sprintf_s(strDebug, DEBUG_STR_LEN,"file size:%d",dwFileSize);
			mPrintDebug(strDebug);

			wrbuffArr = (unsigned char*)calloc(dwFileSize, sizeof(char));
			rdbuffArr = (unsigned char*)calloc(dwFileSize, sizeof(char));

			wcount = fread(wrbuffArr,1,dwFileSize, rdBinFile);
			sprintf_s(strDebug, DEBUG_STR_LEN,"buffer is:%d",wcount);
			mPrintDebug(strDebug);

			wrBinFile = fopen(outfile,"wb");

			mPrintDebug("\n ============================= FIFO write read 1000 time START=================================");

			for(i = 0; i < (dwFileSize/4);i++)
			{
				sprintf_s(strDebug, DEBUG_STR_LEN,"Write read count is :: %d",i);
				mPrintDebug(strDebug); 


				wr_val = (unsigned int)((wrbuffArr[i*4])|(wrbuffArr[i*4+1] << 8)|(wrbuffArr[i*4+2] <<16)|(wrbuffArr[i*4+3] << 24));
				FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_AIPB_SIC_ETH_reg_fifo,wr_val);
				FPGARegAccessRead(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_AIPB_SIC_ETH_reg_fifo,&rd_val);
				rdbuffArr[(i*4)]   = (rd_val & 0xFF);
				rdbuffArr[(i*4)+1] = ((rd_val >> 8) & 0xFF);
				rdbuffArr[(i*4)+2] = ((rd_val >> 16)& 0xFF);
				rdbuffArr[(i*4)+3] = ((rd_val >> 24)& 0xFF);

				if(*a_nPropValue == 20)
				{
					mPrintDebug("********************break encounter*******************************");
					fclose(rdBinFile);
					fclose(wrBinFile);
					*a_nPropValue = 1;
					return *a_nPropValue;
					//break;
				}
				/*if(rd_val != wr_val)
				{
				test_result++;
				sprintf_s(strDebug, DEBUG_STR_LEN,"Test Fail at i = %d",i);
				mPrintDebug(strDebug);
				*a_nPropValue = 1;
				break;
				}
				else
				{
				*a_nPropValue = 0;
				}*/
			}
			fwrite(rdbuffArr,1,dwFileSize,wrBinFile);
			fclose(wrBinFile);
			fclose(rdBinFile);

			int ret = 0;
			ret = memcmp(wrbuffArr,rdbuffArr,dwFileSize);

			//if((numBytesRd == 256) && (numBytesWr == 256))
			if(ret !=0)
			{
				*a_nPropValue = 1; 
			}
			else
			{
				*a_nPropValue = 0; 
			}

			mPrintDebug("\n ============================= FIFO write read 1024 time DONE=================================");


			mPrintSelfTestLog("*********************  Ethernet Self test End *************************************");
			mPrintDebug("*************************    Ethernet Self test End ***********************************");




			return *a_nPropValue;
		}
		long MiddleAPI::RunTest_EMMC(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue)
		{
			mPrintDebug("\n ============================= ================================");
			mPrintDebug("\n ===========================Run Test EMMC ===========================");

			mPrintDebug("\n ============================= ================================");

			unsigned int i = 0;
			unsigned int test_result = 0;
			unsigned int wr_val = 0;
			unsigned int rd_val = 0;
			char strDebug[DEBUG_STR_LEN]	=	{'\0'};
			unsigned int numBytesWr;
			unsigned int numBytesRd;
			FILE *rdBinFile, *wrBinFile; //file for write; // file to read
			int wcount, rcount;
			unsigned char *rdbuffArr;
			unsigned char *wrbuffArr;
			unsigned int write_byte;
			unsigned int read_byte;
			unsigned int temp1,temp2,temp3,temp4;

			unsigned int bitFileType;
			FPGARegAccessRead(LFT_HOST_CONNECTION_SER  , a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_BitFile_Check, &bitFileType); 
			sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTest uart:Bit file %x)",bitFileType );
			mPrintDebug(strDebug);
			if( bitFileType!= 6)
			{
				mPrintSelfTestLog("*********************  WRONG BIT FILE *************************************");
				*a_nPropValue = 2;
				return *a_nPropValue;

			}

			FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_Reset,1);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_Reset,0);
			Sleep(1000);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CLCK_SEL,0);
			Sleep(5000);

			//RegRead(LFT_HOST_CONNECTION_SER,a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_BitFile_Check,&bitFileType);



			char *infile = "self_test_emmc_write.bin";
			char *outfile = "self_test_emmc_read.bin";

			mPrintDebug("\n ============================= test_emmc START =================================");

			mPrintDebug("\n ============================= cmd_value =================================");

			wr_val = 0xF0F0F0F0;
			int ret1 = FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_ARG,wr_val);

			wr_val = 0xFFFFFFFF & 0x40;
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_INDEX,wr_val);

			//	mPrintDebug("\n ============================= send_cmd_en =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_SND_EN,1);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_SND_EN,0);
			//	mPrintDebug("\n ===================== Cmd send pulse generated...==========================");

			Sleep(1000);


			mPrintDebug("\n ============================= cmd_value =================================");

			wr_val = 0xFFFFFFFA;
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_ARG,wr_val);

			wr_val = 0xFFFFFFFF & 0x40;
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_INDEX,wr_val);

			//	mPrintDebug("\n ============================= send_cmd_en =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_SND_EN,1);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_SND_EN,0);
			//	mPrintDebug("\n ===================== Cmd send pulse generated...==========================");

			Sleep(1000);


			mPrintDebug("\n ============================= cmd_value =================================");

			wr_val = 0x00000000;
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_ARG,wr_val);

			wr_val = 0xFFFFFFFF & 0x40;
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_INDEX,wr_val);

			//	mPrintDebug("\n ============================= send_cmd_en =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_SND_EN,1);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_SND_EN,0);
			//	mPrintDebug("\n ===================== Cmd send pulse generated...==========================");

			Sleep(1000);

			//	mPrintDebug("\n ===================== Cmd format type set...==========================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_FRMT,0);

			mPrintDebug("\n ============================= cmd_value =================================");

			wr_val = 0xC0FF8080;
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_ARG,wr_val);

			wr_val = 0xFFFFFFFF & 0x41;
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_INDEX,wr_val);

			//	mPrintDebug("\n ============================= send_cmd_en =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_SND_EN,1);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_SND_EN,0);
			//	mPrintDebug("\n ===================== Cmd send pulse generated...==========================");

			Sleep(1000);
			int timeout=10;
			while(timeout)
			{
				if(*a_nPropValue == 20)
				{


					mPrintDebug("********************break encounter*******************************");
					*a_nPropValue = 1;
					return *a_nPropValue;
					break;
				}

				Sleep(1000);
				FPGARegAccessRead(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_REG_60,&rd_val);
				if((rd_val & 0x0000FFFF) != 0x00003fc0)
				{
					mPrintDebug("\n ============================= cmd_value =================================");

					wr_val = 0xC0FF8080;
					FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_ARG,wr_val);

					wr_val = 0xFFFFFFFF & 0x41;
					FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_INDEX,wr_val);

					//		mPrintDebug("\n ============================= send_cmd_en =================================");
					FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_SND_EN,1);
					FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_SND_EN,0);
					//		mPrintDebug("\n ===================== Cmd send pulse generated...==========================");

					//	mPrintDebug("\n ============================= reading reg 60 again =================================");
				}
				if((rd_val & 0x0000FFFF) == 0x00003fc0)
				{
					break;
				}
				timeout--;
			}
			if(timeout == 0)
			{
				mPrintDebug("\n =============================Time Out =================================");
				return *a_nPropValue =1;
			}

			Sleep(3000);
			//	mPrintDebug("\n ===================== Cmd format type set...==========================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_FRMT,1);

			mPrintDebug("\n ============================= cmd_value =================================");

			wr_val = 0x00000000;
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_ARG,wr_val);

			wr_val = 0xFFFFFFFF & 0x42;
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_INDEX,wr_val);

			//	mPrintDebug("\n ============================= send_cmd_en =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_SND_EN,1);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_SND_EN,0);
			//	mPrintDebug("\n ===================== Cmd send pulse generated...==========================");
			Sleep(3000);
			//	mPrintDebug("\n ===================== Cmd format type set...==========================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_FRMT,0);

			mPrintDebug("\n ============================= cmd_value =================================");

			wr_val = 0x00100000;
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_ARG,wr_val);

			wr_val = 0xFFFFFFFF & 0x43;
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_INDEX,wr_val);
			//	mPrintDebug("\n ============================= send_cmd_en =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_SND_EN,1);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_SND_EN,0);
			//	mPrintDebug("\n ===================== Cmd send pulse generated...==========================");

			Sleep(3000);
			//	mPrintDebug("\n ===================== Cmd format type set...==========================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_FRMT,0);

			mPrintDebug("\n ============================= cmd_value =================================");

			wr_val = 0x00100000;
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_ARG,wr_val);

			wr_val = 0xFFFFFFFF & 0x47;
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_INDEX,wr_val);

			//	mPrintDebug("\n ============================= send_cmd_en =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_SND_EN,1);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_SND_EN,0);
			//	mPrintDebug("\n ===================== Cmd send pulse generated...==========================");

			Sleep(3000);

			if(*a_nPropValue == 20)
			{


				mPrintDebug("********************break encounter*******************************");
				*a_nPropValue = 1;
				return *a_nPropValue;
				//break;
			}
			mPrintDebug("\n ============================= cmd_value =================================");

			wr_val = 0x03B90100;
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_ARG,wr_val);

			wr_val = 0xFFFFFFFF & 0x46;
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_INDEX,wr_val);

			//	mPrintDebug("\n ============================= send_cmd_en =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_SND_EN,1);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_SND_EN,0);
			//	mPrintDebug("\n ===================== Cmd send pulse generated...==========================");
			Sleep(1000);
			timeout=10;
			while(timeout)
			{
				if(*a_nPropValue == 20)
				{


					mPrintDebug("********************break encounter*******************************");
					*a_nPropValue = 1;
					return *a_nPropValue;
					//break;
				}

				FPGARegAccessRead(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_6,&rd_val);
				if(rd_val == 1)
				{
					break;
				}
				else if(rd_val != 1)
				{
					mPrintDebug("\n ============================= waiting after CMD6 =================================");
				}
				timeout--;
			}
			if(timeout == 0)
			{
				mPrintDebug("\n =============================Time Out =================================");
				return *a_nPropValue =1;
			}
			Sleep(3000);
			//	mPrintDebug("\n ============================= setting clock to 26Mhz =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CLCK_SEL,1);
			Sleep(5000);

			mPrintDebug("\n ============================= cmd_value =================================");

			wr_val = 0x03B70200;
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_ARG,wr_val);

			wr_val = 0xFFFFFFFF & 0x46;
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_INDEX,wr_val);

			//	mPrintDebug("\n ============================= send_cmd_en =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_SND_EN,1);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_SND_EN,0);
			//	mPrintDebug("\n ===================== Cmd send pulse generated...==========================");

			Sleep(1000);
			timeout=10;
			while(timeout)
			{
				if(*a_nPropValue == 20)
				{


					mPrintDebug("********************break encounter*******************************");
					*a_nPropValue = 1;
					return *a_nPropValue;
					//break;
				}

				FPGARegAccessRead(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_6,&rd_val);
				if(rd_val != 1)
				{
					mPrintDebug("\n ============================= waiting after CMD6, 2nd =================================");
				}
				else
				{
					break;
				}
				timeout--;
			}
			if(timeout == 0)
			{
				mPrintDebug("\n =============================Time Out =================================");
				return *a_nPropValue =1;
			}
			Sleep(10000);

			mPrintDebug("\n ============================= cmd_value =================================");




			mPrintDebug("\n ============================= data_tx start =================================");


			if(!ifstream (infile))
			{
				mPrintDebug("================File is not present===================");
				return -1;
			}	

			/* opening the file */
			if(!(rdBinFile = fopen(infile,"rb")))
			{
				mPrintDebug("============FILE didnt open for read===============");
				return -1;	
			}
			mPrintDebug("============FILE open succesfully for read=========");	

			fseek(rdBinFile, 0, SEEK_END);
			int dwFileSize = ftell(rdBinFile);
			fseek(rdBinFile, 0, SEEK_SET);

			//if(dwFileSize < 0x40000000)
			//{
			//	
			//}

			wrbuffArr = (unsigned char*)calloc(dwFileSize, sizeof(char));
			rdbuffArr = (unsigned char*)calloc(dwFileSize, sizeof(char));

			wcount = fread(wrbuffArr,1,dwFileSize,rdBinFile);
			tic();
			for(int j =0; j<dwFileSize/32 ; j++)
			{
				wr_val = j + 0x00000010;
				FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_ARG,wr_val);

				wr_val = 0xFFFFFFFF & 0x58;
				FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_INDEX,wr_val);

				//	mPrintDebug("\n ============================= send_cmd_en =================================");
				FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_SND_EN,1);
				FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_SND_EN,0);
				//	mPrintDebug("\n ===================== Cmd send pulse generated...==========================");


				for(i = 1; i <= 8;i++)
				{
					if(*a_nPropValue == 20)
					{


						mPrintDebug("********************break encounter*******************************");
						fclose(wrBinFile);
						*a_nPropValue = 1;
						return *a_nPropValue;
						//break;
					}

					temp1 = (unsigned int)(wrbuffArr[(i-1)*4 + 32*j ] & 0xFF);
					temp2 = (unsigned int)((wrbuffArr[(i-1)*4+1 + 32*j ]) & 0xFF);
					temp3 = (unsigned int)((wrbuffArr[(i-1)*4+2 + 32*j  ]) & 0xFF);
					temp4 = (unsigned int)((wrbuffArr[(i-1)*4+3 + 32*j ]) & 0xFF);
					write_byte = (temp1 | (temp2 << 8) | (temp3 << 16) | (temp4 << 24));
					FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,SPPUFPGARegsDefs(LFT_CENT_EMMC_REG_ADDR + (i*4)*0x10000),write_byte);
				}

				FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_DATA_SND_EN,1);
				FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_DATA_SND_EN,0);
				Sleep(2000);
			}
			mPrintDebug("\n ============================= cmd_value =================================");

			//wr_val = 0x00000011;
			//FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_ARG,wr_val);

			//wr_val = 0xFFFFFFFF & 0x58;
			//FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_INDEX,wr_val);

			////	mPrintDebug("\n ============================= send_cmd_en =================================");
			//FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_SND_EN,1);
			//FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_SND_EN,0);

			//for(i = 1; i <= 8;i++)
			//{
			//	if(*a_nPropValue == 20)
			//	{


			//		mPrintDebug("********************break encounter*******************************");
			//		fclose(wrBinFile);
			//		*a_nPropValue = 1;
			//		return *a_nPropValue;
			//		//break;
			//	}

			//	temp1 = (unsigned int)(wrbuffArr[(i-1)*4+32  ] & 0xFF);
			//	temp2 = (unsigned int)((wrbuffArr[(i-1)*4+1+32  ]) & 0xFF);
			//	temp3 = (unsigned int)((wrbuffArr[(i-1)*4+2+32 ]) & 0xFF);
			//	temp4 = (unsigned int)((wrbuffArr[(i-1)*4+3+32 ]) & 0xFF);
			//	write_byte = (temp1 | (temp2 << 8) | (temp3 << 16) | (temp4 << 24));
			//	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,SPPUFPGARegsDefs(LFT_CENT_EMMC_REG_ADDR + (i*4)*0x10000),write_byte);
			//}
			//sprintf_s(strDebug, DEBUG_STR_LEN,"Write file size : %d byte",dwFileSize);
			//mPrintSelfTestLog(strDebug);
			//toc();

			//FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_DATA_SND_EN,1);
			//FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_DATA_SND_EN,0);
			//
			mPrintDebug("\n ============================= data_tx DONE =================================");

			Sleep(2000);


			mPrintDebug("\n ============================= cmd_value =================================");

			for(int j =0; j<dwFileSize/32 ; j++)
			{

				wr_val = j+ 0x00000010;
				FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_ARG,wr_val);

				wr_val = 0xFFFFFFFF & 0x51;
				FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_INDEX,wr_val);

				//	mPrintDebug("\n ============================= send_cmd_en =================================");
				FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_SND_EN,1);
				FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_SND_EN,0);
				//	mPrintDebug("\n ===================== Cmd send pulse generated...==========================");

				wrBinFile = fopen(outfile,"wb");

				for(i = 1; i <= 8;i++)
				{
					if(*a_nPropValue == 20)
					{


						mPrintDebug("********************break encounter*******************************");
						fclose(rdBinFile);
						*a_nPropValue = 1;
						return *a_nPropValue;
						//break;
					}

					FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,(SPPUFPGARegsDefs)(LFT_CENT_EMMC_REG_ADDR_RX + (i*4)*0x10000) ,&read_byte);

					rdbuffArr[(i-1)*4  +j*32] = (char)(read_byte & 0xFF);
					rdbuffArr[(i-1)*4 + 1 +j*32 ] = (char)((read_byte >> 8) & 0xFF);
					rdbuffArr[(i-1)*4 + 2 +j*32  ] = (char)((read_byte >> 16) & 0xFF);
					rdbuffArr[(i-1)*4 + 3 +j*32 ] = (char)((read_byte >> 24) & 0xFF);
					Sleep(1000);
					/*do
					{
					FPGARegAccessRead(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_RX_DONE,&rd_val);
					if(rd_val == 1)
					{
					mPrintDebug("\n ===================== in while read ==========================");	
					}
					}while(rd_val != 1);*/
				}
			}
			//mPrintDebug("\n ============================= cmd_value =================================");

			//wr_val = 0x00000011;
			//FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_ARG,wr_val);

			//wr_val = 0xFFFFFFFF & 0x51;
			//FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_INDEX,wr_val);

			////	mPrintDebug("\n ============================= send_cmd_en =================================");
			//FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_SND_EN,1);
			//FPGARegAccessWrite(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_CMD_SND_EN,0);
			////	mPrintDebug("\n ===================== Cmd send pulse generated...==========================");

			////wrBinFile = fopen(outfile,"w");

			//for(i = 1; i <= 8;i++)
			//{
			//	if(*a_nPropValue == 20)
			//	{


			//		mPrintDebug("********************break encounter*******************************");
			//		fclose(rdBinFile);
			//		*a_nPropValue = 1;
			//		return *a_nPropValue;
			//		//break;
			//	}

			//	FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,(SPPUFPGARegsDefs)(LFT_CENT_EMMC_REG_ADDR_RX + (i*4)*0x10000) ,&read_byte);

			//	rdbuffArr[(i-1)*4+32  ] = (char)(read_byte & 0xFF);
			//	rdbuffArr[(i-1)*4 + 1+32 ] = (char)((read_byte >> 8) & 0xFF);
			//	rdbuffArr[(i-1)*4 + 2+32  ] = (char)((read_byte >> 16) & 0xFF);
			//	rdbuffArr[(i-1)*4 + 3+32  ] = (char)((read_byte >> 24) & 0xFF);
			//	Sleep(1000);
			//	/*do
			//	{
			//	FPGARegAccessRead(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_EMMC_RX_DONE,&rd_val);
			//	if(rd_val == 1)
			//	{
			//	mPrintDebug("\n ===================== in while read ==========================");	
			//	}
			//	}while(rd_val != 1);*/
			//}
			//Sleep(5000);
			//
			fwrite(rdbuffArr,dwFileSize,1,wrBinFile);

			fclose(wrBinFile);
			fclose(rdBinFile);

			int ret = 0;
			ret = memcmp(wrbuffArr,rdbuffArr,dwFileSize);
			sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn ret::(%d)", ret);
			mPrintDebug(strDebug);
			if (ret != 0)
				*a_nPropValue = 1;
			else
				*a_nPropValue = 0;

			mPrintDebug("\n ============================= test_emmc DONE =================================");
			return *a_nPropValue;
		}

		long MiddleAPI::RunTest_i2ceeprom(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue)
		{
			mPrintDebug("+====================================+");
			mPrintDebug("|     RunTest_i2ceeprom   |");
			mPrintDebug("|	               Start			  |");
			mPrintDebug("+====================================+");


			unsigned int i = 0,j=0;
			unsigned int test_result = 0;
			unsigned int wr_val = 0;
			unsigned int rd_val = 0;
			char strDebug[DEBUG_STR_LEN]	=	{'\0'};
			unsigned int numBytesWr;
			unsigned int numBytesRd;
			FILE *rdBinFile, *wrBinFile; //file for write; // file to read
			int wcount, rcount;
			unsigned char rdbuffArr[1024];
			unsigned char wrbuffArr[1024];
			unsigned int write_byte;
			unsigned int read_byte;
			char *infile = "self_test_i2ceeprom_write.bin";
			char *outfile = "self_test_i2ceeprom_read.bin";


			unsigned int bitFileType;
			FPGARegAccessRead(LFT_HOST_CONNECTION_SER  , a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_BitFile_Check, &bitFileType); 
			//RegRead(LFT_HOST_CONNECTION_SER,a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_BitFile_Check,&bitFileType);
			sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTest uart:Bit file %x)",bitFileType );
			mPrintDebug(strDebug);
			if(bitFileType !=10)
			{
				mPrintSelfTestLog("*********************  WRONG BIT FILE *************************************");
				mPrintDebug("*************************** Wrong bit file **************************************");
				*a_nPropValue = 2;
				return *a_nPropValue;

			}

			mPrintDebug("\n ============================= eeprom_page_write_read_test START =================================");

			mPrintDebug("\n ============================= eeprom_write START =================================");
			mPrintDebug("\n ============================= I2c_busy check =================================");


			unsigned int timeout = 10;
			do
			{
				FPGARegAccessRead(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_I2C_BUSY,&rd_val);
				if(rd_val ==0)
				{
					break;
				}
				timeout--;
				//{
				if(*a_nPropValue == 20)
				{


					mPrintDebug("********************break encounter*******************************");

					*a_nPropValue = 1;
					return *a_nPropValue;
					break;
				}
				Sleep(100);
			}while(timeout =! 0);
			if(timeout ==0)
			{
				mPrintDebug("\n =============================Time Out I2C busy check Failed =================================");
				return *a_nPropValue =1;
			}
			timeout = 10;

			mPrintDebug("\n ============================= I2c_cmd_code =================================");
			write_byte = 0x40;
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_CENT_I2C_CMD_CODE,write_byte);

			mPrintDebug("\n ============================= I2C_data_size =================================");
			write_byte = 0x40;
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_CENT_I2C_DATA_SIZE,write_byte);

			//mPrintDebug("\n ============================= I2C_slave_addr =================================");
			//write_byte = 0x55;
			//FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_CENT_I2C_SLAVE_ADDR,write_byte);

			//mPrintDebug("\n ============================= I2C_reg_offset =================================");
			//write_byte = 0x0000;
			//FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_CENT_I2C_REG_OFFSET,write_byte);

			mPrintDebug("\n ============================= I2C_NO_STOP =================================");
			write_byte = 0;
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_CENT_I2C_NO_STOP,write_byte);

			mPrintDebug("\n ============================= I2c_data_rd_ack =================================");
			write_byte = 0;
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_CENT_I2C_DATA_RD_ACK,write_byte);

			mPrintDebug("\n ============================= I2C_SPEED =================================");
			write_byte = 0x2;
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_CENT_I2C_SPEED,write_byte);


			if(!ifstream (infile))
			{
				mPrintDebug("================File is not present===================");
				return 1;
			}	

			/* opening the file */
			if(!(rdBinFile = fopen(infile,"rb")))
			{
				mPrintDebug("============FILE didnt open for read===============");
				return 1;	
			}
			mPrintDebug("============FILE open succesfully for read=========");	
			/****************************************************************Changed for complete file read write **************************************************************************************/
			/*fseek(rdBinFile, 0, SEEK_END);
			int dwFileSize = ftell(rdBinFile);
			fseek(rdBinFile, 0, SEEK_SET);

			sprintf_s(strDebug, DEBUG_STR_LEN,"file size:%d",dwFileSize);
			mPrintDebug(strDebug);

			wcount = fread(wrbuffArr,64,1,rdBinFile);
			sprintf_s(strDebug, DEBUG_STR_LEN,"buffer is:%d",wcount);
			mPrintDebug(strDebug);

			for(i = 0; i < 64;i++)
			{
			write_byte = (unsigned int)(wrbuffArr[i] & 0xFF);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_CENT_I2C_DATA_IN,write_byte);

			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_CENT_I2C_DATA_IN_VALID,1);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_CENT_I2C_DATA_IN_VALID,0);
			}
			*/



			fseek(rdBinFile, 0L, SEEK_END);
			int dwFileSize= ftell(rdBinFile);
			fseek(rdBinFile, 0L, SEEK_SET);
			wcount = fread(wrbuffArr,dwFileSize,1,rdBinFile);
			for (i = 0; i < dwFileSize/64; i++)
			{
				FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_CENT_I2C_REG_OFFSET,i*16);
				write_byte = 0x55;
				FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_CENT_I2C_SLAVE_ADDR,write_byte);


				for(j=0;j<64;j++)
				{
					write_byte = (unsigned int)(wrbuffArr[j + i*64] & 0xFF);
					FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_CENT_I2C_DATA_IN,write_byte);

					FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_CENT_I2C_DATA_IN_VALID,1);
					FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_CENT_I2C_DATA_IN_VALID,0);
					//{
					if(*a_nPropValue == 20)
					{


						mPrintDebug("********************break encounter*******************************");
						fclose(rdBinFile);
						*a_nPropValue = 1;
						return *a_nPropValue;
						//break;
					}
				}
				FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_CENT_I2C_CMD_EXECUTE,1);
				FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_CENT_I2C_CMD_EXECUTE,0);
			}
			//if(dwFileSize % 256 !=0)
			//{
			//	wcount = fread(wrbuffArr,(dwFileSize%256),1,rdBinFile);
			//	for(j=0;j<(dwFileSize%256);j++)
			//	{
			//		write_byte = (unsigned int)(wrbuffArr[j] & 0xFF);
			//		int k = FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_CENT_I2C_DATA_IN,write_byte);
			//		if(k !=0)
			//		{
			//			mPrintDebug("\n ============================= Connection intrupted =================================");
			//			return *a_nPropValue = 1;
			//			break;
			//		}

			//		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_CENT_I2C_DATA_IN_VALID,1);
			//		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_CENT_I2C_DATA_IN_VALID,0);

			//			//{
			//			if(*a_nPropValue == 20)
			//			{


			//				mPrintDebug("********************break encounter*******************************");
			//				fclose(rdBinFile);
			//				*a_nPropValue = 1;
			//				return *a_nPropValue;
			//				//break;
			//			}
			//	}
			//}
			fclose(rdBinFile);
			/*	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_CENT_I2C_CMD_EXECUTE,1);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_CENT_I2C_CMD_EXECUTE,0);*/

			mPrintDebug("\n ============================= eeprom_write DONE =================================");

			mPrintDebug("\n ============================= eeprom_read START =================================");		



			mPrintDebug("\n ============================= I2c_busy check =================================");

			/*********************************************Changed with timeout **************************************************/
			/*	do
			{
			FPGARegAccessRead(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_I2C_BUSY,&rd_val);
			}while(rd_val != 0);*/



			timeout =100;
			do
			{
				FPGARegAccessRead(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_I2C_BUSY,&rd_val);
				if(rd_val ==0)
				{
					break;
				}
				timeout--;
				//{
				if(*a_nPropValue == 20)
				{


					mPrintDebug("********************break encounter*******************************");
					fclose(rdBinFile);
					*a_nPropValue = 1;
					return *a_nPropValue;
					//break;
				}
				Sleep(100);
			}while(timeout != 0);

			if(timeout == 0)
			{
				mPrintDebug("\n =============================Time Out I2C busy check Failed =================================");
				return *a_nPropValue =1;
			}




			mPrintDebug("\n ============================= I2c_cmd_code =================================");
			write_byte = 0x42;
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_CENT_I2C_CMD_CODE,write_byte);

			mPrintDebug("\n ============================= I2C_data_size =================================");
			write_byte = 0x40;
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_CENT_I2C_DATA_SIZE,write_byte);

			/*mPrintDebug("\n ============================= I2C_slave_addr =================================");
			write_byte = 0x55;
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_CENT_I2C_SLAVE_ADDR,write_byte);*/

			/*mPrintDebug("\n ============================= I2C_reg_offset =================================");
			write_byte = 0x0000;
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_CENT_I2C_REG_OFFSET,write_byte);*/

			mPrintDebug("\n ============================= I2C_NO_STOP =================================");
			write_byte = 0;
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_CENT_I2C_NO_STOP,write_byte);

			mPrintDebug("\n ============================= I2c_data_rd_ack =================================");
			write_byte = 0;
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_CENT_I2C_DATA_RD_ACK,write_byte);

			mPrintDebug("\n ============================= I2C_SPEED =================================");
			write_byte = 0x2;
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_CENT_I2C_SPEED,write_byte);

			/*FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_CENT_I2C_CMD_EXECUTE,1);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_CENT_I2C_CMD_EXECUTE,0);*/

			wrBinFile = fopen(outfile,"wb");

			for (i = 0; i < dwFileSize/64; i++)
			{
				FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_CENT_I2C_REG_OFFSET,i*16);
				write_byte = 0x55;
				FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_CENT_I2C_SLAVE_ADDR,write_byte);

				FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_CENT_I2C_CMD_EXECUTE,1);
				FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_CENT_I2C_CMD_EXECUTE,0);

				for(j=0;j<64;j++)
				{
					do
					{
						FPGARegAccessRead(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_I2C_DATA_OUT_VALID,&rd_val);
						//{
						if(*a_nPropValue == 20)
						{


							mPrintDebug("********************break encounter*******************************");
							fclose(wrBinFile);
							*a_nPropValue = 1;
							return *a_nPropValue;
							//break;
						}
					}while(rd_val == 0);

					int k = FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_CENT_I2C_DATA_OUT,&read_byte);
					if(k !=0)
					{
						mPrintDebug("\n ============================= Connection intrupted =================================");
						return *a_nPropValue = 1;
						break;
					}
					rdbuffArr[j + i*64] = (char)(read_byte & 0xFF);

					FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_CENT_I2C_DATA_RD_ACK,1);
					FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_CENT_I2C_DATA_RD_ACK,0);
				}



			}
			wrBinFile = fopen(outfile,"a");
			fwrite(rdbuffArr,dwFileSize,1,wrBinFile);
			fclose(wrBinFile);
			//if(dwFileSize % 256 !=0)
			//{
			//	for(j=0;j<dwFileSize%256;j++)
			//	{
			//		do
			//		{
			//				//{
			//			if(*a_nPropValue == 20)
			//			{


			//				mPrintDebug("********************break encounter*******************************");
			//				fclose(wrBinFile);
			//				*a_nPropValue = 1;
			//				return *a_nPropValue;
			//				//break;
			//			}
			//			FPGARegAccessRead(a_enConnectionType, a_nModuleID,LFT_SPPU_DEV_FPGA,LFT_CENT_I2C_DATA_OUT_VALID,&rd_val);
			//		}while(rd_val == 0);

			//		int k = FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_CENT_I2C_DATA_OUT,&read_byte);

			//		rdbuffArr[dwFileSize % 256] = (char)(read_byte & 0xFF);
			//		if(k !=0)
			//		{
			//			mPrintDebug("\n ============================= Connection intrupted =================================");
			//			return *a_nPropValue = 1;
			//			break;
			//		}
			//		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_CENT_I2C_DATA_RD_ACK,1);
			//		FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA,LFT_CENT_I2C_DATA_RD_ACK,0);
			//	}
			//	wrBinFile == fopen(outfile,"a");
			//	fwrite(rdbuffArr,dwFileSize%256,1,wrBinFile);
			//	fclose(wrBinFile);
			//}

			//fwrite(rdbuffArr,dwFileSize % 256,1,wrBinFile);

			mPrintDebug("\n ============================= eeprom_read DONE =================================");

			fclose(rdBinFile);

			int ret = 0;
			ret = memcmp(wrbuffArr,rdbuffArr,dwFileSize);
			sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn ret::(%d)", ret);
			mPrintDebug(strDebug);
			if (ret != 0)
				*a_nPropValue = 1;
			else
				*a_nPropValue = 0;

			mPrintDebug("\n ============================= eeprom_page_write_read_test DONE =================================");

			return *a_nPropValue;
		}

		long MiddleAPI::DDRWriteConfig(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType, unsigned int a_nStartAddress, unsigned int a_nSize, unsigned int *a_nSizeWritten, char *a_strFileName)
		{
			unsigned int size = 0x1000;
			unsigned int writeStartAddr = 0;			// TBD
			unsigned int writeEndAddr  =  size;			// TBD
			unsigned int dataType      = 1;
			int ret = 0;
			volatile unsigned int rw_status;
			char strDebug[DEBUG_STR_LEN]	=	{'\0'};
			sprintf_s(strDebug, DEBUG_STR_LEN,"\nIn DDRWriteConfig(%d, %d, %d, %08x, %d, %x, %s)", a_enConnectionType, a_nModuleID, a_enDeviceType, a_nStartAddress, a_nSize, a_nSizeWritten, a_strFileName);
			mPrintDebug(strDebug);
			//if(a_enDeviceType == SPPUDeviceType::LFT_SPPU_DEV_DDR)	// TBD
			{
				mPrintDebug("\n ============================= checker_enable_disable 0 =================================");
				FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_checker,0);
				/*mPrintDebug("\n ============================= checker_enable_disable 1 =================================");
				FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_checker,1);
				mPrintDebug("\n ============================= wait_ddr_init_complete =================================");*/
				mPrintDebug("\n ============================= wait_ddr_init_complete =================================");
				do
				{
					FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_wait_init,&(unsigned int)rw_status);
				}while(rw_status == 0);
				mPrintDebug("\n ============================= DDR3 Initialization Completed =================================");

				mPrintDebug("\n ============================= LFT_AIPB_SIC_DDR3_writeStartAddr =================================");
				FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_writeStartAddr,writeStartAddr);
				mPrintDebug("\n ============================= LFT_AIPB_SIC_DDR3_writeEndAddr =================================");
				FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_writeEndAddr,writeEndAddr);
				/*mPrintDebug("\n ============================= LFT_AIPB_SIC_DDR3_writeSize =================================");
				FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_writeSize,size);
				mPrintDebug("\n ============================= LFT_AIPB_SIC_DDR3_dataType =================================");
				FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_dataType,dataType);*/
				mPrintDebug("\n ============================= DDR3 configuration completes for Writing data =================================");

				mPrintDebug("\n ============================= Give Start Pulse for writing data =================================");
				FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_UART_SEND_WritePulse,1);
				FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_UART_SEND_WritePulse,0);

				/*unsigned int numBytesWr;	
				mPrintDebug("\n ============================= FileWrite START =================================");
				ret	=	MemoryWriteFileInternal(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FIXED_ADDRESS_FOR_IQ_PROGRAMMING, a_nSize, a_nSizeWritten, a_strFileName);	// TBD

				//poll in scase of DDR Access.
				int timeout = 10;
				unsigned int val	=	5;
				while(timeout)	// TBD
				{
				FPGARegAccessRead(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_COMPLETE, &val);
				if(val	==	1)
				break;
				Sleep(100);
				timeout--;
				}
				mPrintDebug("\n ============================= Waiting for Write Done =================================");
				do
				{
				FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_WriteDone,&(unsigned int)rw_status);
				}while(rw_status == 0);
				mPrintDebug("\n ============================= Writing data into DDR3 Completed =================================");*/
			}
			/*else if(a_enDeviceType == SPPUDeviceType::LFT_SPPU_DEV_FX3_SDCARD)
			{
			MemoryWriteFileInternal(a_enConnectionType, a_nModuleID, a_enDeviceType, a_nStartAddress, a_nSize, a_nSizeWritten, a_strFileName);
			}*/
			return ret;
		}

		long MiddleAPI::DDRWriteFinalize(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType, unsigned int a_nStartAddress, unsigned int a_nSize, unsigned int *a_nSizeWritten, char *a_strFileName)
		{
			volatile unsigned int rw_status;
			mPrintDebug("\n ============================= Waiting for Write Done =================================");
			do
			{
				FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_WriteDone,&(unsigned int)rw_status);
			}while(rw_status == 0);
			mPrintDebug("\n ============================= Writing data into DDR3 Completed =================================");
			return 0;
		}

		long MiddleAPI::DDRReadConfig(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType, unsigned int a_nStartAddress, unsigned int a_nSize,unsigned int *a_nSizeRead, char *a_strFileName)
		{
			int ret = 0;
			unsigned int size = 0x1000;
			unsigned int readStartAddr  = 0;
			unsigned int readEndAddr   =  size;
			unsigned int dataType      = 1;
			char strDebug[DEBUG_STR_LEN]	=	{'\0'};
			sprintf_s(strDebug, DEBUG_STR_LEN,"\nIn DDRReadConfig(%d, %d, %d, %08x, %d, %x, %s)", a_enConnectionType, a_nModuleID, a_enDeviceType, a_nStartAddress, a_nSize, a_nSizeRead, a_strFileName);
			mPrintDebug(strDebug);

			mPrintDebug("\n ============================= DDR3 Reading Configuration Starts =================================");
			mPrintDebug("\n ============================= LFT_AIPB_SIC_DDR3_readStartAddr =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_readStartAddr,readStartAddr);
			mPrintDebug("\n ============================= LFT_AIPB_SIC_DDR3_readEndAddr =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_readEndAddr,readEndAddr);
			/*mPrintDebug("\n ============================= LFT_AIPB_SIC_DDR3_readSize =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_readSize,size);
			mPrintDebug("\n ============================= LFT_AIPB_SIC_DDR3_dataType =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_dataType,dataType);*/
			mPrintDebug("\n ============================= DDR3 configuration completes for Reading data =================================");

			mPrintDebug("\n ============================= Give Start Pulse for Reading data pulse =================================");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_UART_SEND_ReadPulse,1);
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_UART_SEND_ReadPulse,0);

			/*mPrintDebug("\n ============================= FileRead START =================================");
			switch(a_enConnectionType)
			{
			case LFT_HOST_CONNECTION_USB:
			pnSizeRead	=	new unsigned long(0);
			ret	=	objUsbApi.RdFileFromSdCard0((UsbApis::DEVICE_TYPES)a_enDeviceType, a_strFileName, a_nStartAddress, a_nSize, pnSizeRead);
			sprintf_s(strDebug, DEBUG_STR_LEN,"returned pnSizeRead:%d", *pnSizeRead);
			mPrintDebug(strDebug);
			*a_nSizeRead	=	(unsigned int) *pnSizeRead;
			delete pnSizeRead;
			return ret;

			case LFT_HOST_CONNECTION_ETH:
			pnSizeRead	=	new unsigned long(0);
			ret	=	objEthernetAPI.FileRead((MiddleEthernetAPI::EthernetAPI::SPPUDeviceTypeEtherent) a_enDeviceType, a_nStartAddress, a_nSize, a_strFileName, (unsigned int *) pnSizeRead);
			sprintf_s(strDebug, DEBUG_STR_LEN,"returned pnSizeRead:%d", *pnSizeRead);
			mPrintDebug(strDebug);
			*a_nSizeRead	=	(unsigned int) *pnSizeRead;
			delete pnSizeRead;
			return ret;

			case LFT_HOST_CONNECTION_PCIE:

			pnSizeRead	=	new unsigned long(0);
			ret	=	FileRecv((DeviceTypesPci) a_enDeviceType, a_strFileName, a_nStartAddress, a_nSize, pnSizeRead);
			sprintf_s(strDebug, DEBUG_STR_LEN,"returned pnSizeRead:%d", *pnSizeRead);
			mPrintDebug(strDebug);
			*a_nSizeRead	=	(unsigned int) *pnSizeRead;
			delete pnSizeRead;
			return ret;
			}
			return -100;*/
			return ret;
		}

		long MiddleAPI::DDRReadFinalize(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType, unsigned int a_nStartAddress, unsigned int a_nSize, unsigned int *a_nSizeWritten, char *a_strFileName)
		{
			volatile unsigned int rw_status;
			mPrintDebug("\n ============================= Waiting for Read Done =================================");
			int wait_Count =0;
			do
			{
				FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_DDR3_ReadDone,&(unsigned int)rw_status);
				wait_Count++;
			}while(rw_status == 0);
			return 0;
		}

		//===================================================== VAB USB =======================================================
#define PREAMBLE_CDP 0x44556677
#define PREAMBLE_VT 0xDDCCBBAA
#define PREAMBLE_IT 0xEEDDCCBB
#define PREAMBLE_IM_START 0xFFEEDDCC

		long MiddleAPI::VAB_File_List(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,vector<MiddleAPIWrapper::MiddleAPI::VAB_File_Info> Info,unsigned int *a_nPropValue)
		{
			char *current_data_ptr;
			char *video_sec_data;
			char *image_sec_data;
			char *data_sec_data;
			FILE *ptr_video_sec_data;
			FILE *ptr_image_sec_data;
			FILE *ptr_data_sec_data;
			DWORD rdval;
			DWORD wrval;
			DWORD *tmp;
			unsigned long long int i;
			char strDebug[DEBUG_STR_LEN]	=	{'\0'};
			unsigned long long int current_video_sec_ptr = 0;
			unsigned long long int current_image_sec_ptr = 0;
			unsigned long long int current_data_sec_ptr = 0;

			mPrintDebug("\n ============================= VAB_File_List creation START=================================");

			mPrintDebug("\n ============================= read flash data Pulse send=================================");
			FT_RegRead(0x00,&rdval);		
			wrval = rdval | (1 << 4);
			FT_RegWrite(0x00,&wrval);

			FT_RegRead(0x00,&rdval);		
			wrval = rdval & 0xFFFFFFEF;
			FT_RegWrite(0x00,&wrval);

			mPrintDebug("\n ============================= read address send=================================");
			FT_RegWrite(0x08,0x00);	

			mPrintDebug("\n ============================= read current pointer=================================");
			FT_RegReadBulk(0x4200,512,current_data_ptr);

			if(((current_data_ptr[3]<<24)|(current_data_ptr[2]<<16)|(current_data_ptr[1]<<8)|current_data_ptr[0]) == PREAMBLE_CDP)
			{
				current_video_sec_ptr = ((current_data_ptr[11]<<56)|(current_data_ptr[10]<<48)|(current_data_ptr[9]<<40)|(current_data_ptr[8] << 32)|(current_data_ptr[7]<<24)|(current_data_ptr[6]<<16)|(current_data_ptr[5]<<8)|current_data_ptr[4]);
				current_image_sec_ptr = ((current_data_ptr[19]<<56)|(current_data_ptr[18]<<48)|(current_data_ptr[17]<<40)|(current_data_ptr[16] << 32)|(current_data_ptr[15]<<24)|(current_data_ptr[14]<<16)|(current_data_ptr[13]<<8)|current_data_ptr[12]);
				current_data_sec_ptr = ((current_data_ptr[27]<<56)|(current_data_ptr[26]<<48)|(current_data_ptr[25]<<40)|(current_data_ptr[24] << 32)|(current_data_ptr[23]<<24)|(current_data_ptr[22]<<16)|(current_data_ptr[21]<<8)|current_data_ptr[20]);
				sprintf_s(strDebug, DEBUG_STR_LEN,"current_video_sec_ptr : %d     current_image_sec_ptr :  %d    current_data_sec_ptr : %d",current_video_sec_ptr,current_image_sec_ptr,current_data_sec_ptr);
				mPrintDebug(strDebug);
				mPrintDebug("\n ============================= Valid data Received =================================");
			}
			else
			{
				mPrintDebug("\n ============================= Invalid data Received =================================");
				return 1;
			}

			//======================================================= video tag reading ===============================================
			ptr_video_sec_data = fopen("Video_tag_data.txt","wb");
			ptr_video_sec_data = fopen("Video_tag_data.txt","a");
			for(i=0;i<current_video_sec_ptr;i++)
			{
				sprintf_s(strDebug, DEBUG_STR_LEN,"Reading Video Tag : %d",i);
				mPrintDebug(strDebug);
				*tmp = (i+1)*512;
				FT_RegWrite(0x08,tmp);	
				FT_RegReadBulk(0x4200,512,video_sec_data);
				fwrite(video_sec_data,512,1,ptr_video_sec_data);
			}
			fclose(ptr_video_sec_data);

			//======================================================= Image tag reading ===============================================
			ptr_image_sec_data = fopen("Image_tag_data.txt","wb");
			ptr_image_sec_data = fopen("Image_tag_data.txt","a");
			for(i=0;i<current_image_sec_ptr;i++)
			{
				sprintf_s(strDebug, DEBUG_STR_LEN,"Reading Image Tag : %d",i*32);
				mPrintDebug(strDebug);
				*tmp = (i+1)*512;
				FT_RegWrite(0x08,tmp);	
				FT_RegReadBulk(0x4200,512,image_sec_data);
				fwrite(image_sec_data,512,1,ptr_image_sec_data);
			}
			fclose(ptr_image_sec_data);

			return *a_nPropValue;
		}

		long MiddleAPI::VAB_File_Delete(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue)
		{
			mPrintDebug("\n ============================= VAB_File_Delete =================================");

			return *a_nPropValue;
		}

		long MiddleAPI::VAB_File_Save(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *file_Index,unsigned int *a_nPropValue)
		{
			mPrintDebug("\n ============================= VAB_File_Save =================================");

			return *a_nPropValue;
		}

		long MiddleAPI::VAB_File_Run(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *file_Index,unsigned int *a_nPropValue)
		{
			mPrintDebug("\n ============================= VAB_File_Run =================================");

			return *a_nPropValue;
		}


		//======================================================================================================================= SKR FTDI

		FT_HANDLE VAB_ftHandle;

#define CMD_WRITE       0x01
#define CMD_READ        0x02

#define SEND_MAGIC_BYTE     0xCC77
#define RECV_MAGIC_BYTE     0xAA88

#define BUFFER_SIZE 600


		long MiddleAPI::FT_Detect(FT_DEVICE_LIST_INFO_NODE *devInfo,DWORD *Devs,unsigned int *a_nPropValue)
		{
			FT_STATUS ftStatus;
			DWORD numDevs = 0;
			char strDebug[DEBUG_STR_LEN]	=	{'\0'};
			mPrintDebug("\r\n In FTDI_USB_Detect ");
			ftStatus = FT_CreateDeviceInfoList(&numDevs);
			mPrintDebug("\r\n FT_CreateDeviceInfoList ");
			if (numDevs > 0)
			{
				devInfo = (FT_DEVICE_LIST_INFO_NODE*)malloc(sizeof(FT_DEVICE_LIST_INFO_NODE)*numDevs);
				ftStatus = FT_GetDeviceInfoList(devInfo,&numDevs);
				mPrintDebug("\r\n FT_GetDeviceInfoList ");
				if (ftStatus != FT_OK)
				{
					mPrintDebug("\r\n ftStatus != FT_OK ");
					*a_nPropValue = 1;
					return *a_nPropValue;
				}
			}
			else
			{
				sprintf_s(strDebug, DEBUG_STR_LEN,"\r\n numDevs : ",numDevs);
				mPrintDebug(strDebug);
				*a_nPropValue = 1;
				return *a_nPropValue;
			}
			sprintf_s(strDebug, DEBUG_STR_LEN,"\r\n numDevs : ",numDevs);
			mPrintDebug(strDebug);
			*Devs = numDevs;
			*a_nPropValue = 0;
			return *a_nPropValue;
		}

		long MiddleAPI::FT_Init(int Device_No,unsigned int *a_nPropValue)
		{
			FT_STATUS ftStatus; 
			DWORD dev_num = 0;
			int res=0;

			mPrintDebug("\n ============================= Open device =================================");
			dev_num = 0;
			ftStatus = FT_Open(Device_No,&VAB_ftHandle);
			if(ftStatus == FT_OK) 
			{ 
				mPrintDebug("\n Device Connected "); 
				*a_nPropValue = 0;
				return *a_nPropValue;
			} 
			else
			{
				mPrintDebug("\n Device Not Connected "); 
				*a_nPropValue = 1;
				return *a_nPropValue;
			}
			mPrintDebug("\n ========================= sync mode setting ===============================");
			FT_SetBitMode(VAB_ftHandle, 0xFF, 0x00); //Reset Mode
			Sleep(100);
			FT_SetLatencyTimer(VAB_ftHandle, 2);
			FT_SetBitMode(VAB_ftHandle, 0xFF, 0x40); //Sync FIFO mode
			FT_SetUSBParameters(VAB_ftHandle,0x10000,0x10000);
			FT_SetTimeouts(VAB_ftHandle,100,0);
			FT_SetTimeouts(&VAB_ftHandle,10000,0);
			mPrintDebug("\n ========================= VAB_USB_open Done ===============================");
			*a_nPropValue = 0;
			return *a_nPropValue;
		}

		long MiddleAPI::FT_DeInit(unsigned int *a_nPropValue)
		{
			FT_Close(VAB_ftHandle);
			mPrintDebug("\n ========================= VAB_USB_close Done ===============================");
			*a_nPropValue = 0;
			return *a_nPropValue;
		}

		long MiddleAPI::FT_RegRead(DWORD address,DWORD * data)
		{
			BYTE RxBuffer[16];
			DWORD pktLen	= 0;
			DWORD nBytesWritten	=	0;
			DWORD dwIncommingReadSize	=	0;
			FT_STATUS ftStatus;
			char strDebug[DEBUG_STR_LEN]	=	{'\0'};

			pktLen = 16;

			RxBuffer[0] = ((SEND_MAGIC_BYTE >> 8) & 0xFF);
			RxBuffer[1] = (SEND_MAGIC_BYTE & 0xFF);

			RxBuffer[2] = ((pktLen >> 8) & 0xFF);
			RxBuffer[3] = (pktLen & 0xFF);

			RxBuffer[4] = 0x00;
			RxBuffer[5] = CMD_READ;
			RxBuffer[6] = 0x00;
			RxBuffer[7] = 0x00;

			RxBuffer[8]  = ((address >> 24) & 0xFF);
			RxBuffer[9]  = ((address >> 16) & 0xFF);
			RxBuffer[10] = ((address >> 8) & 0xFF);
			RxBuffer[11] = (address & 0xFF);

			ftStatus=FT_Write(VAB_ftHandle,RxBuffer,pktLen,&nBytesWritten);
			if(nBytesWritten==0)
			{
				mPrintDebug("\r\n RegRead :: Unable to send Read request to device  ");
				return 1;
			}
			mPrintDebug("\r\n RegRead :: Read request send  ");
			ftStatus=FT_Read(VAB_ftHandle,&RxBuffer,pktLen,&dwIncommingReadSize);
			if(dwIncommingReadSize == 0)
			{
				mPrintDebug("\r\n RegRead :: Unable to read from device ");
				return 1;
			}

			*data = ((RxBuffer[12] << 24)|(RxBuffer[13] << 16)|(RxBuffer[14] << 8)|(RxBuffer[15] << 0));

			sprintf_s(strDebug, DEBUG_STR_LEN,"Address : %8X   Data Rx :  %8X  ",address,data);
			mPrintDebug(strDebug);

			return 0;
		}

		long MiddleAPI::FT_RegReadBulk(DWORD address,unsigned int len,char *data)
		{
			BYTE RxBuffer[BUFFER_SIZE];
			DWORD pktLen	= 0;
			DWORD nBytesWritten	=	0;
			DWORD dwIncommingReadSize	=	0;
			FT_STATUS ftStatus;
			UINT i=0;

			pktLen = 268;

			RxBuffer[0] = ((SEND_MAGIC_BYTE >> 8) & 0xFF);
			RxBuffer[1] = (SEND_MAGIC_BYTE & 0xFF);

			RxBuffer[2] = ((pktLen >> 8) & 0xFF);
			RxBuffer[3] = (pktLen & 0xFF);

			RxBuffer[4] = 0x00;
			RxBuffer[5] = CMD_READ;
			RxBuffer[6] = 0x00;
			RxBuffer[7] = 0x00;

			RxBuffer[8]  = ((address >> 24) & 0xFF);
			RxBuffer[9]  = ((address >> 16) & 0xFF);
			RxBuffer[10] = ((address >> 8) & 0xFF);
			RxBuffer[11] = (address & 0xFF);

			ftStatus=FT_Write(VAB_ftHandle,RxBuffer,pktLen,&nBytesWritten);
			if(nBytesWritten==0)
			{
				mPrintDebug("\r\n RegReadBulk : Unable to send Read request to device");
				return 1;
			}
			mPrintDebug("\r\n RegReadBulk :: Read request send  ");
			ftStatus=FT_Read(VAB_ftHandle,&RxBuffer,pktLen,&dwIncommingReadSize);
			if(dwIncommingReadSize == 0)
			{
				mPrintDebug("\r\n RegReadBulk :: Unable to read from device  ");
				return 1;
			}

			for(i=0;i<256;i++)
			{
				data[i] = RxBuffer[i+12];
			}

			mPrintDebug("\r\n RegReadBulk :: Read Done ");
			return 0;
		}

		long MiddleAPI::FT_RegWrite(DWORD address, DWORD *data)
		{
			BYTE TxBuffer[16];
			DWORD pktLen	= 0;
			DWORD nBytesWritten	=	0;
			BYTE byArrPktResp[16];
			DWORD dwIncommingReadSize	=	0;
			FT_STATUS ftStatus;

			pktLen = 16;

			TxBuffer[0] = ((SEND_MAGIC_BYTE >> 8) & 0xFF);
			TxBuffer[1] = (SEND_MAGIC_BYTE & 0xFF);

			TxBuffer[2] = ((pktLen >> 8) & 0xFF);
			TxBuffer[3] = (pktLen & 0xFF);

			TxBuffer[4] = 0x00;
			TxBuffer[5] = CMD_WRITE;
			TxBuffer[6] = 0x00;
			TxBuffer[7] = 0x00;

			TxBuffer[8]  = ((address >> 24) & 0xFF);
			TxBuffer[9]  = ((address >> 16) & 0xFF);
			TxBuffer[10] = ((address >> 8) & 0xFF);
			TxBuffer[11] = (address & 0xFF);

			TxBuffer[12]  = ((*data >> 24) & 0xFF);
			TxBuffer[13]  = ((*data >> 16) & 0xFF);
			TxBuffer[14]  = ((*data >> 8) & 0xFF);
			TxBuffer[15]  = (*data & 0xFF);

			ftStatus=FT_Write(VAB_ftHandle,TxBuffer,pktLen,&nBytesWritten);
			if(nBytesWritten==0)
			{
				mPrintDebug("\r\n RegWrite : Unable to write data to device ");
				return 1;
			}
			mPrintDebug("\r\n RegWrite : Write Done ");
			ftStatus=FT_Read(VAB_ftHandle,&byArrPktResp,pktLen,&dwIncommingReadSize);
			if(dwIncommingReadSize == 0)
			{
				mPrintDebug("\r\n RegWrite : Unable to read resp device ");
				return 1;
			}
			mPrintDebug("\r\n RegWrite : Write response received ");

			return 0;
		}

		long MiddleAPI::FT_RegWriteBulk(DWORD address,unsigned int len,char *data)
		{
			BYTE TxBuffer[BUFFER_SIZE];
			DWORD pktLen	= 0;
			DWORD nBytesWritten	=	0;
			DWORD i=0;
			FT_STATUS ftStatus;

			pktLen = (12 + len);

			TxBuffer[0] = ((SEND_MAGIC_BYTE >> 8) & 0xFF);
			TxBuffer[1] = (SEND_MAGIC_BYTE & 0xFF);

			TxBuffer[2] = ((pktLen >> 8) & 0xFF);
			TxBuffer[3] = (pktLen & 0xFF);

			TxBuffer[4] = 0x00;
			TxBuffer[5] = CMD_WRITE;
			TxBuffer[6] = 0x00;
			TxBuffer[7] = 0x00;

			TxBuffer[8]  = ((address >> 24) & 0xFF);
			TxBuffer[9]  = ((address >> 16) & 0xFF);
			TxBuffer[10] = ((address >> 8) & 0xFF);
			TxBuffer[11] = (address & 0xFF);

			for(i=0;i<len;i++)
			{
				TxBuffer[12+i]  = *data & 0xFF;
				data++;
			}

			ftStatus=FT_Write(VAB_ftHandle,TxBuffer,pktLen,&nBytesWritten);
			if(nBytesWritten==0)
			{
				mPrintDebug("\r\n RegWriteBulk : Unable to write data to device ");
				return 1;
			}
			mPrintDebug("\r\n RegWriteBulk : Write Done ");
			return 0;
		}






		long MiddleAPI::RegWriteBulk(FT_HANDLE ftHandle, unsigned int address,unsigned int len,unsigned char *data,unsigned int *numBytesWr)
		{
			unsigned char TxBuffer[12 + 256];
			int pktLen	= 12 + 256;
			mPrintDebug("\n Register Bulk Write  :: DONE ");
			DWORD nBytesWritten	=	0;
			DWORD i=0;
			DWORD dwIncommingReadSize	=	0;

			FT_STATUS ftStatus;

			TxBuffer[0] = 0xcc;	// ------ magic byte
			TxBuffer[1] = 0x77;

			TxBuffer[2] = 0x01; // ------ len byte
			TxBuffer[3] = 0x0C;

			TxBuffer[4] = 0x00; 
			TxBuffer[5] = 0x01; // ------ write
			TxBuffer[6] = 0x00; 
			TxBuffer[7] = 0x00;

			TxBuffer[8]  = ((address >> 24) & 0xFF); // ------ address
			TxBuffer[9]  = ((address >> 16) & 0xFF); 
			TxBuffer[10] = ((address >> 8) & 0xFF); 
			TxBuffer[11] = (address & 0xFF);

			for(i=0;i<256;i++)
			{
				TxBuffer[12+i]  = data[i] & 0xFF;
			}

			ftStatus=FT_Write(ftHandle,TxBuffer,pktLen,&nBytesWritten);
			if(nBytesWritten==0)
			{
				mPrintDebug("\n Unable to write data to device");
				FT_Close(ftHandle);
				return 1;
			}
			*numBytesWr = (nBytesWritten-12);
			mPrintDebug("\n Register Bulk Write  :: DONE ");
			return 0;
		}

		long MiddleAPI::RegReadBulk(FT_HANDLE ftHandle, unsigned int address,unsigned int len,unsigned char *data,unsigned int *numBytesRd)
		{
			unsigned char RxBuffer[12 + 256];
			int pktLen	=	16;
			mPrintDebug("\n Register Bulk Read  :: START ");
			DWORD nBytesWritten	=	0;
			DWORD i=0;
			DWORD dwIncommingReadSize	=	0;

			FT_STATUS ftStatus;

			RxBuffer[0] = 0xCC;	// ------ magic byte
			RxBuffer[1] = 0x77;

			RxBuffer[2] = 0x01; // ------ len byte
			RxBuffer[3] = 0x0C;

			RxBuffer[4] = 0x00; 
			RxBuffer[5] = 0x02; // ------ read
			RxBuffer[6] = 0x00; 
			RxBuffer[7] = 0x00;

			RxBuffer[8]  = ((address >> 24) & 0xFF); // ------ address
			RxBuffer[9]  = ((address >> 16) & 0xFF); 
			RxBuffer[10] = ((address >> 8) & 0xFF); 
			RxBuffer[11] = (address & 0xFF);

			ftStatus=FT_Write(ftHandle,RxBuffer,pktLen,&nBytesWritten);
			if(nBytesWritten==0)
			{
				mPrintDebug("\n Unable to write command to device");
				FT_Close(ftHandle);
				return 1;
			}

			pktLen	=	12 + len;

			ftStatus=FT_Read(ftHandle,RxBuffer,pktLen,&dwIncommingReadSize);
			if(dwIncommingReadSize == 0)
			{
				mPrintDebug("\n Unable to read from device");
				FT_Close(ftHandle);
				return 1;
			}
			else
			{
				for(i=0;i<256;i++)
				{
					data[i] = RxBuffer[i+12] & 0xFF;
				}
			}

			*numBytesRd = (dwIncommingReadSize-12);
			mPrintDebug("\n Register Bulk Read  :: DONE ");
			return 0;
		}

		long MiddleAPI::FT_FileWrite(FT_HANDLE ftHandle,unsigned int startAddress, unsigned int size,  char *pchFilePath,  unsigned int *numBytesWrSuccess)
		{
			FILE * pFile;
			errno_t err;
			char strDebug[DEBUG_STR_LEN]	=	{'\0'};	
			unsigned char rDevBuf[256];
			unsigned int numByWrSuccess=0;
			unsigned int numByToWr = size;
			unsigned int numByWriteDone = 0;
			rDevBuf[0] = NULL;

			mPrintDebug("\n\n==========================================================================\n");
			sprintf_s(strDebug, DEBUG_STR_LEN,"\nFT_FileWrite:: startAddress:%d size:%d Filename:%s", startAddress, size, pchFilePath);
			mPrintDebug(strDebug);
			mPrintDebug("\n==========================================================================\n");

			err	=	fopen_s(&pFile, pchFilePath,"rb");
			if( err != 0)
			{
				mPrintDebug("\nUnable to open file\n");
				return -2; 
			}

			while(numByToWr)
			{
				if(numByToWr > 256)
					numByToWr = 256;

				fread(rDevBuf, 1, numByToWr, pFile);

				err = RegWriteBulk(ftHandle, startAddress, 256, rDevBuf,&numByWrSuccess);

				if(err)
				{
					numByWrSuccess = 0;
					break;
				}

				numByWriteDone += numByWrSuccess;
				sprintf_s(strDebug, DEBUG_STR_LEN,"\nFT_FileWrite:: numByWriteDone:: %d ", numByWriteDone);
				mPrintDebug(strDebug);

				if(numByWriteDone >= size)
				{
					break;
				}
				numByToWr = size - numByWriteDone;
			}

			*numBytesWrSuccess = numByWriteDone;

			mPrintDebug("\n==========================================================================\n");
			sprintf_s(strDebug, DEBUG_STR_LEN,"\nFT_FileWrite:: numBytesWrSuccess:: %d ", *numBytesWrSuccess);
			mPrintDebug(strDebug);
			mPrintDebug("\n==========================================================================\n");
			fclose(pFile);
			return 0;
		}

		long MiddleAPI::FT_FileRead(FT_HANDLE ftHandle,unsigned int startAddress, unsigned int size,  char *pchFilePath,  unsigned int *numBytesRdSuccess)
		{
			FILE * pFile;
			errno_t err;
			unsigned char rDevBuf[256];
			unsigned int numByRdSuccess=0;
			unsigned int numByToRd = size;
			unsigned int numByReadDone = 0;
			rDevBuf[0] = NULL;
			char strDebug[DEBUG_STR_LEN]	=	{'\0'};	
			mPrintDebug("\n\n==========================================================================\n");
			sprintf_s(strDebug, DEBUG_STR_LEN,"\nFT_FileRead:: startAddress:%d size:%d Filename:%s", startAddress, size, pchFilePath);
			mPrintDebug(strDebug);
			mPrintDebug("\n==========================================================================\n");

			err	=	fopen_s(&pFile, pchFilePath,"wb");
			if( err != 0)
			{
				mPrintDebug("\nUnable to open file\n");
				return -2; 
			}

			while(numByToRd)
			{
				if(numByToRd > 256)
					numByToRd = 256;

				err = RegReadBulk(ftHandle,startAddress,256,rDevBuf,&numByRdSuccess);
				if(err)
				{
					numByRdSuccess = 0;
					break;
				}

				numByReadDone += numByRdSuccess;

				sprintf_s(strDebug, DEBUG_STR_LEN,"\nFT_FileRead:: numByReadDone : %d ", numByReadDone);
				mPrintDebug(strDebug);
				fwrite(rDevBuf, 1, numByRdSuccess, pFile);

				if(numByReadDone >= size)
				{break;}
				numByToRd = size - numByReadDone;
			}
			*numBytesRdSuccess = numByReadDone;
			mPrintDebug("\n==========================================================================\n");
			sprintf_s(strDebug, DEBUG_STR_LEN,"\nFT_FileRead:: numBytesRdSuccess : %d ", *numBytesRdSuccess);
			mPrintDebug(strDebug);
			mPrintDebug("\n==========================================================================\n");
			fclose(pFile);
			return 0;
		}
		long MiddleAPI::RunTest_usb(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue)
		{
			FILE *wr_ptr;
			FILE *rd_ptr;
			FT_HANDLE ftHandle;
			FT_STATUS ftStatus; 
			unsigned int numBytesWr;
			unsigned int numBytesRd;
			unsigned char file_read[256];
			unsigned char file_write[256];
			DWORD dev_num = 0;
			int res=0;
			char strDebug[DEBUG_STR_LEN]	=	{'\0'};
			mPrintDebug("\n =============================Run Test USB ======================");
			unsigned int bitFileType;
			FPGARegAccessRead(a_enConnectionType  , a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_BitFile_Check, &bitFileType); 
			//RegRead(LFT_HOST_CONNECTION_SER,a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_AIPB_SIC_BitFile_Check,&bitFileType);
			sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RunTest uart:Bit file %x)",bitFileType );
			mPrintDebug(strDebug);
			if(  bitFileType!= 7)
			{
				mPrintSelfTestLog("*********************  WRONG BIT FILE *************************************");
				/**a_nPropValue = 1;
				return *a_nPropValue;*/

			}
			mPrintDebug("\n ============================= Open device =================================");
			dev_num = 0;
			ftStatus = FT_Open(0,&ftHandle);
			if(ftStatus == FT_OK) 
			{ 
				mPrintDebug("\n Device Connected "); 
				*a_nPropValue = 0;
			} 
			else
			{
				mPrintDebug("\n Device Not Connected "); 
				*a_nPropValue = 1;
				goto ext;
			}
			mPrintDebug("\n ========================= sync mode setting ===============================");
			FT_SetBitMode(ftHandle, 0xFF, 0x00); //Reset Mode
			Sleep(100);
			FT_SetLatencyTimer(ftHandle, 2);
			FT_SetBitMode(ftHandle, 0xFF, 0x40); //Sync FIFO mode
			FT_SetUSBParameters(ftHandle,0x10000,0x10000);
			FT_SetTimeouts(ftHandle,100,0);
			FT_SetTimeouts(&ftHandle,10000,0);

			mPrintDebug("\n ========================= SELF Test Process Start===============================");

			wr_ptr = fopen("self_test_usb_write.bin","rb");

			if(wr_ptr == NULL)
			{
				mPrintDebug("Test Data file self_test_usb_write.bin not found");
				*a_nPropValue = 1;
				goto ext;
			}

			fseek(wr_ptr, 0L, SEEK_END);
			unsigned int dwFileSize= ftell(wr_ptr);
			fseek(wr_ptr, 0L, SEEK_SET);

			fclose(wr_ptr);
			//	fread(file_read,1,256,wr_ptr);
			//	res = RegWriteBulk(ftHandle,0x00004200,256,file_read,&numBytesWr);
			//	fclose(wr_ptr);

			//	rd_ptr = fopen("self_test_usb_read.bin","w");
			//	res = RegReadBulk(ftHandle,0x00004200,256,file_write,&numBytesRd);
			//	fwrite(file_write,1,256,rd_ptr);
			//	fclose(rd_ptr);

			FT_FileWrite(ftHandle,0x00004200,dwFileSize,"self_test_usb_write.bin",&numBytesWr);
			if(*a_nPropValue == 20)
			{

				mPrintDebug("********************break encounter*******************************");

				*a_nPropValue = 1;
				return *a_nPropValue;

			}
			FT_FileRead(ftHandle,0x00004200,dwFileSize,"self_test_usb_read.bin",&numBytesRd);
			if(*a_nPropValue == 20)
			{


				mPrintDebug("********************break encounter*******************************");

				*a_nPropValue = 1;
				return *a_nPropValue;

			}
			mPrintDebug("\n ========================= SELF Test Process Complete===============================");
			FT_Close(ftHandle);
			mPrintDebug("\n ============================= Close device =================================");
ext:
			return *a_nPropValue;
		}      







		//=======================================================================================================================


		/*
		__HP__1 : First  minor change. Bug fix. First modification in bangalore.
		__HP__2 : Bug Fix. Added support for 0's append while writing DDR if data is not multiple of 64 bytes.
		__HP__3 : Modifications with checked and told by Dileep. Not tested throughly on hardware. Just once but no conclusion.
		__HP__4 : Modify on 18 Oct 2015, While writing DDR, multiple of 64 byte size must be programmed in FPGA Register.
		__HP__5 : Small Bug Fix to send size in etherned.dll, and in ethernet.cpp __HP__5, used to debug ethernet buffer.
		__HP__6 : 27 Oct 2015, modifing support for data size multiple of 4096 bytes or append 0z to make it than multiple of 64 bytes.
		__HP__7 : 29 Oct 2015, new changed in DDR addressing asked by Dileep.
		__HP__8 : 31 Oct 2015, bug fixed.
		__HP__9 : 5 Nov 2015, adding support to write Multiple of 4096 on SD Card. Changes mailny in "Usb dll"
		__HP__10: 6 Nov 2015, Saving actual data size in Sd Card rethar than successfully written.

		__HP__11: 20 jan 2016: Addes memoryreadfileinternal() API; support for memory access tab page to access DDR 

		__HP__12: 13 May 2016, Changed DDR resolution from 4096 bytes to 8 bytes.

		*/