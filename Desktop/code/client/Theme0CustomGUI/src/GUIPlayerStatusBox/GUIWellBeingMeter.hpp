//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "GUIMeter.hpp"

namespace AAK
{
    namespace Forradia::Theme0
    {
        class GUIWellBeingMeter : public GUIMeter
        {
          public:
            GUIWellBeingMeter(float x, float y, float width, float height)
                : GUIMeter("GUIWellBeingMeter", x, y, width, height, GetFilledColor())
            {
            }

            auto GetHeight() const
            {
                return k_height;
            }

          protected:
            void UpdateDerived() override;

            float GetFilledPercentage() const override;

            Color GetFilledColor() const
            {
                return Palette::GetColor<Hash("Red")>();
            }

          private:
            constexpr static float k_height{0.02f};

            float m_filledPercentage{0.0f};
        };
    }
}