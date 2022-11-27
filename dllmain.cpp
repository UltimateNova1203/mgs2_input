// dllmain.cpp : Defines the entry point for the DLL application.
#include "include/mgs2_input.h"

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved ) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        //hid_init();
        init();
    }
    if (ul_reason_for_call == DLL_PROCESS_DETACH) {
        //hid_exit();
    }

    return TRUE;
}

