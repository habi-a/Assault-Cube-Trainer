#include "Camera.h"
#include "Offsets.h"


std::array<float, 16> Camera::GetViewMatrix(Memory& mem)
{
    std::array<float, 16> view_matrix{};

    mem.Read(mem.GetBase() + Offsets::ViewMatrix, &view_matrix, sizeof(view_matrix));
    return view_matrix;
}

bool Camera::WorldToScreen(const Vec3& pos, Vec2& out, const std::array<float, 16>& matrix, int width, int height)
{
    float clipX = pos.x * matrix[0] + pos.y * matrix[4] + pos.z * matrix[8] + matrix[12];
    float clipY = pos.x * matrix[1] + pos.y * matrix[5] + pos.z * matrix[9] + matrix[13];
    float clipZ = pos.x * matrix[2] + pos.y * matrix[6] + pos.z * matrix[10] + matrix[14];
    float clipW = pos.x * matrix[3] + pos.y * matrix[7] + pos.z * matrix[11] + matrix[15];

    if (clipW < 0.1f)
        return false;

    float ndcX = clipX / clipW;
    float ndcY = clipY / clipW;

    out.x = (width / 2.f * ndcX) + (ndcX + width / 2.f);
    out.y = -(height / 2.f * ndcY) + (ndcY + height / 2.f);
    return true;
}
