#pragma once

#include "CheatManager.h"

#define ID_CHECKBOX_AMMO 101
#define ID_CHECKBOX_HEALTH 102
#define ID_CHECKBOX_ARMOR 103

HWND CreateTrainerUI(HINSTANCE hInstance, CheatManager *cheats);
