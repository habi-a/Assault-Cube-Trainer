#pragma once

#include "Player.h"
#include "Memory.h"

#include <atomic>
#include <thread>


class CheatManager
{
public:
    CheatManager(Player &player, Memory &mem);
    ~CheatManager();

    void EnableInfiniteAmmo(bool enable);

private:
    void AmmoLoop();

    Player &m_player;
    Memory &m_mem;

    std::atomic<bool> m_infiniteAmmo{ false };
    std::atomic<bool> m_running{ true };
    const int         m_ammoFreezeValue = 20;
    std::thread       m_ammoThread;
};
