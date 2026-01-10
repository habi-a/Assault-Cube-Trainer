#pragma once

#include "Memory.h"
#include "Utils.h"

#include <array>
#include <vector>
#include <Windows.h>


struct EntityInfo
{
    int                  health{};
    int                  ammo{};
    int                  armor{};
    int                  team{};
    std::array<char, 16> name{};
    Vec3                 coords{};
    Vec3                 headCoords{};
};

class Entity
{
public:
    [[nodiscard]] int                      GetTeamSide(Memory& mem, DWORD entityAddress)      const noexcept;
    [[nodiscard]] int                      GetHealth(Memory& mem, DWORD entityAddress)        const noexcept;
    [[nodiscard]] int                      GetArmor(Memory& mem, DWORD entityAddress)         const noexcept;
    [[nodiscard]] SIZE_T                   GetPlayerCount(Memory& mem)                        const noexcept;
    [[nodiscard]] Vec3                     GetPosition(Memory& mem, DWORD entityAddress)      const noexcept;
    [[nodiscard]] Vec3                     GetHeadPosition(Memory& mem, DWORD entityAddress)  const noexcept;
    [[nodiscard]] std::array<char, 16>     GetName(Memory& mem, DWORD entityAddress)          const noexcept;
    [[nodiscard]] EntityInfo               GetEntity(Memory& mem, DWORD entityListAddr, SIZE_T index) const noexcept;
    [[nodiscard]] std::vector<EntityInfo>  GetAllEntities(Memory& mem)                        const;
};
