//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "WorldView.hpp"

#include "PlayerCharacter.hpp"

#include "Theme0Properties.hpp"

#include "Update/TileHovering.hpp"

#include "World.hpp"

#include "WorldArea.hpp"

#include "Tile.hpp"

#include "ObjectsStack.hpp"

#include "Object.hpp"

#include "TreeObject.hpp"

#include "Creature.hpp"

#include "Robot.hpp"

#include "GroundRenderer.hpp"

#include "ModelRenderer.hpp"

namespace Forradia::Theme0::GameplayCore
{
    void WorldView::Render() const
    {
        auto gridSize{_<Theme0Properties>().GetGridSize()};

        auto playerPos{_<PlayerCharacter>().GetPosition()};

        auto worldArea{_<World>().GetCurrentWorldArea()};

        auto extraRows{8};

        auto worldAreaSize{worldArea->GetSize()};

        auto hoveredCoordinate{
            _<TileHovering>().GetHoveredCoordinate()};

        auto elevHeight{0.1f};

        auto playerElev{
            worldArea
                ->GetTile(worldAreaSize.width - playerPos.x,
                          worldAreaSize.height -
                              playerPos.y)
                ->GetElevation()};

        auto rendTileSize{
            _<Theme0Properties>().GetTileSize()};

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

                auto tile{worldArea->GetTile(xCoordinate,
                                             yCoordinate)};

                auto objectsStack{tile->GetObjectsStack()};

                auto objects{objectsStack->GetObjects()};

                auto coordinateNW{
                    Point{xCoordinate, yCoordinate}};

                auto coordinateNE{
                    Point{xCoordinate + 1, yCoordinate}};

                auto coordinateSW{
                    Point{xCoordinate, yCoordinate + 1}};

                auto coordinateSE{Point{xCoordinate + 1,
                                        yCoordinate + 1}};

                auto coordinateNEE{
                    Point{xCoordinate + 2, yCoordinate}};

                auto coordinateSEE{Point{xCoordinate + 2,
                                         yCoordinate + 1}};

                auto coordinateSESE{Point{xCoordinate + 2,
                                          yCoordinate + 2}};

                auto coordinateSES{Point{xCoordinate + 1,
                                         yCoordinate + 2}};

                auto coordinateSS{
                    Point{xCoordinate, yCoordinate + 2}};

                if (!worldArea->IsValidCoordinate(
                        coordinateNW) ||
                    !worldArea->IsValidCoordinate(
                        coordinateNE) ||
                    !worldArea->IsValidCoordinate(
                        coordinateSW) ||
                    !worldArea->IsValidCoordinate(
                        coordinateSE))
                {
                    continue;
                }

                auto tileNW{
                    worldArea->GetTile(coordinateNW)};

                auto tileNE{
                    worldArea->GetTile(coordinateNE)};

                auto tileSW{
                    worldArea->GetTile(coordinateSW)};

                auto tileSE{
                    worldArea->GetTile(coordinateSE)};

                auto tileNEE{
                    worldArea->GetTile(coordinateNEE)};

                auto tileSEE{
                    worldArea->GetTile(coordinateSEE)};

                auto tileSESE{
                    worldArea->GetTile(coordinateSESE)};

                auto tileSES{
                    worldArea->GetTile(coordinateSES)};

                auto tileSS{
                    worldArea->GetTile(coordinateSS)};

                Vector<float> elevations;

                auto elevationNW{
                    tileNW ? tileNW->GetElevation() : 0.0f};

                auto elevationNE{
                    tileNE ? tileNE->GetElevation() : 0.0f};

                auto elevationSE{
                    tileSE ? tileSE->GetElevation() : 0.0f};

                auto elevationSW{
                    tileSW ? tileSW->GetElevation() : 0.0f};

                auto elevationNEE{
                    tileNEE ? tileNEE->GetElevation()
                            : 0.0f};

                auto elevationSEE{
                    tileSEE ? tileSEE->GetElevation()
                            : 0.0f};

                auto elevationSESE{
                    tileSESE ? tileSESE->GetElevation()
                             : 0.0f};

                auto elevationSES{
                    tileSES ? tileSES->GetElevation()
                            : 0.0f};

                auto elevationSS{
                    tileSS ? tileSS->GetElevation() : 0.0f};

                elevations.push_back(elevationNW);
                elevations.push_back(elevationNE);
                elevations.push_back(elevationNEE);
                elevations.push_back(elevationSW);
                elevations.push_back(elevationSE);
                elevations.push_back(elevationSEE);
                elevations.push_back(elevationSS);
                elevations.push_back(elevationSES);
                elevations.push_back(elevationSESE);

                auto elevationAverage{
                    (elevationNW + elevationNE +
                     elevationSW + elevationSE) /
                    4};

                auto elevationMax{std::max(
                    elevationNW,
                    std::max(elevationNE,
                             std::max(elevationSE,
                                      elevationSW)))};

                auto ground{tile->GetGround()};

                if (ground == Hash("GroundWater"))
                {
                    auto animationIndex{
                        (GetTicks() +
                         ((xCoordinate + yCoordinate) *
                          100)) /
                        500 % 3};

                    ground = Hash(
                        "GroundWater_" +
                        std::to_string(animationIndex));
                }

                for (auto object : objects)
                {
                    auto objectType{object->GetType()};

                    if (objectType ==
                            Hash("ObjectFirTree") ||
                        objectType ==
                            Hash("ObjectBirchTree"))
                    {
                        auto treeObjects{
                            std::static_pointer_cast<
                                Forradia::Theme0::
                                    TreeObject>(object)};

                        auto trunkParts{
                            treeObjects->GetTrunkParts()};

                        auto needleTypes{
                            treeObjects->GetNeedleTypes()};

                        auto widthFactor{
                            treeObjects->GetWidthFactor()};

                        for (auto i = 0;
                             i < trunkParts.size(); i++)
                        {
                            auto trunkPart{
                                trunkParts.at(i)};

                            auto needleType{
                                needleTypes.at(i)};

                            auto widthDecreaseFactor{
                                0.5f +
                                (trunkParts.size() - i) /
                                    CFloat(
                                        trunkParts.size()) /
                                    2};

                            auto treeWidth{
                                rendTileSize * widthFactor *
                                widthDecreaseFactor};

                            auto trunkPartX{trunkPart.x};

                            auto trunkPartY{trunkPart.x};

                            trunkPartX *= CFloat(i) /
                                          trunkParts.size();

                            trunkPartY *= CFloat(i) /
                                          trunkParts.size();

                            auto trunkPartXCenter{
                                (xCoordinate - 1) *
                                    rendTileSize -
                                rendTileSize / 2 -
                                trunkPartX * treeWidth};

                            auto trunkPartYCenter{
                                (yCoordinate - 1) *
                                    rendTileSize -
                                rendTileSize / 2 -
                                trunkPartY * treeWidth};

                            auto trunkPartZ{-trunkPart.y *
                                            rendTileSize};

                            auto trunkPartWidth{
                                rendTileSize * 0.2f *
                                widthDecreaseFactor};

                            auto trunkPartHeight{
                                rendTileSize * 0.2f};

                            String trunkPartName;

                            if (objectType ==
                                Hash("ObjectFirTree"))
                            {
                                trunkPartName =
                                    "ObjectFirTreeTrunkPar"
                                    "t";
                            }
                            else if (objectType ==
                                     Hash(
                                         "ObjectBirchTree"))
                            {
                                trunkPartName =
                                    "ObjectBirchTreeTrunkPa"
                                    "rt";
                            }

                            _<ModelRenderer>().DrawModel(
                                Hash(trunkPartName),
                                trunkPartXCenter -
                                    trunkPartWidth / 2,
                                trunkPartYCenter -
                                    trunkPartWidth / 2,
                                elevationAverage -
                                    trunkPartZ,
                                elevHeight);

                            auto needleWidth{treeWidth};

                            auto needleHeight{rendTileSize};

                            if (needleType)
                            {
                                _<ModelRenderer>()
                                    .DrawModel(
                                        needleType,
                                        trunkPartXCenter,
                                        trunkPartYCenter,
                                        elevationAverage -
                                            trunkPartZ -
                                            needleHeight /
                                                2,
                                        elevHeight);
                            }
                        }
                    }
                    else
                    {
                        _<ModelRenderer>().DrawModel(
                            objectType,
                            (xCoordinate)*rendTileSize -
                                rendTileSize / 2,
                            (yCoordinate)*rendTileSize -
                                rendTileSize / 2,
                            elevationMax, elevHeight);
                    }
                }

                auto creature{tile->GetCreature()};

                if (creature)
                {
                    auto creatureType{creature->GetType()};

                    creatureType =
                        Hash("CreatureWhiteRabbit");

                    _<ModelRenderer>().DrawModel(
                        creatureType,
                        (xCoordinate)*rendTileSize -
                            rendTileSize / 2,
                        (yCoordinate)*rendTileSize -
                            rendTileSize / 2,
                        elevationMax, elevHeight);
                }

                auto robot{tile->GetRobot()};

                if (robot)
                {
                    auto robotType{robot->GetType()};

                    robotType = Hash("RobotMechWolf");

                    _<ModelRenderer>().DrawModel(
                        robotType,
                        (xCoordinate)*rendTileSize -
                            rendTileSize / 2,
                        (yCoordinate)*rendTileSize -
                            rendTileSize / 2,
                        elevationMax, elevHeight);
                }

                if (xCoordinate + 1 ==
                        worldAreaSize.width - playerPos.x &&
                    yCoordinate + 1 ==
                        worldAreaSize.height - playerPos.y)
                {
                    _<ModelRenderer>().DrawModel(
                        Hash("PlayerFemale"),
                        (xCoordinate)*rendTileSize -
                            rendTileSize / 2,
                        (yCoordinate)*rendTileSize -
                            rendTileSize / 2,
                        elevationMax, elevHeight);
                }

                _<GroundRenderer>().DrawTile(
                    ground, xCoordinate, yCoordinate,
                    rendTileSize, elevations, elevHeight);

                auto waterDepth{tile->GetWaterDepth()};

                for (auto i = 0; i < waterDepth; i++)
                {
                    _<GroundRenderer>().DrawTile(
                        Hash("GroundWaterDepth"),
                        xCoordinate, yCoordinate,
                        rendTileSize, elevations,
                        elevHeight);
                }

                if (xCoordinate ==
                        worldAreaSize.width -
                            hoveredCoordinate.x &&
                    yCoordinate == worldAreaSize.height -
                                       hoveredCoordinate.y)
                {
                    for (auto &elevation : elevations)
                    {
                        elevation += 0.01f;
                    }

                    _<GroundRenderer>().DrawTile(
                        Hash("HoveredTile"), xCoordinate,
                        yCoordinate, rendTileSize,
                        elevations, elevHeight);
                }
            }
        }
    }
}