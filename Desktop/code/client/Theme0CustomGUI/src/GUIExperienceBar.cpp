/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "GUIExperienceBar.hpp"
#include "Math/ExperienceCalculations.hpp"
#include "Player/Player.hpp"

namespace Forradia::Theme0 {
void GUIExperienceBar::UpdateDerived() {
  GUIMeter::UpdateDerived();

  auto &player{_<Theme0::Player>()};
  auto experience{player.GetExperience()};
  auto levelProgress{CalculateFractionalExperienceProgress(experience)};
  m_filledPercentage = levelProgress;
}

float GUIExperienceBar::GetFilledPercentage() const {
  return m_filledPercentage;
}
}