/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include "GUIComponent.hpp"

namespace Forradia {
  /**
   * A panel component for the GUI.
   */
  class GUIPanel : public GUIComponent {
   public:
    /**
     * Constructor.
     *
     * @param uniqueName An unique name for the panel.
     * @param x The x-coordinate of the panel.
     * @param y The y-coordinate of the panel.
     * @param width The width of the panel.
     * @param height The height of the panel.
     * @param backgroundImage The background image of the panel.
     */
    GUIPanel(StringView uniqueName, float x, float y, float width, float height,
             StringView backgroundImage = k_defaultBackgroundImage)
        : GUIComponent(x, y, width, height), k_renderIDBackground(Hash(uniqueName)),
          m_backgroundImage(backgroundImage) {
    }

   protected:
    /**
     * Render tasks specific to the panel, called by the GUIComponent base class.
     */
    virtual auto RenderDerived() const -> void override;

    /**
     * Sets the background image of the panel.
     *
     * @param value The new background image.
     */
    auto SetBackgroundImage(StringView value) -> void {
      m_backgroundImage = value;
    }

   private:
    inline static const String k_defaultBackgroundImage{"GUIPanelBackground"};
    const int k_renderIDBackground;
    String m_backgroundImage;
  };
}
