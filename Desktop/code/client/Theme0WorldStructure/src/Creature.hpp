/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

// TODO: Consider change to having a class called Entity for both Creatures and Robots.

#pragma once

namespace Forradia::Theme0 {
/**
 * A creature in the game world.
 */
class Creature {
 public:
  /**
   * Constructor. Creates a creature of the given type.
   *
   * @param typeHash The creature type as a hash.
   */
  Creature(int typeHash) : m_type(typeHash) {
    // Initialize the creature.
    this->Initialize();
  }

  /**
   * Constructor. Creates a creature of the given type.
   *
   * @param typeName The creature type by name.
   */
  Creature(StringView typeName) : m_type{Hash(typeName)} {
    this->Initialize();
  }

  /**
   * Gets the creature type.
   *
   * @return The creature type.
   */
  auto GetType() const {
    return m_type;
  }

  /**
   * Gets the ticks since the creature last moved.
   *
   * @return The ticks since the creature last moved.
   */
  auto GetTicksLastMovement() const {
    return m_ticksLastMovement;
  }

  /**
   * Sets the ticks since the creature last moved.
   *
   * @param value The new ticks since the creature last moved.
   */
  auto SetTicksLastMovement(int value) -> void {
    m_ticksLastMovement = value;
  }

  /**
   * Gets the movement speed of the creature.
   *
   * @return The movement speed of the creature.
   */
  auto GetMovementSpeed() const {
    return m_movementSpeed;
  }

  /**
   * Gets the destination of the creature.
   *
   * @return The destination of the creature.
   */
  auto GetDestination() const {
    return m_destination;
  }

  /**
   * Sets the destination of the creature.
   *
   * @param value The new destination of the creature.
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
};
}
