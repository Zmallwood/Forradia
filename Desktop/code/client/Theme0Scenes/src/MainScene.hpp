/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include "IScene.hpp"

namespace Forradia::Theme0 {
/**
 * The main scene is the scene where the actual game is played.
 */
class MainScene : public IScene {
  /**
   * Initializes the main scene.
   */
  virtual void InitializeDerived() override;

  /**
   * Called when the main scene is entered.
   */
  virtual void OnEnterDerived() override;

  /**
   * Called every frame.
   */
  virtual void UpdateDerived() override;

  /**
   * Called every frame to render the scene.
   */
  virtual void RenderDerived() const override;
};
}