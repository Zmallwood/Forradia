/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include "GUIComponent.hpp"

namespace Forradia {
  class GUI;

  /**
   * The base class for all scenes.
   */
  class IScene {
   public:
    /**
     * Initializes the scene.
     */
    auto Initialize() -> void;

    /**
     * Called when the scene is entered.
     */
    auto OnEnter() -> void;

    /**
     * Updates the scene.
     */
    auto Update() -> void;

    /**
     * Renders the scene.
     */
    auto Render() const -> void;

   protected:
    /**
     * Initializes the scene. Should be specific to the deriving class.
     */
    virtual auto InitializeDerived() -> void {
    }

    /**
     * Called when the scene is entered. Should be specific to the deriving class.
     */
    virtual auto OnEnterDerived() -> void {
    }

    /**
     * Updates the scene. Should be specific to the deriving class.
     */
    virtual auto UpdateDerived() -> void {
    }

    /**
     * Renders the scene. Should be specific to the deriving class.
     */
    virtual auto RenderDerived() const -> void {
    }

    /**
     * Gets the GUI.
     *
     * @return The GUI.
     */
    auto GetGUI() const {
      return m_gui;
    }

   private:
    std::shared_ptr<GUI> m_gui;
  };
}
