#include "framework.h"

// Digital Inputs
BOOL ds4Cross = false;
BOOL ds4Circle = false;
BOOL ds4Triangle = false;
BOOL ds4Square = false;
BOOL ds4L1 = false;
BOOL ds4L2 = false;
BOOL ds4L3 = false;
BOOL ds4R1 = false;
BOOL ds4R2 = false;
BOOL ds4R3 = false;
BOOL ds4Start = false;
BOOL ds4Select = false;
BOOL ds4DpadUp = false;
BOOL ds4DpadRight = false;
BOOL ds4DpadDown = false;
BOOL ds4DpadLeft = false;

// Analog Sticks
BYTE ds4LeftStickX = 127;
BYTE ds4LeftStickY = 127;
BYTE ds4RightStickX = 127;
BYTE ds4RightStickY = 127;

// Pressure Sensitive inputs
BYTE ds4L2Pressure = 0;
BYTE ds4R2Pressure = 0;

// Rumble
BYTE ds4tRumble = 0;

// DS4 HID Setup
hid_device_info* hidDeviceInfo;
hid_device* hidHandle;
unsigned char inputBufferUSB[31];
unsigned char inputBufferBT[78];
unsigned char outputBufferUSB[31];
unsigned char outputBufferBT[78];
BYTE ds4Type = 0; // 1: v1, 2: v2, 3: WA, 4: BT

