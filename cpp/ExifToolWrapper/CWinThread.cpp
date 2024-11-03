#include <cstdio>
#include <iostream>
#include "CWinThread.h"

using namespace std;

CWinThread* AfxBeginThread(
	AFX_THREADPROC pfnThreadProc,
    LPVOID pParam,
    int nPriority,
    UINT nStackSize,
    DWORD dwCreateFlags,
    LPSECURITY_ATTRIBUTES lpSecurityAttrs
)
{
	CWinThread* t = new CWinThread();
	t->m_hThread = CreateThread( 
		lpSecurityAttrs, 						// default security attributes
		nStackSize,    							// default stack size
		(LPTHREAD_START_ROUTINE) pfnThreadProc, 
		pParam,		 							// thread function arguments
		dwCreateFlags,  						// default creation flags
		&(t->m_nThreadID)); 					// receive thread identifier
		
	if( t->m_hThread == NULL )
    {
        printf("CreateThread error: %d\n", GetLastError());
        ExitProcess(1);
    }
	
	return t;
}
