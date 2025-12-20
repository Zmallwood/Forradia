/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include "IScene.hpp"

namespace Forradia::Theme0 {
  class GUIInteractionMenu;
  class GUIInventoryWindow;
  class GUIPlayerBodyWindow;

  /**
   * The main scene is the scene where the actual game is played.
   */
  class MainScene : public IScene {
    /**
     * Initializes the main scene.
     */
    virtual auto InitializeDerived() -> void override;

    /**
     * Called when the main scene is entered.
     */
    virtual auto OnEnterDerived() -> void override;

    virtual auto OnMouseDown(Uint8 mouseButton) -> void override;

    virtual auto OnMouseUp(Uint8 mouseButton, int clickSpeed) -> void override;

    virtual auto OnMouseWheel(int delta) -> void override;

    // virtual auto Update() -> void override;

    virtual auto Render() const -> void override;

    /**
     * Called every frame.
     */
    virtual auto UpdateDerived() -> void override;

    /**
     * Called every frame to render the scene.
     */
    virtual auto RenderDerived() const -> void override;

   private:
    std::shared_ptr<GUIInteractionMenu> m_guiInteractionMenu;
    std::shared_ptr<GUIInventoryWindow> m_guiInventoryWindow;
    std::shared_ptr<GUIPlayerBodyWindow> m_guiPlayerBodyWindow;
  };
}
