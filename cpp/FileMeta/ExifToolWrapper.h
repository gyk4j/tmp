/*
---
name: ExifToolWrapper.h
description: C++ Wrapper for Phil Harvey's excellent ExifTool
url: https://github.com/gyk4j/tmp/raw/main/cpp/FileMeta/ExifToolWrapper.h
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

#ifndef _EXIFTOOL_WRAPPER_H
#define _EXIFTOOL_WRAPPER_H

#include <string>
#include <vector>
#include <tchar.h>
#include <windows.h>

#define BUFSIZE 4096 

#define CREATE_PIPE_ERROR               -8
#define DUPLICATE_HANDLE_ERROR          -9
#define CREATE_PROCESS_ERROR            -10
#define SET_HANDLE_INFORMATION_ERROR    -11
#define CLOSE_HANDLE_ERROR              -12

namespace ExifToolWrapper
{
    template <typename K, typename V>
    struct KeyValuePair {
        public:
            K Key;
            V Value;
            KeyValuePair(K k, V v)
            {
                Key = k;
                Value = v;
            }
    };
    
    class ExifTool
    {
        public:            
            ExifTool();
            ~ExifTool();
            void ExifTool::Dispose();
            void GetProperties(const TCHAR *filename, std::vector< KeyValuePair<std::string, std::string> > propsRead);            
            static bool TryParseDate(const TCHAR *s, const LPSYSTEMTIME date);
            
        protected:
            void Dispose(bool disposing);
            
        private:
            static const TCHAR* c_exeName;
            static const TCHAR* c_arguments;
            static const TCHAR* c_exitCommand;
            static const int c_timeout;    // in milliseconds
            static const int c_exitTimeout;
                        
            PROCESS_INFORMATION m_exifTool;
            HANDLE m_in;
            HANDLE m_out;
    };
    
    BOOL GetErrorMessage(DWORD dwErrorCode, LPTSTR pBuffer, DWORD cchBufferLength);
}

#endif // _EXIFTOOL_WRAPPER_H
