# Builds all the projects in the solution...
.PHONY: all_projects
all_projects: MiddleAPIWrapper SerialAPI EthernetAPI SppuUsbDll SppuUsbApp PcieDll Test_PciDll 

# Builds project 'MiddleAPIWrapper'...
.PHONY: MiddleAPIWrapper
MiddleAPIWrapper: EthernetAPI SerialAPI 
	make --directory="MiddleAPIWrapper/" --file=MiddleAPIWrapper.makefile

# Builds project 'SerialAPI'...
.PHONY: SerialAPI
SerialAPI: 
	make --directory="SerialAPI/" --file=SerialAPI.makefile

# Builds project 'EthernetAPI'...
.PHONY: EthernetAPI
EthernetAPI: 
	make --directory="EthernetAPI/EthernetAPI/" --file=EthernetAPI.makefile

# Builds project 'SppuUsbDll'...
.PHONY: SppuUsbDll
SppuUsbDll: 
	make --directory="SppuUsbDll/" --file=SppuUsbDll.makefile

# Builds project 'SppuUsbApp'...
.PHONY: SppuUsbApp
SppuUsbApp: SppuUsbDll 
	make --directory="SppuUsbApp/" --file=SppuUsbApp.makefile

# Builds project 'PcieDll'...
.PHONY: PcieDll
PcieDll: 
	make --directory="PcieDll/" --file=PcieDll.makefile

# Builds project 'Test_PciDll'...
.PHONY: Test_PciDll
Test_PciDll: PcieDll 
	make --directory="Test_PciDll/" --file=Test_PciDll.makefile

# Cleans all projects...
.PHONY: clean
clean:
	make --directory="MiddleAPIWrapper/" --file=MiddleAPIWrapper.makefile clean
	make --directory="SerialAPI/" --file=SerialAPI.makefile clean
	make --directory="EthernetAPI/EthernetAPI/" --file=EthernetAPI.makefile clean
	make --directory="SppuUsbDll/" --file=SppuUsbDll.makefile clean
	make --directory="SppuUsbApp/" --file=SppuUsbApp.makefile clean
	make --directory="PcieDll/" --file=PcieDll.makefile clean
	make --directory="Test_PciDll/" --file=Test_PciDll.makefile clean

