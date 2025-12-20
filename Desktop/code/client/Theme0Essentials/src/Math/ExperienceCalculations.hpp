/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

namespace Forradia::Theme0 {
    /**
     * Calculates the current level based on the experience.
     *
     * @param experience The experience.
     * @return The current level.
     */
    auto CalculateCurrentLevel(int experience) -> int;

    /**
     * Calculates the experience required for the given level.
     *
     * @param level The level.
     * @return The experience required for the given level.
     */
    auto CalculateExperienceForLevel(int level) -> int;

    /**
     * Calculates the experience difference to the next level.
     *
     * @param experience The experience.
     * @return The experience difference to the next level.
     */
    auto CalculateExperienceDifferenceToNextLevel(int experience) -> int;

    /**
     * Calculates the experience required for the current level start.
     *
     * @param experience The experience.
     * @return The experience required for the current level start.
     */
    auto CalculateExperienceRequiredForCurrentLevelStart(int experience) -> int;

    /**
     * Calculates the experience gained since the level start.
     *
     * @param experience The experience.
     * @return The experience gained since the level start.
     */
    auto CalculateExperienceGainedSinceLevelStart(int experience) -> int;

    /**
     * Calculates the fractional experience progress.
     *
     * @param experience The experience.
     * @return The fractional experience progress.
     */
    auto CalculateFractionalExperienceProgress(int experience) -> float;
}
