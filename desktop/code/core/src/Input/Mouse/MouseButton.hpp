//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace Forradia
{
    class MouseButton
    {
      public:
        void Reset();

        void RegisterPress();

        void RegisterRelease();

        bool IsPressedPickResult();

        bool HasBeenFiredPickResult();

        bool HasBeenFired();

        bool HasBeenReleasedPickResult();

        bool HasBeenReleased();

      private:
        bool m_pressed{false};

        bool m_hasBeenFired{false};

        bool m_hasBeenReleased{false};
    };
}