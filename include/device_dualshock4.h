#pragma once

#include <hidapi.h>

extern hid_device* hidHandle;
extern hid_device_info* hidDeviceInfo;

extern void exit_ds4();
extern int update_ds4();