#include "zmem.h"

/* not intended as a full on test case */
int main(int argc, char *argv[]){
	void *test, *dlltest;
	HGLOBAL hgtest, hgdlltest;
	HLOCAL hltest, hldlltest;
	HANDLE heapcreate, dllheapcreatetest;
	LPVOID hptest, hpdlltest;
	//LPVOID hvtest;
	
	/* just to see if the code even works */
	test = malloc(100);
	memset(test,'a',100);
	zfree(test);

	hgtest = GlobalAlloc(GMEM_FIXED,100);
	memset(hgtest,'b',100);
	zGlobalFree(hgtest);

	hltest = LocalAlloc(LMEM_FIXED,100);
	memset(hltest,'c',100);
	zLocalFree(hltest);

	heapcreate = HeapCreate(0,100,100);
	hptest = HeapAlloc(heapcreate,HEAP_ZERO_MEMORY,100);
	memset(hptest,'d',100);
	zHeapFree(heapcreate,0,hptest);
	HeapDestroy(heapcreate);


	/* have some code that can be hooked */

	dlltest = malloc(100);
	memset(dlltest,'e',100);
	free(dlltest);

	hgdlltest = GlobalAlloc(GMEM_FIXED,100);
	memset(hgdlltest,'f',100);
	GlobalFree(hgdlltest);

	hldlltest = LocalAlloc(LMEM_FIXED,100);
	memset(hldlltest,'g',100);
	LocalFree(hldlltest);

	dllheapcreatetest = HeapCreate(0,100,100);
	hpdlltest = HeapAlloc(dllheapcreatetest,HEAP_ZERO_MEMORY,100);
	memset(hpdlltest,'h',100);
	HeapFree(dllheapcreatetest,0,hpdlltest);
	HeapDestroy(dllheapcreatetest);

	/* dlib has the same code, so we don't try that out yet*/

	/* yet to implement */
	/*
	hvtest = VirtualAlloc(NULL,100,MEM_COMMIT,PAGE_READWRITE);
	memset(hvtest,'a',100);
	zVirtualFree(hvtest,100,MEM_RELEASE);
	return 0;
	*/
}

/*
	Thanks TheColonial for reminding me of pointer arithmethic and re-educating me on it.
	Old unused code, left here in case someone prefers to do it this way.
	This code also wrapped the allocater to prepend the size of the allocated memory block.
*/

/*
void *zmalloc( size_t size ){
	size_t newsize = (sizeof(size_t) + size);
	size_t *newmalloc = 0;
	void *originalmalloc = NULL;

	originalmalloc = malloc(newsize);
	printf("size %i\n",_msize(originalmalloc));
	if(originalmalloc == NULL){
		return NULL;
	}
	
	(*(size_t *)originalmalloc) = size;
	newmalloc = (size_t *)originalmalloc;

	return (void *)(newmalloc + 1);
}

void zfree(void *memblock){
	size_t *newmemblock = NULL;
	size_t size = 0;

	
	newmemblock = ((size_t *)memblock)-1;
	memcpy_s(&size,sizeof(size_t),newmemblock,sizeof(size_t));
	size += sizeof(size_t);
	SecureZeroMemory((void *)newmemblock,size);
	free((void *)newmemblock);
}
*/