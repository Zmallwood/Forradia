/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GUIWindowTitleBar.hpp"
#include "GUIButton.hpp"
#include "GUIWindow.hpp"
#include "SDLDevice.hpp"
#include "TextRenderer.hpp"

namespace Forradia {
    auto GUIWindowTitleBar::Initialize(std::string_view uniqueName) -> void {
        auto parentWindowBounds{m_parentWindow.GetBounds()};
        AddChildComponent(std::make_shared<GUIButton>(
            uniqueName.data() + std::string("CloseButton"),
            parentWindowBounds.width - ConvertWidthToHeight(0.015F, _<SDLDevice>().GetWindow()),
            0.01F, 0.015F, ConvertWidthToHeight(0.015F, _<SDLDevice>().GetWindow()), "X",
            [this] { m_parentWindow.ToggleVisibility(); }));
    }

    auto GUIWindowTitleBar::RenderDerived() const -> void {
        GUIPanel::RenderDerived();

        auto parentWindowBounds{m_parentWindow.GetBounds()};
        _<TextRenderer>().DrawString(k_renderIDWindowTitleText, k_windowTitle,
                                     parentWindowBounds.x + 0.01F,
                                     parentWindowBounds.y + 0.01F - k_height, FontSizes::_20, false,
                                     false, Palette::GetColor<Hash("Yellow")>());
    }

    auto GUIWindowTitleBar::GetBounds() const -> RectF {
        auto parentWindowBounds{m_parentWindow.GetBounds()};

        RectF boundsResult;
        boundsResult.x = parentWindowBounds.x;
        boundsResult.y = parentWindowBounds.y - k_height;
        boundsResult.width = parentWindowBounds.width;
        boundsResult.height = k_height;
        return boundsResult;
    }
}
