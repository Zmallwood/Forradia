//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#include "GUIExperienceBar.hpp"
#include "Math/ExperienceCalculations.hpp"
#include "Player/PlayerCharacter.hpp"

namespace Forradia::Theme0 {
void GUIExperienceBar::UpdateDerived() {
  GUIMeter::UpdateDerived();

  auto &playerCharacter{_<Theme0::PlayerCharacter>()};
  auto experience{playerCharacter.GetExperience()};
  auto levelProgress{CalculateFractionalExperienceProgress(experience)};
  m_filledPercentage = levelProgress;
}

float GUIExperienceBar::GetFilledPercentage() const {
  return m_filledPercentage;
}
}