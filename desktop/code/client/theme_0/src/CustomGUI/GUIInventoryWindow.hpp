//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "GUICore/GUIWindow.hpp"

namespace Forradia::Theme0
{
    class GUIInventoryWindow : public GUIWindow
    {
      public:
        GUIInventoryWindow()
            : GUIWindow(0.5f, 0.2f, 0.2f, 0.5f, "Inventory")
        {
        }

      protected:
        void RenderDerived() const override;

      private:
        static constexpr float k_margin{0.005f};

        static constexpr float k_slotSize{0.04f};

        inline static const String k_slotImageName{
            "GUIInventoryWindowSlotBackground"};
    };
}