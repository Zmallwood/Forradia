/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

// TODO: Consider change to having a class called Entity for both Creatures and Robots.

#pragma once

namespace Forradia::Theme0 {
/**
 * A robot in the game world.
 */
class Robot {
 public:
  /**
   * Constructor. Creates a robot of the given type.
   *
   * @param typeHash The robot type as a hash.
   * @param originX The x coordinate of the origin.
   * @param originY The y coordinate of the origin.
   */
  Robot(int typeHash, int originX, int originY) : m_type(typeHash), m_origin({originX, originY}) {
    this->Initialize();
  }

  /**
   * Constructor. Creates a robot of the given type.
   *
   * @param typeName The robot type by name.
   * @param originX The x coordinate of the origin.
   * @param originY The y coordinate of the origin.
   */
  Robot(StringView typeName, int originX, int originY)
      : m_type{Hash(typeName)}, m_origin({originX, originY}) {
    this->Initialize();
  }

  /**
   * Gets the robot type.
   *
   * @return The robot type.
   */
  auto GetType() const {
    return m_type;
  }

  /**
   * Gets the ticks since the robot last moved.
   *
   * @return The ticks since the robot last moved.
   */
  auto GetTicksLastMovement() const {
    return m_ticksLastMovement;
  }

  /**
   * Sets the ticks since the robot last moved.
   *
   * @param value The new ticks since the robot last moved.
   */
  auto SetTicksLastMovement(int value) -> void {
    m_ticksLastMovement = value;
  }

  /**
   * Gets the movement speed of the robot.
   *
   * @return The movement speed of the robot.
   */
  auto GetMovementSpeed() const {
    return m_movementSpeed;
  }

  /**
   * Gets the destination of the robot.
   *
   * @return The destination of the robot.
   */
  auto GetDestination() const {
    return m_destination;
  }

  /**
   * Sets the destination of the robot.
   *
   * @param value The new destination of the robot.
   */
  auto SetDestination(Point value) -> void {
    m_destination = value;
  }

  /**
   * Gets the origin of the robot.
   *
   * @return The origin of the robot.
   */
  auto GetOrigin() const {
    return m_origin;
  }

 private:
  auto Initialize() -> void;

  int m_type{0};
  int m_ticksLastMovement{0};
  float m_movementSpeed{1.0f};
  Point m_destination{-1, -1};
  Point m_origin{-1, -1};
};
}
