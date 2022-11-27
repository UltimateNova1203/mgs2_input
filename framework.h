#pragma once

//#define XINPUTBRIDGE_EXPORTS

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <pshpack1.h>
#include <poppack.h>
#include <Xinput.h>
#include <iostream>
#include <thread>
#include <climits>

#include "CPatch.h"
//#include "hidapi.h"
//#include "ScpTypes.h"
//#include "Ds3Types.h"
//#include "XInputBridge.h"
#include "mgs2_input.h"
#include "xinput_device.h"