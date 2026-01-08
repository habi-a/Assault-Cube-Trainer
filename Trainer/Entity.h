#pragma once

#include "Memory.h"
#include "Utils.h"

#include <Windows.h>
#include <vector>


struct EntityInfo
{
    int  health;
    int  ammo;
    int  armor;
    char name[16];
    Vec3 coords;
    Vec3 headCoords;
};

class Entity
{
public:
    int        GetHealth(Memory& mem, DWORD entityAddress) const;
    int        GetArmor(Memory& mem, DWORD entityAddress) const;
    SIZE_T     GetPlayerCount(Memory& mem) const;
    Vec3       GetPosition(Memory& mem, DWORD entityAddress) const;
    Vec3       GetHeadPosition(Memory& mem, DWORD entityAddress) const;
    EntityInfo GetEntity(Memory& mem, DWORD entityListAddress, SIZE_T playerNumber) const;

    std::vector<EntityInfo> GetAllEntities(Memory& mem) const;
private:
};
