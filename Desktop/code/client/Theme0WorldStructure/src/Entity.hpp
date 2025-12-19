/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once

#include "EntityTypes.hpp"

namespace Forradia::Theme0 {
  /**
   * A creature in the game world.
   */
  class Entity {
   public:
    /**
     * Constructor. Creates a creature of the given type.
     *
     * @param typeHash The entity type as a hash.
     */
    Entity(int typeHash) : m_type(typeHash) {
      // Initialize the entity.
      this->Initialize();
    }

    /**
     * Constructor. Creates a entity of the given type.
     *
     * @param typeName The entity type by name.
     */
    Entity(std::string_view typeName) : m_type{Hash(typeName)} {
      this->Initialize();
    }

    /**
     * Gets the entity type.
     *
     * @return The entity type.
     */
    auto GetType() const {
      return m_type;
    }

    /**
     * Gets the ticks since the entity last moved.
     *
     * @return The ticks since the entity last moved.
     */
    auto GetTicksLastMovement() const {
      return m_ticksLastMovement;
    }

    /**
     * Sets the ticks since the entity last moved.
     *
     * @param value The new ticks since the entity last moved.
     */
    auto SetTicksLastMovement(int value) -> void {
      m_ticksLastMovement = value;
    }

    /**
     * Gets the movement speed of the entity.
     *
     * @return The movement speed of the entity.
     */
    auto GetMovementSpeed() const {
      return m_movementSpeed;
    }

    /**
     * Gets the destination of the entity.
     *
     * @return The destination of the entity.
     */
    auto GetDestination() const {
      return m_destination;
    }

    /**
     * Sets the destination of the entity.
     *
     * @param value The new destination of the entity.
     */
    auto SetDestination(Point value) -> void {
      m_destination = value;
    }

   private:
    auto Initialize() -> void;

    int m_type{0};
    int m_ticksLastMovement{0};
    float m_movementSpeed{2.0F};
    Point m_destination{-1, -1};
    EntityTypes m_entityType{EntityTypes::Creature};
  };
}
