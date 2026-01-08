#pragma once

#include "Memory.h"
#include "Utils.h"

#include <array>


class Camera {
public:
    std::array<float, 16> GetViewMatrix(Memory &mem);
    bool WorldToScreen(const Vec3& pos, Vec2& out, const std::array<float, 16>& matrix, int width, int height);

private:
};
