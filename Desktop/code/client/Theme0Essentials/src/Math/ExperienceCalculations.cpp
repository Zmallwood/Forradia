/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "ExperienceCalculations.hpp"

namespace Forradia::Theme0 {
  auto CalculateCurrentLevel(int experience) -> int {
    auto level{std::trunc(log2f(pow(experience + 70, 2) / 5000)) + 1};
    return CInt(level);
  }

  auto CalculateExperienceForLevel(int level) -> int {
    auto experience{std::max(sqrtf(powf(2, level - 1) * 5000) - 70, 0.0F)};
    return CInt(experience);
  }

  auto CalculateExperienceDifferenceToNextLevel(int experience) -> int {
    auto currentLevel{CalculateCurrentLevel(experience)};
    auto nextLevel{currentLevel + 1};
    auto totalExperienceForCurrentLevel{CalculateExperienceForLevel(currentLevel)};
    auto totalExperienceForNextLevel{CalculateExperienceForLevel(nextLevel)};
    return totalExperienceForNextLevel - totalExperienceForCurrentLevel;
  }

  auto CalculateExperienceRequiredForCurrentLevelStart(int experience) -> int {
    auto currentLevel{CalculateCurrentLevel(experience)};
    return CalculateExperienceForLevel(currentLevel);
  }

  auto CalculateExperienceGainedSinceLevelStart(int experience) -> int {
    return experience - CalculateExperienceRequiredForCurrentLevelStart(experience);
  }

  auto CalculateFractionalExperienceProgress(int experience) -> float {
    auto experienceGain{experience - CalculateExperienceRequiredForCurrentLevelStart(experience)};
    auto experienceDiff{CalculateExperienceDifferenceToNextLevel(experience)};
    return CFloat(experienceGain) / experienceDiff;
  }
}
