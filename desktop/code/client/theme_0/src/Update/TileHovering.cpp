//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "TileHovering.hpp"

#include "World.hpp"

#include "WorldArea.hpp"

#include "Tile.hpp"

#include "PlayerCharacter.hpp"

#include "Theme0Properties.hpp"

#include "SDLDevice.hpp"

#include "3D/Camera.hpp"

#include "Mouse/MouseInput.hpp"

namespace Forradia::Theme0::GameplayCore
{
    void TileHovering::Update()
    {
        DetermineHoveredCoordinateWithRaycasting();
    }

    void
    TileHovering::DetermineHoveredCoordinateWithRaycasting()
    {
        IterateOverRenderedTiles();
    }

    void TileHovering::IterateOverRenderedTiles()
    {
        auto worldArea{_<World>().GetCurrentWorldArea()};

        auto worldAreaSize{worldArea->GetSize()};

        auto playerPos{_<PlayerCharacter>().GetPosition()};

        auto gridSize{_<Theme0Properties>().GetGridSize()};

        auto extraRows{8};

        for (auto y = -extraRows;
             y < gridSize.height + extraRows; y++)
        {
            for (auto x = 0; x < gridSize.width; x++)
            {
                auto xCoordinate{
                    (worldAreaSize.width - playerPos.x) -
                    (gridSize.width - 1) / 2 + x};

                auto yCoordinate{
                    (worldAreaSize.height - playerPos.y) -
                    (gridSize.height - 1) / 2 + y};

                auto result{DetermineIfTileIsHovered(
                    xCoordinate, yCoordinate)};

                if (result)
                {
                    m_hoveredCoordinate = {
                        worldAreaSize.width - xCoordinate,
                        worldAreaSize.height - yCoordinate};

                    return;
                }
            }
        }
    }

    bool
    TileHovering::DetermineIfTileIsHovered(int xCoordinate,
                                           int yCoordinate)
    {
        auto result{CheckIfRayIntersectsTile(xCoordinate,
                                             yCoordinate)};

        return result;
    }

    bool
    TileHovering::CheckIfRayIntersectsTile(int xCoordinate,
                                           int yCoordinate)
    {
        // Get mouse position in normalized screen
        // coordinates
        auto mousePos{GetNormallizedMousePosition(
            _<SDLDevice>().GetWindow())};

        // Get camera matrices
        auto viewMatrix{_<Camera>().GetViewMatrix()};
        auto projMatrix{_<Camera>().GetProjectionMatrix()};

        // Get inverse view-projection matrix for
        // unprojecting
        auto invViewProj{
            glm::inverse(projMatrix * viewMatrix)};

        // Convert normalized mouse coordinates to clip
        // space (normalized coordinates are in range [-1,
        // 1])
        glm::vec4 nearPoint{mousePos.x * 2.0f - 1.0f,
                            mousePos.y * 2.0f - 1.0f, -1.0f,
                            1.0f};
        glm::vec4 farPoint{mousePos.x * 2.0f - 1.0f,
                           mousePos.y * 2.0f - 1.0f, 1.0f,
                           1.0f};

        // Unproject to world space
        nearPoint = invViewProj * nearPoint;
        farPoint = invViewProj * farPoint;

        // Perspective divide
        if (std::abs(nearPoint.w) > 0.0001f)
        {
            nearPoint /= nearPoint.w;
        }
        if (std::abs(farPoint.w) > 0.0001f)
        {
            farPoint /= farPoint.w;
        }

        // Compute ray origin and direction
        glm::vec3 rayOrigin{nearPoint.x, nearPoint.y,
                            nearPoint.z};
        glm::vec3 rayDir{glm::normalize(
            glm::vec3(farPoint.x, farPoint.y, farPoint.z) -
            rayOrigin)};

        // Get tile geometry
        auto worldArea{_<World>().GetCurrentWorldArea()};

        auto coordinateNW{Point{xCoordinate, yCoordinate}};
        auto coordinateNE{
            Point{xCoordinate + 1, yCoordinate}};
        auto coordinateSW{
            Point{xCoordinate, yCoordinate + 1}};
        auto coordinateSE{
            Point{xCoordinate + 1, yCoordinate + 1}};

        // Check if coordinates are valid
        if (!worldArea->IsValidCoordinate(coordinateNW) ||
            !worldArea->IsValidCoordinate(coordinateNE) ||
            !worldArea->IsValidCoordinate(coordinateSW) ||
            !worldArea->IsValidCoordinate(coordinateSE))
        {
            return false;
        }

        auto tileNW{worldArea->GetTile(coordinateNW)};
        auto tileNE{worldArea->GetTile(coordinateNE)};
        auto tileSW{worldArea->GetTile(coordinateSW)};
        auto tileSE{worldArea->GetTile(coordinateSE)};

        auto elevationNW{tileNW ? tileNW->GetElevation()
                                : 0.0f};
        auto elevationNE{tileNE ? tileNE->GetElevation()
                                : 0.0f};
        auto elevationSW{tileSW ? tileSW->GetElevation()
                                : 0.0f};
        auto elevationSE{tileSE ? tileSE->GetElevation()
                                : 0.0f};

        // Get tile size and elevation height
        auto rendTileSize{
            _<Theme0Properties>().GetTileSize()};
        auto elevHeight{0.1f};

        // Convert tile coordinates to world space positions
        auto worldXNW{xCoordinate * rendTileSize -
                      rendTileSize / 2};
        auto worldYNW{yCoordinate * rendTileSize -
                      rendTileSize / 2};
        auto worldXNE{(xCoordinate + 1) * rendTileSize -
                      rendTileSize / 2};
        auto worldYNE{yCoordinate * rendTileSize -
                      rendTileSize / 2};
        auto worldXSW{xCoordinate * rendTileSize -
                      rendTileSize / 2};
        auto worldYSW{(yCoordinate + 1) * rendTileSize -
                      rendTileSize / 2};
        auto worldXSE{(xCoordinate + 1) * rendTileSize -
                      rendTileSize / 2};
        auto worldYSE{(yCoordinate + 1) * rendTileSize -
                      rendTileSize / 2};

        // Create 3D vertices for the tile quad
        glm::vec3 vertNW{worldXNW, worldYNW,
                         elevationNW * elevHeight};
        glm::vec3 vertNE{worldXNE, worldYNE,
                         elevationNE * elevHeight};
        glm::vec3 vertSW{worldXSW, worldYSW,
                         elevationSW * elevHeight};
        glm::vec3 vertSE{worldXSE, worldYSE,
                         elevationSE * elevHeight};

        // Test intersection with two triangles that make up
        // the quad
        // Triangle 1: NW -> NE -> SE
        glm::vec2 baryPosition1;
        float distance1;
        auto intersects1{glm::intersectRayTriangle(
            rayOrigin, rayDir, vertNW, vertNE, vertSE,
            baryPosition1, distance1)};

        // Triangle 2: NW -> SE -> SW
        glm::vec2 baryPosition2;
        float distance2;
        auto intersects2{glm::intersectRayTriangle(
            rayOrigin, rayDir, vertNW, vertSE, vertSW,
            baryPosition2, distance2)};

        return intersects1 || intersects2;
    }
}