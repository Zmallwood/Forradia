/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once

namespace Forradia::Theme0 {
class WorldArea;

///
/// Base class for world generators.
///
class WorldGeneratorBase {
 public:
  ///
  /// Prepare the world generator.
  ///
  void Prepare();

 protected:
  ///
  /// Get the distance between two points.
  ///
  /// @param x1 The x coordinate of the first point.
  /// @param y1 The y coordinate of the first point.
  /// @param x2 The x coordinate of the second point.
  /// @param y2 The y coordinate of the second point.
  /// @return The distance between the two points.
  ///
  float GetDistance(int x1, int y1, int x2, int y2) const;

  ///
  /// Get the default ground elevation.
  ///
  /// @return The default ground elevation.
  ///
  auto GetDefaultGroundElevation() const {
    return k_defaultGroundElevation;
  }

  ///
  /// Get the world area.
  ///
  /// @return The world area.
  ///
  auto GetWorldArea() const {
    return m_worldArea;
  }

  ///
  /// Get the size of the world area.
  ///
  /// @return The size of the world area.
  ///
  auto GetWorldAreaSize() const {
    return m_worldAreaSize;
  }

  ///
  /// Get the scale factor of the world.
  ///
  /// @return The scale factor of the world.
  ///
  auto GetWorldScaling() const {
    return m_worldScaling;
  }

 private:
  const int k_defaultGroundElevation{10}; ///< The default ground elevation.
  SharedPtr<WorldArea> m_worldArea;       ///< The world area.
  Size m_worldAreaSize;                   ///< The size of the world area.
  float m_worldScaling;                   ///< The scale factor of the world.
};
}