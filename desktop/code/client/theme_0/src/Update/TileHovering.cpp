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

namespace Forradia::Theme0::GameplayCore
{
    void TileHovering::Update()
    {

        auto worldArea{_<World>().GetCurrentWorldArea()};

        auto worldAreaSize{worldArea->GetSize()};

        auto playerPos{_<PlayerCharacter>().GetPosition()};

        auto rendTileSize{
            _<Theme0Properties>().GetTileSize()};

        auto mousePosition{GetNormallizedMousePosition(
            _<SDLDevice>().GetWindow())};

        auto canvasSize{
            GetCanvasSize(_<SDLDevice>().GetWindow())};

        auto elevHeight{0.1f};

        auto playerElev{
            worldArea
                ->GetTile(worldAreaSize.width - playerPos.x,
                          worldAreaSize.height -
                              playerPos.y)
                ->GetElevation()};

        Point3F cameraPos{
            (worldAreaSize.width - playerPos.x) *
                    rendTileSize +
                rendTileSize / 2,
            (worldAreaSize.height - playerPos.y) *
                    rendTileSize +
                rendTileSize / 2,
            -playerElev * elevHeight};

        glm::mat4 modelMatrix = glm::mat4(1.0f);

        modelMatrix = glm::translate(
            modelMatrix,
            glm::vec3((worldAreaSize.width - playerPos.x) *
                          rendTileSize,
                      (worldAreaSize.height - playerPos.y) *
                          rendTileSize,
                      0.0f));

        auto cameraPosition{_<Camera>().GetPosition()};
        auto cameraLookAt{_<Camera>().GetLookAt()};

        glm::mat4 view = glm::lookAt(
            glm::vec3(cameraPosition.x, cameraPosition.y,
                      cameraPosition.z),
            glm::vec3(cameraLookAt.x, cameraLookAt.y,
                      cameraLookAt.z),
            glm::vec3(0.0f, 0.0f, -1.0f));  

        auto aspectRatio{
            CalcAspectRatio(_<SDLDevice>().GetWindow())};

        glm::mat4 proj = glm::perspective(
            glm::radians(90.0f), aspectRatio, 0.1f, 100.0f);

        auto c = glm::vec3(cameraPos.x, cameraPos.y - 2.0f,
                           -cameraPos.z + 2.5f);

        auto gridSize{_<Theme0Properties>().GetGridSize()};

        auto dir{glm::normalize(glm::unProject(
            glm::vec3((mousePosition.x) * canvasSize.width,
                      (mousePosition.y) * canvasSize.height,
                      1),
            view * modelMatrix, proj,
            glm::vec4(0.0f, 0.0f, canvasSize.width,
                      canvasSize.height)))};

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

                if (!worldArea->IsValidCoordinate(
                        xCoordinate, yCoordinate))
                {
                    continue;
                }

                auto coordinateNW{
                    Point{xCoordinate, yCoordinate}};

                auto coordinateNE{
                    Point{xCoordinate + 1, yCoordinate}};

                auto coordinateSW{
                    Point{xCoordinate, yCoordinate + 1}};

                auto coordinateSE{Point{xCoordinate + 1,
                                        yCoordinate + 1}};

                auto tileNW{
                    worldArea->GetTile(coordinateNW)};

                auto tileNE{
                    worldArea->GetTile(coordinateNE)};

                auto tileSW{
                    worldArea->GetTile(coordinateSW)};

                auto tileSE{
                    worldArea->GetTile(coordinateSE)};

                auto elevationNW{
                    tileNW ? tileNW->GetElevation() : 0.0f};

                auto elevationNE{
                    tileNE ? tileNE->GetElevation() : 0.0f};

                auto elevationSE{
                    tileSE ? tileSE->GetElevation() : 0.0f};

                auto elevationSW{
                    tileSW ? tileSW->GetElevation() : 0.0f};

                auto v00{glm::vec3{
                    (xCoordinate - 1 + 0.5f) * rendTileSize,
                    (yCoordinate - 1 + 0.5f) * rendTileSize,
                    elevationNW * elevHeight}};

                auto v10{glm::vec3{
                    (xCoordinate - 1 + 0.5f + 1) *
                        rendTileSize,
                    (yCoordinate - 1 + 0.5f) * rendTileSize,
                    elevationNE * elevHeight}};

                auto v11{
                    glm::vec3{(xCoordinate - 1 + 0.5f + 1) *
                                  rendTileSize,
                              (yCoordinate - 1 + 0.5f + 1) *
                                  rendTileSize,
                              elevationSE * elevHeight}};

                auto v01{glm::vec3{
                    (xCoordinate - 1 + 0.5f) * rendTileSize,
                    (yCoordinate - 1 + 0.5f + 1) *
                        rendTileSize,
                    elevationSW * elevHeight}};

                glm::vec3 result;

                auto success{glm::intersectLineTriangle(
                    c, dir, v00, v10, v11, result)};

                if (!success)
                {
                    success = {glm::intersectLineTriangle(
                        c, dir, v00, v11, v01, result)};
                }

                if (success)
                {
                    m_hoveredCoordinate = {
                        (worldAreaSize.width - xCoordinate +
                         1),
                        (worldAreaSize.height -
                         yCoordinate + 1)};
                }
            }
        }
    }
}