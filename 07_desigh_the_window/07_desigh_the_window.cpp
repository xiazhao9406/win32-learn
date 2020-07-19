/* -------------------------------------------------------------------
       design windows' content 
--------------------------------------------------------------------*/

#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
    static TCHAR szAppName[] = TEXT("MyWindows");
    HWND hwnd;
    MSG msg;
    WNDCLASS wndclass;

    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = szAppName;

    if (!RegisterClass(&wndclass))
    {
        MessageBox(NULL, TEXT("这个程序需要在 Windows NT 才能执行！"), szAppName, MB_ICONERROR);
        return 0;
    }

    hwnd = CreateWindow(szAppName,
        TEXT(""),
        WS_POPUP,
        100,
        100,
        600,
        400,
        NULL,
        NULL,
        hInstance,
        NULL);

    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rect;
    int i, j, width, length;

    switch (message)
    {
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        GetClientRect(hwnd, &rect);

        // 计算格子的大小
        width = (rect.right - rect.left) / 6;
        length = (rect.bottom - rect.top) / 4;

        // 绘制边框的长
        for (i = rect.left; i < rect.right; i++)
        {
            SetPixel(hdc, i, rect.top, RGB(255, 0, 0));
            SetPixel(hdc, i, rect.top + 1, RGB(255, 0, 0));
            SetPixel(hdc, i, rect.bottom - 1, RGB(255, 0, 0));
            SetPixel(hdc, i, rect.bottom - 2, RGB(255, 0, 0));
        }

        // 绘制边框的宽
        for (j = rect.top; j < rect.bottom; j++)
        {
            SetPixel(hdc, rect.left, j, RGB(255, 0, 0));
            SetPixel(hdc, rect.left + 1, j, RGB(255, 0, 0));
            SetPixel(hdc, rect.right - 1, j, RGB(255, 0, 0));
            SetPixel(hdc, rect.right - 2, j, RGB(255, 0, 0));
        }

        // 画内部格子的竖线
        i = rect.left + width;
        while (i < rect.right)
        {
            for (j = rect.top; j < rect.bottom; j++)
            {
                SetPixel(hdc, i, j, RGB(0, 0, 255));
            }
            i += width;
        }

        // 画内部格子的横线
        j = rect.top + length;
        while (j < rect.bottom)
        {
            for (i = rect.left; i < rect.right; i++)
            {
                SetPixel(hdc, i, j, RGB(0, 255, 0));
            }
            j += length;
        }

        EndPaint(hwnd, &ps);
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}
