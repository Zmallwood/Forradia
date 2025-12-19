/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include "GUIPanel.hpp"

namespace Forradia {
  class GUIWindow;

  /**
   * A title bar for a window.
   */
  class GUIWindowTitleBar : public GUIPanel {
   public:
    /**
     * Constructor.
     *
     * @param uniqueName An unique name for the title bar.
     * @param parentWindow The parent window of the title bar.
     * @param windowTitle The title of the window.
     */
    GUIWindowTitleBar(std::string_view uniqueName, GUIWindow &parentWindow,
                      std::string_view windowTitle)
        : m_parentWindow(parentWindow), k_windowTitle(windowTitle),
          k_renderIDWindowTitleText(Hash(uniqueName.data() + std::string("WindowTitleText"))),
          GUIPanel(uniqueName, 0.0f, 0.0f, 0.0f, 0.0f, "GUIWindowTitleBarBackground") {
      this->Initialize(uniqueName);
    }

    /**
     * Render tasks specific to the title bar, called by the GUIComponent base class.
     */
    auto RenderDerived() const -> void override;

    /**
     * Gets the bounds of the title bar.
     *
     * @return The bounds of the title bar.
     */
    auto GetBounds() const -> RectF override;

    auto GetHeight() const -> float {
      return k_height;
    }

   private:
    auto Initialize(std::string_view uniqueName) -> void;

    inline static const float k_height{0.04f};
    const std::string k_windowTitle;
    const int k_renderIDWindowTitleText;
    GUIWindow &m_parentWindow;
  };
}
