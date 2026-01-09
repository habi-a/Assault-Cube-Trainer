#pragma once

#include <Windows.h>


class Overlay
{
public:
    Overlay() = default;
    ~Overlay();

    bool Create(HWND gameWindow);
    void Update() const;
    void RenderStart();
    void RenderEnd();
    void RenderClear();
    void DrawRect(int x, int y, int w, int h, COLORREF color) const;
    void DrawString(int x, int y, const char* text, COLORREF color) const;
    void DrawFilledRect(int x, int y, int w, int h, COLORREF color) const;

    bool IsCreated();
    int  GetWidth() const;
    int  GetHeight() const;
private:
    bool m_is_created = false;

    int m_width = 0;
    int m_height = 0;

    HWND  m_gameHwnd = nullptr;
    HWND  m_overlayHwnd = nullptr;
    HDC   m_hdc = nullptr;
    HFONT m_fontSmall = nullptr;
};
