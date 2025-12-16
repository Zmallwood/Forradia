/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "GUIWellBeingMeter.hpp"
#include "Player/Player.hpp"

namespace Forradia::Theme0 {
void GUIWellBeingMeter::UpdateDerived() {
  GUIMeter::UpdateDerived();

  auto &player{_<Theme0::Player>()};

  auto health{player.GetWellBeing()};
  auto maxHealth{player.GetMaxWellBeing()};

  auto bounds{this->GetBounds()};

  m_filledPercentage = health / maxHealth;
}

float GUIWellBeingMeter::GetFilledPercentage() const {
  return m_filledPercentage;
}
}