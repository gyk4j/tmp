#include <windows.h>
#include <stdlib.h>

#define FILE_MENU_NEW   1
#define FILE_MENU_OPEN  2
#define FILE_MENU_EXIT  3
#define GENERATE_BUTTON 4


LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void AddMenus(HWND);
void AddControls(HWND);
void loadImages();

HWND hName, hAge, hOut, hLogo;
HMENU hMenu;
HBITMAP hLogoImage, hGenerateImage;

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
    
    // For testing only. Messsage box shows up as soon as app starts.
    /*
    MessageBoxW
    (
        NULL,       // Handle of owner window. NULL = independent.
        L"HELLO",   // Dialog text
        L"HI",      // Title caption
        MB_OK
    );
    */
    
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
    int val;    // For user response when exiting
    switch (msg)
    {
    case WM_COMMAND:
        switch (wp)
        {
        case FILE_MENU_EXIT:
            // Check with user when they exit.
            val = MessageBoxW(hWnd, L"Are you sure?", L"Wait!", MB_YESNO | MB_ICONEXCLAMATION);
            
            // Types of buttons:
            //   - MB_ABORTRETRYIGNORE
            //   - MB_CAMCELTRYCONTINUE
            //   - MB_HELP
            //   - MB_OK
            //   - MB_OKCANCEL
            //   - MB_RETRYCANCEL
            //   - MB_YESNO
            //   - MB_YESNOCANCEL
            // Types of icons:
            //   - MB_ICONEXCLAMATION
            //   - MB_ICONWARNING
            //   - MB_ICONINFORMATION
            //   - MB_ICONASTERISK
            //   - MB_ICONQUESTION
            //   - MB_ICONSTOP
            //   - MB_ICONERROR
            //   - MB_ICONICONHAND
            // Types of response:
            //   - IDABORT = 3
            //   - IDCANCEL = 2
            //   - IDCONTINUE = 11
            //   - IDIGNORE = 5
            //   - IDNO = 7
            //   - IDOK = 1
            //   - IDRETRY = 4
            //   - IDTRYAGAIN = 10
            //   - IDYES = 6
            if(val == IDYES) {
                DestroyWindow(hWnd);
            } else if (val == IDNO) {
                // do anything required...
            }
            break;
        case FILE_MENU_NEW:
            MessageBeep(MB_ICONINFORMATION);
            break;
        case GENERATE_BUTTON:
            char name[30], age[10], out[50];
            GetWindowText(hName, name, 30);
            GetWindowText(hAge, age, 10);
            
            if (strcmp(name, "") == 0 || strcmp(age, "") == 0)
            {
                // Caption = NULL = default "error"
                val = MessageBoxW(hWnd, L"You did not enter anything!", NULL, MB_ABORTRETRYIGNORE | MB_ICONERROR);
                switch (val)
                {
                    case IDABORT:
                        DestroyWindow(hWnd);
                        break;
                    case IDRETRY:
                        return 0; // break out of function
                    case IDIGNORE:
                        break;                                
                }
            }
            
            strcpy(out, name);
            strcat(out, " is ");
            strcat(out, age);
            strcat(out, " years old.");
            
            SetWindowText(hOut, out);
            
            break;
        }
        
        break;
    case WM_CREATE:
        loadImages();
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
    CreateWindowW(L"Static", L"Name :", WS_VISIBLE | WS_CHILD, 100, 50, 98, 38, hWnd, NULL, NULL, NULL);
    hName = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 50, 98, 38, hWnd, NULL, NULL, NULL);
    
    CreateWindowW(L"Static", L"Age :", WS_VISIBLE | WS_CHILD, 100, 90, 98, 38, hWnd, NULL, NULL, NULL);
    hAge = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 90, 98, 38, hWnd, NULL, NULL, NULL);
    
    // hBut handle is only used in AddControls i.e. no need to declare as global variable.
    // Note newly-added BS_BITMAP in style as a bitmap button.
    // Note text/label is NULL as unused/irrelevant.
    HWND hBut = CreateWindowW(L"Button", NULL, WS_VISIBLE | WS_CHILD | BS_BITMAP, 150, 140, 98, 38, hWnd, (HMENU) GENERATE_BUTTON, NULL, NULL);
    SendMessageW
    (
        hBut,                   // Handle of container control
        BM_SETIMAGE,            // Message. BM = button message (e.g. BM_CLICK, BM_SETSTATE, BM_SETCHECK).
        IMAGE_BITMAP,           // wParam: type
        (LPARAM) hGenerateImage // lParam: handle to image. Need to cast type.
    );
    
    hOut = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 200, 300, 200, hWnd, NULL, NULL, NULL);
    // Requires a static control to hold bitmap, with additional style SS_BITMAP.
    // Label/text/caption set as NULL (unused/irrelevant)
    hLogo = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 350, 60, 100, 100, hWnd, NULL, NULL, NULL);
    // Send message to set the bitmap image
    SendMessageW
    (
        hLogo,              // Handle of container control
        STM_SETIMAGE,       // Message. STM = static message (e.g. STM_SETICON).
        IMAGE_BITMAP,       // wParam: type
        (LPARAM) hLogoImage // lParam: handle to image. Need to cast type.
    );
}

void loadImages()
{
    // Need to cast to HBITMAP as it can return several types HBITMAP, HICON etc.
    hLogoImage = (HBITMAP)LoadImageW
    (
        NULL,           // Null if loading from external file
        L"Logo.bmp",    // Absolute path and file name of .bmp file
        IMAGE_BITMAP,   // Type of image
        100,            // Scaled width: 0 (default without resizing)
        100,            // Scaled height: 0 (default without resizing)
        LR_LOADFROMFILE // Loading image from file
    );
    
    hGenerateImage = (HBITMAP)LoadImageW
    (
        NULL,               // Null if loading from external file
        L"Generate.bmp",    // Absolute path and file name of .bmp file
        IMAGE_BITMAP,       // Type of image
        98,                 // Scaled width: fit "Generate" button container
        38,                 // Scaled height: fit "Generate" button container
        LR_LOADFROMFILE     // Loading image from file
    );
}
