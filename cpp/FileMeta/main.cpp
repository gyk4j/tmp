#include <iostream>
#include "ExifToolWrapper.h"

void TestParsing();
void TestGetProperties( const ExifToolWrapper::ExifTool &exifTool );
void DumpProps( const std::map<std::string, std::string> &props );

int main(int argc, char *argv[])
{
    int exitCode = 0;

    try
    {
        ExifToolWrapper::ExifTool exifTool;
#ifdef EXIF_TRACE
        std::cout << _T("main()") << std::endl;
#endif

        //TestParsing();
        TestGetProperties( exifTool );

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
#ifdef EXIF_TRACE
    system("PAUSE");
#endif
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

void TestGetProperties( const ExifToolWrapper::ExifTool &exifTool )
{
    std::map<std::string, std::string> props;

    exifTool.GetProperties( _T("Canon_40D.jpg"), props );
    DumpProps( props );
    props.clear();

    exifTool.GetProperties( _T("Fujifilm_FinePix_E500.jpg"), props );
    DumpProps( props );
    props.clear();

}

void DumpProps( const std::map<std::string, std::string> &props )
{
    std::map<std::string, std::string>::const_iterator it = props.begin();
    
    while( it != props.end() )
    {
        /* If using ExifToolWrapper::KeyValuePair
        std::cout << it->Key << " = " << it->Value << std::endl;
        */
        std::cout << it->first << " = " << it->second << std::endl;
        it++;
    }
}
