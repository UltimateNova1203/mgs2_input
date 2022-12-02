# Input Memory Addresses

| Address  | Type     | Function            | Notes                   |
| -------- | -------- | ------------------- | ----------------------- |
| 00A00A8C | Pointer  | Input Mapping       | Controlled Individually |
| 00EDAC98 | BYTE     | Primary Buttons     | 255=Off, 0=All On       |
| 00EDAC98 | BIT 0    | L1 Button           | 1=Off, 0=On             |
| 00EDAC98 | BIT 1    | R1 Button           | 1=Off, 0=On             |
| 00EDAC98 | BIT 2    | L2 Button           | 1=Off, 0=On             |
| 00EDAC98 | BIT 3    | R2 Button           | 1=Off, 0=On             |
| 00EDAC98 | BIT 4    | Triangle Button     | 1=Off, 0=On             |
| 00EDAC98 | BIT 5    | Circle Button       | 1=Off, 0=On             |
| 00EDAC98 | BIT 6    | Cross Button        | 1=Off, 0=On             |
| 00EDAC98 | BIT 7    | Square Button       | 1=Off, 0=On             |
|          |          |                     |                         |
| 00EDAC99 | BYTE     | Secondary Buttons   | 255=Off, 0=All On       |
| 00EDAC98 | BIT 0    | Select Button       | 1=Off, 0=On             |
| 00EDAC98 | BIT 1    | L3 Button           | 1=Off, 0=On             |
| 00EDAC98 | BIT 2    | R3 Button           | 1=Off, 0=On             |
| 00EDAC98 | BIT 3    | Start Button        | 1=Off, 0=On             |
| 00EDAC98 | BIT 4    | Dpad Up             | 1=Off, 0=On             |
| 00EDAC98 | BIT 5    | Dpad Right          | 1=Off, 0=On             |
| 00EDAC98 | BIT 6    | Dpad Down           | 1=Off, 0=On             |
| 00EDAC98 | BIT 7    | Dpad Left           | 1=Off, 0=On             |
|          |          |                     |                         |
| 00EDAC9C | BYTE     | Right Stick X Axis  | 0-255, Left-Right       |
| 00EDAC9D | BYTE     | Right Stick Y Axis  | 0-255, Up-Down          |
| 00EDAC9E | BYTE     | Left Stick X Axis   | 0-255, Left-Right       |
| 00EDAC9F | BYTE     | Left Stick Y Axis   | 0-255, Up-Down          |
|          |          |                     |                         |
| 00EDACA0 | BYTE     | Dpad Right Pressure | 255=100%, 0=0%          |
| 00EDACA1 | BYTE     | Dpad Down Pressure  | 255=100%, 0=0%          |
| 00EDACA2 | BYTE     | Dpad Up Pressure    | 255=100%, 0=0%          |
| 00EDACA3 | BYTE     | Dpad Left Pressure  | 255=100%, 0=0%          |
| 00EDACA4 | BYTE     | Triangle Pressure   | 255=100%, 0=0%          |
| 00EDACA5 | BYTE     | Circle Pressure     | 255=100%, 0=0%          |
| 00EDACA6 | BYTE     | Cross Pressure      | 255=100%, 0=0%          |
| 00EDACA7 | BYTE     | Square Pressure     | 255=100%, 0=0%          |
| 00EDACA8 | BYTE     | L2 Pressure         | 255=100%, 0=0%          |
| 00EDACA9 | BYTE     | R2 Pressure         | 255=100%, 0=0%          |
| 00EDACAA | BYTE     | L1 Pressure         | 255=100%, 0=0%          |
| 00EDACAB | BYTE     | R1 Pressure         | 255=100%, 0=0%          |
|          |          |                     |                         |
| 00EDAC8D | BYTE     | Rumble              | 255=100%, 0=0%          |
|          |          |                     |                         |
| 00EDAC9A | BYTE     | Extra Functions     | 255=Off, 0=All          |
| 00EDAC9A | BIT 0    | Toggle FPS Mode     | 1=Off, 0=On             |
| 00EDAC9A | BIT 1    | Slow Pressure Ramp  | 1=Off, 0=On             |
| 00EDAC9A | BIT 2    | Weak Pressure (48)  | 1=Off, 0=On             |

