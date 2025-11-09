//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "Directions.hpp"

namespace Forradia::Theme0
{
    class ObjectsStack;

    class Creature;

    class Robot;

    ///
    /// A tile in the game world.
    ///
    class Tile
    {
      public:
        ///
        /// Constructor.
        ///
        Tile()
        {
            this->Initialize();
        }

        ///
        /// Gets the ground type of the tile, which is the hash of the ground type name.
        ///
        /// @return The ground type of the tile.
        ///
        auto GetGround() const
        {
            return m_ground;
        }

        ///
        /// Sets the ground type of the tile, which is the hash of the ground type name.
        ///
        /// @param groundHash The hash of the ground type name.
        ///
        void SetGround(int groundHash);

        ///
        /// Sets the ground type of the tile, which is the name of the ground type.
        ///
        /// @param groundName The name of the ground type.
        ///
        void SetGround(StringView groundName);

        ///
        /// Gets the objects stack of the tile.
        ///
        /// @return The objects stack of the tile.
        ///
        auto GetObjectsStack() const
        {
            return m_objectsStack;
        }

        ///
        /// Gets the creature on the tile.
        ///
        /// @return The creature on the tile, or nullptr if no creature is on the tile.
        ///
        auto GetCreature() const
        {
            return m_creature;
        }

        ///
        /// Sets the creature on the tile.
        ///
        /// @param value The creature on the tile.
        ///
        void SetCreature(SharedPtr<Creature> value)
        {
            m_creature = value;
        }

        ///
        /// Gets the robot on the tile.
        ///
        /// @return The robot on the tile, or nullptr if no robot is on the tile.
        ///
        auto GetRobot() const
        {
            return m_robot;
        }

        ///
        /// Sets the robot on the tile.
        ///
        /// @param value The robot on the tile.
        ///
        void SetRobot(SharedPtr<Robot> value)
        {
            m_robot = value;
        }

        ///
        /// Gets the elevation of the tile.
        ///
        /// @return The elevation of the tile.
        ///
        auto GetElevation() const
        {
            return m_elevation;
        }

        ///
        /// Sets the elevation of the tile.
        ///
        /// @param value The elevation of the tile.
        ///
        void SetElevation(int value)
        {
            m_elevation = value;
        }

        ///
        /// Gets the water depth of the tile. Is zero if there is no water on the tile.
        ///
        /// @return The water depth of the tile.
        ///
        auto GetWaterDepth() const
        {
            return m_waterDepth;
        }

        ///
        /// Sets the water depth of the tile. Is should be zero if there is no water on the tile.
        ///
        /// @param value The water depth of the tile.
        ///
        void SetWaterDepth(int value)
        {
            m_waterDepth = value;
        }

      private:
        ///
        /// Initializes the tile.
        ///
        void Initialize();

        int m_ground{0}; ///< The ground type of the tile.

        SharedPtr<ObjectsStack> m_objectsStack; ///< The objects stack of the tile.

        SharedPtr<Creature> m_creature; ///< The creature on the tile.

        SharedPtr<Robot> m_robot; ///< The robot on the tile.

        int m_elevation{0}; ///< The elevation of the tile.

        int m_waterDepth{0}; ///< The water depth of the tile.
    };
}