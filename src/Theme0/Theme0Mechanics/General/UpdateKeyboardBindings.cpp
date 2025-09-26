#include "UpdateKeyboardBindings.hpp"
#include "Core/Input/Keyboard/KeyboardInput.hpp"
#include "Theme0/Theme0Mechanics/CoreGameObjects/Player.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/World.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/WorldArea.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/Tile.hpp"

namespace Forradia
{
    void UpdateKeyboardBindings()
    {
        if (_<KeyboardInput>().KeyIsPressedPickResult(SDLK_1))
        {
            auto worldArea{_<World>().GetCurrentWorldArea()};

            auto tile{worldArea->GetTile(_<Player>().GetPosition())};

            tile->SetElevation(tile->GetElevation() + 1);
        }
        else if (_<KeyboardInput>().KeyIsPressedPickResult(SDLK_2))
        {
            auto worldArea{_<World>().GetCurrentWorldArea()};

            auto tile{worldArea->GetTile(_<Player>().GetPosition())};

            tile->SetElevation(tile->GetElevation() - 1);
        }
    }
}