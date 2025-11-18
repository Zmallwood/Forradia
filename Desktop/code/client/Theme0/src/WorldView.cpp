//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "WorldView.hpp"

#include "Player/PlayerCharacter.hpp"

#include "Theme0Properties.hpp"

#include "Update/TileHovering.hpp"

#include "World.hpp"

#include "WorldArea.hpp"

#include "Tile.hpp"

#include "ObjectsStack.hpp"

#include "Object.hpp"

#include "Creature.hpp"

#include "Robot.hpp"

#include "GroundRenderer.hpp"

#include "ModelRenderer.hpp"

#include "SkyRenderer.hpp"

namespace Forradia::Theme0::GameplayCore
{
    void WorldView::Initiallize()
    {
        auto worldArea{_<World>().GetCurrentWorldArea()};

        auto worldAreaSize{worldArea->GetSize()};

        for (auto y = 0; y < worldAreaSize.height; y++)
        {
            for (auto x = 0; x < worldAreaSize.width; x++)
            {
                m_renderIDsGround[x][y] =
                    Hash("Ground_" + std::to_string(x) + "_" + std::to_string(y));

                m_renderIDsClaimedTiles[x][y] =
                    Hash("ClaimedTile_" + std::to_string(x) + "_" + std::to_string(y));
            }
        }
    }

