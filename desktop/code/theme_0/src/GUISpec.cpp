/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "GUISpec.hpp"
#include "Core.hpp"
#include "Render.hpp"
#include "Theme0Essentials.hpp"
#include "Update.hpp"
#include "WorldStruct.hpp"

namespace Forradia
{
#define _HIDE_FROM_OUTLINER_GUI_SPEC_TOP_                                      \
    namespace Theme0                                                           \
    {
_HIDE_FROM_OUTLINER_GUI_SPEC_TOP_
namespace SpecializedGUI
{
    void GUIPlayerStatusBox::RenderDerived() const
    {
        GUIPanel::RenderDerived();

        auto bounds{GetBounds()};

        _<Engine::Renderers::TextRenderer>().DrawString(
            _<Theme0::GameplayCore::Player::PlayerCharacter>().GetName(),
            bounds.x + 0.01f, bounds.y + 0.01f,
            Engine::Renderers::FontSizes::_26);
    }

    void GUISystemMenu::Initialize()
    {
        SetVisible(false);
    }

    void GUISystemMenu::UpdateDerived()
    {
        GUIComponent::UpdateDerived();

        _<Core::Engine::Input::MouseInput::LeftMouseButton>().Reset();
    }

    void GUISystemMenu::RenderDerived() const
    {
        GUIComponent::RenderDerived();

        // auto c_sz{GetCanvasSize(_<Engine::SDLDevice>().GetWindow())};

        // auto rect{SDL_Rect{0, 0, c_sz.w, c_sz.h}};

        // SDL_SetRenderDrawBlendMode(_<Engine::SDLDevice>().rend().get(),
        //                            SDL_BLENDMODE_BLEND);

        // SDL_SetRenderDrawColor(_<Engine::SDLDevice>().rend().get(), 200,
        // 0,
        //                        255, 50);

        // SDL_RenderFillRect(_<Engine::SDLDevice>().rend().get(), &rect);
    }

    void GUIInventoryWindow::RenderDerived() const
    {
        GUIWindow::RenderDerived();

        auto bounds{GetBounds()};

        auto marginX{k_margin};

        auto marginY{
            ConvertWidthToHeight(k_margin, _<Engine::SDLDevice>().GetWindow())};

        auto xStart{bounds.x + marginX};

        auto yStart{bounds.y + marginY +
                    GetGUIWindowTitleBar()->GetBounds().height};

        auto slotWidth{k_slotSize};

        auto slotHeight{ConvertWidthToHeight(
            k_slotSize, _<Engine::SDLDevice>().GetWindow())};

        auto numColumns{CInt((bounds.width - 2 * marginX) / slotWidth)};

        auto numRows{CInt((bounds.height - 2 * marginY - (yStart - bounds.y)) /
                          slotHeight)};

        for (auto y = 0; y < numRows; y++)
        {
            for (auto x = 0; x < numColumns; x++)
            {
                _<Engine::Renderers::Image2DRenderer>().DrawImage(
                    k_slotImageName, xStart + x * (slotWidth + marginX),
                    yStart + y * (slotHeight + marginY), slotWidth, slotHeight);
            }
        }
    }

