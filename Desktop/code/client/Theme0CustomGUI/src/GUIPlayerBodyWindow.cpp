//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#include "GUIPlayerBodyWindow.hpp"
#include "GUIButton.hpp"
#include "GUILabel.hpp"
#include "Player/PlayerBodyPart.hpp"
#include "Player/PlayerCharacter.hpp"
#include "SDLDevice.hpp"

namespace Forradia::Theme0
{
    void GUIPlayerBodyWindow::Initialize()
    {
        auto imageWidth{0.07f};

        auto imageHeight{ConvertWidthToHeight(imageWidth, _<SDLDevice>().GetWindow())};

        auto overallBodyImageButton{std::make_shared<GUIButton>(
            "GUIButtonOverallBody", 0.1f - imageWidth / 2, 0.04f, imageWidth, imageHeight, "",
            [this]
            {
                this->SelectBodyPart(CInt(Theme0::GameplayCore::PlayerBodyPartTypes::OverallBody));
                this->UpdateBodyPartInfoLabels();
            },
            "GUIImageOverallBody", "GUIImageOverallBodyHovered")};

        this->AddChildComponent(overallBodyImageButton);

        auto rightArmBodyImageButton{std::make_shared<GUIButton>(
            "GUIButtonRightArm", 0.1f - imageWidth / 2 - imageWidth, 0.04f, imageWidth, imageHeight,
            "",
            [this]
            {
                this->SelectBodyPart(CInt(Theme0::GameplayCore::PlayerBodyPartTypes::RightArm));
                this->UpdateBodyPartInfoLabels();
            },
            "GUIImageRightArm", "GUIImageRightArmHovered")};

        this->AddChildComponent(rightArmBodyImageButton);

        auto leftArmBodyImageButton{std::make_shared<GUIButton>(
            "GUIButtonLeftArm", 0.1f - imageWidth / 2 + imageWidth, 0.04f, imageWidth, imageHeight,
            "",
            [this]
            {
                this->SelectBodyPart(CInt(Theme0::GameplayCore::PlayerBodyPartTypes::LeftArm));
                this->UpdateBodyPartInfoLabels();
            },
            "GUIImageLeftArm", "GUIImageLeftArmHovered")};

        this->AddChildComponent(leftArmBodyImageButton);

        auto legsImageButton{std::make_shared<GUIButton>(
            "GUIButtonLegs", 0.1f - imageWidth / 2, 0.04f + imageHeight, imageWidth, imageHeight,
            "",
            [this]
            {
                this->SelectBodyPart(CInt(Theme0::GameplayCore::PlayerBodyPartTypes::Legs));
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

    void GUIPlayerBodyWindow::SelectBodyPart(int type)
    {
        m_selectedBodyPart = type;
    }

    void GUIPlayerBodyWindow::UpdateBodyPartInfoLabels()
    {
        auto &playerBody{_<Theme0::GameplayCore::PlayerCharacter>().GetBodyRef()};

        constexpr auto overallBody{CInt(Theme0::GameplayCore::PlayerBodyPartTypes::OverallBody)};

        constexpr auto rightArm{CInt(Theme0::GameplayCore::PlayerBodyPartTypes::RightArm)};

        constexpr auto leftArm{CInt(Theme0::GameplayCore::PlayerBodyPartTypes::LeftArm)};

        constexpr auto legs{CInt(Theme0::GameplayCore::PlayerBodyPartTypes::Legs)};

        switch (m_selectedBodyPart)
        {
        case overallBody:
        {
            m_labelBodyPartName->SetText("Body part: Overall body");

            auto strength{
                playerBody.GetBodyPartPtr(Theme0::GameplayCore::PlayerBodyPartTypes::OverallBody)
                    ->GetStrength()};

            m_labelBodyPartStrength->SetText(fmt::format("Strength: {:.2f}", strength));
            auto maxEnergy{
                playerBody.GetBodyPartPtr(Theme0::GameplayCore::PlayerBodyPartTypes::OverallBody)
                    ->GetMaxEnergy()};

            auto currentEnergy{
                playerBody.GetBodyPartPtr(Theme0::GameplayCore::PlayerBodyPartTypes::OverallBody)
                    ->GetCurrentEnergy()};

            m_labelBodyPartEnergy->SetText(
                fmt::format("Energy: {:.2f} / {:.2f}", currentEnergy, maxEnergy));

            auto temperature{
                playerBody.GetBodyPartPtr(Theme0::GameplayCore::PlayerBodyPartTypes::OverallBody)
                    ->GetTemperature()};

            m_labelBodyPartTemperature->SetText(fmt::format("Temperature: {:.2f} C", temperature));
        }

        break;

        case rightArm:
        {
            m_labelBodyPartName->SetText("Body part: Right arm");

            auto strength{
                playerBody.GetBodyPartPtr(Theme0::GameplayCore::PlayerBodyPartTypes::RightArm)
                    ->GetStrength()};

            m_labelBodyPartStrength->SetText(fmt::format("Strength: {:.2f}", strength));

            auto maxEnergy{
                playerBody.GetBodyPartPtr(Theme0::GameplayCore::PlayerBodyPartTypes::RightArm)
                    ->GetMaxEnergy()};

            auto currentEnergy{
                playerBody.GetBodyPartPtr(Theme0::GameplayCore::PlayerBodyPartTypes::RightArm)
                    ->GetCurrentEnergy()};

            m_labelBodyPartEnergy->SetText(
                fmt::format("Energy: {:.2f} / {:.2f}", currentEnergy, maxEnergy));

            auto temperature{
                playerBody.GetBodyPartPtr(Theme0::GameplayCore::PlayerBodyPartTypes::RightArm)
                    ->GetTemperature()};

            m_labelBodyPartTemperature->SetText(fmt::format("Temperature: {:.2f} C", temperature));
        }

        break;

        case leftArm:
        {
            m_labelBodyPartName->SetText("Body part: Left arm");

            auto strength{
                playerBody.GetBodyPartPtr(Theme0::GameplayCore::PlayerBodyPartTypes::LeftArm)
                    ->GetStrength()};

            m_labelBodyPartStrength->SetText(fmt::format("Strength: {:.2f}", strength));

            auto maxEnergy{
                playerBody.GetBodyPartPtr(Theme0::GameplayCore::PlayerBodyPartTypes::LeftArm)
                    ->GetMaxEnergy()};

            auto currentEnergy{
                playerBody.GetBodyPartPtr(Theme0::GameplayCore::PlayerBodyPartTypes::LeftArm)
                    ->GetCurrentEnergy()};

            m_labelBodyPartEnergy->SetText(
                fmt::format("Energy: {:.2f} / {:.2f}", currentEnergy, maxEnergy));

            auto temperature{
                playerBody.GetBodyPartPtr(Theme0::GameplayCore::PlayerBodyPartTypes::LeftArm)
                    ->GetTemperature()};

            m_labelBodyPartTemperature->SetText(fmt::format("Temperature: {:.2f} C", temperature));
        }

        break;

        case legs:
        {
            m_labelBodyPartName->SetText("Body part: Legs");

            auto strength{
                playerBody.GetBodyPartPtr(Theme0::GameplayCore::PlayerBodyPartTypes::Legs)
                    ->GetStrength()};

            m_labelBodyPartStrength->SetText(fmt::format("Strength: {:.2f}", strength));

            auto maxEnergy{
                playerBody.GetBodyPartPtr(Theme0::GameplayCore::PlayerBodyPartTypes::Legs)
                    ->GetMaxEnergy()};

            auto currentEnergy{
                playerBody.GetBodyPartPtr(Theme0::GameplayCore::PlayerBodyPartTypes::Legs)
                    ->GetCurrentEnergy()};

            m_labelBodyPartEnergy->SetText(
                fmt::format("Energy: {:.2f} / {:.2f}", currentEnergy, maxEnergy));

            auto temperature{
                playerBody.GetBodyPartPtr(Theme0::GameplayCore::PlayerBodyPartTypes::Legs)
                    ->GetTemperature()};

            m_labelBodyPartTemperature->SetText(fmt::format("Temperature: {:.2f} C", temperature));
        }

        break;
        }
    }
}