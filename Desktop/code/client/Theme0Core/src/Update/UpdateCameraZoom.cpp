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

namespace Forradia::Theme0 {
void UpdateCameraZoom() {
  auto mouseWheelDelta{_<MouseInput>().GetMouseWheelDeltaPickResult()};
  _<Camera>().AddZoomAmountDelta(mouseWheelDelta);
}
}