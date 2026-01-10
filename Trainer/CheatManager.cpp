#include "Camera.h"
#include "CheatManager.h"
#include "Offsets.h"

#include <algorithm>


CheatManager::CheatManager(Entity &entity, Player &player, Memory &mem, Overlay &overlay, Camera &camera)
    : m_entity(entity), m_player(player), m_mem(mem), m_overlay(overlay), m_camera(camera)
{

    m_cheat_thread = std::thread(&CheatManager::CheatLoop, this);
}

CheatManager::~CheatManager()
{
    m_running = false;

    if (m_cheat_thread.joinable())
        m_cheat_thread.join();
}

void CheatManager::DrawEnemyBox(int teamSide, int localTeam, int x, int y, int boxW, int boxH) noexcept
{
    if (localTeam != teamSide)
        m_overlay.DrawRect(x, y, static_cast<int>(boxW), static_cast<int>(boxH), RGB(255, 0, 0));
    else if (teamSide != -1)
        m_overlay.DrawRect(x, y, static_cast<int>(boxW), static_cast<int>(boxH), RGB(0, 128, 255));
}

void CheatManager::DrawEnemyName(const std::array<char, 16> &name, int x, int y, int boxW) noexcept
{
    int textX = x + boxW / 2 - 12;
    int textY = y - 14;

    m_overlay.DrawString(textX, textY, name.data(), RGB(255, 255, 255));
}

void CheatManager::DrawEnemyHealth(int health, int x, int y, int boxW, int boxH) noexcept
{
    float pct  = std::clamp(health / 100.0f, 0.0f, 1.0f);
    int barX   = x - 6;
    int barY   = y;
    int barW   = 4;
    int barH   = boxH;
    int greenH = static_cast<int>(barH * pct);
    int redH   = barH - greenH;

    m_overlay.DrawFilledRect(barX, barY, barW, redH, RGB(255, 0, 0));
    m_overlay.DrawFilledRect(barX, barY + redH, barW, greenH, RGB(0, 255, 0));
}

void CheatManager::DrawESP() noexcept
{
    auto view = m_camera.GetViewMatrix(m_mem);
    auto enemies = m_entity.GetAllEntities(m_mem);

    const int localTeam = m_player.GetTeamSide(m_mem);

    for (const auto& e : enemies)
    {
        if (e.health <= 0) continue;

        Vec2 screen{}, head{};
        if (!m_camera.WorldToScreen(e.coords, screen, view, m_overlay.GetWidth(), m_overlay.GetHeight())) continue;
        if (!m_camera.WorldToScreen(e.headCoords, head, view, m_overlay.GetWidth(), m_overlay.GetHeight())) continue;

        float h = screen.y - head.y;
        float w = h * 0.5f;

        int x = static_cast<int>(head.x - w * 0.5f);
        int y = static_cast<int>(head.y);

        DrawEnemyBox(e.team, localTeam, x, y, static_cast<int>(w), static_cast<int>(h));
        DrawEnemyName(e.name, x, y, static_cast<int>(w));
        DrawEnemyHealth(e.health, x, y, static_cast<int>(w), static_cast<int>(h));
    }
}

void CheatManager::CheatLoop() noexcept
{
    while (m_running)
    {
        if (m_infiniteAmmo)   m_player.SetAmmo(m_mem, AmmoFreeze);
        if (m_infiniteHealth) m_player.SetHealth(m_mem, HPFreeze);
        if (m_infiniteArmor)  m_player.SetArmor(m_mem, ArmorFreeze);

        if (m_overlay.IsCreated())
        {
            m_overlay.Update();
            m_overlay.RenderStart();
            m_overlay.RenderClear();

            if (m_esp_is_enabled)
                DrawESP();

            m_overlay.RenderEnd();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(8));
    }
}