    void WorldView::Render() const
    {
        SkyRenderer skyRenderer;
        glm::vec3 sunDirection = glm::normalize(glm::vec3(0.7f, 0.0f, 0.7f)); // 45 degrees up in +Z
        float sunElevation = M_PI / 4.0f;                                     // 45 degrees
        _<SkyRenderer>().Render(sunDirection, sunElevation);

        auto gridSize{_<Theme0Properties>().GetGridSize()};

        // Calculate extended ground rendering size
        auto groundGridSize{
            decltype(gridSize){static_cast<decltype(gridSize.width)>(
                                   gridSize.width * k_groundRenderingDistanceMultiplier),
                               static_cast<decltype(gridSize.height)>(
                                   gridSize.height * k_groundRenderingDistanceMultiplier)}};

        auto playerPos{_<PlayerCharacter>().GetPosition()};

        auto worldArea{_<World>().GetCurrentWorldArea()};

        auto worldAreaSize{worldArea->GetSize()};

        auto hoveredCoordinate{_<TileHovering>().GetHoveredCoordinate()};

        auto elevHeight{_<Theme0Properties>().GetElevationHeight()};

        auto playerElev{worldArea->GetTile(playerPos.x, playerPos.y)->GetElevation()};

        auto rendTileSize{_<Theme0Properties>().GetTileSize()};

        // First pass: Render ground tiles at extended distance
        for (auto y = 0; y < groundGridSize.height; y++)
        {
            for (auto x = 0; x < groundGridSize.width; x++)
            {
                auto xCoordinate{playerPos.x - (groundGridSize.width - 1) / 2 + x};

                auto yCoordinate{playerPos.y - (groundGridSize.height - 1) / 2 + y};

                if (!worldArea->IsValidCoordinate(xCoordinate, yCoordinate))
                {
                    continue;
                }

                auto tile{worldArea->GetTile(xCoordinate, yCoordinate)};

                auto objectsStack{tile->GetObjectsStack()};

                auto objects{objectsStack->GetObjects()};

                auto coordinateNW{Point{xCoordinate, yCoordinate}};

                auto coordinateNE{Point{xCoordinate + 1, yCoordinate}};

                auto coordinateSW{Point{xCoordinate, yCoordinate + 1}};

                auto coordinateSE{Point{xCoordinate + 1, yCoordinate + 1}};

                auto coordinateNEE{Point{xCoordinate + 2, yCoordinate}};

                auto coordinateSEE{Point{xCoordinate + 2, yCoordinate + 1}};

                auto coordinateSESE{Point{xCoordinate + 2, yCoordinate + 2}};

                auto coordinateSES{Point{xCoordinate + 1, yCoordinate + 2}};

                auto coordinateSS{Point{xCoordinate, yCoordinate + 2}};

                if (!worldArea->IsValidCoordinate(coordinateNW) ||
                    !worldArea->IsValidCoordinate(coordinateNE) ||
                    !worldArea->IsValidCoordinate(coordinateSW) ||
                    !worldArea->IsValidCoordinate(coordinateSE))
                {
                    continue;
                }

                auto tileNW{worldArea->GetTile(coordinateNW)};

                auto tileNE{worldArea->GetTile(coordinateNE)};

                auto tileSW{worldArea->GetTile(coordinateSW)};

                auto tileSE{worldArea->GetTile(coordinateSE)};

                auto tileNEE{worldArea->GetTile(coordinateNEE)};

                auto tileSEE{worldArea->GetTile(coordinateSEE)};

                auto tileSESE{worldArea->GetTile(coordinateSESE)};

                auto tileSES{worldArea->GetTile(coordinateSES)};

                auto tileSS{worldArea->GetTile(coordinateSS)};

                Vector<float> elevations;

                auto elevationNW{tileNW ? tileNW->GetElevation() : 0.0f};

                auto elevationNE{tileNE ? tileNE->GetElevation() : 0.0f};

                auto elevationSE{tileSE ? tileSE->GetElevation() : 0.0f};

                auto elevationSW{tileSW ? tileSW->GetElevation() : 0.0f};

                auto elevationNEE{tileNEE ? tileNEE->GetElevation() : 0.0f};

                auto elevationSEE{tileSEE ? tileSEE->GetElevation() : 0.0f};

                auto elevationSESE{tileSESE ? tileSESE->GetElevation() : 0.0f};

                auto elevationSES{tileSES ? tileSES->GetElevation() : 0.0f};

                auto elevationSS{tileSS ? tileSS->GetElevation() : 0.0f};

                elevations.push_back(elevationNW);
                elevations.push_back(elevationNE);
                elevations.push_back(elevationNEE);
                elevations.push_back(elevationSW);
                elevations.push_back(elevationSE);
                elevations.push_back(elevationSEE);
                elevations.push_back(elevationSS);
                elevations.push_back(elevationSES);
                elevations.push_back(elevationSESE);

                auto elevationAverage{(elevationNW + elevationNE + elevationSW + elevationSE) / 4};

                auto elevationMax{std::max(
                    elevationNW, std::max(elevationNE, std::max(elevationSE, elevationSW)))};

                auto ground{tile->GetGround()};

                if (ground == Hash("GroundWater"))
                {
                    auto waterDepth{tile->GetWaterDepth()};

                    waterDepth = std::min(waterDepth, k_maxWaterDepthRendering);

                    String waterImageString{"GroundWater_Depth" + std::to_string(waterDepth)};

                    auto animationIndex{(GetTicks() + ((xCoordinate + yCoordinate) * 100)) / 500 %
                                        3};

                    waterImageString += "_" + std::to_string(animationIndex);

                    ground = Hash(waterImageString);
                }

                // Check if this tile is within the normal grid size for object/creature rendering
                auto isWithinNormalGrid{x >= (groundGridSize.width - gridSize.width) / 2 &&
                                        x < (groundGridSize.width + gridSize.width) / 2 &&
                                        y >= (groundGridSize.height - gridSize.height) / 2 &&
                                        y < (groundGridSize.height + gridSize.height) / 2};

                // Only render objects, creatures, and robots within the normal grid size
                if (isWithinNormalGrid)
                {
                    for (auto object : objects)
                    {
                        auto objectType{object->GetType()};

                        _<ModelRenderer>().DrawModel(objectType,
                                                     (xCoordinate)*rendTileSize + rendTileSize / 2,
                                                     (yCoordinate)*rendTileSize + rendTileSize / 2,
                                                     elevationMax, object->GetModelScaling());
                    }

                    auto creature{tile->GetCreature()};

                    if (creature)
                    {
                        auto creatureType{creature->GetType()};

                        _<ModelRenderer>().DrawModel(
                            creatureType, (xCoordinate)*rendTileSize + rendTileSize / 2,
                            (yCoordinate)*rendTileSize + rendTileSize / 2, elevationMax);
                    }

                    auto robot{tile->GetRobot()};

                    if (robot)
                    {
                        auto robotType{robot->GetType()};

                        robotType = Hash("RobotMechWolf");

                        _<ModelRenderer>().DrawModel(
                            robotType, (xCoordinate)*rendTileSize + rendTileSize / 2,
                            (yCoordinate)*rendTileSize + rendTileSize / 2, elevationMax);
                    }

                    if (xCoordinate == playerPos.x && yCoordinate == playerPos.y)
                    {
                        _<ModelRenderer>().DrawModel(
                            Hash("Player"), (xCoordinate)*rendTileSize + rendTileSize / 2,
                            (yCoordinate)*rendTileSize + rendTileSize / 2, elevationMax);
                    }
                }

                _<GroundRenderer>().DrawTile(m_renderIDsGround.at(xCoordinate).at(yCoordinate),
                                             ground, xCoordinate, yCoordinate, rendTileSize,
                                             elevations);

                // Only render ClaimedTile symbol within the normal grid size
                if (worldArea->CoordinateIsClaimed({xCoordinate, yCoordinate}))
                {
                    _<GroundRenderer>().DrawTile(
                        m_renderIDsClaimedTiles.at(xCoordinate).at(yCoordinate),
                        Hash("ClaimedTile"), xCoordinate, yCoordinate, rendTileSize, elevations);
                }

                if (xCoordinate == hoveredCoordinate.x && yCoordinate == hoveredCoordinate.y)
                {
                    for (auto &elevation : elevations)
                    {
                        elevation += 0.01f;
                    }

                    _<GroundRenderer>().DrawTile(k_renderIDGroundSymbolHoveredTile,
                                                 Hash("HoveredTile"), xCoordinate, yCoordinate,
                                                 rendTileSize, elevations, true);
                }
            }
        }
    }
}