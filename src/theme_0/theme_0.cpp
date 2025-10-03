/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "theme_0.hpp"
#include "core.hpp"
#include "func/world_gen/gen_new_world.hpp"
#include "gui.hpp"
#include "input.hpp"
#include "rend.hpp"
#include "theme_0/func/game_props.hpp"
#include "theme_0/func/gui/gui_inventory_window.hpp"
#include "theme_0/func/gui/gui_player_body_window.hpp"
#include "theme_0/func/gui/gui_player_status_panel.hpp"
#include "theme_0/func/gui/gui_system_menu.hpp"
#include "theme_0/func/update.hpp"
#include "theme_0/func/world_struct.hpp"
#include "theme_0/func/world_view.hpp"

namespace forr {
  void run_new_theme_0() {
    _<scene_mngr>().add_scene("IntroScene", _<intro_scene>());
    _<scene_mngr>().add_scene("MainMenuScene", _<main_menu_scene>());
    _<scene_mngr>().add_scene("WorldGenScene", _<world_gen_scene>());
    _<scene_mngr>().add_scene("MainScene", _<main_scene>());
    _<scene_mngr>().go_to_scene("IntroScene");
    _<world>().init(_<game_props>().k_w_area_sz,
                    _<game_props>().k_world_scaling);
    _<game>().start();
  }

  void intro_scene::init_derived() {
    m_start_text = get_gui()->add_child_component(std::make_shared<gui_label>(
        0.45f, 0.5f, 0.1f, 0.04f, "Press to start", true));
  }

  void intro_scene::on_enter_derived() {
    _<gui_text_console>().print("Game started.");
  }

  void intro_scene::update_derived() {
    m_start_text->set_visible((get_ticks() % 800) < 400);

    _<cursor>().set_curs_style(cursor_styles::hovering_clickable_gui);

    if (_<kb_input>().any_key_pressed_pick_result() ||
        _<mouse_input>().any_mouse_button_pressed_pick_result()) {
      _<scene_mngr>().go_to_scene("MainMenuScene");
    }
  }

  void intro_scene::render_derived() const {
    _<image_renderer>().draw_img("DefaultSceneBackground", 0.0f, 0.0f, 1.0f,
                                 1.0f);
    _<image_renderer>().draw_img_auto_h("ForradiaLogo", 0.25f, 0.2f, 0.5f);
  }

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

  void world_gen_scene::on_enter_derived() {
    _<gui_text_console>().print("Generating new world...");
    gen_new_world();
    _<gui_text_console>().print("World generation completed.");
    _<scene_mngr>().go_to_scene("MainScene");
  }

  void main_scene::init_derived() {
    get_gui()->add_child_component(std::make_shared<gui_player_status_panel>());
    get_gui()->add_child_component(__<gui_text_console>());
    get_gui()->add_child_component(std::make_shared<gui_button>(
        0.78f, 0.9f, 0.05f, conv_w_to_h(0.05f, _<sdl_device>().get_win()), "",
        [] { _<gui_player_body_window>().toggle_visibility(); },
        "GUIButtonPlayerBodyBackground",
        "GUIButtonPlayerBodyHoveredBackground"));

    get_gui()->add_child_component(std::make_shared<gui_button>(
        0.85f, 0.9f, 0.05f, conv_w_to_h(0.05f, _<sdl_device>().get_win()), "",
        [] { _<gui_inventory_window>().toggle_visibility(); },
        "GUIButtonInventoryBackground", "GUIButtonInventoryHoveredBackground"));

    get_gui()->add_child_component(std::make_shared<gui_button>(
        0.92f, 0.9f, 0.05f, conv_w_to_h(0.05f, _<sdl_device>().get_win()), "",
        [] { _<gui_system_menu>().toggle_visibility(); },
        "GUIButtonSystemBackground", "GUIButtonSystemHoveredBackground"));
    get_gui()->add_child_component(__<gui_system_menu>());
    get_gui()->add_child_component(__<gui_inventory_window>());
    get_gui()->add_child_component(__<gui_player_body_window>());
    get_gui()->add_child_component(std::make_shared<gui_fps_panel>());
  }

  void main_scene::on_enter_derived() {
    _<gui_text_console>().print("You have entered the world.");
  }

  void main_scene::update_derived() {
    update_npcs();
    update_crea_movem();
    update_mouse_movem();
    update_kb_movem();
    _<tile_hovering>().update();
    update_kb_actions();
  }

  void main_scene::render_derived() const { _<world_view>().render(); }
}