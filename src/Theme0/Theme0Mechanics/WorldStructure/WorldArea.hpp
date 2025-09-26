/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

namespace Forradia
{
    class Tile;
    class Mob;

    class WorldArea
    {
    public:
        WorldArea();

        Size GetSize() const;

        bool IsValidCoordinate(int x,
                               int y) const;

        std::shared_ptr<Tile> GetTile(int x,
                                      int y) const;

        std::shared_ptr<Tile> GetTile(Point coordinate) const;

        auto &GetMobsMirrorRef()
        {
            return m_mobsMirror;
        }

    private:
        std::vector<std::vector<std::shared_ptr<Tile>>> m_tiles;
        std::map<std::shared_ptr<Mob>, Point> m_mobsMirror;
    };
}