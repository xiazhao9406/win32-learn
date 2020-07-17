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
    TCHAR szBuffer[128];
    TEXTMETRIC tm;
    RECT rect;
    static int cxChar, cyChar, iMaxWidth;
    int i, j, k, iExHeight = 1;

    switch (message)
    {
    case WM_CREATE:
        hdc = GetDC(hwnd);
        GetTextMetrics(hdc, &tm);
        cxChar = tm.tmAveCharWidth;
        cyChar = tm.tmHeight + tm.tmExternalLeading;
        ReleaseDC(hwnd, hdc);
        return 0;

    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);

        GetClientRect(hwnd, &rect);    

        TextOut(hdc, 2 * cxChar, cyChar, TEXT("9 * 9 table："), 6);

        for (i = 1; i < 10; i++)
        {
            for (j = 1, k = 1; j <= i; j++, k++)
            {
                // k 用于记录打印的横向位置
                wsprintf(szBuffer, TEXT("%d * %d = %d"), i, j, i * j);

                iMaxWidth = cxChar * 12 * k;
                if (iMaxWidth > (rect.right - rect.left))
                {
                    iExHeight++;        // 如果当前客户区宽度不足以容纳所有内容，则换行（额外添加一行）显示
                    k = 1;        // 如果添加一行，说明要从行首开始打印
                }

                TextOut(hdc, 2 * cxChar + (k - 1) * cxChar * 12, cyChar + (i + iExHeight) * cyChar, szBuffer, lstrlen(szBuffer));
            }
        }

        EndPaint(hwnd, &ps);
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}
