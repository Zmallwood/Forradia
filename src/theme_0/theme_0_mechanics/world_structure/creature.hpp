/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class creature {
  public:
    creature(str_view typeName) : m_type{Hash(typeName)} { initialize(); }

    auto get_type() const { return m_type; }

    auto get_ticks_last_move() const { return m_ticksLastMove; }

    void set_ticks_last_move(int value) { m_ticksLastMove = value; }

    auto get_movement_speed() const { return m_movementSpeed; }

    auto get_destination() const { return m_destination; }

    void set_destination(point value) { m_destination = value; }

  private:
    void initialize();

    int m_type{0};
    int m_ticksLastMove{0};
    float m_movementSpeed{2.0f};
    point m_destination{-1, -1};
  };
}