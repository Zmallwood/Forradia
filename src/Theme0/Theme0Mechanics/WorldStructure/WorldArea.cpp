#include "WorldArea.hpp"
#include "Tile.hpp"
#include "Theme0/Theme0Mechanics/Configuration/GameProperties.hpp"

namespace Forradia
{
    WorldArea::WorldArea()
    {
        auto size{GameProperties::k_worldAreaSize};

        for (auto x = 0; x < size.width; x++)
        {
            m_tiles.push_back(std::vector<std::shared_ptr<Tile>>());

            for (auto y = 0; y < size.height; y++)
            {
                m_tiles[x].push_back(std::make_shared<Tile>());
            }
        }
    }

    Size WorldArea::GetSize() const
    {
        auto width{
            static_cast<int>(m_tiles.size())};

        auto height{0};

        if (width)
        {
            height = m_tiles.at(0).size();
        }

        return {width, height};
    }

    bool WorldArea::IsValidCoordinate(int x,
                                      int y) const
    {
        auto size{GetSize()};

        return x >= 0 &&
               y >= 0 &&
               x < size.width &&
               y < size.height;
    }

    std::shared_ptr<Tile>
    WorldArea::GetTile(int x,
                       int y) const
    {
        if (IsValidCoordinate(x, y))
        {
            return m_tiles.at(x).at(y);
        }

        return nullptr;
    }

    std::shared_ptr<Tile> WorldArea::GetTile(Point coordinate) const
    {
        return GetTile(coordinate.x, coordinate.y);
    }
}