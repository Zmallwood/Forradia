/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include "IScene.hpp"

namespace Forradia::Theme0 {
/**
 * The world generation scene is the scene where the world is generated.
 */
class WorldGenerationScene : public IScene {
 protected:
  /**
   * Called when the world generation scene is entered.
   */
  virtual auto OnEnterDerived() -> void override;
};
}
