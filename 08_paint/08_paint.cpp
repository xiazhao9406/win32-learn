#include <windows.h>
#include <windowsx.h>

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
        MessageBox(NULL, TEXT("this project should run in  Windows NT ！"), szAppName, MB_ICONERROR);
        return 0;
    }

    hwnd = CreateWindow(szAppName,
        TEXT(""),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
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
    static int cxClient, cyClient;
    HPEN hPen = NULL;
    HPEN  hOldPen = NULL;

    switch (message)
    {
    case WM_SIZE:
        cxClient = LOWORD(lParam);
        cyClient = HIWORD(lParam);
        return 0;

    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);

        // 左边黑色扇形
        SelectObject(hdc, GetStockObject(BLACK_BRUSH));
        Pie(hdc, cxClient / 2 - 300, cyClient / 2 - 300, cxClient / 2 + 300, cyClient / 2 + 300, \
            cxClient / 2, cyClient / 2 - 300, cxClient / 2, cyClient / 2 + 300);

        // 右边黑色扇形
        SelectObject(hdc, GetStockObject(WHITE_BRUSH));
        Pie(hdc, cxClient / 2 - 300, cyClient / 2 - 300, cxClient / 2 + 300, cyClient / 2 + 300, \
            cxClient / 2, cyClient / 2 + 300, cxClient / 2, cyClient / 2 - 300);

        // 上方黑色小扇形
        SelectObject(hdc, GetStockObject(BLACK_BRUSH));
        Pie(hdc, cxClient / 2 - 150, cyClient / 2 - 300, cxClient / 2 + 150, cyClient / 2, \
            cxClient / 2, cyClient / 2 + 300, cxClient / 2, cyClient / 2);

        // 下方白色小扇形
        SelectObject(hdc, GetStockObject(WHITE_BRUSH));
        Pie(hdc, cxClient / 2 - 150, cyClient / 2, cxClient / 2 + 150, cyClient / 2 + 300, \
            cxClient / 2, cyClient / 2, cxClient / 2, cyClient / 2 + 300);

        // 将下方白色小扇形的弦覆盖
        hPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
       SelectObject(hdc, hPen);
       hOldPen = (hdc, hPen);
        MoveToEx(hdc, cxClient / 2, cyClient / 2, NULL);
        LineTo(hdc, cxClient / 2, cyClient / 2 + 300);
        SelectObject(hdc, hOldPen);

        // 上方阴鱼的眼睛
        SelectObject(hdc, GetStockObject(WHITE_BRUSH));
        Ellipse(hdc, cxClient / 2 - 50, cyClient / 2 - 200, cxClient / 2 + 50, cyClient / 2 - 100);

        // 下方阳鱼的眼睛
        SelectObject(hdc, GetStockObject(BLACK_BRUSH));
        Ellipse(hdc, cxClient / 2 - 50, cyClient / 2 + 200, cxClient / 2 + 50, cyClient / 2 + 100);

        EndPaint(hwnd, &ps);
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}
