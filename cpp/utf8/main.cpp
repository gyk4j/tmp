
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
void test_utf8( const wchar_t* s );
void test_c();

int _tmain(int argc, _TCHAR *argv[])
{
    UINT uCodePage = save_code_page( UTF_8_CP );
    
    _putts(_T("Windows console/terminal font must be set to a Unicode non-raster font like Consolas or Lucida Console."));
    //test_c();
    test_utf8( L"en: Some English text" );  // English
    test_utf8( L"de: Ä ä Ü ü ß" ); 		// German
    test_utf8( L"ru: Я Б Г Д Ж Й" ); 	// Russian
    test_utf8( L"zh: 中文简体" ); 		// Chinese
    test_utf8( L"jp: ｱｲｳｴｵｶｷｸｹｺｻｼｽｾｿﾀﾁﾂﾃ" ); 	// Japanese
    test_utf8( L"ko: 투서로 뜨고 투서에 지나" );	// Korean
    
    restore_code_page( uCodePage );

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

void test_utf8( const wchar_t* s )
{
    /*
    HANDLE hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
    
    if(hStdOut == INVALID_HANDLE_VALUE){
        puts( "Error: invalid handle value" );
        return;
    }
    
    DWORD dwWritten;
    
    const char* ws = utf8_encode(s).c_str();
    
    WriteFile(
        hStdOut,    // handle to the console screen buffer
        ws,         // pointer to a buffer that contains characters to be written to the console screen buffer
        strlen(ws), // number of characters to be written
        &dwWritten, // pointer to a variable that receives the number of characters actually written
        NULL        // Reserved; must be NULL
    );
    
    WriteFile(
        hStdOut,
        L"\n",
        wcslen(L"\n"),
        &dwWritten,
        NULL
    );
    */
    puts( utf8_encode(s).c_str() );
}

void test_c()
{    
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
}