    void GUIPlayerBodyWindow::Initialize()
    {
        auto imageWidth{0.07f};

        auto imageHeight{ConvertWidthToHeight(
            imageWidth, _<Engine::SDLDevice>().GetWindow())};

        auto overallBodyImageButton{std::make_shared<
            GUIComponentsLibrary::GUIButton>(
            0.1f - imageWidth / 2, 0.04f, imageWidth, imageHeight, "",
            [this]
            {
                SelectBodyPart(CInt(
                    Theme0::GameplayCore::Player::BodyPartTypes::OverallBody));
                UpdateBodyPartInfoLabels();
            },
            "gui_image_overall_body", "gui_image_overall_body_hovered")};

        AddChildComponent(overallBodyImageButton);

        auto rightArmBodyImageButton{
            std::make_shared<GUIComponentsLibrary::GUIButton>(
                0.1f - imageWidth / 2 - imageWidth, 0.04f, imageWidth,
                imageHeight, "",
                [this]
                {
                    SelectBodyPart(CInt(
                        Theme0::GameplayCore::Player::BodyPartTypes::RightArm));
                    UpdateBodyPartInfoLabels();
                },
                "gui_image_right_arm", "gui_image_right_arm_hovered")};

        AddChildComponent(rightArmBodyImageButton);

        auto leftArmBodyImageButton{
            std::make_shared<GUIComponentsLibrary::GUIButton>(
                0.1f - imageWidth / 2 + imageWidth, 0.04f, imageWidth,
                imageHeight, "",
                [this]
                {
                    SelectBodyPart(CInt(
                        Theme0::GameplayCore::Player::BodyPartTypes::LeftArm));
                    UpdateBodyPartInfoLabels();
                },
                "gui_image_left_arm", "gui_image_left_arm_hovered")};

        AddChildComponent(leftArmBodyImageButton);

        auto legsImageButton{std::make_shared<GUIComponentsLibrary::GUIButton>(
            0.1f - imageWidth / 2, 0.04f + imageHeight, imageWidth, imageHeight,
            "",
            [this]
            {
                SelectBodyPart(
                    CInt(Theme0::GameplayCore::Player::BodyPartTypes::Legs));
                UpdateBodyPartInfoLabels();
            },
            "gui_image_legs", "gui_image_legs_hovered")};

        AddChildComponent(legsImageButton);

        m_labelBodyPartName = std::make_shared<GUIComponentsLibrary::GUILabel>(
            0.01f, 0.3f, 0.2f, 0.05f, "Body part: ", false,
            Colors::YellowTransparent);

        m_labelBodyPartStrength =
            std::make_shared<GUIComponentsLibrary::GUILabel>(
                0.01f + 0.01f, 0.3f + 1 * 0.02f, 0.2f, 0.05f, "Strength: ");

        m_labelBodyPartEnergy =
            std::make_shared<GUIComponentsLibrary::GUILabel>(
                0.01f + 0.01f, 0.3f + 2 * 0.02f, 0.2f, 0.05f, "Energy: ");

        m_labelBodyPartTemperature =
            std::make_shared<GUIComponentsLibrary::GUILabel>(
                0.01f + 0.01f, 0.3f + 3 * 0.02f, 0.2f, 0.05f, "Temperature: ");

        AddChildComponent(m_labelBodyPartName);
        AddChildComponent(m_labelBodyPartStrength);
        AddChildComponent(m_labelBodyPartEnergy);
        AddChildComponent(m_labelBodyPartTemperature);
    }

    void GUIPlayerBodyWindow::SelectBodyPart(int type)
    {
        m_selectedBodyPart = type;
    }

