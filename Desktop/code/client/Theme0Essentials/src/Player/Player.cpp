/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "Player.hpp"
#include "ObjectsStack.hpp"
#include "PlayerObjectsInventory.hpp"
#include "Tile.hpp"
#include "World.hpp"
#include "WorldArea.hpp"

namespace Forradia::Theme0 {
  auto Player::Initialize() -> void {
    m_playerObjectsInventory = std::make_shared<PlayerObjectsInventory>();
    this->MoveToSuitablePosition();
  }

  auto Player::MoveToSuitablePosition() -> void {
    auto worldArea{_<World>().GetCurrentWorldArea()};
    auto size{worldArea->GetSize()};

    m_position = {size.width / 2, size.height / 2};

    while (worldArea->GetTile(m_position)->GetGround() == Hash("GroundWater"))
      m_position = {GetRandomInt(size.width), GetRandomInt(size.height)};
  }

  auto Player::MoveNorth() -> void {
    auto newX{m_position.x};
    auto newY{m_position.y - 1};
    auto worldArea{_<World>().GetCurrentWorldArea()};
    if (worldArea->GetTile(newX, newY)->GetGround() != Hash("GroundWater")) {
      m_position = {newX, newY};
      m_playerActions.push_back({PlayerActionTypes::MoveNorth, "", m_position});
    }
  }

  auto Player::MoveEast() -> void {
    auto newX{m_position.x + 1};
    auto newY{m_position.y};
    auto worldArea{_<World>().GetCurrentWorldArea()};
    if (worldArea->GetTile(newX, newY)->GetGround() != Hash("GroundWater")) {
      m_position = {newX, newY};
      m_playerActions.push_back({PlayerActionTypes::MoveNorth, "", m_position});
    }
  }

  auto Player::MoveSouth() -> void {
    auto newX{m_position.x};
    auto newY{m_position.y + 1};
    auto worldArea{_<World>().GetCurrentWorldArea()};
    if (worldArea->GetTile(newX, newY)->GetGround() != Hash("GroundWater")) {
      m_position = {newX, newY};
      m_playerActions.push_back({PlayerActionTypes::MoveNorth, "", m_position});
    }
  }

  auto Player::MoveWest() -> void {
    auto newX{m_position.x - 1};
    auto newY{m_position.y};
    auto worldArea{_<World>().GetCurrentWorldArea()};
    if (worldArea->GetTile(newX, newY)->GetGround() != Hash("GroundWater")) {
      m_position = {newX, newY};
      m_playerActions.push_back({PlayerActionTypes::MoveNorth, "", m_position});
    }
  }

  auto Player::AddExperience(int experience) -> void {
    m_experience += experience;
  }

  auto Player::AddPlayerAction(PlayerActionTypes playerAction, std::string_view actionFirstArgument,
                               Point actionSecondArgument) -> void {
    m_playerActions.push_back(std::tuple<PlayerActionTypes, std::string, Point>{
        playerAction, actionFirstArgument, actionSecondArgument});
  }
}
