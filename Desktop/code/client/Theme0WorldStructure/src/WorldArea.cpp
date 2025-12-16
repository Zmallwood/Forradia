/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "WorldArea.hpp"
#include "ObjectsStack.hpp"
#include "Tile.hpp"

namespace Forradia::Theme0 {
void WorldArea::Initialize(Size worldAreaSize, float worldScaling) {
  auto size{worldAreaSize};
  size.width *= worldScaling;
  size.height *= worldScaling;

  for (auto x = 0; x < size.width; x++) {
    m_tiles.push_back(Vector<std::shared_ptr<Tile>>());
    for (auto y = 0; y < size.height; y++) {
      m_tiles[x].push_back(std::make_shared<Tile>());
    }
  }
}

void WorldArea::Reset() {
  m_creaturesMirror.clear();
  m_robotsMirror.clear();

  auto size{this->GetSize()};

  for (auto y = 0; y < size.height; y++) {
    for (auto x = 0; x < size.width; x++) {
      auto tile{m_tiles[x][y]};

      // Set the tile to its default state.
      tile->SetGround(Hash("GroundGrass"));
      tile->SetCreature(nullptr);
      tile->SetRobot(nullptr);
      tile->SetElevation(0.0f);
      tile->SetWaterDepth(0);
      tile->GetObjectsStack()->ClearObjects();
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
  auto size{this->GetSize()};
  return x >= 0 && y >= 0 && x < size.width && y < size.height;
}

bool WorldArea::IsValidCoordinate(Point coordinate) const {
  return this->IsValidCoordinate(coordinate.x, coordinate.y);
}

SharedPtr<Tile> WorldArea::GetTile(int x, int y) const {
  if (this->IsValidCoordinate(x, y)) {
    return m_tiles.at(x).at(y);
  }
  return nullptr;
}

SharedPtr<Tile> WorldArea::GetTile(Point coord) const {
  return this->GetTile(coord.x, coord.y);
}

void WorldArea::AddClaimedCoordinate(Point coordinate) {
  m_claimedCoordinates.insert(coordinate);
}

bool WorldArea::CoordinateIsClaimed(Point coordinate) const {
  return m_claimedCoordinates.contains(coordinate);
}
}