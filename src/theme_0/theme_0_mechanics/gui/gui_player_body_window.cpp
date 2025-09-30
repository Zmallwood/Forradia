/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "gui_player_body_window.hpp"
#include "core/gui_core/gui_button.hpp"
#include "core/gui_core/gui_label.hpp"
#include "core/rendering/text/text_renderer.hpp"
#include "theme_0/theme_0_mechanics/core_game_objects/player.hpp"

namespace Forradia {
  void GUIPlayerBodyWindow::Initialize() {
    auto imageWidth{0.07f};
    auto imageHeight{ConvertWidthToHeight(imageWidth)};
    auto overallBodyImageButton{std::make_shared<GUIButton>(
        0.1f - imageWidth / 2, 0.04f, imageWidth, imageHeight, "",
        [this] {
          SelectBodyPart(BodyPartTypes::OverallBody);
          UpdateBodyPartInformationLabels();
        },
        "GUIImageOverallBody", "GUIImageOverallBodyHovered")};
    AddChildComponent(overallBodyImageButton);
    auto rightArmBodyImageButton{std::make_shared<GUIButton>(
        0.1f - imageWidth / 2 - imageWidth, 0.04f, imageWidth, imageHeight, "",
        [this] {
          SelectBodyPart(BodyPartTypes::RightArm);
          UpdateBodyPartInformationLabels();
        },
        "GUIImageRightArm", "GUIImageRightArmHovered")};
    AddChildComponent(rightArmBodyImageButton);
    auto leftArmBodyImageButton{std::make_shared<GUIButton>(
        0.1f - imageWidth / 2 + imageWidth, 0.04f, imageWidth, imageHeight, "",
        [this] {
          SelectBodyPart(BodyPartTypes::LeftArm);
          UpdateBodyPartInformationLabels();
        },
        "GUIImageLeftArm", "GUIImageLeftArmHovered")};
    AddChildComponent(leftArmBodyImageButton);
    auto legsImageButton{std::make_shared<GUIButton>(
        0.1f - imageWidth / 2, 0.04f + imageHeight, imageWidth, imageHeight, "",
        [this] {
          SelectBodyPart(BodyPartTypes::Legs);
          UpdateBodyPartInformationLabels();
        },
        "GUIImageLegs", "GUIImageLegsHovered")};
    AddChildComponent(legsImageButton);
    m_labelBodyPartName = std::make_shared<GUILabel>(0.01f, 0.3f, 0.2f, 0.05f,
                                                     "Body part: ", false,
                                                     Colors::YellowTransparent);
    m_labelBodyPartStrength = std::make_shared<GUILabel>(
        0.01f + 0.01f, 0.3f + 1 * 0.02f, 0.2f, 0.05f, "Strength: ");
    m_labelBodyPartEnergy = std::make_shared<GUILabel>(
        0.01f + 0.01f, 0.3f + 2 * 0.02f, 0.2f, 0.05f, "Energy: ");
    m_labelBodyPartTemperature = std::make_shared<GUILabel>(
        0.01f + 0.01f, 0.3f + 3 * 0.02f, 0.2f, 0.05f, "Temperature: ");
    AddChildComponent(m_labelBodyPartName);
    AddChildComponent(m_labelBodyPartStrength);
    AddChildComponent(m_labelBodyPartEnergy);
    AddChildComponent(m_labelBodyPartTemperature);
  }

  void GUIPlayerBodyWindow::SelectBodyPart(BodyPartTypes bodyPartType) {
    m_selectedBodyPart = bodyPartType;
  }

