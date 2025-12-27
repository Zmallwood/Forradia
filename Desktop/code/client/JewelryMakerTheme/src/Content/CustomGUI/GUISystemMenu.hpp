/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "ForradiaEngine/GUICore/GUIComponent.hpp"
#include "ForradiaEngine/Common/General.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    /**
     *  Represents the system menu.
     */
    class GUISystemMenu : public GUIComponent
    {
      public:
        static auto instancePtr() -> std::shared_ptr<GUISystemMenu>
        {
            static std::shared_ptr<GUISystemMenu> instancePtr = std::make_shared<GUISystemMenu>();
            return instancePtr;
        }

        static auto instance() -> GUISystemMenu &
        {
            return *instancePtr();
        }

        GUISystemMenu(const GUISystemMenu &) = delete;

        auto operator=(const GUISystemMenu &) -> GUISystemMenu & = delete;

        /**
         *  Constructor.
         */
        GUISystemMenu() : GUIComponent(k_bounds.x, k_bounds.y, k_bounds.width, k_bounds.height)
        {
            this->initialize();
        }

      protected:
        /**
         *  Initializes the system menu.
         */
        auto initialize() -> void;

        /**
         *  Does update logic that is specific to the system menu.
         */
        auto updateDerived() -> void override;

        /**
         *  Does render logic that is specific to the system menu.
         */
        auto renderDerived() const -> void override;

      private:
        constexpr static RectF k_bounds{0.0F, 0.0F, 1.0F, 1.0F};
        const int k_renderIDBackgroundColor{hash("GUISystemMenuBackgroundColor")};
    };
}
