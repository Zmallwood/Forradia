//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

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
        GUIMeter(StringView uniqueName, float x, float y, float width, float height,
                 Color filledColor)
            : GUIComponent(x, y, width, height), k_renderIDBackground(Hash(uniqueName)),
              k_renderIDFilled(Hash(uniqueName.data() + String("Filled"))),
              k_filledColor(filledColor)
        {
        }

      protected:
        void RenderDerived() const override;

        virtual float GetFilledPercentage() const = 0;

      private:
        const int k_renderIDBackground; ///< The render ID of the background image.

        const int k_renderIDFilled; ///< The render ID of the filled part of the meter.

        const Color k_filledColor; ///< The color of the filled part of the meter.
    };
}