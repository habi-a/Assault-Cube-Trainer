#include "Entity.h"

namespace Offsets
{
    namespace Entity
    {
        constexpr uintptr_t Position = 0x00; // X, Y, Z (à confirmer)
        constexpr uintptr_t Health = 0x14; // à confirmer
    }
}

bool Entity::GetPosition(Memory& mem, uintptr_t entityBase, Vec3& outPos) const
{
    if (!entityBase)
        return false;

    return mem.Read(
        entityBase + Offsets::Entity::Position,
        &outPos,
        sizeof(outPos)
    );
}

bool Entity::GetHealth(Memory& mem, uintptr_t entityBase, int& outHealth) const
{
    if (!entityBase)
        return false;

    return mem.Read(
        entityBase + Offsets::Entity::Health,
        &outHealth,
        sizeof(outHealth)
    );
}
