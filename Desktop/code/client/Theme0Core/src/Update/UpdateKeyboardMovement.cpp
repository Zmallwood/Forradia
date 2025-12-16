//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#include "UpdateKeyboardMovement.hpp"
#include "Keyboard/KeyboardInput.hpp"
#include "NumbersUtilities.hpp"
#include "Player/PlayerCharacter.hpp"
#include "Update/BattleSystem.hpp"

namespace Forradia::Theme0::GameplayCore {
    void UpdateKeyboardMovement() {
        auto upPress{_<KeyboardInput>().KeyIsPressed(SDLK_UP)};

        auto rightPress{_<KeyboardInput>().KeyIsPressed(SDLK_RIGHT)};

        auto downPress{_<KeyboardInput>().KeyIsPressed(SDLK_DOWN)};

        auto leftPress{_<KeyboardInput>().KeyIsPressed(SDLK_LEFT)};

        auto wPress{_<KeyboardInput>().KeyIsPressed(SDLK_w)};

        auto aPress{_<KeyboardInput>().KeyIsPressed(SDLK_a)};

        auto sPress{_<KeyboardInput>().KeyIsPressed(SDLK_s)};

        auto dPress{_<KeyboardInput>().KeyIsPressed(SDLK_d)};

        if (upPress || rightPress || downPress || leftPress || wPress || aPress || sPress ||
            dPress) {
            _<Theme0::GameplayCore::PlayerCharacter>().SetDestination({-1, -1});

            _<GameplayCore::BattleSystem>().SetTargetedRobot(nullptr);
        }

        auto now{GetTicks()};

        if (now >= _<Theme0::GameplayCore::PlayerCharacter>().GetTicksLastMovement() +
                       InvertSpeed(_<Theme0::GameplayCore::

                                         PlayerCharacter>()
                                       .GetMovementSpeed()) &&
            (upPress || rightPress || downPress || leftPress || wPress || aPress || sPress ||
             dPress)) {
            if (upPress || wPress) {
                _<Theme0::GameplayCore::PlayerCharacter>().MoveNorth();
            }

            if (rightPress || dPress) {
                _<Theme0::GameplayCore::PlayerCharacter>().MoveEast();
            }

            if (downPress || sPress) {
                _<Theme0::GameplayCore::PlayerCharacter>().MoveSouth();
            }

            if (leftPress || aPress) {
                _<Theme0::GameplayCore::PlayerCharacter>().MoveWest();
            }

            _<Theme0::GameplayCore::PlayerCharacter>().SetTicksLastMovement(now);
        }
    }
}