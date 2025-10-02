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
  void world_view::render() const {
    auto gridSize{calculate_grid_size()};
    auto tileSize{calculate_tile_size()};
    auto playerPosition{get_singleton<player>().get_position()};
    auto worldArea{get_singleton<world>().get_current_world_area()};
    auto playerElevation{worldArea->get_tile(playerPosition)->get_elevation()};
    auto extraRows{8};
    for (auto i = 0; i < 3; i++) {
      for (auto y = -extraRows; y < gridSize.height + extraRows; y++) {
        for (auto x = 0; x < gridSize.width; x++) {
          auto xCoordinate{playerPosition.x - (gridSize.width - 1) / 2 + x};
          auto yCoordinate{playerPosition.y - (gridSize.height - 1) / 2 + y};
          if (!worldArea->is_valid_coordinate(xCoordinate, yCoordinate)) {
            continue;
          }
          auto tile{worldArea->get_tile(xCoordinate, yCoordinate)};
          float xCanvas;
          float yCanvas;
          float widthCanvas;
          float heightCanvas;
          auto coordNW{point{xCoordinate, yCoordinate}};
          auto coordNE{point{xCoordinate + 1, yCoordinate}};
          auto coordSW{point{xCoordinate, yCoordinate + 1}};
          auto coordSE{point{xCoordinate + 1, yCoordinate + 1}};
          if (!worldArea->is_valid_coordinate(coordNW.x, coordNW.y) ||
              !worldArea->is_valid_coordinate(coordNE.x, coordNE.y) ||
              !worldArea->is_valid_coordinate(coordSW.x, coordSW.y) ||
              !worldArea->is_valid_coordinate(coordSE.x, coordSE.y)) {
            continue;
          }
          auto tileNW{worldArea->get_tile(coordNW)};
          auto tileNE{worldArea->get_tile(coordNE)};
          auto tileSW{worldArea->get_tile(coordSW)};
          auto tileSE{worldArea->get_tile(coordSE)};
          auto ground{tile ? tile->get_ground() : 0};
          auto groundTypeRendered{ground};
          xCanvas = x * tileSize.width;
          yCanvas = y * tileSize.height -
                    tileNW->get_elevation() * tileSize.height / 2;
          yCanvas += playerElevation * tileSize.height / 2;
          widthCanvas = tileSize.width;
          heightCanvas = ceil(tileSize.height, 2.5f);
          // if (ground != Hash("GroundWater"))
          if (true) {
            str groundName;
            if (ground == hash("GroundGrass")) {
              groundName = "GroundGrass";
            } else if (ground == hash("GroundWater")) {
              groundName = "GroundDirt";
            } else if (ground == hash("GroundDirt")) {
              groundName = "GroundDirt";
            } else if (ground == hash("GroundRock")) {
              groundName = "GroundRock";
            }
            str fullGroundName{groundName};
            if (tileNW->get_elevation() > tileSW->get_elevation() &&
                tileNE->get_elevation() > tileSE->get_elevation()) {
              heightCanvas += tileSize.height / 2;
              fullGroundName = groundName + "SlopeSouth";
            } else if (tileNW->get_elevation() < tileSW->get_elevation() &&
                       tileNE->get_elevation() < tileSE->get_elevation()) {
              heightCanvas -= tileSize.height / 2;
              fullGroundName = groundName + "SlopeNorth";
            } else if (tileNE->get_elevation() > tileNW->get_elevation() &&
                       tileSE->get_elevation() > tileSW->get_elevation()) {
              yCanvas -= tileSize.height / 2;
              heightCanvas += tileSize.height / 2;
              fullGroundName = groundName + "SlopeWest";
            } else if (tileNW->get_elevation() > tileNE->get_elevation() &&
                       tileSW->get_elevation() > tileSE->get_elevation()) {
              heightCanvas += tileSize.height / 2;
              fullGroundName = groundName + "SlopeEast";
            } else if (tileNW->get_elevation() > tileNE->get_elevation() &&
                       tileNW->get_elevation() > tileSE->get_elevation() &&
                       tileNW->get_elevation() > tileSW->get_elevation()) {
              heightCanvas += tileSize.height / 2;
              fullGroundName = groundName + "SlopeSouthEast";
            } else if (tileNE->get_elevation() > tileNW->get_elevation() &&
                       tileNE->get_elevation() > tileSE->get_elevation() &&
                       tileNE->get_elevation() > tileSW->get_elevation()) {
              yCanvas -= tileSize.height / 2;
              heightCanvas += tileSize.height / 2;
              fullGroundName = groundName + "SlopeSouthWest";
            } else if (tileSW->get_elevation() > tileNW->get_elevation() &&
                       tileSW->get_elevation() > tileSE->get_elevation() &&
                       tileSW->get_elevation() > tileNE->get_elevation()) {
              fullGroundName = groundName + "SlopeNorthEast";
            } else if (tileSE->get_elevation() > tileNW->get_elevation() &&
                       tileSE->get_elevation() > tileNE->get_elevation() &&
                       tileSE->get_elevation() > tileSW->get_elevation()) {
              fullGroundName = groundName + "SlopeNorthWest";
            } else if (tileSW->get_elevation() < tileNW->get_elevation() &&
                       tileSW->get_elevation() < tileNE->get_elevation() &&
                       tileSW->get_elevation() < tileSE->get_elevation()) {
              heightCanvas += tileSize.height / 2;
              fullGroundName = groundName + "SlopeSouthWestInverted";
            } else if (tileSE->get_elevation() < tileNW->get_elevation() &&
                       tileSE->get_elevation() < tileNE->get_elevation() &&
                       tileSE->get_elevation() < tileSW->get_elevation()) {
              heightCanvas += tileSize.height / 2;
              fullGroundName = groundName + "SlopeSouthEastInverted";
            } else if (tileNW->get_elevation() < tileNE->get_elevation() &&
                       tileNW->get_elevation() < tileSW->get_elevation() &&
                       tileNW->get_elevation() < tileSE->get_elevation()) {
              yCanvas -= tileSize.height / 2;
              fullGroundName = groundName + "SlopeNorthWestInverted";
            } else if (tileNE->get_elevation() < tileNW->get_elevation() &&
                       tileNE->get_elevation() < tileSW->get_elevation() &&
                       tileNE->get_elevation() < tileSE->get_elevation()) {
              fullGroundName = groundName + "SlopeNorthEastInverted";
            } else if (tileSW->get_elevation() == tileNE->get_elevation() &&
                       tileNW->get_elevation() < tileSW->get_elevation() &&
                       tileSE->get_elevation() < tileSW->get_elevation()) {
              yCanvas -= tileSize.height / 2;
              heightCanvas += tileSize.height / 2;
              fullGroundName = groundName + "SlopeDiagonalSouthWestToNorthEast";
            } else if (tileNW->get_elevation() == tileSE->get_elevation() &&
                       tileNE->get_elevation() < tileNW->get_elevation() &&
                       tileSW->get_elevation() < tileNW->get_elevation()) {
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
            groundTypeRendered = hash(fullGroundName);
          }
          // else if (ground == Hash("GroundWater"))
          // {
          //     auto animIndex{(GetTicks() + ((xCoordinate + yCoordinate) *
          //     100)) / 500 % 3};
          //     groundTypeRendered = Hash("GroundWater_" +
          //     std::to_string(animIndex) + "_New");
          // }
          if (i == 0) {
            get_singleton<image_renderer>().draw_image(
                groundTypeRendered, xCanvas, yCanvas, widthCanvas,
                heightCanvas);
          } else if (ground != hash("GroundWater") && i == 1) {
            vec<directions> riverDirections{tile->get_river_direction_1(),
                                            tile->get_river_direction_2()};
            auto riverPartWidth{0.4f * widthCanvas};
            auto riverPartHeight{0.4f * heightCanvas};
            auto partLenght{2.5f};
            auto animIndex{(get_ticks() + ((xCoordinate + yCoordinate) * 100)) /
                           500 % 3};
            for (auto j = 0; j < 2; j++) {
              switch (riverDirections.at(j)) {
              case directions::North: {
                for (auto k = 0.0f; k < partLenght; k += 0.5f) {
                  rect_f bounds{xCanvas + widthCanvas / 2 - riverPartWidth / 2,
                                yCanvas + heightCanvas / 2 -
                                    riverPartHeight / 2 - k * riverPartHeight,
                                riverPartWidth, riverPartHeight};
                  get_singleton<image_renderer>().draw_image(
                      "RiverPart_" + std::to_string(animIndex), bounds.x,
                      bounds.y, bounds.width, bounds.height);
                }
              } break;
              case directions::East: {
                for (auto k = 0.0f; k < partLenght; k += 0.5f) {
                  rect_f bounds{xCanvas + widthCanvas / 2 - riverPartWidth / 2 +
                                    k * riverPartWidth,
                                yCanvas + heightCanvas / 2 -
                                    riverPartHeight / 2,
                                riverPartWidth, riverPartHeight};
                  get_singleton<image_renderer>().draw_image(
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
                  get_singleton<image_renderer>().draw_image(
                      "RiverPart_" + std::to_string(animIndex), bounds.x,
                      bounds.y, bounds.width, bounds.height);
                }
              } break;
              case directions::West: {
                for (auto k = 0.0f; k < partLenght; k += 0.5f) {
                  rect_f bounds{xCanvas + widthCanvas / 2 - riverPartWidth / 2 -
                                    k * riverPartWidth,
                                yCanvas + heightCanvas / 2 -
                                    riverPartHeight / 2,
                                riverPartWidth, riverPartHeight};
                  get_singleton<image_renderer>().draw_image(
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
                  get_singleton<image_renderer>().draw_image(
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
                  get_singleton<image_renderer>().draw_image(
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
                  get_singleton<image_renderer>().draw_image(
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
                  get_singleton<image_renderer>().draw_image(
                      "RiverPart_" + std::to_string(animIndex), bounds.x,
                      bounds.y, bounds.width, bounds.height);
                }
              } break;
              }
            }
          } else if (ground == hash("GroundWater") && i == 1) {
            auto animIndex{(get_ticks() + ((xCoordinate + yCoordinate) * 100)) /
                           500 % 3};
            get_singleton<image_renderer>().draw_image(
                "GroundWaterEdge", xCanvas - widthCanvas * 0.2f,
                yCanvas - heightCanvas * 0.2f, widthCanvas * 1.4f,
                heightCanvas * 1.4f);
          } else if (ground == hash("GroundWater") && i == 2) {

            auto animIndex{(get_ticks() + ((xCoordinate + yCoordinate) * 100)) /
                           500 % 3};
            get_singleton<image_renderer>().draw_image(
                "GroundWater_" + std::to_string(animIndex), xCanvas, yCanvas,
                widthCanvas, heightCanvas);

            for (auto i = 0; i < tile->get_elevation(); i++) {
              get_singleton<image_renderer>().draw_image(
                  "GroundWaterHeight", xCanvas, yCanvas, widthCanvas,
                  heightCanvas);
            }

            // groundTypeRendered = Hash("GroundWater_" +
            // std::to_string(animIndex) + "_New");
            // _<ImageRenderer>().DrawImage(groundTypeRendered, xCanvas -
            // tileSize.width * 3 / 2, yCanvas - tileSize.height * 3 / 2,
            // tileSize.width * 4, tileSize.height * 4);
            if (ground == hash("GroundWater")) {
              for (auto i = 0; i < tile->get_water_depth(); i++) {
                get_singleton<image_renderer>().draw_image(
                    "GroundWaterDepth", xCanvas, yCanvas, widthCanvas,
                    heightCanvas);
              }
            }
          }
          if (ground == hash("GroundGrass")) {
            get_singleton<image_renderer>().draw_image(
                "GroundGrassLayer", xCanvas, yCanvas, widthCanvas,
                heightCanvas);
          } else if (ground == hash("GroundDirt")) {
            get_singleton<image_renderer>().draw_image(
                "GroundDirtLayer", xCanvas, yCanvas, widthCanvas, heightCanvas);
          } else if (ground == hash("GroundRock")) {
            get_singleton<image_renderer>().draw_image(
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
              get_singleton<tile_hovering>().get_hovered_coordinate()};
          if (xCoordinate == hoveredCoordinate.x &&
              yCoordinate == hoveredCoordinate.y) {
            get_singleton<image_renderer>().draw_image(
                "HoveredTile", xCanvas, yCanvas, widthCanvas, heightCanvas);
          }
          auto playerDestination{get_singleton<player>().get_destination()};
          if (xCoordinate == playerDestination.x &&
              yCoordinate == playerDestination.y) {
            get_singleton<image_renderer>().draw_image(
                "DestinationTile", xCanvas, yCanvas, widthCanvas, heightCanvas);
          }
          if (xCoordinate == playerPosition.x &&
              yCoordinate == playerPosition.y) {
            get_singleton<image_renderer>().draw_image(
                "Shadow", xCanvas, yCanvas, widthCanvas, heightCanvas);
            get_singleton<image_renderer>().draw_image(
                "Player", xCanvas, yCanvas, tileSize.width, tileSize.height);
          }
          auto objectsStack{tile ? tile->get_objects_stack() : nullptr};
          if (objectsStack) {
            for (const auto &object : objectsStack->get_objects()) {
              if (object->get_type() != hash("ObjectPinkFlower")) {
                get_singleton<image_renderer>().draw_image(
                    "Shadow", xCanvas, yCanvas, tileSize.width,
                    tileSize.height);
              }
              auto objectType{object->get_type()};
              if (objectType == hash("ObjectFirTree") ||
                  objectType == hash("ObjectBirchTree")) {
                auto treeObject{std::static_pointer_cast<tree_object>(object)};
                auto trunkParts{treeObject->get_trunk_parts()};
                auto needleTypes{treeObject->get_needle_types()};
                auto widthFactor{treeObject->get_width_factor()};
                for (auto i = 0; i < trunkParts.size(); i++) {
                  auto trunkPart{trunkParts.at(i)};
                  auto needleType{needleTypes.at(i)};
                  auto widthDecreaseFactor{0.5f +
                                           (trunkParts.size() - i) /
                                               c_float(trunkParts.size()) / 2};
                  auto treeWidth{tileSize.width * widthFactor *
                                 widthDecreaseFactor};
                  auto trunkPartX{trunkPart.x};
                  trunkPartX *= c_float(i) / trunkParts.size() *
                                std::sin(get_ticks() / 700.0f +
                                         xCoordinate * yCoordinate);
                  auto trunkPartXCenter{xCanvas + tileSize.width / 2 +
                                        trunkPartX * treeWidth};
                  auto trunkPartYCenter{yCanvas + tileSize.height -
                                        trunkPart.y * tileSize.height};
                  auto trunkPartWidth{tileSize.width * 0.2f *
                                      widthDecreaseFactor};
                  auto trunkPartHeight{tileSize.height * 0.2f};
                  str trunkPartName;
                  if (objectType == hash("ObjectFirTree")) {
                    trunkPartName = "ObjectFirTreeTrunkPart";
                  } else if (objectType == hash("ObjectBirchTree")) {
                    trunkPartName = "ObjectBirchTreeTrunkPart";
                  }
                  get_singleton<image_renderer>().draw_image(
                      trunkPartName, trunkPartXCenter - trunkPartWidth / 2,
                      trunkPartYCenter - trunkPartHeight / 2, trunkPartWidth,
                      trunkPartHeight);
                  auto needleWidth{treeWidth};
                  auto needleHeight{tileSize.height};
                  if (needleType) {
                    get_singleton<image_renderer>().draw_image(
                        needleType, trunkPartXCenter - needleWidth / 2,
                        trunkPartYCenter - needleHeight / 2, needleWidth,
                        needleHeight);
                  }
                }
                continue;
              }
              auto objectImageSize{
                  get_singleton<image_bank>().get_image_size(objectType)};
              auto objectWidth{objectImageSize.width / 60.0f * tileSize.width};
              auto objectHeight{objectImageSize.height / 60.0f *
                                tileSize.height};
              get_singleton<image_renderer>().draw_image(
                  objectType, xCanvas + tileSize.width / 2 - objectWidth / 2,
                  yCanvas + tileSize.height - objectHeight, objectWidth,
                  objectHeight);
            }
          }
          auto creature{tile ? tile->get_creature() : nullptr};
          if (creature) {
            auto creatureType{creature->get_type()};
            auto creatureImageSize{
                get_singleton<image_bank>().get_image_size(creatureType)};
            auto creatureWidth{creatureImageSize.width / 60.0f *
                               tileSize.width};
            auto creatureHeight{creatureImageSize.height / 60.0f *
                                tileSize.height};
            get_singleton<image_renderer>().draw_image(
                creatureType, xCanvas + tileSize.width / 2 - creatureWidth / 2,
                yCanvas + tileSize.height - creatureHeight, creatureWidth,
                creatureHeight);
          }
        }
      }
    }
  }
}