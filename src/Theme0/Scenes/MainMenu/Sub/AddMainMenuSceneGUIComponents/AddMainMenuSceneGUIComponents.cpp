/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "AddMainMenuSceneGUIComponents.hpp"
#include "Core/GUICore/GUI.hpp"
#include "Core/GUICore/GUIPanel.hpp"
#include "Core/GUICore/GUITextConsole.hpp"
#include "Sub/AddMainMenuSceneGUIButtons.hpp"

namespace Forradia {
  void AddMainMenuSceneGUIComponents(SharedPtr<GUI> mainMenuSceneGUI) {
    mainMenuSceneGUI->AddChildComponent(
        std::make_shared<GUIPanel>(0.4f, 0.32f, 0.2f, 0.2f));

    AddMainMenuSceneGUIButtons(mainMenuSceneGUI);

    mainMenuSceneGUI->AddChildComponent(__<GUITextConsole>());
  }
}