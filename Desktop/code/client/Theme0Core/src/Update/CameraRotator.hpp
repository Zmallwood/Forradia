/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once

namespace Forradia::Theme0 {
  /**
   * Manages the rotation of the camera.
   */
  class CameraRotator {
   public:
    auto OnMouseDown(Uint8 mouseButton) -> void;

    auto OnMouseUp(Uint8 mouseButton) -> void;

    /**
     * Updates the camera rotation.
     */
    auto Update() -> void;

   private:
    bool m_isRotating{false};
    PointF m_mousePositionLastUpdate{-1.0F, -1.0F};
  };
}
