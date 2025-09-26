#include "World.hpp"
#include "WorldArea.hpp"

namespace Forradia
{
    World::World()
        : m_currentWorldArea{std::make_shared<WorldArea>()}
    {
    }
}