#pragma once

#include "Bypass.h"

class Player
{
public:
	explicit Player(uintptr_t moduleBase);

	int  GetAmmo(Bypass &mem) const;
	void SetAmmo(Bypass &mem, int value) const;

private:
	uintptr_t ResolveAmmoAddress(Bypass& mem) const;
	uintptr_t m_moduleBase;
};
