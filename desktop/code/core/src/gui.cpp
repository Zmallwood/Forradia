/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui.hpp"
#include "core.hpp"
#include "render.hpp"

_NS_START_
SharedPtr<GUIComponentsLibrary::GUIComponent>
GUIComponentsLibrary::GUIComponent::add_child_comp(
    SharedPtr<GUIComponentsLibrary::GUIComponent> comp)
{
    comp->set_parent_comp(this);

    children_.push_back(comp);

    return comp;
}

void GUIComponentsLibrary::GUIComponent::update()
{
    if (!visible_ || !enabled_)
    {
        return;
    }

    for (auto comp : std::views::reverse(children_))
    {
        comp->update();
    }

    update_derived();
}

void GUIComponentsLibrary::GUIComponent::render() const
{
    if (!visible_)
    {
        return;
    }

    render_derived();

    for (auto comp : children_)
    {
        comp->render();
    }
}

RectF GUIComponentsLibrary::GUIComponent::bounds() const
{
    auto b_res{bounds_};

    if (parent_comp_)
    {
        auto parent_pos{parent_comp_->bounds().GetPosition()};

        b_res.Offset(parent_pos);
    }

    return b_res;
}

void GUIComponentsLibrary::GUIComponent::toggle_visible()
{
    visible_ = !visible_;
}

void GUIComponentsLibrary::GUIComponent::set_pos(PointF new_pos)
{
    bounds_.x = new_pos.x;
    bounds_.y = new_pos.y;
}

void GUIComponentsLibrary::GUILabel::render_derived() const
{
    auto b{bounds()};

    auto x{b.x};
    auto y{b.y};

    if (cent_align_)
    {
        b.x += b.w / 2;
        b.y += b.h / 2;
    }

    _<Engine::Renderers::TextRenderer>().draw_str(
        text_, b.x, b.y, Engine::Renderers::FontSizes::_20, cent_align_, color_);
}

void GUIComponentsLibrary::GUIPanel::render_derived() const
{
    auto b{bounds()};

    _<Engine::Renderers::Image2DRenderer>().draw_img(bg_img_, b.x, b.y, b.w, b.h);
}

void GUIComponentsLibrary::GUIButton::update_derived()
{
    GUIComponentsLibrary::GUIPanel::update_derived();

    auto mouse_pos{GetNormallizedMousePosition(_<Engine::SDLDevice>().GetWindow())};

    auto hovered{bounds().Contains(mouse_pos)};

    if (hovered)
    {
        set_bg_img(hovered_bg_img_);

        _<Engine::Cursor>().SetCursorStyle(
            Engine::Cursor::CursorStyles::hovering_clickable_gui);

        if (_<Core::Engine::Input::MouseInput::LeftMouseButton>()
                .HasBeenFiredPickResult())
        {
            action_();
        }
    }
    else
    {
        set_bg_img(bg_img_);
    }
}

void GUIComponentsLibrary::GUIButton::render_derived() const
{
    GUIPanel::render_derived();

    auto b{bounds()};

    _<Engine::Renderers::TextRenderer>().draw_str(
        text_, b.x + b.w / 2, b.y + b.h / 2, Engine::Renderers::FontSizes::_20,
        true);
}

void GUIComponentsLibrary::GUIMovablePanel::update_derived()
{
    auto mouse_pos{GetNormallizedMousePosition(_<Engine::SDLDevice>().GetWindow())};

    auto drag_area{get_drag_area()};

    if (drag_area.Contains(mouse_pos))
    {
        _<Engine::Cursor>().SetCursorStyle(
            Engine::Cursor::CursorStyles::hovering_clickable_gui);

        if (_<Core::Engine::Input::MouseInput::LeftMouseButton>()
                .HasBeenFiredPickResult())
        {
            start_move();
        }
    }

    if (_<Core::Engine::Input::MouseInput::LeftMouseButton>()
            .HasBeenReleased())
    {
        stop_move();
    }

    auto b{bounds()};

    if (b.Contains(mouse_pos))
    {
        if (_<Core::Engine::Input::MouseInput::LeftMouseButton>()
                .HasBeenFired())
        {
            _<Core::Engine::Input::MouseInput::LeftMouseButton>().Reset();
        }
    }
    if (being_moved())
    {
        auto curr_mouse_pos{GetNormallizedMousePosition(_<Engine::SDLDevice>().GetWindow())};

        auto new_pos{move_start_pos() + curr_mouse_pos -
                     move_start_mouse_pos()};

        set_pos(new_pos);
    }
}

