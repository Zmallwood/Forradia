/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class Creature {
  public:
    Creature(StringView typeName) : m_type{Hash(typeName)} { Initialize(); }

    auto GetType() const { return m_type; }

    auto GetTicksLastMove() const { return m_ticksLastMove; }

    void SetTicksLastMove(int value) { m_ticksLastMove = value; }

    auto GetMovementSpeed() const { return m_movementSpeed; }

    auto GetDestination() const { return m_destination; }

    void SetDestination(Point value) { m_destination = value; }

  private:
    void Initialize();

    int m_type{0};
    int m_ticksLastMove{0};
    float m_movementSpeed{2.0f};
    Point m_destination{-1, -1};
  };
}