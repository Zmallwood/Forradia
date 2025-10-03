/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "intro_scene.hpp"
#include "core/core.hpp"
#include "core/gui.hpp"
#include "core/input.hpp"
#include "core/rend/images/image_renderer.hpp"

namespace forr {
  void intro_scene::init_derived() {
    m_start_text = get_gui()->add_child_component(std::make_shared<gui_label>(
        0.45f, 0.5f, 0.1f, 0.04f, "Press to start", true));
  }

  void intro_scene::on_enter_derived() {
    get_ston<gui_text_console>().print("Game started.");
  }

  void intro_scene::update_derived() {
    m_start_text->set_visible((get_ticks() % 800) < 400);

    get_ston<cursor>().set_curs_style(cursor_styles::hovering_clickable_gui);

    if (get_ston<keyboard_input>().any_key_pressed_pick_result() ||
        get_ston<mouse_input>().any_mouse_button_pressed_pick_result()) {
      get_ston<scene_manager>().go_to_scene("MainMenuScene");
    }
  }

  void intro_scene::render_derived() const {
    get_ston<image_renderer>().draw_img("DefaultSceneBackground", 0.0f, 0.0f,
                                        1.0f, 1.0f);
    get_ston<image_renderer>().draw_img_auto_h("ForradiaLogo", 0.25f, 0.2f,
                                               0.5f);
  }
}
