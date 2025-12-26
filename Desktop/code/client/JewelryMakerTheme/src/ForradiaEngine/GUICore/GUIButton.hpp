/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include "GUIPanel.hpp"
    #include "ForradiaEngine/Common/General.hpp"
    #include <functional>
// clang-format on

namespace ForradiaEngine
{
    /**
     *  A button component for the GUI.
     */
    class GUIButton : public GUIPanel
    {
      public:
        /**
         *  Constructor.
         *
         *  @param uniqueName A unique name for the button.
         *  @param xPos The x-coordinate of the button.
         *  @param yPos The y-coordinate of the button.
         *  @param width The width of the button.
         *  @param height The height of the button.
         *  @param text The text to display on the button.
         *  @param action The action to perform when the button is clicked.
         *  @param backgroundImage The background image of the button.
         *  @param hoveredBackgroundImage The background image of the button when hovered.
         */
        GUIButton(std::string_view uniqueName, float xPos, float yPos, float width, float height,
                  std::string_view text, std::function<void()> action,
                  std::string_view backgroundImage = k_defaultBackgroundImage,
                  std::string_view hoveredBackgroundImage = k_defaultHoveredBackgroundImage)
            : GUIPanel(uniqueName, xPos, yPos, width, height),
              k_renderIDText(hash(uniqueName.data() + std::string("Text"))), m_text(text),
              m_action(std::move(action)), m_backgroundImage(backgroundImage),
              m_hoveredBackgroundImage(hoveredBackgroundImage)
        {
        }

      protected:
        auto onMouseUp(Uint8 mouseButton, int clickSpeed) -> bool override;

        /**
         *  Update tasks specific to the button, called by the GUIComponent base class.
         */
        auto updateDerived() -> void override;

        /**
         *  Render tasks specific to the button, called by the GUIComponent base class.
         */
        auto renderDerived() const -> void override;

      private:
        inline static const std::string k_defaultBackgroundImage{"GUIButtonBackground"};
        inline static const std::string k_defaultHoveredBackgroundImage{
            "GUIButtonHoveredBackground"};
        const int k_renderIDText{};
        std::string m_text{};
        std::function<void()> m_action{};
        std::string m_backgroundImage{};
        std::string m_hoveredBackgroundImage{};
    };
}
