#include <windows.h>

void print(char * str);

LRESULT CALLBACK mainWindowCallback(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_SIZE:
        {
            print("Received Size Message\n");
            return 0;
        } break;
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            print("Received Destroy Message\n");
            return 0;
        } break;
        case WM_CLOSE:
        {
            print("Received Close Message\n");
            DestroyWindow(hwnd);
            UnregisterClass("RayMarcherWindowClass", GetModuleHandle(NULL));
            return 0;
        } break;
        case WM_ACTIVATEAPP:
        {
            print("Received Activate Message\n");
            return 0;
        } break;
        default:
        {
        } break;
    }
    return DefWindowProcA(hwnd, uMsg, wParam, lParam);
}

void print(char * str) {
    int len = 0;
    while (str[len]) len++;
    
    WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), str, len, NULL, NULL);
}

int CALLBACK WinMain(
    HINSTANCE bInstance,
    HINSTANCE bPrevInstance,
    LPSTR  lpCmdLine,
    int nCmdShow)
{
    AllocConsole();

    WNDCLASSA windowClass = {};
    windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    windowClass.lpfnWndProc = mainWindowCallback;
    windowClass.hInstance = bInstance;
    //windowClass.hIcon;
    windowClass.lpszClassName = "RayMarcherWindowClass";
    
    if (!RegisterClass(&windowClass))
    {
        print("Could not register window!\n");
        DWORD error = GetLastError();
        if (error != ERROR_CLASS_ALREADY_EXISTS) {
            return HRESULT_FROM_WIN32(error);
        }
    }
    
    HWND windowHandle = CreateWindowExA(
        0,
        windowClass.lpszClassName,
        "Raymarcher",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        0,
        0,
        bInstance,
        0);
    
    if (!windowHandle) {
        print("Could not create window!\n");
        DWORD error = GetLastError();
        return HRESULT_FROM_WIN32(error);
    }
    
    while (true)
    {
        MSG message;
        BOOL messageResult = GetMessageA(&message, 0, 0, 0);

        if (messageResult <= 0)
        {
            break;
        }
        
        TranslateMessage(&message);
        DispatchMessageA(&message);
        
    }

    
    print("test\n");
    MessageBoxA(0, "Continue?", "", MB_SYSTEMMODAL);
    return 0;
}