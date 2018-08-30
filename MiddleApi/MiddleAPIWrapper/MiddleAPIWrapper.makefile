# Compiler flags...
CPP_COMPILER = g++
C_COMPILER = gcc

# Include paths...
Debug_Include_Path=
Debug_Include_Path=
Release_Include_Path=
Release_Include_Path=

# Library paths...
Debug_Library_Path=-L"../gccDebug" 
Debug_Library_Path=
Release_Library_Path=-L"D:/project/sppu/29th9/0.00.044/10thsep_4.30latest/MiddleAPIWrapper/gccRelease" -L"D:/project/sppu/MiddileWrapper/guichenges/0.00.039_all_28aug15/MiddleAPIWrapper/gccRelease" -L"D:/project/sppu/MiddileWrapper/0.00.039_all_28aug15/MiddleAPIWrapper/gccRelease" -L"D:/sppu/latest20.8.15/MiddleAPIWrapper/gccRelease" -L"Q:/gccLib" -L"../gccRelease" 
Release_Library_Path=

# Additional libraries...
Debug_Libraries=-Wl,--start-group -lSppuUsbDll  -Wl,--end-group
Debug_Libraries=-Wl,--start-group -lSppuUsbDlld  -Wl,--end-group
Release_Libraries=-Wl,--start-group -lSerialAPI -lEthernetAPI -lSppuUsbDLL -lPcieDll -lwdapi1160 -lxbmd_memory_diag -lFTD2XX  -Wl,--end-group
Release_Libraries=-Wl,--start-group -lSerialAPI -lEthernetAPI -lSppuUsbDLL -lwdapi1160 -lxbmd_memory_diag  -Wl,--end-group

# Preprocessor definitions...
Debug_Preprocessor_Definitions=-D GCC_BUILD -D _DEBUG -D _WINDOWS -D _USRDLL -D MIDDLEAPIWRAPPER_EXPORTS 
Debug_Preprocessor_Definitions=-D GCC_BUILD -D _DEBUG -D _WINDOWS -D _USRDLL -D MIDDLEAPIWRAPPER_EXPORTS 
Release_Preprocessor_Definitions=-D GCC_BUILD -D NDEBUG -D _WINDOWS -D _USRDLL -D MIDDLEAPIWRAPPER_EXPORTS 
Release_Preprocessor_Definitions=-D GCC_BUILD -D NDEBUG -D _WINDOWS -D _USRDLL -D MIDDLEAPIWRAPPER_EXPORTS 

# Implictly linked object files...
Debug_Implicitly_Linked_Objects=
Debug_Implicitly_Linked_Objects=
Release_Implicitly_Linked_Objects=
Release_Implicitly_Linked_Objects=

# Compiler flags...
Debug_Compiler_Flags=-fPIC -O0 -g 
Debug_Compiler_Flags=-fPIC -O0 -g 
Release_Compiler_Flags=-fPIC -O2 
Release_Compiler_Flags=-fPIC -O2 

# Builds all configurations for this project...
.PHONY: build_all_configurations
build_all_configurations: Debug Debug Release Release 

# Builds the Debug configuration...
.PHONY: Debug
Debug: create_folders gccDebug/Data_Recorder/dataRecorder.o gccDebug/Fast_Centroid/FastCentroidApp.o gccDebug/MiddleAPIWrapper.o 
	g++ -fPIC -shared -Wl,-soname,libMiddleAPIWrapper.so -o ../gccDebug/libMiddleAPIWrapper.so gccDebug/Data_Recorder/dataRecorder.o gccDebug/Fast_Centroid/FastCentroidApp.o gccDebug/MiddleAPIWrapper.o  $(Debug_Implicitly_Linked_Objects)

# Compiles file Data_Recorder/dataRecorder.cpp for the Debug configuration...
-include gccDebug/Data_Recorder/dataRecorder.d
gccDebug/Data_Recorder/dataRecorder.o: Data_Recorder/dataRecorder.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c Data_Recorder/dataRecorder.cpp $(Debug_Include_Path) -o gccDebug/Data_Recorder/dataRecorder.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM Data_Recorder/dataRecorder.cpp $(Debug_Include_Path) > gccDebug/Data_Recorder/dataRecorder.d

# Compiles file Fast_Centroid/FastCentroidApp.cpp for the Debug configuration...
-include gccDebug/Fast_Centroid/FastCentroidApp.d
gccDebug/Fast_Centroid/FastCentroidApp.o: Fast_Centroid/FastCentroidApp.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c Fast_Centroid/FastCentroidApp.cpp $(Debug_Include_Path) -o gccDebug/Fast_Centroid/FastCentroidApp.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM Fast_Centroid/FastCentroidApp.cpp $(Debug_Include_Path) > gccDebug/Fast_Centroid/FastCentroidApp.d

