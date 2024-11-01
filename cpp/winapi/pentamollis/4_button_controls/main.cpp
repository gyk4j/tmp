#include <windows.h>

#define FILE_MENU_NEW   1
#define FILE_MENU_OPEN  2
#define FILE_MENU_EXIT  3
#define CHANGE_TITLE    4

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void AddMenus(HWND);
void AddControls(HWND);

HMENU hMenu;
HWND hEdit;
HWND hButton;

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
    
    CreateWindowW
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

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
    case WM_COMMAND:
        switch (wp)
        {
        case FILE_MENU_EXIT:
            DestroyWindow(hWnd);
            break;
        case FILE_MENU_NEW:
            MessageBeep(MB_ICONINFORMATION);
            break;
        case CHANGE_TITLE:
            wchar_t text[100];
            GetWindowTextW(hEdit, text, 100);
            SetWindowTextW(hWnd, text);
            break;
        }
        
        break;
    case WM_CREATE:
        AddMenus(hWnd);
        AddControls(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProcW(hWnd, msg, wp, lp);
    }
}

void AddMenus(HWND hWnd)
{
    hMenu = CreateMenu();
    HMENU hFileMenu = CreateMenu();
    HMENU hSubMenu = CreateMenu();
    
    AppendMenu( hSubMenu, MF_STRING, 0, "SubMenu Item" );
    
    
    AppendMenu( hFileMenu, MF_STRING, FILE_MENU_NEW, "New" );
    AppendMenu( hFileMenu, MF_POPUP, (UINT_PTR) hSubMenu, "Open SubMenu" );
    AppendMenu( hFileMenu, MF_SEPARATOR, 0, 0 ); // Param 3 and 4 ignored if MF_SEPARATOR
    AppendMenu( hFileMenu, MF_STRING, FILE_MENU_EXIT, "Exit" );
    
    AppendMenu
    (
        hMenu,                  // Menu to append
        MF_POPUP,               // Flags: MF_POPUP for menu
        (UINT_PTR) hFileMenu,   // Menu item handle () 
        "File"                  // if MF_STRING, pointer to string for menu item text
    );
    
    AppendMenu
    (
        hMenu,      // Menu to append
        MF_STRING,  // Flags: MF_STRING for text content
        0,          // Menu item ID (NULL) 
        "Help"      // if MF_STRING, pointer to string for menu item text
    );    
    
    SetMenu
    (
        hWnd,   // Window handle
        hMenu   // Menu handle
    );
}

void AddControls(HWND hWnd)
{
    CreateWindowW
    (
        L"static",                          // Label
        L"Enter Text Here :",               // Window text/caption
        WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,  // Window style(s)
        200,                                // Position left X
        100,                                // Position top Y
        100,                                // Control width
        50,                                 // Control height
        hWnd,                               // Window handle
        NULL,                               // Menu (unused)
        NULL,                               // Instance (child control)
        NULL                                // Parameters (unused)
    );
    
    hEdit = CreateWindowW
    (
        L"Edit",                            // Textbox
        L"...",                             // Window text/caption
        WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,  // Window style(s)
        200,                                // Position left X
        152,                                // Position top Y
        100,                                // Control width
        50,                                 // Control height
        hWnd,                               // Window handle
        NULL,                               // Menu (unused)
        NULL,                               // Instance (child control)
        NULL                                // Parameters (unused)
    );
    
    hButton = CreateWindowW
    (
        L"Button",                          // Textbox
        L"Change Title",                    // Window text/caption
        WS_VISIBLE | WS_CHILD,              // Window style(s)
        200,                                // Position left X
        204,                                // Position top Y
        100,                                // Control width
        50,                                 // Control height
        hWnd,                               // Window handle
        (HMENU) CHANGE_TITLE,               // Control ID
        NULL,                               // Instance (child control)
        NULL                                // Parameters (unused)
    );
}
