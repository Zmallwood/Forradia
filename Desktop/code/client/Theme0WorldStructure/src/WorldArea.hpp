//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#pragma once

namespace Forradia::Theme0
{
    class Tile;

    class Creature;

    class Robot;

    ///
    /// A world area in the game.
    ///
    class WorldArea
    {
      public:
        ///
        /// Constructor.
        ///
        /// @param worldAreaSize The size of the world area.
        /// @param worldScaling The scaling of the world area size.
        ///
        WorldArea(Size worldAreaSize, float worldScaling)
        {
            // Initialize the world area.

            this->Initialize(worldAreaSize, worldScaling);
        }

        ///
        /// Resets the world area.
        ///
        void Reset();

        ///
        /// Gets the size of the world area.
        ///
        /// @return The size of the world area.
        ///
        Size GetSize() const;

        ///
        /// Checks if a coordinate is valid in the world area.
        ///
        /// @param x The x coordinate.
        /// @param y The y coordinate.
        /// @return True if the coordinate is valid, false otherwise.
        ///
        bool IsValidCoordinate(int x, int y) const;

        ///
        /// Checks if a coordinate is valid in the world area.
        ///
        /// @param coordinate The coordinate.
        /// @return True if the coordinate is valid, false otherwise.
        ///
        bool IsValidCoordinate(Point coordinate) const;

        ///
        /// Gets the tile at the given coordinate.
        ///
        /// @param x The x coordinate.
        /// @param y The y coordinate.
        /// @return The tile at the given coordinate, or nullptr if the coordinate is invalid.
        ///
        SharedPtr<Tile> GetTile(int x, int y) const;

        ///
        /// Gets the tile at the given coordinate.
        ///
        /// @param coordinate The coordinate.
        /// @return The tile at the given coordinate, or nullptr if the coordinate is invalid.
        ///
        SharedPtr<Tile> GetTile(Point coord) const;

        ///
        /// Adds a claimed coordinate.
        ///
        /// @param coordinate The coordinate to add.
        ///
        void AddClaimedCoordinate(Point coordinate);

        ///
        /// Checks if a coordinate is claimed.
        ///
        /// @param coordinate The coordinate to check.
        /// @return True if the coordinate is claimed, false otherwise.
        ///
        bool CoordinateIsClaimed(Point coordinate) const;

        ///
        /// Gets a reference to the creatures mirror.
        ///
        /// @return A reference to the creatures mirror.
        ///
        auto &GetCreaturesMirrorRef()
        {
            return m_creaturesMirror;
        }

        ///
        /// Gets a reference to the robots mirror.
        ///
        /// @return A reference to the robots mirror.
        ///
        auto &GetRobotsMirrorRef()
        {
            return m_robotsMirror;
        }

      private:
        ///
        /// Initializes the world area.
        ///
        /// @param worldAreaSize The size of the world area.
        /// @param worldScaling The scaling of the world area size.
        ///
        void Initialize(Size worldAreaSize, float worldScaling);

        Vector<Vector<SharedPtr<Tile>>> m_tiles; ///< The tiles in the world area.

        std::map<SharedPtr<Creature>, Point> m_creaturesMirror; ///< The creatures mirror.

        std::map<SharedPtr<Robot>, Point> m_robotsMirror; ///< The robots mirror.

        std::set<Point> m_claimedCoordinates; ///< The claimed coordinates.
    };
}