# Compiles file MiddleAPIWrapper.cpp for the Debug configuration...
-include gccDebug/MiddleAPIWrapper.d
gccDebug/MiddleAPIWrapper.o: MiddleAPIWrapper.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c MiddleAPIWrapper.cpp $(Debug_Include_Path) -o gccDebug/MiddleAPIWrapper.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM MiddleAPIWrapper.cpp $(Debug_Include_Path) > gccDebug/MiddleAPIWrapper.d

# Builds the Debug configuration...
.PHONY: Debug
Debug: create_folders x64/gccDebug/Data_Recorder/dataRecorder.o x64/gccDebug/Fast_Centroid/FastCentroidApp.o x64/gccDebug/MiddleAPIWrapper.o 
	g++ -fPIC -shared -Wl,-soname,libMiddleAPIWrapper.so -o ../x64/gccDebug/libMiddleAPIWrapper.so x64/gccDebug/Data_Recorder/dataRecorder.o x64/gccDebug/Fast_Centroid/FastCentroidApp.o x64/gccDebug/MiddleAPIWrapper.o  $(Debug_Implicitly_Linked_Objects)

# Compiles file Data_Recorder/dataRecorder.cpp for the Debug configuration...
-include x64/gccDebug/Data_Recorder/dataRecorder.d
x64/gccDebug/Data_Recorder/dataRecorder.o: Data_Recorder/dataRecorder.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c Data_Recorder/dataRecorder.cpp $(Debug_Include_Path) -o x64/gccDebug/Data_Recorder/dataRecorder.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM Data_Recorder/dataRecorder.cpp $(Debug_Include_Path) > x64/gccDebug/Data_Recorder/dataRecorder.d

# Compiles file Fast_Centroid/FastCentroidApp.cpp for the Debug configuration...
-include x64/gccDebug/Fast_Centroid/FastCentroidApp.d
x64/gccDebug/Fast_Centroid/FastCentroidApp.o: Fast_Centroid/FastCentroidApp.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c Fast_Centroid/FastCentroidApp.cpp $(Debug_Include_Path) -o x64/gccDebug/Fast_Centroid/FastCentroidApp.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM Fast_Centroid/FastCentroidApp.cpp $(Debug_Include_Path) > x64/gccDebug/Fast_Centroid/FastCentroidApp.d

# Compiles file MiddleAPIWrapper.cpp for the Debug configuration...
-include x64/gccDebug/MiddleAPIWrapper.d
x64/gccDebug/MiddleAPIWrapper.o: MiddleAPIWrapper.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c MiddleAPIWrapper.cpp $(Debug_Include_Path) -o x64/gccDebug/MiddleAPIWrapper.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM MiddleAPIWrapper.cpp $(Debug_Include_Path) > x64/gccDebug/MiddleAPIWrapper.d

# Builds the Release configuration...
.PHONY: Release
Release: create_folders gccRelease/Data_Recorder/dataRecorder.o gccRelease/Fast_Centroid/FastCentroidApp.o gccRelease/MiddleAPIWrapper.o 
	g++ -fPIC -shared -Wl,-soname,libMiddleAPIWrapper.so -o ../gccRelease/libMiddleAPIWrapper.so gccRelease/Data_Recorder/dataRecorder.o gccRelease/Fast_Centroid/FastCentroidApp.o gccRelease/MiddleAPIWrapper.o  $(Release_Implicitly_Linked_Objects)

# Compiles file Data_Recorder/dataRecorder.cpp for the Release configuration...
-include gccRelease/Data_Recorder/dataRecorder.d
gccRelease/Data_Recorder/dataRecorder.o: Data_Recorder/dataRecorder.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c Data_Recorder/dataRecorder.cpp $(Release_Include_Path) -o gccRelease/Data_Recorder/dataRecorder.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM Data_Recorder/dataRecorder.cpp $(Release_Include_Path) > gccRelease/Data_Recorder/dataRecorder.d

# Compiles file Fast_Centroid/FastCentroidApp.cpp for the Release configuration...
-include gccRelease/Fast_Centroid/FastCentroidApp.d
gccRelease/Fast_Centroid/FastCentroidApp.o: Fast_Centroid/FastCentroidApp.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c Fast_Centroid/FastCentroidApp.cpp $(Release_Include_Path) -o gccRelease/Fast_Centroid/FastCentroidApp.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM Fast_Centroid/FastCentroidApp.cpp $(Release_Include_Path) > gccRelease/Fast_Centroid/FastCentroidApp.d

