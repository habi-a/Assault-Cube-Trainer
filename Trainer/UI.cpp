#include "UI.h"


static LRESULT CALLBACK UIPrc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    auto* cheats = reinterpret_cast<CheatManager*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

    switch (msg)
    {
    case WM_COMMAND:
    {
        if (!cheats || HIWORD(wParam) != BN_CLICKED)
            break;

        const bool checked = SendMessage(reinterpret_cast<HWND>(lParam), BM_GETCHECK, 0, 0) == BST_CHECKED;

        switch (LOWORD(wParam))
        {
            case UI::ID_AMMO:   cheats->EnableInfiniteAmmo(checked);   break;
            case UI::ID_HEALTH: cheats->EnableInfiniteHealth(checked); break;
            case UI::ID_ARMOR:  cheats->EnableInfiniteArmor(checked);  break;
            case UI::ID_ESP:    cheats->EnableESP(checked);            break;
            default: break;
        }
        break;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

HWND CreateTrainerUI(HINSTANCE hInstance, CheatManager* cheats)
{
    constexpr const wchar_t CLASS_NAME[] = L"AssaultCubeTrainerUI";

    WNDCLASSW wc{};
    wc.lpfnWndProc = UIPrc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    if (!RegisterClassW(&wc))
        return nullptr;

    HWND hwnd = CreateWindowExW(0,CLASS_NAME, L"AssaultCube Trainer", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 250, 230, nullptr, nullptr, hInstance, nullptr);

    if (!hwnd)
        return nullptr;

    SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(cheats));

    auto MakeCheckBox = [&](const wchar_t* txt, int id, int y)
    {
        return CreateWindowW(L"BUTTON", txt, WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, 20, y, 200, 22, hwnd, reinterpret_cast<HMENU>(id), hInstance, nullptr);
    };

    MakeCheckBox(L"Infinite Ammo", UI::ID_AMMO, 30);
    MakeCheckBox(L"Infinite Health", UI::ID_HEALTH, 60);
    MakeCheckBox(L"Infinite Armor", UI::ID_ARMOR, 90);
    MakeCheckBox(L"Enable ESP", UI::ID_ESP, 120);

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
    return hwnd;
}
