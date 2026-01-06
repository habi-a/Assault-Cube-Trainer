#pragma once

#include "Memory.h"
#include <vector>

class Player
{
public:
    int  GetAmmo(Memory &mem) const;
    void SetAmmo(Memory &mem, int value) const;

private:
    uintptr_t ResolvePointerChain(Memory &mem, uintptr_t baseOffset, const std::vector<uintptr_t> &offsets) const;
};
