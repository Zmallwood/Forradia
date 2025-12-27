/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "GUIPanel.hpp"

namespace ForradiaEngine
{
    class GUIWindow;

    /**
     *  A title bar for a window.
     */
    class GUIWindowTitleBar : public GUIPanel
    {
      public:
        /**
         *  Constructor.
         *
         *  @param uniqueName A unique name for the title bar.
         *  @param parentWindow The parent window of the title bar.
         *  @param windowTitle The title of the window.
         */
        GUIWindowTitleBar(std::string_view uniqueName, GUIWindow &parentWindow,
                          std::string_view windowTitle)
            : GUIPanel(uniqueName, 0.0F, 0.0F, 0.0F, 0.0F, "GUIWindowTitleBarBackground"),
              k_windowTitle(windowTitle),
              k_renderIDWindowTitleText(hash(uniqueName.data() + std::string("WindowTitleText"))),
              m_parentWindow(parentWindow)
        {
            this->initialize(uniqueName);
        }

        /**
         *  Render tasks specific to the title bar, called by the GUIComponent base class.
         */
        auto renderDerived() const -> void override;

        /**
         *  Gets the bounds of the title bar.
         *
         *  @return The bounds of the title bar.
         */
        auto getBounds() const -> RectF override;

        static auto getHeight() -> float
        {
            return k_height;
        }

      private:
        auto initialize(std::string_view uniqueName) -> void;

        constexpr static float k_height{0.04F};
        const std::string k_windowTitle{};
        const float k_closeButtonTopMargin{0.01F};
        const float k_closeButtonRightMargin{0.02F};
        const float k_closeButtonWidth{0.015F};
        const float k_titleTopMargin{0.01F};
        const float k_titleLeftMargin{0.01F};
        const int k_renderIDWindowTitleText{};
        GUIWindow &m_parentWindow;
    };
}
