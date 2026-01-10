#include "Player.h"
#include "Offsets.h"


template<typename T>
T Player::ReadField(Memory& mem, uintptr_t offset, T failValue) const noexcept
{
    uintptr_t addr = mem.ResolveAddress(Offsets::PlayerBase, offset);
    if (!addr)
        return failValue;

    T value{};
    mem.Read(addr, &value, sizeof(T));
    return value;
}

template<typename T>
void Player::WriteField(Memory& mem, uintptr_t offset, T value) const noexcept
{
    uintptr_t addr = mem.ResolveAddress(Offsets::PlayerBase, offset);
    if (!addr)
        return;

    mem.Write(addr, &value, sizeof(T));
}

int Player::GetTeamSide(Memory& mem) const noexcept
{
    return ReadField<int>(mem, Offsets::Team, -1);
}

int Player::GetAmmo(Memory& mem) const noexcept
{
    return ReadField<int>(mem, Offsets::Ammo, -1);
}

void Player::SetAmmo(Memory& mem, int value) const noexcept
{
    WriteField<int>(mem, Offsets::Ammo, value);
}

int Player::GetHealth(Memory& mem) const noexcept
{
    return ReadField<int>(mem, Offsets::Health, -1);
}

void Player::SetHealth(Memory& mem, int value) const noexcept
{
    WriteField<int>(mem, Offsets::Health, value);
}

int Player::GetArmor(Memory& mem) const noexcept
{
    return ReadField<int>(mem, Offsets::Armor, -1);
}

void Player::SetArmor(Memory& mem, int value) const noexcept
{
    WriteField<int>(mem, Offsets::Armor, value);
}
