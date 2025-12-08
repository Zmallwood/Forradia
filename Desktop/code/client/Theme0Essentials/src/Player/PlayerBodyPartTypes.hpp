//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#pragma once

namespace Forradia::Theme0::GameplayCore
{
    ///
    /// Types of body parts for the player.
    /// TODO: Decide if should be used also for other entities.
    ///
    enum class PlayerBodyPartTypes
    {
        None, ///< No body part.

        OverallBody, ///< The overall body.

        RightArm, ///< The right arm.

        LeftArm, ///< The left arm.

        Legs ///< The legs.
    };
}