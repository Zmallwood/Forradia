//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "GUIComponent.hpp"

namespace Forradia
{
    ///
    /// A meter component for the GUI.
    ///
    class GUIMeter : public GUIComponent
    {
      public:
        GUIMeter(StringView uniqueName, float x, float y, float width, float height)
            : GUIComponent(x, y, width, height), k_renderIDBackground(Hash(uniqueName)),
              k_renderIDFilled(Hash(uniqueName.data() + String("Filled")))
        {
            std::cout << "GUIMeter: x: " << x << ", y: " << y << ", width: " << width
                      << ", height: " << height << std::endl;
        }

      protected:
        void RenderDerived() const override;

      private:
        const int k_renderIDBackground; ///< The render ID of the background image.

        const int k_renderIDFilled; ///< The render ID of the filled part of the meter.

        float m_filledPercentage; ///< The percentage of the meter that is filled.

        Color m_filledColor; ///< The color of the filled part of the meter.
    };
}