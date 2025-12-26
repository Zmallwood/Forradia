/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

namespace ForradiaEngine::JewelryMakerTheme
{
    /* Level calculation */ // clang-format off
        /**
        *  Calculates the current level based on the experience.
        *
        *  @param experience The experience.
        *  @return The current level.
        */
        auto calculateCurrentLevel(int experience) -> int;
    // clang-format on

    /* Experience calculations */ // clang-format off
        /**
        *  Calculates the experience required for the given level.
        *
        *  @param level The level.
        *  @return The experience required for the given level.
        */
        auto calculateExperienceForLevel(int level) -> int;

        /**
        *  Calculates the experience difference to the next level.
        *
        *  @param experience The experience.
        *  @return The experience difference to the next level.
        */
        auto calculateExperienceDifferenceToNextLevel(int experience) -> int;

        /**
        *  Calculates the experience required for the current level start.
        *
        *  @param experience The experience.
        *  @return The experience required for the current level start.
        */
        auto calculateExperienceRequiredForCurrentLevelStart(int experience) -> int;

        /**
        *  Calculates the experience gained since the level start.
        *
        *  @param experience The experience.
        *  @return The experience gained since the level start.
        */
        auto calculateExperienceGainedSinceLevelStart(int experience) -> int;
    // clang-format on

    /* Fractional experience calculation */ // clang-format off
        /**
        *  Calculates the fractional experience progress.
        *
        *  @param experience The experience.
        *  @return The fractional experience progress.
        */
        auto calculateFractionalExperienceProgress(int experience) -> float;
    // clang-format on
}
