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
        auto result{m_hasBeenFired};
        m_hasBeenFired = false;
        return result;
    }

    bool MouseButton::HasBeenFired() const {
        return m_hasBeenFired;
    }
}