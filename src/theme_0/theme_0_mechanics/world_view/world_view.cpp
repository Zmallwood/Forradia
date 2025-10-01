/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "world_view.hpp"
#include "core/image_assets/image_bank.hpp"
#include "core/rendering/images/image_renderer.hpp"
#include "theme_0/theme_0_mechanics/core_game_objects/player.hpp"
#include "theme_0/theme_0_mechanics/math/tile_grid_math.hpp"
#include "theme_0/theme_0_mechanics/world_interaction/tile_hovering.hpp"
#include "theme_0/theme_0_mechanics/world_structure/creature.hpp"
#include "theme_0/theme_0_mechanics/world_structure/object.hpp"
#include "theme_0/theme_0_mechanics/world_structure/objects_stack.hpp"
#include "theme_0/theme_0_mechanics/world_structure/tile.hpp"
#include "theme_0/theme_0_mechanics/world_structure/tree_object.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world_area.hpp"

namespace forr {
  void world_view::Render() const {
    auto gridSize{CalculateGridSize()};
    auto tileSize{CalculateTileSize()};
    auto playerPosition{GetSingleton<player>().GetPosition()};
    auto worldArea{GetSingleton<world>().GetCurrentWorldArea()};
    auto playerElevation{worldArea->GetTile(playerPosition)->GetElevation()};
    auto extraRows{8};
    for (auto i = 0; i < 3; i++) {
      for (auto y = -extraRows; y < gridSize.height + extraRows; y++) {
        for (auto x = 0; x < gridSize.width; x++) {
          auto xCoordinate{playerPosition.x - (gridSize.width - 1) / 2 + x};
          auto yCoordinate{playerPosition.y - (gridSize.height - 1) / 2 + y};
          if (!worldArea->IsValidCoordinate(xCoordinate, yCoordinate)) {
            continue;
          }
          auto tile{worldArea->GetTile(xCoordinate, yCoordinate)};
          float xCanvas;
          float yCanvas;
          float widthCanvas;
          float heightCanvas;
          auto coordNW{point{xCoordinate, yCoordinate}};
          auto coordNE{point{xCoordinate + 1, yCoordinate}};
          auto coordSW{point{xCoordinate, yCoordinate + 1}};
          auto coordSE{point{xCoordinate + 1, yCoordinate + 1}};
          if (!worldArea->IsValidCoordinate(coordNW.x, coordNW.y) ||
              !worldArea->IsValidCoordinate(coordNE.x, coordNE.y) ||
              !worldArea->IsValidCoordinate(coordSW.x, coordSW.y) ||
              !worldArea->IsValidCoordinate(coordSE.x, coordSE.y)) {
            continue;
          }
          auto tileNW{worldArea->GetTile(coordNW)};
          auto tileNE{worldArea->GetTile(coordNE)};
          auto tileSW{worldArea->GetTile(coordSW)};
          auto tileSE{worldArea->GetTile(coordSE)};
          auto ground{tile ? tile->GetGround() : 0};
          auto groundTypeRendered{ground};
          xCanvas = x * tileSize.width;
          yCanvas = y * tileSize.height -
                    tileNW->GetElevation() * tileSize.height / 2;
          yCanvas += playerElevation * tileSize.height / 2;
          widthCanvas = tileSize.width;
          heightCanvas = Ceil(tileSize.height, 2.5f);
          // if (ground != Hash("GroundWater"))
          if (true) {
            str groundName;
            if (ground == Hash("GroundGrass")) {
              groundName = "GroundGrass";
            } else if (ground == Hash("GroundWater")) {
              groundName = "GroundDirt";
            } else if (ground == Hash("GroundDirt")) {
              groundName = "GroundDirt";
            } else if (ground == Hash("GroundRock")) {
              groundName = "GroundRock";
            }
            str fullGroundName{groundName};
            if (tileNW->GetElevation() > tileSW->GetElevation() &&
                tileNE->GetElevation() > tileSE->GetElevation()) {
              heightCanvas += tileSize.height / 2;
              fullGroundName = groundName + "SlopeSouth";
            } else if (tileNW->GetElevation() < tileSW->GetElevation() &&
                       tileNE->GetElevation() < tileSE->GetElevation()) {
              heightCanvas -= tileSize.height / 2;
              fullGroundName = groundName + "SlopeNorth";
            } else if (tileNE->GetElevation() > tileNW->GetElevation() &&
                       tileSE->GetElevation() > tileSW->GetElevation()) {
              yCanvas -= tileSize.height / 2;
              heightCanvas += tileSize.height / 2;
              fullGroundName = groundName + "SlopeWest";
            } else if (tileNW->GetElevation() > tileNE->GetElevation() &&
                       tileSW->GetElevation() > tileSE->GetElevation()) {
              heightCanvas += tileSize.height / 2;
              fullGroundName = groundName + "SlopeEast";
            } else if (tileNW->GetElevation() > tileNE->GetElevation() &&
                       tileNW->GetElevation() > tileSE->GetElevation() &&
                       tileNW->GetElevation() > tileSW->GetElevation()) {
              heightCanvas += tileSize.height / 2;
              fullGroundName = groundName + "SlopeSouthEast";
            } else if (tileNE->GetElevation() > tileNW->GetElevation() &&
                       tileNE->GetElevation() > tileSE->GetElevation() &&
                       tileNE->GetElevation() > tileSW->GetElevation()) {
              yCanvas -= tileSize.height / 2;
              heightCanvas += tileSize.height / 2;
              fullGroundName = groundName + "SlopeSouthWest";
            } else if (tileSW->GetElevation() > tileNW->GetElevation() &&
                       tileSW->GetElevation() > tileSE->GetElevation() &&
                       tileSW->GetElevation() > tileNE->GetElevation()) {
              fullGroundName = groundName + "SlopeNorthEast";
            } else if (tileSE->GetElevation() > tileNW->GetElevation() &&
                       tileSE->GetElevation() > tileNE->GetElevation() &&
                       tileSE->GetElevation() > tileSW->GetElevation()) {
              fullGroundName = groundName + "SlopeNorthWest";
            } else if (tileSW->GetElevation() < tileNW->GetElevation() &&
                       tileSW->GetElevation() < tileNE->GetElevation() &&
                       tileSW->GetElevation() < tileSE->GetElevation()) {
              heightCanvas += tileSize.height / 2;
              fullGroundName = groundName + "SlopeSouthWestInverted";
            } else if (tileSE->GetElevation() < tileNW->GetElevation() &&
                       tileSE->GetElevation() < tileNE->GetElevation() &&
                       tileSE->GetElevation() < tileSW->GetElevation()) {
              heightCanvas += tileSize.height / 2;
              fullGroundName = groundName + "SlopeSouthEastInverted";
            } else if (tileNW->GetElevation() < tileNE->GetElevation() &&
                       tileNW->GetElevation() < tileSW->GetElevation() &&
                       tileNW->GetElevation() < tileSE->GetElevation()) {
              yCanvas -= tileSize.height / 2;
              fullGroundName = groundName + "SlopeNorthWestInverted";
            } else if (tileNE->GetElevation() < tileNW->GetElevation() &&
                       tileNE->GetElevation() < tileSW->GetElevation() &&
                       tileNE->GetElevation() < tileSE->GetElevation()) {
              fullGroundName = groundName + "SlopeNorthEastInverted";
            } else if (tileSW->GetElevation() == tileNE->GetElevation() &&
                       tileNW->GetElevation() < tileSW->GetElevation() &&
                       tileSE->GetElevation() < tileSW->GetElevation()) {
              yCanvas -= tileSize.height / 2;
              heightCanvas += tileSize.height / 2;
              fullGroundName = groundName + "SlopeDiagonalSouthWestToNorthEast";
            } else if (tileNW->GetElevation() == tileSE->GetElevation() &&
                       tileNE->GetElevation() < tileNW->GetElevation() &&
                       tileSW->GetElevation() < tileNW->GetElevation()) {
              heightCanvas += tileSize.height / 2;
              fullGroundName = groundName + "SlopeDiagonalNorthWestToSouthEast";
            }
            // if (ground == Hash("GroundWater"))
            // {
            //     auto animIndex{(GetTicks() + ((xCoordinate + yCoordinate) *
            //     100)) / 500 % 3};
            //     fullGroundName = fullGroundName + "_" +
            //     std::to_string(animIndex);
            // }
            groundTypeRendered = Hash(fullGroundName);
          }
          // else if (ground == Hash("GroundWater"))
          // {
          //     auto animIndex{(GetTicks() + ((xCoordinate + yCoordinate) *
          //     100)) / 500 % 3};
          //     groundTypeRendered = Hash("GroundWater_" +
          //     std::to_string(animIndex) + "_New");
          // }
          if (i == 0) {
            GetSingleton<image_renderer>().DrawImage(groundTypeRendered,
                                                     xCanvas, yCanvas,
                                                     widthCanvas, heightCanvas);
          } else if (ground != Hash("GroundWater") && i == 1) {
            vec<directions> riverDirections{tile->GetRiverDirection1(),
                                            tile->GetRiverDirection2()};
            auto riverPartWidth{0.4f * widthCanvas};
            auto riverPartHeight{0.4f * heightCanvas};
            auto partLenght{2.5f};
            auto animIndex{(GetTicks() + ((xCoordinate + yCoordinate) * 100)) /
                           500 % 3};
            for (auto j = 0; j < 2; j++) {
              switch (riverDirections.at(j)) {
              case directions::North: {
                for (auto k = 0.0f; k < partLenght; k += 0.5f) {
                  rect_f bounds{xCanvas + widthCanvas / 2 - riverPartWidth / 2,
                               yCanvas + heightCanvas / 2 -
                                   riverPartHeight / 2 - k * riverPartHeight,
                               riverPartWidth, riverPartHeight};
                  GetSingleton<image_renderer>().DrawImage(
                      "RiverPart_" + std::to_string(animIndex), bounds.x,
                      bounds.y, bounds.width, bounds.height);
                }
              } break;
              case directions::East: {
                for (auto k = 0.0f; k < partLenght; k += 0.5f) {
                  rect_f bounds{xCanvas + widthCanvas / 2 - riverPartWidth / 2 +
                                   k * riverPartWidth,
                               yCanvas + heightCanvas / 2 - riverPartHeight / 2,
                               riverPartWidth, riverPartHeight};
                  GetSingleton<image_renderer>().DrawImage(
                      "RiverPart_" + std::to_string(animIndex), bounds.x,
                      bounds.y, bounds.width, bounds.height);
                }
              } break;
              case directions::South: {
                for (auto k = 0.0f; k < partLenght; k += 0.5f) {
                  rect_f bounds{xCanvas + widthCanvas / 2 - riverPartWidth / 2,
                               yCanvas + heightCanvas / 2 +
                                   riverPartHeight / 2 + k * riverPartHeight,
                               riverPartWidth, riverPartHeight};
                  GetSingleton<image_renderer>().DrawImage(
                      "RiverPart_" + std::to_string(animIndex), bounds.x,
                      bounds.y, bounds.width, bounds.height);
                }
              } break;
              case directions::West: {
                for (auto k = 0.0f; k < partLenght; k += 0.5f) {
                  rect_f bounds{xCanvas + widthCanvas / 2 - riverPartWidth / 2 -
                                   k * riverPartWidth,
                               yCanvas + heightCanvas / 2 - riverPartHeight / 2,
                               riverPartWidth, riverPartHeight};
                  GetSingleton<image_renderer>().DrawImage(
                      "RiverPart_" + std::to_string(animIndex), bounds.x,
                      bounds.y, bounds.width, bounds.height);
                }
              } break;
              case directions::NorthEast: {
                for (auto k = 0.0f; k < partLenght; k += 0.5f) {
                  rect_f bounds{xCanvas + widthCanvas / 2 - riverPartWidth / 2 +
                                   k * riverPartWidth,
                               yCanvas + heightCanvas / 2 -
                                   riverPartHeight / 2 - k * riverPartHeight,
                               riverPartWidth, riverPartHeight};
                  GetSingleton<image_renderer>().DrawImage(
                      "RiverPart_" + std::to_string(animIndex), bounds.x,
                      bounds.y, bounds.width, bounds.height);
                }
              } break;
              case directions::SouthEast: {
                for (auto k = 0.0f; k < partLenght; k += 0.5f) {
                  rect_f bounds{xCanvas + widthCanvas / 2 - riverPartWidth / 2 +
                                   k * riverPartWidth,
                               yCanvas + heightCanvas / 2 -
                                   riverPartHeight / 2 + k * riverPartHeight,
                               riverPartWidth, riverPartHeight};
                  GetSingleton<image_renderer>().DrawImage(
                      "RiverPart_" + std::to_string(animIndex), bounds.x,
                      bounds.y, bounds.width, bounds.height);
                }
              } break;
              case directions::SouthWest: {
                for (auto k = 0.0f; k < partLenght; k += 0.5f) {
                  rect_f bounds{xCanvas + widthCanvas / 2 - riverPartWidth / 2 -
                                   k * riverPartWidth,
                               yCanvas + heightCanvas / 2 -
                                   riverPartHeight / 2 + k * riverPartHeight,
                               riverPartWidth, riverPartHeight};
                  GetSingleton<image_renderer>().DrawImage(
                      "RiverPart_" + std::to_string(animIndex), bounds.x,
                      bounds.y, bounds.width, bounds.height);
                }
              } break;
              case directions::NorthWest: {
                for (auto k = 0.0f; k < partLenght; k += 0.5f) {
                  rect_f bounds{xCanvas + widthCanvas / 2 - riverPartWidth / 2 -
                                   k * riverPartWidth,
                               yCanvas + heightCanvas / 2 -
                                   riverPartHeight / 2 - k * riverPartHeight,
                               riverPartWidth, riverPartHeight};
                  GetSingleton<image_renderer>().DrawImage(
                      "RiverPart_" + std::to_string(animIndex), bounds.x,
                      bounds.y, bounds.width, bounds.height);
                }
              } break;
              }
            }
          } else if (ground == Hash("GroundWater") && i == 1) {
            auto animIndex{(GetTicks() + ((xCoordinate + yCoordinate) * 100)) /
                           500 % 3};
            GetSingleton<image_renderer>().DrawImage(
                "GroundWaterEdge", xCanvas - widthCanvas * 0.2f,
                yCanvas - heightCanvas * 0.2f, widthCanvas * 1.4f,
                heightCanvas * 1.4f);
          } else if (ground == Hash("GroundWater") && i == 2) {

            auto animIndex{(GetTicks() + ((xCoordinate + yCoordinate) * 100)) /
                           500 % 3};
            GetSingleton<image_renderer>().DrawImage(
                "GroundWater_" + std::to_string(animIndex), xCanvas, yCanvas,
                widthCanvas, heightCanvas);

            for (auto i = 0; i < tile->GetElevation(); i++) {
              GetSingleton<image_renderer>().DrawImage(
                  "GroundWaterHeight", xCanvas, yCanvas, widthCanvas,
                  heightCanvas);
            }

            // groundTypeRendered = Hash("GroundWater_" +
            // std::to_string(animIndex) + "_New");
            // _<ImageRenderer>().DrawImage(groundTypeRendered, xCanvas -
            // tileSize.width * 3 / 2, yCanvas - tileSize.height * 3 / 2,
            // tileSize.width * 4, tileSize.height * 4);
            if (ground == Hash("GroundWater")) {
              for (auto i = 0; i < tile->GetWaterDepth(); i++) {
                GetSingleton<image_renderer>().DrawImage(
                    "GroundWaterDepth", xCanvas, yCanvas, widthCanvas,
                    heightCanvas);
              }
            }
          }
          if (ground == Hash("GroundGrass")) {
            GetSingleton<image_renderer>().DrawImage("GroundGrassLayer",
                                                     xCanvas, yCanvas,
                                                     widthCanvas, heightCanvas);
          } else if (ground == Hash("GroundDirt")) {
            GetSingleton<image_renderer>().DrawImage(
                "GroundDirtLayer", xCanvas, yCanvas, widthCanvas, heightCanvas);
          } else if (ground == Hash("GroundRock")) {
            GetSingleton<image_renderer>().DrawImage(
                "GroundRockLayer", xCanvas, yCanvas, widthCanvas, heightCanvas);
          }
          if (i < 2) {
            continue;
          }
          // if (ground == Hash("GroundWater"))
          // {
          //     point N{xCoordinate, yCoordinate - 1};
          //     point S{xCoordinate, yCoordinate + 1};
          //     point W{xCoordinate - 1, yCoordinate};
          //     point E{xCoordinate + 1, yCoordinate};
          //     auto tileN{worldArea->IsValidCoordinate(N.x, N.y) ?
          //     worldArea->GetTile(N) : nullptr}; auto
          //     tileS{worldArea->IsValidCoordinate(S.x, S.y) ?
          //     worldArea->GetTile(S) : nullptr}; auto
          //     tileW{worldArea->IsValidCoordinate(W.x, W.y) ?
          //     worldArea->GetTile(W) : nullptr}; auto
          //     tileE{worldArea->IsValidCoordinate(E.x, E.y) ?
          //     worldArea->GetTile(E) : nullptr};
          //     if (tileN && tileN->GetGround() != Hash("GroundWater"))
          //     {
          //         _<ImageRenderer>().DrawImage("EdgeNorth", xCanvas, yCanvas,
          //         widthCanvas, heightCanvas);
          //     }
          //     if (tileE && tileE->GetGround() != Hash("GroundWater"))
          //     {
          //         _<ImageRenderer>().DrawImage("EdgeEast", xCanvas, yCanvas,
          //         widthCanvas, heightCanvas);
          //     }
          //     if (tileS && tileS->GetGround() != Hash("GroundWater"))
          //     {
          //         _<ImageRenderer>().DrawImage("EdgeSouth", xCanvas, yCanvas,
          //         widthCanvas, heightCanvas);
          //     }
          //     if (tileW && tileW->GetGround() != Hash("GroundWater"))
          //     {
          //         _<ImageRenderer>().DrawImage("EdgeWest", xCanvas, yCanvas,
          //         widthCanvas, heightCanvas);
          //     }
          // }
          auto hoveredCoordinate{
              GetSingleton<tile_hovering>().GetHoveredCoordinate()};
          if (xCoordinate == hoveredCoordinate.x &&
              yCoordinate == hoveredCoordinate.y) {
            GetSingleton<image_renderer>().DrawImage(
                "HoveredTile", xCanvas, yCanvas, widthCanvas, heightCanvas);
          }
          auto playerDestination{GetSingleton<player>().GetDestination()};
          if (xCoordinate == playerDestination.x &&
              yCoordinate == playerDestination.y) {
            GetSingleton<image_renderer>().DrawImage(
                "DestinationTile", xCanvas, yCanvas, widthCanvas, heightCanvas);
          }
          if (xCoordinate == playerPosition.x &&
              yCoordinate == playerPosition.y) {
            GetSingleton<image_renderer>().DrawImage("Shadow", xCanvas, yCanvas,
                                                     widthCanvas, heightCanvas);
            GetSingleton<image_renderer>().DrawImage(
                "Player", xCanvas, yCanvas, tileSize.width, tileSize.height);
          }
          auto objectsStack{tile ? tile->GetObjectsStack() : nullptr};
          if (objectsStack) {
            for (const auto &object : objectsStack->GetObjects()) {
              if (object->GetType() != Hash("ObjectPinkFlower")) {
                GetSingleton<image_renderer>().DrawImage(
                    "Shadow", xCanvas, yCanvas, tileSize.width,
                    tileSize.height);
              }
              auto objectType{object->GetType()};
              if (objectType == Hash("ObjectFirTree") ||
                  objectType == Hash("ObjectBirchTree")) {
                auto treeObject{std::static_pointer_cast<tree_object>(object)};
                auto trunkParts{treeObject->GetTrunkparts()};
                auto needleTypes{treeObject->GetNeedleTypes()};
                auto widthFactor{treeObject->GetWidthFactor()};
                for (auto i = 0; i < trunkParts.size(); i++) {
                  auto trunkPart{trunkParts.at(i)};
                  auto needleType{needleTypes.at(i)};
                  auto widthDecreaseFactor{0.5f +
                                           (trunkParts.size() - i) /
                                               CFloat(trunkParts.size()) / 2};
                  auto treeWidth{tileSize.width * widthFactor *
                                 widthDecreaseFactor};
                  auto trunkPartX{trunkPart.x};
                  trunkPartX *=
                      CFloat(i) / trunkParts.size() *
                      std::sin(GetTicks() / 700.0f + xCoordinate * yCoordinate);
                  auto trunkPartXCenter{xCanvas + tileSize.width / 2 +
                                        trunkPartX * treeWidth};
                  auto trunkPartYCenter{yCanvas + tileSize.height -
                                        trunkPart.y * tileSize.height};
                  auto trunkPartWidth{tileSize.width * 0.2f *
                                      widthDecreaseFactor};
                  auto trunkPartHeight{tileSize.height * 0.2f};
                  str trunkPartName;
                  if (objectType == Hash("ObjectFirTree")) {
                    trunkPartName = "ObjectFirTreeTrunkPart";
                  } else if (objectType == Hash("ObjectBirchTree")) {
                    trunkPartName = "ObjectBirchTreeTrunkPart";
                  }
                  GetSingleton<image_renderer>().DrawImage(
                      trunkPartName, trunkPartXCenter - trunkPartWidth / 2,
                      trunkPartYCenter - trunkPartHeight / 2, trunkPartWidth,
                      trunkPartHeight);
                  auto needleWidth{treeWidth};
                  auto needleHeight{tileSize.height};
                  if (needleType) {
                    GetSingleton<image_renderer>().DrawImage(
                        needleType, trunkPartXCenter - needleWidth / 2,
                        trunkPartYCenter - needleHeight / 2, needleWidth,
                        needleHeight);
                  }
                }
                continue;
              }
              auto objectImageSize{
                  GetSingleton<image_bank>().GetImageSize(objectType)};
              auto objectWidth{objectImageSize.width / 60.0f * tileSize.width};
              auto objectHeight{objectImageSize.height / 60.0f *
                                tileSize.height};
              GetSingleton<image_renderer>().DrawImage(
                  objectType, xCanvas + tileSize.width / 2 - objectWidth / 2,
                  yCanvas + tileSize.height - objectHeight, objectWidth,
                  objectHeight);
            }
          }
          auto creature{tile ? tile->GetCreature() : nullptr};
          if (creature) {
            auto creatureType{creature->GetType()};
            auto creatureImageSize{
                GetSingleton<image_bank>().GetImageSize(creatureType)};
            auto creatureWidth{creatureImageSize.width / 60.0f *
                               tileSize.width};
            auto creatureHeight{creatureImageSize.height / 60.0f *
                                tileSize.height};
            GetSingleton<image_renderer>().DrawImage(
                creatureType, xCanvas + tileSize.width / 2 - creatureWidth / 2,
                yCanvas + tileSize.height - creatureHeight, creatureWidth,
                creatureHeight);
          }
        }
      }
    }
  }
}