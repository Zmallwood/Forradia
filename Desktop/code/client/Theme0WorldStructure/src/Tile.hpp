/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "Directions.hpp"

namespace Forradia::Theme0
{
    class ObjectsStack;
    class Entity;
    // class Robot;

    /**
        A tile in the game world.
     */
    class Tile
    {
      public:
        /**
            Constructor.
         */
        Tile()
        {
            // Initialize the tile by creating necessary components.
            this->Initialize();
        }

        /**
            Gets the ground type of the tile, which is the hash of the ground type name.

            @return The ground type of the tile.
         */
        auto GetGround() const
        {
            return m_ground;
        }

        /**
            Sets the ground type of the tile, which is the hash of the ground type name.

            @param groundHash The hash of the ground type name.
         */
        auto SetGround(int groundHash) -> void;

        /**
            Sets the ground type of the tile, which is the name of the ground type.

            @param groundName The name of the ground type.
         */
        auto SetGround(std::string_view groundName) -> void;

        /**
            Gets the objects stack of the tile.

            @return The objects stack of the tile.
         */
        auto GetObjectsStack() const
        {
            return m_objectsStack;
        }

        /**
            Gets the entity on the tile.

            @return The entity on the tile, or nullptr if no entity is on the tile.
         */
        auto GetEntity() const
        {
            return m_entity;
        }

        /**
            Sets the entity on the tile.

            @param value The entity on the tile.
         */
        auto SetEntity(std::shared_ptr<Entity> value) -> void
        {
            m_entity = value;
        }

        /**
            Gets the elevation of the tile.

            @return The elevation of the tile.
         */
        auto GetElevation() const
        {
            return m_elevation;
        }

        /**
            Sets the elevation of the tile.

            @param value The elevation of the tile.
         */
        auto SetElevation(int value) -> void
        {
            m_elevation = value;
        }

        /**
            Gets the water depth of the tile. Is zero if there is no water on the tile.

            @return The water depth of the tile.
         */
        auto GetWaterDepth() const
        {
            return m_waterDepth;
        }

        /**
            Sets the water depth of the tile. Is should be zero if there is no water on the tile.

            @param value The water depth of the tile.
         */
        auto SetWaterDepth(int value) -> void
        {
            m_waterDepth = value;
        }

        /**
            Gets whether to force a redraw of the tile.

            @return Whether to force a redraw of the tile.
         */
        auto GetForceRedraw() const
        {
            return m_forceRedraw;
        }

        /**
            Sets whether to force a redraw of the tile.

            @param value Whether to force a redraw of the tile.
         */
        auto SetForceRedraw(bool value) -> void
        {
            m_forceRedraw = value;
        }

      private:
        auto Initialize() -> void;

        int m_ground{0};
        std::shared_ptr<ObjectsStack> m_objectsStack{};
        std::shared_ptr<Entity> m_entity{};
        // SharedPtr<Robot> m_robot;
        int m_elevation{0};
        int m_waterDepth{0};
        bool m_forceRedraw{false};
    };
}
