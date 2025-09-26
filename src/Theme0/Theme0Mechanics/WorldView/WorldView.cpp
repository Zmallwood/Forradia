#include "WorldView.hpp"
#include "Core/Rendering/ImageRenderer.hpp"
#include "Core/Assets/ImageBank.hpp"
#include "Theme0/Theme0Mechanics/Math/TileGridMath.hpp"
#include "Theme0/Theme0Mechanics/CoreGameObjects/Player.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/World.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/WorldArea.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/Tile.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/ObjectsStack.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/Object.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/Mob.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/TreeObject.hpp"

namespace Forradia
{
    void WorldView::Render() const
    {
        auto gridSize{CalculateGridSize()};

        auto tileSize{CalculateTileSize()};

        auto playerPosition{_<Player>().GetPosition()};

        auto worldArea{_<World>().GetCurrentWorldArea()};

        for (auto y = 0; y < gridSize.height; y++)
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

                xCanvas = x * tileSize.width;
                yCanvas = y * tileSize.height - tileNW->GetElevation() * tileSize.height / 2;
                widthCanvas = tileSize.width;
                heightCanvas = tileSize.height;

                if (ground == Hash("GroundGrass"))
                {
                    if (tileNW->GetElevation() > tileSW->GetElevation() &&
                        tileNE->GetElevation() > tileSE->GetElevation())
                    {
                        heightCanvas += tileSize.height / 2;
                        ground = Hash("GroundGrassSlopeSouth");
                    }
                    else if (tileNW->GetElevation() < tileSW->GetElevation() &&
                             tileNE->GetElevation() < tileSE->GetElevation())
                    {
                        heightCanvas -= tileSize.height / 2;
                        ground = Hash("GroundGrassSlopeNorth");
                    }
                    else if (tileNE->GetElevation() > tileNW->GetElevation() &&
                             tileSE->GetElevation() > tileSW->GetElevation())
                    {
                        yCanvas -= tileSize.height / 2;
                        heightCanvas += tileSize.height / 2;
                        ground = Hash("GroundGrassSlopeWest");
                    }
                    else if (tileNW->GetElevation() > tileNE->GetElevation() &&
                             tileSW->GetElevation() > tileSE->GetElevation())
                    {
                        heightCanvas += tileSize.height / 2;
                        ground = Hash("GroundGrassSlopeEast");
                    }
                    else if (tileNW->GetElevation() > tileNE->GetElevation() &&
                             tileNW->GetElevation() > tileSE->GetElevation() &&
                             tileNW->GetElevation() > tileSW->GetElevation())
                    {
                        heightCanvas += tileSize.height / 2;
                        ground = Hash("GroundGrassSlopeSouthEast");
                    }
                    else if (tileNE->GetElevation() > tileNW->GetElevation() &&
                             tileNE->GetElevation() > tileSE->GetElevation() &&
                             tileNE->GetElevation() > tileSW->GetElevation())
                    {
                        yCanvas -= tileSize.height / 2;
                        heightCanvas += tileSize.height / 2;
                        ground = Hash("GroundGrassSlopeSouthWest");
                    }
                    else if (tileSW->GetElevation() > tileNW->GetElevation() &&
                             tileSW->GetElevation() > tileSE->GetElevation() &&
                             tileSW->GetElevation() > tileNE->GetElevation())
                    {
                        ground = Hash("GroundGrassSlopeNorthEast");
                    }
                    else if (tileSE->GetElevation() > tileNW->GetElevation() &&
                             tileSE->GetElevation() > tileNE->GetElevation() &&
                             tileSE->GetElevation() > tileSW->GetElevation())
                    {
                        ground = Hash("GroundGrassSlopeNorthWest");
                    }
                    else if (tileSW->GetElevation() < tileNW->GetElevation() &&
                             tileSW->GetElevation() < tileNE->GetElevation() &&
                             tileSW->GetElevation() < tileSE->GetElevation())
                    {
                        heightCanvas += tileSize.height / 2;
                        ground = Hash("GroundGrassSlopeSouthWestInverted");
                    }
                    else if (tileSE->GetElevation() < tileNW->GetElevation() &&
                             tileSE->GetElevation() < tileNE->GetElevation() &&
                             tileSE->GetElevation() < tileSW->GetElevation())
                    {
                        heightCanvas += tileSize.height / 2;
                        ground = Hash("GroundGrassSlopeSouthEastInverted");
                    }
                    else if (tileNW->GetElevation() < tileNE->GetElevation() &&
                             tileNW->GetElevation() < tileSW->GetElevation() &&
                             tileNW->GetElevation() < tileSE->GetElevation())
                    {
                        yCanvas -= tileSize.height / 2;
                        ground = Hash("GroundGrassSlopeNorthWestInverted");
                    }
                    else if (tileNE->GetElevation() < tileNW->GetElevation() &&
                             tileNE->GetElevation() < tileSW->GetElevation() &&
                             tileNE->GetElevation() < tileSE->GetElevation())
                    {
                        ground = Hash("GroundGrassSlopeNorthEastInverted");
                    }
                    else if (tileSW->GetElevation() == tileNE->GetElevation() && tileNW->GetElevation() < tileSW->GetElevation() && tileSE->GetElevation() < tileSW->GetElevation())
                    {
                        yCanvas -= tileSize.height / 2;
                        heightCanvas += tileSize.height / 2;
                        ground = Hash("GroundGrassSlopeDiagonalSouthWestToNorthEast");
                    }
                    else if (tileNW->GetElevation() == tileSE->GetElevation() && tileNE->GetElevation() < tileNW->GetElevation() && tileSW->GetElevation() < tileNW->GetElevation())
                    {
                        heightCanvas += tileSize.height / 2;
                        ground = Hash("GroundGrassSlopeDiagonalNorthWestToSouthEast");
                    }
                }

                _<ImageRenderer>().DrawImage(ground, xCanvas, yCanvas, widthCanvas, heightCanvas);

                if (xCoordinate == playerPosition.x &&
                    yCoordinate == playerPosition.y)
                {
                    _<ImageRenderer>().DrawImage("Player", xCanvas, yCanvas, widthCanvas, heightCanvas);
                }

                auto objectsStack{tile ? tile->GetObjectsStack() : nullptr};

                if (objectsStack)
                {
                    for (const auto &object : objectsStack->GetObjects())
                    {
                        auto objectType{object->GetType()};

                        if (objectType == Hash("ObjectFirTree"))
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

                                auto trunkPartXCenter{xCanvas + tileSize.width / 2 + trunkPart.x * treeWidth};
                                auto trunkPartYCenter{yCanvas + tileSize.height - trunkPart.y * tileSize.height};
                                auto trunkPartWidth{tileSize.width * 0.2f * widthDecreaseFactor};
                                auto trunkPartHeight{tileSize.height * 0.2f};

                                _<ImageRenderer>().DrawImage("ObjectFirTreeTrunkPart", trunkPartXCenter - trunkPartWidth / 2, trunkPartYCenter - trunkPartHeight / 2, trunkPartWidth, trunkPartHeight);

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

                auto mob{tile ? tile->GetMob() : nullptr};

                if (mob)
                {
                    auto mobType{mob->GetType()};

                    auto mobImageSize{
                        _<ImageBank>().GetImageSize(mobType)};

                    auto mobWidth{mobImageSize.width / 60.0f * tileSize.width};
                    auto mobHeight{mobImageSize.height / 60.0f * tileSize.height};

                    _<ImageRenderer>().DrawImage(mobType, xCanvas + tileSize.width / 2 - mobWidth / 2, yCanvas + tileSize.height - mobHeight, mobWidth, mobHeight);
                }
            }
        }
    }
}