#pragma once

#include "Memory.h"

#include <Windows.h>


struct Vec3
{
    float x;
    float y;
    float z;
};

class Entity
{
public:
    void PrintHealth(Memory& mem) const;
    //bool GetPosition(Memory &mem, Vec3 &outPos) const;
    //bool GetHealth(Memory &mem, int &outHealth) const;
private:
    SIZE_T GetPlayerCount(Memory& mem) const;
    int GetHealthByEntity(Memory& mem, DWORD entity_address) const;
};
