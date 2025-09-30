/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "AddMainMenuSceneGUIButtons.hpp"
#include "Core/Engine/Engine.hpp"
#include "Core/GUICore/GUI.hpp"
#include "Core/GUICore/GUIButton.hpp"
#include "Core/ScenesCore/SceneManager.hpp"

namespace Forradia {
  void AddMainMenuSceneGUIButtons(SharedPtr<GUI> mainMenuSceneGUI) {
    mainMenuSceneGUI->AddChildComponent(
        std::make_shared<GUIButton>(0.45f, 0.36f, 0.1f, 0.04f, "New game", [] {
          _<SceneManager>().GoToScene("WorldGenerationScene");
        }));

    mainMenuSceneGUI->AddChildComponent(std::make_shared<GUIButton>(
        0.45f, 0.44f, 0.1f, 0.04f, "Quit", [] { _<Engine>().Stop(); }));
  }
}