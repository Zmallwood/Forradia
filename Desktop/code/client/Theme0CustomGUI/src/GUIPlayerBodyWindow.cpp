/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GUIPlayerBodyWindow.hpp"
#include "GUIButton.hpp"
#include "GUILabel.hpp"
#include "Player/Player.hpp"
#include "Player/PlayerBodyPart.hpp"
#include "SDLDevice.hpp"

namespace Forradia::Theme0 {
    auto GUIPlayerBodyWindow::Initialize() -> void {
        auto imageWidth{0.07f};
        auto imageHeight{ConvertWidthToHeight(imageWidth, _<SDLDevice>().GetWindow())};

        auto overallBodyImageButton{std::make_shared<GUIButton>(
            "GUIButtonOverallBody", 0.1f - imageWidth / 2, 0.04f, imageWidth, imageHeight, "",
            [this] {
                this->SelectBodyPart(static_cast<int>(Theme0::PlayerBodyPartTypes::OverallBody));
                this->UpdateBodyPartInfoLabels();
            },
            "GUIImageOverallBody", "GUIImageOverallBodyHovered")};

        this->AddChildComponent(overallBodyImageButton);

        auto rightArmBodyImageButton{std::make_shared<GUIButton>(
            "GUIButtonRightArm", 0.1f - imageWidth / 2 - imageWidth, 0.04f, imageWidth, imageHeight,
            "",
            [this] {
                this->SelectBodyPart(static_cast<int>(Theme0::PlayerBodyPartTypes::RightArm));
                this->UpdateBodyPartInfoLabels();
            },
            "GUIImageRightArm", "GUIImageRightArmHovered")};

        this->AddChildComponent(rightArmBodyImageButton);

        auto leftArmBodyImageButton{std::make_shared<GUIButton>(
            "GUIButtonLeftArm", 0.1f - imageWidth / 2 + imageWidth, 0.04f, imageWidth, imageHeight,
            "",
            [this] {
                this->SelectBodyPart(static_cast<int>(Theme0::PlayerBodyPartTypes::LeftArm));
                this->UpdateBodyPartInfoLabels();
            },
            "GUIImageLeftArm", "GUIImageLeftArmHovered")};

        this->AddChildComponent(leftArmBodyImageButton);

        auto legsImageButton{std::make_shared<GUIButton>(
            "GUIButtonLegs", 0.1f - imageWidth / 2, 0.04f + imageHeight, imageWidth, imageHeight,
            "",
            [this] {
                this->SelectBodyPart(static_cast<int>(Theme0::PlayerBodyPartTypes::Legs));
                this->UpdateBodyPartInfoLabels();
            },
            "GUIImageLegs", "GUIImageLegsHovered")};

        this->AddChildComponent(legsImageButton);

        m_labelBodyPartName = std::make_shared<GUILabel>(
            "GUILabelBodyPartName", 0.01f, 0.3f, 0.2f, 0.05f, "Body part: ", false,
            Palette::GetColor<Hash("YellowTransparent")>());
        m_labelBodyPartStrength = std::make_shared<GUILabel>(
            "GUILabelBodyPartStrength", 0.01f + 0.01f, 0.3f + 1 * 0.02f, 0.2f, 0.05f, "Strength: ");
        m_labelBodyPartEnergy = std::make_shared<GUILabel>(
            "GUILabelBodyPartEnergy", 0.01f + 0.01f, 0.3f + 2 * 0.02f, 0.2f, 0.05f, "Energy: ");
        m_labelBodyPartTemperature =
            std::make_shared<GUILabel>("GUILabelBodyPartTemperature", 0.01f + 0.01f,
                                       0.3f + 3 * 0.02f, 0.2f, 0.05f, "Temperature: ");

        this->AddChildComponent(m_labelBodyPartName);
        this->AddChildComponent(m_labelBodyPartStrength);
        this->AddChildComponent(m_labelBodyPartEnergy);
        this->AddChildComponent(m_labelBodyPartTemperature);
    }

    auto GUIPlayerBodyWindow::SelectBodyPart(int type) -> void {
        m_selectedBodyPart = type;
    }

