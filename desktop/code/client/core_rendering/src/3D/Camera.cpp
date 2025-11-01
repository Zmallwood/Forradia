//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "Camera.hpp"

#include "World.hpp"

#include "WorldArea.hpp"

#include "Tile.hpp"

#include "PlayerCharacter.hpp"

#include "Theme0Properties.hpp"

namespace Forradia
{
    Point3F Camera::GetPosition() const
    {
        auto point{GetLookAt()};

        point.y -= 2.0f;
        point.z += 1.0f;

        return point;
    }

    Point3F Camera::GetLookAt() const
    {
        auto worldArea{
            _<Theme0::World>().GetCurrentWorldArea()};

        auto worldAreaSize{worldArea->GetSize()};

        auto rendTileSize{
            _<Theme0::Theme0Properties>().GetTileSize()};

        auto playerPos{
            _<Theme0::GameplayCore::PlayerCharacter>()
                .GetPosition()};

        auto elevHeight{0.1f};

        auto playerElev{
            worldArea
                ->GetTile(worldAreaSize.width - playerPos.x,
                          worldAreaSize.height -
                              playerPos.y)
                ->GetElevation()};

        Point3F lookAt{
            (worldAreaSize.width - playerPos.x) *
                    rendTileSize +
                rendTileSize / 2,
            (worldAreaSize.height - playerPos.y) *
                    rendTileSize +
                rendTileSize / 2,
            playerElev * elevHeight};

        return lookAt;
    }
}