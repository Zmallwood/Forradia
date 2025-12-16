//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#include "UpdateCameraZoom.hpp"
#include "3D/Camera.hpp"
#include "Mouse/MouseInput.hpp"

namespace Forradia::Theme0::GameplayCore {
    void UpdateCameraZoom() {
        // Obtain the mouse wheel delta.

        auto mouseWheelDelta{_<MouseInput>().GetMouseWheelDeltaPickResult()};

        // Add the mouse wheel delta to the camera zoom amount.

        _<Camera>().AddZoomAmountDelta(mouseWheelDelta);
    }
}