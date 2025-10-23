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

    for (auto component : std::views::reverse(m_childComponents))
    {
        component->Update();
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

    for (auto component : m_childComponents)
    {
        component->Render();
    }
}

RectF GUIComponentsLibrary::GUIComponent::GetBounds() const
{
    auto boundsResult{m_bounds};

    if (m_parentComponent)
    {
        auto parentPosition{m_parentComponent->GetBounds().GetPosition()};

        boundsResult.Offset(parentPosition);
    }

    return boundsResult;
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
    auto bounds{GetBounds()};

    auto x{bounds.x};
    auto y{bounds.y};

    if (m_centerAlign)
    {
        bounds.x += bounds.width / 2;
        bounds.y += bounds.height / 2;
    }

    _<Engine::Renderers::TextRenderer>().DrawString(
        m_text, bounds.x, bounds.y, Engine::Renderers::FontSizes::_20,
        m_centerAlign, m_color);
}

void GUIComponentsLibrary::GUIPanel::RenderDerived() const
{
    auto bounds{GetBounds()};

    _<Engine::Renderers::Image2DRenderer>().DrawImage(
        m_backgroundImage, bounds.x, bounds.y, bounds.width, bounds.height);
}

void GUIComponentsLibrary::GUIButton::UpdateDerived()
{
    GUIComponentsLibrary::GUIPanel::UpdateDerived();

    auto mousePosition{
        GetNormallizedMousePosition(_<Engine::SDLDevice>().GetWindow())};

    auto hovered{GetBounds().Contains(mousePosition)};

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

    auto bounds{GetBounds()};

    _<Engine::Renderers::TextRenderer>().DrawString(
        m_text, bounds.x + bounds.width / 2, bounds.y + bounds.height / 2,
        Engine::Renderers::FontSizes::_20, true);
}

void GUIComponentsLibrary::GUIMovablePanel::UpdateDerived()
{
    auto mousePosition{
        GetNormallizedMousePosition(_<Engine::SDLDevice>().GetWindow())};

    auto dragArea{GetDragArea()};

    if (dragArea.Contains(mousePosition))
    {
        _<Engine::Cursor>().SetCursorStyle(
            Engine::Cursor::CursorStyles::hovering_clickable_gui);

        if (_<Core::Engine::Input::MouseInput::LeftMouseButton>()
                .HasBeenFiredPickResult())
        {
            StartMove();
        }
    }

    if (_<Core::Engine::Input::MouseInput::LeftMouseButton>().HasBeenReleased())
    {
        StopMove();
    }

    auto bounds{GetBounds()};

    if (bounds.Contains(mousePosition))
    {
        if (_<Core::Engine::Input::MouseInput::LeftMouseButton>()
                .HasBeenFired())
        {
            _<Core::Engine::Input::MouseInput::LeftMouseButton>().Reset();
        }
    }
    if (GetIsBeingMoved())
    {
        auto currentMousePosition{
            GetNormallizedMousePosition(_<Engine::SDLDevice>().GetWindow())};

        auto newPosition{GetMoveStartingPosition() + currentMousePosition -
                         GetMoveStartingMousePosition()};

        SetPosition(newPosition);
    }
}

void GUIComponentsLibrary::GUIMovablePanel::StartMove()
{
    m_isBeingMoved = true;

    m_moveStartingPosition = GetBounds().GetPosition();

    m_moveStartingMousePosition =
        GetNormallizedMousePosition(_<Engine::SDLDevice>().GetWindow());
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
    auto parentWindowBounds{m_parentWindow.GetBounds()};

    AddChildComponent(std::make_shared<GUIButton>(
        parentWindowBounds.width -
            ConvertWidthToHeight(0.015f, _<Engine::SDLDevice>().GetWindow()),
        0.01f, 0.015f,
        ConvertWidthToHeight(0.015f, _<Engine::SDLDevice>().GetWindow()), "X",
        [this] { m_parentWindow.ToggleVisibility(); }));
}

void GUIComponentsLibrary::GUIWindow::GUIWindowTitleBar::RenderDerived() const
{
    GUIPanel::RenderDerived();

    auto parentWindowBounds{m_parentWindow.GetBounds()};

    _<Engine::Renderers::TextRenderer>().DrawString(
        k_windowTitle, parentWindowBounds.x + 0.01f,
        parentWindowBounds.y + 0.01f, Engine::Renderers::FontSizes::_20, false,
        Colors::yellow);
}

RectF GUIComponentsLibrary::GUIWindow::GUIWindowTitleBar::GetBounds() const
{
    RectF boundsResult;

    auto parentWindowBounds{m_parentWindow.GetBounds()};

    boundsResult.x = parentWindowBounds.x;
    boundsResult.y = parentWindowBounds.y;
    boundsResult.width = parentWindowBounds.width;
    boundsResult.height = k_h;

    return boundsResult;
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

    auto bounds{GetBounds()};

    auto maxNumLines{CInt(bounds.height / k_lineHeight - 1)};

    auto y{bounds.y + k_margin};

    for (auto i = 0; i < maxNumLines; i++)
    {
        auto index{m_lines.size() - maxNumLines + i};

        if (index < 0 || index >= m_lines.size())
        {
            continue;
        }

        auto textLine = m_lines.at(index);

        _<Engine::Renderers::TextRenderer>().DrawString(textLine,
                                                        bounds.x + k_margin, y);

        y += k_lineHeight;
    }

    auto separatorRect{RectF{bounds.x, bounds.y + bounds.height - k_lineHeight,
                             bounds.width, k_separatorHeight}};

    _<Engine::Renderers::Image2DRenderer>().DrawImage(
        "black", separatorRect.x, separatorRect.y, separatorRect.width,
        separatorRect.height);
}

void GUIComponentsLibrary::GUIChatBox::Print(StringView text)
{
    m_lines.push_back(text.data());
}
_NS_END_