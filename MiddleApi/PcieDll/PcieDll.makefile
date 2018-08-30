# Compiler flags...
CPP_COMPILER = g++
C_COMPILER = gcc

# Include paths...
Debug_Include_Path=
Release_Include_Path=

# Library paths...
Debug_Library_Path=
Release_Library_Path=

# Additional libraries...
Debug_Libraries=
Release_Libraries=-Wl,--start-group -lSetupApi  -Wl,--end-group

# Preprocessor definitions...
Debug_Preprocessor_Definitions=-D GCC_BUILD -D _DEBUG -D _WINDOWS -D _USRDLL -D PCIEDLL_EXPORTS 
Release_Preprocessor_Definitions=-D GCC_BUILD -D NDEBUG -D _WINDOWS -D _USRDLL -D PCIEDLL_EXPORTS 

# Implictly linked object files...
Debug_Implicitly_Linked_Objects=
Release_Implicitly_Linked_Objects=

# Compiler flags...
Debug_Compiler_Flags=-fPIC -O0 -g 
Release_Compiler_Flags=-fPIC -O2 

# Builds all configurations for this project...
.PHONY: build_all_configurations
build_all_configurations: Debug Release 

# Builds the Debug configuration...
.PHONY: Debug
Debug: create_folders gccDebug/PcieBulkXfer.o gccDebug/PcieDevOpenClose.o gccDebug/PcieRegAccess.o 
	g++ -fPIC -shared -Wl,-soname,libPcieDll.so -o ../gccDebug/libPcieDll.so gccDebug/PcieBulkXfer.o gccDebug/PcieDevOpenClose.o gccDebug/PcieRegAccess.o  $(Debug_Implicitly_Linked_Objects)

# Compiles file PcieBulkXfer.cpp for the Debug configuration...
-include gccDebug/PcieBulkXfer.d
gccDebug/PcieBulkXfer.o: PcieBulkXfer.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c PcieBulkXfer.cpp $(Debug_Include_Path) -o gccDebug/PcieBulkXfer.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM PcieBulkXfer.cpp $(Debug_Include_Path) > gccDebug/PcieBulkXfer.d

# Compiles file PcieDevOpenClose.cpp for the Debug configuration...
-include gccDebug/PcieDevOpenClose.d
gccDebug/PcieDevOpenClose.o: PcieDevOpenClose.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c PcieDevOpenClose.cpp $(Debug_Include_Path) -o gccDebug/PcieDevOpenClose.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM PcieDevOpenClose.cpp $(Debug_Include_Path) > gccDebug/PcieDevOpenClose.d

# Compiles file PcieRegAccess.cpp for the Debug configuration...
-include gccDebug/PcieRegAccess.d
gccDebug/PcieRegAccess.o: PcieRegAccess.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c PcieRegAccess.cpp $(Debug_Include_Path) -o gccDebug/PcieRegAccess.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM PcieRegAccess.cpp $(Debug_Include_Path) > gccDebug/PcieRegAccess.d

# Builds the Release configuration...
.PHONY: Release
Release: create_folders gccRelease/PcieBulkXfer.o gccRelease/PcieDevOpenClose.o gccRelease/PcieRegAccess.o 
	g++ -fPIC -shared -Wl,-soname,libPcieDll.so -o ../gccRelease/libPcieDll.so gccRelease/PcieBulkXfer.o gccRelease/PcieDevOpenClose.o gccRelease/PcieRegAccess.o  $(Release_Implicitly_Linked_Objects)

# Compiles file PcieBulkXfer.cpp for the Release configuration...
-include gccRelease/PcieBulkXfer.d
gccRelease/PcieBulkXfer.o: PcieBulkXfer.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c PcieBulkXfer.cpp $(Release_Include_Path) -o gccRelease/PcieBulkXfer.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM PcieBulkXfer.cpp $(Release_Include_Path) > gccRelease/PcieBulkXfer.d

# Compiles file PcieDevOpenClose.cpp for the Release configuration...
-include gccRelease/PcieDevOpenClose.d
gccRelease/PcieDevOpenClose.o: PcieDevOpenClose.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c PcieDevOpenClose.cpp $(Release_Include_Path) -o gccRelease/PcieDevOpenClose.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM PcieDevOpenClose.cpp $(Release_Include_Path) > gccRelease/PcieDevOpenClose.d

# Compiles file PcieRegAccess.cpp for the Release configuration...
-include gccRelease/PcieRegAccess.d
gccRelease/PcieRegAccess.o: PcieRegAccess.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c PcieRegAccess.cpp $(Release_Include_Path) -o gccRelease/PcieRegAccess.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM PcieRegAccess.cpp $(Release_Include_Path) > gccRelease/PcieRegAccess.d

# Creates the intermediate and output folders for each configuration...
.PHONY: create_folders
create_folders:
	mkdir -p gccDebug/source
	mkdir -p ../gccDebug
	mkdir -p gccRelease/source
	mkdir -p ../gccRelease

# Cleans intermediate and output files (objects, libraries, executables)...
.PHONY: clean
clean:
	rm -f gccDebug/*.o
	rm -f gccDebug/*.d
	rm -f ../gccDebug/*.a
	rm -f ../gccDebug/*.so
	rm -f ../gccDebug/*.dll
	rm -f ../gccDebug/*.exe
	rm -f gccRelease/*.o
	rm -f gccRelease/*.d
	rm -f ../gccRelease/*.a
	rm -f ../gccRelease/*.so
	rm -f ../gccRelease/*.dll
	rm -f ../gccRelease/*.exe

