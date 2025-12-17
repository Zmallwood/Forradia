/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "Player.hpp"
#include "ObjectsStack.hpp"
#include "PlayerObjectsInventory.hpp"
#include "Tile.hpp"
#include "World.hpp"
#include "WorldArea.hpp"

namespace Forradia::Theme0 {
void Player::Initialize() {
  m_playerObjectsInventory = std::make_shared<PlayerObjectsInventory>();
  this->MoveToSuitablePosition();
}

void Player::MoveToSuitablePosition() {
  auto worldArea{_<World>().GetCurrentWorldArea()};
  auto size{worldArea->GetSize()};

  m_position = {size.width / 2, size.height / 2};

  while (worldArea->GetTile(m_position)->GetGround() == Hash("GroundWater"))
    m_position = {GetRandomInt(size.width), GetRandomInt(size.height)};
}

void Player::MoveNorth() {
  auto newX{m_position.x};
  auto newY{m_position.y - 1};
  auto worldArea{_<World>().GetCurrentWorldArea()};
  if (worldArea->GetTile(newX, newY)->GetGround() != Hash("GroundWater")) {
    m_position = {newX, newY};
    m_playerActions.push_back({PlayerActionTypes::MoveNorth, "", m_position});
  }
}

void Player::MoveEast() {
  auto newX{m_position.x + 1};
  auto newY{m_position.y};
  auto worldArea{_<World>().GetCurrentWorldArea()};
  if (worldArea->GetTile(newX, newY)->GetGround() != Hash("GroundWater")) {
    m_position = {newX, newY};
    m_playerActions.push_back({PlayerActionTypes::MoveNorth, "", m_position});
  }
}

void Player::MoveSouth() {
  auto newX{m_position.x};
  auto newY{m_position.y + 1};
  auto worldArea{_<World>().GetCurrentWorldArea()};
  if (worldArea->GetTile(newX, newY)->GetGround() != Hash("GroundWater")) {
    m_position = {newX, newY};
    m_playerActions.push_back({PlayerActionTypes::MoveNorth, "", m_position});
  }
}

void Player::MoveWest() {
  auto newX{m_position.x - 1};
  auto newY{m_position.y};
  auto worldArea{_<World>().GetCurrentWorldArea()};
  if (worldArea->GetTile(newX, newY)->GetGround() != Hash("GroundWater")) {
    m_position = {newX, newY};
    m_playerActions.push_back({PlayerActionTypes::MoveNorth, "", m_position});
  }
}

void Player::AddExperience(int experience) {
  m_experience += experience;
}

void Player::AddPlayerAction(PlayerActionTypes playerAction, StringView actionFirstArgument,
                             Point actionSecondArgument) {
  m_playerActions.push_back(std::tuple<PlayerActionTypes, String, Point>{
      playerAction, actionFirstArgument, actionSecondArgument});
}
}