/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include <cmath>

    #include "ExperienceCalculations.hpp"
// clang-format on

namespace ForradiaEngine::JewelryMakerTheme
{
    /* Level calculation */ // clang-format off
        auto calculateCurrentLevel(int experience) -> int
        {
            auto level{std::trunc(log2f(pow(experience + 70, 2) / 5000)) + 1};

            return static_cast<int>(level);
        }
    // clang-format on

    /* Experience calculations */ // clang-format off
        auto calculateExperienceForLevel(int level) -> int
        {
            auto experience{std::max(sqrtf(powf(2, level - 1) * 5000) - 70, 0.0F)};

            return static_cast<int>(experience);
        }

        auto calculateExperienceDifferenceToNextLevel(int experience) -> int
        {
            auto currentLevel{calculateCurrentLevel(experience)};
            auto nextLevel{currentLevel + 1};
            auto totalExperienceForCurrentLevel{calculateExperienceForLevel(currentLevel)};
            auto totalExperienceForNextLevel{calculateExperienceForLevel(nextLevel)};

            return totalExperienceForNextLevel - totalExperienceForCurrentLevel;
        }

        auto calculateExperienceRequiredForCurrentLevelStart(int experience) -> int
        {
            auto currentLevel{calculateCurrentLevel(experience)};

            return calculateExperienceForLevel(currentLevel);
        }

        auto calculateExperienceGainedSinceLevelStart(int experience) -> int
        {
            return experience - calculateExperienceRequiredForCurrentLevelStart(experience);
        }
    // clang-format on

    /* Fractional experience calculation */ // clang-format off
        auto calculateFractionalExperienceProgress(int experience) -> float
        {
            auto experienceGain{experience -
                                calculateExperienceRequiredForCurrentLevelStart(experience)};
            auto experienceDiff{calculateExperienceDifferenceToNextLevel(experience)};

            return static_cast<float>(experienceGain) / experienceDiff;
        }
    // clang-format on
}
