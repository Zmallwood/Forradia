/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

namespace Forradia {
  class Tile;
  class Creature;

  class WorldArea {
  public:
    WorldArea() { Initialize(); }

    Size GetSize() const;

    bool IsValidCoordinate(int x, int y) const;

    SharedPtr<Tile> GetTile(int x, int y) const;

    SharedPtr<Tile> GetTile(Point coordinate) const;

    auto &GetCreaturesMirrorRef() { return m_creaturesMirror; }

  private:
    void Initialize();

    Vector<Vector<SharedPtr<Tile>>> m_tiles;
    Map<SharedPtr<Creature>, Point> m_creaturesMirror;
  };
}