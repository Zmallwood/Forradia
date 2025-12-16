/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once

#include "Coloring/Palette.hpp"
#include "GUIMeter.hpp"

namespace Forradia::Theme0 {
class GUIExperienceBar : public GUIMeter {
 public:
  GUIExperienceBar()
      : GUIMeter("GUIExperienceBar", 0.0f, 1.0f - k_height, 1.0f, k_height, GetFilledColor()) {
  }

  auto GetHeight() const {
    return k_height;
  }

 protected:
  void UpdateDerived() override;

  float GetFilledPercentage() const override;

  Color GetFilledColor() const {
    return Palette::GetColor<Hash("Yellow")>();
  }

 private:
  constexpr static float k_height{0.018f};
  float m_filledPercentage{0.0f};
};
}