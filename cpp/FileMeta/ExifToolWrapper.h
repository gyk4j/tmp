/*
---
name: ExifToolWrapper.h
description: C++ Wrapper for Phil Harvey's excellent ExifTool
url: https://github.com/gyk4j/tmp/raw/main/cpp/FileMeta/ExifToolWrapper.h
version: 1.0
keywords: CodeBit
dateModified: 2024-11-14
license: http://unlicense.org
about: https://sno.phy.queensu.ca/~phil/exiftool/
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

namespace ExifToolWrapper
{
    class ExifTool
    {
        public:            
            ExifTool();
            ~ExifTool();
            void ExifTool::Dispose();
//            void GetProperties(string filename, ICollection<KeyValuePair<string, string>> propsRead);
//            static bool TryParseDate(string s, DateTimeKind kind, out DateTime date);
            
        protected:
            void Dispose(bool disposing);
            
        private:
            static const std::string c_exeName;
            static const std::string c_arguments;
            static const std::string c_exitCommand;
            static const int c_timeout;    // in milliseconds
            static const int c_exitTimeout;
            
//            static Encoding s_Utf8NoBOM = new UTF8Encoding(false);
//            
//            Process m_exifTool;
//            StreamWriter m_in;
//            StreamReader m_out;
    };
}

#endif // _EXIFTOOL_WRAPPER_H