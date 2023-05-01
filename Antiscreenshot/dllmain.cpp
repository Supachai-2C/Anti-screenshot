
#include "windows.h"


signed int __stdcall EnumFunc(HWND hWnd, int a2)
{
    DWORD dwProcessId;

    GetWindowThreadProcessId(hWnd, &dwProcessId);
    if (dwProcessId == a2)
        SetWindowDisplayAffinity(hWnd, 17);
    return 1;
}

void StartAddress() {
    while (1)
    {
        DWORD v1 = GetCurrentProcessId();
        EnumWindows((WNDENUMPROC)EnumFunc, v1);
        Sleep(2500u);
    }
}



extern "C" __declspec(dllexport) BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:

        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)StartAddress, NULL, 0, NULL);

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

