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
//#define EXIF_TRACE

#include <tchar.h>
#include <ctype.h>
#include <iostream>
#include <windows.h>
#include "ExifToolWrapper.h"

namespace ExifToolWrapper
{
    LPCTSTR ExifTool::c_exeName = _T("exiftool.exe");
    LPCTSTR ExifTool::c_arguments = _T("-stay_open 1 -@ - -common_args -charset UTF8 -G1 -args");
    LPCTSTR ExifTool::c_exitCommand = _T("-stay_open\n0\n-execute\n");
    const DWORD ExifTool::c_timeout = 30000;    // in milliseconds
    const DWORD ExifTool::c_exitTimeout = 15000;
    
    // Reference: https://learn.microsoft.com/en-us/windows/win32/intl/code-page-identifiers
    const UINT ExifTool::s_Utf8NoBOM = 65001;
    
    ExifTool::ExifTool()
    {
#ifdef EXIF_TRACE
        std::cout << "ExifTool()" << std::endl;
#endif
        
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
        
        // Set UTF-8 code page
        if ( IsValidCodePage( s_Utf8NoBOM ) ) {
            if ( SetConsoleCP( s_Utf8NoBOM ) == 0 )
                std::cerr << "WARN: Failed to set UTF-8 input code page" << std::endl;
            if ( SetConsoleOutputCP( s_Utf8NoBOM ) == 0 )
                std::cerr << "WARN: Failed to set UTF-8 output code page" << std::endl;
        } else {
            std::cerr << "WARN: UTF-8 code page is unavailable?" << std::endl;
        }
        
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
            m_in = hInWr;
            m_out = hOutRd;
            
            // CreateProcess does not return a Process object like in .NET.
            // Closest equivalence is the PROCESS_INFORMATION struct.
            ZeroMemory( &m_exifTool, sizeof(PROCESS_INFORMATION) );
            CopyMemory( &m_exifTool, &piProcInfo, sizeof(PROCESS_INFORMATION) );
        }
        
        // Close handles to the child process and its primary thread.
        // Some applications might keep these handles to monitor the status
        // of the child process, for example.
        // CloseHandle( piProcInfo.hProcess );   
        // CloseHandle( piProcInfo.hThread );
        
        // Close handles to the stdin and stdout pipes no longer needed by the child process.
        // If they are not explicitly closed, there is no way to recognize that the child process has ended.
        
