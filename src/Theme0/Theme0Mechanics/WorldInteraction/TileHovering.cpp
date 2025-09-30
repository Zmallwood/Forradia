/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "TileHovering.hpp"
#include "Theme0/Theme0Mechanics/CoreGameObjects/Player.hpp"
#include "Theme0/Theme0Mechanics/Math/TileGridMath.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/Tile.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/World.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/WorldArea.hpp"

namespace Forradia {
  void TileHovering::Update() {
    auto playerPosition{_<Player>().GetPosition()};

    auto mousePosition{GetNormalizedMousePosition()};

    auto tileSize{CalculateTileSize()};

    auto screenRelativeX{CInt(mousePosition.x / tileSize.width)};

    auto gridSize{CalculateGridSize()};

    auto hoveredXCoordinate{playerPosition.x - (gridSize.width - 1) / 2 +
                            screenRelativeX};

    auto screenRelativeXPx{
        (hoveredXCoordinate - (playerPosition.x - (gridSize.width - 1) / 2)) *
        tileSize.width};

    auto worldArea{_<World>().GetCurrentWorldArea()};

    auto extraRows{8};

    auto topYCoordinate{CInt(playerPosition.y - (gridSize.height - 1) / 2) -
                        extraRows};

    auto playerTile{worldArea->GetTile(playerPosition)};

    auto playerElevation{
        playerTile ? worldArea->GetTile(playerPosition)->GetElevation() : 0};

    auto screenRelativeYPx{-extraRows * tileSize.height};

    for (auto y = -extraRows; y < gridSize.height + extraRows; y++) {
      auto yCoordinate{CInt(playerPosition.y - (gridSize.height - 1) / 2 + y)};
      auto coordinate{Point{hoveredXCoordinate, yCoordinate}};

      auto tile{worldArea->GetTile(coordinate)};

      if (!tile) {
        screenRelativeYPx = 0.5f +
                            (y - (gridSize.height - 1) / 2) * tileSize.height +
                            playerElevation * tileSize.height / 2;
        continue;
      }

      auto elevation{tile->GetElevation()};

      screenRelativeYPx = 0.5f +
                          (y - (gridSize.height - 1) / 2) * tileSize.height +
                          (playerElevation - elevation) * tileSize.height / 2;

      auto coordNW{Point{coordinate.x, coordinate.y}};
      auto coordNE{Point{coordinate.x + 1, coordinate.y}};
      auto coordSW{Point{coordinate.x, coordinate.y + 1}};
      auto coordSE{Point{coordinate.x + 1, coordinate.y + 1}};

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

      if (!tileNW || !tileNE || !tileSE || !tileSW) {
        continue;
      }

      float localTileHeight;

      if (tileNW->GetElevation() > tileSW->GetElevation() &&
          tileNE->GetElevation() > tileSE->GetElevation()) {
        localTileHeight = tileSize.height * 1.5f;
      } else if (tileNW->GetElevation() < tileSW->GetElevation() &&
                 tileNE->GetElevation() < tileSE->GetElevation()) {
        localTileHeight = tileSize.height * 0.5f;
      } else if (tileNE->GetElevation() > tileNW->GetElevation() &&
                 tileSE->GetElevation() > tileSW->GetElevation()) {
        localTileHeight = tileSize.height * 1.5f;
      } else if (tileNW->GetElevation() > tileNE->GetElevation() &&
                 tileSW->GetElevation() > tileSE->GetElevation()) {
        localTileHeight = tileSize.height * 1.5f;
      } else if (tileNW->GetElevation() > tileNE->GetElevation() &&
                 tileNW->GetElevation() > tileSE->GetElevation() &&
                 tileNW->GetElevation() > tileSW->GetElevation()) {
        localTileHeight = tileSize.height * 1.5f;
      } else if (tileNE->GetElevation() > tileNW->GetElevation() &&
                 tileNE->GetElevation() > tileSE->GetElevation() &&
                 tileNE->GetElevation() > tileSW->GetElevation()) {
        localTileHeight = tileSize.height * 1.5f;
      } else if (tileSW->GetElevation() > tileNW->GetElevation() &&
                 tileSW->GetElevation() > tileSE->GetElevation() &&
                 tileSW->GetElevation() > tileNE->GetElevation()) {
        localTileHeight = tileSize.height * 1.0f;
      } else if (tileSE->GetElevation() > tileNW->GetElevation() &&
                 tileSE->GetElevation() > tileNE->GetElevation() &&
                 tileSE->GetElevation() > tileSW->GetElevation()) {
        localTileHeight = tileSize.height * 1.0f;
      } else if (tileSW->GetElevation() < tileNW->GetElevation() &&
                 tileSW->GetElevation() < tileNE->GetElevation() &&
                 tileSW->GetElevation() < tileSE->GetElevation()) {
        localTileHeight = tileSize.height * 1.5f;
      } else if (tileSE->GetElevation() < tileNW->GetElevation() &&
                 tileSE->GetElevation() < tileNE->GetElevation() &&
                 tileSE->GetElevation() < tileSW->GetElevation()) {
        localTileHeight = tileSize.height * 1.5f;
      } else if (tileNW->GetElevation() < tileNE->GetElevation() &&
                 tileNW->GetElevation() < tileSW->GetElevation() &&
                 tileNW->GetElevation() < tileSE->GetElevation()) {
        localTileHeight = tileSize.height * 1.0f;
      } else if (tileNE->GetElevation() < tileNW->GetElevation() &&
                 tileNE->GetElevation() < tileSW->GetElevation() &&
                 tileNE->GetElevation() < tileSE->GetElevation()) {
        localTileHeight = tileSize.height * 1.0f;
      } else if (tileSW->GetElevation() == tileNE->GetElevation() &&
                 tileNW->GetElevation() < tileSW->GetElevation() &&
                 tileSE->GetElevation() < tileSW->GetElevation()) {
        localTileHeight = tileSize.height * 1.5f;
      } else if (tileNW->GetElevation() == tileSE->GetElevation() &&
                 tileNE->GetElevation() < tileNW->GetElevation() &&
                 tileSW->GetElevation() < tileNW->GetElevation()) {
        localTileHeight = tileSize.height * 1.5f;
      } else {
        localTileHeight = tileSize.height;
      }

      auto rect{RectF{screenRelativeXPx,
                      screenRelativeYPx - localTileHeight / 2, tileSize.width,
                      localTileHeight}};

      if (rect.Contains(mousePosition)) {
        m_hoveredCoordinate = {hoveredXCoordinate, yCoordinate};
        return;
      }
    }
  }
}