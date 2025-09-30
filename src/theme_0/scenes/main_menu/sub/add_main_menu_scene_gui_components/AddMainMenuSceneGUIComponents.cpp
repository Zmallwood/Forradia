/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "AddMainMenuSceneGUIComponents.hpp"
#include "core/gui_core/GUI.hpp"
#include "core/gui_core/GUIPanel.hpp"
#include "core/gui_core/GUITextConsole.hpp"
#include "sub/AddMainMenuSceneGUIButtons.hpp"

namespace Forradia {
  void AddMainMenuSceneGUIComponents(SharedPtr<GUI> mainMenuSceneGUI) {
    mainMenuSceneGUI->AddChildComponent(
        std::make_shared<GUIPanel>(0.4f, 0.32f, 0.2f, 0.2f));

    AddMainMenuSceneGUIButtons(mainMenuSceneGUI);

    mainMenuSceneGUI->AddChildComponent(GetSingletonPtr<GUITextConsole>());
  }
}