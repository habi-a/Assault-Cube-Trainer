#pragma once

#include "CheatManager.h"
#include <Windows.h>


namespace UI
{
    constexpr int ID_AMMO = 101;
    constexpr int ID_HEALTH = 102;
    constexpr int ID_ARMOR = 103;
    constexpr int ID_ESP = 104;
}

HWND CreateTrainerUI(HINSTANCE hInstance, CheatManager* cheats);
