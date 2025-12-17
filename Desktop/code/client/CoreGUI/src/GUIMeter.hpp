/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include "GUIComponent.hpp"

namespace Forradia {
/**
 * A meter component for the GUI.
 */
class GUIMeter : public GUIComponent {
 public:
  /**
   * Constructor.
   *
   * @param uniqueName An unique name for the meter.
   * @param x The x-coordinate of the meter.
   * @param y The y-coordinate of the meter.
   * @param width The width of the meter.
   * @param height The height of the meter.
   * @param filledColor The color of the filled part of the meter.
   */
  GUIMeter(StringView uniqueName, float x, float y, float width, float height, Color filledColor)
      : GUIComponent(x, y, width, height), k_renderIDBackground(Hash(uniqueName)),
        k_renderIDFilled(Hash(uniqueName.data() + String("Filled"))), k_filledColor(filledColor) {
  }

 protected:
  /**
   * Render tasks specific to the meter, called by the GUIComponent base class.
   */
  auto RenderDerived() const -> void override;

  /**
   * Gets the filled percentage of the meter.
   *
   * @return The filled percentage of the meter.
   */
  virtual auto GetFilledPercentage() const -> float = 0;

 private:
  const int k_renderIDBackground;
  const int k_renderIDFilled;
  const Color k_filledColor;
};
}
