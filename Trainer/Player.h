#pragma once

#include "Memory.h"
#include <cstdint>


class Player
{
public:
    [[nodiscard]] int  GetTeamSide(Memory& mem) const noexcept;
    [[nodiscard]] int  GetAmmo(Memory& mem) const noexcept;
    [[nodiscard]] int  GetHealth(Memory& mem) const noexcept;
    [[nodiscard]] int  GetArmor(Memory& mem) const noexcept;

    void SetAmmo(Memory& mem, int value) const noexcept;
    void SetHealth(Memory& mem, int value) const noexcept;
    void SetArmor(Memory& mem, int value) const noexcept;

private:
    template<typename T>
    [[nodiscard]] T ReadField(Memory& mem, uintptr_t offset, T failValue = T{}) const noexcept;

    template<typename T>
    void WriteField(Memory& mem, uintptr_t offset, T value) const noexcept;
};
