//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#include "WorldArea.hpp"
#include "ObjectsStack.hpp"
#include "Tile.hpp"

namespace Forradia::Theme0 {
    void WorldArea::Initialize(Size worldAreaSize, float worldScaling) {
        // Obtain the size of the world area.

        auto size{worldAreaSize};

        size.width *= worldScaling;

        size.height *= worldScaling;

        // Create the tiles in the world area.

        for (auto x = 0; x < size.width; x++) {
            // Create a new row of tiles.

            m_tiles.push_back(Vector<std::shared_ptr<Tile>>());

            // Create the tiles in the row.

            for (auto y = 0; y < size.height; y++) {
                // Create a new tile.

                m_tiles[x].push_back(std::make_shared<Tile>());
            }
        }
    }

    void WorldArea::Reset() {
        // Clear the creatures mirror.

        m_creaturesMirror.clear();

        // Clear the robots mirror.

        m_robotsMirror.clear();

        // Obtain the size of the world area.

        auto size{this->GetSize()};

        // Iterate through the tiles in the world area.

        for (auto y = 0; y < size.height; y++) {
            for (auto x = 0; x < size.width; x++) {
                // Obtain the tile.

                auto tile{m_tiles[x][y]};

                // Set the tile to its default state.

                tile->SetGround(Hash("GroundGrass"));

                tile->SetCreature(nullptr);

                tile->SetRobot(nullptr);

                tile->SetElevation(0.0f);

                tile->SetWaterDepth(0);

                tile->GetObjectsStack()->ClearObjects();
            }
        }
    }

    Size WorldArea::GetSize() const {
        // Obtain the width of the world area.

        auto width{CInt(m_tiles.size())};

        // Obtain the height of the world area.

        auto height{0};

        if (width) {
            height = m_tiles.at(0).size();
        }

        // Return the size of the world area.

        return {width, height};
    }

    bool WorldArea::IsValidCoordinate(int x, int y) const {
        // Obtain the size of the world area.

        auto size{this->GetSize()};

        // Return true if the coordinate is valid, false otherwise.

        return x >= 0 && y >= 0 && x < size.width && y < size.height;
    }

    bool WorldArea::IsValidCoordinate(Point coordinate) const {
        // Forward the call to other IsValidCoordinate method.

        return this->IsValidCoordinate(coordinate.x, coordinate.y);
    }

    SharedPtr<Tile> WorldArea::GetTile(int x, int y) const {
        // If the coordinate is valid, return the tile.

        if (this->IsValidCoordinate(x, y)) {
            return m_tiles.at(x).at(y);
        }

        // Otherwise, return nullptr to indicate an invalid coordinate.

        return nullptr;
    }

    SharedPtr<Tile> WorldArea::GetTile(Point coord) const {
        // Forward the call to other GetTile method.

        return this->GetTile(coord.x, coord.y);
    }

    void WorldArea::AddClaimedCoordinate(Point coordinate) {
        // Add the coordinate to the claimed coordinates.

        m_claimedCoordinates.insert(coordinate);
    }

    bool WorldArea::CoordinateIsClaimed(Point coordinate) const {
        // Return true if the coordinate is claimed, false otherwise.

        return m_claimedCoordinates.contains(coordinate);
    }
}