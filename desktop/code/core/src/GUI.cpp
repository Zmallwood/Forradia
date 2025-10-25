//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "GUI.hpp"
#include "Core.hpp"
#include "Render.hpp"

namespace Forradia
{
    SharedPtr<GUIComponent> GUIComponent::AddChildComponent(
        SharedPtr<GUIComponent> component)
    {
        component->SetParentComponent(this);

        m_childComponents.push_back(component);

        return component;
    }

    void GUIComponent::Update()
    {
        if (!m_visible || !m_enabled)
        {
            return;
        }

        for (auto component :
             std::views::reverse(m_childComponents))
        {
            component->Update();
        }

        UpdateDerived();
    }

    void GUIComponent::Render() const
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

    RectF GUIComponent::GetBounds() const
    {
        auto boundsResult{m_bounds};

        if (m_parentComponent)
        {
            auto parentPosition{
                m_parentComponent->GetBounds()
                    .GetPosition()};

            boundsResult.Offset(parentPosition);
        }

        return boundsResult;
    }

    void GUIComponent::ToggleVisibility()
    {
        m_visible = !m_visible;
    }

    void GUIComponent::SetPosition(PointF newPosition)
    {
        m_bounds.x = newPosition.x;
        m_bounds.y = newPosition.y;
    }

