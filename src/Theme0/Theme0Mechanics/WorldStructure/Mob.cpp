#include "Mob.hpp"

namespace Forradia
{
    Mob::Mob(std::string_view typeName)
        : m_type{Hash(typeName)}
    {
        m_movementSpeed *= (RandomInt( 3 ) + 1) / 2.0f;
    }
}