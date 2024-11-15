/*
---
name: ExifToolWrapper.cpp
description: C++ Wrapper for Phil Harvey's excellent ExifTool
url: https://github.com/gyk4j/tmp/raw/main/cpp/FileMeta/ExifToolWrapper.cpp
version: 1.0
keywords: CodeBit
dateModified: 2024-11-14
license: http://unlicense.org
about: https://exiftool.org/
# Metadata in MicroYaml format. See http://filemeta.org/CodeBit.html
...
*/

/*
Unlicense: http://unlicense.org

This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or distribute
this software, either in source code form or as a compiled binary, for any
purpose, commercial or non-commercial, and by any means.

In jurisdictions that recognize copyright laws, the author or authors of this
software dedicate any and all copyright interest in the software to the
public domain. We make this dedication for the benefit of the public at large
and to the detriment of our heirs and successors. We intend this dedication
to be an overt act of relinquishment in perpetuity of all present and future
rights to this software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>
*/
#define EXIF_TRACE

#include <tchar.h>
#include <ctype.h>
#include <iostream>
#include <windows.h>
#include "ExifToolWrapper.h"

namespace ExifToolWrapper
{
    const TCHAR* ExifTool::c_exeName = "exiftool.exe";
    const TCHAR* ExifTool::c_arguments = "-stay_open 1 -@ - -common_args -charset UTF8 -G1 -args";
    const TCHAR* ExifTool::c_exitCommand = "-stay_open\n0\n-execute\n";
    const int ExifTool::c_timeout = 30000;    // in milliseconds
    const int ExifTool::c_exitTimeout = 15000;
    
    //Encoding ExifTool::s_Utf8NoBOM = new UTF8Encoding(false);
    
    ExifTool::ExifTool()
    {
        std::cout << "ExifTool()" << std::endl;
        
        SECURITY_ATTRIBUTES saAttr;
        
        // Set the bInheritHandle flag so pipe handles are inherited.
        saAttr.nLength = sizeof( SECURITY_ATTRIBUTES );   
        saAttr.bInheritHandle = TRUE;
        saAttr.lpSecurityDescriptor = NULL;   
        
        HANDLE hInRd, hInWr;
        
        // Create a pipe for the child process's STDIN.
        if ( !CreatePipe( &hInRd, &hInWr, &saAttr, 0 ) )
            throw CREATE_PIPE_ERROR;
            
        // Ensure the write handle to the pipe for STDIN is not inherited.
        if ( !SetHandleInformation(hInWr, HANDLE_FLAG_INHERIT, 0) )
            throw SET_HANDLE_INFORMATION_ERROR;
        
        HANDLE hOutRd, hOutWr;
        
        // Create a pipe for the child process's STDOUT.        
        if ( !CreatePipe( &hOutRd, &hOutWr, &saAttr, 0 ) )
            throw CREATE_PIPE_ERROR;
        
        // Ensure the read handle to the pipe for STDOUT is not inherited.
        if ( !SetHandleInformation(hOutRd, HANDLE_FLAG_INHERIT, 0) )
            throw SET_HANDLE_INFORMATION_ERROR;
        
        // void CreateChildProcess()
        // Create a child process that uses the previously created pipes for STDIN and STDOUT.
        
        TCHAR szCmdline[BUFSIZE];
        ZeroMemory( szCmdline, BUFSIZE );
        _tcscpy( szCmdline, c_exeName );
        _tcscat( szCmdline, TEXT(" ") );
        _tcscat( szCmdline, c_arguments );
        
        PROCESS_INFORMATION piProcInfo; 
        STARTUPINFO siStartInfo;
        BOOL bSuccess = FALSE;
        
        // Set up members of the PROCESS_INFORMATION structure.
        
        ZeroMemory( &piProcInfo, sizeof(PROCESS_INFORMATION) );
        
        // Set up members of the STARTUPINFO structure. 
        // This structure specifies the STDIN and STDOUT handles for redirection.

        ZeroMemory( &siStartInfo, sizeof(STARTUPINFO) );  
        siStartInfo.cb = sizeof(STARTUPINFO);
        siStartInfo.hStdInput = hInRd; 
        siStartInfo.hStdOutput = hOutWr;
        siStartInfo.hStdError = hOutWr;
        siStartInfo.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
        siStartInfo.wShowWindow = SW_HIDE;
        
        // Create the child process.
        
        bSuccess = CreateProcess(
            NULL,           // filename 
            szCmdline,      // command line 
            NULL,           // process security attribute 
            NULL,           // primary thread security attributes 
            TRUE,           // handles are inherited 
            0,              // creation flags 
            NULL,           // use parent's environment
            NULL,           // use parent's current directory 
            &siStartInfo,   // STARTUPINFO pointer
            &piProcInfo);   // receives PROCESS_INFORMATION
            
    	if ( ! bSuccess )
    		throw CREATE_PROCESS_ERROR;
    	else
    	{
            // Close handles to the child process and its primary thread.
            // Some applications might keep these handles to monitor the status
            // of the child process, for example.
            // CloseHandle( piProcInfo.hProcess );   
            // CloseHandle( piProcInfo.hThread );
            
            // Close handles to the stdin and stdout pipes no longer needed by the child process.
            // If they are not explicitly closed, there is no way to recognize that the child process has ended.
            
            CloseHandle( hOutWr );
            CloseHandle( hInRd );
    
            m_in = hInWr;
            m_out = hOutRd;
            
            // CreateProcess does not return a Process object like in .NET.
            // Closest equivalence is the PROCESS_INFORMATION struct.
            ZeroMemory( &m_exifTool, sizeof(PROCESS_INFORMATION) );
            memcpy( &m_exifTool, &piProcInfo, sizeof(PROCESS_INFORMATION) );
        }
    }
    
