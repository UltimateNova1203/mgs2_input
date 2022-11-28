# MGS2 Input PC Fix
 
* Restores pressure sensitivity for the L2/R2 buttons.
* Clamps L2/R2 range for smoother actuation.
* Clamps Left/Right sticks when fully extended, intended to fix diagonal walking/crawling speed issues
* Sets DPAD to 20% pressure, to force walking mode (similar to MGS3 on PS2/PS3)
* Slightly faster weapon disengage speed via the L3 button.
* Removes DInput and Keyboard/Mouse inputs, only Xinput is available at this time.

# Addresses

## Primary/Secondary Buttons

Both Primary and Secondary buttons are at BYTE value 255 when not actuated. When pressing a button, the corresponding BIT is brought low (i.e. 0), which is accomplished via a BITWISE operation. This tells MGS2 that the button is being pressed.

MGS2 also checks for pressure value, which is represented via a BYTE (i.e. values of 0-255). This comes into play when using the DPAD/R1/L2/R2/Square buttons, which have additional controls via pressure. If L2 is being pressed while in First Person View mode, the view will slide to the left. The distance is controlled via L2's pressure value, a higher value being more distance slid.

## "Triggers"

L2/R2 pressure values effectively cap at 180, afterwards FPS mode slide will no longer increase. To make actuation more "smooth", multiplying the value of pressure by 0.7 will make it so full trigger depression will go to full FPS slide, without wasted travel.

## Sticks

Both Left/Right sticks have a separate BYTE for the X/Y axis. Centered is considered 127, Left/Up 0, and Right/Down 255. Due to the nature of how MGS2 was designed, it expects a square mapped stick, which was the case for the PS1/PS2 era controllers. Issues crop up when using a circular mapped stick, starting with the Xbox/360 era with XInput. Clamping the first 0-40 to 0, and last 215-255 to 255, will resolve issues with diagonals not registered as full tilt.

## Rumble

Simple BYTE actuates rumble, 0 being 0% rumble, and 255 being 100% rumble. There is only one address at play, so they are duplicated between both motors on the controller.

## Pressure Check

Only appears to be used when letting off the square button to lower weapon without firing. If set to 253, game will consider you to be lowering your weapon, and can let off the square button fully. If left to 255, letting off square will fire the weapon.

## Memory Address

| Address  | Type | Function            | Notes |
| -------- | ---- | ------------------- | ----- |
| 00EDAC98 | BYTE | Primary Buttons     | 255=Off, 0=All On |
| 00EDAC98 | BIT0 | L1 Button           | 1=Off, 0=On       |
| 00EDAC98 | BIT1 | R1 Button           | 1=Off, 0=On       |
| 00EDAC98 | BIT2 | L2 Button           | 1=Off, 0=On       |
| 00EDAC98 | BIT3 | R2 Button           | 1=Off, 0=On       |
| 00EDAC98 | BIT4 | Triangle Button     | 1=Off, 0=On       |
| 00EDAC98 | BIT5 | Circle Button       | 1=Off, 0=On       |
| 00EDAC98 | BIT6 | Cross Button        | 1=Off, 0=On       |
| 00EDAC98 | BIT7 | Square Button       | 1=Off, 0=On       |
|          |      |                     |                   |
| 00EDAC99 | BYTE | Secondary Buttons   | 255=Off, 0=All On |
| 00EDAC98 | BIT0 | Select Button       | 1=Off, 0=On       |
| 00EDAC98 | BIT1 | L3 Button           | 1=Off, 0=On       |
| 00EDAC98 | BIT2 | R3 Button           | 1=Off, 0=On       |
| 00EDAC98 | BIT3 | Start Button        | 1=Off, 0=On       |
| 00EDAC98 | BIT4 | Dpad Up             | 1=Off, 0=On       |
| 00EDAC98 | BIT5 | Dpad Right          | 1=Off, 0=On       |
| 00EDAC98 | BIT6 | Dpad Down           | 1=Off, 0=On       |
| 00EDAC98 | BIT7 | Dpad Left           | 1=Off, 0=On       |
|          |      |                     |                   |
| 00EDAC9C | BYTE | Right Stick X Axis  | 0-255, Left-Right |
| 00EDAC9D | BYTE | Right Stick Y Axis  | 0-255, Up-Down    |
| 00EDAC9E | BYTE | Left Stick X Axis   | 0-255, Left-Right |
| 00EDAC9F | BYTE | Left Stick Y Axis   | 0-255, Up-Down    |
|          |      |                     |                   |
| 00EDACA0 | BYTE | Dpad Right Pressure | 255=100%, 0=0%    |
| 00EDACA1 | BYTE | Dpad Down Pressure  | 255=100%, 0=0%    |
| 00EDACA2 | BYTE | Dpad Up Pressure    | 255=100%, 0=0%    |
| 00EDACA3 | BYTE | Dpad Left Pressure  | 255=100%, 0=0%    |
| 00EDACA4 | BYTE | Triangle Pressure   | 255=100%, 0=0%    |
| 00EDACA5 | BYTE | Circle Pressure     | 255=100%, 0=0%    |
| 00EDACA6 | BYTE | Cross Pressure      | 255=100%, 0=0%    |
| 00EDACA7 | BYTE | Square Pressure     | 255=100%, 0=0%    |
| 00EDACA8 | BYTE | L2 Pressure         | 255=100%, 0=0%    |
| 00EDACA9 | BYTE | R2 Pressure         | 255=100%, 0=0%    |
| 00EDACAA | BYTE | L1 Pressure         | 255=100%, 0=0%    |
| 00EDACAB | BYTE | R1 Pressure         | 255=100%, 0=0%    |
|          |      |                     |                   |
| 00EDAC8D | BYTE | Rumble              | 255=100%, 0=0%    |
|          |      |                     |                   |
| 00EDAC9A | BYTE | Pressure Check      | 255=Off, 253=Low  |
