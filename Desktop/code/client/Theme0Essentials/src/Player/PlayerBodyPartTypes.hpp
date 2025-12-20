/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

namespace Forradia::Theme0 {
    /**
     * Types of body parts for the player.
     * TODO: Decide if should keep this, and if so, if should also be used for other entities.
     */
    enum class PlayerBodyPartTypes {
        None,
        OverallBody,
        RightArm,
        LeftArm,
        Legs
    };
}
