/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "GUIWindowTitleBar.hpp"
    
    #include "ForradiaEngine/Common/Utilities.hpp"
    #include "ForradiaEngine/Common/Matter/Coloring.hpp"
    #include "GUIButton.hpp"
    #include "GUIWindow.hpp"
    #include "ForradiaEngine/GraphicsDevices/SDLDevice.hpp"
    #include "ForradiaEngine/Rendering/Text/TextRenderer.hpp"
// clang-format on

namespace ForradiaEngine
{
    auto GUIWindowTitleBar::initialize(std::string_view uniqueName) -> void
    {
        auto parentWindowBounds{m_parentWindow.getBounds()};

        addChildComponent(std::make_shared<GUIButton>(
            uniqueName.data() + std::string("CloseButton"),
            parentWindowBounds.width - k_closeButtonRightMargin, k_closeButtonTopMargin,
            k_closeButtonWidth,
            convertWidthToHeight(k_closeButtonWidth, SDLDevice::instance().getWindow()), "X",
            [this] { m_parentWindow.toggleVisibility(); }));
    }

    auto GUIWindowTitleBar::renderDerived() const -> void
    {
        GUIPanel::renderDerived();

        auto parentWindowBounds{m_parentWindow.getBounds()};

        TextRenderer::instance().drawString(
            k_renderIDWindowTitleText, k_windowTitle, parentWindowBounds.x + k_titleLeftMargin,
            parentWindowBounds.y + k_titleTopMargin - k_height, FontSizes::_20, false, false,
            Palette::getColor<hash("Yellow")>());
    }

    auto GUIWindowTitleBar::getBounds() const -> RectF
    {
        auto parentWindowBounds{m_parentWindow.getBounds()};

        RectF boundsResult;
        boundsResult.x = parentWindowBounds.x;
        boundsResult.y = parentWindowBounds.y - k_height;
        boundsResult.width = parentWindowBounds.width;
        boundsResult.height = k_height;

        return boundsResult;
    }
}
