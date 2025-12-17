/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include "IScene.hpp"

namespace Forradia::Theme0 {
/**
 * The play scene is the scene where the player can choose to play a new game or continue a saved
 * game.
 */
class PlayScene : public IScene {
  /**
   * Initializes the play scene.
   */
 protected:
  /**
   * Initializes the play scene.
   */
  virtual void InitializeDerived() override;

  /**
   * Called every frame to render the scene.
   */
  virtual void RenderDerived() const override;
};
}