#include <windows.h>

#include "AimpPlugin.h"

HMODULE g_moduleHandle = nullptr;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID) {
    if (reason == DLL_PROCESS_ATTACH) {
        g_moduleHandle = hModule;
    }
    return TRUE;
}

// AIMP looks up the undecorated name, while MSVC decorates stdcall on x86.
#if defined(_MSC_VER) && defined(_M_IX86)
#pragma comment(linker, "/EXPORT:AIMPPluginGetHeader=_AIMPPluginGetHeader@4")
extern "C"
#else
extern "C" __declspec(dllexport)
#endif
HRESULT WINAPI AIMPPluginGetHeader(IAIMPPlugin** Header) {
    if (!Header) {
        return E_POINTER;
    }
    *Header = new AimpSubsonicPlugin();
    return *Header ? S_OK : E_OUTOFMEMORY;
}
