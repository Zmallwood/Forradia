//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "WorldArea.hpp"

#include "Tile.hpp"

namespace Forradia::Theme0
{
    void WorldArea::Initialize(Size worldAreaSize,
                               float worldScaling)
    {
        auto size{worldAreaSize};

        size.width *= worldScaling;

        size.height *= worldScaling;

        for (auto x = 0; x < size.width; x++)
        {
            m_tiles.push_back(
                Vector<std::shared_ptr<Tile>>());

            for (auto y = 0; y < size.height; y++)
            {
                m_tiles[x].push_back(
                    std::make_shared<Tile>());
            }
        }
    }

    void WorldArea::Reset()
    {
        m_creaturesMirror.clear();
        m_robotsMirror.clear();

        auto size{this->GetSize()};

        for (auto y = 0; y < size.height; y++)
        {
            for (auto x = 0; x < size.width; x++)
            {
                auto tile{m_tiles[x][y]};

                tile->SetCreature(nullptr);
                tile->SetRobot(nullptr);
                tile->SetGround(Hash("GroundGrass"));
                tile->SetElevation(0.0f);
                tile->SetWaterDepth(0);
            }
        }
    }

    Size WorldArea::GetSize() const
    {
        auto width{CInt(m_tiles.size())};

        auto height{0};

        if (width)
        {
            height = m_tiles.at(0).size();
        }

        return {width, height};
    }

    bool WorldArea::IsValidCoordinate(int x, int y) const
    {
        auto size{GetSize()};

        return x >= 0 && y >= 0 && x < size.width &&
               y < size.height;
    }

    bool WorldArea::IsValidCoordinate(Point coord) const
    {
        return this->IsValidCoordinate(coord.x, coord.y);
    }

    SharedPtr<Tile> WorldArea::GetTile(int x, int y) const
    {
        if (this->IsValidCoordinate(x, y))
        {
            return m_tiles.at(x).at(y);
        }

        return nullptr;
    }

    SharedPtr<Tile> WorldArea::GetTile(Point coord) const
    {
        return this->GetTile(coord.x, coord.y);
    }
}