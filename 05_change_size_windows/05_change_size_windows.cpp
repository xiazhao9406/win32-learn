﻿#include <windows.h>
#include <windowsx.h>
#include "strsafe.h"
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
    RECT rect;
    size_t iTarget;
    TCHAR szBuffer[128];
    static int cxClient, cyClient;

    switch (message)
    {
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        StringCchPrintf(szBuffer, 128, TEXT("客户区当前分辨率是：%d * %d px"), cxClient, cyClient);
        StringCchLength(szBuffer, 128, &iTarget);
        TextOut(hdc, 10, 10, szBuffer, iTarget);
        EndPaint(hwnd, &ps);
        return 0;
// the change part
    case WM_SIZE:
        if (SIZE_MAXIMIZED == wParam)
            MessageBox(hwnd, TEXT("窗口被最大化"), TEXT("提示"), MB_OK);
        if (SIZE_MINIMIZED == wParam)
            MessageBox(hwnd, TEXT("窗口被最小化"), TEXT("提示"), MB_OK);
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}

