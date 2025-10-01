/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "tile_hovering.hpp"
#include "theme_0/theme_0_mechanics/core_game_objects/player.hpp"
#include "theme_0/theme_0_mechanics/math/tile_grid_math.hpp"
#include "theme_0/theme_0_mechanics/world_structure/tile.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world_area.hpp"

namespace forr {
  void tile_hovering::update() {
    auto playerPosition{GetSingleton<player>().get_position()};
    auto mousePosition{GetNormalizedMousePosition()};
    auto tileSize{CalculateTileSize()};
    auto screenRelativeX{CInt(mousePosition.x / tileSize.width)};
    auto gridSize{CalculateGridSize()};
    auto hoveredXCoordinate{playerPosition.x - (gridSize.width - 1) / 2 +
                            screenRelativeX};
    auto screenRelativeXPx{
        (hoveredXCoordinate - (playerPosition.x - (gridSize.width - 1) / 2)) *
        tileSize.width};
    auto worldArea{GetSingleton<world>().get_current_world_area()};
    auto extraRows{8};
    auto topYCoordinate{CInt(playerPosition.y - (gridSize.height - 1) / 2) -
                        extraRows};
    auto playerTile{worldArea->get_tile(playerPosition)};
    auto playerElevation{
        playerTile ? worldArea->get_tile(playerPosition)->get_elevation() : 0};
    auto screenRelativeYPx{-extraRows * tileSize.height};
    for (auto y = -extraRows; y < gridSize.height + extraRows; y++) {
      auto yCoordinate{CInt(playerPosition.y - (gridSize.height - 1) / 2 + y)};
      auto coordinate{point{hoveredXCoordinate, yCoordinate}};
      auto tile{worldArea->get_tile(coordinate)};
      if (!tile) {
        screenRelativeYPx = 0.5f +
                            (y - (gridSize.height - 1) / 2) * tileSize.height +
                            playerElevation * tileSize.height / 2;
        continue;
      }
      auto elevation{tile->get_elevation()};
      screenRelativeYPx = 0.5f +
                          (y - (gridSize.height - 1) / 2) * tileSize.height +
                          (playerElevation - elevation) * tileSize.height / 2;
      auto coordNW{point{coordinate.x, coordinate.y}};
      auto coordNE{point{coordinate.x + 1, coordinate.y}};
      auto coordSW{point{coordinate.x, coordinate.y + 1}};
      auto coordSE{point{coordinate.x + 1, coordinate.y + 1}};
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
      if (!tileNW || !tileNE || !tileSE || !tileSW) {
        continue;
      }
      float localTileHeight;
      if (tileNW->get_elevation() > tileSW->get_elevation() &&
          tileNE->get_elevation() > tileSE->get_elevation()) {
        localTileHeight = tileSize.height * 1.5f;
      } else if (tileNW->get_elevation() < tileSW->get_elevation() &&
                 tileNE->get_elevation() < tileSE->get_elevation()) {
        localTileHeight = tileSize.height * 0.5f;
      } else if (tileNE->get_elevation() > tileNW->get_elevation() &&
                 tileSE->get_elevation() > tileSW->get_elevation()) {
        localTileHeight = tileSize.height * 1.5f;
      } else if (tileNW->get_elevation() > tileNE->get_elevation() &&
                 tileSW->get_elevation() > tileSE->get_elevation()) {
        localTileHeight = tileSize.height * 1.5f;
      } else if (tileNW->get_elevation() > tileNE->get_elevation() &&
                 tileNW->get_elevation() > tileSE->get_elevation() &&
                 tileNW->get_elevation() > tileSW->get_elevation()) {
        localTileHeight = tileSize.height * 1.5f;
      } else if (tileNE->get_elevation() > tileNW->get_elevation() &&
                 tileNE->get_elevation() > tileSE->get_elevation() &&
                 tileNE->get_elevation() > tileSW->get_elevation()) {
        localTileHeight = tileSize.height * 1.5f;
      } else if (tileSW->get_elevation() > tileNW->get_elevation() &&
                 tileSW->get_elevation() > tileSE->get_elevation() &&
                 tileSW->get_elevation() > tileNE->get_elevation()) {
        localTileHeight = tileSize.height * 1.0f;
      } else if (tileSE->get_elevation() > tileNW->get_elevation() &&
                 tileSE->get_elevation() > tileNE->get_elevation() &&
                 tileSE->get_elevation() > tileSW->get_elevation()) {
        localTileHeight = tileSize.height * 1.0f;
      } else if (tileSW->get_elevation() < tileNW->get_elevation() &&
                 tileSW->get_elevation() < tileNE->get_elevation() &&
                 tileSW->get_elevation() < tileSE->get_elevation()) {
        localTileHeight = tileSize.height * 1.5f;
      } else if (tileSE->get_elevation() < tileNW->get_elevation() &&
                 tileSE->get_elevation() < tileNE->get_elevation() &&
                 tileSE->get_elevation() < tileSW->get_elevation()) {
        localTileHeight = tileSize.height * 1.5f;
      } else if (tileNW->get_elevation() < tileNE->get_elevation() &&
                 tileNW->get_elevation() < tileSW->get_elevation() &&
                 tileNW->get_elevation() < tileSE->get_elevation()) {
        localTileHeight = tileSize.height * 1.0f;
      } else if (tileNE->get_elevation() < tileNW->get_elevation() &&
                 tileNE->get_elevation() < tileSW->get_elevation() &&
                 tileNE->get_elevation() < tileSE->get_elevation()) {
        localTileHeight = tileSize.height * 1.0f;
      } else if (tileSW->get_elevation() == tileNE->get_elevation() &&
                 tileNW->get_elevation() < tileSW->get_elevation() &&
                 tileSE->get_elevation() < tileSW->get_elevation()) {
        localTileHeight = tileSize.height * 1.5f;
      } else if (tileNW->get_elevation() == tileSE->get_elevation() &&
                 tileNE->get_elevation() < tileNW->get_elevation() &&
                 tileSW->get_elevation() < tileNW->get_elevation()) {
        localTileHeight = tileSize.height * 1.5f;
      } else {
        localTileHeight = tileSize.height;
      }
      auto rect{rect_f{screenRelativeXPx,
                       screenRelativeYPx - localTileHeight / 2, tileSize.width,
                       localTileHeight}};
      if (rect.contains(mousePosition)) {
        m_hoveredCoordinate = {hoveredXCoordinate, yCoordinate};
        return;
      }
    }
  }
}