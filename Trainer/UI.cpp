#include "UI.h"


LRESULT CALLBACK UIPrc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    CheatManager* cheats;

    switch (msg)
    {
        case WM_COMMAND:
            if (LOWORD(wParam) == ID_CHECKBOX_AMMO)
            {
                cheats = reinterpret_cast<CheatManager*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

                if (cheats)
                {
                    bool checked = SendMessage((HWND)lParam, BM_GETCHECK, 0, 0) == BST_CHECKED;
                    cheats->EnableInfiniteAmmo(checked);
                }
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

HWND CreateTrainerUI(HINSTANCE hInstance, CheatManager* cheats)
{
    const wchar_t CLASS_NAME[] = L"AssaultCubeTrainerUI";

    WNDCLASS wc{};
    HWND hwnd;

    wc.lpfnWndProc = UIPrc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    if (!RegisterClass(&wc))
        return nullptr;

    hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"AssaultCube Trainer",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT,
        300, 150,
        nullptr,
        nullptr,
        hInstance,
        nullptr
    );

    if (!hwnd)
        return nullptr;

    SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(cheats));
    CreateWindow(
        L"BUTTON",
        L"Infinite Ammo",
        WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
        20, 30, 200, 25,
        hwnd,
        (HMENU)ID_CHECKBOX_AMMO,
        hInstance,
        nullptr
    );

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    return hwnd;
}
