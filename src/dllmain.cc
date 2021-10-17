// ------------------------------------------------------------------
// file:   dllmain.cc
// desc:   example file for creating executeable's for Windows 10 Pro.
//         with the AsmJit by:
//         available under:
//
// autor:  Jens Kallup - <kallup.jens@web.de>
//         kallup.net * non-profit
// date:   2021-10-12
//
// policy: only for education usage !!! - no commercial use allowed.
//         free to distribute if copyright notice is intact.
// ------------------------------------------------------------------

# include <windows.h>
# include <Process.h>

extern "C" BOOL WINAPI
DllMain(
    HINSTANCE hinstDLL,  // handle to DLL module
    DWORD fdwReason,     // reason for calling function
    LPVOID lpReserved )  // reserved
{
    // Perform actions based on the reason for calling.
    switch( fdwReason ) 
    { 
        case DLL_PROCESS_ATTACH:
         // Initialize once for each new process.
         // Return FALSE to fail DLL load.
            break;

        case DLL_THREAD_ATTACH:
         // Do thread-specific initialization.
            break;

        case DLL_THREAD_DETACH:
         // Do thread-specific cleanup.
            break;

        case DLL_PROCESS_DETACH:
         // Perform any necessary cleanup.
            break;
    }
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}
