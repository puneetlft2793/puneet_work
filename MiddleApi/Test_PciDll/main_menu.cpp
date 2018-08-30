#include "Pcie.h"

#define READ_DATA_FILE			".\\rtest.bin"
#define WRITE_DATA_FILE			".\\stest.bin"

using namespace Pcie;

int main()
{
	Pcie::c_Pcie obj;
	HANDLE	L_hs3_1000;
	int ch = 0;
	int choice = 0, ret = 0, choice_read = 0, choice_write = 0;
	UINT32 regAddr = 0;
	UINT32 regRdVal = 0, regWrVal = 0;
	DWORD rdStartAddr, wrStartAddr;
	DWORD rdNumBlocks, wrNumBlocks;
	DWORD numByRdSuccess, numByWrSuccess;

	while(1)
	{
		printf("+==============================+\n"
				"|        SPPU PCI DEMO         |\n"
				"|  Version 0.00.001 (Release)  |\n"
				"+==============================+\n"
				"    PCI MAIN MENU\n"
				"    -------------\n"
				"1. Open Device\n"
				"2. Close Device\n"
				"3. Reg Read SPPU\n"
				"4. Reg Write SPPU\n"
				"5. Reg Read BMD\n"
				"6. Reg Write BMD\n"
				"7. File Read\n"
				"8. File Write\n"
				"99. Exit.\n"
				"===============================\n");
		printf("Enter your choice\n");
		scanf("%d", &choice);

		switch(choice)
		{
			case 1:
				printf("	Open Device\n"
						"	-----------\n");				
				L_hs3_1000 = obj.OpenDeviceByGuid( (LPGUID) &GuidDriver);
				//hs3_1000 = OpenDeviceByGuid( (LPGUID) &GUID_RIFFA_INTERFACE);
				if (L_hs3_1000 && L_hs3_1000 != INVALID_HANDLE_VALUE)
				{
					printf("Success: File Opened!\n");
				}
				else 
				{
					printf("Error: File not Opened!\nhs3_1000 = %ld\n", (HANDLE)L_hs3_1000);
				}
				break;

			case 2:
				printf("	Close Device\n"
						"	-------------\n");
				obj.CloseDevice();
				break;

			case 3:
				printf("    Reg Read (SPPU)\n"
						"	---------------\n");
				printf("Enter register Address\n0x");
				scanf("%x", &regAddr);
				printf("You Entered :- \n");
				printf("RegAddr = 0x%x\n", regAddr);
				if(0 == obj.RegisterRead(regAddr, &regRdVal))
					printf("Value Read at addr = 0x%x = 0x%x\n",  regAddr, regRdVal);
				else
					printf("Test Application: Error! See log file.\n");
				break;

			case 4:

				printf("    Reg Write (SPPU)\n"
						"	----------------\n");
				printf("Enter register Address\n0x");
				scanf("%x", &regAddr);
				printf("Enter value \n0x");
				scanf("%x", &regWrVal);
				printf("You Entered :- \n");
				printf("RegAddr = 0x%x\n", regAddr);
				printf("RegVal  = 0x%x\n", regWrVal);
				if(0 == obj.RegisterWrite(regAddr, regWrVal))
					printf("Value Wrote at addr = 0x%x = 0x%x\n",  regAddr, regWrVal);
				else
					printf("Test Application: Error! See log file.\n");

				break;
			
			case 5:
				printf("    Reg Read (BMD)\n"
						"	--------------\n");
				printf("Enter register Address\n0x");
				scanf("%x", &regAddr);
				printf("You Entered :- \n");
				printf("RegAddr = 0x%x\n", regAddr);
				if(0 == obj.__RegisterRead(regAddr, &regRdVal))
					printf("Value Read at addr = 0x%x = 0x%x\n",  regAddr, regRdVal);
				else
					printf("Test Application: Error! See log file.\n");
				break;

			case 6:
				printf("    Reg Write (BMD)\n"
						"	---------------\n");
				printf("Enter register Address\n0x");
				scanf("%x", &regAddr);
				printf("Enter value \n0x");
				scanf("%x", &regWrVal);
				printf("You Entered :- \n");
				printf("RegAddr = 0x%x\n", regAddr);
				printf("RegVal  = 0x%x\n", regWrVal);
				if(0 == obj.__RegisterWrite(regAddr, regWrVal))
					printf("Value Wrote at addr = 0x%x = 0x%x\n",  regAddr, regWrVal);
				else
					printf("Test Application: Error! See log file.\n");
				break;

			case 7:
				printf("	File Read\n"
						"	 ---------\n");
				printf("Enter Start Address\n0x");
				scanf("%x", &regAddr);
				printf("Enter number of bytes to read\n0x");
				scanf("%x", &regWrVal);
				if(0 == obj.FileRecv((DeviceTypesPci)6, READ_DATA_FILE, regAddr, regWrVal, &numByRdSuccess))
					printf("SUCCESS: File Recv. See log file for more information\n");
				else
					printf("FAILURE: File Recv. See log file for more information\n");
				break;
			
			case 8:
				printf("	File Write\n"
						"	 ----------\n");
				printf("Enter Start Address\n0x");
				scanf("%x", &regAddr);
				printf("Enter number of bytes to write\n0x");
				scanf("%x", &regWrVal);
				if(0 == obj.FileSend((DeviceTypesPci)6, WRITE_DATA_FILE, regAddr, regWrVal, &numByWrSuccess))
					printf("SUCCESS: File Send. See log file for more information\n");
				else
					printf("FAILURE: File Send. See log file for more information\n");
				break;
			
			case 99:
				exit(0);
			default:
				printf("Choice not recognized! (%d)\n", choice); 
		}
	}		//While(1)


//	test_main();	//This will work only in x64 mode and not in Win32 mode.

	printf("Enter any character to exit!\n");
	scanf("%d", &ch);
	return 0;
}
