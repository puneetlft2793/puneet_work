# Compiler flags...
CPP_COMPILER = g++
C_COMPILER = gcc

# Include paths...
Debug_Include_Path=-I"./include" 
Release_Include_Path=-I"./include" 

# Library paths...
Debug_Library_Path=
Release_Library_Path=

# Additional libraries...
Debug_Libraries=-Wl,--start-group -lCyAPI -lSetupAPI  -Wl,--end-group
Release_Libraries=-Wl,--start-group -lCyAPI -lSetupAPI  -Wl,--end-group

# Preprocessor definitions...
Debug_Preprocessor_Definitions=-D GCC_BUILD -D _DEBUG -D _WINDOWS -D _USRDLL -D SPPUUSBDLL_EXPORTS 
Release_Preprocessor_Definitions=-D GCC_BUILD -D NDEBUG -D _WINDOWS -D _USRDLL -D SPPUUSBDLL_EXPORTS 

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
Debug: create_folders gccDebug/dllmain.o gccDebug/SppuUsbDll.o gccDebug/stdafx.o 
	g++ -fPIC -shared -Wl,-soname,libSppuUsbDll.so -o ../gccDebug/libSppuUsbDll.so gccDebug/dllmain.o gccDebug/SppuUsbDll.o gccDebug/stdafx.o  $(Debug_Implicitly_Linked_Objects)

# Compiles file dllmain.cpp for the Debug configuration...
-include gccDebug/dllmain.d
gccDebug/dllmain.o: dllmain.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c dllmain.cpp $(Debug_Include_Path) -o gccDebug/dllmain.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM dllmain.cpp $(Debug_Include_Path) > gccDebug/dllmain.d

# Compiles file SppuUsbDll.cpp for the Debug configuration...
-include gccDebug/SppuUsbDll.d
gccDebug/SppuUsbDll.o: SppuUsbDll.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c SppuUsbDll.cpp $(Debug_Include_Path) -o gccDebug/SppuUsbDll.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM SppuUsbDll.cpp $(Debug_Include_Path) > gccDebug/SppuUsbDll.d

# Compiles file stdafx.cpp for the Debug configuration...
-include gccDebug/stdafx.d
gccDebug/stdafx.o: stdafx.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c stdafx.cpp $(Debug_Include_Path) -o gccDebug/stdafx.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM stdafx.cpp $(Debug_Include_Path) > gccDebug/stdafx.d

# Builds the Release configuration...
.PHONY: Release
Release: create_folders gccRelease/dllmain.o gccRelease/SppuUsbDll.o gccRelease/stdafx.o 
	g++ -fPIC -shared -Wl,-soname,libSppuUsbDll.so -o ../gccRelease/libSppuUsbDll.so gccRelease/dllmain.o gccRelease/SppuUsbDll.o gccRelease/stdafx.o  $(Release_Implicitly_Linked_Objects)

# Compiles file dllmain.cpp for the Release configuration...
-include gccRelease/dllmain.d
gccRelease/dllmain.o: dllmain.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c dllmain.cpp $(Release_Include_Path) -o gccRelease/dllmain.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM dllmain.cpp $(Release_Include_Path) > gccRelease/dllmain.d

# Compiles file SppuUsbDll.cpp for the Release configuration...
-include gccRelease/SppuUsbDll.d
gccRelease/SppuUsbDll.o: SppuUsbDll.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c SppuUsbDll.cpp $(Release_Include_Path) -o gccRelease/SppuUsbDll.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM SppuUsbDll.cpp $(Release_Include_Path) > gccRelease/SppuUsbDll.d

# Compiles file stdafx.cpp for the Release configuration...
-include gccRelease/stdafx.d
gccRelease/stdafx.o: stdafx.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c stdafx.cpp $(Release_Include_Path) -o gccRelease/stdafx.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM stdafx.cpp $(Release_Include_Path) > gccRelease/stdafx.d

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

