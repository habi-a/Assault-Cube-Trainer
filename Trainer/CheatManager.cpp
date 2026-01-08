#include "Camera.h"
#include "CheatManager.h"


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

void CheatManager::DrawESP()
{
    std::array<float, 16> view_matrix = m_camera.GetViewMatrix(m_mem);
    std::vector<EntityInfo> ennemies_info = m_entity.GetAllEntities(m_mem);

    for (EntityInfo &ennemy : ennemies_info)
    {
        Vec2 ennemy_screen      = {};
        Vec2 ennemy_screen_head = {};
        if (m_camera.WorldToScreen(ennemy.coords, ennemy_screen, view_matrix, m_overlay.GetWidth(), m_overlay.GetHeight())
            && m_camera.WorldToScreen(ennemy.headCoords, ennemy_screen_head, view_matrix, m_overlay.GetWidth(), m_overlay.GetHeight())) {
            float boxHeight = (ennemy_screen.y - ennemy_screen_head.y);
            float boxWidth = boxHeight * 0.45f;

            m_overlay.DrawRect(
                static_cast<int>(ennemy_screen_head.x - boxWidth * 0.5f),
                static_cast<int>(ennemy_screen_head.y),
                static_cast<int>(boxWidth),
                static_cast<int>(boxHeight),
                RGB(255, 0, 0)
            );
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
        Sleep(10);
    }
}
