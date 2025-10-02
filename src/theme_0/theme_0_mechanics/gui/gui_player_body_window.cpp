/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui_player_body_window.hpp"
#include "core/gui_core/gui_button.hpp"
#include "core/gui_core/gui_label.hpp"
#include "core/rendering/text/text_renderer.hpp"
#include "theme_0/theme_0_mechanics/core_game_objects/player.hpp"

namespace forr {
  void gui_player_body_window::initialize() {
    auto imageWidth{0.07f};
    auto imageHeight{convert_width_to_height(imageWidth)};
    auto overallBodyImageButton{std::make_shared<gui_button>(
        0.1f - imageWidth / 2, 0.04f, imageWidth, imageHeight, "",
        [this] {
          select_body_part(body_part_types::OverallBody);
          update_body_part_information_labels();
        },
        "GUIImageOverallBody", "GUIImageOverallBodyHovered")};
    add_child_component(overallBodyImageButton);
    auto rightArmBodyImageButton{std::make_shared<gui_button>(
        0.1f - imageWidth / 2 - imageWidth, 0.04f, imageWidth, imageHeight, "",
        [this] {
          select_body_part(body_part_types::RightArm);
          update_body_part_information_labels();
        },
        "GUIImageRightArm", "GUIImageRightArmHovered")};
    add_child_component(rightArmBodyImageButton);
    auto leftArmBodyImageButton{std::make_shared<gui_button>(
        0.1f - imageWidth / 2 + imageWidth, 0.04f, imageWidth, imageHeight, "",
        [this] {
          select_body_part(body_part_types::LeftArm);
          update_body_part_information_labels();
        },
        "GUIImageLeftArm", "GUIImageLeftArmHovered")};
    add_child_component(leftArmBodyImageButton);
    auto legsImageButton{std::make_shared<gui_button>(
        0.1f - imageWidth / 2, 0.04f + imageHeight, imageWidth, imageHeight, "",
        [this] {
          select_body_part(body_part_types::Legs);
          update_body_part_information_labels();
        },
        "GUIImageLegs", "GUIImageLegsHovered")};
    add_child_component(legsImageButton);
    m_labelBodyPartName = std::make_shared<gui_label>(
        0.01f, 0.3f, 0.2f, 0.05f, "Body part: ", false,
        colors::yellow_transp);
    m_labelBodyPartStrength = std::make_shared<gui_label>(
        0.01f + 0.01f, 0.3f + 1 * 0.02f, 0.2f, 0.05f, "Strength: ");
    m_labelBodyPartEnergy = std::make_shared<gui_label>(
        0.01f + 0.01f, 0.3f + 2 * 0.02f, 0.2f, 0.05f, "Energy: ");
    m_labelBodyPartTemperature = std::make_shared<gui_label>(
        0.01f + 0.01f, 0.3f + 3 * 0.02f, 0.2f, 0.05f, "Temperature: ");
    add_child_component(m_labelBodyPartName);
    add_child_component(m_labelBodyPartStrength);
    add_child_component(m_labelBodyPartEnergy);
    add_child_component(m_labelBodyPartTemperature);
  }

  void gui_player_body_window::select_body_part(body_part_types bodyPartType) {
    m_selectedBodyPart = bodyPartType;
  }

  void gui_player_body_window::update_body_part_information_labels() {
    auto &playerBody{get_singleton<player>().get_player_body_ref()};
    switch (m_selectedBodyPart) {
    case body_part_types::OverallBody: {
      m_labelBodyPartName->set_text("Body part: Overall body");
      auto strength{playerBody.get_body_part_ptr(body_part_types::OverallBody)
                        ->get_strength()};
      m_labelBodyPartStrength->set_text(
          fmt::format("Strength: {:.2f}", strength));
      auto maxEnergy{playerBody.get_body_part_ptr(body_part_types::OverallBody)
                         ->get_max_energy()};
      auto currentEnergy{
          playerBody.get_body_part_ptr(body_part_types::OverallBody)
              ->get_current_energy()};
      m_labelBodyPartEnergy->set_text(
          fmt::format("Energy: {:.2f} / {:.2f}", currentEnergy, maxEnergy));
      auto temperature{
          playerBody.get_body_part_ptr(body_part_types::OverallBody)
              ->get_temperature()};
      m_labelBodyPartTemperature->set_text(
          fmt::format("Temperature: {:.2f} C", temperature));
    } break;
    case body_part_types::RightArm: {
      m_labelBodyPartName->set_text("Body part: Right arm");
      auto strength{playerBody.get_body_part_ptr(body_part_types::RightArm)
                        ->get_strength()};
      m_labelBodyPartStrength->set_text(
          fmt::format("Strength: {:.2f}", strength));
      auto maxEnergy{playerBody.get_body_part_ptr(body_part_types::RightArm)
                         ->get_max_energy()};
      auto currentEnergy{
          playerBody.get_body_part_ptr(body_part_types::RightArm)
              ->get_current_energy()};
      m_labelBodyPartEnergy->set_text(
          fmt::format("Energy: {:.2f} / {:.2f}", currentEnergy, maxEnergy));
      auto temperature{playerBody.get_body_part_ptr(body_part_types::RightArm)
                           ->get_temperature()};
      m_labelBodyPartTemperature->set_text(
          fmt::format("Temperature: {:.2f} C", temperature));
    } break;
    case body_part_types::LeftArm: {
      m_labelBodyPartName->set_text("Body part: Left arm");
      auto strength{playerBody.get_body_part_ptr(body_part_types::LeftArm)
                        ->get_strength()};
      m_labelBodyPartStrength->set_text(
          fmt::format("Strength: {:.2f}", strength));
      auto maxEnergy{playerBody.get_body_part_ptr(body_part_types::LeftArm)
                         ->get_max_energy()};
      auto currentEnergy{playerBody.get_body_part_ptr(body_part_types::LeftArm)
                             ->get_current_energy()};
      m_labelBodyPartEnergy->set_text(
          fmt::format("Energy: {:.2f} / {:.2f}", currentEnergy, maxEnergy));
      auto temperature{playerBody.get_body_part_ptr(body_part_types::LeftArm)
                           ->get_temperature()};
      m_labelBodyPartTemperature->set_text(
          fmt::format("Temperature: {:.2f} C", temperature));
    } break;
    case body_part_types::Legs: {
      m_labelBodyPartName->set_text("Body part: Legs");
      auto strength{
          playerBody.get_body_part_ptr(body_part_types::Legs)->get_strength()};
      m_labelBodyPartStrength->set_text(
          fmt::format("Strength: {:.2f}", strength));
      auto maxEnergy{playerBody.get_body_part_ptr(body_part_types::Legs)
                         ->get_max_energy()};
      auto currentEnergy{playerBody.get_body_part_ptr(body_part_types::Legs)
                             ->get_current_energy()};
      m_labelBodyPartEnergy->set_text(
          fmt::format("Energy: {:.2f} / {:.2f}", currentEnergy, maxEnergy));
      auto temperature{playerBody.get_body_part_ptr(body_part_types::Legs)
                           ->get_temperature()};
      m_labelBodyPartTemperature->set_text(
          fmt::format("Temperature: {:.2f} C", temperature));
    } break;
    }
  }
}