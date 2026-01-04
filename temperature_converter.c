#include <windows.h>
#include <stdio.h>

HWND hTempInput, hUnitBox, hResult;

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    char buffer[100];
    double temp, c, f, k;

    switch (msg) {
    case WM_CREATE:
        CreateWindow("STATIC", "Enter Temperature:",
                     WS_VISIBLE | WS_CHILD,
                     20, 20, 150, 20,
                     hwnd, NULL, NULL, NULL);

        hTempInput = CreateWindow("EDIT", "",
                     WS_VISIBLE | WS_CHILD | WS_BORDER,
                     20, 45, 150, 25,
                     hwnd, NULL, NULL, NULL);

        CreateWindow("STATIC", "Select Unit:",
                     WS_VISIBLE | WS_CHILD,
                     20, 80, 150, 20,
                     hwnd, NULL, NULL, NULL);

        hUnitBox = CreateWindow("COMBOBOX", "",
                     WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST,
                     20, 105, 150, 100,
                     hwnd, NULL, NULL, NULL);

        SendMessage(hUnitBox, CB_ADDSTRING, 0, (LPARAM)"Celsius");
        SendMessage(hUnitBox, CB_ADDSTRING, 0, (LPARAM)"Fahrenheit");
        SendMessage(hUnitBox, CB_ADDSTRING, 0, (LPARAM)"Kelvin");
        SendMessage(hUnitBox, CB_SETCURSEL, 0, 0);

        CreateWindow("BUTTON", "Convert",
                     WS_VISIBLE | WS_CHILD,
                     20, 145, 150, 30,
                     hwnd, (HMENU)1, NULL, NULL);

        hResult = CreateWindow("STATIC", "",
                     WS_VISIBLE | WS_CHILD,
                     20, 190, 260, 60,
                     hwnd, NULL, NULL, NULL);
        break;

    case WM_COMMAND:
        if (LOWORD(wp) == 1) {
            GetWindowText(hTempInput, buffer, 100);
            temp = atof(buffer);

            int index = SendMessage(hUnitBox, CB_GETCURSEL, 0, 0);

            if (index == 0) { // Celsius
                f = (temp * 9 / 5) + 32;
                k = temp + 273.15;
                sprintf(buffer, "Fahrenheit: %.2f\nKelvin: %.2f", f, k);
            }
            else if (index == 1) { // Fahrenheit
                c = (temp - 32) * 5 / 9;
                k = c + 273.15;
                sprintf(buffer, "Celsius: %.2f\nKelvin: %.2f", c, k);
            }
            else { // Kelvin
                c = temp - 273.15;
                f = (c * 9 / 5) + 32;
                sprintf(buffer, "Celsius: %.2f\nFahrenheit: %.2f", c, f);
            }

            SetWindowText(hResult, buffer);
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hwnd, msg, wp, lp);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR args, int ncmd) {
    WNDCLASS wc = {0};
    wc.lpszClassName = "TempConverter";
    wc.hInstance = hInst;
    wc.lpfnWndProc = WindowProcedure;

    RegisterClass(&wc);

    CreateWindow("TempConverter", "Temperature Converter",
                 WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                 300, 200, 320, 320,
                 NULL, NULL, hInst, NULL);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
