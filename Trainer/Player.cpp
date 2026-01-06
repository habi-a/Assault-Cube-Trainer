#include "Player.h"


namespace Offsets
{
    namespace LocalPlayer
    {
        constexpr uintptr_t Base   = 0x0017E0A8;
        constexpr uintptr_t Ammo   = 0x140;
        constexpr uintptr_t Health = 0xEC;
        constexpr uintptr_t Armor  = 0xF0;
        constexpr uintptr_t Name   = 0x205;
    }
}

uintptr_t Player::ResolveAddress(Memory &mem, uintptr_t fieldOffset) const
{
    uintptr_t addr = mem.GetBase() + Offsets::LocalPlayer::Base;

    if (!mem.Read(addr, &addr, sizeof(addr)))
        return 0;
    return addr + fieldOffset;
}

int Player::GetAmmo(Memory &mem) const
{
    int ammo = 0;
    uintptr_t addr = ResolveAddress(mem, Offsets::LocalPlayer::Ammo);

    if (!addr)
        return 0;
    mem.Read(addr, &ammo, sizeof(ammo));
    return ammo;
}


void Player::SetAmmo(Memory &mem, int value) const
{
    uintptr_t addr = ResolveAddress(mem, Offsets::LocalPlayer::Ammo);

    if (!addr)
        return;
    mem.Write(addr, &value, sizeof(value));
}

int Player::GetHealth(Memory &mem) const
{
    int health = 0;
    uintptr_t addr = ResolveAddress(mem, Offsets::LocalPlayer::Health);

    if (!addr)
        return 0;
    mem.Read(addr, &health, sizeof(health));
    return health;
}


void Player::SetHealth(Memory &mem, int value) const
{
    uintptr_t addr = ResolveAddress(mem, Offsets::LocalPlayer::Health);

    if (!addr)
        return;
    mem.Write(addr, &value, sizeof(value));
}

int Player::GetArmor(Memory &mem) const
{
    int armor = 0;
    uintptr_t addr = ResolveAddress(mem, Offsets::LocalPlayer::Armor);

    if (!addr)
        return 0;
    mem.Read(addr, &armor, sizeof(armor));
    return armor;
}


void Player::SetArmor(Memory &mem, int value) const
{
    uintptr_t addr = ResolveAddress(mem, Offsets::LocalPlayer::Armor);

    if (!addr)
        return;
    mem.Write(addr, &value, sizeof(value));
}
