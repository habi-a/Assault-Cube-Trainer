#include "Camera.h"
#include "Offsets.h"


static constexpr float W_EPSILON = 0.1f;

std::array<float, 16> Camera::GetViewMatrix(Memory& mem) const noexcept
{
    std::array<float, 16> matrix{};
    mem.Read(mem.GetBase() + Offsets::ViewMatrix, matrix.data(), sizeof(matrix));
    return matrix;
}

bool Camera::WorldToScreen(const Vec3& pos, Vec2& out, const std::array<float, 16>& m, int width, int height) const noexcept
{
    float clipX = pos.x * m[0] + pos.y * m[4] + pos.z * m[8] + m[12];
    float clipY = pos.x * m[1] + pos.y * m[5] + pos.z * m[9] + m[13];
    float clipW = pos.x * m[3] + pos.y * m[7] + pos.z * m[11] + m[15];

    if (clipW < W_EPSILON)
        return false;

    float invW = 1.0f / clipW;
    float ndcX = clipX * invW;
    float ndcY = clipY * invW;

    out.x = (ndcX * 0.5f + 0.5f) * width;
    out.y = (1.0f - (ndcY * 0.5f + 0.5f)) * height;
    return true;
}
