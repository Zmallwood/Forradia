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

#include "ObjectsInventory.hpp"

namespace Forradia::Theme0::GameplayCore
{
    void PlayerCharacter::Initialize()
    {
        m_objectsInventory =
            std::make_shared<ObjectsInventory>();

        this->MoveToSuitablePosition();

        auto worldArea{_<World>().GetCurrentWorldArea()};

        auto size{worldArea->GetSize()};

        worldArea
            ->GetTile(size.width - m_position.x,
                      size.height - m_position.y - 1)
            ->GetObjectsStack()
            ->AddObject("ObjectComputer");
    }

    void PlayerCharacter::MoveToSuitablePosition()
    {
        auto worldArea{_<World>().GetCurrentWorldArea()};

        auto size{worldArea->GetSize()};

        m_position = {size.width / 2, size.height / 2};

        while (
            worldArea->GetTile(m_position)->GetGround() ==
            Hash("GroundWater"))
        {
            m_position = {GetRandomInt(size.width),
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