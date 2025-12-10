//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#include "WorldView.hpp"
#include "Coloring/Palette.hpp"
#include "Creature.hpp"
#include "Directions.hpp"
#include "GroundRenderer.hpp"
#include "ModelRenderer.hpp"
#include "Object.hpp"
#include "ObjectsStack.hpp"
#include "Player/PlayerCharacter.hpp"
#include "Robot.hpp"
#include "SkyRenderer.hpp"
#include "Theme0Properties.hpp"
#include "Tile.hpp"
#include "TileData.hpp"
#include "Update/BattleSystem.hpp"
#include "Update/TileHovering.hpp"
#include "World.hpp"
#include "WorldArea.hpp"

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

                // m_renderIDsGroundCorners1[x][y] =
                //     Hash("GroundCorner_" + std::to_string(x) + "_" + std::to_string(y));

                // m_renderIDsGroundCorners2[x][y] =
                //     Hash("GroundCorner_" + std::to_string(x) + "_" + std::to_string(y));

                // m_renderIDsGroundCorners3[x][y] =
                //     Hash("GroundCorner_" + std::to_string(x) + "_" + std::to_string(y));

                // m_renderIDsGroundCorners4[x][y] =
                //     Hash("GroundCorner_" + std::to_string(x) + "_" + std::to_string(y));

                m_renderIDsClaimedTiles[x][y] =
                    Hash("ClaimedTile_" + std::to_string(x) + "_" + std::to_string(y));

                m_renderIDsRivers1[x][y] =
                    Hash("River1_" + std::to_string(x) + "_" + std::to_string(y));

                m_renderIDsRivers2[x][y] =
                    Hash("River2_" + std::to_string(x) + "_" + std::to_string(y));
            }
        }
    }

    void WorldView::Render() const
    {
        SkyRenderer skyRenderer;

        // 45 degrees up in +Z

        glm::vec3 sunDirection = glm::normalize(glm::vec3(0.7f, 0.0f, 0.7f));

        // 45 degrees

        float sunElevation = M_PI / 4.0f;

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

        Vector<TileData> tiles;

        // Vector<TileData> tileCorners1;

        // Vector<TileData> tileCorners2;

        // Vector<TileData> tileCorners3;

        // Vector<TileData> tileCorners4;

        Vector<TileData> rivers1;

        Vector<TileData> rivers2;

        std::map<int, std::map<int, Vector<float>>> elevationsAll;

        auto fnIterationGround{
            [&](int x, int y)
            {
                auto xCoordinate{playerPos.x - (groundGridSize.width - 1) / 2 + x};

                auto yCoordinate{playerPos.y - (groundGridSize.height - 1) / 2 + y};

                if (!worldArea->IsValidCoordinate(xCoordinate, yCoordinate))
                {
                    return;
                }

                auto tile{worldArea->GetTile(xCoordinate, yCoordinate)};

                auto objectsStack{tile->GetObjectsStack()};

                auto objects{objectsStack->GetObjects()};

                auto coordinateNWW{Point{xCoordinate - 1, yCoordinate}};

                auto coordinateNNW{Point{xCoordinate, yCoordinate - 1}};

                auto coordinateNNWW{Point{xCoordinate - 1, yCoordinate - 1}};

                auto coordinateNNE{Point{xCoordinate + 1, yCoordinate - 1}};

                auto coordinateSWW{Point{xCoordinate - 1, yCoordinate + 1}};

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
                    return;
                }

                auto tileNWW{worldArea->GetTile(coordinateNWW)};

                auto tileNNW{worldArea->GetTile(coordinateNNW)};

                auto tileNNWW{worldArea->GetTile(coordinateNNWW)};

                auto tileNNE{worldArea->GetTile(coordinateNNE)};

                auto tileSWW{worldArea->GetTile(coordinateSWW)};

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

                elevationsAll[xCoordinate][yCoordinate] = elevations;

                auto elevationAverage{(elevationNW + elevationNE + elevationSW + elevationSE) / 4};

                auto elevationMax{std::max(
                    elevationNW, std::max(elevationNE, std::max(elevationSE, elevationSW)))};

                auto ground{tile->GetGround()};

                // if (ground == Hash("GroundWater"))
                // {
                //     auto grassCornerNW{false};
                //     auto grassCornerNE{false};
                //     auto grassCornerSE{false};
                //     auto grassCornerSW{false};

                //     if (tileNWW && tileNWW->GetGround() == Hash("GroundGrass") && tileNNW &&
                //         tileNNW->GetGround() == Hash("GroundGrass") && tileNNWW &&
                //         tileNNWW->GetGround() == Hash("GroundGrass"))
                //     {
                //         tileCorners1.push_back(
                //             {m_renderIDsGroundCorners1.at(xCoordinate).at(yCoordinate),
                //              Hash("GroundGrassCornerNW"), xCoordinate, yCoordinate,
                //              rendTileSize, elevations, false});
                //     }
                // }

                auto color00{Palette::GetColor<Hash("White")>()};
                auto color10{Palette::GetColor<Hash("White")>()};
                auto color11{Palette::GetColor<Hash("White")>()};
                auto color01{Palette::GetColor<Hash("White")>()};

                switch (ground)
                {
                case Hash("GroundGrass"):
                    color00 = Palette::GetColor<Hash("Green")>();
                    break;
                case Hash("GroundWater"):
                    color00 = Palette::GetColor<Hash("MildBlue")>();
                    break;
                case Hash("GroundDirt"):
                    color00 = Palette::GetColor<Hash("Brown")>();
                    break;
                case Hash("GroundRock"):
                    color00 = Palette::GetColor<Hash("Gray")>();
                    break;
                }

                if (tileNE)
                {
                    switch (tileNE->GetGround())
                    {
                    case Hash("GroundGrass"):
                        color10 = Palette::GetColor<Hash("Green")>();
                        break;
                    case Hash("GroundWater"):
                        color10 = Palette::GetColor<Hash("MildBlue")>();
                        break;
                    case Hash("GroundDirt"):
                        color10 = Palette::GetColor<Hash("Brown")>();
                        break;
                    case Hash("GroundRock"):
                        color10 = Palette::GetColor<Hash("Gray")>();
                        break;
                    }
                }

                if (tileSE)
                {
                    switch (tileSE->GetGround())
                    {
                    case Hash("GroundGrass"):
                        color11 = Palette::GetColor<Hash("Green")>();
                        break;
                    case Hash("GroundWater"):
                        color11 = Palette::GetColor<Hash("MildBlue")>();
                        break;
                    case Hash("GroundDirt"):
                        color11 = Palette::GetColor<Hash("Brown")>();
                        break;
                    case Hash("GroundRock"):
                        color11 = Palette::GetColor<Hash("Gray")>();
                        break;
                    }
                }

                if (tileSW)
                {
                    switch (tileSW->GetGround())
                    {
                    case Hash("GroundGrass"):
                        color01 = Palette::GetColor<Hash("Green")>();
                        break;
                    case Hash("GroundWater"):
                        color01 = Palette::GetColor<Hash("MildBlue")>();
                        break;
                    case Hash("GroundDirt"):
                        color01 = Palette::GetColor<Hash("Brown")>();
                        break;
                    case Hash("GroundRock"):
                        color01 = Palette::GetColor<Hash("Gray")>();
                        break;
                    }
                }

                //ground = Hash("GroundWater");
                

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

                // Check if this tile is within the normal grid size for object/creature
                // rendering.

                auto isWithinNormalGrid{x >= (groundGridSize.width - gridSize.width) / 2 &&
                                        x < (groundGridSize.width + gridSize.width) / 2 &&
                                        y >= (groundGridSize.height - gridSize.height) / 2 &&
                                        y < (groundGridSize.height + gridSize.height) / 2};

                auto forceRedraw{tile->GetForceRedraw()};

                tile->SetForceRedraw(false);

                ground = Hash("GroundGrass");

                tiles.push_back({m_renderIDsGround.at(xCoordinate).at(yCoordinate), ground,
                                 xCoordinate, yCoordinate, rendTileSize, elevations, forceRedraw,
                                 color00, color10, color11, color01});
            }};

        auto fnIterationAllExceptGround{
            [&](int x, int y)
            {
                auto xCoordinate{playerPos.x - (groundGridSize.width - 1) / 2 + x};

                auto yCoordinate{playerPos.y - (groundGridSize.height - 1) / 2 + y};

                if (!worldArea->IsValidCoordinate(xCoordinate, yCoordinate))
                {
                    return;
                }

                auto tile{worldArea->GetTile(xCoordinate, yCoordinate)};

                auto objectsStack{tile->GetObjectsStack()};

                auto objects{objectsStack->GetObjects()};

                if (elevationsAll.find(xCoordinate) == elevationsAll.end() ||
                    elevationsAll[xCoordinate].find(yCoordinate) ==
                        elevationsAll[xCoordinate].end())
                {
                    return;
                }

                Vector<float> &elevations = elevationsAll[xCoordinate][yCoordinate];

                auto &elevationNW = elevations[0];
                auto &elevationNE = elevations[1];
                auto &elevationNEE = elevations[2];
                auto &elevationSW = elevations[3];
                auto &elevationSE = elevations[4];
                auto &elevationSEE = elevations[5];
                auto &elevationSS = elevations[6];
                auto &elevationSES = elevations[7];
                auto &elevationSESE = elevations[8];

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

                // Check if this tile is within the normal grid size for object/creature
                // rendering.

                auto isWithinNormalGrid{x >= (groundGridSize.width - gridSize.width) / 2 &&
                                        x < (groundGridSize.width + gridSize.width) / 2 &&
                                        y >= (groundGridSize.height - gridSize.height) / 2 &&
                                        y < (groundGridSize.height + gridSize.height) / 2};

                // Only render objects, creatures, and robots within the normal grid size.

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

                if (xCoordinate == hoveredCoordinate.x && yCoordinate == hoveredCoordinate.y)
                {
                    for (auto &elevation : elevations)
                    {
                        elevation += 0.01f;
                    }

                    _<GroundRenderer>().SetupState();

                    _<GroundRenderer>().DrawTile(k_renderIDGroundSymbolHoveredTile,
                                                 Hash("HoveredTile"), xCoordinate, yCoordinate,
                                                 rendTileSize, elevations, true);

                    // Only render ClaimedTile symbol within the normal grid size.

                    if (worldArea->CoordinateIsClaimed({xCoordinate, yCoordinate}))
                    {
                        _<GroundRenderer>().DrawTile(
                            m_renderIDsClaimedTiles.at(xCoordinate).at(yCoordinate),
                            Hash("ClaimedTile"), xCoordinate, yCoordinate, rendTileSize,
                            elevations);
                    }

                    _<GroundRenderer>().RestoreState();
                }

                auto targetedRobot{_<BattleSystem>().GetTargetedRobot()};

                if (targetedRobot)
                {
                    auto &robots{worldArea->GetRobotsMirrorRef()};

                    auto targetedRobotCoordinates{robots.at(targetedRobot)};

                    if (targetedRobotCoordinates.x == xCoordinate &&
                        targetedRobotCoordinates.y == yCoordinate)
                    {
                        for (auto &elevation : elevations)
                        {
                            elevation += 0.01f;
                        }

                        _<GroundRenderer>().SetupState();

                        _<GroundRenderer>().DrawTile(k_renderIDGroundSymbolTargetedRobot,
                                                     Hash("TargetedRobot"), xCoordinate,
                                                     yCoordinate, rendTileSize, elevations, true);

                        _<GroundRenderer>().RestoreState();
                    }
                }
            }};

        _<GroundRenderer>().SetupState();

        auto tilesGroupSize{20};

        // First pass: Render ground tiles at extended distance.

        for (auto y = 0; y < groundGridSize.height; y++)
        {
            for (auto x = 0; x < groundGridSize.width; x++)
            {
                auto xCoordinate{playerPos.x - (groundGridSize.width - 1) / 2 + x};

                auto yCoordinate{playerPos.y - (groundGridSize.height - 1) / 2 + y};

                if (xCoordinate % tilesGroupSize == 0 && yCoordinate % tilesGroupSize == 0)
                {
                    for (auto yy = 0; yy < tilesGroupSize; yy++)
                    {
                        for (auto xx = 0; xx < tilesGroupSize; xx++)
                        {
                            fnIterationGround(x + xx, y + yy);
                        }
                    }
                }
            }
        }
        if (!tiles.empty())
        {
            _<GroundRenderer>().DrawTiles(tiles);
            // if (!rivers1.empty())
            // {
            //     std::cout << "rivers1" << std::endl;
            // }
            //_<GroundRenderer>().DrawTiles(rivers1);
            // if (!rivers2.empty())
            // {
            //     std::cout << "rivers2" << std::endl;
            // }
            //_<GroundRenderer>().DrawTiles(rivers2);
        }

        tiles.clear();
        //rivers1.clear();
        //rivers2.clear();

        _<GroundRenderer>().SetupState();

        // Second pass: Render all except ground tiles.

        for (auto y = 0; y < worldAreaSize.height; y++)
        {
            for (auto x = 0; x < worldAreaSize.width; x++)
            {
                fnIterationAllExceptGround(x, y);
            }
        }
    }
}