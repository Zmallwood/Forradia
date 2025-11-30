//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "MouseButton.hpp"

namespace AAK
{
    namespace Forradia
    {
        bool MouseButton::HasBeenReleasedPickResult()
        {
            // Check if the button has been released and store as result.

            auto result{m_hasBeenReleased};

            // Clear the been-released state of the button.

            m_hasBeenReleased = false;

            // Return the result.

            return result;
        }

        bool MouseButton::HasBeenReleased() const
        {
            // Return the been-released state of the button.

            return m_hasBeenReleased;
        }
    }
}