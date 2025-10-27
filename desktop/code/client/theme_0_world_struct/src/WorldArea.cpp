//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "WorldArea.hpp"

#include "Tile.hpp"

namespace Forradia::Theme0
{
    void WorldArea::Initialize(Size w_area_sz,
                               float world_scaling)
    {
        auto size{w_area_sz};

        size.width *= world_scaling;

        size.height *= world_scaling;

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