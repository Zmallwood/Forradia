/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include "ForradiaEngine/GUICore/GUIPanel.hpp"
    #include "GUIInteractionMenuEntry.hpp"
// clang-format on

namespace ForradiaEngine::Theme0
{
    /**
     *  Represents the interaction menu.
     */
    class GUIInteractionMenu : public GUIPanel
    {
      public:
        static auto instancePtr() -> std::shared_ptr<GUIInteractionMenu>
        {
            static std::shared_ptr<GUIInteractionMenu> instancePtr =
                std::make_shared<GUIInteractionMenu>();
            return instancePtr;
        }

        static auto instance() -> GUIInteractionMenu &
        {
            return *instancePtr();
        }

        GUIInteractionMenu(const GUIInteractionMenu &) = delete;

        GUIInteractionMenu &operator=(const GUIInteractionMenu &) = delete;

        /**
         *  Constructor.
         */
        GUIInteractionMenu() : GUIPanel("GUIInteractionMenu", 0.0f, 0.0f, 0.2f, 0.14f)
        {
            this->initialize();
        }

        auto onMouseUp(Uint8 mouseButton, int clickSpeed) -> bool override;

        /**
         *  Builds the menu.
         */
        auto buildMenu() -> void;

        auto handleClick() -> void;

        auto showMenuForTileAndObjects(int groundHash, const std::vector<int> &objectHashes)
            -> void;

        /**
         *  Gets the timed actions.
         *
         *  @return The timed actions.
         */
        auto &getTimedActionsRef()
        {
            return m_timedActions;
        }

        /**
         *  Gets the clicked coordinate.
         *
         *  @return The clicked coordinate.
         */
        auto getClickedCoordinate() const
        {
            return m_clickedCoordinate;
        }

      protected:
        /**
         *  Initializes the interaction menu.
         */
        auto initialize() -> void;

        auto updateDerived() -> void override;

        /**
         *  Does render logic that is specific to the interaction menu.
         */
        auto renderDerived() const -> void override;

      private:
        static constexpr float k_indentWidth{0.01f};
        static constexpr float k_lineHeight{0.035f};
        const int k_renderIDActionsString{hash("GUIInteractionMenuActionsString")};
        const int k_maxNumMenuEntries{40};
        constexpr static int k_renderIDHoveredRow{hash("GUIInteractionMenuHoveredRow")};
        std::vector<int> m_renderIDsMenuEntryStrings{};
        std::vector<GUIInteractionMenuEntry> m_entries{};
        Point m_clickedCoordinate{-1, -1};
        std::unordered_map<int, int> m_timedActions{};
        std::vector<std::shared_ptr<Object> *> m_clickedObjects{};
    };
}
