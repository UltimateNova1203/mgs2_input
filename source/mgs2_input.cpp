#include "../include/mgs2_input.h"

// Digital Inputs
bool inputCross = false;
bool inputCircle = false;
bool inputTriangle = false;
bool inputSquare = false;
bool inputL1 = false;
bool inputL2 = false;
bool inputL3 = false;
bool inputR1 = false;
bool inputR2 = false;
bool inputR3 = false;
bool inputStart = false;
bool inputSelect = false;
bool inputDpadUp = false;
bool inputDpadRight = false;
bool inputDpadDown = false;
bool inputDpadLeft = false;

// Analog Sticks
BYTE inputLeftStickX = 127;
BYTE inputLeftStickY = 127;
BYTE inputRightStickX = 127;
BYTE inputRightStickY = 127;

// Pressure Sensitive Inputs
BYTE inputCrossPressure = 0;
BYTE inputCirclePressure = 0;
BYTE inputTrianglePressure = 0;
BYTE inputSquarePressure = 0;
BYTE inputL1Pressure = 0;
BYTE inputL2Pressure = 0;
BYTE inputR1Pressure = 0;
BYTE inputR2Pressure = 0;
BYTE inputDpadUpPressure = 0;
BYTE inputDpadRightPressure = 0;
BYTE inputDpadDownPressure = 0;
BYTE inputDpadLeftPressure = 0;

void pad_init() {
    // Disable buttons
    CPatch::Nop(0x008CF65E, 6);

    // Disable pressure sensitivity
    CPatch::Nop(0x008CF656, 2);

    // Disable left stick
    CPatch::Nop(0x008CF632, 5);         // X-axis
    CPatch::Nop(0x008CF63D, 6);         // Y-axis

    // Disable right stick
    CPatch::Nop(0x008CF637, 6);         // X-axis
    CPatch::Nop(0x008CF62C, 6);         // Y-axis

    // Center sticks
    CPatch::SetChar(0x00EDAC9E, 127);   // Left X-axis
    CPatch::SetChar(0x00EDAC9F, 127);   // Left Y-axis
    CPatch::SetChar(0x00EDAC9C, 127);   // Right X-axis
    CPatch::SetChar(0x00EDAC9D, 127);   // Right Y-axis

    // Set pressure sensitivity to 0
    CPatch::SetChar(0x00EDACA0, 0);     // Dpad Left
    CPatch::SetChar(0x00EDACA1, 0);     // Dpad Right
    CPatch::SetChar(0x00EDACA2, 0);     // Dpad Up
    CPatch::SetChar(0x00EDACA3, 0);     // Dpad Down
    CPatch::SetChar(0x00EDACA4, 0);     // Triangle
    CPatch::SetChar(0x00EDACA5, 0);     // Circle
    CPatch::SetChar(0x00EDACA6, 0);     // Cross
    CPatch::SetChar(0x00EDACA7, 0);     // Square
    CPatch::SetChar(0x00EDACA8, 0);     // L2
    CPatch::SetChar(0x00EDACA9, 0);     // R2
    CPatch::SetChar(0x00EDACAA, 0);     // L1
    CPatch::SetChar(0x00EDACAB, 0);     // R1

    // Fix pressure check
    CPatch::SetChar(0x00EDAC9A, 255);
}