    void GUIPlayerBodyWindow::UpdateBodyPartInfoLabels()
    {
        auto &playerBody{
            _<Theme0::GameplayCore::Player::PlayerCharacter>().GetBodyRef()};

        constexpr auto overallBody{
            CInt(Theme0::GameplayCore::Player::BodyPartTypes::OverallBody)};

        constexpr auto rightArm{
            CInt(Theme0::GameplayCore::Player::BodyPartTypes::RightArm)};

        constexpr auto leftArm{
            CInt(Theme0::GameplayCore::Player::BodyPartTypes::LeftArm)};

        constexpr auto legs{
            CInt(Theme0::GameplayCore::Player::BodyPartTypes::Legs)};

        switch (m_selectedBodyPart)
        {
        case overallBody:
        {
            m_labelBodyPartName->SetText("Body part: Overall body");

            auto strength{playerBody
                              .GetBodyPartPtr(Theme0::GameplayCore::Player::
                                                  BodyPartTypes::OverallBody)
                              ->GetStrength()};

            m_labelBodyPartStrength->SetText(
                fmt::format("Strength: {:.2f}", strength));
            auto maxEnergy{playerBody
                               .GetBodyPartPtr(Theme0::GameplayCore::Player::
                                                   BodyPartTypes::OverallBody)
                               ->GetMaxEnergy()};

            auto currentEnergy{
                playerBody
                    .GetBodyPartPtr(Theme0::GameplayCore::Player::
                                        BodyPartTypes::OverallBody)
                    ->GetCurrentEnergy()};

            m_labelBodyPartEnergy->SetText(fmt::format(
                "Energy: {:.2f} / {:.2f}", currentEnergy, maxEnergy));

            auto temperature{playerBody
                                 .GetBodyPartPtr(Theme0::GameplayCore::Player::
                                                     BodyPartTypes::OverallBody)
                                 ->GetTemperature()};

            m_labelBodyPartTemperature->SetText(
                fmt::format("Temperature: {:.2f} C", temperature));
        }

        break;

        case rightArm:
        {
            m_labelBodyPartName->SetText("Body part: Right arm");

            auto strength{
                playerBody
                    .GetBodyPartPtr(
                        Theme0::GameplayCore::Player::BodyPartTypes::RightArm)
                    ->GetStrength()};

            m_labelBodyPartStrength->SetText(
                fmt::format("Strength: {:.2f}", strength));

            auto maxEnergy{
                playerBody
                    .GetBodyPartPtr(
                        Theme0::GameplayCore::Player::BodyPartTypes::RightArm)
                    ->GetMaxEnergy()};

            auto currentEnergy{
                playerBody
                    .GetBodyPartPtr(
                        Theme0::GameplayCore::Player::BodyPartTypes::RightArm)
                    ->GetCurrentEnergy()};

            m_labelBodyPartEnergy->SetText(fmt::format(
                "Energy: {:.2f} / {:.2f}", currentEnergy, maxEnergy));

            auto temperature{
                playerBody
                    .GetBodyPartPtr(
                        Theme0::GameplayCore::Player::BodyPartTypes::RightArm)
                    ->GetTemperature()};

            m_labelBodyPartTemperature->SetText(
                fmt::format("Temperature: {:.2f} C", temperature));
        }

        break;

        case leftArm:
        {
            m_labelBodyPartName->SetText("Body part: Left arm");

            auto strength{
                playerBody
                    .GetBodyPartPtr(
                        Theme0::GameplayCore::Player::BodyPartTypes::LeftArm)
                    ->GetStrength()};

            m_labelBodyPartStrength->SetText(
                fmt::format("Strength: {:.2f}", strength));

            auto maxEnergy{
                playerBody
                    .GetBodyPartPtr(
                        Theme0::GameplayCore::Player::BodyPartTypes::LeftArm)
                    ->GetMaxEnergy()};

            auto currentEnergy{
                playerBody
                    .GetBodyPartPtr(
                        Theme0::GameplayCore::Player::BodyPartTypes::LeftArm)
                    ->GetCurrentEnergy()};

            m_labelBodyPartEnergy->SetText(fmt::format(
                "Energy: {:.2f} / {:.2f}", currentEnergy, maxEnergy));

            auto temperature{
                playerBody
                    .GetBodyPartPtr(
                        Theme0::GameplayCore::Player::BodyPartTypes::LeftArm)
                    ->GetTemperature()};

            m_labelBodyPartTemperature->SetText(
                fmt::format("Temperature: {:.2f} C", temperature));
        }

        break;

        case legs:
        {
            m_labelBodyPartName->SetText("Body part: Legs");

            auto strength{
                playerBody
                    .GetBodyPartPtr(
                        Theme0::GameplayCore::Player::BodyPartTypes::Legs)
                    ->GetStrength()};

            m_labelBodyPartStrength->SetText(
                fmt::format("Strength: {:.2f}", strength));

            auto maxEnergy{
                playerBody
                    .GetBodyPartPtr(
                        Theme0::GameplayCore::Player::BodyPartTypes::Legs)
                    ->GetMaxEnergy()};

            auto currentEnergy{
                playerBody
                    .GetBodyPartPtr(
                        Theme0::GameplayCore::Player::BodyPartTypes::Legs)
                    ->GetCurrentEnergy()};

            m_labelBodyPartEnergy->SetText(fmt::format(
                "Energy: {:.2f} / {:.2f}", currentEnergy, maxEnergy));

            auto temperature{
                playerBody
                    .GetBodyPartPtr(
                        Theme0::GameplayCore::Player::BodyPartTypes::Legs)
                    ->GetTemperature()};

            m_labelBodyPartTemperature->SetText(
                fmt::format("Temperature: {:.2f} C", temperature));
        }

        break;
        }
    }

