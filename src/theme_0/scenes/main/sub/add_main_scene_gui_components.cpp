/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "add_main_scene_gui_components.hpp"
#include "core/gui_core/gui.hpp"
#include "core/gui_core/gui_fps_panel.hpp"
#include "core/gui_core/gui_text_console.hpp"
#include "core/gui_core/windows/gui_window.hpp"
#include "sub/add_main_scene_gui_buttons.hpp"
#include "theme_0/theme_0_mechanics/gui/gui_inventory_window.hpp"
#include "theme_0/theme_0_mechanics/gui/gui_player_body_window.hpp"
#include "theme_0/theme_0_mechanics/gui/gui_player_status_panel.hpp"
#include "theme_0/theme_0_mechanics/gui/gui_system_menu.hpp"

namespace forr {
  void AddMainSceneGUIComponents(std::shared_ptr<gui> mainSceneGUI) {
    mainSceneGUI->AddChildComponent(
        std::make_shared<gui_player_status_panel>());
    mainSceneGUI->AddChildComponent(GetSingletonPtr<gui_text_console>());
    AddMainSceneGUIButtons(mainSceneGUI);
    mainSceneGUI->AddChildComponent(GetSingletonPtr<gui_system_menu>());
    mainSceneGUI->AddChildComponent(GetSingletonPtr<gui_inventory_window>());
    mainSceneGUI->AddChildComponent(GetSingletonPtr<gui_player_body_window>());
    mainSceneGUI->AddChildComponent(std::make_shared<gui_fps_panel>());
  }
}