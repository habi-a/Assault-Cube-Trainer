#include "CheatManager.h"


CheatManager::CheatManager(Player& player, Memory& mem)
    : m_player(player), m_mem(mem)
{
    m_ammoThread = std::thread(&CheatManager::AmmoLoop, this);
}

CheatManager::~CheatManager()
{
    m_running = false;

    if (m_ammoThread.joinable())
        m_ammoThread.join();
}

void CheatManager::EnableInfiniteAmmo(bool enable)
{
    m_infiniteAmmo = enable;
}

void CheatManager::AmmoLoop()
{
    while (m_running)
    {
        if (m_infiniteAmmo)
        {
            m_player.SetAmmo(m_mem, m_ammoFreezeValue);
        }
        Sleep(50);
    }
}
