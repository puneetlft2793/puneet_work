#include "MiddleAPIWrapper.h"

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
		
	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RegWrite(%d, %d, %d, %08x, %08x)", a_enConnectionType, a_nModuleID, a_enDeviceType, address, data);
	mPrintDebug(strDebug);

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
				return RegisterWrite(address,data);
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
	sprintf_s(strDebug,DEBUG_STR_LEN,"\nIn RegRead(%d, %d, %d, %08x, %08x)", a_enConnectionType, a_nModuleID, a_enDeviceType, address, *data);
	mPrintDebug(strDebug);

	return ret;
}

	

	 // no switch case matched


int MiddleAPI::connect(SPPUHostConnectionType a_enConnectionType, int a_nConnectionParam)    //eth : IP addr, (0x0A000050) == 10.0.0.80 , USB( No Par), UART( B0: COM Port#, B1: BaudRate)
{
	int ret	= 0;
	mPrintDebug("\nIn connect(SOCKET_CONN)");	

	char strDebug[DEBUG_STR_LEN]	=	{'\0'};
	sprintf_s(strDebug,DEBUG_STR_LEN,"Info(Param: %08x)",a_nConnectionParam);
	mPrintDebug(strDebug);

	switch(a_enConnectionType)
	{
		case LFT_HOST_CONNECTION_USB:
		ret	=	objUsbApi.OpenDevice(); //USB 
		break;

		case LFT_HOST_CONNECTION_ETH:
    //TBD   call  connect(MiddleEthernetAPI::Sockets a_sockets) 
		break;
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
    default:
        break;
	}
}

#if 1
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
		//FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_WRITE_AXIS_BURST_LENGTH, nAxisBurstLength);
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

long MiddleAPI::MemoryWriteFile(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType, unsigned int a_nStartAddress, unsigned int a_nSize, unsigned int *a_nSizeWritten,char *a_strFileName)
{
	int ret	=	0;

	char strDebug[DEBUG_STR_LEN]	=	{'\0'};

	sprintf_s(strDebug, DEBUG_STR_LEN,"\nIn MemoryWriteFile(%d, %d, %d, %08x, %d, %x, %s)", a_enConnectionType, a_nModuleID, a_enDeviceType, a_nStartAddress, a_nSize, a_nSizeWritten, a_strFileName);
	mPrintDebug(strDebug);


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
	else if(a_enDeviceType == SPPUDeviceType::LFT_SPPU_DEV_FX3_SDCARD)
	{
		MemoryWriteFileInternal(a_enConnectionType, a_nModuleID, a_enDeviceType, a_nStartAddress, a_nSize, a_nSizeWritten, a_strFileName);
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

	switch(a_enConnectionType)
	{
		case LFT_HOST_CONNECTION_USB:
			pnSizeWritten	=	new unsigned long(0);
			ret	=	objUsbApi.WrFileToSdCard0((UsbApis::DEVICE_TYPES)a_enDeviceType, a_strFileName, a_nStartAddress, a_nSize, pnSizeWritten);
			*a_nSizeWritten	=	(unsigned int) *pnSizeWritten;
			delete pnSizeWritten;
			return ret;
	
		case LFT_HOST_CONNECTION_ETH:
			ret	=	objEthernetAPI.FileWrite((MiddleEthernetAPI::EthernetAPI::SPPUDeviceTypeEtherent) a_enDeviceType, a_nStartAddress, a_nSize, a_strFileName);
			return ret;

		case LFT_HOST_CONNECTION_PCIE:
			pnSizeWritten	=	new unsigned long(0);
			ret =   FileSend((DeviceTypesPci) a_enDeviceType, a_strFileName, a_nStartAddress, a_nSize, pnSizeWritten);
			*a_nSizeWritten	=	(unsigned int) *pnSizeWritten;
			delete pnSizeWritten;
			return ret;
	}

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

		case LFT_HOST_CONNECTION_PCIE:
			pnSizeRead	=	new unsigned long(0);
			ret	=	BufRecv((DeviceTypesPci) a_enDeviceType, a_pchRdBuff, a_nStartAddress, a_nSize, pnSizeRead);
			*a_nSizeRead	=	(unsigned int) *pnSizeRead;
			delete pnSizeRead;
			return ret;
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

		case LFT_HOST_CONNECTION_PCIE:
			pnSizeWritten	=	new unsigned long(0);
			ret	=	BufSend((DeviceTypesPci)a_enDeviceType, a_pchWrBuff, a_nStartAddress, a_nSize, pnSizeWritten);
			*a_nSizeWritten	=	(unsigned int) *pnSizeWritten;
			delete pnSizeWritten;
			return ret;
	}

	return -100;
}

//Changing for DDR Access. __HP__3: 
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

	case LFT_HOST_CONNECTION_PCIE:
		return UpdateFirmWare((DeviceTypesPci) a_enDeviceType, a_strFileName);
	}
}

