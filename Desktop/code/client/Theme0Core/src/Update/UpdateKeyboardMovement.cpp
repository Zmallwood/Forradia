/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "UpdateKeyboardMovement.hpp"
#include "NumbersUtilities.hpp"
#include "Player/Player.hpp"

namespace Forradia::Theme0 {
    auto UpdateKeyboardMovementStart(SDL_Keycode key) -> void {
        auto upPress{key == SDLK_UP};
        auto rightPress{key == SDLK_RIGHT};
        auto downPress{key == SDLK_DOWN};
        auto leftPress{key == SDLK_LEFT};
        auto wPress{key == SDLK_w};
        auto aPress{key == SDLK_a};
        auto sPress{key == SDLK_s};
        auto dPress{key == SDLK_d};
        // auto upPress{_<KeyboardInput>().KeyIsPressed(SDLK_UP)};
        // auto rightPress{_<KeyboardInput>().KeyIsPressed(SDLK_RIGHT)};
        // auto downPress{_<KeyboardInput>().KeyIsPressed(SDLK_DOWN)};
        // auto leftPress{_<KeyboardInput>().KeyIsPressed(SDLK_LEFT)};
        // auto wPress{_<KeyboardInput>().KeyIsPressed(SDLK_w)};
        // auto aPress{_<KeyboardInput>().KeyIsPressed(SDLK_a)};
        // auto sPress{_<KeyboardInput>().KeyIsPressed(SDLK_s)};
        // auto dPress{_<KeyboardInput>().KeyIsPressed(SDLK_d)};

        if (upPress || rightPress || downPress || leftPress || wPress || aPress || sPress ||
            dPress) {
            _<Theme0::Player>().SetDestination({-1, -1});
            //_<BattleSystem>().SetTargetedRobot(nullptr);
        }

        auto now{GetTicks()};

        // if (now >= _<Theme0::Player>().GetTicksLastMovement() +
        //                InvertSpeed(_<Theme0::Player>().GetMovementSpeed()) &&
        //     (upPress || rightPress || downPress || leftPress || wPress || aPress || sPress ||
        //      dPress)) {
        if (upPress || wPress)
            _<Theme0::Player>().StartMovingNorth();
        if (rightPress || dPress)
            _<Theme0::Player>().StartMovingEast();
        if (downPress || sPress)
            _<Theme0::Player>().StartMovingSouth();
        if (leftPress || aPress)
            _<Theme0::Player>().StartMovingWest();

        //_<Theme0::Player>().SetTicksLastMovement(now);
        //}
    }

    auto UpdateKeyboardMovementStop() -> void {
        _<Theme0::Player>().StopMoving();
    }
}