DWORD crc_table[256] = {
		0x00000000, 0x77073096, 0xEE0E612C, 0x990951BA,
		0x076DC419, 0x706AF48F, 0xE963A535, 0x9E6495A3,
		0x0EDB8832, 0x79DCB8A4, 0xE0D5E91E, 0x97D2D988,
		0x09B64C2B, 0x7EB17CBD, 0xE7B82D07, 0x90BF1D91,
		0x1DB71064, 0x6AB020F2, 0xF3B97148, 0x84BE41DE,
		0x1ADAD47D, 0x6DDDE4EB, 0xF4D4B551, 0x83D385C7,
		0x136C9856, 0x646BA8C0, 0xFD62F97A, 0x8A65C9EC,
		0x14015C4F, 0x63066CD9, 0xFA0F3D63, 0x8D080DF5,
		0x3B6E20C8, 0x4C69105E, 0xD56041E4, 0xA2677172,
		0x3C03E4D1, 0x4B04D447, 0xD20D85FD, 0xA50AB56B,
		0x35B5A8FA, 0x42B2986C, 0xDBBBC9D6, 0xACBCF940,
		0x32D86CE3, 0x45DF5C75, 0xDCD60DCF, 0xABD13D59,
		0x26D930AC, 0x51DE003A, 0xC8D75180, 0xBFD06116,
		0x21B4F4B5, 0x56B3C423, 0xCFBA9599, 0xB8BDA50F,
		0x2802B89E, 0x5F058808, 0xC60CD9B2, 0xB10BE924,
		0x2F6F7C87, 0x58684C11, 0xC1611DAB, 0xB6662D3D,
		0x76DC4190, 0x01DB7106, 0x98D220BC, 0xEFD5102A,
		0x71B18589, 0x06B6B51F, 0x9FBFE4A5, 0xE8B8D433,
		0x7807C9A2, 0x0F00F934, 0x9609A88E, 0xE10E9818,
		0x7F6A0DBB, 0x086D3D2D, 0x91646C97, 0xE6635C01,
		0x6B6B51F4, 0x1C6C6162, 0x856530D8, 0xF262004E,
		0x6C0695ED, 0x1B01A57B, 0x8208F4C1, 0xF50FC457,
		0x65B0D9C6, 0x12B7E950, 0x8BBEB8EA, 0xFCB9887C,
		0x62DD1DDF, 0x15DA2D49, 0x8CD37CF3, 0xFBD44C65,
		0x4DB26158, 0x3AB551CE, 0xA3BC0074, 0xD4BB30E2,
		0x4ADFA541, 0x3DD895D7, 0xA4D1C46D, 0xD3D6F4FB,
		0x4369E96A, 0x346ED9FC, 0xAD678846, 0xDA60B8D0,
		0x44042D73, 0x33031DE5, 0xAA0A4C5F, 0xDD0D7CC9,
		0x5005713C, 0x270241AA, 0xBE0B1010, 0xC90C2086,
		0x5768B525, 0x206F85B3, 0xB966D409, 0xCE61E49F,
		0x5EDEF90E, 0x29D9C998, 0xB0D09822, 0xC7D7A8B4,
		0x59B33D17, 0x2EB40D81, 0xB7BD5C3B, 0xC0BA6CAD,
		0xEDB88320, 0x9ABFB3B6, 0x03B6E20C, 0x74B1D29A,
		0xEAD54739, 0x9DD277AF, 0x04DB2615, 0x73DC1683,
		0xE3630B12, 0x94643B84, 0x0D6D6A3E, 0x7A6A5AA8,
		0xE40ECF0B, 0x9309FF9D, 0x0A00AE27, 0x7D079EB1,
		0xF00F9344, 0x8708A3D2, 0x1E01F268, 0x6906C2FE,
		0xF762575D, 0x806567CB, 0x196C3671, 0x6E6B06E7,
		0xFED41B76, 0x89D32BE0, 0x10DA7A5A, 0x67DD4ACC,
		0xF9B9DF6F, 0x8EBEEFF9, 0x17B7BE43, 0x60B08ED5,
		0xD6D6A3E8, 0xA1D1937E, 0x38D8C2C4, 0x4FDFF252,
		0xD1BB67F1, 0xA6BC5767, 0x3FB506DD, 0x48B2364B,
		0xD80D2BDA, 0xAF0A1B4C, 0x36034AF6, 0x41047A60,
		0xDF60EFC3, 0xA867DF55, 0x316E8EEF, 0x4669BE79,
		0xCB61B38C, 0xBC66831A, 0x256FD2A0, 0x5268E236,
		0xCC0C7795, 0xBB0B4703, 0x220216B9, 0x5505262F,
		0xC5BA3BBE, 0xB2BD0B28, 0x2BB45A92, 0x5CB36A04,
		0xC2D7FFA7, 0xB5D0CF31, 0x2CD99E8B, 0x5BDEAE1D,
		0x9B64C2B0, 0xEC63F226, 0x756AA39C, 0x026D930A,
		0x9C0906A9, 0xEB0E363F, 0x72076785, 0x05005713,
		0x95BF4A82, 0xE2B87A14, 0x7BB12BAE, 0x0CB61B38,
		0x92D28E9B, 0xE5D5BE0D, 0x7CDCEFB7, 0x0BDBDF21,
		0x86D3D2D4, 0xF1D4E242, 0x68DDB3F8, 0x1FDA836E,
		0x81BE16CD, 0xF6B9265B, 0x6FB077E1, 0x18B74777,
		0x88085AE6, 0xFF0F6A70, 0x66063BCA, 0x11010B5C,
		0x8F659EFF, 0xF862AE69, 0x616BFFD3, 0x166CCF45,
		0xA00AE278, 0xD70DD2EE, 0x4E048354, 0x3903B3C2,
		0xA7672661, 0xD06016F7, 0x4969474D, 0x3E6E77DB,
		0xAED16A4A, 0xD9D65ADC, 0x40DF0B66, 0x37D83BF0,
		0xA9BCAE53, 0xDEBB9EC5, 0x47B2CF7F, 0x30B5FFE9,
		0xBDBDF21C, 0xCABAC28A, 0x53B39330, 0x24B4A3A6,
		0xBAD03605, 0xCDD70693, 0x54DE5729, 0x23D967BF,
		0xB3667A2E, 0xC4614AB8, 0x5D681B02, 0x2A6F2B94,
		0xB40BBE37, 0xC30C8EA1, 0x5A05DF1B, 0x2D02EF8D
};

DWORD crc_32(unsigned char* buf, int length) {
	DWORD result = 0xFFFFFFFF;
	int index = 0;
	while (index < length) {
		result = crc_table[(result & 0xFF) ^ buf[index]] ^ (result >> 8);
		index++;
	}
	return result ^ 0xFFFFFFFF;
}

