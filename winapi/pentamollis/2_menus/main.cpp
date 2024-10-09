#include <windows.h>

#define FILE_MENU_NEW   1
#define FILE_MENU_OPEN  2
#define FILE_MENU_EXIT  3

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void AddMenus(HWND hWnd);

HMENU hMenu;

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
        }
        
        break;
    case WM_CREATE:
        AddMenus(hWnd);
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
        (UINT_PTR) hFileMenu,  // Menu item handle () 
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
