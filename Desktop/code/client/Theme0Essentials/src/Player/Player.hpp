/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include "PlayerActions/PlayerActionTypes.hpp"
#include "PlayerBody.hpp"
#include "PlayerModes.hpp"

namespace Forradia::Theme0 {
class PlayerObjectsInventory;

/**
 * Represents the player character.
 */
class Player {
 public:
  /**
   * Constructor.
   */
  Player() {
    // Initialize the player character.
    this->Initialize();
  }

  /**
   * Moves the player north.
   */
  void MoveNorth();

  /**
   * Moves the player east.
   */
  void MoveEast();

  /**
   * Moves the player south.
   */
  void MoveSouth();

  /**
   * Moves the player west.
   */
  void MoveWest();

  /**
   * Adds experience to the player.
   *
   * @param experience The experience to add.
   */
  void AddExperience(int experience);

  /**
   * Adds a player action to the player.
   *
   * @param playerAction The type of the player action.
   * @param actionFirstArgument The first argument of the player action.
   * @param actionSecondArgument The second argument of the player action.
   */
  void AddPlayerAction(PlayerActionTypes playerAction, StringView actionFirstArgument = "",
                       Point actionSecondArgument = {-1, -1});

  /**
   * Gets the name of the player.
   *
   * @return The name of the player.
   */
  auto GetName() const {
    return m_name;
  }

  /**
   * Sets the position of the player.
   *
   * @param value The value to set.
   */
  void SetPosition(Point value) {
    m_position = value;
  }

  /**
   * Gets the position of the player.
   *
   * @return The position of the player.
   */
  auto GetPosition() const {
    return m_position;
  }

  /**
   * Gets the movement speed of the player.
   *
   * @return The movement speed of the player.
   */
  auto GetMovementSpeed() const {
    return m_movementSpeed;
  }

  /**
   * Gets the ticks since last movement.
   *
   * @return The ticks since last movement.
   */
  auto GetTicksLastMovement() const {
    return m_ticksLastMovement;
  }

  /**
   * Sets the ticks since last movement.
   *
   * @param value The value to set.
   */
  void SetTicksLastMovement(int value) {
    m_ticksLastMovement = value;
  }

  /**
   * Gets the destination of the player.
   *
   * @return The destination of the player.
   */
  auto GetDestination() const {
    return m_destination;
  }

  /**
   * Sets the destination of the player.
   *
   * @param value The value to set.
   */
  void SetDestination(Point value) {
    m_destination = value;
  }

  /**
   * Gets the body of the player.
   *
   * @return The body of the player.
   */
  auto &GetBodyRef() {
    return m_playerBody;
  }

  /**
   * Gets the objects inventory of the player.
   *
   * @return The objects inventory of the player.
   */
  auto &GetObjectsInventoryRef() const {
    return *m_playerObjectsInventory;
  }

  /**
   * Gets the experience of the player.
   *
   * @return The experience of the player.
   */
  auto GetExperience() const {
    return m_experience;
  }

  // auto GetPlayerMode() const {
  //   return m_playerMode;
  // }

  // void SetPlayerMode(PlayerModes playerMode) {
  //   m_playerMode = playerMode;
  // }

  /**
   * Gets the well being of the player.
   *
   * @return The well being of the player.
   */
  auto GetWellBeing() const {
    return m_wellBeing;
  }

  /**
   * Gets the max well being of the player.
   *
   * @return The max well being of the player.
   */
  auto GetMaxWellBeing() const {
    return m_maxWellBeing;
  }

  // auto GetAttackSpeed() const {
  //   return m_attackSpeed;
  // }

  // auto GetTicksLastHitAnother() const {
  //   return m_ticksLastHitAnother;
  // }

  // void SetTicksLastHitAnother(int value) {
  //   m_ticksLastHitAnother = value;
  // }

  /**
   * Gets the player actions of the player.
   *
   * @return The player actions of the player.
   */
  auto &GetPlayerActionsRef() const {
    return m_playerActions;
  }

  /**
   * Gets the quest completion points of the player.
   *
   * @return The quest completion points of the player.
   */
  auto &GetQuestCompletionPointsRef() {
    return m_questCompletionPoints;
  }

 private:
  void Initialize();

  void MoveToSuitablePosition();

  String m_name{"Unnamed Player"};
  Point m_position{60, 50};
  float m_movementSpeed{5.0f};
  int m_ticksLastMovement{0};
  Point m_destination{-1, -1};
  PlayerBody m_playerBody;
  SharedPtr<PlayerObjectsInventory> m_playerObjectsInventory;
  int m_experience{0};
  // PlayerModes m_playerMode{PlayerModes::Interaction};
  float m_wellBeing{10.0f};
  float m_maxWellBeing{10.0f};
  // float m_attackSpeed{3.0f};
  // int m_ticksLastHitAnother{0};
  Vector<std::tuple<PlayerActionTypes, String, Point>> m_playerActions;
  std::map<String, int> m_questCompletionPoints;
};
}