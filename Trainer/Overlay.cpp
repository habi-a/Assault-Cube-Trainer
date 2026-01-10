#include "Overlay.h"


Overlay::~Overlay() noexcept
{
    if (m_fontSmall) {
        DeleteObject(m_fontSmall);
        m_fontSmall = nullptr;
    }

    if (m_overlayHwnd) {
        DestroyWindow(m_overlayHwnd);
        m_overlayHwnd = nullptr;
    }
}

bool Overlay::Create(HWND gameWindow) noexcept
{
    if (!gameWindow)
        return false;

    m_gameHwnd = gameWindow;
    RECT r{};
    GetWindowRect(m_gameHwnd, &r);

    m_overlayHwnd = CreateWindowExA(
        WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_NOACTIVATE, "STATIC", nullptr, WS_POPUP, r.left, r.top, r.right - r.left, r.bottom - r.top, nullptr, nullptr, nullptr, nullptr
    );

    if (!m_overlayHwnd)
        return false;

    m_fontSmall = CreateFontA(12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH, "Tahoma");

    if (!m_fontSmall)
        return false;

    SetLayeredWindowAttributes(m_overlayHwnd, RGB(0, 0, 0), 255, LWA_COLORKEY | LWA_ALPHA);
    ShowWindow(m_overlayHwnd, SW_SHOWNA);

    m_width = r.right - r.left;
    m_height = r.bottom - r.top;
    m_is_created = true;
    return true;
}

void Overlay::Update() const noexcept
{
    if (!m_gameHwnd || !m_overlayHwnd)
        return;

    RECT r{};
    GetWindowRect(m_gameHwnd, &r);
    MoveWindow(m_overlayHwnd, r.left, r.top, r.right - r.left, r.bottom - r.top, TRUE);
}

void Overlay::RenderStart() noexcept
{
    if (m_overlayHwnd)
        m_hdc = GetDC(m_overlayHwnd);
}

void Overlay::RenderEnd() noexcept
{
    if (m_overlayHwnd && m_hdc) {
        ReleaseDC(m_overlayHwnd, m_hdc);
        m_hdc = nullptr;
    }
}

void Overlay::RenderClear() noexcept
{
    if (!m_hdc)
        return;
    PatBlt(m_hdc, 0, 0, m_width, m_height, BLACKNESS);
}

void Overlay::DrawRect(int x, int y, int w, int h, COLORREF color) const noexcept
{
    if (!m_hdc)
        return;

    HPEN pen = CreatePen(PS_SOLID, 1, color);
    HGDIOBJ oldPen = SelectObject(m_hdc, pen);
    HGDIOBJ oldBrush = SelectObject(m_hdc, GetStockObject(NULL_BRUSH));

    Rectangle(m_hdc, x, y, x + w, y + h);

    SelectObject(m_hdc, oldPen);
    SelectObject(m_hdc, oldBrush);
    DeleteObject(pen);
}

void Overlay::DrawFilledRect(int x, int y, int w, int h, COLORREF color) const noexcept
{
    if (!m_hdc)
        return;

    HBRUSH brush = CreateSolidBrush(color);
    RECT r{ x, y, x + w, y + h };
    FillRect(m_hdc, &r, brush);
    DeleteObject(brush);
}

void Overlay::DrawString(int x, int y, const char* text, COLORREF color) const noexcept
{
    if (!m_hdc || !text)
        return;

    HFONT oldFont = (HFONT)SelectObject(m_hdc, m_fontSmall);
    SetTextColor(m_hdc, color);
    SetBkMode(m_hdc, TRANSPARENT);
    TextOutA(m_hdc, x, y, text, (int)strlen(text));
    SelectObject(m_hdc, oldFont);
}
