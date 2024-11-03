#include <windows.h>

#ifndef CWINTHREAD_H
#define CWINTHREAD_H

#define AFX_CDECL __cdecl

typedef UINT (AFX_CDECL *AFX_THREADPROC)(LPVOID);

class CWinThread
{
	public:		
		HANDLE m_hThread;		// this thread's HANDLE
		DWORD m_nThreadID;      // this thread's ID
};

CWinThread* AfxBeginThread(
	AFX_THREADPROC pfnThreadProc,
    LPVOID pParam,
    int nPriority = THREAD_PRIORITY_NORMAL,
    UINT nStackSize = 0,
    DWORD dwCreateFlags = 0,
    LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL
);

#endif
