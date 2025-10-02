/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui_player_body_window.hpp"
#include "core/gui_core/gui_button.hpp"
#include "core/gui_core/gui_label.hpp"
#include "core/rend/text/text_renderer.hpp"
#include "theme_0/theme_0_mechanics/core_game_objects/player.hpp"

namespace forr {
  void gui_player_body_window::initialize() {
    auto image_width{0.07f};
    auto image_height{convert_width_to_height(image_width)};
    auto overall_body_image_button{std::make_shared<gui_button>(
        0.1f - image_width / 2, 0.04f, image_width, image_height, "",
        [this] {
          select_body_part(body_part_types::overall_body);
          update_body_part_information_labels();
        },
        "GUIImageOverallBody", "GUIImageOverallBodyHovered")};
    add_child_component(overall_body_image_button);
    auto right_arm_body_image_button{std::make_shared<gui_button>(
        0.1f - image_width / 2 - image_width, 0.04f, image_width, image_height,
        "",
        [this] {
          select_body_part(body_part_types::right_arm);
          update_body_part_information_labels();
        },
        "GUIImageRightArm", "GUIImageRightArmHovered")};
    add_child_component(right_arm_body_image_button);
    auto left_arm_body_image_button{std::make_shared<gui_button>(
        0.1f - image_width / 2 + image_width, 0.04f, image_width, image_height,
        "",
        [this] {
          select_body_part(body_part_types::left_arm);
          update_body_part_information_labels();
        },
        "GUIImageLeftArm", "GUIImageLeftArmHovered")};
    add_child_component(left_arm_body_image_button);
    auto legs_image_button{std::make_shared<gui_button>(
        0.1f - image_width / 2, 0.04f + image_height, image_width, image_height,
        "",
        [this] {
          select_body_part(body_part_types::legs);
          update_body_part_information_labels();
        },
        "GUIImageLegs", "GUIImageLegsHovered")};
    add_child_component(legs_image_button);
    m_label_body_part_name = std::make_shared<gui_label>(
        0.01f, 0.3f, 0.2f, 0.05f, "Body part: ", false, colors::yellow_transp);
    m_label_body_part_strength = std::make_shared<gui_label>(
        0.01f + 0.01f, 0.3f + 1 * 0.02f, 0.2f, 0.05f, "Strength: ");
    m_label_body_part_energy = std::make_shared<gui_label>(
        0.01f + 0.01f, 0.3f + 2 * 0.02f, 0.2f, 0.05f, "Energy: ");
    m_label_body_part_temperature = std::make_shared<gui_label>(
        0.01f + 0.01f, 0.3f + 3 * 0.02f, 0.2f, 0.05f, "Temperature: ");
    add_child_component(m_label_body_part_name);
    add_child_component(m_label_body_part_strength);
    add_child_component(m_label_body_part_energy);
    add_child_component(m_label_body_part_temperature);
  }

  void
  gui_player_body_window::select_body_part(body_part_types body_part_type) {
    m_selected_body_part = body_part_type;
  }

  void gui_player_body_window::update_body_part_information_labels() {
    auto &player_body{get_singleton<player>().get_player_body_ref()};
    switch (m_selected_body_part) {
    case body_part_types::overall_body: {
      m_label_body_part_name->set_text("Body part: Overall body");
      auto strength{
          player_body.get_body_part_ptr(body_part_types::overall_body)
              ->get_strength()};
      m_label_body_part_strength->set_text(
          fmt::format("Strength: {:.2f}", strength));
      auto max_energy{
          player_body.get_body_part_ptr(body_part_types::overall_body)
              ->get_max_energy()};
      auto current_energy{
          player_body.get_body_part_ptr(body_part_types::overall_body)
              ->get_current_energy()};
      m_label_body_part_energy->set_text(
          fmt::format("Energy: {:.2f} / {:.2f}", current_energy, max_energy));
      auto temperature{
          player_body.get_body_part_ptr(body_part_types::overall_body)
              ->get_temperature()};
      m_label_body_part_temperature->set_text(
          fmt::format("Temperature: {:.2f} C", temperature));
    } break;
    case body_part_types::right_arm: {
      m_label_body_part_name->set_text("Body part: Right arm");
      auto strength{player_body.get_body_part_ptr(body_part_types::right_arm)
                        ->get_strength()};
      m_label_body_part_strength->set_text(
          fmt::format("Strength: {:.2f}", strength));
      auto max_energy{player_body.get_body_part_ptr(body_part_types::right_arm)
                          ->get_max_energy()};
      auto current_energy{
          player_body.get_body_part_ptr(body_part_types::right_arm)
              ->get_current_energy()};
      m_label_body_part_energy->set_text(
          fmt::format("Energy: {:.2f} / {:.2f}", current_energy, max_energy));
      auto temperature{
          player_body.get_body_part_ptr(body_part_types::right_arm)
              ->get_temperature()};
      m_label_body_part_temperature->set_text(
          fmt::format("Temperature: {:.2f} C", temperature));
    } break;
    case body_part_types::left_arm: {
      m_label_body_part_name->set_text("Body part: Left arm");
      auto strength{player_body.get_body_part_ptr(body_part_types::left_arm)
                        ->get_strength()};
      m_label_body_part_strength->set_text(
          fmt::format("Strength: {:.2f}", strength));
      auto max_energy{player_body.get_body_part_ptr(body_part_types::left_arm)
                          ->get_max_energy()};
      auto current_energy{
          player_body.get_body_part_ptr(body_part_types::left_arm)
              ->get_current_energy()};
      m_label_body_part_energy->set_text(
          fmt::format("Energy: {:.2f} / {:.2f}", current_energy, max_energy));
      auto temperature{player_body.get_body_part_ptr(body_part_types::left_arm)
                           ->get_temperature()};
      m_label_body_part_temperature->set_text(
          fmt::format("Temperature: {:.2f} C", temperature));
    } break;
    case body_part_types::legs: {
      m_label_body_part_name->set_text("Body part: Legs");
      auto strength{
          player_body.get_body_part_ptr(body_part_types::legs)->get_strength()};
      m_label_body_part_strength->set_text(
          fmt::format("Strength: {:.2f}", strength));
      auto max_energy{player_body.get_body_part_ptr(body_part_types::legs)
                          ->get_max_energy()};
      auto current_energy{player_body.get_body_part_ptr(body_part_types::legs)
                              ->get_current_energy()};
      m_label_body_part_energy->set_text(
          fmt::format("Energy: {:.2f} / {:.2f}", current_energy, max_energy));
      auto temperature{player_body.get_body_part_ptr(body_part_types::legs)
                           ->get_temperature()};
      m_label_body_part_temperature->set_text(
          fmt::format("Temperature: {:.2f} C", temperature));
    } break;
    }
  }
}