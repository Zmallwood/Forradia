/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "add_main_menu_scene_gui_components.hpp"
#include "gui.hpp"
#include "sub/add_main_menu_scene_gui_buttons.hpp"

namespace forr {
  void add_main_menu_scene_gui_components(s_ptr<gui> main_menu_scene_gui) {
    main_menu_scene_gui->add_child_component(
        std::make_shared<gui_panel>(0.4f, 0.32f, 0.2f, 0.2f));
    add_main_menu_scene_gui_buttons(main_menu_scene_gui);
    main_menu_scene_gui->add_child_component(__<gui_text_console>());
  }
}