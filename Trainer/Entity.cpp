#include "Entity.h"
#include "Offsets.h"


SIZE_T Entity::GetPlayerCount(Memory& mem) const noexcept
{
    SIZE_T count{};
    mem.Read(mem.GetBase() + Offsets::PlayerCount, &count, sizeof(int));
    return count;
}

int Entity::GetTeamSide(Memory& mem, DWORD address) const noexcept
{
    int team{ -1 };
    mem.Read(address + Offsets::Team, &team, sizeof(team));
    return team;
}

int Entity::GetArmor(Memory& mem, DWORD address) const noexcept
{
    int armor{ -1 };
    mem.Read(address + Offsets::Armor, &armor, sizeof(armor));
    return armor;
}

int Entity::GetHealth(Memory& mem, DWORD address) const noexcept
{
    int hp{ -1 };
    mem.Read(address + Offsets::Health, &hp, sizeof(hp));
    return hp;
}

std::array<char, 16> Entity::GetName(Memory& mem, DWORD address) const noexcept
{
    std::array<char, 16> buffer{};
    mem.Read(address + Offsets::Name, buffer.data(), buffer.size());
    return buffer;
}

Vec3 Entity::GetPosition(Memory& mem, DWORD address) const noexcept
{
    Vec3 pos{};
    mem.Read(address + Offsets::PosX, &pos.x, sizeof(float));
    mem.Read(address + Offsets::PosY, &pos.y, sizeof(float));
    mem.Read(address + Offsets::PosZ, &pos.z, sizeof(float));
    return pos;
}

Vec3 Entity::GetHeadPosition(Memory& mem, DWORD address) const noexcept
{
    Vec3 pos{};
    mem.Read(address + Offsets::HeadPosX, &pos.x, sizeof(float));
    mem.Read(address + Offsets::HeadPosY, &pos.y, sizeof(float));
    mem.Read(address + Offsets::HeadPosZ, &pos.z, sizeof(float));
    return pos;
}

EntityInfo Entity::GetEntity(Memory& mem, DWORD listAddr, SIZE_T index) const noexcept
{
    DWORD address{};
    mem.Read(listAddr + static_cast<DWORD>(index * sizeof(DWORD)), &address, sizeof(address));

    EntityInfo out{};
    out.team = GetTeamSide(mem, address);
    out.health = GetHealth(mem, address);
    out.armor = GetArmor(mem, address);
    out.name = GetName(mem, address);
    out.coords = GetPosition(mem, address);
    out.headCoords = GetHeadPosition(mem, address);
    return out;
}

std::vector<EntityInfo> Entity::GetAllEntities(Memory& mem) const
{
    DWORD listAddr{};
    const SIZE_T count = GetPlayerCount(mem);
    mem.Read(mem.GetBase() + Offsets::EntityList, &listAddr, sizeof(listAddr));

    std::vector<EntityInfo> vec;
    vec.reserve(count);

    for (SIZE_T i = 1; i < count; ++i)
        vec.emplace_back(GetEntity(mem, listAddr, i));

    return vec;
}
