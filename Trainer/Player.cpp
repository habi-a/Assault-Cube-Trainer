#include "Player.h"


namespace Offsets
{
    constexpr uintptr_t PlayerBase = 0x0017E0A8;
    const std::vector<uintptr_t> AmmoOffsets = {
        0x140
    };
}

uintptr_t Player::ResolvePointerChain(Memory& mem, uintptr_t baseOffset, const std::vector<uintptr_t>& offsets) const
{
    uintptr_t addr = mem.GetBase() + baseOffset;

    if (!mem.Read(addr, &addr, sizeof(addr)))
        return 0;

    for (size_t i = 0; i < offsets.size(); ++i)
    {
        addr += offsets[i];

        if (i + 1 < offsets.size())
        {
            if (!mem.Read(addr, &addr, sizeof(addr)))
                return 0;
        }
    }
    return addr;
}

int Player::GetAmmo(Memory& mem) const
{
    int ammo = 0;

    uintptr_t addr = ResolvePointerChain(
        mem,
        Offsets::PlayerBase,
        Offsets::AmmoOffsets
    );

    if (!addr)
        return 0;
    mem.Read(addr, &ammo, sizeof(ammo));
    return ammo;
}

void Player::SetAmmo(Memory& mem, int value) const
{
    uintptr_t addr = ResolvePointerChain(
        mem,
        Offsets::PlayerBase,
        Offsets::AmmoOffsets
    );

    if (!addr)
        return;
    mem.Write(addr, &value, sizeof(value));
}
