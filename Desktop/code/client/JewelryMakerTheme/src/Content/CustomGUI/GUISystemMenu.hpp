/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include "ForradiaEngine/GUICore/GUIComponent.hpp"
// clang-format on

namespace ForradiaEngine::Theme0
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

        GUISystemMenu &operator=(const GUISystemMenu &) = delete;

        /**
         *  Constructor.
         */
        GUISystemMenu() : GUIComponent(0.0f, 0.0f, 1.0f, 1.0f)
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
        virtual auto updateDerived() -> void override;

        /**
         *  Does render logic that is specific to the system menu.
         */
        virtual auto renderDerived() const -> void override;

      private:
        const int k_renderIDBackgroundColor{hash("GUISystemMenuBackgroundColor")};
    };
}
