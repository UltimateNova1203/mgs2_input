#include "framework.h"

bool xinputDpadUp = false;
bool xinputDpadDown = false;
bool xinputDpadLeft = false;
bool xinputDpadRight = false;
bool xinputStart = false;
bool xinputBack = false;
bool xinputLeftThumb = false;
bool xinputRightThumb = false;
bool xinputLeftShoulder = false;
bool xinputRightShoulder = false;
bool xinputA = false;
bool xinputB = false;
bool xinputX = false;
bool xinputY = false;
BYTE xinputLeftTrigger = 0;
BYTE xinputRightTrigger = 0;
short xinputLeftStickX = 0;
short xinputLeftStickY = 0;
short xinputRightStickX = 0;
short xinputRightStickY = 0;

void use_xinput() {
    for (DWORD ControllerIndex = 0; ControllerIndex < XUSER_MAX_COUNT; ++ControllerIndex) {
        XINPUT_STATE ControllerState;

        if (XInputGetState(ControllerIndex, &ControllerState) == ERROR_SUCCESS) {

            xinputDpadUp = ControllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP;
            xinputDpadDown = ControllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN;
            xinputDpadLeft = ControllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT;
            xinputDpadRight = ControllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
            xinputStart = ControllerState.Gamepad.wButtons & XINPUT_GAMEPAD_START;
            xinputBack = ControllerState.Gamepad.wButtons & XINPUT_GAMEPAD_BACK;
            xinputLeftThumb = ControllerState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB;
            xinputRightThumb = ControllerState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB;
            xinputLeftShoulder = ControllerState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER;
            xinputRightShoulder = ControllerState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER;
            xinputA = ControllerState.Gamepad.wButtons & XINPUT_GAMEPAD_A;
            xinputB = ControllerState.Gamepad.wButtons & XINPUT_GAMEPAD_B;
            xinputX = ControllerState.Gamepad.wButtons & XINPUT_GAMEPAD_X;
            xinputY = ControllerState.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
            xinputLeftTrigger = ControllerState.Gamepad.bLeftTrigger;
            xinputRightTrigger = ControllerState.Gamepad.bRightTrigger;
            xinputLeftStickX = ControllerState.Gamepad.sThumbLX;
            xinputLeftStickY = ControllerState.Gamepad.sThumbLY;
            xinputRightStickX = ControllerState.Gamepad.sThumbRX;
            xinputRightStickY = ControllerState.Gamepad.sThumbRY;

            // A Button
            if (xinputA) {
                inputCross = true;
                inputCrossPressure = 255;
            }
            else {
                inputCross = false;
                inputCrossPressure = 0;
            }

            // B Button
            if (xinputB) {
                inputCircle = true;
                inputCirclePressure = 255;
            }
            else {
                inputCircle = false;
                inputCirclePressure = 0;
            }

            // X Button
            if (xinputX) {
                inputSquare = true;
                inputSquarePressure = 255;
            }
            else {
                if (xinputLeftThumb) {
                    inputSquare = true;

                    if (inputSquarePressure > 7) { inputSquarePressure = inputSquarePressure - 4; }
                    else if (inputSquarePressure > 0) { inputSquarePressure = inputSquarePressure - 1; }
                    else if (inputSquarePressure == 0) {
                        inputSquare = false;
                        inputSquarePressure = 0;
                    }
                }
                else {
                    inputSquare = false;
                    inputSquarePressure = 0;
                }
            }

            // Y Button
            if (xinputY) {
                inputTriangle = true;
                inputTrianglePressure = 255;
            }
            else {
                inputTriangle = false;
                inputTrianglePressure = 0;
            }

            // Start Button
            if (xinputStart) { inputStart = true; }
            else { inputStart = false; }

            // Back Button
            if (xinputBack) { inputSelect = true; }
            else { inputSelect = false; }

            // Dpad Up
            if (xinputDpadUp) { inputDpadUp = true; }
            else { inputDpadUp = false; }

            // Dpad Right
            if (xinputDpadRight) { inputDpadRight = true; }
            else { inputDpadRight = false; }

            // Dpad Down
            if (xinputDpadDown) { inputDpadDown = true; }
            else { inputDpadDown = false; }

            // Dpad Left
            if (xinputDpadLeft) { inputDpadLeft = true; }
            else { inputDpadLeft = false; }

            if (xinputDpadUp || xinputDpadRight || xinputDpadDown || xinputDpadLeft) {
#ifdef XINPUT_DPAD_STALK
                inputDpadUpPressure = 48;
                inputDpadRightPressure = 48;
                inputDpadDownPressure = 48;
                inputDpadLeftPressure = 48;
#endif
#ifndef XINPUT_DPAD_STALK
                inputDpadUpPressure = 255;
                inputDpadRightPressure = 255;
                inputDpadDownPressure = 255;
                inputDpadLeftPressure = 255;
#endif
            }

            if (!xinputDpadUp && !xinputDpadRight && !xinputDpadDown && !xinputDpadLeft) {
                inputDpadUpPressure = 0;
                inputDpadRightPressure = 0;
                inputDpadDownPressure = 0;
                inputDpadLeftPressure = 0;
            }

            // Left Shoulder
            if (xinputLeftShoulder) {
                inputL1 = true;
                inputL1Pressure = 255;
            }
            else {
                inputL1 = false;
                inputL1Pressure = 0;
            }

            // Left Trigger
            if (xinputLeftTrigger > 24) {
                inputL2 = true;
                inputL2Pressure = xinputLeftTrigger;
            }
            else {
                inputL2 = false;
                inputL2Pressure = xinputLeftTrigger;
            }

            // Right Shoulder
            if (xinputRightShoulder) {
                inputR1 = true;
                inputR1Pressure = 255;
            }
            else {
                inputR1 = false;
                inputR1Pressure = 0;
            }

            // Right Trigger
            if (xinputRightTrigger > 24) {
                inputR2 = true;
                inputR2Pressure = xinputRightTrigger;
            }
            else {
                inputR2 = false;
                inputR2Pressure = xinputRightTrigger;
            }

            // Left Thumb
            if (xinputLeftThumb) { CPatch::SetChar(0x00EDAC9A, 253); }
            else { CPatch::SetChar(0x00EDAC9A, 255); }

            // Right Thumb
            if (xinputRightThumb) { inputR3 = true; }
            else { inputR3 = false; }

            // Left Thumbstick
            inputLeftStickX = (xinputLeftStickX + 32767) / 256;
            inputLeftStickY = (-xinputLeftStickY + 32767) / 256;

            // Right Thumbstick
            inputRightStickX = (xinputRightStickX + 32767) / 256;
            inputRightStickY = (-xinputRightStickY + 32767) / 256;
        }
    }
}
