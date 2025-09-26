#include "Game.hpp"
#include "Engine/Engine.hpp"

namespace Forradia
{
    void Game::Start() const
    {
        _<Engine>().Run();
    }
}
