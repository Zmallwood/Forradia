/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "ForradiaEngine/GUICore/GUIWindow.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    /**
     *  Represents the inventory window.
     */
    class GUICraftingWindow : public GUIWindow
    {
      public:
        static auto instancePtr() -> std::shared_ptr<GUICraftingWindow>
        {
            static std::shared_ptr<GUICraftingWindow> instancePtr =
                std::make_shared<GUICraftingWindow>();
            return instancePtr;
        }

        static auto instance() -> GUICraftingWindow &
        {
            return *instancePtr();
        }

        GUICraftingWindow(const GUICraftingWindow &) = delete;

        auto operator=(const GUICraftingWindow &) -> GUICraftingWindow & = delete;

        /**
         *  Constructor.
         */
        GUICraftingWindow()
            : GUIWindow("GUICraftingWindow", k_defaultBounds.x, k_defaultBounds.y,
                        k_defaultBounds.width, k_defaultBounds.height, "Crafting")
        {
            this->initialize();
        }

      private:
        auto initialize() -> void;

        constexpr static RectF k_defaultBounds{0.2F, 0.2F, 0.2F, 0.5F};
    };
}
