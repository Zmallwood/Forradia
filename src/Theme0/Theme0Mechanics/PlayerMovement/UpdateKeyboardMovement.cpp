#include "UpdateKeyboardMovement.hpp"
#include "Theme0/Theme0Mechanics/CoreGameObjects/Player.hpp"
#include "Core/Input/Keyboard/KeyboardInput.hpp"

namespace Forradia
{
    void UpdateKeyboardMovement()
    {
        auto upPressed{_<KeyboardInput>().KeyIsPressed(SDLK_UP)};
        auto rightPressed{_<KeyboardInput>().KeyIsPressed(SDLK_RIGHT)};
        auto downPressed{_<KeyboardInput>().KeyIsPressed(SDLK_DOWN)};
        auto leftPressed{_<KeyboardInput>().KeyIsPressed(SDLK_LEFT)};

        auto now{GetTicks()};

        if (now >= _<Player>().GetTicksLastMove() + InvertMovementSpeed(_<Player>().GetMovementSpeed()) && (upPressed || rightPressed || downPressed || leftPressed))
        {
            if (upPressed)
            {
                _<Player>().MoveNorth();
            }

            if (rightPressed)
            {
                _<Player>().MoveEast();
            }

            if (downPressed)
            {
                _<Player>().MoveSouth();
            }

            if (leftPressed)
            {
                _<Player>().MoveWest();
            }

            _<Player>().SetTicksLastMove(now);
        }
    }
}