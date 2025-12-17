/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "UpdateCameraZoom.hpp"
#include "3D/Camera.hpp"
#include "Mouse/MouseInput.hpp"
#include "StdAfx.hpp"

namespace Forradia::Theme0 {
auto UpdateCameraZoom() -> void {
  auto mouseWheelDelta{_<MouseInput>().GetMouseWheelDeltaPickResult()};
  _<Camera>().AddZoomAmountDelta(mouseWheelDelta);
}
}
