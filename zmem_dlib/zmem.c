/*
	DiabloHorn http://diablohorn.wordpress.com
*/
#include "zmem.h"
#include <malloc.h>

__declspec(dllexport) void zfree(void *memblock){
	size_t blocksize = _msize(memblock);

	if(blocksize != -1){
		SecureZeroMemory(memblock,blocksize);
	}
	free(memblock);
}

__declspec(dllexport) HGLOBAL WINAPI zGlobalFree(HGLOBAL hMem){
	size_t blocksize = GlobalSize(hMem); 
	LPVOID lock_pointer = NULL;

	if(blocksize != 0){
		lock_pointer = GlobalLock(hMem); //just in case it was allocated with the MOVEABLE flag
		if(lock_pointer == NULL){
			return hMem;
		}	
		SecureZeroMemory(lock_pointer,blocksize);
		GlobalUnlock(lock_pointer);
	}
	return GlobalFree(hMem);
}

__declspec(dllexport) HLOCAL WINAPI zLocalFree(HLOCAL hMem){
	size_t blocksize = LocalSize(hMem); 
	LPVOID lock_pointer = NULL;

	if(blocksize != 0){
		lock_pointer = LocalLock(hMem); //just in case it was allocated with the MOVEABLE flag
		if(lock_pointer == NULL){
			return hMem;
		}
		SecureZeroMemory(lock_pointer,blocksize);
		LocalUnlock(hMem);
	}
	return LocalFree(hMem);
}

__declspec(dllexport) BOOL WINAPI zHeapFree(HANDLE hHeap,DWORD dwFlags,LPVOID lpMem){	
	size_t blocksize = HeapSize(hHeap,dwFlags,lpMem);
	
	if(blocksize != -1){
		SecureZeroMemory(lpMem,blocksize);
	}
	return HeapFree(hHeap,dwFlags,lpMem);
}

/*
__declspec(dllexport) BOOL WINAPI zVirtualFree(LPVOID lpAddress,SIZE_T dwSize,DWORD dwFreeType){
	//todo
	return VirtualFree(lpAddress,dwSize,dwFreeType);
}

__declspec(dllexport) BOOL WINAPI zVirtualFreeEx(HANDLE hProcess,LPVOID lpAddress,SIZE_T dwSize,DWORD dwFreeType){
	//todo
	return VirtualFreeEx(hProcess,lpAddress,dwSize,dwFreeType);
}
*/

