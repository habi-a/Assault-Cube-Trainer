#include "CheatManager.h"


CheatManager::CheatManager(Entity &entity, Player& player, Memory& mem)
    : m_entity(entity), m_player(player), m_mem(mem)
{
    m_cheat_thread = std::thread(&CheatManager::CheatLoop, this);
}

CheatManager::~CheatManager()
{
    m_running = false;

    if (m_cheat_thread.joinable())
        m_cheat_thread.join();
}

void CheatManager::EnableInfiniteAmmo(bool enable)
{
    m_infiniteAmmo = enable;
}

void CheatManager::EnableInfiniteHealth(bool enable)
{
    m_infiniteHealth = enable;
}

void CheatManager::EnableInfiniteArmor(bool enable)
{
    m_infiniteArmor = enable;
}

void CheatManager::EnableESP(bool enable)
{
    m_esp_is_enabled = enable;
}

void CheatManager::CheatLoop()
{
    while (m_running)
    {
        if (m_infiniteAmmo)
            m_player.SetAmmo(m_mem, m_ammoFreezeValue);
        if (m_infiniteHealth)
            m_player.SetHealth(m_mem, m_healthFreezeValue);
        if (m_infiniteArmor)
            m_player.SetArmor(m_mem, m_armorFreezeValue);
        if (m_esp_is_enabled)
            m_entity.PrintHealth(m_mem);
        Sleep(50);
    }
}


