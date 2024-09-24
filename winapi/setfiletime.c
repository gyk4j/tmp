#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void ErrorExit(LPCTSTR lpszFunction);

int main(int argc, char *argv[])
{
    BOOL err;
    
    SYSTEMTIME lt, st;
    
    //GetSystemTime(&st);
    //GetLocalTime(&lt);
    
    st.wYear = 2001;
    st.wMonth = 9;
    st.wDay = 11;
    st.wHour = 12;
    st.wMinute = 14;
    st.wSecond = 53;
    st.wMilliseconds = 0;
    
    TIME_ZONE_INFORMATION *lpTimeZoneInformation = NULL;
    SYSTEMTIME *lpLocalTime = &lt;
    LPSYSTEMTIME lpUniversalTime = &st;
    
    err = SystemTimeToTzSpecificLocalTime(
        NULL,
        &st,
        &lt);
    
    if (err == 0){
        ErrorExit(TEXT("SystemTimeToTzSpecificLocalTime"));
    }
    
    printf("system time: %04d-%02d-%02d %02d:%02d:%02d.%03dZ\n", 
        st.wYear, st.wMonth, st.wDay,
        st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
        
    printf(" local time: %04d-%02d-%02d %02d:%02d:%02d.%03d \n", 
        lt.wYear, lt.wMonth, lt.wDay,
        lt.wHour, lt.wMinute, lt.wSecond, lt.wMilliseconds);
    
    FILETIME ft;
    SYSTEMTIME *lpSystemTime = &st;
    LPFILETIME lpFileTime = &ft;
    
    err = SystemTimeToFileTime(lpSystemTime, lpFileTime);
    if (err == 0){
        ErrorExit(TEXT("SystemTimeToFileTime"));
    }

    HANDLE hFile = CreateFile(
        "test.txt",                
        GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    
    if (hFile == INVALID_HANDLE_VALUE) 
    { 
        ErrorExit(TEXT("CreateFile"));        
    }
        
    FILETIME *lpCreationTime = lpFileTime;
    FILETIME *lpLastAccessTime = lpFileTime;
    FILETIME *lpLastWriteTime = lpFileTime;
    
    err = SetFileTime(
        hFile,
        lpCreationTime,
        lpLastAccessTime,
        lpLastWriteTime
    );
        
    //printf(" The local time is: %02d:%02d\n", lt.wHour, lt.wMinute);
    
    system("PAUSE");	
    return 0;
}

void ErrorExit(LPCTSTR lpszFunction) 
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

    // Display the error message and exit the process

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
        (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
    /*
    StringCchPrintf((LPTSTR)lpDisplayBuf, 
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("%s failed with error %d: %s"), 
        lpszFunction, dw, lpMsgBuf);
    */
    sprintf(lpDisplayBuf, TEXT("%s failed with error %d: %s"), lpszFunction, dw, lpMsgBuf);
    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK); 

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
    ExitProcess(dw); 
}