long MiddleAPI::RunTest(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,
			SPPUDeviceType a_enDeviceType,SPPUTestTypes a_enTestType, unsigned int *a_nPropValue)
{
	// TODO function call
	switch(a_enTestType)
	{
	
	case LFT_SPPU_TEST_FPGA	:
		 RunTestFPGA(a_enConnectionType,a_nModuleID,a_enDeviceType,a_nPropValue);
		 break;
    case LFT_SPPU_TEST_DAC_FPGA_INTERFACE:
		 RunTestDAC_FPGA(a_enConnectionType,a_nModuleID,a_enDeviceType,a_nPropValue);
		 break;
	case LFT_SPPU_TEST_SPI_NOR_FLASH:
		 RunTestNORFLASH(a_enConnectionType,a_nModuleID,a_enDeviceType,a_nPropValue);
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
	case LFT_SPPU_TEST_USB:
		 RunTestUSB(a_enConnectionType,a_nModuleID,a_enDeviceType,a_nPropValue);
		 break;
	case LFT_SPPU_TEST_ETHERNET:
		 RunTestEthernet(a_enConnectionType,a_nModuleID,a_enDeviceType,a_nPropValue);
		 break;
	case LFT_SPPU_TEST_TRIGGE_IN:
		 RunTest_trigger(a_enConnectionType,a_nModuleID,a_enDeviceType,a_nPropValue);
		 break;
	case LFT_SPPU_TEST_UNIT_TEST:
		// RunTestLMK(a_enConnectionType,a_nModuleID,a_enDeviceType,a_nPropValue);
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
	FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_DAC_SETUP_READ_FROM_DAC0, 0);
	return FPGARegAccessWrite(a_enConnectionType, a_nModuleID, a_enDeviceType, LFT_SPPU_FPGA_DAC_SETUP_READ_FROM_DAC1, 0);
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
	FPGARegAccessWrite(LFT_HOST_CONNECTION_ETH  , a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_RUN_TEST_FPGA, 66050); // has to chenged
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
	char strDebug[DEBUG_STR_LEN]     = {'/0'};
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

long MiddleAPI::RunTest_temp(SPPUHostConnectionType a_enConnectionType,unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,unsigned int *a_nPropValue) // chenged on 20th aug
{
	
	unsigned int readValue = 0;

	FPGARegAccessRead(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA ,LFT_SPPU_RUN_TEST_TEMP,&readValue);
	if(readValue == 0)
		*a_nPropValue = 0;
	else
		*a_nPropValue = 1;

	

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

	 sprintf_s(strDebug, DEBUG_STR_LEN,"\nIn FPGARegAccessRead(%d, %d, %d, %x, %x)", a_enConnectionType, a_nModuleID, a_enDeviceType, a_enSPPUFPGARegsDefs, *a_nPropValue);
	 mPrintDebug(strDebug);
 
	
	return ret;
}

int MiddleAPI::FPGARegAccessWrite(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,SPPUDeviceType a_enDeviceType,SPPUFPGARegsDefs a_enSPPUFPGARegsDefs, unsigned int a_nPropValue)           // sudeshna_reg_access  
		
{
	
	char strDebug[DEBUG_STR_LEN]	=	{'\0'};
		
	sprintf_s(strDebug, DEBUG_STR_LEN,"\nIn FPGARegAccessWrite(%d, %d, %d, %x, %x)", a_enConnectionType, a_nModuleID, a_enDeviceType, a_enSPPUFPGARegsDefs, a_nPropValue);
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
			

			break;

		case LFT_SPPU_FPGA_PROP_PULSE_WIDTH_channel_1:
			mPrintDebug("**************************Set PULSE_WIDTH_channel_1**************************");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DAC_SETUP_PULSEWIDTH_DAC0, a_nPropValue/4);
		

			break;
		case LFT_SPPU_FPGA_PROP_PULSE_WIDTH_channel_2:

			mPrintDebug("**************************Set PULSE_WIDTH_channel_2**************************");
			FPGARegAccessWrite(a_enConnectionType, a_nModuleID, LFT_SPPU_DEV_FPGA, LFT_SPPU_FPGA_DAC_SETUP_PULSEWIDTH_DAC1, a_nPropValue/4);

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


long MiddleAPI::GetDACProperty(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,
			SPPUDACProp a_enDACProp, unsigned int *a_nPropValue)		
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
	  
		


long MiddleAPI::SetLMKProperty(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID, SPPUDeviceType a_enDeviceType,
		 SPPULMKProp a_enLMKProp, unsigned int a_nPropValue)
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
}


long MiddleAPI::GetLMKProperty(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,
			SPPULMKProp a_enLMKProp, unsigned int *a_nPropValue)
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

long MiddleAPI::GetAttenuatorProperty(SPPUHostConnectionType a_enConnectionType, unsigned int a_nModuleID,SPPUAttenuatorProp a_enAttenuatorProp,
	 unsigned int *a_nPropValue)
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

MiddleAPI::~MiddleAPI()
{

}

/*
__HP__1 : First  minor change. Bug fix. First modification in bangalore.
__HP__2 : Bug Fix. Added support for 0's append while writing DDR if data is not multiple of 64 bytes.
__HP__3 : Modifications with checked and told by Dileep. Not tested throughly on hardware. Just once but no conclusion.
__HP__4 : Modify on 18 Oct 2015, While writing DDR, multiple of 64 byte size must be programmed in FPGA Register.
*/