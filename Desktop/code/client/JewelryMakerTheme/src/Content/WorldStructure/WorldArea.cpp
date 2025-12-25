/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "WorldArea.hpp"
    #include "ObjectsStack.hpp"
    #include "Tile.hpp"
// clang-format on

namespace ForradiaEngine::JewelryMakerTheme
{
    auto WorldArea::initialize(Size worldAreaSize, float worldScaling) -> void
    {
        auto size{worldAreaSize};
        size.width *= worldScaling;
        size.height *= worldScaling;

        for (auto x = 0; x < size.width; x++)
        {
            m_tiles.push_back(std::vector<std::shared_ptr<Tile>>());

            for (auto y = 0; y < size.height; y++)
            {
                m_tiles[x].push_back(std::make_shared<Tile>());
            }
        }
    }

    auto WorldArea::reset() -> void
    {
        m_entitiesMirror.clear();

        auto size{this->getSize()};

        for (auto y = 0; y < size.height; y++)
        {
            for (auto x = 0; x < size.width; x++)
            {
                auto tile{m_tiles[x][y]};

                // Set the tile to its default state.
                tile->setGround(hash("GroundGrass"));
                tile->setEntity(nullptr);
                tile->setElevation(0.0F);
                tile->setWaterDepth(0);
                tile->getObjectsStack()->clearObjects();
            }
        }
    }

    auto WorldArea::getSize() const -> Size
    {
        auto width{static_cast<int>(m_tiles.size())};
        auto height{0};

        if (width)
        {
            height = m_tiles.at(0).size();
        }

        return {width, height};
    }

    auto WorldArea::isValidCoordinate(int x, int y) const -> bool
    {
        auto size{this->getSize()};

        return x >= 0 && y >= 0 && x < size.width && y < size.height;
    }

    auto WorldArea::isValidCoordinate(Point coordinate) const -> bool
    {
        return this->isValidCoordinate(coordinate.x, coordinate.y);
    }

    auto WorldArea::getTile(int x, int y) const -> std::shared_ptr<Tile>
    {
        if (this->isValidCoordinate(x, y))
        {
            return m_tiles.at(x).at(y);
        }

        return nullptr;
    }

    auto WorldArea::getTile(Point coord) const -> std::shared_ptr<Tile>
    {
        return this->getTile(coord.x, coord.y);
    }
}
