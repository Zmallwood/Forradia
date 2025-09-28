/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "WorldView.hpp"
#include "Core/Rendering/Images/ImageRenderer.hpp"
#include "Core/ImageAssets/ImageBank.hpp"
#include "Theme0/Theme0Mechanics/Math/TileGridMath.hpp"
#include "Theme0/Theme0Mechanics/CoreGameObjects/Player.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/World.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/WorldArea.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/Tile.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/ObjectsStack.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/Object.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/Creature.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/TreeObject.hpp"
#include "Theme0/Theme0Mechanics/WorldInteraction/TileHovering.hpp"

namespace Forradia
{
    void WorldView::Render() const
    {
        auto gridSize{CalculateGridSize()};

        auto tileSize{CalculateTileSize()};

        auto playerPosition{_<Player>().GetPosition()};

        auto worldArea{_<World>().GetCurrentWorldArea()};

        auto playerElevation{worldArea->GetTile(playerPosition)->GetElevation()};

        auto extraRows{8};

        for (auto i = 0; i < 3; i++)
        {
            for (auto y = -extraRows; y < gridSize.height + extraRows; y++)
            {
                for (auto x = 0; x < gridSize.width; x++)
                {
                    auto xCoordinate{playerPosition.x - (gridSize.width - 1) / 2 + x};
                    auto yCoordinate{playerPosition.y - (gridSize.height - 1) / 2 + y};

                    if (!worldArea->IsValidCoordinate(xCoordinate, yCoordinate))
                    {
                        continue;
                    }

                    auto tile{worldArea->GetTile(xCoordinate, yCoordinate)};

                    float xCanvas;
                    float yCanvas;
                    float widthCanvas;
                    float heightCanvas;

                    auto coordNW{Point{xCoordinate, yCoordinate}};
                    auto coordNE{Point{xCoordinate + 1, yCoordinate}};
                    auto coordSW{Point{xCoordinate, yCoordinate + 1}};
                    auto coordSE{Point{xCoordinate + 1, yCoordinate + 1}};

                    if (!worldArea->IsValidCoordinate(coordNW.x, coordNW.y) ||
                        !worldArea->IsValidCoordinate(coordNE.x, coordNE.y) ||
                        !worldArea->IsValidCoordinate(coordSW.x, coordSW.y) ||
                        !worldArea->IsValidCoordinate(coordSE.x, coordSE.y))
                    {
                        continue;
                    }

                    auto tileNW{worldArea->GetTile(coordNW)};
                    auto tileNE{worldArea->GetTile(coordNE)};
                    auto tileSW{worldArea->GetTile(coordSW)};
                    auto tileSE{worldArea->GetTile(coordSE)};

                    auto ground{tile ? tile->GetGround() : 0};

                    auto groundTypeRendered{ground};

                    xCanvas = x * tileSize.width;
                    yCanvas = y * tileSize.height - tileNW->GetElevation() * tileSize.height / 2;
                    yCanvas += playerElevation * tileSize.height / 2;
                    widthCanvas = tileSize.width;
                    heightCanvas = tileSize.height;

                    // if (ground != Hash("GroundWater"))
                    if (true)
                    {
                        String groundName;

                        if (ground == Hash("GroundGrass"))
                        {
                            groundName = "GroundGrass";
                        }
                        else if (ground == Hash("GroundWater"))
                        {
                            groundName = "GroundDirt";
                        }
                        else if (ground == Hash("GroundDirt"))
                        {
                            groundName = "GroundDirt";
                        }
                        else if (ground == Hash("GroundRock"))
                        {
                            groundName = "GroundRock";
                        }

                        String fullGroundName{groundName};

                        if (tileNW->GetElevation() > tileSW->GetElevation() &&
                            tileNE->GetElevation() > tileSE->GetElevation())
                        {
                            heightCanvas += tileSize.height / 2;
                            fullGroundName = groundName + "SlopeSouth";
                        }
                        else if (tileNW->GetElevation() < tileSW->GetElevation() &&
                                 tileNE->GetElevation() < tileSE->GetElevation())
                        {
                            heightCanvas -= tileSize.height / 2;
                            fullGroundName = groundName + "SlopeNorth";
                        }
                        else if (tileNE->GetElevation() > tileNW->GetElevation() &&
                                 tileSE->GetElevation() > tileSW->GetElevation())
                        {
                            yCanvas -= tileSize.height / 2;
                            heightCanvas += tileSize.height / 2;
                            fullGroundName = groundName + "SlopeWest";
                        }
                        else if (tileNW->GetElevation() > tileNE->GetElevation() &&
                                 tileSW->GetElevation() > tileSE->GetElevation())
                        {
                            heightCanvas += tileSize.height / 2;
                            fullGroundName = groundName + "SlopeEast";
                        }
                        else if (tileNW->GetElevation() > tileNE->GetElevation() &&
                                 tileNW->GetElevation() > tileSE->GetElevation() &&
                                 tileNW->GetElevation() > tileSW->GetElevation())
                        {
                            heightCanvas += tileSize.height / 2;
                            fullGroundName = groundName + "SlopeSouthEast";
                        }
                        else if (tileNE->GetElevation() > tileNW->GetElevation() &&
                                 tileNE->GetElevation() > tileSE->GetElevation() &&
                                 tileNE->GetElevation() > tileSW->GetElevation())
                        {
                            yCanvas -= tileSize.height / 2;
                            heightCanvas += tileSize.height / 2;
                            fullGroundName = groundName + "SlopeSouthWest";
                        }
                        else if (tileSW->GetElevation() > tileNW->GetElevation() &&
                                 tileSW->GetElevation() > tileSE->GetElevation() &&
                                 tileSW->GetElevation() > tileNE->GetElevation())
                        {
                            fullGroundName = groundName + "SlopeNorthEast";
                        }
                        else if (tileSE->GetElevation() > tileNW->GetElevation() &&
                                 tileSE->GetElevation() > tileNE->GetElevation() &&
                                 tileSE->GetElevation() > tileSW->GetElevation())
                        {
                            fullGroundName = groundName + "SlopeNorthWest";
                        }
                        else if (tileSW->GetElevation() < tileNW->GetElevation() &&
                                 tileSW->GetElevation() < tileNE->GetElevation() &&
                                 tileSW->GetElevation() < tileSE->GetElevation())
                        {
                            heightCanvas += tileSize.height / 2;
                            fullGroundName = groundName + "SlopeSouthWestInverted";
                        }
                        else if (tileSE->GetElevation() < tileNW->GetElevation() &&
                                 tileSE->GetElevation() < tileNE->GetElevation() &&
                                 tileSE->GetElevation() < tileSW->GetElevation())
                        {
                            heightCanvas += tileSize.height / 2;
                            fullGroundName = groundName + "SlopeSouthEastInverted";
                        }
                        else if (tileNW->GetElevation() < tileNE->GetElevation() &&
                                 tileNW->GetElevation() < tileSW->GetElevation() &&
                                 tileNW->GetElevation() < tileSE->GetElevation())
                        {
                            yCanvas -= tileSize.height / 2;
                            fullGroundName = groundName + "SlopeNorthWestInverted";
                        }
                        else if (tileNE->GetElevation() < tileNW->GetElevation() &&
                                 tileNE->GetElevation() < tileSW->GetElevation() &&
                                 tileNE->GetElevation() < tileSE->GetElevation())
                        {
                            fullGroundName = groundName + "SlopeNorthEastInverted";
                        }
                        else if (tileSW->GetElevation() == tileNE->GetElevation() && tileNW->GetElevation() < tileSW->GetElevation() && tileSE->GetElevation() < tileSW->GetElevation())
                        {
                            yCanvas -= tileSize.height / 2;
                            heightCanvas += tileSize.height / 2;
                            fullGroundName = groundName + "SlopeDiagonalSouthWestToNorthEast";
                        }
                        else if (tileNW->GetElevation() == tileSE->GetElevation() && tileNE->GetElevation() < tileNW->GetElevation() && tileSW->GetElevation() < tileNW->GetElevation())
                        {
                            heightCanvas += tileSize.height / 2;
                            fullGroundName = groundName + "SlopeDiagonalNorthWestToSouthEast";
                        }

                        // if (ground == Hash("GroundWater"))
                        // {
                        //     auto animIndex{(GetTicks() + ((xCoordinate + yCoordinate) * 100)) / 500 % 3};

                        //     fullGroundName = fullGroundName + "_" + std::to_string(animIndex);
                        // }

                        groundTypeRendered = Hash(fullGroundName);
                    }
                    // else if (ground == Hash("GroundWater"))
                    // {
                    //     auto animIndex{(GetTicks() + ((xCoordinate + yCoordinate) * 100)) / 500 % 3};

                    //     groundTypeRendered = Hash("GroundWater_" + std::to_string(animIndex) + "_New");
                    // }

                    if (i == 0)
                    {
                        _<ImageRenderer>().DrawImage(groundTypeRendered, xCanvas, yCanvas, widthCanvas, heightCanvas);
                    }
                    else if (ground == Hash("GroundWater") && i == 1)
                    {
                        _<ImageRenderer>().DrawImage("GroundWaterEdge_New", xCanvas - tileSize.width * 3 / 2, yCanvas - tileSize.height * 3 / 2, tileSize.width * 4, tileSize.height * 4);
                    }
                    else if (ground == Hash("GroundWater") && i == 2)
                    {
                        auto animIndex{(GetTicks()/2 + ((xCoordinate + yCoordinate) * 100)) / 500 % 3};

                        groundTypeRendered = Hash("GroundWater_" + std::to_string(animIndex) + "_New");

                        _<ImageRenderer>().DrawImage(groundTypeRendered, xCanvas, yCanvas, widthCanvas, heightCanvas);
                        _<ImageRenderer>().DrawImage(groundTypeRendered, xCanvas - tileSize.width * 3 / 2, yCanvas - tileSize.height * 3 / 2, tileSize.width * 4, tileSize.height * 4);

                        if (ground == Hash("GroundWater"))
                        {
                            for (auto i = 0; i < tile->GetWaterDepth(); i++)
                            {
                                _<ImageRenderer>().DrawImage("GroundWaterDepth_New", xCanvas - tileSize.width * 3 / 2, yCanvas - tileSize.height * 3 / 2, tileSize.width * 4, tileSize.height * 4);
                            }
                        }
                    }

                    if (ground == Hash("GroundGrass"))
                    {
                        _<ImageRenderer>().DrawImage("GroundGrassLayer", xCanvas, yCanvas, widthCanvas, heightCanvas);
                    }
                    else if (ground == Hash("GroundDirt"))
                    {
                        _<ImageRenderer>().DrawImage("GroundDirtLayer", xCanvas, yCanvas, widthCanvas, heightCanvas);
                    }
                    else if (ground == Hash("GroundRock"))
                    {
                        _<ImageRenderer>().DrawImage("GroundRockLayer", xCanvas, yCanvas, widthCanvas, heightCanvas);
                    }

                    if (i < 2)
                    {
                        continue;
                    }

                    // if (ground == Hash("GroundWater"))
                    // {
                    //     Point N{xCoordinate, yCoordinate - 1};
                    //     Point S{xCoordinate, yCoordinate + 1};
                    //     Point W{xCoordinate - 1, yCoordinate};
                    //     Point E{xCoordinate + 1, yCoordinate};

                    //     auto tileN{worldArea->IsValidCoordinate(N.x, N.y) ? worldArea->GetTile(N) : nullptr};
                    //     auto tileS{worldArea->IsValidCoordinate(S.x, S.y) ? worldArea->GetTile(S) : nullptr};
                    //     auto tileW{worldArea->IsValidCoordinate(W.x, W.y) ? worldArea->GetTile(W) : nullptr};
                    //     auto tileE{worldArea->IsValidCoordinate(E.x, E.y) ? worldArea->GetTile(E) : nullptr};

                    //     if (tileN && tileN->GetGround() != Hash("GroundWater"))
                    //     {
                    //         _<ImageRenderer>().DrawImage("EdgeNorth", xCanvas, yCanvas, widthCanvas, heightCanvas);
                    //     }

                    //     if (tileE && tileE->GetGround() != Hash("GroundWater"))
                    //     {
                    //         _<ImageRenderer>().DrawImage("EdgeEast", xCanvas, yCanvas, widthCanvas, heightCanvas);
                    //     }

                    //     if (tileS && tileS->GetGround() != Hash("GroundWater"))
                    //     {
                    //         _<ImageRenderer>().DrawImage("EdgeSouth", xCanvas, yCanvas, widthCanvas, heightCanvas);
                    //     }

                    //     if (tileW && tileW->GetGround() != Hash("GroundWater"))
                    //     {
                    //         _<ImageRenderer>().DrawImage("EdgeWest", xCanvas, yCanvas, widthCanvas, heightCanvas);
                    //     }
                    // }

                    auto hoveredCoordinate{_<TileHovering>().GetHoveredCoordinate()};

                    if (xCoordinate == hoveredCoordinate.x && yCoordinate == hoveredCoordinate.y)
                    {
                        _<ImageRenderer>().DrawImage("HoveredTile", xCanvas, yCanvas, widthCanvas, heightCanvas);
                    }

                    auto playerDestination{_<Player>().GetDestination()};

                    if (xCoordinate == playerDestination.x && yCoordinate == playerDestination.y)
                    {
                        _<ImageRenderer>().DrawImage("DestinationTile", xCanvas, yCanvas, widthCanvas, heightCanvas);
                    }

                    if (xCoordinate == playerPosition.x &&
                        yCoordinate == playerPosition.y)
                    {
                        _<ImageRenderer>().DrawImage("Shadow", xCanvas, yCanvas, widthCanvas, heightCanvas);
                        _<ImageRenderer>().DrawImage("Player", xCanvas, yCanvas, tileSize.width, tileSize.height);
                    }

                    auto objectsStack{tile ? tile->GetObjectsStack() : nullptr};

                    if (objectsStack)
                    {
                        for (const auto &object : objectsStack->GetObjects())
                        {
                            if (object->GetType() != Hash("ObjectPinkFlower"))
                            {
                                _<ImageRenderer>().DrawImage("Shadow", xCanvas, yCanvas, tileSize.width, tileSize.height);
                            }

                            auto objectType{object->GetType()};

                            if (objectType == Hash("ObjectFirTree") || objectType == Hash("ObjectBirchTree"))
                            {
                                auto treeObject{std::static_pointer_cast<TreeObject>(object)};

                                auto trunkParts{treeObject->GetTrunkparts()};
                                auto needleTypes{treeObject->GetNeedleTypes()};

                                auto widthFactor{treeObject->GetWidthFactor()};

                                for (auto i = 0; i < trunkParts.size(); i++)
                                {
                                    auto trunkPart{trunkParts.at(i)};
                                    auto needleType{needleTypes.at(i)};

                                    auto widthDecreaseFactor{0.5f + (trunkParts.size() - i) / static_cast<float>(trunkParts.size()) / 2};

                                    auto treeWidth{tileSize.width * widthFactor * widthDecreaseFactor};

                                    auto trunkPartX{trunkPart.x};

                                    trunkPartX *= static_cast<float>(i) / trunkParts.size() * std::sin(GetTicks() / 700.0f);

                                    auto trunkPartXCenter{xCanvas + tileSize.width / 2 + trunkPartX * treeWidth};
                                    auto trunkPartYCenter{yCanvas + tileSize.height - trunkPart.y * tileSize.height};
                                    auto trunkPartWidth{tileSize.width * 0.2f * widthDecreaseFactor};
                                    auto trunkPartHeight{tileSize.height * 0.2f};

                                    std::string trunkPartName;

                                    if (objectType == Hash("ObjectFirTree"))
                                    {
                                        trunkPartName = "ObjectFirTreeTrunkPart";
                                    }
                                    else if (objectType == Hash("ObjectBirchTree"))
                                    {
                                        trunkPartName = "ObjectBirchTreeTrunkPart";
                                    }

                                    _<ImageRenderer>().DrawImage(trunkPartName, trunkPartXCenter - trunkPartWidth / 2, trunkPartYCenter - trunkPartHeight / 2, trunkPartWidth, trunkPartHeight);

                                    auto needleWidth{treeWidth};
                                    auto needleHeight{tileSize.height};

                                    if (needleType)
                                    {
                                        _<ImageRenderer>().DrawImage(needleType, trunkPartXCenter - needleWidth / 2, trunkPartYCenter - needleHeight / 2, needleWidth, needleHeight);
                                    }
                                }

                                continue;
                            }

                            auto objectImageSize{
                                _<ImageBank>().GetImageSize(objectType)};

                            auto objectWidth{objectImageSize.width / 60.0f * tileSize.width};
                            auto objectHeight{objectImageSize.height / 60.0f * tileSize.height};

                            _<ImageRenderer>().DrawImage(objectType, xCanvas + tileSize.width / 2 - objectWidth / 2, yCanvas + tileSize.height - objectHeight, objectWidth, objectHeight);
                        }
                    }

                    auto creature{tile ? tile->GetCreature() : nullptr};

                    if (creature)
                    {
                        auto creatureType{creature->GetType()};

                        auto creatureImageSize{
                            _<ImageBank>().GetImageSize(creatureType)};

                        auto creatureWidth{creatureImageSize.width / 60.0f * tileSize.width};
                        auto creatureHeight{creatureImageSize.height / 60.0f * tileSize.height};

                        _<ImageRenderer>().DrawImage(creatureType, xCanvas + tileSize.width / 2 - creatureWidth / 2, yCanvas + tileSize.height - creatureHeight, creatureWidth, creatureHeight);
                    }
                }
            }
        }
    }
}