/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "add_main_menu_scene_gui_buttons.hpp"
#include "core/core.hpp"
#include "core/gui_core/gui.hpp"
#include "core/gui_core/gui_button.hpp"
#include "core/scenes_core/scene_manager.hpp"

namespace forr {
  void add_main_menu_scene_gui_buttons(s_ptr<gui> main_menu_scene_gui) {
    main_menu_scene_gui->add_child_component(
        std::make_shared<gui_button>(0.45f, 0.36f, 0.1f, 0.04f, "New game", [] {
          get_singleton<scene_manager>().go_to_scene("WorldGenerationScene");
        }));

    main_menu_scene_gui->add_child_component(
        std::make_shared<gui_button>(0.45f, 0.44f, 0.1f, 0.04f, "Quit",
                                     [] { get_singleton<engine>().stop(); }));
  }
}