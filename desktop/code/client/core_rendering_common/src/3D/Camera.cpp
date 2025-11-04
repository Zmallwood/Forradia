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
        // Returns the camera position in world space.
        // The position is derived from the look-at point
        // with a fixed backward (−Y) and upward (+Z) offset
        // to place the camera slightly behind and above the
        // target for an angled view.

        auto point{GetLookAt()};

        point.y -= m_zoomAmount;
        point.z += m_zoomAmount;

        return point;
    }

    Point3F Camera::GetLookAt() const
    {
        // Computes the point in world space the camera
        // should
        // look at. This targets the center of the player's
        // current tile and uses the tile's elevation to set
        // Z.

        // Obtain current world area and determine its size.

        auto worldArea{
            _<Theme0::World>().GetCurrentWorldArea()};

        auto worldAreaSize{worldArea->GetSize()};

        // Rendered size of a single tile in world units.

        auto rendTileSize{
            _<Theme0::Theme0Properties>().GetTileSize()};

        // Player position in tile-space (grid indices).

        auto playerPos{
            _<Theme0::GameplayCore::PlayerCharacter>()
                .GetPosition()};

        // Multiplier mapping tile elevation to world Z
        // height.

        auto elevHeight{0.1f};

        // Elevation at the player's tile. Coordinates are
        // (currently, it would be preferred if it wasnt)
        // flipped relative to render space (width - x,
        // height - y).

        auto playerElev{
            worldArea
                ->GetTile(worldAreaSize.width - playerPos.x,
                          worldAreaSize.height -
                              playerPos.y)
                ->GetElevation()};

        // Construct the resulting look-at point in world
        // space. Again, the coordinates are (currently, it
        // would be preferred if it wasnt) flipped relative
        // to render space (width - x, height - y).

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

    void Camera::AddZoomAmountDelta(float zoomAmountDelta)
    {
        m_zoomAmount += zoomAmountDelta;

        m_zoomAmount = std::max(
            std::min(m_zoomAmount, k_maxZoomAmount),
            k_minZoomAmount);
    }
}