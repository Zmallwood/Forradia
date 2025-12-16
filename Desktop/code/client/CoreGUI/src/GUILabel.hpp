//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#pragma once

#include "GUIComponent.hpp"

namespace Forradia {
///
/// A label component for the GUI.
///
class GUILabel : public GUIComponent {
 public:
  ///
  /// Constructor.
  ///
  /// @param uniqueName An unique name for the label.
  /// @param x The x-coordinate of the label.
  /// @param y The y-coordinate of the label.
  /// @param width The width of the label.
  /// @param height The height of the label.
  /// @param text The text to display on the label.
  /// @param centerAlign Whether to center the text.
  /// @param color The color of the text.
  ///
  GUILabel(StringView uniqueName, float x, float y, float width, float height, StringView text = "",
           bool centerAlign = false, Color color = Palette::GetColor<Hash("WheatTransparent")>())
      : GUIComponent(x, y, width, height), k_renderIDText(Hash(uniqueName)), m_text(text),
        m_centerAlign(centerAlign), m_color(color) {
  }

  ///
  /// Sets the text of the label.
  ///
  /// @param value The new text.
  ///
  void SetText(StringView value) {
    m_text = value;
  }

 protected:
  ///
  /// Render tasks specific to the label, called by the GUIComponent base class.
  ///
  virtual void RenderDerived() const override;

 private:
  const int k_renderIDText;  ///< The render ID of the text.
  String m_text;             ///< The text of the label.
  bool m_centerAlign{false}; ///< Whether to center the text.
  Color m_color;             ///< The color of the text.
};
}