/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "EntityTypes.hpp"
#include "ForradiaEngine/Common/Matter/Geometry.hpp"
#include "Directions.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    /**
     *  A creature in the game world.
     */
    class Entity
    {
      public:
        /**
         *  Constructor. Creates a creature of the given type.
         *
         *  @param typeHash The entity type as a hash.
         */
        Entity(int typeHash) : m_type(typeHash)
        {
            // Initialize the entity.
            this->initialize();
        }

        /**
         *  Constructor. Creates a entity of the given type.
         *
         *  @param typeName The entity type by name.
         */
        Entity(std::string_view typeName) : m_type{hash(typeName)}
        {
            this->initialize();
        }

        /**
         *  Gets the smooth position of the entity.
         *
         *  @param position The position of the entity.
         *  @return The smooth position of the entity.
         */
        auto getSmoothPosition(Point position) const -> PointF;

        /**
         *  Updates the entity.
         */
        auto update() -> void;

        /**
         *  Updates the rotation of the entity in degrees.
         */
        auto updateRotationDegrees() -> void;

        /**
         *  Gets the entity type.
         *
         *  @return The entity type.
         */
        auto getType() const
        {
            return m_type;
        }

        /**
         *  Gets the ticks since the entity last moved.
         *
         *  @return The ticks since the entity last moved.
         */
        auto getTicksLastMovement() const
        {
            return m_ticksLastMovement;
        }

        /**
         *  Sets the ticks since the entity last moved.
         *
         *  @param value The new ticks since the entity last moved.
         */
        auto setTicksLastMovement(int value) -> void
        {
            m_ticksLastMovement = value;
        }

        /**
         *  Gets the movement speed of the entity.
         *
         *  @return The movement speed of the entity.
         */
        auto getMovementSpeed() const
        {
            return m_movementSpeed;
        }

        /**
         *  Gets the destination of the entity.
         *
         *  @return The destination of the entity.
         */
        auto getDestination() const
        {
            return m_destination;
        }

        /**
         *  Sets the destination of the entity.
         *
         *  @param value The new destination of the entity.
         */
        auto setDestination(Point value) -> void
        {
            m_destination = value;
        }

        /**
         *  Sets the direction of the entity.
         *
         *  @param value The new direction of the entity.
         */
        auto setDirection(Directions value) -> void
        {
            m_direction = value;
        }

        /**
         *  Gets the rotation of the entity in degrees.
         *
         *  @return The rotation of the entity in degrees.
         */
        auto getRotationDegrees() const -> float
        {
            return m_rotationDegrees;
        }

      private:
        auto initialize() -> void;

        int m_type{0};
        int m_ticksLastMovement{0};
        float m_movementSpeed{2.0F};
        Point m_destination{-1, -1};
        EntityTypes m_entityType{EntityTypes::Creature};
        Directions m_direction{Directions::None};
        float m_rotationDegrees{0.0F};
    };
}
