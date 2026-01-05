#include <array>

#include "Player.h"


namespace Offsets
{
	constexpr uintptr_t PlayerBase = 0x0017E0A8;

	constexpr std::array<uintptr_t, 1> Ammo = {
		0x140
	};
}

Player::Player(uintptr_t moduleBase)
	: m_moduleBase(moduleBase)
{
}

uintptr_t Player::ResolveAmmoAddress(Bypass& mem) const
{
	uintptr_t addr = m_moduleBase + Offsets::PlayerBase;

	mem.Read(addr, &addr, sizeof(addr));

	for (size_t i = 0; i < Offsets::Ammo.size(); ++i) {
		addr += Offsets::Ammo[i];

		if (i + 1 < Offsets::Ammo.size())
			mem.Read(addr, &addr, sizeof(addr));
	}
	return addr;
}

int Player::GetAmmo(Bypass& mem) const
{
	int ammo = 0;
	mem.Read(ResolveAmmoAddress(mem), &ammo, sizeof(ammo));
	return ammo;
}

void Player::SetAmmo(Bypass& mem, int value) const
{
	mem.Write(ResolveAmmoAddress(mem), &value, sizeof(value));
}
