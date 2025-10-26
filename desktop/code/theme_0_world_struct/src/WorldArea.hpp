//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace Forradia
{
    namespace Theme0
    {
        class Tile;

        class Creature;

        class NPC;

        class WorldArea
        {
          public:
            WorldArea(Size w_area_sz, float world_scaling)
            {
                Initialize(w_area_sz, world_scaling);
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

            auto &GetNPCsMirrorRef()
            {
                return m_npcsMirror;
            }

          private:
            void Initialize(Size w_area_sz,
                            float world_scaling);

            Vector<Vector<SharedPtr<Tile>>> m_tiles;

            std::map<SharedPtr<Creature>, Point>
                m_creaturesMirror;

            std::map<SharedPtr<NPC>, Point> m_npcsMirror;
        };
    }
}