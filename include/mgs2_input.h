#pragma once

#include "framework.h"

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

// Rumble
extern BYTE outputRumble;

extern void init();
extern void pad_init();