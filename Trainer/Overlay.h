#pragma once

#include <Windows.h>


class Overlay
{
public:
    Overlay() = default;
    ~Overlay();

    bool Create(HWND gameWindow);
    void Update();
    void RenderStart();
    void RenderEnd();
    void RenderClear();
    void DrawRect(int x, int y, int w, int h, COLORREF color);

    bool IsCreated();
    int  GetWidth() const;
    int  GetHeight() const;
private:
    bool m_is_created = false;

    int m_width = 0;
    int m_height = 0;

    HWND m_gameHwnd = nullptr;
    HWND m_overlayHwnd = nullptr;
    HDC  m_hdc = nullptr;
};