    auto GUIPlayerBodyWindow::UpdateBodyPartInfoLabels() -> void {
        auto &playerBody{_<Theme0::Player>().GetBodyRef()};

        constexpr auto overallBody{static_cast<int>(Theme0::PlayerBodyPartTypes::OverallBody)};
        constexpr auto rightArm{static_cast<int>(Theme0::PlayerBodyPartTypes::RightArm)};
        constexpr auto leftArm{static_cast<int>(Theme0::PlayerBodyPartTypes::LeftArm)};
        constexpr auto legs{static_cast<int>(Theme0::PlayerBodyPartTypes::Legs)};

        switch (m_selectedBodyPart) {
        case overallBody: {
            m_labelBodyPartName->SetText("Body part: Overall body");

            auto strength{
                playerBody.GetBodyPartPtr(Theme0::PlayerBodyPartTypes::OverallBody)->GetStrength()};

            m_labelBodyPartStrength->SetText(fmt::format("Strength: {:.2f}", strength));
            auto maxEnergy{playerBody.GetBodyPartPtr(Theme0::PlayerBodyPartTypes::OverallBody)
                               ->GetMaxEnergy()};

            auto currentEnergy{playerBody.GetBodyPartPtr(Theme0::PlayerBodyPartTypes::OverallBody)
                                   ->GetCurrentEnergy()};

            m_labelBodyPartEnergy->SetText(
                fmt::format("Energy: {:.2f} / {:.2f}", currentEnergy, maxEnergy));

            auto temperature{playerBody.GetBodyPartPtr(Theme0::PlayerBodyPartTypes::OverallBody)
                                 ->GetTemperature()};

            m_labelBodyPartTemperature->SetText(fmt::format("Temperature: {:.2f} C", temperature));
        } break;
        case rightArm: {
            m_labelBodyPartName->SetText("Body part: Right arm");

            auto strength{
                playerBody.GetBodyPartPtr(Theme0::PlayerBodyPartTypes::RightArm)->GetStrength()};

            m_labelBodyPartStrength->SetText(fmt::format("Strength: {:.2f}", strength));

            auto maxEnergy{
                playerBody.GetBodyPartPtr(Theme0::PlayerBodyPartTypes::RightArm)->GetMaxEnergy()};

            auto currentEnergy{playerBody.GetBodyPartPtr(Theme0::PlayerBodyPartTypes::RightArm)
                                   ->GetCurrentEnergy()};

            m_labelBodyPartEnergy->SetText(
                fmt::format("Energy: {:.2f} / {:.2f}", currentEnergy, maxEnergy));

            auto temperature{
                playerBody.GetBodyPartPtr(Theme0::PlayerBodyPartTypes::RightArm)->GetTemperature()};

            m_labelBodyPartTemperature->SetText(fmt::format("Temperature: {:.2f} C", temperature));
        } break;
        case leftArm: {
            m_labelBodyPartName->SetText("Body part: Left arm");

            auto strength{
                playerBody.GetBodyPartPtr(Theme0::PlayerBodyPartTypes::LeftArm)->GetStrength()};

            m_labelBodyPartStrength->SetText(fmt::format("Strength: {:.2f}", strength));

            auto maxEnergy{
                playerBody.GetBodyPartPtr(Theme0::PlayerBodyPartTypes::LeftArm)->GetMaxEnergy()};

            auto currentEnergy{playerBody.GetBodyPartPtr(Theme0::PlayerBodyPartTypes::LeftArm)
                                   ->GetCurrentEnergy()};

            m_labelBodyPartEnergy->SetText(
                fmt::format("Energy: {:.2f} / {:.2f}", currentEnergy, maxEnergy));

            auto temperature{
                playerBody.GetBodyPartPtr(Theme0::PlayerBodyPartTypes::LeftArm)->GetTemperature()};

            m_labelBodyPartTemperature->SetText(fmt::format("Temperature: {:.2f} C", temperature));
        } break;
        case legs: {
            m_labelBodyPartName->SetText("Body part: Legs");

            auto strength{
                playerBody.GetBodyPartPtr(Theme0::PlayerBodyPartTypes::Legs)->GetStrength()};

            m_labelBodyPartStrength->SetText(fmt::format("Strength: {:.2f}", strength));

            auto maxEnergy{
                playerBody.GetBodyPartPtr(Theme0::PlayerBodyPartTypes::Legs)->GetMaxEnergy()};

            auto currentEnergy{
                playerBody.GetBodyPartPtr(Theme0::PlayerBodyPartTypes::Legs)->GetCurrentEnergy()};

            m_labelBodyPartEnergy->SetText(
                fmt::format("Energy: {:.2f} / {:.2f}", currentEnergy, maxEnergy));

            auto temperature{
                playerBody.GetBodyPartPtr(Theme0::PlayerBodyPartTypes::Legs)->GetTemperature()};

            m_labelBodyPartTemperature->SetText(fmt::format("Temperature: {:.2f} C", temperature));
        } break;
        }
    }
}
