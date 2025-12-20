/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once
#include "Coloring/Color.hpp"
#include "Coloring/Palette.hpp"
#include "GUIComponent.hpp"
#include "Hash.hpp"

namespace Forradia {
    /**
     * A label component for the GUI.
     */
    class GUILabel : public GUIComponent {
      public:
        /**
         * Constructor.
         *
         * @param uniqueName An unique name for the label.
         * @param x The x-coordinate of the label.
         * @param y The y-coordinate of the label.
         * @param width The width of the label.
         * @param height The height of the label.
         * @param text The text to display on the label.
         * @param centerAlign Whether to center the text.
         * @param color The color of the text.
         */
        GUILabel(std::string_view uniqueName, float xPos, float yPos, float width, float height,
                 std::string_view text = "", bool centerAlign = false,
                 Color color = Palette::GetColor<Hash("WheatTransparent")>())
            : GUIComponent(xPos, yPos, width, height), k_renderIDText(Hash(uniqueName)),
              m_text(text), m_centerAlign(centerAlign), m_color(color) {
        }

        /**
         * Sets the text of the label.
         *
         * @param value The new text.
         */
        auto SetText(std::string_view value) -> void {
            m_text = value;
        }

      protected:
        /**
         * Render tasks specific to the label, called by the GUIComponent base class.
         */
        auto RenderDerived() const -> void override;

      private:
        const int k_renderIDText;
        std::string m_text;
        bool m_centerAlign{false};
        Color m_color;
    };
}