void update_input() {
    pad_init();

    BYTE gamePrimaryButtons = 255;      // 0x00EDAC98
    BYTE gameL1 = 1;                    // Bit 0
    BYTE gameR1 = 2;                    // Bit 1
    BYTE gameL2 = 4;                    // Bit 2
    BYTE gameR2 = 8;                    // Bit 3
    BYTE gameTriangle = 16;             // Bit 4
    BYTE gameCircle = 32;               // Bit 5
    BYTE gameCross = 64;                // Bit 6
    BYTE gameSquare = 128;              // Bit 7

    BYTE gameSecondaryButtons = 255;    // 0x00EDAC99
    BYTE gameSelect = 1;                // Bit 0
    BYTE gameL3 = 2;                    // Bit 1
    BYTE gameR3 = 4;                    // Bit 2
    BYTE gameStart = 8;                 // Bit 3
    BYTE gameDpadUp = 16;               // Bit 4
    BYTE gameDpadRight = 32;            // Bit 5
    BYTE gameDpadDown = 64;             // Bit 6
    BYTE gameDpadLeft = 128;            // Bit 7

    BYTE gameRightStickX = 127;         // 0x00EDAC9C
    BYTE gameRightStickY = 127;         // 0x00EDAC9D
    BYTE gameLeftStickX = 127;          // 0x00EDAC9E
    BYTE gameLeftStickY = 127;          // 0x00EDAC9F

    while (true) {
        use_xinput();

        // Reset input states
        gamePrimaryButtons = 255;
        gameSecondaryButtons = 255;
        gameLeftStickX = 127;
        gameLeftStickY = 127;
        gameRightStickX = 127;
        gameRightStickY = 127;

        // Update button states
        if (inputCross) { gamePrimaryButtons = gamePrimaryButtons ^ gameCross; }
        if (inputCircle) { gamePrimaryButtons = gamePrimaryButtons ^ gameCircle; }
        if (inputTriangle) { gamePrimaryButtons = gamePrimaryButtons ^ gameTriangle; }
        if (inputSquare) { gamePrimaryButtons = gamePrimaryButtons ^ gameSquare; }
        if (inputL1) { gamePrimaryButtons = gamePrimaryButtons ^ gameL1; }
        if (inputL2) { gamePrimaryButtons = gamePrimaryButtons ^ gameL2; }
        if (inputL3) { gameSecondaryButtons = gameSecondaryButtons ^ gameL3; }
        if (inputR1) { gamePrimaryButtons = gamePrimaryButtons ^ gameR1; }
        if (inputR2) { gamePrimaryButtons = gamePrimaryButtons ^ gameR2; }
        if (inputR3) { gameSecondaryButtons = gameSecondaryButtons ^ gameR3; }
        if (inputStart) { gameSecondaryButtons = gameSecondaryButtons ^ gameStart; }
        if (inputSelect) { gameSecondaryButtons = gameSecondaryButtons ^ gameSelect; }
        if (inputDpadUp) { gameSecondaryButtons = gameSecondaryButtons ^ gameDpadUp; }
        if (inputDpadRight) { gameSecondaryButtons = gameSecondaryButtons ^ gameDpadRight; }
        if (inputDpadDown) { gameSecondaryButtons = gameSecondaryButtons ^ gameDpadDown; }
        if (inputDpadLeft) { gameSecondaryButtons = gameSecondaryButtons ^ gameDpadLeft; }
 
        CPatch::SetChar(0x00EDAC98, gamePrimaryButtons);
        CPatch::SetChar(0x00EDAC99, gameSecondaryButtons);

        // Feather L2/R2 pressure
        inputL2Pressure = inputL2Pressure * 0.7;
        inputR2Pressure = inputR2Pressure * 0.7;

        // Update pressure states
        CPatch::SetChar(0x00EDACA6, inputCrossPressure);
        CPatch::SetChar(0x00EDACA5, inputCirclePressure);
        CPatch::SetChar(0x00EDACA4, inputTrianglePressure);
        CPatch::SetChar(0x00EDACA7, inputSquarePressure);
        CPatch::SetChar(0x00EDACAA, inputL1Pressure);
        CPatch::SetChar(0x00EDACA8, inputL2Pressure);
        CPatch::SetChar(0x00EDACAB, inputR1Pressure);
        CPatch::SetChar(0x00EDACA9, inputR2Pressure);
        CPatch::SetChar(0x00EDACA2, inputDpadUpPressure);
        CPatch::SetChar(0x00EDACA0, inputDpadRightPressure);
        CPatch::SetChar(0x00EDACA1, inputDpadDownPressure);
        CPatch::SetChar(0x00EDACA3, inputDpadLeftPressure);

        // Ramp sticks towards edges
        if (inputLeftStickX < 40) { inputLeftStickX = 0; }
        if (inputLeftStickY < 40) { inputLeftStickY = 0; }
        if (inputRightStickX < 40) { inputRightStickX = 0; }
        if (inputRightStickY < 40) { inputRightStickY = 0; }
        if (inputLeftStickX > 215) { inputLeftStickX = 255; }
        if (inputLeftStickY > 215) { inputLeftStickY = 255; }
        if (inputRightStickX > 215) { inputRightStickX = 255; }
        if (inputRightStickY > 215) { inputRightStickY = 255; }

        // Update stick states
        gameLeftStickX = inputLeftStickX;
        gameLeftStickY = inputLeftStickY;
        gameRightStickX = inputRightStickX;
        gameRightStickY = inputRightStickY;

        CPatch::SetChar(0x00EDAC9E, gameLeftStickX);
        CPatch::SetChar(0x00EDAC9F, gameLeftStickY);
        CPatch::SetChar(0x00EDAC9C, gameRightStickX);
        CPatch::SetChar(0x00EDAC9D, gameRightStickY);

        // Polling rate 250Hz
        Sleep(4);
    }
}

void init() {
    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&update_input, 0, 0, NULL);
}