#include "Entity.h"
#include "Offsets.h"


SIZE_T Entity::GetPlayerCount(Memory &mem) const
{
    SIZE_T player_numbers = 0;

    mem.Read(mem.GetBase() + Offsets::PlayerCount , &player_numbers, sizeof(int));
    return player_numbers;
}

int Entity::GetArmor(Memory& mem, DWORD entity_address) const
{
    int armor = -1;

    mem.Read(entity_address + Offsets::Armor, &armor, sizeof(armor));
    return armor;
}

int Entity::GetHealth(Memory& mem, DWORD entity_address) const
{
    int health = -1;

    mem.Read(entity_address + Offsets::Health, &health, sizeof(health));
    return health;
}

Vec3 Entity::GetPosition(Memory &mem, DWORD entity_address) const
{
    Vec3 pos{};

    mem.Read(entity_address + Offsets::PosX, &pos.x, sizeof(float));
    mem.Read(entity_address + Offsets::PosY, &pos.y, sizeof(float));
    mem.Read(entity_address + Offsets::PosZ, &pos.z, sizeof(float));
    return pos;
}

Vec3 Entity::GetHeadPosition(Memory &mem, DWORD entity_address) const
{
    Vec3 pos{};

    mem.Read(entity_address + Offsets::HeadPosX, &pos.x, sizeof(float));
    mem.Read(entity_address + Offsets::HeadPosY, &pos.y, sizeof(float));
    mem.Read(entity_address + Offsets::HeadPosZ, &pos.z, sizeof(float));
    return pos;
}

EntityInfo Entity::GetEntity(Memory& mem, DWORD entityListAddress, SIZE_T playerNumber) const
{
    EntityInfo entity{};
    DWORD entity_address = 0;

    mem.Read(entityListAddress + playerNumber * sizeof(entity_address), &entity_address, sizeof(entity_address));

    entity.health = GetHealth(mem, entity_address);
    entity.armor = GetArmor(mem, entity_address);
    entity.coords = GetPosition(mem, entity_address);
    entity.headCoords = GetHeadPosition(mem, entity_address);
    return entity;
}

std::vector<EntityInfo> Entity::GetAllEntities(Memory& mem) const
{
    std::vector<EntityInfo> entities;
    DWORD entity_list_address = 0;
    SIZE_T player_numbers = GetPlayerCount(mem);

    mem.Read(mem.GetBase() + Offsets::EntityList, &entity_list_address, sizeof(entity_list_address));
    for (SIZE_T i = 1; i < player_numbers; ++i)
        entities.push_back(GetEntity(mem, entity_list_address, i));
    return entities;
}
