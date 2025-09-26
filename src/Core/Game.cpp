#include "Game.hpp"
#include "Engine/Engine.hpp"

namespace Forradia
{
    void Game::Start() const
    {
        std::cout << "Running game\n";

        _<Engine>().Run();
    }
}