    void ExifTool::GetProperties(const TCHAR *filename, std::vector< KeyValuePair<std::string, std::string> > propsRead)
    {
        DWORD dwRead, dwWritten;
        BOOL bSuccess = FALSE;
        TCHAR chBuf[BUFSIZE];
        HANDLE hParentStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        
        dwRead = _tcslen(filename) * sizeof(TCHAR);
        bSuccess = WriteFile(m_in, filename, dwRead, &dwWritten, NULL);
        if ( ! bSuccess ) return;
        
        FlushFileBuffers(m_in);
        
        dwRead = _tcslen("\n-execute\n") * sizeof(TCHAR);
        bSuccess = WriteFile(m_in, "\n-execute\n", dwRead, &dwWritten, NULL);
        if ( ! bSuccess ) return;
        
        FlushFileBuffers(m_in);
        
        // Flush???
            
#ifdef EXIF_TRACE
        OutputDebugString(_T(filename));
        OutputDebugString(_T("-execute"));
#endif
        // Close the pipe handle so the child process stops reading.
        
        if ( ! CloseHandle(m_in) )
            throw CLOSE_HANDLE_ERROR;

        TCHAR line[BUFSIZE];
        for (; ; )
        {
            ZeroMemory( line,  BUFSIZE );
            bSuccess = ReadFile( m_out, line, BUFSIZE, &dwRead, NULL);
            if( ! bSuccess || dwRead == 0 ) break;
            
            // Echo to parent stdout
            // bSuccess = WriteFile(hParentStdOut, line, dwRead, &dwWritten, NULL);
            // if (! bSuccess ) break;
#ifdef EXIF_TRACE
            OutputDebugString(_T(line));
#endif
            if (_tcsstr(line, "{ready") == &line[0]) break;
            if (line[0] == '-')
            {
                int eq = _tcscspn(line, "=");
                if (eq > 1)
                {
                    ZeroMemory( chBuf,  BUFSIZE );
                    _tcsncpy( chBuf, &line[1], eq - 1 );
                    std::string *key = new std::string(chBuf);
                    
                    ZeroMemory( chBuf,  BUFSIZE );
                    _tcscpy( chBuf, &line[eq + 1] );
                    int i;
                    
                    // Trim
                    for(i = BUFSIZE-1; i >= 0; i--){
                        int isSpace = isspace(chBuf[i]);
                        if (chBuf[i] != 0 && !isSpace) {
                            break;
                        } else if (isSpace) {
                            chBuf[i] = 0;
                        }
                    }
                    std::string *value = new std::string(chBuf);
                    
                    KeyValuePair<std::string, std::string> *kvp = new KeyValuePair<std::string, std::string>(*key, *value);
                    propsRead.push_back(*kvp);
                }
            }
        }
    }
    
