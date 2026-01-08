#include "Overlay.h"


Overlay::~Overlay()
{
    if (m_overlayHwnd)
    {
        DestroyWindow(m_overlayHwnd);
        m_overlayHwnd = nullptr;
    }
}

bool Overlay::IsCreated()
{
    return m_is_created;
}

int Overlay::GetWidth() const
{ 
    return m_width;
}

int Overlay::GetHeight() const
{ 
    return m_height;
}

bool Overlay::Create(HWND gameWindow)
{
    RECT r;

    m_gameHwnd = gameWindow;
    if (!m_gameHwnd)
        return false;

    GetWindowRect(m_gameHwnd, &r);
    m_overlayHwnd = CreateWindowEx(
        WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TRANSPARENT,
        L"STATIC",
        nullptr,
        WS_POPUP,
        r.left, r.top,
        r.right - r.left,
        r.bottom - r.top,
        nullptr,
        nullptr,
        nullptr,
        nullptr
    );

    if (!m_overlayHwnd)
        return false;
    SetLayeredWindowAttributes(m_overlayHwnd, RGB(0, 0, 0), 255, LWA_COLORKEY | LWA_ALPHA);
    ShowWindow(m_overlayHwnd, SW_SHOW);
    m_is_created = true;
    m_width = r.right - r.left;
    m_height = r.bottom - r.top;
    return true;
}


void Overlay::Update()
{
    RECT r;

    if (!m_gameHwnd || !m_overlayHwnd)
        return;
    GetWindowRect(m_gameHwnd, &r);
    MoveWindow(
        m_overlayHwnd,
        r.left, r.top,
        r.right - r.left,
        r.bottom - r.top,
        TRUE
    );
}


void Overlay::RenderStart()
{
    if (!m_overlayHwnd)
        return;

    m_hdc = GetDC(m_overlayHwnd);
}

void Overlay::RenderEnd()
{
    if (m_overlayHwnd && m_hdc)
    {
        ReleaseDC(m_overlayHwnd, m_hdc);
        m_hdc = nullptr;
    }
}

void Overlay::RenderClear()
{
    RECT r;

    if (!m_hdc)
        return;
    GetClientRect(m_overlayHwnd, &r);
    FillRect(m_hdc, &r, (HBRUSH)GetStockObject(BLACK_BRUSH));
}

void Overlay::DrawRect(int x, int y, int w, int h, COLORREF color)
{
    if (!m_hdc)
        return;

    HPEN pen = CreatePen(PS_SOLID, 1, color);
    HBRUSH brush = (HBRUSH)GetStockObject(NULL_BRUSH);
    HGDIOBJ oldPen = SelectObject(m_hdc, pen);
    HGDIOBJ oldBrush = SelectObject(m_hdc, brush);

    Rectangle(m_hdc, x, y, x + w, y + h);
    SelectObject(m_hdc, oldPen);
    SelectObject(m_hdc, oldBrush);
    DeleteObject(pen);
}
