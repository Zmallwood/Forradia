/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include <memory>

#include "Directions.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    class ObjectsStack;
    class Entity;
    // class Robot;

    /**
     *  A tile in the game world.
     */
    class Tile
    {
      public:
        /**
         *  Constructor.
         */
        Tile()
        {
            // Initialize the tile by creating necessary components.
            this->initialize();
        }

        /**
         *  Gets the ground type of the tile, which is the hash of the ground type name.
         *
         *  @return The ground type of the tile.
         */
        auto getGround() const
        {
            return m_ground;
        }

        /**
         *  Sets the ground type of the tile, which is the hash of the ground type name.
         *
         *  @param groundHash The hash of the ground type name.
         */
        auto setGround(int groundHash) -> void;

        /**
         *  Sets the ground type of the tile, which is the name of the ground type.
         *
         *  @param groundName The name of the ground type.
         */
        auto setGround(std::string_view groundName) -> void;

        /**
         *  Gets the objects stack of the tile.
         *
         *  @return The objects stack of the tile.
         */
        auto getObjectsStack() const
        {
            return m_objectsStack;
        }

        /**
         *  Gets the entity on the tile.
         *
         *  @return The entity on the tile, or nullptr if no entity is on the tile.
         */
        auto getEntity() const
        {
            return m_entity;
        }

        /**
         *  Sets the entity on the tile.
         *
         *  @param value The entity on the tile.
         */
        auto setEntity(std::shared_ptr<Entity> value) -> void
        {
            m_entity = value;
        }

        /**
         *  Gets the elevation of the tile.
         *
         *  @return The elevation of the tile.
         */
        auto getElevation() const
        {
            return m_elevation;
        }

        /**
         *  Sets the elevation of the tile.
         *
         *  @param value The elevation of the tile.
         */
        auto setElevation(int value) -> void
        {
            m_elevation = value;
        }

        /**
         *  Gets the water depth of the tile. Is zero if there is no water on the tile.
         *
         *  @return The water depth of the tile.
         */
        auto getWaterDepth() const
        {
            return m_waterDepth;
        }

        /**
         *  Sets the water depth of the tile. Is should be zero if there is no water on the tile.
         *
         *  @param value The water depth of the tile.
         */
        auto setWaterDepth(int value) -> void
        {
            m_waterDepth = value;
        }

        /**
         *  Gets whether to force a redraw of the tile.
         *
         *  @return Whether to force a redraw of the tile.
         */
        auto getForceRedraw() const
        {
            return m_forceRedraw;
        }

        /**
         *  Sets whether to force a redraw of the tile.
         *
         *  @param value Whether to force a redraw of the tile.
         */
        auto setForceRedraw(bool value) -> void
        {
            m_forceRedraw = value;
        }

      private:
        auto initialize() -> void;

        int m_ground{0};
        std::shared_ptr<ObjectsStack> m_objectsStack{};
        std::shared_ptr<Entity> m_entity{};
        // SharedPtr<Robot> m_robot;
        int m_elevation{0};
        int m_waterDepth{0};
        bool m_forceRedraw{false};
    };
}