    void ExifTool::Dispose(bool disposing)
    {
        DWORD dwRead, dwWritten;
        BOOL bSuccess = FALSE;
        TCHAR chBuf[BUFSIZE];
        
        std::cout << "hProcess: " << m_exifTool.hProcess << std::endl;
        if (m_exifTool.hProcess != NULL)
        {
            if (!disposing)
            {
                OutputDebugString(_T("Failed to dispose ExifTool."));
                std::cout << "Called from destructor!" << std::endl;
            }
        
            // If process is running, shut it down cleanly
            DWORD dwExitCode;
            
            bSuccess = GetExitCodeProcess( m_exifTool.hProcess, &dwExitCode );
            std::cout << "GetExitCodeProcess: " << bSuccess << ", Exit Code: " << dwExitCode << std::endl;
            if ( bSuccess && dwExitCode == STILL_ACTIVE )
            {
                std::cout << "exiftool is STILL ACTIVE" << std::endl;
                
                dwRead = _tcslen(c_exitCommand) * sizeof(TCHAR);
                bSuccess = WriteFile(m_in, c_exitCommand, dwRead, &dwWritten, NULL);
                if ( ! bSuccess ) return;
                
                FlushFileBuffers(m_in);
        
                bSuccess = TerminateProcess( m_exifTool.hProcess, 0 );
                
                OutputDebugString(_T("TerminateProcess"));
                std::cout << "TerminateProcess: " << bSuccess << std::endl;
                
                dwExitCode = WaitForSingleObject( m_exifTool.hProcess, c_exitTimeout );
                
                if (dwExitCode == WAIT_TIMEOUT)
                {
                    bSuccess = TerminateProcess( m_exifTool.hProcess, 0 );
                    OutputDebugString(_T("Timed out waiting for exiftool to exit."));
                    std::cout << "WAIT_TIMEOUT: " << bSuccess << std::endl;
                }
                else if (dwExitCode == WAIT_FAILED)
                {
                    OutputDebugString(_T("ExifTool terminate wait failed."));
                    std::cout << "WAIT_FAILED" << std::endl;
                }
                else if (dwExitCode == WAIT_ABANDONED)
                {
                    OutputDebugString(_T("ExifTool terminate wait abandoned."));
                    std::cout << "WAIT_ABANDONED" << std::endl;
                }
                #ifdef EXIF_TRACE
                else if (dwExitCode == WAIT_OBJECT_0)
                {
                    OutputDebugString(_T("ExifTool exited cleanly."));
                    std::cout << "WAIT_OBJECT_0" << std::endl;
                }
                #endif
                else
                {
                    OutputDebugString(_T("ExifTool terminate unknown status."));
                    std::cout << "WAIT_UNKNOWN" << std::endl;
                }
            } else {
                DWORD err = GetLastError();
                ZeroMemory( chBuf,  BUFSIZE );
                GetErrorMessage( err, chBuf,  BUFSIZE );
                std::cout << std::string(chBuf) << std::endl;
            }
        
            if (m_out != NULL)
            {
                CloseHandle(m_out);
                m_out = NULL;
                std::cout << "Closed m_out" << std::endl;
            }
            if (m_in != NULL)
            {
                CloseHandle(m_in);
                m_in = NULL;
                std::cout << "Closed m_in" << std::endl;
            }
            
            CloseHandle( m_exifTool.hProcess );
            CloseHandle( m_exifTool.hThread );
            
            ZeroMemory( &m_exifTool, sizeof(PROCESS_INFORMATION) );
            std::cout << "After ZeroMemory( m_exifTool )" << std::endl;
        }
    }
    
    ExifTool::~ExifTool()
    {
        std::cout << "~ExifTool()" << std::endl;
        // Do not change this code. Put cleanup code in Dispose(bool disposing) above.
        Dispose(false);
    }
    
    // This code added to correctly implement the disposable pattern.
    void ExifTool::Dispose()
    {
        std::cout << "Dispose()" << std::endl;
        // Do not change this code. Put cleanup code in Dispose(bool disposing) above.
        Dispose(true);
        // No garbage collector in C++
    }
    
