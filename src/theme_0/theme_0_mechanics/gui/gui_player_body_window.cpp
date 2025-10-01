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
  void gui_player_body_window::Initialize() {
    auto imageWidth{0.07f};
    auto imageHeight{ConvertWidthToHeight(imageWidth)};
    auto overallBodyImageButton{std::make_shared<gui_button>(
        0.1f - imageWidth / 2, 0.04f, imageWidth, imageHeight, "",
        [this] {
          SelectBodyPart(body_part_types::OverallBody);
          UpdateBodyPartInformationLabels();
        },
        "GUIImageOverallBody", "GUIImageOverallBodyHovered")};
    AddChildComponent(overallBodyImageButton);
    auto rightArmBodyImageButton{std::make_shared<gui_button>(
        0.1f - imageWidth / 2 - imageWidth, 0.04f, imageWidth, imageHeight, "",
        [this] {
          SelectBodyPart(body_part_types::RightArm);
          UpdateBodyPartInformationLabels();
        },
        "GUIImageRightArm", "GUIImageRightArmHovered")};
    AddChildComponent(rightArmBodyImageButton);
    auto leftArmBodyImageButton{std::make_shared<gui_button>(
        0.1f - imageWidth / 2 + imageWidth, 0.04f, imageWidth, imageHeight, "",
        [this] {
          SelectBodyPart(body_part_types::LeftArm);
          UpdateBodyPartInformationLabels();
        },
        "GUIImageLeftArm", "GUIImageLeftArmHovered")};
    AddChildComponent(leftArmBodyImageButton);
    auto legsImageButton{std::make_shared<gui_button>(
        0.1f - imageWidth / 2, 0.04f + imageHeight, imageWidth, imageHeight, "",
        [this] {
          SelectBodyPart(body_part_types::Legs);
          UpdateBodyPartInformationLabels();
        },
        "GUIImageLegs", "GUIImageLegsHovered")};
    AddChildComponent(legsImageButton);
    m_labelBodyPartName = std::make_shared<gui_label>(
        0.01f, 0.3f, 0.2f, 0.05f, "Body part: ", false,
        colors::YellowTransparent);
    m_labelBodyPartStrength = std::make_shared<gui_label>(
        0.01f + 0.01f, 0.3f + 1 * 0.02f, 0.2f, 0.05f, "Strength: ");
    m_labelBodyPartEnergy = std::make_shared<gui_label>(
        0.01f + 0.01f, 0.3f + 2 * 0.02f, 0.2f, 0.05f, "Energy: ");
    m_labelBodyPartTemperature = std::make_shared<gui_label>(
        0.01f + 0.01f, 0.3f + 3 * 0.02f, 0.2f, 0.05f, "Temperature: ");
    AddChildComponent(m_labelBodyPartName);
    AddChildComponent(m_labelBodyPartStrength);
    AddChildComponent(m_labelBodyPartEnergy);
    AddChildComponent(m_labelBodyPartTemperature);
  }

  void gui_player_body_window::SelectBodyPart(body_part_types bodyPartType) {
    m_selectedBodyPart = bodyPartType;
  }

  void gui_player_body_window::UpdateBodyPartInformationLabels() {
    auto &playerBody{GetSingleton<player>().GetPlayerBodyRef()};
    switch (m_selectedBodyPart) {
    case body_part_types::OverallBody: {
      m_labelBodyPartName->SetText("Body part: Overall body");
      auto strength{playerBody.GetBodyPartPtr(body_part_types::OverallBody)
                        ->GetStrength()};
      m_labelBodyPartStrength->SetText(
          fmt::format("Strength: {:.2f}", strength));
      auto maxEnergy{playerBody.GetBodyPartPtr(body_part_types::OverallBody)
                         ->GetMaxEnergy()};
      auto currentEnergy{
          playerBody.GetBodyPartPtr(body_part_types::OverallBody)
              ->GetCurrentEnergy()};
      m_labelBodyPartEnergy->SetText(
          fmt::format("Energy: {:.2f} / {:.2f}", currentEnergy, maxEnergy));
      auto temperature{playerBody.GetBodyPartPtr(body_part_types::OverallBody)
                           ->GetTemperature()};
      m_labelBodyPartTemperature->SetText(
          fmt::format("Temperature: {:.2f} C", temperature));
    } break;
    case body_part_types::RightArm: {
      m_labelBodyPartName->SetText("Body part: Right arm");
      auto strength{
          playerBody.GetBodyPartPtr(body_part_types::RightArm)->GetStrength()};
      m_labelBodyPartStrength->SetText(
          fmt::format("Strength: {:.2f}", strength));
      auto maxEnergy{
          playerBody.GetBodyPartPtr(body_part_types::RightArm)->GetMaxEnergy()};
      auto currentEnergy{playerBody.GetBodyPartPtr(body_part_types::RightArm)
                             ->GetCurrentEnergy()};
      m_labelBodyPartEnergy->SetText(
          fmt::format("Energy: {:.2f} / {:.2f}", currentEnergy, maxEnergy));
      auto temperature{playerBody.GetBodyPartPtr(body_part_types::RightArm)
                           ->GetTemperature()};
      m_labelBodyPartTemperature->SetText(
          fmt::format("Temperature: {:.2f} C", temperature));
    } break;
    case body_part_types::LeftArm: {
      m_labelBodyPartName->SetText("Body part: Left arm");
      auto strength{
          playerBody.GetBodyPartPtr(body_part_types::LeftArm)->GetStrength()};
      m_labelBodyPartStrength->SetText(
          fmt::format("Strength: {:.2f}", strength));
      auto maxEnergy{
          playerBody.GetBodyPartPtr(body_part_types::LeftArm)->GetMaxEnergy()};
      auto currentEnergy{playerBody.GetBodyPartPtr(body_part_types::LeftArm)
                             ->GetCurrentEnergy()};
      m_labelBodyPartEnergy->SetText(
          fmt::format("Energy: {:.2f} / {:.2f}", currentEnergy, maxEnergy));
      auto temperature{playerBody.GetBodyPartPtr(body_part_types::LeftArm)
                           ->GetTemperature()};
      m_labelBodyPartTemperature->SetText(
          fmt::format("Temperature: {:.2f} C", temperature));
    } break;
    case body_part_types::Legs: {
      m_labelBodyPartName->SetText("Body part: Legs");
      auto strength{
          playerBody.GetBodyPartPtr(body_part_types::Legs)->GetStrength()};
      m_labelBodyPartStrength->SetText(
          fmt::format("Strength: {:.2f}", strength));
      auto maxEnergy{
          playerBody.GetBodyPartPtr(body_part_types::Legs)->GetMaxEnergy()};
      auto currentEnergy{
          playerBody.GetBodyPartPtr(body_part_types::Legs)->GetCurrentEnergy()};
      m_labelBodyPartEnergy->SetText(
          fmt::format("Energy: {:.2f} / {:.2f}", currentEnergy, maxEnergy));
      auto temperature{
          playerBody.GetBodyPartPtr(body_part_types::Legs)->GetTemperature()};
      m_labelBodyPartTemperature->SetText(
          fmt::format("Temperature: {:.2f} C", temperature));
    } break;
    }
  }
}