# Button Mapping Memory Addresses

## Button Map Addresses

| Address  | Type | Input           |
| -------- | ---- | --------------- |
| 01186A80 | INT  | Cross Button    |
| 01186A84 | INT  | Circle Button   |
| 01186A88 | INT  | Square Button   |
| 01186A8C | INT  | Triangle Button |
| 01186A90 | INT  | L1 Button       |
| 01186A94 | INT  | R1 Button       |
| 01186A98 | INT  | Select Button   |
| 01186A9C | INT  | Start Button    |
| 01186AA0 | INT  | L3 Button       |
| 01186AA4 | INT  | R3 Button       |
| 01186AA8 | INT  | L2 Button       |
| 01186AAC | INT  | R2 Button       |

## FPS Button Map Addresses

| Address  | Type | Input           |
| -------- | ---- | --------------- |
| 01186B40 | INT  | Cross Button    |
| 01186B44 | INT  | Circle Button   |
| 01186B48 | INT  | Square Button   |
| 01186B4C | INT  | Triangle Button |
| 01186B50 | INT  | L1 Button       |
| 01186B54 | INT  | R1 Button       |
| 01186B58 | INT  | Select Button   |
| 01186B5C | INT  | Start Button    |
| 01186B60 | INT  | L3 Button       |
| 01186B64 | INT  | R3 Button       |
| 01186B68 | INT  | L2 Button       |
| 01186B6C | INT  | R2 Button       |


## Button Map Layout

| Offset | Bit   | Input              | Notes       |
| ------ | ----- | ------------------ | ----------- |
| +0x0   | Bit 0 | L1 Button          | 0=Off, 1=On |
| +0x0   | Bit 1 | R1 Button          | 0=Off, 1=On |
| +0x0   | Bit 2 | L2 Button          | 0=Off, 1=On |
| +0x0   | Bit 3 | R2 Button          | 0=Off, 1=On |
| +0x0   | Bit 4 | Triangle Button    | 0=Off, 1=On |
| +0x0   | Bit 5 | Circle Button      | 0=Off, 1=On |
| +0x0   | Bit 6 | Cross Button       | 0=Off, 1=On |
| +0x0   | Bit 7 | Square Button      | 0=Off, 1=On |
|        |       |                    |             |
| +0x1   | Bit 0 | Select Button      | 0=Off, 1=On |
| +0x1   | Bit 1 | L3 Button          | 0=Off, 1=On |
| +0x1   | Bit 2 | R3 Button          | 0=Off, 1=On |
| +0x1   | Bit 3 | Start Button       | 0=Off, 1=On |
| +0x1   | Bit 4 | Dpad Up            | 0=Off, 1=On |
| +0x1   | Bit 5 | Dpad Right         | 0=Off, 1=On |
| +0x1   | Bit 6 | Dpad Down          | 0=Off, 1=On |
| +0x1   | Bit 7 | Dpad Left          | 0=Off, 1=On |
|        |       |                    |             |
| +0x2   | Bit 0 | Toggle FPS Mode    | 0=Off, 1=On |
| +0x2   | Bit 1 | Slow Pressure Ramp | 0=Off, 1=On |
| +0x2   | Bit 2 | Weak Pressure (48) | 0=Off, 1=On |
| +0x2   | Bit 3 | EX3                | Unknown     |
| +0x2   | Bit 4 | EX4                | Unknown     |
| +0x2   | Bit 5 | EX5                | Unknown     |
| +0x2   | Bit 6 | EX6                | Unknown     |
| +0x2   | Bit 7 | EX7                | Unknown     |
|        |       |                    |             |
| +0x3   | Bit 0 | Unknown            | Unknown     |
| +0x3   | Bit 1 | Unknown            | Unknown     |
| +0x3   | Bit 2 | Unknown            | Unknown     |
| +0x3   | Bit 3 | Unknown            | Unknown     |
| +0x3   | Bit 4 | Unknown            | Unknown     |
| +0x3   | Bit 5 | Unknown            | Unknown     |
| +0x3   | Bit 6 | Unknown            | Unknown     |
| +0x3   | Bit 7 | Unknown            | Unknown     |