    bool ExifTool::TryParseDate(const TCHAR *s, const LPSYSTEMTIME date)
    {
        date->wDayOfWeek = 2; // Tues for Jan 1, 1980
        date->wYear = 1980;
        date->wMonth = 1;
        date->wDay = 1;
        date->wHour = 0;
        date->wMinute = 0;
        date->wSecond = 0;
        date->wMilliseconds = 0;
        
        int year, month, day, hour, minute, second;
        
        // Trim s
        int l, r, start, end;
        for(l=0 * sizeof(TCHAR); l < _tcslen(s); l += sizeof(TCHAR)){
            if (!isspace(s[l])){
                start = l;
                break;
            }
        }
        
        for(r=_tcslen(s)-sizeof(TCHAR); r >= 0; r -= sizeof(TCHAR)){
            if (!isspace(s[r])){
                end = r;
                break;
            }
        }
        
        size_t len = _tcslen(s) * sizeof(TCHAR);
        TCHAR *t = (TCHAR*) malloc(len);
        memset(t, 0, len);
        _tcsncpy(t, &s[l], end - start + 1);
        
        _tprintf(" IN: %s (%d)\n", s, _tcslen(s));
        _tprintf("OUT: %s (%d)\n", t, _tcslen(t));
        
        const int DECIMAL = 10;
        TCHAR *endptr;
        
        endptr = &t[4];
        year = _tcstol(&t[0], &endptr, DECIMAL);
        if (year == 0) return false;
        if (t[4] != ':') return false;
        
        endptr = &t[7];
        month = _tcstol(&t[5], &endptr, DECIMAL);
        if (month == 0) return false;
        if (t[7] != ':') return false;
        
        endptr = &t[10];
        day = _tcstol(&t[8], &endptr, DECIMAL);
        if (day == 0) return false;
        if (t[10] != ' ') return false;
        
        endptr = &t[13];
        hour = _tcstol(&t[11], &endptr, DECIMAL);
        //if (hour == 0) return false;
        if (t[13] != ':') return false;
        
        endptr = &t[16];
        minute = _tcstol(&t[14], &endptr, DECIMAL);
        //if (minute == 0) return false;
        if (t[16] != ':') return false;
        
        endptr = &t[19];
        second = _tcstol(&t[17], &endptr, DECIMAL);
        //if (second == 0) return false;
        
        if (year < 1900 || year > 2200) return false;
        if (month < 1 || month > 12) return false;
        if (day < 1 || day > 31) return false;
        if (hour < 0 || hour > 23) return false;
        if (minute < 0 || minute > 59) return false;
        if (second < 0 || second > 59) return false;
        
        date->wYear = year;
        date->wMonth = month;
        date->wDay = day;
        date->wHour = hour;
        date->wMinute = minute;
        date->wSecond = second;
        
        free(t);
        t = NULL;
        
        return true;
    }
}

BOOL GetErrorMessage(DWORD dwErrorCode, LPTSTR pBuffer, DWORD cchBufferLength)
{
    if (cchBufferLength == 0)
    {
    return FALSE;
    }
    
    DWORD cchMsg = FormatMessage(
        FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,  /* (not used with FORMAT_MESSAGE_FROM_SYSTEM) */
        dwErrorCode,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        pBuffer,
        cchBufferLength,
        NULL);
        
    return (cchMsg > 0);
}

void TestParsing();

int main(int argc, char *argv[])
{
    int exitCode = 0;
    
    try
    {
        ExifToolWrapper::ExifTool exifTool;
        std::cout << _T("main()") << std::endl;
        
        //TestParsing();
        Sleep(5000);
        
        exifTool.Dispose();
    } catch(int exception) {
        switch (exception)
        {
            case CREATE_PIPE_ERROR:
                std::cerr << _T("CREATE_PIPE_ERROR") << std::endl;
                break;
            case DUPLICATE_HANDLE_ERROR:
                std::cerr << _T("DUPLICATE_HANDLE_ERROR") << std::endl;
                break;
            case CREATE_PROCESS_ERROR:
                std::cerr << _T("CREATE_PROCESS_ERROR") << std::endl;
                break;
            case SET_HANDLE_INFORMATION_ERROR:
                std::cerr << _T("SET_HANDLE_INFORMATION_ERROR") << std::endl;
                break;
            case CLOSE_HANDLE_ERROR:
                std::cerr << _T("CLOSE_HANDLE_ERROR") << std::endl;
                break;
            default:
                std::cerr << _T("An unknown exception occurred.") << std::endl;
                break;
        }
        
        exitCode = exception;
    }
    
    return exitCode;
}

void TestParsing()
{
    SYSTEMTIME date;
    bool ok = ExifToolWrapper::ExifTool::TryParseDate(_T("   1819:08:09 12:34:56    "), &date);
    
    _tprintf(_T("Status: %s\n"), (ok)? _T("OK"): _T("Error"));
    _tprintf("Date: %04d-%02d-%02d\nTime: %02d:%02d:%02d\n",
        date.wYear, date.wMonth, date.wDay,
        date.wHour, date.wMinute, date.wSecond);
}




