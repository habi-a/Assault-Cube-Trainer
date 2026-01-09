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

int CheatManager::GetGameMode() const
{
    int game_mode = 0;

    m_mem.Read(m_mem.GetBase() + Offsets::GameMode, &game_mode, sizeof(int));
    return game_mode;
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

void CheatManager::DrawEnemyBox(int team_side, int x, int y, int boxW, int boxH)
{
    if (m_player.GetTeamSide(m_mem) != team_side)
        m_overlay.DrawRect(x, y, (int)boxW, (int)boxH, RGB(255, 0, 0));
    else if (team_side != -1)
        m_overlay.DrawRect(x, y, (int)boxW, (int)boxH, RGB(0, 128, 255));
}

void CheatManager::DrawEnemyName(const std::array<char, 16> &name, int x, int y, int boxW)
{
    int textX = x + boxW / 2 - 12;
    int textY = y - 14;

    m_overlay.DrawString(textX, textY, name.data(), RGB(255, 255, 255));
}

void CheatManager::DrawEnemyHealth(int health, int x, int y, int boxW, int boxH)
{
    float pct  = std::clamp(health / 100.0f, 0.0f, 1.0f);
    int barX   = x - 6;
    int barY   = y;
    int barW   = 4;
    int barH   = boxH;
    int greenH = (int)(barH * pct);
    int redH   = barH - greenH;

    m_overlay.DrawFilledRect(barX, barY, barW, redH, RGB(255, 0, 0));
    m_overlay.DrawFilledRect(barX, barY + redH, barW, greenH, RGB(0, 255, 0));
}

void CheatManager::DrawESP()
{
    std::array<float, 16> view_matrix = m_camera.GetViewMatrix(m_mem);
    std::vector<EntityInfo> enemies_info = m_entity.GetAllEntities(m_mem);

    for (EntityInfo& enemy : enemies_info)
    {
        Vec2 screen{}, head{};
        if (m_camera.WorldToScreen(enemy.coords, screen, view_matrix, m_overlay.GetWidth(), m_overlay.GetHeight())
            && m_camera.WorldToScreen(enemy.headCoords, head, view_matrix, m_overlay.GetWidth(), m_overlay.GetHeight())
            && enemy.health > 0)
        {
            float boxH = screen.y - head.y;
            float boxW = boxH * 0.5f;

            int x = (int)(head.x - boxW * 0.5f);
            int y = (int)head.y;

            DrawEnemyBox(enemy.team, x, y, (int)boxW, (int)boxH);
            DrawEnemyName(enemy.name, x, y, (int)boxW);
            DrawEnemyHealth(enemy.health, x, y, (int)boxW, (int)boxH);
        }
    }
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
        if (m_overlay.IsCreated()) {
            m_overlay.Update();
            m_overlay.RenderStart();
            m_overlay.RenderClear();
            if (m_esp_is_enabled)
                DrawESP();
            m_overlay.RenderEnd();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}
