/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "main_menu_scene.hpp"
#include "core/rend/images/image_renderer.hpp"
#include "sub/add_main_menu_scene_gui_components/add_main_menu_scene_gui_components.hpp"

namespace forr {
  void main_menu_scene::initialize_derived() {
    add_main_menu_scene_gui_components(get_gui());
  }

  void main_menu_scene::update_derived() {}

  void main_menu_scene::render_derived() const {
    get_ston<image_renderer>().draw_img("DefaultSceneBackground", 0.0f, 0.0f,
                                          1.0f, 1.0f);
    get_ston<image_renderer>().draw_img_auto_h("ForradiaLogo",
                                                           0.35f, 0.1f, 0.3f);
  }
}
