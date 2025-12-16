//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#pragma once

namespace Forradia {
    ///
    /// Enum for the available cursor styles.
    ///
    enum class CursorStyles {
        Normal,               ///< The default cursor style.
        HoveringClickableGUI, ///< The cursor style when hovering over a clickable GUI element.
        HoveringCreature      /// < The cursor style when hovering over a creature.
    };
}