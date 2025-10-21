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
    void GUIPlayerStatusBox::render_derived() const
    {
        GUIPanel::render_derived();

        auto b{bounds()};

        _<Engine::Renderers::TextRenderer>().draw_str(
            _<Theme0::GameplayCore::Player::PlayerCharacter>().name(), b.x + 0.01f,
            b.y + 0.01f, Engine::Renderers::FontSizes::_26);
    }

    void GUISystemMenu::init()
    {
        set_visible(false);
    }

    void GUISystemMenu::update_derived()
    {
        GUIComponent::update_derived();

        _<Core::Engine::Input::MouseInput::LeftMouseButton>().reset();
    }

    void GUISystemMenu::render_derived() const
    {
        GUIComponent::render_derived();

        auto c_sz{get_canv_sz(_<Engine::SDLDevice>().win())};

        auto rect{SDL_Rect{0, 0, c_sz.w, c_sz.h}};

        SDL_SetRenderDrawBlendMode(_<Engine::SDLDevice>().rend().get(),
                                   SDL_BLENDMODE_BLEND);

        SDL_SetRenderDrawColor(_<Engine::SDLDevice>().rend().get(), 200, 0,
                               255, 50);

        SDL_RenderFillRect(_<Engine::SDLDevice>().rend().get(), &rect);
    }

    void GUIInventoryWindow::render_derived() const
    {
        GUIWindow::render_derived();

        auto b{bounds()};

        auto margin_x{k_margin};

        auto margin_y{conv_w_to_h(k_margin, _<Engine::SDLDevice>().win())};

        auto x_start{b.x + margin_x};

        auto y_start{b.y + margin_y + get_win_title_bar()->bounds().h};

        auto slot_w{k_slot_size};

        auto slot_h{conv_w_to_h(k_slot_size, _<Engine::SDLDevice>().win())};

        auto num_cols{c_int((b.w - 2 * margin_x) / slot_w)};

        auto num_rows{c_int((b.h - 2 * margin_y - (y_start - b.y)) / slot_h)};

        for (auto y = 0; y < num_rows; y++)
        {
            for (auto x = 0; x < num_cols; x++)
            {
                _<Engine::Renderers::Image2DRenderer>().draw_img(
                    k_slot_img_name, x_start + x * (slot_w + margin_x),
                    y_start + y * (slot_h + margin_y), slot_w, slot_h);
            }
        }
    }

    void GUIPlayerBodyWindow::init()
    {
        auto img_w{0.07f};

        auto img_h{conv_w_to_h(img_w, _<Engine::SDLDevice>().win())};

        auto overall_body_img_btn{
            std::make_shared<GUIComponentsLibrary::GUIButton>(
                0.1f - img_w / 2, 0.04f, img_w, img_h, "",
                [this]
                {
                    sel_body_part(c_int(Theme0::GameplayCore::Player::
                                            BodyPartTypes::overall_body));
                    update_body_part_info_lbls();
                },
                "gui_image_overall_body", "gui_image_overall_body_hovered")};

        add_child_comp(overall_body_img_btn);

        auto right_arm_body_img_btn{std::make_shared<
            GUIComponentsLibrary::GUIButton>(
            0.1f - img_w / 2 - img_w, 0.04f, img_w, img_h, "",
            [this]
            {
                sel_body_part(c_int(
                    Theme0::GameplayCore::Player::BodyPartTypes::right_arm));
                update_body_part_info_lbls();
            },
            "gui_image_right_arm", "gui_image_right_arm_hovered")};

        add_child_comp(right_arm_body_img_btn);

        auto left_arm_body_img_btn{std::make_shared<
            GUIComponentsLibrary::GUIButton>(
            0.1f - img_w / 2 + img_w, 0.04f, img_w, img_h, "",
            [this]
            {
                sel_body_part(c_int(
                    Theme0::GameplayCore::Player::BodyPartTypes::left_arm));
                update_body_part_info_lbls();
            },
            "gui_image_left_arm", "gui_image_left_arm_hovered")};

        add_child_comp(left_arm_body_img_btn);

        auto legs_img_btn{std::make_shared<GUIComponentsLibrary::GUIButton>(
            0.1f - img_w / 2, 0.04f + img_h, img_w, img_h, "",
            [this]
            {
                sel_body_part(
                    c_int(Theme0::GameplayCore::Player::BodyPartTypes::legs));
                update_body_part_info_lbls();
            },
            "gui_image_legs", "gui_image_legs_hovered")};

        add_child_comp(legs_img_btn);

        lbl_body_part_name_ = std::make_shared<GUIComponentsLibrary::GUILabel>(
            0.01f, 0.3f, 0.2f, 0.05f, "Body part: ", false,
            colors::yellow_transp);

        lbl_body_part_str_ = std::make_shared<GUIComponentsLibrary::GUILabel>(
            0.01f + 0.01f, 0.3f + 1 * 0.02f, 0.2f, 0.05f, "Strength: ");

        lbl_body_part_energy_ =
            std::make_shared<GUIComponentsLibrary::GUILabel>(
                0.01f + 0.01f, 0.3f + 2 * 0.02f, 0.2f, 0.05f, "Energy: ");

        lbl_body_part_temp_ = std::make_shared<GUIComponentsLibrary::GUILabel>(
            0.01f + 0.01f, 0.3f + 3 * 0.02f, 0.2f, 0.05f, "Temperature: ");

        add_child_comp(lbl_body_part_name_);
        add_child_comp(lbl_body_part_str_);
        add_child_comp(lbl_body_part_energy_);
        add_child_comp(lbl_body_part_temp_);
    }

    void GUIPlayerBodyWindow::sel_body_part(int type)
    {
        sel_body_part_ = type;
    }

    void GUIPlayerBodyWindow::update_body_part_info_lbls()
    {
        auto &p_body{_<Theme0::GameplayCore::Player::PlayerCharacter>().body_ref()};

        constexpr auto overall_body{
            c_int(Theme0::GameplayCore::Player::BodyPartTypes::overall_body)};

        constexpr auto right_arm{
            c_int(Theme0::GameplayCore::Player::BodyPartTypes::right_arm)};

        constexpr auto left_arm{
            c_int(Theme0::GameplayCore::Player::BodyPartTypes::left_arm)};

        constexpr auto legs{
            c_int(Theme0::GameplayCore::Player::BodyPartTypes::legs)};

        switch (sel_body_part_)
        {
        case overall_body:
        {
            lbl_body_part_name_->set_text("Body part: Overall body");

            auto String{p_body
                         .body_part_ptr(Theme0::GameplayCore::Player::
                                            BodyPartTypes::overall_body)
                         ->str()};

            lbl_body_part_str_->set_text(fmt::format("Strength: {:.2f}", String));
            auto max_energy{
                p_body
                    .body_part_ptr(Theme0::GameplayCore::Player::
                                       BodyPartTypes::overall_body)
                    ->max_energy()};

            auto curr_energy{
                p_body
                    .body_part_ptr(Theme0::GameplayCore::Player::
                                       BodyPartTypes::overall_body)
                    ->curr_energy()};

            lbl_body_part_energy_->set_text(fmt::format(
                "Energy: {:.2f} / {:.2f}", curr_energy, max_energy));

            auto temp{p_body
                          .body_part_ptr(Theme0::GameplayCore::Player::
                                             BodyPartTypes::overall_body)
                          ->temp()};

            lbl_body_part_temp_->set_text(
                fmt::format("Temperature: {:.2f} C", temp));
        }

        break;

        case right_arm:
        {
            lbl_body_part_name_->set_text("Body part: Right arm");

            auto String{p_body
                         .body_part_ptr(Theme0::GameplayCore::Player::
                                            BodyPartTypes::right_arm)
                         ->str()};

            lbl_body_part_str_->set_text(fmt::format("Strength: {:.2f}", String));

            auto max_energy{p_body
                                .body_part_ptr(Theme0::GameplayCore::Player::
                                                   BodyPartTypes::right_arm)
                                ->max_energy()};

            auto curr_energy{p_body
                                 .body_part_ptr(Theme0::GameplayCore::Player::
                                                    BodyPartTypes::right_arm)
                                 ->curr_energy()};

            lbl_body_part_energy_->set_text(fmt::format(
                "Energy: {:.2f} / {:.2f}", curr_energy, max_energy));

            auto temp{p_body
                          .body_part_ptr(Theme0::GameplayCore::Player::
                                             BodyPartTypes::right_arm)
                          ->temp()};

            lbl_body_part_temp_->set_text(
                fmt::format("Temperature: {:.2f} C", temp));
        }

        break;

        case left_arm:
        {
            lbl_body_part_name_->set_text("Body part: Left arm");

            auto String{
                p_body
                    .body_part_ptr(
                        Theme0::GameplayCore::Player::BodyPartTypes::left_arm)
                    ->str()};

            lbl_body_part_str_->set_text(fmt::format("Strength: {:.2f}", String));

            auto max_energy{
                p_body
                    .body_part_ptr(
                        Theme0::GameplayCore::Player::BodyPartTypes::left_arm)
                    ->max_energy()};

            auto curr_energy{
                p_body
                    .body_part_ptr(
                        Theme0::GameplayCore::Player::BodyPartTypes::left_arm)
                    ->curr_energy()};

            lbl_body_part_energy_->set_text(fmt::format(
                "Energy: {:.2f} / {:.2f}", curr_energy, max_energy));

            auto temp{
                p_body
                    .body_part_ptr(
                        Theme0::GameplayCore::Player::BodyPartTypes::left_arm)
                    ->temp()};

            lbl_body_part_temp_->set_text(
                fmt::format("Temperature: {:.2f} C", temp));
        }

        break;

        case legs:
        {
            lbl_body_part_name_->set_text("Body part: Legs");

            auto String{
                p_body
                    .body_part_ptr(
                        Theme0::GameplayCore::Player::BodyPartTypes::legs)
                    ->str()};

            lbl_body_part_str_->set_text(fmt::format("Strength: {:.2f}", String));

            auto max_energy{
                p_body
                    .body_part_ptr(
                        Theme0::GameplayCore::Player::BodyPartTypes::legs)
                    ->max_energy()};

            auto curr_energy{
                p_body
                    .body_part_ptr(
                        Theme0::GameplayCore::Player::BodyPartTypes::legs)
                    ->curr_energy()};

            lbl_body_part_energy_->set_text(fmt::format(
                "Energy: {:.2f} / {:.2f}", curr_energy, max_energy));

            auto temp{
                p_body
                    .body_part_ptr(
                        Theme0::GameplayCore::Player::BodyPartTypes::legs)
                    ->temp()};

            lbl_body_part_temp_->set_text(
                fmt::format("Temperature: {:.2f} C", temp));
        }

        break;
        }
    }

    void GUIInteractionMenu::init()
    {
        set_visible(false);
    }

    void GUIInteractionMenu::build_menu()
    {
        entries_.clear();

        auto hov_tl{_<TileHovering>().hovered_coord()};

        auto w_area{_<World>().curr_w_area()};

        auto tl{w_area->get_tl(hov_tl.x, hov_tl.y)};

        if (tl && tl->ground() == hash("ground_grass"))
        {
            entries_.push_back(
                {"Forage", [=]()
                 {
                     _<GUIComponentsLibrary::GUIChatBox>().print(
                         "Grass foraged. You found blue berries.");
                 }});
        }

        auto objects{tl->objects_stack()->objects()};

        for (auto &obj : objects)
        {
            auto type{obj->type()};

            if (type == hash("object_fir_tree") ||
                type == hash("object_birch_tree"))
            {
                entries_.push_back(
                    {"Cut down tree", [=]()
                     {
                         _<GUIComponentsLibrary::GUIChatBox>().print(
                             "Tree cut down. You found some wood.");
                     }});
            }
        }
    }

    void GUIInteractionMenu::update_derived()
    {
        GUIPanel::update_derived();

        auto b{bounds()};

        auto mouse_pos{norm_mouse_pos(_<Engine::SDLDevice>().win())};

        auto i{0};

        for (auto &entry : entries_)
        {
            auto menu_entry_rect{RectF{b.x + 0.01f + k_indent_w,
                                        b.y + 0.01f + k_line_h * (i + 1), b.w,
                                        k_line_h}};

            if (_<Core::Engine::Input::MouseInput::LeftMouseButton>()
                    .been_fired_no_pick_res())
            {
                if (menu_entry_rect.contains(mouse_pos))
                {
                    entry.action()();
                }

                set_visible(false);
            }

            ++i;
        }
        if (_<Core::Engine::Input::MouseInput::LeftMouseButton>()
                .been_fired_pick_res())
        {
            set_visible(false);
        }
    }

    void GUIInteractionMenu::render_derived() const
    {
        GUIPanel::render_derived();

        auto b{bounds()};

        _<Engine::Renderers::TextRenderer>().draw_str(
            "Actions", b.x + 0.01f, b.y + 0.01f,
            Engine::Renderers::FontSizes::_20, false, colors::yellow_transp);

        auto i{0};

        for (auto &entry : entries_)
        {
            _<Engine::Renderers::TextRenderer>().draw_str(
                entry.label(), b.x + 0.01f + k_indent_w,
                b.y + 0.01f + (i + 1) * k_line_h,
                Engine::Renderers::FontSizes::_20);

            ++i;
        }
    }
}
}
_NS_END_