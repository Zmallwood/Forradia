/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "WorldArea.hpp"
#include "ObjectsStack.hpp"
#include "Tile.hpp"

namespace Forradia::Theme0 {
    auto WorldArea::Initialize(Size worldAreaSize, float worldScaling) -> void {
        auto size{worldAreaSize};
        size.width *= worldScaling;
        size.height *= worldScaling;

        for (auto x = 0; x < size.width; x++) {
            m_tiles.push_back(std::vector<std::shared_ptr<Tile>>());
            for (auto y = 0; y < size.height; y++)
                m_tiles[x].push_back(std::make_shared<Tile>());
        }
    }

    auto WorldArea::Reset() -> void {
        m_entitiesMirror.clear();

        auto size{this->GetSize()};

        for (auto y = 0; y < size.height; y++) {
            for (auto x = 0; x < size.width; x++) {
                auto tile{m_tiles[x][y]};

                // Set the tile to its default state.
                tile->SetGround(Hash("GroundGrass"));
                tile->SetEntity(nullptr);
                // tile->SetRobot(nullptr);
                tile->SetElevation(0.0F);
                tile->SetWaterDepth(0);
                tile->GetObjectsStack()->ClearObjects();
            }
        }
    }

    auto WorldArea::GetSize() const -> Size {
        auto width{static_cast<int>(m_tiles.size())};
        auto height{0};
        if (width)
            height = m_tiles.at(0).size();
        return {width, height};
    }

    auto WorldArea::IsValidCoordinate(int x, int y) const -> bool {
        auto size{this->GetSize()};
        return x >= 0 && y >= 0 && x < size.width && y < size.height;
    }

    auto WorldArea::IsValidCoordinate(Point coordinate) const -> bool {
        return this->IsValidCoordinate(coordinate.x, coordinate.y);
    }

    auto WorldArea::GetTile(int x, int y) const -> std::shared_ptr<Tile> {
        if (this->IsValidCoordinate(x, y))
            return m_tiles.at(x).at(y);
        return nullptr;
    }

    auto WorldArea::GetTile(Point coord) const -> std::shared_ptr<Tile> {
        return this->GetTile(coord.x, coord.y);
    }
}
