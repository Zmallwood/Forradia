//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "GUIPanel.hpp"

namespace Forradia
{
    class GUIWindow;

    ///
    /// A title bar for a window.
    ///
    class GUIWindowTitleBar : public GUIPanel
    {
      public:
        ///
        /// Constructor.
        ///
        /// @param uniqueName An unique name for the title bar.
        /// @param parentWindow The parent window of the title bar.
        /// @param windowTitle The title of the window.
        ///
        GUIWindowTitleBar(StringView uniqueName, GUIWindow &parentWindow, StringView windowTitle)
            : m_parentWindow(parentWindow), k_windowTitle(windowTitle),
              k_renderIDWindowTitleText(Hash(uniqueName.data() + String("WindowTitleText"))),
              GUIPanel(uniqueName, 0.0f, 0.0f, 0.0f, 0.0f, "GUIWindowTitleBarBackground")
        {
            this->Initialize(uniqueName);
        }

        ///
        /// Render tasks specific to the title bar, called by the GUIComponent base class.
        ///
        void RenderDerived() const override;

        ///
        /// Gets the bounds of the title bar.
        ///
        /// @return The bounds of the title bar.
        ///
        RectF GetBounds() const override;

      private:
        ///
        /// Initializes the title bar.
        ///
        /// @param uniqueName An unique name for the title bar.
        ///
        void Initialize(StringView uniqueName);

        inline static const float k_height{0.04f}; ///< The height of the title bar.

        const String k_windowTitle; ///< The title of the window.

        const int k_renderIDWindowTitleText; ///< The render ID of the window title text.

        GUIWindow &m_parentWindow; ///< The parent window of the title bar.
    };
}