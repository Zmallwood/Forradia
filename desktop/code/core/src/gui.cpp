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

    m_childComponents.push_back(comp);

    return comp;
}

void GUIComponentsLibrary::GUIComponent::Update()
{
    if (!m_visible || !m_enabled)
    {
        return;
    }

    for (auto comp : std::views::reverse(m_childComponents))
    {
        comp->Update();
    }

    UpdateDerived();
}

void GUIComponentsLibrary::GUIComponent::Render() const
{
    if (!m_visible)
    {
        return;
    }

    RenderDerived();

    for (auto comp : m_childComponents)
    {
        comp->Render();
    }
}

RectF GUIComponentsLibrary::GUIComponent::GetBounds() const
{
    auto b_res{m_bounds};

    if (m_parentComponent)
    {
        auto parent_pos{m_parentComponent->GetBounds().GetPosition()};

        b_res.Offset(parent_pos);
    }

    return b_res;
}

void GUIComponentsLibrary::GUIComponent::ToggleVisibility()
{
    m_visible = !m_visible;
}

void GUIComponentsLibrary::GUIComponent::SetPosition(PointF new_pos)
{
    m_bounds.x = new_pos.x;
    m_bounds.y = new_pos.y;
}

void GUIComponentsLibrary::GUILabel::RenderDerived() const
{
    auto b{GetBounds()};

    auto x{b.x};
    auto y{b.y};

    if (m_centerAlign)
    {
        b.x += b.w / 2;
        b.y += b.h / 2;
    }

    _<Engine::Renderers::TextRenderer>().DrawString(
        m_text, b.x, b.y, Engine::Renderers::FontSizes::_20, m_centerAlign, m_color);
}

void GUIComponentsLibrary::GUIPanel::RenderDerived() const
{
    auto b{GetBounds()};

    _<Engine::Renderers::Image2DRenderer>().DrawImage(m_backgroundImage, b.x, b.y, b.w, b.h);
}

void GUIComponentsLibrary::GUIButton::UpdateDerived()
{
    GUIComponentsLibrary::GUIPanel::UpdateDerived();

    auto mouse_pos{GetNormallizedMousePosition(_<Engine::SDLDevice>().GetWindow())};

    auto hovered{GetBounds().Contains(mouse_pos)};

    if (hovered)
    {
        SetBackgroundImage(m_hoveredBackgroundImage);

        _<Engine::Cursor>().SetCursorStyle(
            Engine::Cursor::CursorStyles::hovering_clickable_gui);

        if (_<Core::Engine::Input::MouseInput::LeftMouseButton>()
                .HasBeenFiredPickResult())
        {
            m_action();
        }
    }
    else
    {
        SetBackgroundImage(m_backgroundImage);
    }
}

void GUIComponentsLibrary::GUIButton::RenderDerived() const
{
    GUIPanel::RenderDerived();

    auto b{GetBounds()};

    _<Engine::Renderers::TextRenderer>().DrawString(
        m_text, b.x + b.w / 2, b.y + b.h / 2, Engine::Renderers::FontSizes::_20,
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
    m_isBeingMoved = true;

    m_moveStartingPosition = GetBounds().GetPosition();

    m_moveStartingMousePosition = GetNormallizedMousePosition(_<Engine::SDLDevice>().GetWindow());
}

void GUIComponentsLibrary::GUIMovablePanel::StopMove()
{
    m_isBeingMoved = false;
}

RectF GUIComponentsLibrary::GUIMovablePanel::GetDragArea()
{
    return GetBounds();
}

void GUIComponentsLibrary::GUIWindow::GUIWindowTitleBar::Initialize()
{
    auto parent_win_b{m_parentWindow.GetBounds()};

    AddChildComponent(std::make_shared<GUIButton>(
        parent_win_b.w - ConvertWidthToHeight(0.015f, _<Engine::SDLDevice>().GetWindow()),
        0.01f, 0.015f, ConvertWidthToHeight(0.015f, _<Engine::SDLDevice>().GetWindow()), "X",
        [this] { m_parentWindow.ToggleVisibility(); }));
}

void GUIComponentsLibrary::GUIWindow::GUIWindowTitleBar::RenderDerived() const
{
    GUIPanel::RenderDerived();

    auto parent_win_b{m_parentWindow.GetBounds()};

    _<Engine::Renderers::TextRenderer>().DrawString(
        k_windowTitle, parent_win_b.x + 0.01f, parent_win_b.y + 0.01f,
        Engine::Renderers::FontSizes::_20, false, Colors::yellow);
}

RectF GUIComponentsLibrary::GUIWindow::GUIWindowTitleBar::GetBounds() const
{
    RectF b_res;

    auto parent_win_b{m_parentWindow.GetBounds()};

    b_res.x = parent_win_b.x;
    b_res.y = parent_win_b.y;
    b_res.w = parent_win_b.w;
    b_res.h = k_h;

    return b_res;
}
void GUIComponentsLibrary::GUIWindow::Initialize(StringView win_title)
{
    SetVisible(false);

    m_guiWindowTitleBar = std::make_shared<GUIWindowTitleBar>(*this, win_title);

    AddChildComponent(m_guiWindowTitleBar);
}

void GUIComponentsLibrary::GUIWindow::RenderDerived() const
{
    GUIMovablePanel::RenderDerived();
}

RectF GUIComponentsLibrary::GUIWindow::GetDragArea()
{
    return m_guiWindowTitleBar->GetBounds();
}

void GUIComponentsLibrary::GUIFPSPanel::Initialize()
{
    m_fpsTextPanel = std::make_shared<GUILabel>(0.01f, 0.01f, 0.1f, 0.05f);

    AddChildComponent(m_fpsTextPanel);
}

void GUIComponentsLibrary::GUIFPSPanel::UpdateDerived()
{
    GUIMovablePanel::UpdateDerived();

    auto fps{_<Engine::FPSCounter>().GetFPS()};

    m_fpsTextPanel->SetText(fmt::format("FPS: {}", fps));
}

void GUIComponentsLibrary::GUIChatBox::RenderDerived() const
{
    GUIPanel::RenderDerived();

    auto b{GetBounds()};

    auto max_num_lines{CInt(b.h / k_lineHeight - 1)};

    auto y{b.y + k_margin};

    for (auto i = 0; i < max_num_lines; i++)
    {
        auto idx{m_lines.size() - max_num_lines + i};

        if (idx < 0 || idx >= m_lines.size())
        {
            continue;
        }

        auto text_line = m_lines.at(idx);

        _<Engine::Renderers::TextRenderer>().DrawString(text_line, b.x + k_margin, y);

        y += k_lineHeight;
    }

    auto sep_rect{RectF{b.x, b.y + b.h - k_lineHeight, b.w, k_separatorHeight}};

    _<Engine::Renderers::Image2DRenderer>().DrawImage(
        "black", sep_rect.x, sep_rect.y, sep_rect.w, sep_rect.h);
}

void GUIComponentsLibrary::GUIChatBox::Print(StringView text)
{
    m_lines.push_back(text.data());
}
_NS_END_