# Compiles file MiddleAPIWrapper.cpp for the Release configuration...
-include gccRelease/MiddleAPIWrapper.d
gccRelease/MiddleAPIWrapper.o: MiddleAPIWrapper.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c MiddleAPIWrapper.cpp $(Release_Include_Path) -o gccRelease/MiddleAPIWrapper.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM MiddleAPIWrapper.cpp $(Release_Include_Path) > gccRelease/MiddleAPIWrapper.d

# Builds the Release configuration...
.PHONY: Release
Release: create_folders x64/gccRelease/Data_Recorder/dataRecorder.o x64/gccRelease/Fast_Centroid/FastCentroidApp.o x64/gccRelease/MiddleAPIWrapper.o 
	g++ -fPIC -shared -Wl,-soname,libMiddleAPIWrapper.so -o ../x64/gccRelease/libMiddleAPIWrapper.so x64/gccRelease/Data_Recorder/dataRecorder.o x64/gccRelease/Fast_Centroid/FastCentroidApp.o x64/gccRelease/MiddleAPIWrapper.o  $(Release_Implicitly_Linked_Objects)

# Compiles file Data_Recorder/dataRecorder.cpp for the Release configuration...
-include x64/gccRelease/Data_Recorder/dataRecorder.d
x64/gccRelease/Data_Recorder/dataRecorder.o: Data_Recorder/dataRecorder.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c Data_Recorder/dataRecorder.cpp $(Release_Include_Path) -o x64/gccRelease/Data_Recorder/dataRecorder.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM Data_Recorder/dataRecorder.cpp $(Release_Include_Path) > x64/gccRelease/Data_Recorder/dataRecorder.d

# Compiles file Fast_Centroid/FastCentroidApp.cpp for the Release configuration...
-include x64/gccRelease/Fast_Centroid/FastCentroidApp.d
x64/gccRelease/Fast_Centroid/FastCentroidApp.o: Fast_Centroid/FastCentroidApp.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c Fast_Centroid/FastCentroidApp.cpp $(Release_Include_Path) -o x64/gccRelease/Fast_Centroid/FastCentroidApp.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM Fast_Centroid/FastCentroidApp.cpp $(Release_Include_Path) > x64/gccRelease/Fast_Centroid/FastCentroidApp.d

# Compiles file MiddleAPIWrapper.cpp for the Release configuration...
-include x64/gccRelease/MiddleAPIWrapper.d
x64/gccRelease/MiddleAPIWrapper.o: MiddleAPIWrapper.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c MiddleAPIWrapper.cpp $(Release_Include_Path) -o x64/gccRelease/MiddleAPIWrapper.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM MiddleAPIWrapper.cpp $(Release_Include_Path) > x64/gccRelease/MiddleAPIWrapper.d

# Creates the intermediate and output folders for each configuration...
.PHONY: create_folders
create_folders:
	mkdir -p gccDebug/source
	mkdir -p ../gccDebug
	mkdir -p x64/gccDebug/source
	mkdir -p ../x64/gccDebug
	mkdir -p gccRelease/source
	mkdir -p ../gccRelease
	mkdir -p x64/gccRelease/source
	mkdir -p ../x64/gccRelease

# Cleans intermediate and output files (objects, libraries, executables)...
.PHONY: clean
clean:
	rm -f gccDebug/*.o
	rm -f gccDebug/*.d
	rm -f ../gccDebug/*.a
	rm -f ../gccDebug/*.so
	rm -f ../gccDebug/*.dll
	rm -f ../gccDebug/*.exe
	rm -f x64/gccDebug/*.o
	rm -f x64/gccDebug/*.d
	rm -f ../x64/gccDebug/*.a
	rm -f ../x64/gccDebug/*.so
	rm -f ../x64/gccDebug/*.dll
	rm -f ../x64/gccDebug/*.exe
	rm -f gccRelease/*.o
	rm -f gccRelease/*.d
	rm -f ../gccRelease/*.a
	rm -f ../gccRelease/*.so
	rm -f ../gccRelease/*.dll
	rm -f ../gccRelease/*.exe
	rm -f x64/gccRelease/*.o
	rm -f x64/gccRelease/*.d
	rm -f ../x64/gccRelease/*.a
	rm -f ../x64/gccRelease/*.so
	rm -f ../x64/gccRelease/*.dll
	rm -f ../x64/gccRelease/*.exe

