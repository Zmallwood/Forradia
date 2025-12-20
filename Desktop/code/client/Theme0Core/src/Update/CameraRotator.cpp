/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "CameraRotator.hpp"
#include "3D/Camera.hpp"
#include "Mouse/MouseInput.hpp"
#include "SDLDevice.hpp"

namespace Forradia::Theme0 {

  auto CameraRotator::OnMouseDown(Uint8 mouseButton) -> void {
    if (mouseButton == SDL_BUTTON_RIGHT) {
      m_isRotating = true;

      m_mousePositionLastUpdate = GetNormallizedMousePosition(_<SDLDevice>().GetWindow());
    }
  }

  auto CameraRotator::OnMouseUp(Uint8 mouseButton) -> void {
    if (mouseButton == SDL_BUTTON_RIGHT) {
      if (m_isRotating)
        m_isRotating = false;
    }
  }

  auto CameraRotator::Update() -> void {
    if (m_isRotating) {
      auto mousePosition{GetNormallizedMousePosition(_<SDLDevice>().GetWindow())};

      auto dX{mousePosition.x - m_mousePositionLastUpdate.x};

      _<Camera>().AddRotationDeltaSideways(dX);

      auto dY{mousePosition.y - m_mousePositionLastUpdate.y};

      _<Camera>().AddRotationDeltaVertical(dY);
    }
  }
}
