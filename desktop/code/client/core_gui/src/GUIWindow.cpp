//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "GUIWindow.hpp"

#include "GUIButton.hpp"

#include "SDLDevice.hpp"

#include "TextRenderer.hpp"

namespace Forradia
{
    void GUIWindow::GUIWindowTitleBar::Initialize(StringView uniqueName)
    {
        auto parentWindowBounds{m_parentWindow.GetBounds()};

        AddChildComponent(std::make_shared<GUIButton>(
            uniqueName.data() + String("CloseButton"),
            parentWindowBounds.width - ConvertWidthToHeight(0.015f, _<SDLDevice>().GetWindow()),
            0.01f, 0.015f, ConvertWidthToHeight(0.015f, _<SDLDevice>().GetWindow()), "X",
            [this] { m_parentWindow.ToggleVisibility(); }));
    }

    void GUIWindow::GUIWindowTitleBar::RenderDerived() const
    {
        GUIPanel::RenderDerived();

        auto parentWindowBounds{m_parentWindow.GetBounds()};

        _<TextRenderer>().DrawString(k_renderIDWindowTitleText, k_windowTitle,
                                     parentWindowBounds.x + 0.01f, parentWindowBounds.y + 0.01f,
                                     FontSizes::_20, false, false,
                                     Palette::GetColor<Hash("Yellow")>());
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
    void GUIWindow::Initialize(StringView uniqueName, StringView windowTitle)
    {
        this->SetVisible(false);

        m_guiWindowTitleBar = std::make_shared<GUIWindowTitleBar>(uniqueName, *this, windowTitle);

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