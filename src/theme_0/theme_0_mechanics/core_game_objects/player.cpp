/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "player.hpp"
#include "theme_0/theme_0_mechanics/configuration/game_properties.hpp"
#include "theme_0/theme_0_mechanics/world_structure/tile.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world_area.hpp"

namespace forr {
  void Player::Initialize() { MoveToSuitablePosition(); }

  void Player::MoveToSuitablePosition() {
    auto worldArea{GetSingleton<World>().GetCurrentWorldArea()};
    auto size{worldArea->GetSize()};
    m_position = {size.width / 2, size.height / 2};
    while (worldArea->GetTile(m_position)->GetGround() == Hash("GroundWater")) {
      m_position = {RandomInt(size.width), RandomInt(size.height)};
    }
  }

  void Player::MoveNorth() { m_position.y -= 1; }

  void Player::MoveEast() { m_position.x += 1; }

  void Player::MoveSouth() { m_position.y += 1; }

  void Player::MoveWest() { m_position.x -= 1; }
}