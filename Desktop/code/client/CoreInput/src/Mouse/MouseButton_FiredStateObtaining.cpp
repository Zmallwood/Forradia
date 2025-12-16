//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Complete.
// TODO:

#include "MouseButton.hpp"

namespace Forradia {
    bool MouseButton::HasBeenFiredPickResult() {
        // Check if the button has been fired and store as result.
        auto result{m_hasBeenFired};

        // Clear the been-fired state of the button.
        m_hasBeenFired = false;

        // Return the result.
        return result;
    }

    bool MouseButton::HasBeenFired() const {
        // Return the been-fired state of the button.
        return m_hasBeenFired;
    }
}