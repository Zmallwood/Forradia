//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "GUIWindow.hpp"

#include "GUIButton.hpp"

#include "SDLDevice.hpp"

#include "Rendering.hpp"

namespace Forradia
{
    void GUIWindow::GUIWindowTitleBar::Initialize()
    {
        auto parentWindowBounds{m_parentWindow.GetBounds()};

        AddChildComponent(std::make_shared<GUIButton>(
            parentWindowBounds.width -
                ConvertWidthToHeight(
                    0.015f, _<SDLDevice>().GetWindow()),
            0.01f, 0.015f,
            ConvertWidthToHeight(
                0.015f, _<SDLDevice>().GetWindow()),
            "X",
            [this] { m_parentWindow.ToggleVisibility(); }));
    }

    void GUIWindow::GUIWindowTitleBar::RenderDerived() const
    {
        GUIPanel::RenderDerived();

        auto parentWindowBounds{m_parentWindow.GetBounds()};

        _<RenderersCollection::TextRenderer>().DrawString(
            k_windowTitle, parentWindowBounds.x + 0.01f,
            parentWindowBounds.y + 0.01f,
            RenderersCollection::FontSizes::_20, false,
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
        this->SetVisible(false);

        m_guiWindowTitleBar =
            std::make_shared<GUIWindowTitleBar>(
                *this, windowTitle);

        this->AddChildComponent(m_guiWindowTitleBar);
    }

    void GUIWindow::RenderDerived() const
    {
        GUIMovablePanel::RenderDerived();
    }

    RectF GUIWindow::GetDragArea()
    {
        return m_guiWindowTitleBar->GetBounds();
    }
}