void exit_ds4() {

	if (ds4Type == 1 || ds4Type == 2) {
		outputBufferUSB[0] = 0x05;
		outputBufferUSB[1] = 0xFF;
		outputBufferUSB[4] = 0x00; // Left Motor
		outputBufferUSB[5] = 0x00; // Right Motor
		outputBufferUSB[6] = 0x00; // Red LED
		outputBufferUSB[7] = 0x00; // Green LED
		outputBufferUSB[8] = 0xFF; // Blue LED
		outputBufferUSB[9] = 0x00;
		outputBufferUSB[10] = 0x00;
		hid_set_nonblocking(hidHandle, 1);
		hid_write(hidHandle, outputBufferUSB, 31);
	}

	if (ds4Type == 3 || ds4Type == 4) {
		outputBufferBT[0] = 0x05;
		outputBufferBT[1] = 0xFF;
		outputBufferBT[4] = 0x00;
		outputBufferBT[5] = 0x00;
		outputBufferBT[6] = 0x00;
		outputBufferBT[7] = 0x00; // Left Motor
		outputBufferBT[8] = 0x00; //Right Motor
		outputBufferBT[9] = 0x00; // Red LED
		outputBufferBT[10] = 0x00; // Green LED
		outputBufferBT[11] = 0xFF; // Blue LED
		hid_set_nonblocking(hidHandle, 1);
		hid_write(hidHandle, outputBufferBT, 78);
	}

	hid_close(hidHandle);
	hid_exit();
}

int update_ds4() {
	hid_init();

	while (true) {

/*		 // Try DS4 v1 USB
		hidHandle = hid_open(0x054C, 0x054C, NULL);
		if (!hidHandle) {
			// Try DS4 v2 USB
			hidHandle = hid_open(0x054C, 0x9CC, NULL);

			if (!hidHandle) {
				// Try DS4 Wireless Adapter
				hidDeviceInfo = hid_enumerate(0x054C, 0x0BA0);
				hidHandle = hid_open_path(hidDeviceInfo->path);

				if (!hidHandle) {
					// Try DS4 over Bluetooth
					hidDeviceInfo = hid_enumerate(0x054C, 0x081F);
					hidHandle = hid_open_path(hidDeviceInfo->path);

					if (!hidHandle) {
						ds4Type = 0;
					}
					else { ds4Type = 4; }
				}
				else { ds4Type = 3; }
			}
			else { ds4Type = 2; }
		}
		else { ds4Type = 1; }*/

		hidHandle = hid_open(0x054C, 0x09CC, NULL);
		if (!hidHandle) {
			hidDeviceInfo = hid_enumerate(0x054C, 0x0BA0);
			hidHandle = hid_open_path(hidDeviceInfo->path);
			ds4Type = 3;
			memset(outputBufferBT, 0, 78);
			outputBufferBT[0] = 0x15;
			outputBufferBT[1] = 0xC0 | 1;
			outputBufferBT[2] = 0xA0;
			outputBufferBT[3] = 0xF7;
			outputBufferBT[4] = 0x04;
			outputBufferBT[6] = 0x00;
			outputBufferBT[7] = 0xFF;
			outputBufferBT[8] = 0x00;
			hid_set_nonblocking(hidHandle, 0);
			hid_write(hidHandle, outputBufferBT, 78);
		} 
		else { 
			ds4Type = 2;
			memset(outputBufferUSB, 0, 31);
			outputBufferUSB[0] = 0x05;
			outputBufferUSB[1] = 0xFF;
			outputBufferUSB[6] = 0xFF;
			outputBufferUSB[7] = 0x00;
			outputBufferUSB[8] = 0x00;
			hid_set_nonblocking(hidHandle, 0);
			hid_write(hidHandle, outputBufferUSB, 31);
		}

		hidDeviceInfo = hid_enumerate(0x054C, 0x0BA0);
		hidHandle = hid_open_path(hidDeviceInfo->path);

		// Prep Wired controllers
		if (ds4Type == 1 || ds4Type == 2) {
		}

		// Prep Wireless controllers
		if (ds4Type == 3 || ds4Type == 4) {
		}

		// Write LED status for Wired controllers
		if (ds4Type == 1 || ds4Type == 2) {
		}

		// Write LED status for Wireless controllers
		if (ds4Type == 3 || ds4Type == 4) {
		}

		hid_set_nonblocking(hidHandle, 0);

		if (ds4Type == 1 || ds4Type == 2) {
		}

		if (ds4Type == 3 || ds4Type == 4) {
			//DWORD crc = crc_32(outputBufferBT, 75);
			//memcpy(&outputBufferBT[75], &crc, 4);

		}

		// Polling rate 250Hz
		Sleep(4);
	}
}

