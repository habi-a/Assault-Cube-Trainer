#include "Camera.h"
#include "Memory.h"
#include "CheatManager.h"
#include "Player.h"
#include "UI.h"

#include <Windows.h>


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
    Memory       mem;
    Entity       entity;
    Player       player;
    Overlay      overlay;
    Camera       camera;
    CheatManager cheats(entity, player, mem, overlay, camera);

    constexpr const wchar_t* kProcessName = L"ac_client.exe";
    constexpr const wchar_t* kGameTitle = L"AssaultCube";

    MSG msg{};

    if (!mem.Attach(kProcessName, PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION))
    {
        MessageBoxW(
            nullptr,
            L"Impossible d'attacher le process ac_client.exe, le jeu est-il lancé ?",
            L"Erreur",
            MB_ICONERROR | MB_OK
        );
        return EXIT_FAILURE;
    }

    HWND gameWindow = FindWindowW(nullptr, kGameTitle);
    if (!gameWindow)
    {
        MessageBoxW(
            nullptr,
            L"Impossible de trouver la fenêtre AssaultCube, le jeu est-il lancé ?",
            L"Erreur",
            MB_ICONERROR | MB_OK
        );
        return EXIT_FAILURE;
    }

    if (!overlay.Create(gameWindow))
    {
        MessageBoxW(nullptr, L"Impossible de créer l'overlay", L"Erreur", MB_ICONERROR | MB_OK);
        return EXIT_FAILURE;
    }

    HWND menuWindow = CreateTrainerUI(hInstance, &cheats);
    if (!menuWindow)
    {
        MessageBoxW(nullptr, L"Impossible de créer l'interface", L"Erreur", MB_ICONERROR | MB_OK);
        return EXIT_FAILURE;
    }

    while (GetMessageW(&msg, nullptr, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    return EXIT_SUCCESS;
}
