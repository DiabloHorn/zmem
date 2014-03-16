from winappdbg import Debug, EventHandler
from winappdbg.win32 import *
import sys

class MyEventHandler(EventHandler):
    #case matters
    apiHooks = {'kernel32.dll':[('HeapFree',(HANDLE, DWORD, LPVOID)),
                                ('LocalFree',(HLOCAL,)),
                                ('GlobalFree',(HGLOBAL,))]
                }
    
    def pre_HeapFree(self, event, ra, hHeap, dwFlags, lpMem):
        print "entered hooked heapfree"
        if lpMem:
            print "%s" % event.get_process().peek(lpMem,100)

    def pre_LocalFree(self, event, ra, hMem):
        print "entered hooked localfree"
        if hMem:
            print "%s" % event.get_process().peek(hMem,100)        

    def pre_GlobalFree(self, event, ra, hMem):
        print "entered hooked globalfree"
        if hMem:
            print "%s" % event.get_process().peek(hMem,100)
        
if __name__ == "__main__":
    with Debug( MyEventHandler(), bKillOnExit = True ) as debug:
        print sys.argv[1:]
        debug.execv( sys.argv[1:])        
        debug.loop()