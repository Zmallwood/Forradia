/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include "IScene.hpp"

namespace Forradia {
class GUIComponent;
}

namespace Forradia::Theme0 {
/**
 * The intro scene is the first scene that is displayed when the game is started.
 * It displays the title of the game and the main menu.
 */
class IntroScene : public IScene {
 protected:
  /**
   * Initializes the intro scene.
   */
  virtual void InitializeDerived() override;

  /**
   * Called when the intro scene is entered.
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

 private:
  SharedPtr<GUIComponent> m_startText;
};
}