//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "UpdateCameraZoom.hpp"

#include "Mouse/MouseInput.hpp"

#include "3D/Camera.hpp"

namespace AAK
{
    namespace Forradia::Theme0::GameplayCore
    {
        void UpdateCameraZoom()
        {
            // Obtain the mouse wheel delta.

            auto mouseWheelDelta{_<MouseInput>().GetMouseWheelDeltaPickResult()};

            // Add the mouse wheel delta to the camera zoom amount.

            _<Camera>().AddZoomAmountDelta(mouseWheelDelta);
        }
    }
}