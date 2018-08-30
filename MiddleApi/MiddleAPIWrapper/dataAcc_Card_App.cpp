#include "../MiddleAPIWrapper.h"
#include <iostream>
#include <fstream>

#define		DEBUG_FILE_NAME				".\\centroid.txt"//"C:\\SppuUsbLog\\LogFile.txt"
#define		SAMPLE_DATA_FILE_NAME       ".\\samPledata.bin"
#define		VIDEO_FILE_SAMPLE           ".\\Wildlife.wmv"

#define DEBUG_FILE_EXIST	(-1 != _access(FAST_CENTROID_DEBUG_FILE, 0x0))

#include <stdio.h>
#include <iostream>
#include<fstream>
#include <math.h>

using namespace MiddleAPIWrapper;