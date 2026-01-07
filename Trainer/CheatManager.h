#pragma once

#include "Entity.h"
#include "Player.h"
#include "Memory.h"

#include <atomic>
#include <thread>


class CheatManager
{
public:
    CheatManager(Entity &entity, Player &player, Memory &mem);
    ~CheatManager();

    void EnableInfiniteAmmo(bool enable);
    void EnableInfiniteHealth(bool enable);
    void EnableInfiniteArmor(bool enable);
    void EnableESP(bool enable);
private:
    void CheatLoop();

    Entity &m_entity;
    Player &m_player;
    Memory &m_mem;

    std::atomic<bool> m_running{ true };
    std::thread       m_cheat_thread;

    std::atomic<bool> m_infiniteAmmo{ false };
    const int         m_ammoFreezeValue = 20;

    std::atomic<bool> m_infiniteHealth{ false };
    const int         m_healthFreezeValue = 100;

    std::atomic<bool> m_infiniteArmor{ false };
    const int         m_armorFreezeValue = 100;

    std::atomic<bool> m_esp_is_enabled{ false };
};
