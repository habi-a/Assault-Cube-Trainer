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
    CheatManager cheats(entity, player, mem);
    HWND         hwnd;
    MSG          msg{};

    if (!mem.Attach(L"ac_client.exe", PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION))
    {
        MessageBox(nullptr, L"Impossible d'attacher le process ac_client.exe", L"Erreur", MB_ICONERROR | MB_OK);
        return EXIT_FAILURE;
    }

    hwnd = CreateTrainerUI(hInstance, &cheats);
    if (!hwnd)
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
