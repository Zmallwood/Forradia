//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "PlayerCharacter.hpp"

#include "World.hpp"

#include "WorldArea.hpp"

#include "Tile.hpp"

#include "ObjectsStack.hpp"

#include "PlayerObjectsInventory.hpp"

namespace AAK
{
    namespace Forradia::Theme0::GameplayCore
    {
        void PlayerCharacter::Initialize()
        {
            // Initialize the objects inventory.

            m_playerObjectsInventory = std::make_shared<PlayerObjectsInventory>();

            // Move to a suitable position.

            this->MoveToSuitablePosition();
        }

        void PlayerCharacter::MoveToSuitablePosition()
        {
            // Get the current world area and size.

            auto worldArea{_<World>().GetCurrentWorldArea()};

            auto size{worldArea->GetSize()};

            // Set the initial position to the center of the world area.

            m_position = {size.width / 2, size.height / 2};

            // While the position is on water.

            while (worldArea->GetTile(m_position)->GetGround() == Hash("GroundWater"))
            {
                // Move to a random position.

                m_position = {GetRandomInt(size.width), GetRandomInt(size.height)};
            }
        }

        void PlayerCharacter::MoveNorth()
        {
            // Move the player north.

            m_position.y -= 1;
        }

        void PlayerCharacter::MoveEast()
        {
            // Move the player east.

            m_position.x += 1;
        }

        void PlayerCharacter::MoveSouth()
        {
            // Move the player south.

            m_position.y += 1;
        }

        void PlayerCharacter::MoveWest()
        {
            // Move the player west.

            m_position.x -= 1;
        }

        void PlayerCharacter::AddExperience(int experience)
        {
            // Add experience to the player.

            m_experience += experience;
        }
    }
}