/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "add_main_scene_gui_buttons.hpp"
#include "sub/add_main_scene_inventory_window_button.hpp"
#include "sub/add_main_scene_player_body_window_button.hpp"
#include "sub/add_main_scene_system_menu_button.hpp"

namespace Forradia {
  void AddMainSceneGUIButtons(SharedPtr<GUI> mainSceneGUI) {
    AddMainScenePlayerBodyWindowButton(mainSceneGUI);
    AddMainSceneInventoryWindowButton(mainSceneGUI);
    AddMainSceneSystemMenuButton(mainSceneGUI);
  }
}