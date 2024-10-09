// NOTE: Requires comdlg32.lib (VC++) / libcomdlg32.a (Mingw).

#include <windows.h>
#include <stdio.h>

#define OPEN_FILE_BUTTON 1

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void AddControls(HWND);

HWND hMainWindow, hEdit;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int nCmdShow)
{
    WNDCLASSW wc = {0};
    
    wc.hbrBackground = (HBRUSH) COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"myWindowClass";
    wc.lpfnWndProc = WindowProcedure;
    
    if(!RegisterClassW(&wc))
        return -1;
    
    hMainWindow = CreateWindowW
    (
        L"myWindowClass",                   // Registered Window class
        L"My Window",                       // Window title
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,   // Window style(s)
        100,                                // Position left X
        100,                                // Position top Y
        500,                                // Window Width
        500,                                // Window Height
        NULL,                               // Parent window handle
        NULL,                               // Menu handle
        NULL,                               // Application handle (set in wc)
        NULL                                // Other parameters...
    );    
    
    MSG msg = {0};
    
    while( GetMessageW(&msg, NULL, 0, 0) )
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return 0;
}

void display_file(char* path)
{
    FILE *file;
    file = fopen( path, "r" );
    
    // Check if file fails to open.
    if(file == NULL)
    {
        MessageBox( NULL, "Failed to open", "Error", MB_OK );
        return;
    }
    
    // Get size of file.
    fseek( file, 0, SEEK_END );
    int _size = ftell( file );    
    rewind( file );
    
    // Prepare the buffer.
    // Add 1 extra for terminating character
    char *data = (char*) malloc( sizeof(char) * (_size + 1) ); 
    //new char( _size + 1 ); // Always crash.
    
    // Read the file
    fread
    ( 
        data,   // Destination buffer to write to
        _size,  // Size of 1 element to read
        1,      // Number of elements
        file    // Source file handle
    );
    
    data[_size] = '\0'; // Terminate the string.
    
    SetWindowText
    (
        hEdit,  // Edit box to set the text for.
        data    // Data (text) value to set.
    );
    
    free( data );
    
    fclose(file);
}

void open_file(HWND hWnd)
{
    OPENFILENAME ofn;
    
    char file_name[100];
    
    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = hWnd;                   // Parent window
    ofn.lpstrFile = file_name;              // Selected file stored in variable
    ofn.lpstrFile[0] = '\0';                // Terminating character i.e. no default selected file
    ofn.nMaxFile = 100;                     // Integer specifying max buffer length
    ofn.lpstrFilter = "All files (*.*)\0*.*\0Source files (*.cpp)\0*.cpp\0Text files (*.txt)\0*.txt\0";
    ofn.nFilterIndex = 1;                   // Select default filter
    
    GetOpenFileName(&ofn);
    
    // Print the selected file.
    // MessageBox(hWnd, ofn.lpstrFile, "", MB_OK);
    
    display_file( ofn.lpstrFile );
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    int val;    // For user response when exiting
    switch (msg)
    {
    case WM_COMMAND:
        switch (wp)
        {
        case OPEN_FILE_BUTTON:
            open_file(hWnd);
            break;   
        }
        
        break;
    case WM_CREATE:        
        AddControls(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProcW(hWnd, msg, wp, lp);
    }
}

void AddControls(HWND hWnd)
{    
    CreateWindowW
    (
        L"Button",                  // Control type
        L"Open File",               // Text/Caption
        WS_VISIBLE | WS_CHILD,      // Styles
        10,                         // Left X
        10,                         // Top Y
        150,                        // Width
        36,                         // Height
        hWnd,                       // Parent container
        (HMENU) OPEN_FILE_BUTTON,   // Control ID
        NULL,                       // Unused
        NULL                        // Unused
    );
    
    hEdit = CreateWindowW
    (
        L"Edit",                    // Control type 
        L"",                        // Text/Caption
        WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_BORDER | ES_AUTOVSCROLL, 
        10,                         // Left X
        50,                         // Top Y
        400,                        // Width
        300,                        // Height
        hWnd,                       // Parent container
        NULL,                       // Control ID
        NULL,                       // Unused
        NULL                        // Unused
    );
}

