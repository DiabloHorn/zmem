#include "zmem.h"

int main(int argc, char *argv[]){
	void *test;
	HGLOBAL hgtest;
	HLOCAL hltest;
	HANDLE heapcreate;
	LPVOID hptest;
	//LPVOID hvtest;

	test = malloc(100);
	memset(test,'a',100);
	zfree(test);

	hgtest = GlobalAlloc(GMEM_FIXED,100);
	memset(hgtest,'a',100);
	zGlobalFree(hgtest);

	hltest = LocalAlloc(LMEM_FIXED,100);
	memset(hltest,'a',100);
	zLocalFree(hltest);

	heapcreate = HeapCreate(0,100,100);
	hptest = HeapAlloc(heapcreate,HEAP_ZERO_MEMORY,100);
	memset(hptest,'a',100);
	zHeapFree(heapcreate,0,hptest);
	HeapDestroy(heapcreate);
	/* yet to implement 
	hvtest = VirtualAlloc(NULL,100,MEM_COMMIT,PAGE_READWRITE);
	memset(hvtest,'a',100);
	zVirtualFree(hvtest,100,MEM_RELEASE);
	return 0;
	*/
}