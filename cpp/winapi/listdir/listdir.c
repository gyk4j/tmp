#include <windows.h>
#include <tchar.h> 
#include <stdio.h>

void DisplayErrorBox(LPTSTR lpszFunction);
DWORD Walk(const TCHAR* szDir);

int _tmain(int argc, TCHAR *argv[])
{
    
    TCHAR szDir[MAX_PATH];
    size_t length_of_arg;
    
    // If the directory is not specified as a command-line argument,
    // print usage.
    
    if(argc != 2)
    {
        _tprintf(TEXT("\nUsage: %s <directory name>\n"), argv[0]);
        return (-1);
    }
    
    // Check that the input path plus 3 is not longer than MAX_PATH.
    // Three characters are for the "\*" plus NULL appended below.
    length_of_arg = _tcslen(argv[1]); //, MAX_PATH);
    
    if (length_of_arg > (MAX_PATH - 3))
    {
        _tprintf(TEXT("\nDirectory path is too long.\n"));
        return (-1);
    }
    
    _tprintf(TEXT("\nTarget directory is %s\n\n"), argv[1]);
    
    // Prepare string for use with FindFile functions.  First, copy the
    // string to a buffer, then append '\*' to the directory name.
    
    _tcsncpy(szDir, argv[1], MAX_PATH);
    if (szDir[_tcslen(szDir)-sizeof(TCHAR)] != '\\')
        _tcsncat(szDir, TEXT("\\"), MAX_PATH);
    _tcsncat(szDir, TEXT("*"), MAX_PATH);
    
    return Walk(szDir);
}

DWORD Walk(const TCHAR* szDir)
{
    WIN32_FIND_DATA ffd;
    LARGE_INTEGER filesize;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    DWORD dwError=0;
    
    // Find the first file in the directory.
    
    hFind = FindFirstFile(szDir, &ffd);
    
    if (INVALID_HANDLE_VALUE == hFind) 
    {
        DisplayErrorBox(TEXT("FindFirstFile"));
        return dwError;
    } 
    
    // List all the files in the directory with some info about them.
    
    do
    {
        if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            _tprintf(TEXT("\t[%s]\n"), ffd.cFileName);
            
            if (_tcscmp(ffd.cFileName, _TEXT(".")) != 0 &&
                _tcscmp(ffd.cFileName, _TEXT("..")) != 0) {
                
                TCHAR szSubDir[MAX_PATH];
                memset(szSubDir, 0, MAX_PATH);
                _tcsncpy(szSubDir, szDir, _tcslen(szDir) - sizeof(TCHAR));
                _tcsncat(szSubDir, ffd.cFileName, MAX_PATH);
                _tprintf(TEXT("%s\n"), szSubDir);
                if (szDir[_tcslen(szSubDir)-sizeof(TCHAR)] != '\\')
                    _tcsncat(szSubDir, TEXT("\\"), MAX_PATH);
                _tcsncat(szSubDir, TEXT("*"), MAX_PATH);       
                
                Walk(szSubDir);
            }
        }
        else
        {
            filesize.LowPart = ffd.nFileSizeLow;
            filesize.HighPart = ffd.nFileSizeHigh;
            _tprintf(TEXT("\t%-24s %10ld bytes\n"), ffd.cFileName, filesize.QuadPart);
        }
    }
    while (FindNextFile(hFind, &ffd) != 0);
    
    dwError = GetLastError();
    if (dwError != ERROR_NO_MORE_FILES) 
    {
        DisplayErrorBox(TEXT("FindFirstFile"));
    }
    
    FindClose(hFind);
    return dwError;
}


void DisplayErrorBox(LPTSTR lpszFunction) 
{ 
    // Retrieve the system error message for the last-error code
    
    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError(); 
    
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );
    
    // Display the error message and clean up
    
    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
        (lstrlen((LPCTSTR)lpMsgBuf)+lstrlen((LPCTSTR)lpszFunction)+40)*sizeof(TCHAR));
    _sntprintf((LPTSTR)lpDisplayBuf, 
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("%s failed with error %d: %s"), 
        lpszFunction, dw, lpMsgBuf); 
    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK); 
    
    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
}
