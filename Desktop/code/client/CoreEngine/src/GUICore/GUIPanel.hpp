/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "GUIComponent.hpp"
#include "Hash.hpp"

namespace Forradia
{
    /**
     *  A panel component for the GUI.
     */
    class GUIPanel : public GUIComponent
    {
      public:
        /**
         *  Constructor.
         *
         *  @param uniqueName A unique name for the panel.
         *  @param xPos The x-coordinate of the panel.
         *  @param yPos The y-coordinate of the panel.
         *  @param width The width of the panel.
         *  @param height The height of the panel.
         *  @param backgroundImage The background image of the panel.
         */
        GUIPanel(std::string_view uniqueName, float xPos, float yPos, float width, float height,
                 std::string_view backgroundImage = k_defaultBackgroundImage)
            : GUIComponent(xPos, yPos, width, height), k_renderIDBackground(hash(uniqueName)),
              m_backgroundImage(backgroundImage)
        {
        }

        /**
         *  Render tasks specific to the panel, called by the GUIComponent base class.
         */
        auto renderDerived() const -> void override;

        /**
         *  Sets the background image of the panel.
         *
         *  @param value The new background image.
         */
        auto setBackgroundImage(std::string_view value) -> void
        {
            m_backgroundImage = value;
        }

      private:
        inline static const std::string k_defaultBackgroundImage{"GUIPanelBackground"};
        const int k_renderIDBackground{};
        std::string m_backgroundImage{};
    };
}
