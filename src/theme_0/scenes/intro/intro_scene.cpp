/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "intro_scene.hpp"
#include "core/core.hpp"
#include "core/gui_core/gui.hpp"
#include "core/gui_core/gui_label.hpp"
#include "core/gui_core/gui_text_console.hpp"
#include "core/input/keyboard/keyboard_input.hpp"
#include "core/input/mouse/mouse_input.hpp"
#include "core/rend/images/image_renderer.hpp"
#include "core/scenes_core/scene_manager.hpp"

namespace forr {
  void intro_scene::initialize_derived() {
    m_start_text = get_gui()->add_child_component(std::make_shared<gui_label>(
        0.45f, 0.5f, 0.1f, 0.04f, "Press to start", true));
  }

  void intro_scene::on_enter_derived() {
    get_singleton<gui_text_console>().print("Game started.");
  }

  void intro_scene::update_derived() {
    m_start_text->set_visible((get_ticks() % 800) < 400);

    get_singleton<cursor>().set_cursor_style(
        cursor_styles::hovering_clickable_gui);

    if (get_singleton<keyboard_input>().any_key_is_pressed_pick_result() ||
        get_singleton<mouse_input>()
            .any_mouse_button_is_pressed_pick_result()) {
      get_singleton<scene_manager>().go_to_scene("MainMenuScene");
    }
  }

  void intro_scene::render_derived() const {
    get_singleton<image_renderer>().draw_image("DefaultSceneBackground", 0.0f,
                                               0.0f, 1.0f, 1.0f);
    get_singleton<image_renderer>().draw_image_with_auto_height(
        "ForradiaLogo", 0.25f, 0.2f, 0.5f);
  }
}
