//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace Forradia::Theme0
{
    class Tile;

    class Creature;

    class Robot;

    class WorldArea
    {
      public:
        WorldArea(Size worldAreaSize, float worldScaling)
        {
            this->Initialize(worldAreaSize, worldScaling);
        }

        Size GetSize() const;

        bool IsValidCoordinate(int x, int y) const;

        bool IsValidCoordinate(Point coord) const;

        SharedPtr<Tile> GetTile(int x, int y) const;

        SharedPtr<Tile> GetTile(Point coord) const;

        auto &GetCreaturesMirrorRef()
        {
            return m_creaturesMirror;
        }

        auto &GetRobotsMirrorRef()
        {
            return m_robotsMirror;
        }

      private:
        void Initialize(Size worldAreaSize,
                        float worldScaling);

        Vector<Vector<SharedPtr<Tile>>> m_tiles;

        std::map<SharedPtr<Creature>, Point>
            m_creaturesMirror;

        std::map<SharedPtr<Robot>, Point> m_robotsMirror;
    };
}