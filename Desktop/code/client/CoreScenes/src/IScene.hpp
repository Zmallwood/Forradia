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
  void Initialize();

  /**
   * Called when the scene is entered.
   */
  void OnEnter();

  /**
   * Updates the scene.
   */
  void Update();

  /**
   * Renders the scene.
   */
  void Render() const;

 protected:
  /**
   * Initializes the scene. Should be specific to the deriving class.
   */
  virtual void InitializeDerived() {
  }

  /**
   * Called when the scene is entered. Should be specific to the deriving class.
   */
  virtual void OnEnterDerived() {
  }

  /**
   * Updates the scene. Should be specific to the deriving class.
   */
  virtual void UpdateDerived() {
  }

  /**
   * Renders the scene. Should be specific to the deriving class.
   */
  virtual void RenderDerived() const {
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
  SharedPtr<GUI> m_gui;
};
}