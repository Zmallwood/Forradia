/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class Tile;
  class Creature;

  class WorldArea {
  public:
    WorldArea() { Initialize(); }

    Size GetSize() const;

    bool IsValidCoordinate(int x, int y) const;

    s_ptr<Tile> GetTile(int x, int y) const;

    s_ptr<Tile> GetTile(Point coordinate) const;

    auto &GetCreaturesMirrorRef() { return m_creaturesMirror; }

  private:
    void Initialize();

    vec<vec<s_ptr<Tile>>> m_tiles;
    std::map<s_ptr<Creature>, Point> m_creaturesMirror;
  };
}