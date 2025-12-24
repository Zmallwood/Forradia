/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "TileHovering.hpp"
#include "3D/Camera.hpp"
#include "MouseUtilities.hpp"
#include "Player/Player.hpp"
#include "GraphicsDevices/SDLDevice.hpp"
#include "Theme0Properties.hpp"
#include "Tile.hpp"
#include "World.hpp"
#include "WorldArea.hpp"
#include <glm/gtx/intersect.hpp>

namespace Forradia::Theme0
{
    auto TileHovering::update() -> void
    {
        TileHovering::determineHoveredCoordinateWithRayCasting();
    }

    auto TileHovering::determineHoveredCoordinateWithRayCasting() -> void
    {
        TileHovering::iterateOverRenderedTiles();
    }

    auto TileHovering::iterateOverRenderedTiles() -> void
    {
        auto worldArea{World::instance().getCurrentWorldArea()};
        auto playerPos{Player::instance().getPosition()};
        auto gridSize{Theme0Properties::instance().getGridSize()};

        // Iterate over the rendered tiles.
        for (auto yPos = 0; yPos < gridSize.height; yPos++)
        {
            for (auto xPos = 0; xPos < gridSize.width; xPos++)
            {
                auto xCoordinate{playerPos.x - (gridSize.width - 1) / 2 + xPos};
                auto yCoordinate{playerPos.y - (gridSize.height - 1) / 2 + yPos};

                if (TileHovering::determineIfTileIsHovered(xCoordinate, yCoordinate))
                {
                    m_hoveredCoordinate = {xCoordinate, yCoordinate};

                    return;
                }
            }
        }
    }

    auto TileHovering::determineIfTileIsHovered(int xCoordinate, int yCoordinate) -> bool
    {
        auto result{TileHovering::checkIfRayIntersectsTile(xCoordinate, yCoordinate)};

        return result;
    }

    auto TileHovering::checkIfRayIntersectsTile(int xCoordinate, int yCoordinate) -> bool
    {
        auto mousePos{getNormalizedMousePosition(SDLDevice::instance().getWindow())};

        // Get camera matrices.
        auto viewMatrix{Camera::instance().getViewMatrix()};
        auto projectionMatrix{Camera::getProjectionMatrix()};

        // Get inverse view-projection matrix for unprojecting.
        auto inverseViewProjection{glm::inverse(projectionMatrix * viewMatrix)};

        // Convert normalized mouse coordinates to clip space (normalized coordinates are in
        // range
        // [-1, 1]).

        // NOLINTNEXTLINE(readability-magic-numbers)
        glm::vec4 nearPoint{mousePos.x * 2.0F - 1.0F, mousePos.y * 2.0F - 1.0F, -1.0F, 1.0F};

        // NOLINTNEXTLINE(readability-magic-numbers)
        glm::vec4 farPoint{mousePos.x * 2.0F - 1.0F, mousePos.y * 2.0F - 1.0F, 1.0F, 1.0F};

        // Unproject to world space.
        nearPoint = inverseViewProjection * nearPoint;
        farPoint = inverseViewProjection * farPoint;

        // Perspective divide.
        // NOLINTNEXTLINE(readability-magic-numbers)
        if (std::abs(nearPoint.w) > 0.0001F)
        {
            nearPoint /= nearPoint.w;
        }

        // NOLINTNEXTLINE(readability-magic-numbers)
        if (std::abs(farPoint.w) > 0.0001F)
        {
            farPoint /= farPoint.w;
        }

        // Compute ray origin and direction.
        glm::vec3 rayOrigin{nearPoint.x, nearPoint.y, nearPoint.z};
        glm::vec3 rayDir{glm::normalize(glm::vec3(farPoint.x, farPoint.y, farPoint.z) - rayOrigin)};

        // Get the world area.
        auto worldArea{World::instance().getCurrentWorldArea()};

        // Get the tile coordinates.
        auto coordinateNW{Point{xCoordinate, yCoordinate}};
        auto coordinateNE{Point{xCoordinate + 1, yCoordinate}};
        auto coordinateSW{Point{xCoordinate, yCoordinate + 1}};
        auto coordinateSE{Point{xCoordinate + 1, yCoordinate + 1}};

        // Check if coordinates are valid.
        if (!worldArea->isValidCoordinate(coordinateNW) ||
            !worldArea->isValidCoordinate(coordinateNE) ||
            !worldArea->isValidCoordinate(coordinateSW) ||
            !worldArea->isValidCoordinate(coordinateSE))
        {
            return false;
        }

        // Get the tiles.
        auto tileNW{worldArea->getTile(coordinateNW)};
        auto tileNE{worldArea->getTile(coordinateNE)};
        auto tileSW{worldArea->getTile(coordinateSW)};
        auto tileSE{worldArea->getTile(coordinateSE)};

        // Get the elevations.
        auto elevationNW{tileNW ? tileNW->getElevation() : 0.0F};
        auto elevationNE{tileNE ? tileNE->getElevation() : 0.0F};
        auto elevationSW{tileSW ? tileSW->getElevation() : 0.0F};
        auto elevationSE{tileSE ? tileSE->getElevation() : 0.0F};

        // Get tile size and elevation height.
        auto tileSize{Theme0Properties::instance().getTileSize()};
        auto elevationHeight{Theme0Properties::instance().getElevationHeight()};

        // Convert tile coordinates to world space positions.
        auto worldXNW{xCoordinate * tileSize - tileSize / 2};
        auto worldYNW{yCoordinate * tileSize - tileSize / 2};
        auto worldXNE{(xCoordinate + 1) * tileSize - tileSize / 2};
        auto worldYNE{yCoordinate * tileSize - tileSize / 2};
        auto worldXSW{xCoordinate * tileSize - tileSize / 2};
        auto worldYSW{(yCoordinate + 1) * tileSize - tileSize / 2};
        auto worldXSE{(xCoordinate + 1) * tileSize - tileSize / 2};
        auto worldYSE{(yCoordinate + 1) * tileSize - tileSize / 2};

        // Create 3D vertices for the tile quad.
        glm::vec3 vertNW{worldXNW, worldYNW, elevationNW * elevationHeight};
        glm::vec3 vertNE{worldXNE, worldYNE, elevationNE * elevationHeight};
        glm::vec3 vertSW{worldXSW, worldYSW, elevationSW * elevationHeight};
        glm::vec3 vertSE{worldXSE, worldYSE, elevationSE * elevationHeight};

        // Test intersection with two triangles that make up the quad Triangle 1: NW -> NE ->
        // SE.

        glm::vec2 baryPosition1;
        float distance1;

        auto intersects1{glm::intersectRayTriangle(rayOrigin, rayDir, vertNW, vertNE, vertSE,
                                                   baryPosition1, distance1)};

        // Triangle 2: NW -> SE -> SW.

        glm::vec2 baryPosition2;
        float distance2;

        auto intersects2{glm::intersectRayTriangle(rayOrigin, rayDir, vertNW, vertSE, vertSW,
                                                   baryPosition2, distance2)};

        // Return the result of the intersection tests.
        return intersects1 || intersects2;
    }
}
