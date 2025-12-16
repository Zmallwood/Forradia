//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#include "ExperienceCalculations.hpp"

namespace Forradia::Theme0 {
    int CalculateCurrentLevel(int experience) {
        auto level{std::trunc(log2f(pow(experience + 70, 2) / 5000)) + 1};
        return CInt(level);
    }

    int CalculateExperienceForLevel(int level) {
        auto experience{std::max(sqrtf(powf(2, level - 1) * 5000) - 70, 0.0f)};
        return CInt(experience);
    }

    int CalculateExperienceDifferenceToNextLevel(int experience) {
        auto currentLevel{CalculateCurrentLevel(experience)};
        auto nextLevel{currentLevel + 1};
        auto totalExperienceForCurrentLevel{CalculateExperienceForLevel(currentLevel)};
        auto totalExperienceForNextLevel{CalculateExperienceForLevel(nextLevel)};
        return totalExperienceForNextLevel - totalExperienceForCurrentLevel;
    }

    int CalculateExperienceRequiredForCurrentLevelStart(int experience) {
        auto currentLevel{CalculateCurrentLevel(experience)};
        return CalculateExperienceForLevel(currentLevel);
    }

    int CalculateExperienceGainedSinceLevelStart(int experience) {
        return experience - CalculateExperienceRequiredForCurrentLevelStart(experience);
    }

    float CalculateFractionalExperienceProgress(int experience) {
        auto experienceGain{experience -
                            CalculateExperienceRequiredForCurrentLevelStart(experience)};
        auto experienceDiff{CalculateExperienceDifferenceToNextLevel(experience)};
        return CFloat(experienceGain) / experienceDiff;
    }
}