#include "Offsets.h"
#include "Player.h"

int Player::GetTeamSide(Memory& mem) const
{
    int team_side = -1;
    uintptr_t addr = mem.ResolveAddress(Offsets::PlayerBase, Offsets::Team);

    if (!addr)
        return team_side;
    mem.Read(addr, &team_side, sizeof(team_side));
    return team_side;
}

int Player::GetAmmo(Memory &mem) const
{
    int ammo = -1;
    uintptr_t addr = mem.ResolveAddress(Offsets::PlayerBase, Offsets::Ammo);

    if (!addr)
        return ammo;
    mem.Read(addr, &ammo, sizeof(ammo));
    return ammo;
}

void Player::SetAmmo(Memory &mem, int value) const
{
    uintptr_t addr = mem.ResolveAddress(Offsets::PlayerBase, Offsets::Ammo);

    if (!addr)
        return;
    mem.Write(addr, &value, sizeof(value));
}

int Player::GetHealth(Memory &mem) const
{
    int health = -1;
    uintptr_t addr = mem.ResolveAddress(Offsets::PlayerBase, Offsets::Health);

    if (!addr)
        return health;
    mem.Read(addr, &health, sizeof(health));
    return health;
}

void Player::SetHealth(Memory &mem, int value) const
{
    uintptr_t addr = mem.ResolveAddress(Offsets::PlayerBase, Offsets::Health);

    if (!addr)
        return;
    mem.Write(addr, &value, sizeof(value));
}

int Player::GetArmor(Memory &mem) const
{
    int armor = -1;
    uintptr_t addr = mem.ResolveAddress(Offsets::PlayerBase, Offsets::Armor);

    if (!addr)
        return armor;
    mem.Read(addr, &armor, sizeof(armor));
    return armor;
}

void Player::SetArmor(Memory &mem, int value) const
{
    uintptr_t addr = mem.ResolveAddress(Offsets::PlayerBase, Offsets::Armor);

    if (!addr)
        return;
    mem.Write(addr, &value, sizeof(value));
}
