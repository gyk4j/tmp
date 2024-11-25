
//#define UNICODE
//#define _UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <iostream>

#include "mingw-unicode.h"

#define TEST_FILE _T("utf8.txt")
#define UTF_16_CP 1200
#define UTF_8_CP 65001

/* Shared helper/utility functions */
UINT save_code_page( UINT uNewCodePage );
void restore_code_page( UINT uCodePage );
std::string utf8_encode(const std::wstring &wstr);
std::wstring utf8_decode(const std::string &str);

/* Tests */
void test_de();
void test_ru();
void test_zh();
void test_jp();
void test_c();

int _tmain(int argc, _TCHAR *argv[])
{
    _putts(_T("Windows console/terminal font must be set to a Unicode non-raster font like Consolas or Lucida Console."));
    test_c();
    test_de();
    test_ru();
    test_zh();
    test_jp();

    return 0;
}

/*
* Set UTF-8 code page
* Returns current code page.
*/
UINT save_code_page( UINT uNewCodePage )
{
    UINT uCodePage = GetConsoleOutputCP();
    
    if ( !SetConsoleOutputCP( uNewCodePage ) )
    {
        _tprintf( _T("Error: failed to change console code page to UTF-8.\n") );
    }

    //_setmode( _fileno(stdout), _O_TEXT );
    
    return uCodePage;
}

/*
*
*/
void restore_code_page( UINT uCodePage )
{
    if ( !SetConsoleOutputCP( uCodePage ) )
    {
        _tprintf( _T("Error: failed to restore console code page to %d.\n"), uCodePage );
    }
}

/*
* Convert a wide Unicode string to an UTF8 string
*/
std::string utf8_encode(const std::wstring &wstr)
{
    if( wstr.empty() ) return std::string();
    
    int size_needed = WideCharToMultiByte(
        CP_UTF8,            // CodePage: CP_ACP / CP_MACCP / CP_OEMCP / CP_SYMBOL / CP_THREAD_ACP / CP_UTF7 / CP_UTF8
        0,                  // Flags: WC_NO_BEST_FIT_CHARS | WC_COMPOSITECHECK | WC_DEFAULTCHAR
        &wstr[0],           // lpWideCharStr
        (int)wstr.size(),   // cchWideChar
        NULL,               // lpMultiByteStr; NULL = Get size/length
        0,                  // cbMultiByte; 0 = Get size/length
        NULL,               // lpDefaultChar
        NULL                // lpUsedDefaultChar
    );
    
    std::string strTo( size_needed, 0 );
    
    WideCharToMultiByte(
        CP_UTF8,            // CodePage: CP_ACP / CP_MACCP / CP_OEMCP / CP_SYMBOL / CP_THREAD_ACP / CP_UTF7 / CP_UTF8
        0,                  // Flags: WC_NO_BEST_FIT_CHARS | WC_COMPOSITECHECK | WC_DEFAULTCHAR
        &wstr[0],           // lpWideCharStr
        (int)wstr.size(),   // cchWideChar
        &strTo[0],          // lpMultiByteStr
        size_needed,        // cbMultiByte
        NULL,               // lpDefaultChar
        NULL                // lpUsedDefaultChar
    );
    
    return strTo;
}

/*
* Convert an UTF8 string to a wide Unicode String
*/
std::wstring utf8_decode(const std::string &str)
{
    if( str.empty() ) return std::wstring();
    
    int size_needed = MultiByteToWideChar(
        CP_UTF8,            // CodePage: CP_ACP / CP_MACCP / CP_OEMCP / CP_SYMBOL / CP_THREAD_ACP / CP_UTF7 / CP_UTF8
        0,                  // Flags: MB_PRECOMPOSED (default) / MB_COMPOSITE, MB_USEGLYPHCHARS | MB_ERR_INVALID_CHARS
        &str[0],            // lpMultiByteStr
        (int)str.size(),    // cbMultiByte
        NULL,               // NULL = Get size/length
        0                   // 0 = Get size/length
    );
    
    std::wstring wstrTo( size_needed, 0 );
    
    MultiByteToWideChar(
        CP_UTF8,            // CodePage: CP_ACP / CP_MACCP / CP_OEMCP / CP_SYMBOL / CP_THREAD_ACP / CP_UTF7 / CP_UTF8
        0,                  // Flags: MB_PRECOMPOSED (default) / MB_COMPOSITE, MB_USEGLYPHCHARS | MB_ERR_INVALID_CHARS
        &str[0],            // lpMultiByteStr
        (int)str.size(),    // cbMultiByte
        &wstrTo[0],         // lpWideCharStr
        size_needed         // cchWideChar
    );
    
    return wstrTo;
}

void test_de()
{
    UINT uCodePage = save_code_page( UTF_8_CP );
    wchar_t* de = L"Ä ä Ü ü ß";
    puts( utf8_encode(de).c_str() );
    restore_code_page( uCodePage );
}

void test_ru()
{
    UINT uCodePage = save_code_page( UTF_8_CP );
    wchar_t* ru = L"Я Б Г Д Ж Й";
    puts( utf8_encode(ru).c_str() );
    restore_code_page( uCodePage );
}

void test_zh()
{
    UINT uCodePage = save_code_page( UTF_8_CP );
    wchar_t* zh = L"中文简体";
    puts( utf8_encode(zh).c_str() );
    restore_code_page( uCodePage );
}

void test_jp()
{
    UINT uCodePage = save_code_page( UTF_8_CP );
    wchar_t* jp = L"ｱｲｳｴｵｶｷｸｹｺｻｼｽｾｿﾀﾁﾂﾃ";
    puts( utf8_encode(jp).c_str() );
    restore_code_page( uCodePage );
}

void test_c()
{
    UINT uCodePage = save_code_page( UTF_8_CP );
    
    FILE* fp = _tfopen( TEST_FILE, _T("rt") );
    
    if ( fp == NULL )
    {
        _tprintf( _T("Error: failed to open '%s'.\n"), TEST_FILE );
        return;
    }
    
    TCHAR   buffer[128];
    TCHAR   decode[128];
    
    while( _fgetts( buffer, sizeof( buffer ), fp ) != NULL )
    {
        _tprintf( _T("%s\n"), buffer );
        _putts( buffer );
        //WriteConsole();
        ZeroMemory( buffer, sizeof(buffer) );
        ZeroMemory( buffer, sizeof(decode) );
    }
    
    fclose( fp );
    
    restore_code_page( uCodePage );
}

