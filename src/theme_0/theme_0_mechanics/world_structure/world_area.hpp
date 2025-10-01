/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class tile;
  class creature;

  class world_area {
  public:
    world_area() { Initialize(); }

    size GetSize() const;

    bool IsValidCoordinate(int x, int y) const;

    s_ptr<tile> GetTile(int x, int y) const;

    s_ptr<tile> GetTile(point coordinate) const;

    auto &GetCreaturesMirrorRef() { return m_creaturesMirror; }

  private:
    void Initialize();

    vec<vec<s_ptr<tile>>> m_tiles;
    std::map<s_ptr<creature>, point> m_creaturesMirror;
  };
}