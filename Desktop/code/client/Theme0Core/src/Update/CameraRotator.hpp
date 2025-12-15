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
    class CameraRotator
    {
      public:
        void Update();

      private:
        bool m_isRotating{false};
        PointF m_mousePositionLastUpdate{-1.0f, -1.0f};
    };
}