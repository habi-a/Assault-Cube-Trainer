#pragma once

#include <Windows.h>
#include <string>
#include <utility>


class Overlay
{
public:
    Overlay() noexcept = default;
    ~Overlay() noexcept;

    [[nodiscard]] bool Create(HWND gameWindow) noexcept;
    void Update() const noexcept;
    void RenderStart() noexcept;
    void RenderEnd() noexcept;
    void RenderClear() noexcept;

    void DrawRect(int x, int y, int w, int h, COLORREF color) const noexcept;
    void DrawFilledRect(int x, int y, int w, int h, COLORREF color) const noexcept;
    void DrawString(int x, int y, const char* text, COLORREF color) const noexcept;

    [[nodiscard]] bool IsCreated() const noexcept { return m_is_created; }
    [[nodiscard]] int  GetWidth()  const noexcept { return m_width; }
    [[nodiscard]] int  GetHeight() const noexcept { return m_height; }

private:
    bool  m_is_created = false;
    int   m_width = 0;
    int   m_height = 0;
    HWND  m_gameHwnd = nullptr;
    HWND  m_overlayHwnd = nullptr;
    HDC   m_hdc = nullptr;
    HFONT m_fontSmall = nullptr;
};
