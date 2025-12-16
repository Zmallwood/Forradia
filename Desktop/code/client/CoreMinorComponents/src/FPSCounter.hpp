//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#pragma once

namespace Forradia {
///
///  Class for the FPS counter.
///
class FPSCounter {
 public:
  ///
  /// Updates the FPS counter.
  ///
  void Update();

  ///
  /// Gets the current FPS.
  ///
  /// @return The current FPS.
  ///
  auto GetFPS() const {
    return m_fps;
  }

 private:
  int m_fps{0};             ///< The current FPS.
  int m_framesCount{0};     ///< The frame count.
  int m_ticksLastUpdate{0}; ///< The last update time.
};
}