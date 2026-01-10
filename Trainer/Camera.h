#pragma once

#include "Memory.h"
#include "Utils.h"

#include <array>


class Camera
{
public:
    [[nodiscard]] std::array<float, 16> GetViewMatrix(Memory& mem) const noexcept;
    [[nodiscard]] bool WorldToScreen(const Vec3& pos, Vec2& out, const std::array<float, 16>& matrix, int width, int height) const noexcept;
};
