#pragma once

#include "Memory.h"
#include "Utils.h"

#include <array>
#include <Windows.h>
#include <vector>

struct EntityInfo
{
    int                  health;
    int                  ammo;
    int                  armor;
    int                  team;
    std::array<char, 16> name;
    Vec3                 coords;
    Vec3                 headCoords;
};

class Entity
{
public:
    int                      GetTeamSide(Memory& mem, DWORD entity_address) const;
    int                      GetHealth(Memory& mem, DWORD entityAddress) const;
    int                      GetArmor(Memory& mem, DWORD entityAddress) const;
    SIZE_T                   GetPlayerCount(Memory& mem) const;
    Vec3                     GetPosition(Memory& mem, DWORD entityAddress) const;
    std::array<char, 16>     GetName(Memory& mem, DWORD entity_address) const;
    Vec3                     GetHeadPosition(Memory& mem, DWORD entityAddress) const;
    EntityInfo               GetEntity(Memory& mem, DWORD entityListAddress, SIZE_T playerNumber) const;
    std::vector<EntityInfo>  GetAllEntities(Memory& mem) const;
private:
};
