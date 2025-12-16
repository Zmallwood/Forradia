//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#pragma once

namespace Forradia::Theme0::GameplayCore {
    int CalculateCurrentLevel(int experience);

    int CalculateExperienceForLevel(int level);

    int CalculateExperienceDifferenceToNextLevel(int experience);

    int CalculateExperienceRequiredForCurrentLevelStart(int experience);

    int CalculateExperienceGainedSinceLevelStart(int experience);

    float CalculateFractionalExperienceProgress(int experience);
}