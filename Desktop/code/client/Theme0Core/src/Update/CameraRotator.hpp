/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once

namespace Forradia::Theme0 {
/**
 * Manages the rotation of the camera.
 */
class CameraRotator {
 public:
  /**
   * Updates the camera rotation.
   */
  void Update();

 private:
  bool m_isRotating{false};
  PointF m_mousePositionLastUpdate{-1.0f, -1.0f};
};
}