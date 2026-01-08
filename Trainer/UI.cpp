#include "UI.h"


LRESULT CALLBACK UIPrc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    CheatManager* cheats;

    switch (msg)
    {
        case WM_COMMAND:
            if (HIWORD(wParam) != BN_CLICKED)
                break;

            cheats = reinterpret_cast<CheatManager*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
            if (!cheats)
                break;
            if (LOWORD(wParam) == ID_CHECKBOX_AMMO)
            {
                bool checked =
                    SendMessage((HWND)lParam, BM_GETCHECK, 0, 0) == BST_CHECKED;
                cheats->EnableInfiniteAmmo(checked);
            }
            else if (LOWORD(wParam) == ID_CHECKBOX_HEALTH)
            {
                bool checked =
                    SendMessage((HWND)lParam, BM_GETCHECK, 0, 0) == BST_CHECKED;
                cheats->EnableInfiniteHealth(checked);
            }
            else if (LOWORD(wParam) == ID_CHECKBOX_ARMOR)
            {
                bool checked =
                    SendMessage((HWND)lParam, BM_GETCHECK, 0, 0) == BST_CHECKED;
                cheats->EnableInfiniteArmor(checked);
            }
            else if (LOWORD(wParam) == ID_CHECKBOX_ESP)
            {
                bool checked =
                    SendMessage((HWND)lParam, BM_GETCHECK, 0, 0) == BST_CHECKED;
                cheats->EnableESP(checked);
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
    HWND     hwnd;

    wc.lpfnWndProc   = UIPrc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;

    if (!RegisterClass(&wc))
        return nullptr;

    hwnd = CreateWindowEx(0, CLASS_NAME, L"AssaultCube Trainer", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 
        300, 300, nullptr, nullptr, hInstance, nullptr);
    if (!hwnd)
        return nullptr;

    SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(cheats));
    CreateWindow(L"BUTTON", L"Infinite Ammo", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, 20, 30, 200, 25, hwnd, (HMENU)ID_CHECKBOX_AMMO, hInstance, nullptr);
    CreateWindow(L"BUTTON", L"Infinite Health", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, 20, 65, 200, 25, hwnd, (HMENU)ID_CHECKBOX_HEALTH, hInstance, nullptr);
    CreateWindow(L"BUTTON", L"Infinite Armor", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, 20, 100, 200, 25, hwnd, (HMENU)ID_CHECKBOX_ARMOR, hInstance, nullptr);
    CreateWindow(L"BUTTON", L"Enable ESP", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, 20, 135, 200, 25, hwnd, (HMENU)ID_CHECKBOX_ESP, hInstance, nullptr);
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
    return hwnd;
}
