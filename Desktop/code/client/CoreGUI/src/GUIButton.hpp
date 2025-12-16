/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include "GUIPanel.hpp"

namespace Forradia {
///
/// A button component for the GUI.
///
class GUIButton : public GUIPanel {
 public:
  ///
  /// Constructor.
  ///
  /// @param uniqueName An unique name for the button.
  /// @param x The x-coordinate of the button.
  /// @param y The y-coordinate of the button.
  /// @param width The width of the button.
  /// @param height The height of the button.
  /// @param text The text to display on the button.
  /// @param action The action to perform when the button is clicked.
  /// @param backgroundImage The background image of the button.
  /// @param hoveredBackgroundImage The background image of the button when hovered.
  ///
  GUIButton(StringView uniqueName, float x, float y, float width, float height, StringView text,
            Function<void()> action, StringView backgroundImage = k_defaultBackgroundImage,
            StringView hoveredBackgroundImage = k_defaultHoveredBackgroundImage)
      : GUIPanel(uniqueName, x, y, width, height),
        k_renderIDText(Hash(uniqueName.data() + String("Text"))), m_text(text), m_action(action),
        m_backgroundImage(backgroundImage), m_hoveredBackgroundImage(hoveredBackgroundImage) {
  }

 protected:
  ///
  /// Update tasks specific to the button, called by the GUIComponent base class.
  ///
  virtual void UpdateDerived() override;

  ///
  /// Render tasks specific to the button, called by the GUIComponent base class.
  ///
  virtual void RenderDerived() const override;

 private:
  inline static const String k_defaultBackgroundImage{
      "GUIButtonBackground"}; ///< The default background image of the button when not
                              ///< hovered.

  inline static const String k_defaultHoveredBackgroundImage{
      "GUIButtonHoveredBackground"}; ///< The default background image of the button when
                                     ///< hovered.

  const int k_renderIDText;        ///< The render ID of the text.
  String m_text;                   ///< The text to display on the button.
  Function<void()> m_action;       ///< The action to perform when the button is clicked.
  String m_backgroundImage;        ///< The background image of the button when not hovered.
  String m_hoveredBackgroundImage; ///< The background image of the button when hovered.
};
}