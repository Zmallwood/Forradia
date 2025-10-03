/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui_spec.hpp"
#include "engine.hpp"
#include "input.hpp"
#include "rend.hpp"

namespace forr {
  void gui_player_status_panel::render_derived() const {
    gui_panel::render_derived();
    auto b{bounds()};
    _<text_renderer>().draw_str(_<player>().name(), b.x + 0.01f,
                                b.y + 0.01f, font_sizes::_26);
  }

  void gui_system_menu::init() { set_visible(false); }

  void gui_system_menu::update_derived() {
    gui_component::update_derived();
    _<mouse_input>().left_btn_ref().reset();
  }

  void gui_system_menu::render_derived() const {
    gui_component::render_derived();
    auto c_sz{canv_sz(_<sdl_device>().win())};
    auto rect{SDL_Rect{0, 0, c_sz.w, c_sz.h}};
    SDL_SetRenderDrawBlendMode(_<sdl_device>().rend().get(),
                               SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(_<sdl_device>().rend().get(), 200, 0, 255, 50);
    SDL_RenderFillRect(_<sdl_device>().rend().get(), &rect);
  }

  void gui_inventory_window::render_derived() const {
    gui_window::render_derived();
  }

  void gui_player_body_window::init() {
    auto img_w{0.07f};
    auto img_h{conv_w_to_h(img_w, _<sdl_device>().win())};
    auto overall_body_img_btn{std::make_shared<gui_button>(
        0.1f - img_w / 2, 0.04f, img_w, img_h, "",
        [this] {
          sel_body_part(body_part_types::overall_body);
          update_body_part_info_lbls();
        },
        "GUIImageOverallBody", "GUIImageOverallBodyHovered")};
    add_child_component(overall_body_img_btn);
    auto right_arm_body_img_btn{std::make_shared<gui_button>(
        0.1f - img_w / 2 - img_w, 0.04f, img_w, img_h, "",
        [this] {
          sel_body_part(body_part_types::right_arm);
          update_body_part_info_lbls();
        },
        "GUIImageRightArm", "GUIImageRightArmHovered")};
    add_child_component(right_arm_body_img_btn);
    auto left_arm_body_img_btn{std::make_shared<gui_button>(
        0.1f - img_w / 2 + img_w, 0.04f, img_w, img_h, "",
        [this] {
          sel_body_part(body_part_types::left_arm);
          update_body_part_info_lbls();
        },
        "GUIImageLeftArm", "GUIImageLeftArmHovered")};
    add_child_component(left_arm_body_img_btn);
    auto legs_img_btn{std::make_shared<gui_button>(
        0.1f - img_w / 2, 0.04f + img_h, img_w, img_h, "",
        [this] {
          sel_body_part(body_part_types::legs);
          update_body_part_info_lbls();
        },
        "GUIImageLegs", "GUIImageLegsHovered")};
    add_child_component(legs_img_btn);
    lbl_body_part_name_ = std::make_shared<gui_label>(
        0.01f, 0.3f, 0.2f, 0.05f, "Body part: ", false, colors::yellow_transp);
    lbl_body_part_str_ = std::make_shared<gui_label>(
        0.01f + 0.01f, 0.3f + 1 * 0.02f, 0.2f, 0.05f, "Strength: ");
    lbl_body_part_energy_ = std::make_shared<gui_label>(
        0.01f + 0.01f, 0.3f + 2 * 0.02f, 0.2f, 0.05f, "Energy: ");
    lbl_body_part_temp_ = std::make_shared<gui_label>(
        0.01f + 0.01f, 0.3f + 3 * 0.02f, 0.2f, 0.05f, "Temperature: ");
    add_child_component(lbl_body_part_name_);
    add_child_component(lbl_body_part_str_);
    add_child_component(lbl_body_part_energy_);
    add_child_component(lbl_body_part_temp_);
  }

  void gui_player_body_window::sel_body_part(body_part_types type) {
    sel_body_part_ = type;
  }

  void gui_player_body_window::update_body_part_info_lbls() {
    auto &p_body{_<player>().body_ref()};
    switch (sel_body_part_) {
    case body_part_types::overall_body: {
      lbl_body_part_name_->set_text("Body part: Overall body");
      auto str{
          p_body.body_part_ptr(body_part_types::overall_body)->str()};
      lbl_body_part_str_->set_text(fmt::format("Strength: {:.2f}", str));
      auto max_energy{p_body.body_part_ptr(body_part_types::overall_body)
                          ->max_energy()};
      auto curr_energy{p_body.body_part_ptr(body_part_types::overall_body)
                           ->curr_energy()};
      lbl_body_part_energy_->set_text(
          fmt::format("Energy: {:.2f} / {:.2f}", curr_energy, max_energy));
      auto temp{
          p_body.body_part_ptr(body_part_types::overall_body)->temp()};
      lbl_body_part_temp_->set_text(fmt::format("Temperature: {:.2f} C", temp));
    } break;
    case body_part_types::right_arm: {
      lbl_body_part_name_->set_text("Body part: Right arm");
      auto str{p_body.body_part_ptr(body_part_types::right_arm)->str()};
      lbl_body_part_str_->set_text(fmt::format("Strength: {:.2f}", str));
      auto max_energy{p_body.body_part_ptr(body_part_types::right_arm)
                          ->max_energy()};
      auto curr_energy{p_body.body_part_ptr(body_part_types::right_arm)
                           ->curr_energy()};
      lbl_body_part_energy_->set_text(
          fmt::format("Energy: {:.2f} / {:.2f}", curr_energy, max_energy));
      auto temp{
          p_body.body_part_ptr(body_part_types::right_arm)->temp()};
      lbl_body_part_temp_->set_text(fmt::format("Temperature: {:.2f} C", temp));
    } break;
    case body_part_types::left_arm: {
      lbl_body_part_name_->set_text("Body part: Left arm");
      auto str{p_body.body_part_ptr(body_part_types::left_arm)->str()};
      lbl_body_part_str_->set_text(fmt::format("Strength: {:.2f}", str));
      auto max_energy{p_body.body_part_ptr(body_part_types::left_arm)
                          ->max_energy()};
      auto curr_energy{p_body.body_part_ptr(body_part_types::left_arm)
                           ->curr_energy()};
      lbl_body_part_energy_->set_text(
          fmt::format("Energy: {:.2f} / {:.2f}", curr_energy, max_energy));
      auto temp{
          p_body.body_part_ptr(body_part_types::left_arm)->temp()};
      lbl_body_part_temp_->set_text(fmt::format("Temperature: {:.2f} C", temp));
    } break;
    case body_part_types::legs: {
      lbl_body_part_name_->set_text("Body part: Legs");
      auto str{p_body.body_part_ptr(body_part_types::legs)->str()};
      lbl_body_part_str_->set_text(fmt::format("Strength: {:.2f}", str));
      auto max_energy{
          p_body.body_part_ptr(body_part_types::legs)->max_energy()};
      auto curr_energy{
          p_body.body_part_ptr(body_part_types::legs)->curr_energy()};
      lbl_body_part_energy_->set_text(
          fmt::format("Energy: {:.2f} / {:.2f}", curr_energy, max_energy));
      auto temp{p_body.body_part_ptr(body_part_types::legs)->temp()};
      lbl_body_part_temp_->set_text(fmt::format("Temperature: {:.2f} C", temp));
    } break;
    }
  }
}