void GUIComponentsLibrary::GUIMovablePanel::start_move()
{
    being_moved_ = true;

    move_start_pos_ = bounds().GetPosition();

    move_start_mouse_pos_ = GetNormallizedMousePosition(_<Engine::SDLDevice>().GetWindow());
}

void GUIComponentsLibrary::GUIMovablePanel::stop_move()
{
    being_moved_ = false;
}

RectF GUIComponentsLibrary::GUIMovablePanel::get_drag_area()
{
    return bounds();
}

void GUIComponentsLibrary::GUIWindow::gui_win_title_bar::init()
{
    auto parent_win_b{parent_win_.bounds()};

    add_child_comp(std::make_shared<GUIButton>(
        parent_win_b.w - ConvertWidthToHeight(0.015f, _<Engine::SDLDevice>().GetWindow()),
        0.01f, 0.015f, ConvertWidthToHeight(0.015f, _<Engine::SDLDevice>().GetWindow()), "X",
        [this] { parent_win_.toggle_visible(); }));
}

void GUIComponentsLibrary::GUIWindow::gui_win_title_bar::render_derived() const
{
    GUIPanel::render_derived();

    auto parent_win_b{parent_win_.bounds()};

    _<Engine::Renderers::TextRenderer>().draw_str(
        k_win_title, parent_win_b.x + 0.01f, parent_win_b.y + 0.01f,
        Engine::Renderers::FontSizes::_20, false, Colors::yellow);
}

RectF GUIComponentsLibrary::GUIWindow::gui_win_title_bar::bounds() const
{
    RectF b_res;

    auto parent_win_b{parent_win_.bounds()};

    b_res.x = parent_win_b.x;
    b_res.y = parent_win_b.y;
    b_res.w = parent_win_b.w;
    b_res.h = k_h;

    return b_res;
}
void GUIComponentsLibrary::GUIWindow::init(StringView win_title)
{
    set_visible(false);

    gui_win_title_bar_ = std::make_shared<gui_win_title_bar>(*this, win_title);

    add_child_comp(gui_win_title_bar_);
}

void GUIComponentsLibrary::GUIWindow::render_derived() const
{
    GUIMovablePanel::render_derived();
}

RectF GUIComponentsLibrary::GUIWindow::get_drag_area()
{
    return gui_win_title_bar_->bounds();
}

void GUIComponentsLibrary::GUIFPSPanel::init()
{
    fps_text_pnl_ = std::make_shared<GUILabel>(0.01f, 0.01f, 0.1f, 0.05f);

    add_child_comp(fps_text_pnl_);
}

void GUIComponentsLibrary::GUIFPSPanel::update_derived()
{
    GUIMovablePanel::update_derived();

    auto fps{_<Engine::FPSCounter>().GetFPS()};

    fps_text_pnl_->set_text(fmt::format("FPS: {}", fps));
}

void GUIComponentsLibrary::GUIChatBox::render_derived() const
{
    GUIPanel::render_derived();

    auto b{bounds()};

    auto max_num_lines{CInt(b.h / k_line_h - 1)};

    auto y{b.y + k_marg};

    for (auto i = 0; i < max_num_lines; i++)
    {
        auto idx{lines_.size() - max_num_lines + i};

        if (idx < 0 || idx >= lines_.size())
        {
            continue;
        }

        auto text_line = lines_.at(idx);

        _<Engine::Renderers::TextRenderer>().draw_str(text_line, b.x + k_marg, y);

        y += k_line_h;
    }

    auto sep_rect{RectF{b.x, b.y + b.h - k_line_h, b.w, k_sep_h}};

    _<Engine::Renderers::Image2DRenderer>().draw_img(
        "black", sep_rect.x, sep_rect.y, sep_rect.w, sep_rect.h);
}

void GUIComponentsLibrary::GUIChatBox::print(StringView text)
{
    lines_.push_back(text.data());
}
_NS_END_