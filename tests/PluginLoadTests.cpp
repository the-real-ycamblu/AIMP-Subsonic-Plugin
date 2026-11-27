#include <windows.h>

#include <iostream>

int wmain(int argc, wchar_t* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: aimp_subsonic_load_tests.exe <absolute path to plugin DLL>\n";
        return 1;
    }

    HMODULE plugin = LoadLibraryW(argv[1]);
    if (!plugin) {
        const DWORD error = GetLastError();
        std::cerr << "Could not load plugin DLL. Windows error: " << error << '\n';
        return 1;
    }

    const bool hasEntryPoint = GetProcAddress(plugin, "AIMPPluginGetHeader") != nullptr;
    FreeLibrary(plugin);
    if (!hasEntryPoint) {
        std::cerr << "Plugin does not export AIMPPluginGetHeader.\n";
        return 1;
    }

    return 0;
}
