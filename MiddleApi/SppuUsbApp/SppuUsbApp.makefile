# Compiler flags...
CPP_COMPILER = g++
C_COMPILER = gcc

# Include paths...
Debug_Include_Path=-I"../SppuUsbDll/include" -I"../SppuUsbDll/" 
Release_Include_Path=-I"../SppuUsbDll/include" -I"../SppuUsbDll/" 

# Library paths...
Debug_Library_Path=
Release_Library_Path=

# Additional libraries...
Debug_Libraries=
Release_Libraries=

# Preprocessor definitions...
Debug_Preprocessor_Definitions=-D GCC_BUILD -D _DEBUG -D _CONSOLE 
Release_Preprocessor_Definitions=-D GCC_BUILD -D NDEBUG -D _CONSOLE 

# Implictly linked object files...
Debug_Implicitly_Linked_Objects=
Release_Implicitly_Linked_Objects=

# Compiler flags...
Debug_Compiler_Flags=-O0 -g 
Release_Compiler_Flags=-O2 

# Builds all configurations for this project...
.PHONY: build_all_configurations
build_all_configurations: Debug Release 

# Builds the Debug configuration...
.PHONY: Debug
Debug: create_folders gccDebug/SppuUsbApp.o gccDebug/stdafx.o 
	g++ gccDebug/SppuUsbApp.o gccDebug/stdafx.o  $(Debug_Library_Path) $(Debug_Libraries) -Wl,-rpath,./ -o ../gccDebug/SppuUsbApp.exe

# Compiles file SppuUsbApp.cpp for the Debug configuration...
-include gccDebug/SppuUsbApp.d
gccDebug/SppuUsbApp.o: SppuUsbApp.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c SppuUsbApp.cpp $(Debug_Include_Path) -o gccDebug/SppuUsbApp.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM SppuUsbApp.cpp $(Debug_Include_Path) > gccDebug/SppuUsbApp.d

# Compiles file stdafx.cpp for the Debug configuration...
-include gccDebug/stdafx.d
gccDebug/stdafx.o: stdafx.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c stdafx.cpp $(Debug_Include_Path) -o gccDebug/stdafx.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM stdafx.cpp $(Debug_Include_Path) > gccDebug/stdafx.d

# Builds the Release configuration...
.PHONY: Release
Release: create_folders gccRelease/SppuUsbApp.o gccRelease/stdafx.o 
	g++ gccRelease/SppuUsbApp.o gccRelease/stdafx.o  $(Release_Library_Path) $(Release_Libraries) -Wl,-rpath,./ -o ../gccRelease/SppuUsbApp.exe

# Compiles file SppuUsbApp.cpp for the Release configuration...
-include gccRelease/SppuUsbApp.d
gccRelease/SppuUsbApp.o: SppuUsbApp.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c SppuUsbApp.cpp $(Release_Include_Path) -o gccRelease/SppuUsbApp.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM SppuUsbApp.cpp $(Release_Include_Path) > gccRelease/SppuUsbApp.d

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

