// dllmain.cpp : Defines the entry point for the DLL application.
#include "framework.h"

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved ) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        init();
    }

    if (ul_reason_for_call == DLL_PROCESS_DETACH) {
        exit_ds4();
    }

    return TRUE;
}

