/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui.hpp"
#include "core.hpp"
#include "render.hpp"

_NS_START_
SharedPtr<GUIComponentsLibrary::GUIComponent>
GUIComponentsLibrary::GUIComponent::AddChildComponent(
    SharedPtr<GUIComponentsLibrary::GUIComponent> comp)
{
    comp->SetParentComponent(this);

    children_.push_back(comp);

    return comp;
}

void GUIComponentsLibrary::GUIComponent::Update()
{
    if (!visible_ || !enabled_)
    {
        return;
    }

    for (auto comp : std::views::reverse(children_))
    {
        comp->Update();
    }

    UpdateDerived();
}

void GUIComponentsLibrary::GUIComponent::Render() const
{
    if (!visible_)
    {
        return;
    }

    RenderDerived();

    for (auto comp : children_)
    {
        comp->Render();
    }
}

RectF GUIComponentsLibrary::GUIComponent::GetBounds() const
{
    auto b_res{bounds_};

    if (parent_component_)
    {
        auto parent_pos{parent_component_->GetBounds().GetPosition()};

        b_res.Offset(parent_pos);
    }

    return b_res;
}

void GUIComponentsLibrary::GUIComponent::ToggleVisibility()
{
    visible_ = !visible_;
}

void GUIComponentsLibrary::GUIComponent::SetPosition(PointF new_pos)
{
    bounds_.x = new_pos.x;
    bounds_.y = new_pos.y;
}

void GUIComponentsLibrary::GUILabel::RenderDerived() const
{
    auto b{GetBounds()};

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

void GUIComponentsLibrary::GUIPanel::RenderDerived() const
{
    auto b{GetBounds()};

    _<Engine::Renderers::Image2DRenderer>().draw_img(background_image_, b.x, b.y, b.w, b.h);
}

void GUIComponentsLibrary::GUIButton::UpdateDerived()
{
    GUIComponentsLibrary::GUIPanel::UpdateDerived();

    auto mouse_pos{GetNormallizedMousePosition(_<Engine::SDLDevice>().GetWindow())};

    auto hovered{GetBounds().Contains(mouse_pos)};

    if (hovered)
    {
        SetBackgroundImage(hovered_bg_img_);

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
        SetBackgroundImage(bg_img_);
    }
}

void GUIComponentsLibrary::GUIButton::RenderDerived() const
{
    GUIPanel::RenderDerived();

    auto b{GetBounds()};

    _<Engine::Renderers::TextRenderer>().draw_str(
        text_, b.x + b.w / 2, b.y + b.h / 2, Engine::Renderers::FontSizes::_20,
        true);
}

void GUIComponentsLibrary::GUIMovablePanel::UpdateDerived()
{
    auto mouse_pos{GetNormallizedMousePosition(_<Engine::SDLDevice>().GetWindow())};

    auto drag_area{GetDragArea()};

    if (drag_area.Contains(mouse_pos))
    {
        _<Engine::Cursor>().SetCursorStyle(
            Engine::Cursor::CursorStyles::hovering_clickable_gui);

        if (_<Core::Engine::Input::MouseInput::LeftMouseButton>()
                .HasBeenFiredPickResult())
        {
            StartMove();
        }
    }

    if (_<Core::Engine::Input::MouseInput::LeftMouseButton>()
            .HasBeenReleased())
    {
        StopMove();
    }

    auto b{GetBounds()};

    if (b.Contains(mouse_pos))
    {
        if (_<Core::Engine::Input::MouseInput::LeftMouseButton>()
                .HasBeenFired())
        {
            _<Core::Engine::Input::MouseInput::LeftMouseButton>().Reset();
        }
    }
    if (GetIsBeingMoved())
    {
        auto curr_mouse_pos{GetNormallizedMousePosition(_<Engine::SDLDevice>().GetWindow())};

        auto new_pos{GetMoveStartingPosition() + curr_mouse_pos -
                     GetMoveStartingMousePosition()};

        SetPosition(new_pos);
    }
}

void GUIComponentsLibrary::GUIMovablePanel::StartMove()
{
    is_being_moved_ = true;

    move_starting_position_ = GetBounds().GetPosition();

    move_starting_mouse_position_ = GetNormallizedMousePosition(_<Engine::SDLDevice>().GetWindow());
}

void GUIComponentsLibrary::GUIMovablePanel::StopMove()
{
    is_being_moved_ = false;
}

RectF GUIComponentsLibrary::GUIMovablePanel::GetDragArea()
{
    return GetBounds();
}

void GUIComponentsLibrary::GUIWindow::GUIWindowTitleBar::Initialize()
{
    auto parent_win_b{parent_win_.GetBounds()};

    AddChildComponent(std::make_shared<GUIButton>(
        parent_win_b.w - ConvertWidthToHeight(0.015f, _<Engine::SDLDevice>().GetWindow()),
        0.01f, 0.015f, ConvertWidthToHeight(0.015f, _<Engine::SDLDevice>().GetWindow()), "X",
        [this] { parent_win_.ToggleVisibility(); }));
}

void GUIComponentsLibrary::GUIWindow::GUIWindowTitleBar::RenderDerived() const
{
    GUIPanel::RenderDerived();

    auto parent_win_b{parent_win_.GetBounds()};

    _<Engine::Renderers::TextRenderer>().draw_str(
        k_win_title, parent_win_b.x + 0.01f, parent_win_b.y + 0.01f,
        Engine::Renderers::FontSizes::_20, false, Colors::yellow);
}

RectF GUIComponentsLibrary::GUIWindow::GUIWindowTitleBar::GetBounds() const
{
    RectF b_res;

    auto parent_win_b{parent_win_.GetBounds()};

    b_res.x = parent_win_b.x;
    b_res.y = parent_win_b.y;
    b_res.w = parent_win_b.w;
    b_res.h = k_h;

    return b_res;
}
void GUIComponentsLibrary::GUIWindow::Initialize(StringView win_title)
{
    SetVisible(false);

    gui_window_title_bar_ = std::make_shared<GUIWindowTitleBar>(*this, win_title);

    AddChildComponent(gui_window_title_bar_);
}

void GUIComponentsLibrary::GUIWindow::RenderDerived() const
{
    GUIMovablePanel::RenderDerived();
}

RectF GUIComponentsLibrary::GUIWindow::GetDragArea()
{
    return gui_window_title_bar_->GetBounds();
}

void GUIComponentsLibrary::GUIFPSPanel::Initialize()
{
    fps_text_pnl_ = std::make_shared<GUILabel>(0.01f, 0.01f, 0.1f, 0.05f);

    AddChildComponent(fps_text_pnl_);
}

void GUIComponentsLibrary::GUIFPSPanel::UpdateDerived()
{
    GUIMovablePanel::UpdateDerived();

    auto fps{_<Engine::FPSCounter>().GetFPS()};

    fps_text_pnl_->SetText(fmt::format("FPS: {}", fps));
}

void GUIComponentsLibrary::GUIChatBox::RenderDerived() const
{
    GUIPanel::RenderDerived();

    auto b{GetBounds()};

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

void GUIComponentsLibrary::GUIChatBox::Print(StringView text)
{
    lines_.push_back(text.data());
}
_NS_END_