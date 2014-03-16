#ifndef ZMEM_H
#define ZMEM_H
#include <Windows.h>

/* http://illmatics.com/Understanding_the_LFH.pdf */
/* http://msdn.microsoft.com/en-us/library/windows/desktop/aa366781(v=vs.85).aspx */

__declspec(dllexport) void zfree(void *memblock);
__declspec(dllexport) HGLOBAL WINAPI zGlobalFree(HGLOBAL hMem);
__declspec(dllexport) HLOCAL WINAPI zLocalFree(HLOCAL hMem);
__declspec(dllexport) BOOL WINAPI zHeapFree(HANDLE hHeap,DWORD dwFlags,LPVOID lpMem);
//__declspec(dllexport) BOOL WINAPI zVirtualFree(LPVOID lpAddress,SIZE_T dwSize,DWORD dwFreeType);
//__declspec(dllexport) BOOL WINAPI zVirtualFreeEx(HANDLE hProcess,LPVOID lpAddress,SIZE_T dwSize,DWORD dwFreeType);
#endif