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
Debug_Preprocessor_Definitions=-D GCC_BUILD -D _DEBUG -D _WINDOWS -D _USRDLL -D SERIALAPI_EXPORTS 
Release_Preprocessor_Definitions=-D GCC_BUILD -D NDEBUG -D _WINDOWS -D _USRDLL -D SERIALAPI_EXPORTS 

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
Debug: create_folders gccDebug/../EthernetAPI/EthernetAPI/cprotocol.o gccDebug/SerialAPI.o 
	g++ -fPIC -shared -Wl,-soname,libSerialAPI.so -o ../gccDebug/libSerialAPI.so gccDebug/../EthernetAPI/EthernetAPI/cprotocol.o gccDebug/SerialAPI.o  $(Debug_Implicitly_Linked_Objects)

# Compiles file ../EthernetAPI/EthernetAPI/cprotocol.cpp for the Debug configuration...
-include gccDebug/../EthernetAPI/EthernetAPI/cprotocol.d
gccDebug/../EthernetAPI/EthernetAPI/cprotocol.o: ../EthernetAPI/EthernetAPI/cprotocol.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c ../EthernetAPI/EthernetAPI/cprotocol.cpp $(Debug_Include_Path) -o gccDebug/../EthernetAPI/EthernetAPI/cprotocol.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM ../EthernetAPI/EthernetAPI/cprotocol.cpp $(Debug_Include_Path) > gccDebug/../EthernetAPI/EthernetAPI/cprotocol.d

# Compiles file SerialAPI.cpp for the Debug configuration...
-include gccDebug/SerialAPI.d
gccDebug/SerialAPI.o: SerialAPI.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c SerialAPI.cpp $(Debug_Include_Path) -o gccDebug/SerialAPI.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM SerialAPI.cpp $(Debug_Include_Path) > gccDebug/SerialAPI.d

# Builds the Release configuration...
.PHONY: Release
Release: create_folders gccRelease/../EthernetAPI/EthernetAPI/cprotocol.o gccRelease/SerialAPI.o 
	g++ -fPIC -shared -Wl,-soname,libSerialAPI.so -o ../gccRelease/libSerialAPI.so gccRelease/../EthernetAPI/EthernetAPI/cprotocol.o gccRelease/SerialAPI.o  $(Release_Implicitly_Linked_Objects)

# Compiles file ../EthernetAPI/EthernetAPI/cprotocol.cpp for the Release configuration...
-include gccRelease/../EthernetAPI/EthernetAPI/cprotocol.d
gccRelease/../EthernetAPI/EthernetAPI/cprotocol.o: ../EthernetAPI/EthernetAPI/cprotocol.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c ../EthernetAPI/EthernetAPI/cprotocol.cpp $(Release_Include_Path) -o gccRelease/../EthernetAPI/EthernetAPI/cprotocol.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM ../EthernetAPI/EthernetAPI/cprotocol.cpp $(Release_Include_Path) > gccRelease/../EthernetAPI/EthernetAPI/cprotocol.d

# Compiles file SerialAPI.cpp for the Release configuration...
-include gccRelease/SerialAPI.d
gccRelease/SerialAPI.o: SerialAPI.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c SerialAPI.cpp $(Release_Include_Path) -o gccRelease/SerialAPI.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM SerialAPI.cpp $(Release_Include_Path) > gccRelease/SerialAPI.d

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

