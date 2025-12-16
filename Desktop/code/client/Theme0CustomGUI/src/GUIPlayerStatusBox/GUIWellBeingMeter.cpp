/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "GUIWellBeingMeter.hpp"
#include "Player/PlayerCharacter.hpp"

namespace Forradia::Theme0 {
void GUIWellBeingMeter::UpdateDerived() {
  GUIMeter::UpdateDerived();

  auto &playerCharacter{_<Theme0::PlayerCharacter>()};

  auto health{playerCharacter.GetWellBeing()};
  auto maxHealth{playerCharacter.GetMaxWellBeing()};

  auto bounds{this->GetBounds()};

  m_filledPercentage = health / maxHealth;
}

float GUIWellBeingMeter::GetFilledPercentage() const {
  return m_filledPercentage;
}
}