    void GUIInteractionMenu::Initialize()
    {
        SetVisible(false);
    }

    void GUIInteractionMenu::BuildMenu()
    {
        m_entries.clear();

        auto hoveredCoordinate{_<TileHovering>().GetHoveredCoordinate()};

        m_clickedCoordinate = hoveredCoordinate;

        auto worldArea{_<World>().GetCurrentWorldArea()};

        auto worldAreaSize{worldArea->GetSize()};

        auto tile{
            worldArea->GetTile(worldAreaSize.width - hoveredCoordinate.x,
                               worldAreaSize.height - hoveredCoordinate.y)};

        if (tile && tile->GetGround() == Hash("ground_grass"))
        {
            m_entries.push_back(
                {"Forage", [=]()
                 {
                     _<GUIComponentsLibrary::GUIChatBox>().Print(
                         "Grass foraged. You found blue berries.");
                 }});
        }

        auto objects{tile->GetObjectsStack()->GetObjects()};

        for (auto &object : objects)
        {
            auto type{object->GetType()};

            if (type == Hash("object_fir_tree"))
            {
                m_entries.push_back(
                    {"Cut down tree", [=]()
                     {
                         tile->GetObjectsStack()->RemoveObjectOfType(
                             "object_fir_tree");
                         tile->GetObjectsStack()->AddObject(
                             "object_felled_tree");
                         _<GUIComponentsLibrary::GUIChatBox>().Print(
                             "Tree cut down. You found some wood.");
                     }});
            }

            if (type == Hash("object_birch_tree"))
            {
                m_entries.push_back(
                    {"Cut down tree", [=]()
                     {
                         tile->GetObjectsStack()->RemoveObjectOfType(
                             "object_birch_tree");
                         tile->GetObjectsStack()->AddObject(
                             "object_felled_tree");
                         _<GUIComponentsLibrary::GUIChatBox>().Print(
                             "Tree cut down. You found some wood.");
                     }});
            }
        }
    }

    void GUIInteractionMenu::UpdateDerived()
    {
        GUIPanel::UpdateDerived();

        auto bounds{GetBounds()};

        auto mousePosition{
            GetNormallizedMousePosition(_<Engine::SDLDevice>().GetWindow())};

        auto i{0};

        for (auto &entry : m_entries)
        {
            auto menuEntryRect{RectF{bounds.x + 0.01f + k_indentWidth,
                                     bounds.y + 0.01f + k_lineHeight * (i + 1),
                                     bounds.width, k_lineHeight}};

            if (_<Core::Engine::Input::MouseInput::LeftMouseButton>()
                    .HasBeenFired())
            {
                if (menuEntryRect.Contains(mousePosition))
                {
                    entry.GetAction()();
                }

                SetVisible(false);
            }

            ++i;
        }
        if (_<Core::Engine::Input::MouseInput::LeftMouseButton>()
                .HasBeenFiredPickResult())
        {
            SetVisible(false);
        }
    }

    void GUIInteractionMenu::RenderDerived() const
    {
        GUIPanel::RenderDerived();

        auto bounds{GetBounds()};

        _<Engine::Renderers::TextRenderer>().DrawString(
            "Actions", bounds.x + 0.01f, bounds.y + 0.01f,
            Engine::Renderers::FontSizes::_20, false,
            Colors::YellowTransparent);

        auto i{0};

        for (auto &entry : m_entries)
        {
            _<Engine::Renderers::TextRenderer>().DrawString(
                entry.GetLabel(), bounds.x + 0.01f + k_indentWidth,
                bounds.y + 0.01f + (i + 1) * k_lineHeight,
                Engine::Renderers::FontSizes::_20);

            ++i;
        }
    }
}
}
}