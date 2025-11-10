//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "GUIMovablePanel.hpp"

namespace Forradia
{
    class GUIWindowTitleBar;

    ///
    /// A window component for the GUI that can be moved by the mouse.
    ///
    class GUIWindow : public GUIMovablePanel
    {
      public:
        ///
        /// Constructor.
        ///
        /// @param uniqueName An unique name for the window.
        /// @param x The x-coordinate of the window.
        /// @param y The y-coordinate of the window.
        /// @param width The width of the window.
        /// @param height The height of the window.
        /// @param windowTitle The title of the window.
        ///
        GUIWindow(StringView uniqueName, float x, float y, float width, float height,
                  StringView windowTitle)
            : GUIMovablePanel(uniqueName, x, y, width, height)
        {
            this->Initialize(uniqueName.data() + String("WindowTitleBar"), windowTitle);
        }

      protected:
        ///
        /// Render tasks specific to the window, called by the GUIComponent base class.
        ///
        void RenderDerived() const override;

        ///
        /// Gets the draggable area for the window. This is the area which the player can drag the
        /// window by.
        ///
        /// @return The draggable area of the window.
        ///
        RectF GetDraggableArea() override;

        ///
        /// Gets the window title bar of the window.
        ///
        /// @return The window title bar of the window.
        ///
        auto GetGUIWindowTitleBar() const
        {
            return m_guiWindowTitleBar;
        }

      private:
        ///
        /// Initializes the window.
        ///
        /// @param uniqueName An unique name for the window.
        /// @param windowTitle The title of the window.
        ///
        void Initialize(StringView uniqueName, StringView windowTitle);

        SharedPtr<GUIWindowTitleBar> m_guiWindowTitleBar; ///< The window title bar of the window.
    };
}