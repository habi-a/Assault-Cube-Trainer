#pragma once

#include "Memory.h"

struct Vec3
{
    float x;
    float y;
    float z;
};

class Entity
{
public:
    bool GetPosition(Memory &mem, uintptr_t entityBase, Vec3 &outPos) const;
    bool GetHealth(Memory &mem, uintptr_t entityBase, int &outHealth) const;
private:
    int  health;
    int  ammo;
    char name[16];
    Vec3 coords;
};
