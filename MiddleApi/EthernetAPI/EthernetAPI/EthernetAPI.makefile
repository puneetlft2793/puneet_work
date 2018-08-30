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
Release_Libraries=

# Preprocessor definitions...
Debug_Preprocessor_Definitions=-D GCC_BUILD -D _DEBUG -D _WINDOWS -D _USRDLL -D MIDDLEAPI_EXPORTS 
Release_Preprocessor_Definitions=-D GCC_BUILD -D NDEBUG -D _WINDOWS -D _USRDLL -D MIDDLEAPI_EXPORTS 

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
Debug: create_folders gccDebug/cprotocol.o gccDebug/EthernetAPI.o 
	g++ -fPIC -shared -Wl,-soname,libEthernetAPI.so -o ../../gccDebug/libEthernetAPI.so gccDebug/cprotocol.o gccDebug/EthernetAPI.o  $(Debug_Implicitly_Linked_Objects)

# Compiles file cprotocol.cpp for the Debug configuration...
-include gccDebug/cprotocol.d
gccDebug/cprotocol.o: cprotocol.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c cprotocol.cpp $(Debug_Include_Path) -o gccDebug/cprotocol.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM cprotocol.cpp $(Debug_Include_Path) > gccDebug/cprotocol.d

# Compiles file EthernetAPI.cpp for the Debug configuration...
-include gccDebug/EthernetAPI.d
gccDebug/EthernetAPI.o: EthernetAPI.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c EthernetAPI.cpp $(Debug_Include_Path) -o gccDebug/EthernetAPI.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM EthernetAPI.cpp $(Debug_Include_Path) > gccDebug/EthernetAPI.d

# Builds the Release configuration...
.PHONY: Release
Release: create_folders gccRelease/cprotocol.o gccRelease/EthernetAPI.o 
	g++ -fPIC -shared -Wl,-soname,libEthernetAPI.so -o ../../gccRelease/libEthernetAPI.so gccRelease/cprotocol.o gccRelease/EthernetAPI.o  $(Release_Implicitly_Linked_Objects)

# Compiles file cprotocol.cpp for the Release configuration...
-include gccRelease/cprotocol.d
gccRelease/cprotocol.o: cprotocol.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c cprotocol.cpp $(Release_Include_Path) -o gccRelease/cprotocol.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM cprotocol.cpp $(Release_Include_Path) > gccRelease/cprotocol.d

# Compiles file EthernetAPI.cpp for the Release configuration...
-include gccRelease/EthernetAPI.d
gccRelease/EthernetAPI.o: EthernetAPI.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c EthernetAPI.cpp $(Release_Include_Path) -o gccRelease/EthernetAPI.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM EthernetAPI.cpp $(Release_Include_Path) > gccRelease/EthernetAPI.d

# Creates the intermediate and output folders for each configuration...
.PHONY: create_folders
create_folders:
	mkdir -p gccDebug/source
	mkdir -p ../../gccDebug
	mkdir -p gccRelease/source
	mkdir -p ../../gccRelease

# Cleans intermediate and output files (objects, libraries, executables)...
.PHONY: clean
clean:
	rm -f gccDebug/*.o
	rm -f gccDebug/*.d
	rm -f ../../gccDebug/*.a
	rm -f ../../gccDebug/*.so
	rm -f ../../gccDebug/*.dll
	rm -f ../../gccDebug/*.exe
	rm -f gccRelease/*.o
	rm -f gccRelease/*.d
	rm -f ../../gccRelease/*.a
	rm -f ../../gccRelease/*.so
	rm -f ../../gccRelease/*.dll
	rm -f ../../gccRelease/*.exe

