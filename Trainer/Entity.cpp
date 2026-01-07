#include "Entity.h"
#include "Offsets.h"


SIZE_T Entity::GetPlayerCount(Memory &mem) const
{
    SIZE_T player_numbers = 0;

    mem.Read(mem.GetBase() + Offsets::PlayerCount , &player_numbers, sizeof(int));
    return player_numbers;
}


void Entity::PrintHealth(Memory &mem) const
{
    int health;
    SIZE_T player_numbers = GetPlayerCount(mem);
    DWORD entity_list_address = 0;

    mem.Read(mem.GetBase() + Offsets::EntityList, &entity_list_address, sizeof(entity_list_address));
    for (int i = 1; i < player_numbers; ++i)
    {
        DWORD entity_address = 0;
        mem.Read(entity_list_address + i * 4, &entity_address, sizeof(entity_address));

        if (!entity_address)
            continue;
        health = -1;
        mem.Read(entity_address + Offsets::Health, &health, sizeof(health));
        char buffer[128];
        sprintf_s(buffer, "Player[%d] HP=%d\n", i, health);
        OutputDebugStringA(buffer);
    }
}
