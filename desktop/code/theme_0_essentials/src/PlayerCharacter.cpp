//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "PlayerCharacter.hpp"

#include "World.hpp"

#include "WorldArea.hpp"

#include "Tile.hpp"

namespace Forradia
{
    namespace Theme0
    {
        namespace GameplayCore
        {
            void PlayerCharacter::Initialize()
            {
                this->MoveToSuitablePosition();
            }

            void PlayerCharacter::MoveToSuitablePosition()
            {
                auto worldArea{
                    _<World>().GetCurrentWorldArea()};

                auto size{worldArea->GetSize()};

                m_position = {size.width / 2,
                              size.height / 2};

                while (worldArea->GetTile(m_position)
                           ->GetGround() ==
                       Hash("GroundWater"))
                {
                    m_position = {
                        GetRandomInt(size.width),
                        GetRandomInt(size.height)};
                }
            }

            void PlayerCharacter::MoveNorth()
            {
                m_position.y -= 1;
            }

            void PlayerCharacter::MoveEast()
            {
                m_position.x += 1;
            }

            void PlayerCharacter::MoveSouth()
            {
                m_position.y += 1;
            }

            void PlayerCharacter::MoveWest()
            {
                m_position.x -= 1;
            }
        }
    }
}