/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "add_main_menu_scene_gui_components.hpp"
#include "core/gui_core/gui.hpp"
#include "core/gui_core/gui_panel.hpp"
#include "core/gui_core/gui_text_console.hpp"
#include "sub/add_main_menu_scene_gui_buttons.hpp"

namespace Forradia {
  void AddMainMenuSceneGUIComponents(SharedPtr<GUI> mainMenuSceneGUI) {
    mainMenuSceneGUI->AddChildComponent(
        std::make_shared<GUIPanel>(0.4f, 0.32f, 0.2f, 0.2f));
    AddMainMenuSceneGUIButtons(mainMenuSceneGUI);
    mainMenuSceneGUI->AddChildComponent(GetSingletonPtr<GUITextConsole>());
  }
}