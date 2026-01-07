#pragma once

#include "Memory.h"

class Player
{
public:
    int  GetAmmo(Memory &mem) const;
    void SetAmmo(Memory &mem, int value) const;
    int  GetHealth(Memory &mem) const;
    void SetHealth(Memory &mem, int value) const;
    int  GetArmor(Memory &mem) const;
    void SetArmor(Memory &mem, int value) const;
};
