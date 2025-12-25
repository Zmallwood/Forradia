/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include "EntityTypes.hpp"
    #include "ForradiaEngine/Common/Matter/Geometry/Point.hpp"
// clang-format on

namespace ForradiaEngine::Theme0
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

      private:
        auto initialize() -> void;

        int m_type{0};
        int m_ticksLastMovement{0};
        float m_movementSpeed{2.0F};
        Point m_destination{-1, -1};
        EntityTypes m_entityType{EntityTypes::Creature};
    };
}
