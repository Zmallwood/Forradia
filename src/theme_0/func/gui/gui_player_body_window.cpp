/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui_player_body_window.hpp"
#include "core.hpp"
#include "gui.hpp"
#include "theme_0/func/player.hpp"

namespace forr {
  void gui_player_body_window::init() {
    auto img_w{0.07f};
    auto img_h{conv_w_to_h(img_w, _<sdl_device>().get_win())};
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
    m_lbl_body_part_name = std::make_shared<gui_label>(
        0.01f, 0.3f, 0.2f, 0.05f, "Body part: ", false, colors::yellow_transp);
    m_lbl_body_part_str = std::make_shared<gui_label>(
        0.01f + 0.01f, 0.3f + 1 * 0.02f, 0.2f, 0.05f, "Strength: ");
    m_lbl_body_part_energy = std::make_shared<gui_label>(
        0.01f + 0.01f, 0.3f + 2 * 0.02f, 0.2f, 0.05f, "Energy: ");
    m_lbl_body_part_temp = std::make_shared<gui_label>(
        0.01f + 0.01f, 0.3f + 3 * 0.02f, 0.2f, 0.05f, "Temperature: ");
    add_child_component(m_lbl_body_part_name);
    add_child_component(m_lbl_body_part_str);
    add_child_component(m_lbl_body_part_energy);
    add_child_component(m_lbl_body_part_temp);
  }

  void gui_player_body_window::sel_body_part(body_part_types type) {
    m_sel_body_part = type;
  }

  void gui_player_body_window::update_body_part_info_lbls() {
    auto &p_body{_<player>().get_body_ref()};
    switch (m_sel_body_part) {
    case body_part_types::overall_body: {
      m_lbl_body_part_name->set_text("Body part: Overall body");
      auto str{
          p_body.get_body_part_ptr(body_part_types::overall_body)->get_str()};
      m_lbl_body_part_str->set_text(fmt::format("Strength: {:.2f}", str));
      auto max_energy{p_body.get_body_part_ptr(body_part_types::overall_body)
                          ->get_max_energy()};
      auto curr_energy{p_body.get_body_part_ptr(body_part_types::overall_body)
                           ->get_curr_energy()};
      m_lbl_body_part_energy->set_text(
          fmt::format("Energy: {:.2f} / {:.2f}", curr_energy, max_energy));
      auto temp{
          p_body.get_body_part_ptr(body_part_types::overall_body)->get_temp()};
      m_lbl_body_part_temp->set_text(
          fmt::format("Temperature: {:.2f} C", temp));
    } break;
    case body_part_types::right_arm: {
      m_lbl_body_part_name->set_text("Body part: Right arm");
      auto str{p_body.get_body_part_ptr(body_part_types::right_arm)->get_str()};
      m_lbl_body_part_str->set_text(fmt::format("Strength: {:.2f}", str));
      auto max_energy{p_body.get_body_part_ptr(body_part_types::right_arm)
                          ->get_max_energy()};
      auto curr_energy{p_body.get_body_part_ptr(body_part_types::right_arm)
                           ->get_curr_energy()};
      m_lbl_body_part_energy->set_text(
          fmt::format("Energy: {:.2f} / {:.2f}", curr_energy, max_energy));
      auto temp{
          p_body.get_body_part_ptr(body_part_types::right_arm)->get_temp()};
      m_lbl_body_part_temp->set_text(
          fmt::format("Temperature: {:.2f} C", temp));
    } break;
    case body_part_types::left_arm: {
      m_lbl_body_part_name->set_text("Body part: Left arm");
      auto str{p_body.get_body_part_ptr(body_part_types::left_arm)->get_str()};
      m_lbl_body_part_str->set_text(fmt::format("Strength: {:.2f}", str));
      auto max_energy{p_body.get_body_part_ptr(body_part_types::left_arm)
                          ->get_max_energy()};
      auto curr_energy{p_body.get_body_part_ptr(body_part_types::left_arm)
                           ->get_curr_energy()};
      m_lbl_body_part_energy->set_text(
          fmt::format("Energy: {:.2f} / {:.2f}", curr_energy, max_energy));
      auto temp{
          p_body.get_body_part_ptr(body_part_types::left_arm)->get_temp()};
      m_lbl_body_part_temp->set_text(
          fmt::format("Temperature: {:.2f} C", temp));
    } break;
    case body_part_types::legs: {
      m_lbl_body_part_name->set_text("Body part: Legs");
      auto str{p_body.get_body_part_ptr(body_part_types::legs)->get_str()};
      m_lbl_body_part_str->set_text(fmt::format("Strength: {:.2f}", str));
      auto max_energy{
          p_body.get_body_part_ptr(body_part_types::legs)->get_max_energy()};
      auto curr_energy{
          p_body.get_body_part_ptr(body_part_types::legs)->get_curr_energy()};
      m_lbl_body_part_energy->set_text(
          fmt::format("Energy: {:.2f} / {:.2f}", curr_energy, max_energy));
      auto temp{p_body.get_body_part_ptr(body_part_types::legs)->get_temp()};
      m_lbl_body_part_temp->set_text(
          fmt::format("Temperature: {:.2f} C", temp));
    } break;
    }
  }
}