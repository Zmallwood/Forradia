//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#pragma once

namespace Forradia::Theme0
{
    ///
    /// Class for storing creature properties.
    ///
    class CreatureIndexEntry
    {
      public:
        float modelScaling{1.0f}; ///< The scaling factor for the creature model.

        float levitationHeight{0.0f}; ///< The height at which the creature levitates.
    };
}