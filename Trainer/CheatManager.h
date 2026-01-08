#pragma once

#include "Camera.h"
#include "Entity.h"
#include "Memory.h"
#include "Player.h"
#include "Overlay.h"

#include <atomic>
#include <thread>


class CheatManager
{
public:
    CheatManager(Entity &entity, Player &player, Memory &mem, Overlay &overlay, Camera &camera);
    ~CheatManager();

    void EnableInfiniteAmmo(bool enable);
    void EnableInfiniteHealth(bool enable);
    void EnableInfiniteArmor(bool enable);
    void EnableESP(bool enable);
private:
    void CheatLoop();
    void DrawESP();

    Entity  &m_entity;
    Player  &m_player;
    Memory  &m_mem;
    Overlay &m_overlay;
    Camera  &m_camera;

    std::thread       m_cheat_thread;
    std::atomic<bool> m_running{ true };
    std::atomic<bool> m_infiniteAmmo{ false };
    std::atomic<bool> m_infiniteHealth{ false };
    std::atomic<bool> m_infiniteArmor{ false };
    std::atomic<bool> m_esp_is_enabled{ false };

    const int m_ammoFreezeValue = 20;
    const int m_healthFreezeValue = 100;
    const int m_armorFreezeValue = 100;
};