    void GUILabel::RenderDerived() const
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
            m_text, bounds.x, bounds.y,
            Engine::Renderers::FontSizes::_20,
            m_centerAlign, m_color);
    }

    void GUIPanel::RenderDerived() const
    {
        auto bounds{GetBounds()};

        _<Engine::Renderers::Image2DRenderer>().DrawImage(
            m_backgroundImage, bounds.x, bounds.y,
            bounds.width, bounds.height);
    }

    void GUIButton::UpdateDerived()
    {
        GUIPanel::UpdateDerived();

        auto mousePosition{GetNormallizedMousePosition(
            _<Engine::SDLDevice>().GetWindow())};

        auto hovered{GetBounds().Contains(mousePosition)};

        if (hovered)
        {
            SetBackgroundImage(m_hoveredBackgroundImage);

            _<Engine::Cursor>().SetCursorStyle(
                Engine::Cursor::CursorStyles::
                    HoveringClickableGUI);

            if (_<Engine::Input::MouseInput::
                      LeftMouseButton>()
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

    void GUIButton::RenderDerived() const
    {
        GUIPanel::RenderDerived();

        auto bounds{GetBounds()};

        _<Engine::Renderers::TextRenderer>().DrawString(
            m_text, bounds.x + bounds.width / 2,
            bounds.y + bounds.height / 2,
            Engine::Renderers::FontSizes::_20, true);
    }

    void GUIMovablePanel::UpdateDerived()
    {
        auto mousePosition{GetNormallizedMousePosition(
            _<Engine::SDLDevice>().GetWindow())};

        auto dragArea{GetDragArea()};

        if (dragArea.Contains(mousePosition))
        {
            _<Engine::Cursor>().SetCursorStyle(
                Engine::Cursor::CursorStyles::
                    HoveringClickableGUI);

            if (_<Engine::Input::MouseInput::
                      LeftMouseButton>()
                    .HasBeenFiredPickResult())
            {
                StartMove();
            }
        }

        if (_<Engine::Input::MouseInput::LeftMouseButton>()
                .HasBeenReleased())
        {
            StopMove();
        }

        auto bounds{GetBounds()};

        if (bounds.Contains(mousePosition))
        {
            if (_<Engine::Input::MouseInput::
                      LeftMouseButton>()
                    .HasBeenFired())
            {
                _<Engine::Input::MouseInput::
                      LeftMouseButton>()
                    .Reset();
            }
        }
        if (GetIsBeingMoved())
        {
            auto currentMousePosition{
                GetNormallizedMousePosition(
                    _<Engine::SDLDevice>().GetWindow())};

            auto newPosition{
                GetMoveStartingPosition() +
                currentMousePosition -
                GetMoveStartingMousePosition()};

            SetPosition(newPosition);
        }
    }

    void GUIMovablePanel::StartMove()
    {
        m_isBeingMoved = true;

        m_moveStartingPosition = GetBounds().GetPosition();

        m_moveStartingMousePosition =
            GetNormallizedMousePosition(
                _<Engine::SDLDevice>().GetWindow());
    }

    void GUIMovablePanel::StopMove()
    {
        m_isBeingMoved = false;
    }

    RectF GUIMovablePanel::GetDragArea()
    {
        return GetBounds();
    }

    void GUIWindow::GUIWindowTitleBar::Initialize()
    {
        auto parentWindowBounds{m_parentWindow.GetBounds()};

        AddChildComponent(std::make_shared<GUIButton>(
            parentWindowBounds.width -
                ConvertWidthToHeight(
                    0.015f,
                    _<Engine::SDLDevice>().GetWindow()),
            0.01f, 0.015f,
            ConvertWidthToHeight(
                0.015f, _<Engine::SDLDevice>().GetWindow()),
            "X",
            [this] { m_parentWindow.ToggleVisibility(); }));
    }

    void GUIWindow::GUIWindowTitleBar::RenderDerived() const
    {
        GUIPanel::RenderDerived();

        auto parentWindowBounds{m_parentWindow.GetBounds()};

        _<Engine::Renderers::TextRenderer>().DrawString(
            k_windowTitle, parentWindowBounds.x + 0.01f,
            parentWindowBounds.y + 0.01f,
            Engine::Renderers::FontSizes::_20, false,
            Colors::Yellow);
    }

    RectF GUIWindow::GUIWindowTitleBar::GetBounds() const
    {
        RectF boundsResult;

        auto parentWindowBounds{m_parentWindow.GetBounds()};

        boundsResult.x = parentWindowBounds.x;
        boundsResult.y = parentWindowBounds.y;
        boundsResult.width = parentWindowBounds.width;
        boundsResult.height = k_h;

        return boundsResult;
    }
    void GUIWindow::Initialize(StringView windowTitle)
    {
        SetVisible(false);

        m_guiWindowTitleBar =
            std::make_shared<GUIWindowTitleBar>(
                *this, windowTitle);

        AddChildComponent(m_guiWindowTitleBar);
    }

    void GUIWindow::RenderDerived() const
    {
        GUIMovablePanel::RenderDerived();
    }

    RectF GUIWindow::GetDragArea()
    {
        return m_guiWindowTitleBar->GetBounds();
    }

    void GUIFPSPanel::Initialize()
    {
        m_fpsTextPanel = std::make_shared<GUILabel>(
            0.01f, 0.01f, 0.1f, 0.05f);

        AddChildComponent(m_fpsTextPanel);
    }

    void GUIFPSPanel::UpdateDerived()
    {
        GUIMovablePanel::UpdateDerived();

        auto fps{_<Engine::FPSCounter>().GetFPS()};

        m_fpsTextPanel->SetText(
            fmt::format("FPS: {}", fps));
    }

    void GUIChatBox::RenderDerived() const
    {
        GUIPanel::RenderDerived();

        auto bounds{GetBounds()};

        auto maxNumLines{
            CInt(bounds.height / k_lineHeight - 1)};

        auto y{bounds.y + k_margin};

        for (auto i = 0; i < maxNumLines; i++)
        {
            auto index{m_lines.size() - maxNumLines + i};

            if (index < 0 || index >= m_lines.size())
            {
                continue;
            }

            auto textLine = m_lines.at(index);

            _<Engine::Renderers::TextRenderer>().DrawString(
                textLine, bounds.x + k_margin, y);

            y += k_lineHeight;
        }

        auto separatorRect{
            RectF{bounds.x,
                  bounds.y + bounds.height - k_lineHeight,
                  bounds.width, k_separatorHeight}};

        _<Engine::Renderers::Image2DRenderer>().DrawImage(
            "black", separatorRect.x, separatorRect.y,
            separatorRect.width, separatorRect.height);
    }

    void GUIChatBox::Print(StringView text)
    {
        m_lines.push_back(text.data());
    }
}