        CloseHandle( hOutWr );
        CloseHandle( hInRd );
    }
    
    void ExifTool::GetProperties(const std::string filename, std::map<std::string, std::string> &propsRead) const
    {
        DWORD dwRead = 0, dwWritten = 0;
        BOOL bSuccess = FALSE;
        TCHAR chBuf[BUFSIZE];
        HANDLE hParentStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        
        dwRead = filename.length() * sizeof(TCHAR);
        bSuccess = WriteFile(m_in, filename.c_str(), dwRead, &dwWritten, NULL);
        if ( ! bSuccess ) return;
        
        FlushFileBuffers(m_in);
        
        dwRead = _tcslen("\n-execute\n") * sizeof(TCHAR);
        bSuccess = WriteFile(m_in, "\n-execute\n", dwRead, &dwWritten, NULL);
        if ( ! bSuccess ) return;
        
        FlushFileBuffers(m_in);
            
#ifdef EXIF_TRACE
        OutputDebugString(filename.c_str());
        OutputDebugString(_T("-execute"));
#endif
        // Close the pipe handle so the child process stops reading.
        
        //if ( ! CloseHandle(m_in) )
        //    throw CLOSE_HANDLE_ERROR;
        
        int bi = 0;

        TCHAR line[BUFSIZE];
        int li = 0;

        // Read first block
        ZeroMemory( chBuf, BUFSIZE );
        bSuccess = ReadFile( m_out, chBuf, BUFSIZE, &dwRead, NULL );

#ifdef EXIF_TRACE
        std::cout << "--- First block: dwRead = " << dwRead << std::endl;
        
        // once a new block has been read, reset block index.
        if ( bSuccess && dwRead > 0 ) {
            LPCSTR isFullBlock = (dwRead == BUFSIZE) ? _T("Yes"): _T("No");
            std::cout << "Full block: " << std::string(isFullBlock) << std::endl;
        } else {
            // Failed to read anything for further processing.
            std::cout << "Failed to read first block." << std::endl;
        }
#endif
        
        if ( !bSuccess || dwRead == 0 )
            return;

        for (; ; )
        {
            // Prepare to extract a line.
            ZeroMemory( line,  BUFSIZE );
            for (int li = 0; li < BUFSIZE && bi < dwRead; li++, bi++)
            {
                if ( chBuf[bi] != '\n' && chBuf[bi] != '\r' ) {
                    line[li] = chBuf[bi];
                } else if( chBuf[bi] == '\n' ){
                    // Exit line splitting loop and let line be parsed/processed.
                    ++bi;
                    break;
                }
                
                // Have we reached the last byte/character of block?
                if ( bi == dwRead-1 )
                {
                    // Read next block
                    ZeroMemory( chBuf, BUFSIZE );
                    bSuccess = ReadFile( m_out, chBuf, BUFSIZE, &dwRead, NULL );
                    if ( !bSuccess || dwRead == 0 ) {
                        line[li+1] = 0;
                        break;
                    }
#ifdef EXIF_TRACE
                    std::cout << "--- Next block: dwRead = " << dwRead << std::endl;
                    
                    if ( bSuccess && dwRead > 0 ) {
                        LPCSTR isFullBlock = (dwRead == BUFSIZE)? _T("Yes") : _T("No");
                        std::cout << "Full block: " << std::string(isFullBlock) << std::endl;
                    } else {
                        // Failed to read a new block for further processing.
                        // Should not happen unless metadata happens to be 
                        // multiples of BUFSIZE.
                        std::cout << "Last block already read. Failed to read next block." << std::endl;
                    }
#endif                    
                    // once a new block has been read, reset block index.
                    // bi will be automatically incremented at the end of this
                    // loop. If we reset to bi = 0, chBuf[0] will be skipped
                    // without being processed.
                    bi = -1;
                }
            }
            
            if ( _tcslen( line ) == 0 )
                break;
            
#ifdef EXIF_TRACE
            OutputDebugString(_T(line));
            std::cout << std::string(line) << std::endl;
#endif

            if (_tcscmp(line, "{ready}") == 0) break;
            if (line[0] == '-')
            {
                int eq = _tcscspn(line, "=");
                if (eq > 1)
                {
                    TCHAR tkBuf[BUFSIZE];
                    
                    ZeroMemory( tkBuf,  BUFSIZE );
                    _tcsncpy( tkBuf, &line[1], eq - 1 );
                    std::string key(tkBuf);
                    
                    ZeroMemory( tkBuf,  BUFSIZE );
                    _tcscpy( tkBuf, &line[eq + 1] );
                    
                    // Trim
                    std::string value(tkBuf);
                    /*
                    KeyValuePair<std::string, std::string> *kvp = 
                        new KeyValuePair<std::string, std::string>(key, value);
                    propsRead.push_back(*kvp);
                    
                    KeyValuePair<std::string, std::string> kvp(key, value);
                    propsRead.push_back(kvp);
                    */
                    
                    propsRead[key] = value;
                }
            }
        }
    }
    
    void ExifTool::Dispose(bool disposing)
    {
        DWORD dwRead, dwWritten;
        BOOL bSuccess = FALSE;
        TCHAR chBuf[BUFSIZE];

#ifdef EXIF_TRACE
        std::cout << "hProcess: " << m_exifTool.hProcess << std::endl;
#endif

        if (m_exifTool.hProcess != NULL)
        {
#ifdef EXIF_TRACE
            if (!disposing)
            {
                OutputDebugString(_T("Failed to dispose ExifTool."));
                std::cout << "Called from destructor!" << std::endl;
            }
#endif
        
            // If process is running, shut it down cleanly
            DWORD dwExitCode;
            
            bSuccess = GetExitCodeProcess( m_exifTool.hProcess, &dwExitCode );
#ifdef EXIF_TRACE
            std::cout << "GetExitCodeProcess: " << bSuccess << ", Exit Code: " << dwExitCode << std::endl;
#endif
            if ( bSuccess && dwExitCode == STILL_ACTIVE )
            {
#ifdef EXIF_TRACE
                std::cout << "exiftool is STILL ACTIVE" << std::endl;
#endif
                
                dwRead = _tcslen(c_exitCommand) * sizeof(TCHAR);
                bSuccess = WriteFile(m_in, c_exitCommand, dwRead, &dwWritten, NULL);
                if ( ! bSuccess ) return;
                
                FlushFileBuffers(m_in);
#ifdef EXIF_TRACE
                std::cout << "Waiting for exit..." << std::endl;
#endif
                
                dwExitCode = WaitForSingleObject( m_exifTool.hProcess, c_exitTimeout );
#ifdef EXIF_TRACE
                std::cout << "exiftool process has exited." << std::endl;
#endif
                
                if (dwExitCode == WAIT_TIMEOUT)
                {
                    bSuccess = TerminateProcess( m_exifTool.hProcess, 0 );
#ifdef EXIF_TRACE
                    OutputDebugString(_T("Timed out waiting for exiftool to exit."));
                    std::cout << "WAIT_TIMEOUT: " << bSuccess << std::endl;
#endif
                }
                else if (dwExitCode == WAIT_FAILED)
                {
#ifdef EXIF_TRACE
                    OutputDebugString(_T("ExifTool terminate wait failed."));
                    std::cout << "WAIT_FAILED" << std::endl;
#endif
                }
                else if (dwExitCode == WAIT_ABANDONED)
                {
#ifdef EXIF_TRACE
                    OutputDebugString(_T("ExifTool terminate wait abandoned."));
                    std::cout << "WAIT_ABANDONED" << std::endl;
#endif
                }
                #ifdef EXIF_TRACE
                else if (dwExitCode == WAIT_OBJECT_0)
                {
#ifdef EXIF_TRACE
                    OutputDebugString(_T("ExifTool exited cleanly."));
                    std::cout << "WAIT_OBJECT_0" << std::endl;
#endif
                }
                #endif
                else
                {
#ifdef EXIF_TRACE
                    OutputDebugString(_T("ExifTool terminate unknown status."));
                    std::cout << "WAIT_UNKNOWN" << std::endl;
#endif
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
#ifdef EXIF_TRACE
                std::cout << "Closed m_out" << std::endl;
#endif
            }
            if (m_in != NULL)
            {
                CloseHandle(m_in);
                m_in = NULL;
#ifdef EXIF_TRACE
                std::cout << "Closed m_in" << std::endl;
#endif
            }
            
            CloseHandle( m_exifTool.hProcess );
            CloseHandle( m_exifTool.hThread );
            
            ZeroMemory( &m_exifTool, sizeof(PROCESS_INFORMATION) );
#ifdef EXIF_TRACE
            std::cout << "After ZeroMemory( m_exifTool )" << std::endl;
#endif
        }
    }
    
    ExifTool::~ExifTool()
    {
#ifdef EXIF_TRACE
        std::cout << "~ExifTool()" << std::endl;
#endif
        // Do not change this code. Put cleanup code in Dispose(bool disposing) above.
        Dispose(false);
    }
    
    // This code added to correctly implement the disposable pattern.
    void ExifTool::Dispose()
    {
#ifdef EXIF_TRACE
        std::cout << "Dispose()" << std::endl;
#endif
        // Do not change this code. Put cleanup code in Dispose(bool disposing) above.
        Dispose(true);
        // No garbage collector in C++
    }
    
    BOOL ExifTool::TryParseDate(const std::string s, const DateTimeKind kind, const LPSYSTEMTIME date)
    {
        // Need to make a writable copy.
        LPCTSTR ro = s.c_str();
        int lro = _tcslen(ro) + 1;
        LPTSTR ts = new TCHAR[lro];
        ZeroMemory( ts, lro );
        _tcsncpy( ts, ro, lro );
        
        date->wDayOfWeek = 1; // Mon for Jan 1, 1900
        date->wYear = 1900;
        date->wMonth = 1;
        date->wDay = 1;
        date->wHour = 0;
        date->wMinute = 0;
        date->wSecond = 0;
        date->wMilliseconds = 0;
        
        int year, month, day, hour, minute, second;
        
        // Trim s
        int l, r, start, end;
        for(l=0 * sizeof(TCHAR); l < _tcslen(ts); l += sizeof(TCHAR)){
            if (!isspace(ts[l])){
                start = l;
                break;
            }
        }
        
        for(r=_tcslen(ts)-sizeof(TCHAR); r >= 0; r -= sizeof(TCHAR)){
            if (!isspace(ts[r])){
                end = r;
                break;
            }
        }
        
        size_t len = _tcslen(ts) + 1;
        LPTSTR t = new TCHAR[len];
        ZeroMemory(t, len);
        _tcsncpy(t, &ts[l], end - start + 1);

#ifdef EXIF_TRACE
        _tprintf(" IN: %s (%d)\n", ts, _tcslen(ts));
        _tprintf("OUT: %s (%d)\n", t, _tcslen(t));
#endif
        
        const int DECIMAL = 10;
        const int TOKEN_LEN = 5;
        TCHAR token[TOKEN_LEN];
        
        ZeroMemory( token, TOKEN_LEN );
        _tcsncpy( token, &t[0], 4 );
        year = _tcstol( token, NULL, DECIMAL );
#ifdef EXIF_TRACE
        _tprintf( "yyyy: %d\n", year );
#endif
        if (year == 0) return false;
        if (t[4] != ':') return false;

        ZeroMemory( token, TOKEN_LEN );
        _tcsncpy( token, &t[5], 2 );
        month = _tcstol( token, NULL, DECIMAL );
#ifdef EXIF_TRACE
        _tprintf( "MM: %d\n", month );
#endif
        if (month == 0) return false;
        if (t[7] != ':') return false;
        
        ZeroMemory( token, TOKEN_LEN );
        _tcsncpy( token, &t[8], 2 );
        day = _tcstol( token, NULL, DECIMAL );
#ifdef EXIF_TRACE
        _tprintf( "dd: %d\n", day );
#endif
        if (day == 0) return false;
        if (t[10] != ' ') return false;
        
        ZeroMemory( token, TOKEN_LEN );
        _tcsncpy( token, &t[11], 2 );
        hour = _tcstol( token, NULL, DECIMAL );
#ifdef EXIF_TRACE
        _tprintf( "HH: %d\n", hour );
#endif
        //if (hour == 0) return false;
        if (t[13] != ':') return false;
        
        ZeroMemory( token, TOKEN_LEN );
        _tcsncpy( token, &t[14], 2 );
        minute = _tcstol( token, NULL, DECIMAL );
#ifdef EXIF_TRACE
        _tprintf( "mm: %d\n", minute );
#endif
        //if (minute == 0) return false;
        if (t[16] != ':') return false;
        
        ZeroMemory( token, TOKEN_LEN );
        _tcsncpy( token, &t[17], 2 );
        second = _tcstol( token, NULL, DECIMAL );
#ifdef EXIF_TRACE
        _tprintf( "ss: %d\n", second );
#endif
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
        
        switch (kind)
        {
            case Unspecified:
                // Skip any time conversion.
                break;
            case Utc:
                SYSTEMTIME local;
                if ( SystemTimeToTzSpecificLocalTime(
                    NULL,   // lpTimeZoneInformation. Use currently active time zone.
                    date,   // lpUniversalTime
                    &local  // lpLocalTime
                ) )
                {
                    CopyMemory( date, &local, sizeof(SYSTEMTIME) );
                } else {
                    std::cerr << "WARN: Local time conversion failed." << std::endl;
                }
                break;
            case Local:
                SYSTEMTIME utc;
                if ( TzSpecificLocalTimeToSystemTime(
                    NULL,   // lpTimeZoneInformation. Use currently active time zone.
                    date,   // lpLocalTime
                    &utc    // lpUniversalTime
                ) )
                {
                    CopyMemory( date, &utc, sizeof(SYSTEMTIME) );
                } else {
                    std::cerr << "WARN: Local time conversion failed." << std::endl;
                }
                break;
            default:
                // Skip any time conversion.
                break;
        }
        
        delete[] t;
        t = NULL;
        
        delete[] ts;
        ts = NULL;
        
        return true;
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
}