  void GUIPlayerBodyWindow::UpdateBodyPartInformationLabels() {
    auto &playerBody{GetSingleton<Player>().GetPlayerBodyRef()};
    switch (m_selectedBodyPart) {
    case BodyPartTypes::OverallBody: {
      m_labelBodyPartName->SetText("Body part: Overall body");
      auto strength{
          playerBody.GetBodyPartPtr(BodyPartTypes::OverallBody)->GetStrength()};
      m_labelBodyPartStrength->SetText(
          fmt::format("Strength: {:.2f}", strength));
      auto maxEnergy{playerBody.GetBodyPartPtr(BodyPartTypes::OverallBody)
                         ->GetMaxEnergy()};
      auto currentEnergy{playerBody.GetBodyPartPtr(BodyPartTypes::OverallBody)
                             ->GetCurrentEnergy()};
      m_labelBodyPartEnergy->SetText(
          fmt::format("Energy: {:.2f} / {:.2f}", currentEnergy, maxEnergy));
      auto temperature{playerBody.GetBodyPartPtr(BodyPartTypes::OverallBody)
                           ->GetTemperature()};
      m_labelBodyPartTemperature->SetText(
          fmt::format("Temperature: {:.2f} C", temperature));
    } break;
    case BodyPartTypes::RightArm: {
      m_labelBodyPartName->SetText("Body part: Right arm");
      auto strength{
          playerBody.GetBodyPartPtr(BodyPartTypes::RightArm)->GetStrength()};
      m_labelBodyPartStrength->SetText(
          fmt::format("Strength: {:.2f}", strength));
      auto maxEnergy{
          playerBody.GetBodyPartPtr(BodyPartTypes::RightArm)->GetMaxEnergy()};
      auto currentEnergy{playerBody.GetBodyPartPtr(BodyPartTypes::RightArm)
                             ->GetCurrentEnergy()};
      m_labelBodyPartEnergy->SetText(
          fmt::format("Energy: {:.2f} / {:.2f}", currentEnergy, maxEnergy));
      auto temperature{
          playerBody.GetBodyPartPtr(BodyPartTypes::RightArm)->GetTemperature()};
      m_labelBodyPartTemperature->SetText(
          fmt::format("Temperature: {:.2f} C", temperature));
    } break;
    case BodyPartTypes::LeftArm: {
      m_labelBodyPartName->SetText("Body part: Left arm");
      auto strength{
          playerBody.GetBodyPartPtr(BodyPartTypes::LeftArm)->GetStrength()};
      m_labelBodyPartStrength->SetText(
          fmt::format("Strength: {:.2f}", strength));
      auto maxEnergy{
          playerBody.GetBodyPartPtr(BodyPartTypes::LeftArm)->GetMaxEnergy()};
      auto currentEnergy{playerBody.GetBodyPartPtr(BodyPartTypes::LeftArm)
                             ->GetCurrentEnergy()};
      m_labelBodyPartEnergy->SetText(
          fmt::format("Energy: {:.2f} / {:.2f}", currentEnergy, maxEnergy));
      auto temperature{
          playerBody.GetBodyPartPtr(BodyPartTypes::LeftArm)->GetTemperature()};
      m_labelBodyPartTemperature->SetText(
          fmt::format("Temperature: {:.2f} C", temperature));
    } break;
    case BodyPartTypes::Legs: {
      m_labelBodyPartName->SetText("Body part: Legs");
      auto strength{
          playerBody.GetBodyPartPtr(BodyPartTypes::Legs)->GetStrength()};
      m_labelBodyPartStrength->SetText(
          fmt::format("Strength: {:.2f}", strength));
      auto maxEnergy{
          playerBody.GetBodyPartPtr(BodyPartTypes::Legs)->GetMaxEnergy()};
      auto currentEnergy{
          playerBody.GetBodyPartPtr(BodyPartTypes::Legs)->GetCurrentEnergy()};
      m_labelBodyPartEnergy->SetText(
          fmt::format("Energy: {:.2f} / {:.2f}", currentEnergy, maxEnergy));
      auto temperature{
          playerBody.GetBodyPartPtr(BodyPartTypes::Legs)->GetTemperature()};
      m_labelBodyPartTemperature->SetText(
          fmt::format("Temperature: {:.2f} C", temperature));
    } break;
    }
  }
}