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
    MSG          msg{};
    HWND         menu_window;
    HWND         game_window;

    if (!mem.Attach(L"ac_client.exe", PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION))
    {
        MessageBox(nullptr, L"Impossible d'attacher le process ac_client.exe, le jeu est il lancé ?", L"Erreur", MB_ICONERROR | MB_OK);
        return EXIT_FAILURE;
    }

    game_window = FindWindowW(nullptr, L"AssaultCube");
    if (!game_window)
    {
        MessageBox(nullptr, L"Impossible de trouver la fenêtre du jeu AssaultCube, le jeu est il lancé ?", L"Erreur", MB_ICONERROR | MB_OK);
        return EXIT_FAILURE;
    }
    overlay.Create(game_window);

    menu_window = CreateTrainerUI(hInstance, &cheats);
    if (!menu_window)
    {
        MessageBox(nullptr, L"Impossible de créer l'interface", L"Erreur", MB_ICONERROR | MB_OK);
        return EXIT_FAILURE;
    }

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return EXIT_SUCCESS;
}
