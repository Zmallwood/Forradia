/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "GUIMovablePanel.hpp"

namespace Forradia {
    class GUIWindowTitleBar;

    /**
     * A window component for the GUI that can be moved by the mouse.
     */
    class GUIWindow : public GUIMovablePanel {
      public:
        /**
         * Constructor.
         *
         * @param uniqueName An unique name for the window.
         * @param x The x-coordinate of the window.
         * @param y The y-coordinate of the window.
         * @param width The width of the window.
         * @param height The height of the window.
         * @param windowTitle The title of the window.
         */
        GUIWindow(std::string_view uniqueName, float x, float y, float width, float height,
                  std::string_view windowTitle)
            : GUIMovablePanel(uniqueName, x, y, width, height) {
            this->Initialize(uniqueName.data() + std::string("WindowTitleBar"), windowTitle);
        }

        /**
         * Gets the window title bar of the window.
         *
         * @return The window title bar of the window.
         */
        auto GetGUIWindowTitleBar() const {
            return m_guiWindowTitleBar;
        }

      protected:
        /**
         * Render tasks specific to the window, called by the GUIComponent base class.
         */
        auto RenderDerived() const -> void override;

        /**
         * Gets the draggable area for the window. This is the area which the player can drag
         * the window by.
         *
         * @return The draggable area of the window.
         */
        auto GetDraggableArea() const -> RectF override;

      private:
        auto Initialize(std::string_view uniqueName, std::string_view windowTitle) -> void;

        std::shared_ptr<GUIWindowTitleBar> m_guiWindowTitleBar;
    };
}
