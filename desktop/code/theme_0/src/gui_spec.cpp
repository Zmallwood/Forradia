/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui_spec.hpp"
#include "core.hpp"
#include "render.hpp"
#include "theme_0_core.hpp"
#include "update.hpp"
#include "world_struct.hpp"

_NS_START_
#define _HIDE_FROM_OUTLINER_GUI_SPEC_TOP_                                      \
    namespace Theme0                                                           \
    {
_HIDE_FROM_OUTLINER_GUI_SPEC_TOP_
namespace SpecializedGUI
{
    void GUIPlayerStatusBox::RenderDerived() const
    {
        GUIPanel::RenderDerived();

        auto b{GetBounds()};

        _<Engine::Renderers::TextRenderer>().DrawString(
            _<Theme0::GameplayCore::Player::PlayerCharacter>().GetName(), b.x + 0.01f,
            b.y + 0.01f, Engine::Renderers::FontSizes::_26);
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

        // SDL_SetRenderDrawColor(_<Engine::SDLDevice>().rend().get(), 200, 0,
        //                        255, 50);

        // SDL_RenderFillRect(_<Engine::SDLDevice>().rend().get(), &rect);
    }

    void GUIInventoryWindow::RenderDerived() const
    {
        GUIWindow::RenderDerived();

        auto b{GetBounds()};

        auto margin_x{k_margin};

        auto margin_y{ConvertWidthToHeight(k_margin, _<Engine::SDLDevice>().GetWindow())};

        auto x_start{b.x + margin_x};

        auto y_start{b.y + margin_y + GetGUIWindowTitleBar()->GetBounds().h};

        auto slot_w{k_slotSize};

        auto slot_h{ConvertWidthToHeight(k_slotSize, _<Engine::SDLDevice>().GetWindow())};

        auto num_cols{CInt((b.w - 2 * margin_x) / slot_w)};

        auto num_rows{CInt((b.h - 2 * margin_y - (y_start - b.y)) / slot_h)};

        for (auto y = 0; y < num_rows; y++)
        {
            for (auto x = 0; x < num_cols; x++)
            {
                _<Engine::Renderers::Image2DRenderer>().DrawImage(
                    k_slotImageName, x_start + x * (slot_w + margin_x),
                    y_start + y * (slot_h + margin_y), slot_w, slot_h);
            }
        }
    }

    void GUIPlayerBodyWindow::Initialize()
    {
        auto img_w{0.07f};

        auto img_h{ConvertWidthToHeight(img_w, _<Engine::SDLDevice>().GetWindow())};

        auto overall_body_img_btn{
            std::make_shared<GUIComponentsLibrary::GUIButton>(
                0.1f - img_w / 2, 0.04f, img_w, img_h, "",
                [this]
                {
                    SelectBodyPart(CInt(Theme0::GameplayCore::Player::
                                            BodyPartTypes::overall_body));
                    UpdateBodyPartInfoLabels();
                },
                "gui_image_overall_body", "gui_image_overall_body_hovered")};

        AddChildComponent(overall_body_img_btn);

        auto right_arm_body_img_btn{std::make_shared<
            GUIComponentsLibrary::GUIButton>(
            0.1f - img_w / 2 - img_w, 0.04f, img_w, img_h, "",
            [this]
            {
                SelectBodyPart(CInt(
                    Theme0::GameplayCore::Player::BodyPartTypes::right_arm));
                UpdateBodyPartInfoLabels();
            },
            "gui_image_right_arm", "gui_image_right_arm_hovered")};

        AddChildComponent(right_arm_body_img_btn);

        auto left_arm_body_img_btn{std::make_shared<
            GUIComponentsLibrary::GUIButton>(
            0.1f - img_w / 2 + img_w, 0.04f, img_w, img_h, "",
            [this]
            {
                SelectBodyPart(CInt(
                    Theme0::GameplayCore::Player::BodyPartTypes::left_arm));
                UpdateBodyPartInfoLabels();
            },
            "gui_image_left_arm", "gui_image_left_arm_hovered")};

        AddChildComponent(left_arm_body_img_btn);

        auto legs_img_btn{std::make_shared<GUIComponentsLibrary::GUIButton>(
            0.1f - img_w / 2, 0.04f + img_h, img_w, img_h, "",
            [this]
            {
                SelectBodyPart(
                    CInt(Theme0::GameplayCore::Player::BodyPartTypes::legs));
                UpdateBodyPartInfoLabels();
            },
            "gui_image_legs", "gui_image_legs_hovered")};

        AddChildComponent(legs_img_btn);

        m_labelBodyPartName = std::make_shared<GUIComponentsLibrary::GUILabel>(
            0.01f, 0.3f, 0.2f, 0.05f, "Body part: ", false,
            Colors::yellow_transp);

        m_labelBodyPartStrength = std::make_shared<GUIComponentsLibrary::GUILabel>(
            0.01f + 0.01f, 0.3f + 1 * 0.02f, 0.2f, 0.05f, "Strength: ");

        m_labelBodyPartEnergy =
            std::make_shared<GUIComponentsLibrary::GUILabel>(
                0.01f + 0.01f, 0.3f + 2 * 0.02f, 0.2f, 0.05f, "Energy: ");

        m_labelBodyPartTemperature = std::make_shared<GUIComponentsLibrary::GUILabel>(
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
        auto &p_body{_<Theme0::GameplayCore::Player::PlayerCharacter>().GetBodyRef()};

        constexpr auto overall_body{
            CInt(Theme0::GameplayCore::Player::BodyPartTypes::overall_body)};

        constexpr auto right_arm{
            CInt(Theme0::GameplayCore::Player::BodyPartTypes::right_arm)};

        constexpr auto left_arm{
            CInt(Theme0::GameplayCore::Player::BodyPartTypes::left_arm)};

        constexpr auto legs{
            CInt(Theme0::GameplayCore::Player::BodyPartTypes::legs)};

        switch (m_selectedBodyPart)
        {
        case overall_body:
        {
            m_labelBodyPartName->SetText("Body part: Overall body");

            auto String{p_body
                         .GetBodyPartPtr(Theme0::GameplayCore::Player::
                                            BodyPartTypes::overall_body)
                         ->GetStrength()};

            m_labelBodyPartStrength->SetText(fmt::format("Strength: {:.2f}", String));
            auto max_energy{
                p_body
                    .GetBodyPartPtr(Theme0::GameplayCore::Player::
                                       BodyPartTypes::overall_body)
                    ->GetMaxEnergy()};

            auto curr_energy{
                p_body
                    .GetBodyPartPtr(Theme0::GameplayCore::Player::
                                       BodyPartTypes::overall_body)
                    ->GetCurrentEnergy()};

            m_labelBodyPartEnergy->SetText(fmt::format(
                "Energy: {:.2f} / {:.2f}", curr_energy, max_energy));

            auto temp{p_body
                          .GetBodyPartPtr(Theme0::GameplayCore::Player::
                                             BodyPartTypes::overall_body)
                          ->GetTemperature()};

            m_labelBodyPartTemperature->SetText(
                fmt::format("Temperature: {:.2f} C", temp));
        }

        break;

        case right_arm:
        {
            m_labelBodyPartName->SetText("Body part: Right arm");

            auto String{p_body
                         .GetBodyPartPtr(Theme0::GameplayCore::Player::
                                            BodyPartTypes::right_arm)
                         ->GetStrength()};

            m_labelBodyPartStrength->SetText(fmt::format("Strength: {:.2f}", String));

            auto max_energy{p_body
                                .GetBodyPartPtr(Theme0::GameplayCore::Player::
                                                   BodyPartTypes::right_arm)
                                ->GetMaxEnergy()};

            auto curr_energy{p_body
                                 .GetBodyPartPtr(Theme0::GameplayCore::Player::
                                                    BodyPartTypes::right_arm)
                                 ->GetCurrentEnergy()};

            m_labelBodyPartEnergy->SetText(fmt::format(
                "Energy: {:.2f} / {:.2f}", curr_energy, max_energy));

            auto temp{p_body
                          .GetBodyPartPtr(Theme0::GameplayCore::Player::
                                             BodyPartTypes::right_arm)
                          ->GetTemperature()};

            m_labelBodyPartTemperature->SetText(
                fmt::format("Temperature: {:.2f} C", temp));
        }

        break;

        case left_arm:
        {
            m_labelBodyPartName->SetText("Body part: Left arm");

            auto String{
                p_body
                    .GetBodyPartPtr(
                        Theme0::GameplayCore::Player::BodyPartTypes::left_arm)
                    ->GetStrength()};

            m_labelBodyPartStrength->SetText(fmt::format("Strength: {:.2f}", String));

            auto max_energy{
                p_body
                    .GetBodyPartPtr(
                        Theme0::GameplayCore::Player::BodyPartTypes::left_arm)
                    ->GetMaxEnergy()};

            auto curr_energy{
                p_body
                    .GetBodyPartPtr(
                        Theme0::GameplayCore::Player::BodyPartTypes::left_arm)
                    ->GetCurrentEnergy()};

            m_labelBodyPartEnergy->SetText(fmt::format(
                "Energy: {:.2f} / {:.2f}", curr_energy, max_energy));

            auto temp{
                p_body
                    .GetBodyPartPtr(
                        Theme0::GameplayCore::Player::BodyPartTypes::left_arm)
                    ->GetTemperature()};

            m_labelBodyPartTemperature->SetText(
                fmt::format("Temperature: {:.2f} C", temp));
        }

        break;

        case legs:
        {
            m_labelBodyPartName->SetText("Body part: Legs");

            auto String{
                p_body
                    .GetBodyPartPtr(
                        Theme0::GameplayCore::Player::BodyPartTypes::legs)
                    ->GetStrength()};

            m_labelBodyPartStrength->SetText(fmt::format("Strength: {:.2f}", String));

            auto max_energy{
                p_body
                    .GetBodyPartPtr(
                        Theme0::GameplayCore::Player::BodyPartTypes::legs)
                    ->GetMaxEnergy()};

            auto curr_energy{
                p_body
                    .GetBodyPartPtr(
                        Theme0::GameplayCore::Player::BodyPartTypes::legs)
                    ->GetCurrentEnergy()};

            m_labelBodyPartEnergy->SetText(fmt::format(
                "Energy: {:.2f} / {:.2f}", curr_energy, max_energy));

            auto temp{
                p_body
                    .GetBodyPartPtr(
                        Theme0::GameplayCore::Player::BodyPartTypes::legs)
                    ->GetTemperature()};

            m_labelBodyPartTemperature->SetText(
                fmt::format("Temperature: {:.2f} C", temp));
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
        entries_.clear();

        auto hov_tl{_<TileHovering>().GetHoveredCoordinate()};

        auto w_area{_<World>().GetCurrentWorldArea()};

        auto tl{w_area->GetTile(hov_tl.x, hov_tl.y)};

        if (tl && tl->GetGround() == Hash("ground_grass"))
        {
            entries_.push_back(
                {"Forage", [=]()
                 {
                     _<GUIComponentsLibrary::GUIChatBox>().Print(
                         "Grass foraged. You found blue berries.");
                 }});
        }

        auto objects{tl->GetObjectsStack()->GetObjects()};

        for (auto &obj : objects)
        {
            auto type{obj->GetType()};

            if (type == Hash("object_fir_tree") ||
                type == Hash("object_birch_tree"))
            {
                entries_.push_back(
                    {"Cut down tree", [=]()
                     {
                         _<GUIComponentsLibrary::GUIChatBox>().Print(
                             "Tree cut down. You found some wood.");
                     }});
            }
        }
    }

    void GUIInteractionMenu::UpdateDerived()
    {
        GUIPanel::UpdateDerived();

        auto b{GetBounds()};

        auto mouse_pos{GetNormallizedMousePosition(_<Engine::SDLDevice>().GetWindow())};

        auto i{0};

        for (auto &entry : entries_)
        {
            auto menu_entry_rect{RectF{b.x + 0.01f + k_indent_w,
                                        b.y + 0.01f + k_line_h * (i + 1), b.w,
                                        k_line_h}};

            if (_<Core::Engine::Input::MouseInput::LeftMouseButton>()
                    .HasBeenFired())
            {
                if (menu_entry_rect.Contains(mouse_pos))
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

        auto b{GetBounds()};

        _<Engine::Renderers::TextRenderer>().DrawString(
            "Actions", b.x + 0.01f, b.y + 0.01f,
            Engine::Renderers::FontSizes::_20, false, Colors::yellow_transp);

        auto i{0};

        for (auto &entry : entries_)
        {
            _<Engine::Renderers::TextRenderer>().DrawString(
                entry.GetLabel(), b.x + 0.01f + k_indent_w,
                b.y + 0.01f + (i + 1) * k_line_h,
                Engine::Renderers::FontSizes::_20);

            ++i;
        }
    }
}
}
_NS_END_