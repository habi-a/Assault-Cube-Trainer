#pragma once

#include <cmath>


struct Vec2
{
    float x{};
    float y{};

    constexpr Vec2() = default;
    constexpr Vec2(float _x, float _y) : x(_x), y(_y) {}
};

struct Vec3
{
    float x{};
    float y{};
    float z{};

    constexpr Vec3() = default;
    constexpr Vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};
