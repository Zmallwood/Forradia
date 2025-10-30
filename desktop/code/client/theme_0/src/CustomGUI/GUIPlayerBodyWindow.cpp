//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "GUIPlayerBodyWindow.hpp"

#include "SDLDevice.hpp"

#include "PlayerCharacter.hpp"

#include "GUIButton.hpp"

#include "GUILabel.hpp"

namespace Forradia::Theme0
{
    void GUIPlayerBodyWindow::Initialize()
    {
        auto imageWidth{0.07f};

        auto imageHeight{ConvertWidthToHeight(
            imageWidth, _<SDLDevice>().GetWindow())};

        auto overallBodyImageButton{
            std::make_shared<GUIButton>(
                0.1f - imageWidth / 2, 0.04f, imageWidth,
                imageHeight, "",
                [this]
                {
                    this->SelectBodyPart(CInt(
                        Theme0::GameplayCore::
                            BodyPartTypes::OverallBody));
                    this->UpdateBodyPartInfoLabels();
                },
                "GUIImageOverallBody",
                "GUIImageOverallBodyHovered")};

        this->AddChildComponent(overallBodyImageButton);

        auto rightArmBodyImageButton{
            std::make_shared<GUIButton>(
                0.1f - imageWidth / 2 - imageWidth, 0.04f,
                imageWidth, imageHeight, "",
                [this]
                {
                    this->SelectBodyPart(
                        CInt(Theme0::GameplayCore::
                                 BodyPartTypes::RightArm));
                    this->UpdateBodyPartInfoLabels();
                },
                "GUIImageRightArm",
                "GUIImageRightArmHovered")};

        this->AddChildComponent(rightArmBodyImageButton);

        auto leftArmBodyImageButton{
            std::make_shared<GUIButton>(
                0.1f - imageWidth / 2 + imageWidth, 0.04f,
                imageWidth, imageHeight, "",
                [this]
                {
                    this->SelectBodyPart(
                        CInt(Theme0::GameplayCore::
                                 BodyPartTypes::LeftArm));
                    this->UpdateBodyPartInfoLabels();
                },
                "GUIImageLeftArm",
                "GUIImageLeftArmHovered")};

        this->AddChildComponent(leftArmBodyImageButton);

        auto legsImageButton{std::make_shared<GUIButton>(
            0.1f - imageWidth / 2, 0.04f + imageHeight,
            imageWidth, imageHeight, "",
            [this]
            {
                this->SelectBodyPart(
                    CInt(Theme0::GameplayCore::
                             BodyPartTypes::Legs));
                this->UpdateBodyPartInfoLabels();
            },
            "GUIImageLegs", "GUIImageLegsHovered")};

        this->AddChildComponent(legsImageButton);

        m_labelBodyPartName = std::make_shared<GUILabel>(
            0.01f, 0.3f, 0.2f, 0.05f, "Body part: ", false,
            Palette::GetColor<Hash("YellowTransparent")>());

        m_labelBodyPartStrength =
            std::make_shared<GUILabel>(
                0.01f + 0.01f, 0.3f + 1 * 0.02f, 0.2f,
                0.05f, "Strength: ");

        m_labelBodyPartEnergy = std::make_shared<GUILabel>(
            0.01f + 0.01f, 0.3f + 2 * 0.02f, 0.2f, 0.05f,
            "Energy: ");

        m_labelBodyPartTemperature =
            std::make_shared<GUILabel>(
                0.01f + 0.01f, 0.3f + 3 * 0.02f, 0.2f,
                0.05f, "Temperature: ");

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
        auto &playerBody{
            _<Theme0::GameplayCore::PlayerCharacter>()
                .GetBodyRef()};

        constexpr auto overallBody{
            CInt(Theme0::GameplayCore::BodyPartTypes::
                     OverallBody)};

        constexpr auto rightArm{CInt(
            Theme0::GameplayCore::BodyPartTypes::RightArm)};

        constexpr auto leftArm{CInt(
            Theme0::GameplayCore::BodyPartTypes::LeftArm)};

        constexpr auto legs{CInt(
            Theme0::GameplayCore::BodyPartTypes::Legs)};

        switch (m_selectedBodyPart)
        {
        case overallBody:
        {
            m_labelBodyPartName->SetText(
                "Body part: Overall body");

            auto strength{
                playerBody
                    .GetBodyPartPtr(
                        Theme0::GameplayCore::
                            BodyPartTypes::OverallBody)
                    ->GetStrength()};

            m_labelBodyPartStrength->SetText(
                fmt::format("Strength: {:.2f}", strength));
            auto maxEnergy{
                playerBody
                    .GetBodyPartPtr(
                        Theme0::GameplayCore::
                            BodyPartTypes::OverallBody)
                    ->GetMaxEnergy()};

            auto currentEnergy{
                playerBody
                    .GetBodyPartPtr(
                        Theme0::GameplayCore::
                            BodyPartTypes::OverallBody)
                    ->GetCurrentEnergy()};

            m_labelBodyPartEnergy->SetText(
                fmt::format("Energy: {:.2f} / {:.2f}",
                            currentEnergy, maxEnergy));

            auto temperature{
                playerBody
                    .GetBodyPartPtr(
                        Theme0::GameplayCore::
                            BodyPartTypes::OverallBody)
                    ->GetTemperature()};

            m_labelBodyPartTemperature->SetText(fmt::format(
                "Temperature: {:.2f} C", temperature));
        }

        break;

        case rightArm:
        {
            m_labelBodyPartName->SetText(
                "Body part: Right arm");

            auto strength{
                playerBody
                    .GetBodyPartPtr(
                        Theme0::GameplayCore::
                            BodyPartTypes::RightArm)
                    ->GetStrength()};

            m_labelBodyPartStrength->SetText(
                fmt::format("Strength: {:.2f}", strength));

            auto maxEnergy{
                playerBody
                    .GetBodyPartPtr(
                        Theme0::GameplayCore::
                            BodyPartTypes::RightArm)
                    ->GetMaxEnergy()};

            auto currentEnergy{
                playerBody
                    .GetBodyPartPtr(
                        Theme0::GameplayCore::
                            BodyPartTypes::RightArm)
                    ->GetCurrentEnergy()};

            m_labelBodyPartEnergy->SetText(
                fmt::format("Energy: {:.2f} / {:.2f}",
                            currentEnergy, maxEnergy));

            auto temperature{
                playerBody
                    .GetBodyPartPtr(
                        Theme0::GameplayCore::
                            BodyPartTypes::RightArm)
                    ->GetTemperature()};

            m_labelBodyPartTemperature->SetText(fmt::format(
                "Temperature: {:.2f} C", temperature));
        }

        break;

        case leftArm:
        {
            m_labelBodyPartName->SetText(
                "Body part: Left arm");

            auto strength{
                playerBody
                    .GetBodyPartPtr(
                        Theme0::GameplayCore::
                            BodyPartTypes::LeftArm)
                    ->GetStrength()};

            m_labelBodyPartStrength->SetText(
                fmt::format("Strength: {:.2f}", strength));

            auto maxEnergy{
                playerBody
                    .GetBodyPartPtr(
                        Theme0::GameplayCore::
                            BodyPartTypes::LeftArm)
                    ->GetMaxEnergy()};

            auto currentEnergy{
                playerBody
                    .GetBodyPartPtr(
                        Theme0::GameplayCore::
                            BodyPartTypes::LeftArm)
                    ->GetCurrentEnergy()};

            m_labelBodyPartEnergy->SetText(
                fmt::format("Energy: {:.2f} / {:.2f}",
                            currentEnergy, maxEnergy));

            auto temperature{
                playerBody
                    .GetBodyPartPtr(
                        Theme0::GameplayCore::
                            BodyPartTypes::LeftArm)
                    ->GetTemperature()};

            m_labelBodyPartTemperature->SetText(fmt::format(
                "Temperature: {:.2f} C", temperature));
        }

        break;

        case legs:
        {
            m_labelBodyPartName->SetText("Body part: Legs");

            auto strength{
                playerBody
                    .GetBodyPartPtr(Theme0::GameplayCore::
                                        BodyPartTypes::Legs)
                    ->GetStrength()};

            m_labelBodyPartStrength->SetText(
                fmt::format("Strength: {:.2f}", strength));

            auto maxEnergy{
                playerBody
                    .GetBodyPartPtr(Theme0::GameplayCore::
                                        BodyPartTypes::Legs)
                    ->GetMaxEnergy()};

            auto currentEnergy{
                playerBody
                    .GetBodyPartPtr(Theme0::GameplayCore::
                                        BodyPartTypes::Legs)
                    ->GetCurrentEnergy()};

            m_labelBodyPartEnergy->SetText(
                fmt::format("Energy: {:.2f} / {:.2f}",
                            currentEnergy, maxEnergy));

            auto temperature{
                playerBody
                    .GetBodyPartPtr(Theme0::GameplayCore::
                                        BodyPartTypes::Legs)
                    ->GetTemperature()};

            m_labelBodyPartTemperature->SetText(fmt::format(
                "Temperature: {:.2f} C", temperature));
        }

        break;
        }
    }
}