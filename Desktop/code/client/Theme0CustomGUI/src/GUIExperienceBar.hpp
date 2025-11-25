//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "GUIMeter.hpp"

namespace Forradia::Theme0
{
    class GUIExperienceBar : public GUIMeter
    {
      public:
        GUIExperienceBar() : GUIMeter("GUIExperienceBar", 0.0f, 1.0f - k_height, 1.0f, k_height)
        {
        }

        auto GetHeight() const
        {
            return k_height;
        }

      private:
        constexpr static float k_height{0.04f};
    };
}