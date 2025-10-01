/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "world_area.hpp"
#include "theme_0/theme_0_mechanics/configuration/game_properties.hpp"
#include "tile.hpp"

namespace forr {
  void world_area::Initialize() {
    auto size{game_properties::k_worldAreaSize};
    size.width *= GetSingleton <game_properties>().k_worldScalingFactor;
    size.height *= GetSingleton<game_properties>().k_worldScalingFactor;
    for (auto x = 0; x < size.width; x++) {
      m_tiles.push_back(vec<std::shared_ptr<tile>>());
      for (auto y = 0; y < size.height; y++) {
        m_tiles[x].push_back(std::make_shared<tile>());
      }
    }
  }

  size world_area::GetSize() const {
    auto width{CInt(m_tiles.size())};
    auto height{0};
    if (width) {
      height = m_tiles.at(0).size();
    }
    return {width, height};
  }

  bool world_area::IsValidCoordinate(int x, int y) const {
    auto size{GetSize()};
    return x >= 0 && y >= 0 && x < size.width && y < size.height;
  }

  s_ptr<tile> world_area::GetTile(int x, int y) const {
    if (IsValidCoordinate(x, y)) {
      return m_tiles.at(x).at(y);
    }
    return nullptr;
  }

  s_ptr<tile> world_area::GetTile(point coordinate) const {
    return GetTile(coordinate.x, coordinate.y);
  }
}