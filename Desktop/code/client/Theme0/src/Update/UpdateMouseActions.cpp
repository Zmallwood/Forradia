//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "UpdateMouseActions.hpp"

#include "Mouse/MouseInput.hpp"

#include "GUIInteractionMenu/GUIInteractionMenu.hpp"

#include "SDLDevice.hpp"

#include "Player/PlayerCharacter.hpp"

#include "Update/BattleSystem.hpp"

#include "Update/TileHovering.hpp"

#include "World.hpp"

#include "WorldArea.hpp"

#include "Tile.hpp"

namespace AAK
{
    namespace Forradia::Theme0::GameplayCore
    {
        void UpdateMouseActions()
        {
            if (_<MouseInput>().GetRightMouseButtonRef().HasBeenReleased() &&
                _<MouseInput>().GetRightMouseButtonRef().GetTicksClickSpeed() < 200)
            {
                auto currentPlayerMode{_<PlayerCharacter>().GetPlayerMode()};

                switch (currentPlayerMode)
                {
                case PlayerModes::Interaction:

                    _<GUIInteractionMenu>().BuildMenu();

                    _<GUIInteractionMenu>().SetVisible(true);

                    _<GUIInteractionMenu>().SetPosition(
                        GetNormallizedMousePosition(_<SDLDevice>().GetWindow()));
                    break;
                case PlayerModes::Battle:

                    auto currentWorldArea{_<World>().GetCurrentWorldArea()};

                    auto hoveredTile{
                        currentWorldArea->GetTile(_<TileHovering>().GetHoveredCoordinate())};

                    if (hoveredTile)
                    {
                        auto robot{hoveredTile->GetRobot()};

                        if (robot)
                        {
                            _<GameplayCore::BattleSystem>().SetTargetedRobot(robot);
                        }
                    }

                    break;
                }
            }
        }
    }
}