/*
void ds4Init(
	_In_ BOOL isBT,
	_In_ UCHAR outputBuffer[80]
) {
	// Are we using Bluetooth?
	if (isBT) {
		// Report ID
		outputBuffer[0] = 0x15;
		outputBuffer[1] = 0xC0 | 1;
		outputBuffer[2] = 0xA0;
		outputBuffer[3] = 0xF7;
		outputBuffer[4] = 0x04;
	}

	// Guess we're using USB then
	else {
		// Report ID
		outputBuffer[0] = 0x05;
		outputBuffer[1] = 0xf7;
		outputBuffer[2] = 0x04;
	}
}

void ds4SetLEDs(
	_In_ BOOL isBT,
	_In_ UCHAR outputBuffer[80],
	_In_ DS4_LIGHTBAR Lightbar
) {
	// Are we using Bluetooth?
	if (isBT) {
		outputBuffer[9] = Lightbar.bRed;
		outputBuffer[10] = Lightbar.bGreen;
		outputBuffer[11] = Lightbar.bBlue;
	}

	// Guess we're using USB then
	else {
		outputBuffer[6] = Lightbar.bRed;
		outputBuffer[7] = Lightbar.bGreen;
		outputBuffer[8] = Lightbar.bBlue;
	}
}

void ds4SetRumble(
	_In_ BOOL isBT,
	_In_ UCHAR outputBuffer[80],
	_In_ DS4_VIBRATION Vibration
) {
	// Are we using Bluetooth?
	if (isBT) {
		outputBuffer[7] = Vibration.bLeftMotor;
		outputBuffer[8] = Vibration.bRightMotor;
	}

	// Guess we're using USB then
	else {
		outputBuffer[4] = Vibration.bLeftMotor;
		outputBuffer[5] = Vibration.bRightMotor;
	}
}

void ds4Enable(
	_In_ BOOL enable,
	_In_ BOOL isBT,
	_In_ hid_device* hidHandle
) {
	DS4_LIGHTBAR Lightbar;
	DS4_VIBRATION Vibration;

	UCHAR usbOutputBuffer[80];
	UCHAR btOutputBuffer[80];

	// Turning on the DS4
	if (enable) {
		Lightbar.bRed = 0xA0;
		Lightbar.bGreen = 0xA0;
		Lightbar.bBlue = 0xA0;

		Vibration.bLeftMotor = 0x00;
		Vibration.bRightMotor = 0x00;

		// Are we using Bluetooth?
		if (isBT) {
			memset(btOutputBuffer, 0, 80);

			ds4Init(isBT, btOutputBuffer);
			ds4SetLEDs(isBT, btOutputBuffer, Lightbar);
			ds4SetRumble(isBT, btOutputBuffer, Vibration);

			hid_set_nonblocking(hidHandle, 0);
			hid_write(hidHandle, btOutputBuffer, 80);
		}

		// Guess we're using USB then
		else {
			memset(usbOutputBuffer, 0, 80);

			ds4Init(isBT, usbOutputBuffer);
			ds4SetLEDs(isBT, usbOutputBuffer, Lightbar);
			ds4SetRumble(isBT, usbOutputBuffer, Vibration);

			hid_set_nonblocking(hidHandle, 0);
			hid_write(hidHandle, usbOutputBuffer, 80);
		}
	}

	// Turning off the DS4
	else {
		Lightbar.bRed = 0x00;
		Lightbar.bGreen = 0x00;
		Lightbar.bBlue = 0x00;

		Vibration.bLeftMotor = 0x00;
		Vibration.bRightMotor = 0x00;

		// Are we using Bluetooth?
		if (isBT) {
			memset(btOutputBuffer, 0, 80);

			// Report ID
			btOutputBuffer[0] = 0x15;
			btOutputBuffer[1] = 0xC0 | 1;
			btOutputBuffer[2] = 0xA0;
			btOutputBuffer[3] = 0xF7;
			btOutputBuffer[4] = 0x04;

			ds4SetLEDs(isBT, btOutputBuffer, Lightbar);
			ds4SetRumble(isBT, btOutputBuffer, Vibration);

			hid_set_nonblocking(hidHandle, 0);
			hid_write(hidHandle, btOutputBuffer, 80);
		}

		// Guess we're using USB then
		else {
			memset(usbOutputBuffer, 0, 31);

			// Report ID
			usbOutputBuffer[0] = 0x05;
			usbOutputBuffer[1] = 0xff;

			// Lightbar Flash Time
			usbOutputBuffer[9] = 0x00;
			usbOutputBuffer[10] = 0x00;

			ds4SetLEDs(isBT, usbOutputBuffer, Lightbar);
			ds4SetRumble(isBT, usbOutputBuffer, Vibration);

			hid_set_nonblocking(hidHandle, 1);
			hid_write(hidHandle, usbOutputBuffer, 80);
		}
	}
}

void ds4GetState(
	_In_ BOOL isBT,
	_In_ hid_device* hidHandle,
	_Out_ DS4_STATE* pState
) {
	UCHAR btInputBuffer[80];
	UCHAR usbInputBuffer[80];

	if (isBT) {
		hid_read(hidHandle, btInputBuffer, 80);
		pState->Gamepad.bLeftThumbX = btInputBuffer[4];
		pState->Gamepad.bLeftThumbY = btInputBuffer[5];
		pState->Gamepad.bRightThumbX = btInputBuffer[6];
		pState->Gamepad.bRightThumbY = btInputBuffer[7];
		pState->Gamepad.bPrimaryButtons = btInputBuffer[8];
		pState->Gamepad.bSecondaryButtons = btInputBuffer[9];
		pState->Gamepad.bSpecialButtons = btInputBuffer[10];
		pState->Gamepad.bL2Pressure = btInputBuffer[11];
		pState->Gamepad.bR2Pressure = btInputBuffer[12];
		pState->Accel.sAccelX = (btInputBuffer[16] << 8) | btInputBuffer[17];
		pState->Accel.sAccelY = (btInputBuffer[18] << 8) | btInputBuffer[19];
		pState->Accel.sAccelZ = (btInputBuffer[20] << 8) | btInputBuffer[21];
		pState->Gyro.sGyroX = (btInputBuffer[22] << 8) | btInputBuffer[23];
		pState->Gyro.sGyroY = (btInputBuffer[24] << 8) | btInputBuffer[25];
		pState->Gyro.sGyroZ = (btInputBuffer[26] << 8) | btInputBuffer[27];
		pState->Touchpad.bFinger1 = (btInputBuffer[38] & 0x7f);
		pState->Touchpad.bFinger1X = (((btInputBuffer[40] & 0x0F) << 8) | btInputBuffer[39]);
		pState->Touchpad.bFinger1Y = (((btInputBuffer[40] & 0x0F) << 4) | ((btInputBuffer[39] & 0xf0) >> 4));
		pState->Touchpad.bFinger2 = (btInputBuffer[42] & 0x7f);
		pState->Touchpad.bFinger2X = (((btInputBuffer[44] & 0x0F) << 8) | btInputBuffer[43]);
		pState->Touchpad.bFinger2Y = (((btInputBuffer[45] & 0x0F) << 4) | ((btInputBuffer[44] & 0xf0) >> 4));
	}

	else {
		hid_read(hidHandle, usbInputBuffer, 80);
		pState->Gamepad.bLeftThumbX = usbInputBuffer[1];
		pState->Gamepad.bLeftThumbY = usbInputBuffer[2];
		pState->Gamepad.bRightThumbX = usbInputBuffer[3];
		pState->Gamepad.bRightThumbY = usbInputBuffer[4];
		pState->Gamepad.bPrimaryButtons = usbInputBuffer[5];
		pState->Gamepad.bSecondaryButtons = usbInputBuffer[6];
		pState->Gamepad.bSpecialButtons = usbInputBuffer[7];
		pState->Gamepad.bL2Pressure = usbInputBuffer[8];
		pState->Gamepad.bR2Pressure = usbInputBuffer[9];
		pState->Gyro.sGyroX = (usbInputBuffer[13] << 8) | usbInputBuffer[14];
		pState->Gyro.sGyroY = (usbInputBuffer[15] << 8) | usbInputBuffer[16];
		pState->Gyro.sGyroZ = (usbInputBuffer[17] << 8) | usbInputBuffer[18];
		pState->Accel.sAccelX = (usbInputBuffer[19] << 8) | usbInputBuffer[20];
		pState->Accel.sAccelY = (usbInputBuffer[21] << 8) | usbInputBuffer[22];
		pState->Accel.sAccelZ = (usbInputBuffer[23] << 8) | usbInputBuffer[24];
		pState->Touchpad.bFinger1 = (usbInputBuffer[35] & 0x7f);
		pState->Touchpad.bFinger1X = (((usbInputBuffer[47] & 0x0F) << 8) | usbInputBuffer[36]);
		pState->Touchpad.bFinger1Y = (((usbInputBuffer[47] & 0x0F) << 4) | ((usbInputBuffer[36] & 0xf0) >> 4));
		pState->Touchpad.bFinger2 = (usbInputBuffer[39] & 0x7f);
		pState->Touchpad.bFinger2X = (((usbInputBuffer[41] & 0x0F) << 8) | usbInputBuffer[40]);
		pState->Touchpad.bFinger2Y = (((usbInputBuffer[42] & 0x0F) << 4) | ((usbInputBuffer[41] & 0xf0) >> 4));
	}
}

void ds4SetState(
	_In_ BOOL isBT,
	_In_ hid_device* hidHandle,
	_In_ DS4_LIGHTBAR* pLightbar,
	_In_ DS4_VIBRATION* pVibration
) {
	UCHAR btOutputBuffer[80];
	UCHAR usbOutputBuffer[80];

	if (isBT) {
		ds4SetLEDs(isBT, btOutputBuffer, *pLightbar);
		ds4SetRumble(isBT, btOutputBuffer, *pVibration);
	}

	else {
		ds4SetLEDs(isBT, usbOutputBuffer, *pLightbar);
		ds4SetRumble(isBT, usbOutputBuffer, *pVibration);
	}
}



void use_ds4input() {
	BOOL isBT;

	hidHandleInfo = hid_enumerate(0x054C, 0x0BA0);
	hidHandle = hid_open_path(hidHandleInfo->path);

	// Try USB first
	//hidHandle = hid_open(0x054C, 0x054C, NULL); //DS4 USB V1
	//if (!hidHandle) { hidHandle = hid_open(0x054C, 0x09CC, NULL); } //DS4 USB V2
	
	//if (hidHandle) {
		//isBT = false;
		// Accessed DS4 USB
		//ds4Enable(true, isBT, hidHandle);
	//}

	//else {
		//hidHandleInfo = hid_enumerate(0x054C, 0x0BA0);
		//hidHandle = hid_open_path(hidHandleInfo->path);

	isBT = true;
		//hidHandleInfo = hid_enumerate(0x054C, 0x0BA0); //DS4 Wireless Adapter
		//hidHandle = hid_open_path(hidHandleInfo->path);

		//if(!hidHandle) {
			//hidHandleInfo = hid_enumerate(0x054C, 0x081F); //DS4 Bluetooth
			//hidHandle = hid_open_path(hidHandleInfo->path);
		//}

		ds4Enable(true, isBT, hidHandle);
	//}

	//if (hidHandleInfo->vendor_id == 0x054C) { 
		//isBT = false; 
		//hidHandle = hid_open_path(hidHandleInfo);
		//ds4Enable(true, isBT, hidHandle);
	//}
	//if (hidHandleInfo->vendor_id == 0x09CC) { isBT = false; }
	//if (hidHandleInfo->vendor_id == 0x0BA0) { isBT = true; }
	//if (hidHandleInfo->vendor_id == 0x081F) { isBT = true; }


	DS4_STATE dualshock4;
	DS4_LIGHTBAR dualshock4lightbar;
	DS4_VIBRATION dualshock4vibration;
	ds4GetState(isBT, hidHandle, &dualshock4);

	// Primary buttons
	inputCross = dualshock4.Gamepad.bPrimaryButtons & DS4_GAMEPAD_CROSS;
	inputCircle = dualshock4.Gamepad.bPrimaryButtons & DS4_GAMEPAD_CIRCLE;
	inputTriangle = dualshock4.Gamepad.bPrimaryButtons & DS4_GAMEPAD_TRIANGLE;
	inputSquare = dualshock4.Gamepad.bPrimaryButtons & DS4_GAMEPAD_SQUARE;
	inputDpadUp = dualshock4.Gamepad.bPrimaryButtons & DS4_GAMEPAD_DPAD_UP;
	inputDpadDown = dualshock4.Gamepad.bPrimaryButtons & DS4_GAMEPAD_DPAD_DOWN;
	inputDpadLeft = dualshock4.Gamepad.bPrimaryButtons & DS4_GAMEPAD_DPAD_LEFT;
	inputDpadRight = dualshock4.Gamepad.bPrimaryButtons & DS4_GAMEPAD_DPAD_RIGHT;

	// Edge cases for DS4 Dpad ordinals
	BOOL boolDpadUpLeft = dualshock4.Gamepad.bPrimaryButtons & DS4_GAMEPAD_DPAD_UPLEFT;
	BOOL boolDpadUpRight = dualshock4.Gamepad.bPrimaryButtons & DS4_GAMEPAD_DPAD_UPRIGHT;
	BOOL boolDpadDownLeft = dualshock4.Gamepad.bPrimaryButtons & DS4_GAMEPAD_DPAD_DOWNLEFT;
	BOOL boolDpadDownRight = dualshock4.Gamepad.bPrimaryButtons & DS4_GAMEPAD_DPAD_DOWNRIGHT;
	//if (boolDpadUpLeft) { inputDpadUp = true; inputDpadLeft = true; };
	//if (boolDpadUpRight) { inputDpadUp = true; inputDpadRight = true; };
	//if (boolDpadDownLeft) { inputDpadDown = true; inputDpadLeft = true; };
	//if (boolDpadDownRight) { inputDpadDown = true; inputDpadRight = true; };

	// Secondary buttons
	inputL1 = dualshock4.Gamepad.bSecondaryButtons & DS4_GAMEPAD_L1;
	inputL2 = dualshock4.Gamepad.bSecondaryButtons & DS4_GAMEPAD_L2;
	inputL3 = dualshock4.Gamepad.bSecondaryButtons & DS4_GAMEPAD_L3;
	inputR1 = dualshock4.Gamepad.bSecondaryButtons & DS4_GAMEPAD_R1;
	inputR2 = dualshock4.Gamepad.bSecondaryButtons & DS4_GAMEPAD_R2;
	inputR3 = dualshock4.Gamepad.bSecondaryButtons & DS4_GAMEPAD_R3;
	inputStart = dualshock4.Gamepad.bSecondaryButtons & DS4_GAMEPAD_OPTIONS;
	inputSelect = dualshock4.Gamepad.bSpecialButtons & DS4_GAMEPAD_TOUCHPAD;

	// Analog Sticks
	inputLeftStickX = dualshock4.Gamepad.bLeftThumbX;
	inputLeftStickY = dualshock4.Gamepad.bLeftThumbY;
	inputRightStickX = dualshock4.Gamepad.bRightThumbX;
	inputRightStickY = dualshock4.Gamepad.bRightThumbY;

	// Pressure Sensitivity
	inputL2Pressure = dualshock4.Gamepad.bL2Pressure;
	inputR2Pressure = dualshock4.Gamepad.bR2Pressure;

	// Fake the other pressure sensitivity
	if (inputCross) { inputCrossPressure = 255; } else { inputCrossPressure = 0; }
	if (inputCircle) { inputCirclePressure = 255; } else { inputCirclePressure = 0; }
	if (inputTriangle) { inputTrianglePressure = 255; } else { inputTrianglePressure = 0; }
	if (inputSquare) { inputSquarePressure = 255; } else { inputSquarePressure = 0; }
	if (inputL1) { inputL1Pressure = 255; } else { inputL1Pressure = 0; }
	if (inputR1) { inputR1Pressure = 255; } else { inputR1Pressure = 0; }
	if (inputDpadUp) { inputDpadUpPressure = 255; } else { inputDpadUpPressure = 0; }
	if (inputDpadLeft) { inputDpadLeftPressure = 255; } else { inputDpadLeftPressure = 0; }
	if (inputDpadDown) { inputDpadDownPressure = 255; } else { inputDpadDownPressure = 0; }
	if (inputDpadRight) { inputDpadRightPressure = 255; } else { inputDpadRightPressure = 0; }

	// Rumble
	dualshock4vibration.bLeftMotor = outputRumble;
	dualshock4vibration.bRightMotor = outputRumble;

	// Lightbar
	dualshock4lightbar.bRed = 0;
	dualshock4lightbar.bGreen = 140;
	dualshock4lightbar.bBlue = 140;

	// Update physical controller
	ds4SetState(isBT, hidHandle, &dualshock4lightbar, &dualshock4vibration);
}
*/
