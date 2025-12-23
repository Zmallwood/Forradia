/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "GUIMovablePanel.hpp"

namespace Forradia
{
    class GUIWindowTitleBar;

    /**
        A window component for the GUI that can be moved by the mouse.
     */
    class GUIWindow : public GUIMovablePanel
    {
      public:
        /**
            Constructor.

            @param uniqueName A unique name for the window.
            @param xPos The x-coordinate of the window.
            @param yPos The y-coordinate of the window.
            @param width The width of the window.
            @param height The height of the window.
            @param windowTitle The title of the window.
         */
        GUIWindow(std::string_view uniqueName, float xPos, float yPos, float width, float height,
                  std::string_view windowTitle)
            : GUIMovablePanel(uniqueName, xPos + s_positionOffset, yPos + s_positionOffset, width,
                              height)
        {
            this->Initialize(uniqueName.data() + std::string("WindowTitleBar"), windowTitle);
        }

        /**
            Gets the window title bar of the window.

            @return The window title bar of the window.
         */
        auto GetGUIWindowTitleBar() const
        {
            return m_guiWindowTitleBar;
        }

      protected:
        /**
            Render tasks specific to the window, called by the GUIComponent base class.
         */
        auto RenderDerived() const -> void override;

        /**
            Gets the draggable area for the window. This is the area which the player can drag
            the window by.

            @return The draggable area of the window.
         */
        auto GetDraggableArea() const -> RectF override;

      private:
        auto Initialize(std::string_view uniqueName, std::string_view windowTitle) -> void;

        constexpr static float k_positionOffsetChange{0.05F};
        inline static float s_positionOffset{0.0F};
        std::shared_ptr<GUIWindowTitleBar> m_guiWindowTitleBar{};
    };
}
