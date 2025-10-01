/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "sub/player_body.hpp"

namespace forr {
  class player {
  public:
    player() { Initialize(); }

    void MoveNorth();

    void MoveEast();

    void MoveSouth();

    void MoveWest();

    auto GetName() const { return m_name; }

    auto GetPosition() const { return m_position; }

    auto GetMovementSpeed() const { return m_movementSpeed; }

    auto GetTicksLastMove() const { return m_ticksLastMove; }

    void SetTicksLastMove(int value) { m_ticksLastMove = value; }

    auto GetDestination() const { return m_destination; }

    void SetDestination(point value) { m_destination = value; }

    auto &GetPlayerBodyRef() { return m_playerBody; }

  private:
    void Initialize();

    void MoveToSuitablePosition();

    str m_name{"Unnamed Player"};
    point m_position{60, 50};
    float m_movementSpeed{5.0f};
    int m_ticksLastMove{0};
    point m_destination{-1, -1};
    player_body m_playerBody;
  };
}