#pragma once

#include "Camera.h"
#include "Entity.h"
#include "Memory.h"
#include "Player.h"
#include "Overlay.h"

#include <array>
#include <atomic>
#include <thread>


class CheatManager {
public:
    CheatManager(Entity&, Player&, Memory&, Overlay&, Camera&);
    ~CheatManager();

    void EnableInfiniteAmmo(bool enable)    noexcept { m_infiniteAmmo = enable; }
    void EnableInfiniteHealth(bool enable)  noexcept { m_infiniteHealth = enable; }
    void EnableInfiniteArmor(bool enable)   noexcept { m_infiniteArmor = enable; }
    void EnableESP(bool enable)             noexcept { m_esp_is_enabled = enable; }

private:
    void CheatLoop() noexcept;
    void DrawESP() noexcept;
    void DrawEnemyBox(int teamSide, int localTeam, int x, int y, int w, int h) noexcept;
    void DrawEnemyName(const std::array<char, 16>& name, int x, int y, int w) noexcept;
    void DrawEnemyHealth(int hp, int x, int y, int w, int h) noexcept;

    Entity& m_entity;
    Player& m_player;
    Memory& m_mem;
    Overlay& m_overlay;
    Camera& m_camera;

    std::thread       m_cheat_thread;
    std::atomic<bool> m_running{ true };
    std::atomic<bool> m_infiniteAmmo{ false };
    std::atomic<bool> m_infiniteHealth{ false };
    std::atomic<bool> m_infiniteArmor{ false };
    std::atomic<bool> m_esp_is_enabled{ false };

    static constexpr int AmmoFreeze  = 20;
    static constexpr int HPFreeze    = 100;
    static constexpr int ArmorFreeze = 100;
};
