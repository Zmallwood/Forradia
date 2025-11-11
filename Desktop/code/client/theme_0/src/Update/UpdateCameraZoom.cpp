//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "UpdateCameraZoom.hpp"

#include "Mouse/MouseInput.hpp"

#include "3D/Camera.hpp"

namespace Forradia::Theme0::GameplayCore
{
    void UpdateCameraZoom()
    {
        auto mouseWheelDelta{_<MouseInput>().GetMouseWheelDeltaPickResult()};

        _<Camera>().AddZoomAmountDelta(mouseWheelDelta);
    }
}