#pragma once

#include <Windows.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <thread>

#include "CPatch.h"
#include "dualshock3_device.h"
#include "dualshock4_device.h"
#include "xinput_device.h"

// Digital Inputs
extern bool inputCross;
extern bool inputCircle;
extern bool inputTriangle;
extern bool inputSquare;
extern bool inputL1;
extern bool inputL2;
extern bool inputL3;
extern bool inputR1;
extern bool inputR2;
extern bool inputR3;
extern bool inputStart;
extern bool inputSelect;
extern bool inputDpadUp;
extern bool inputDpadRight;
extern bool inputDpadDown;
extern bool inputDpadLeft;

// Analog Sticks
extern BYTE inputLeftStickX;
extern BYTE inputLeftStickY;
extern BYTE inputRightStickX;
extern BYTE inputRightStickY;

// Pressure Sensitive Inputs
extern BYTE inputCrossPressure;
extern BYTE inputCirclePressure;
extern BYTE inputTrianglePressure;
extern BYTE inputSquarePressure;
extern BYTE inputL1Pressure;
extern BYTE inputL2Pressure;
extern BYTE inputR1Pressure;
extern BYTE inputR2Pressure;
extern BYTE inputDpadUpPressure;
extern BYTE inputDpadRightPressure;
extern BYTE inputDpadDownPressure;
extern BYTE inputDpadLeftPressure;

extern void init();
extern void pad_init();