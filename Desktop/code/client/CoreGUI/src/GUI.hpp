/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once

#include "GUIPanel.hpp"

namespace Forradia {
///
/// The root GUI class which is created for every scene.
///
class GUI : public GUIComponent {
 public:
  ///
  /// Constructor.
  ///
  GUI() : GUIComponent(0.0f, 0.0f, 1.0f, 1.0f) {
  }
};
}