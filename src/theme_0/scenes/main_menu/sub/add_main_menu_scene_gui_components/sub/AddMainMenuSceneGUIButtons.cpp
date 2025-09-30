/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "AddMainMenuSceneGUIButtons.hpp"
#include "core/engine/Engine.hpp"
#include "core/gui_core/GUI.hpp"
#include "core/gui_core/GUIButton.hpp"
#include "core/scenes_core/SceneManager.hpp"

namespace Forradia {
  void AddMainMenuSceneGUIButtons(SharedPtr<GUI> mainMenuSceneGUI) {
    mainMenuSceneGUI->AddChildComponent(
        std::make_shared<GUIButton>(0.45f, 0.36f, 0.1f, 0.04f, "New game", [] {
          GetSingleton<SceneManager>().GoToScene("WorldGenerationScene");
        }));

    mainMenuSceneGUI->AddChildComponent(std::make_shared<GUIButton>(
        0.45f, 0.44f, 0.1f, 0.04f, "Quit", [] { GetSingleton<Engine>().Stop(); }));
  }
}