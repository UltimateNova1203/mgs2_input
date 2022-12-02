#pragma once

#include "framework.h"

// Digital Inputs
extern BOOL inputCross;
extern BOOL inputCircle;
extern BOOL inputTriangle;
extern BOOL inputSquare;
extern BOOL inputL1;
extern BOOL inputL2;
extern BOOL inputL3;
extern BOOL inputR1;
extern BOOL inputR2;
extern BOOL inputR3;
extern BOOL inputStart;
extern BOOL inputSelect;
extern BOOL inputDpadUp;
extern BOOL inputDpadRight;
extern BOOL inputDpadDown;
extern BOOL inputDpadLeft;

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

// Rumble
extern BYTE outputRumble;

// Say I fixed it
extern BOOL ds4Initialized;

extern void init();
extern void pad_init();