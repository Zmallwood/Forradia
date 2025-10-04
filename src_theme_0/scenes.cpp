/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "scenes.hpp"
#include "engine.hpp"
#include "game_props.hpp"
#include "gui.hpp"
#include "gui_spec.hpp"
#include "input.hpp"
#include "rend.hpp"
#include "update.hpp"
#include "world_grator.hpp"
#include "world_struct.hpp"
#include "world_view.hpp"

namespace forr {
  void intro_scene::init_derived() {
    start_text_comp_ = gui()->add_child_comp(std::make_shared<gui_label>(
        0.45f, 0.5f, 0.1f, 0.04f, "Press to start", true));
  }

  void intro_scene::on_enter_derived() {
    _<gui_chat_box>().print("Game started.");
  }

  void intro_scene::update_derived() {
    start_text_comp_->set_visible((ticks() % 800) < 400);

    _<cursor>().set_curs_style(curs_styles::hovering_clickable_gui);

    if (_<kb_inp>().any_key_pressed_pick_res() ||
        _<mouse_inp>().any_mouse_btn_pressed_pick_res())
      _<scene_mngr>().go_to_scene("main_menu_scene");
  }

  void intro_scene::render_derived() const {
    _<img_rend>().draw_img("default_scene_bg", 0.0f, 0.0f, 1.0f, 1.0f);
    _<img_rend>().draw_img_auto_h("forradia_logo", 0.25f, 0.2f, 0.5f);
  }

  void main_menu_scene::init_derived() {
    gui()->add_child_comp(std::make_shared<gui_panel>(0.4f, 0.32f, 0.2f, 0.2f));
    gui()->add_child_comp(
        std::make_shared<gui_button>(0.45f, 0.36f, 0.1f, 0.04f, "New game", [] {
          _<scene_mngr>().go_to_scene("world_gen_scene");
        }));

    gui()->add_child_comp(std::make_shared<gui_button>(
        0.45f, 0.44f, 0.1f, 0.04f, "Quit", [] { _<engine>().stop(); }));
    gui()->add_child_comp(__<gui_chat_box>());
  }

  void main_menu_scene::update_derived() {}

  void main_menu_scene::render_derived() const {
    _<img_rend>().draw_img("default_scene_bg", 0.0f, 0.0f, 1.0f, 1.0f);
    _<img_rend>().draw_img_auto_h("forradia_logo", 0.35f, 0.1f, 0.3f);
  }

  void world_gen_scene::on_enter_derived() {
    _<gui_chat_box>().print("Generating new world...");
    _<world_grator>().gen_new_world();
    _<gui_chat_box>().print("World generation completed.");
    _<scene_mngr>().go_to_scene("main_scene");
  }

  void main_scene::init_derived() {
    gui()->add_child_comp(std::make_shared<gui_player_status_box>());
    gui()->add_child_comp(__<gui_chat_box>());
    gui()->add_child_comp(std::make_shared<gui_button>(
        0.78f, 0.9f, 0.05f, conv_w_to_h(0.05f, _<sdl_device>().win()), "",
        [] { _<gui_player_body_win>().toggle_visible(); },
        "gui_button_player_body_bg", "gui_button_player_body_hovered_bg"));

    gui()->add_child_comp(std::make_shared<gui_button>(
        0.85f, 0.9f, 0.05f, conv_w_to_h(0.05f, _<sdl_device>().win()), "",
        [] { _<gui_inventory_win>().toggle_visible(); },
        "gui_button_inventory_bg", "gui_button_inventory_hovered_bg"));

    gui()->add_child_comp(std::make_shared<gui_button>(
        0.92f, 0.9f, 0.05f, conv_w_to_h(0.05f, _<sdl_device>().win()), "",
        [] { _<gui_sys_menu>().toggle_visible(); }, "gui_button_system_menu_bg",
        "gui_button_system_menu_hovered_bg"));
    gui()->add_child_comp(__<gui_sys_menu>());
    gui()->add_child_comp(__<gui_inventory_win>());
    gui()->add_child_comp(__<gui_player_body_win>());
    gui()->add_child_comp(std::make_shared<gui_fps_panel>());
    gui()->add_child_comp(__<gui_interact_menu>());
  }

  void main_scene::on_enter_derived() {
    _<gui_chat_box>().print("You have entered the world.");
  }

  void main_scene::update_derived() {
    update_kb_actions();
    update_mouse_actions();
    update_npcs();
    update_crea_movem();
    update_mouse_movem();
    update_kb_movem();
    _<tl_hovering>().update();
  }

  void main_scene::render_derived() const { _<world_view>().render(); }
}