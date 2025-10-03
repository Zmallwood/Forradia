/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "main_menu_scene.hpp"
#include "core.hpp"
#include "gui.hpp"
#include "rend.hpp"
#include "scenes.hpp"

namespace forr {
  void main_menu_scene::init_derived() {
    get_gui()->add_child_component(
        std::make_shared<gui_panel>(0.4f, 0.32f, 0.2f, 0.2f));
    get_gui()->add_child_component(
        std::make_shared<gui_button>(0.45f, 0.36f, 0.1f, 0.04f, "New game", [] {
          _<scene_mngr>().go_to_scene("WorldGenScene");
        }));

    get_gui()->add_child_component(std::make_shared<gui_button>(
        0.45f, 0.44f, 0.1f, 0.04f, "Quit", [] { _<engine>().stop(); }));
    get_gui()->add_child_component(__<gui_text_console>());
  }

  void main_menu_scene::update_derived() {}

  void main_menu_scene::render_derived() const {
    _<image_renderer>().draw_img("DefaultSceneBackground", 0.0f, 0.0f, 1.0f,
                                 1.0f);
    _<image_renderer>().draw_img_auto_h("ForradiaLogo", 0.35f, 0.1f, 0.3f);
  }
}
