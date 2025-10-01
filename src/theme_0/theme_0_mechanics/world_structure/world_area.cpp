/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "world_area.hpp"
#include "tile.hpp"
#include "theme_0/theme_0_mechanics/configuration/game_properties.hpp"

namespace forr {
  void WorldArea::Initialize() {
    auto size{GameProperties::k_worldAreaSize};
    size.width *= GetSingleton<GameProperties>().k_worldScalingFactor;
    size.height *= GetSingleton<GameProperties>().k_worldScalingFactor;
    for (auto x = 0; x < size.width; x++) {
      m_tiles.push_back(Vector<std::shared_ptr<Tile>>());
      for (auto y = 0; y < size.height; y++) {
        m_tiles[x].push_back(std::make_shared<Tile>());
      }
    }
  }

  Size WorldArea::GetSize() const {
    auto width{CInt(m_tiles.size())};
    auto height{0};
    if (width) {
      height = m_tiles.at(0).size();
    }
    return {width, height};
  }

  bool WorldArea::IsValidCoordinate(int x, int y) const {
    auto size{GetSize()};
    return x >= 0 && y >= 0 && x < size.width && y < size.height;
  }

  SharedPtr<Tile> WorldArea::GetTile(int x, int y) const {
    if (IsValidCoordinate(x, y)) {
      return m_tiles.at(x).at(y);
    }
    return nullptr;
  }

  SharedPtr<Tile> WorldArea::GetTile(Point coordinate) const {
    return GetTile(coordinate.x, coordinate.y);
  }
}