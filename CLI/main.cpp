Include:
#include <NoMercy.hpp>

Additional flags:
#pragma comment(linker, "/ALIGN:0x10000")

Libs:
// #ifdef _DEBUG
//     #ifdef _WIN64
//         #pragma comment( lib, "NoMercy_x64_d.lib" )
//     #else
//         #pragma comment( lib, "NoMercy_x86_d.lib" )
//     #endif
// #else
    #ifdef _WIN64
        #pragma comment( lib, "NoMercy_x64.lib" )
    #else
        #pragma comment( lib, "NoMercy_x86.lib" )
    #endif
// #endif

Initilization:
void __stdcall OnNoMercyMessage(int Code, const char* c_szMessage, const void* lpParam)
{
    // ...
}

if (!NM_Initialize(1, 1, &OnNoMercyMessage))
    return EXIT_FAILURE;

Finalization:
NM_Finalize();
