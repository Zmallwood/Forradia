/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once

namespace Forradia {
/**
 * Point in 3D space using dimensions of float type.
 */
class Point3F {
 public:
  /**
   * The x dimension.
   */
  float x{0.0f};

  /**
   * The y dimension.
   */
  float y{0.0f};

  /**
   * The z dimension.
   */
  float z{0.0f};
};
}