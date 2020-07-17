#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
    static TCHAR szCaption[] = TEXT("homework");
    int result;

    do {
        do {
            result = MessageBox(NULL, TEXT("Have you seen the MessageBox?"), szCaption, MB_YESNO |
                MB_ICONQUESTION);
            if (IDNO == result) {
                MessageBox(NULL, TEXT("LOOk at me, I am right the MessageBox!"), szCaption, MB_OK
                    | MB_ICONEXCLAMATION);
            }
            else {
                break;
            }
        } while (TRUE);
        MessageBox(NULL, TEXT("enen, it is nice you see that!"), szCaption, MB_OK);
        result = MessageBox(NULL, TEXT("try again?"), szCaption, MB_RETRYCANCEL | MB_ICONQUESTION);
    } while (IDRETRY == result);

    return 0;
}