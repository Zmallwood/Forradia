/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include "ForradiaEngine/GUICore/GUIPanel.hpp"
    #include "GUIInteractionMenuEntry.hpp"
    #include "ForradiaEngine/Common/Matter/Geometry.hpp"
    #include "Action.hpp"
    #include <vector>
// clang-format on

namespace ForradiaEngine::JewelryMakerTheme
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

        auto operator=(const GUIInteractionMenu &) -> GUIInteractionMenu & = delete;

        /**
         *  Constructor.
         */
        GUIInteractionMenu() : GUIPanel("GUIInteractionMenu", 0.0F, 0.0F, k_defaultWidth, 0.0F)
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
        static auto checkActionGroundMatches(Action &action, int groundHash) -> bool;

        static auto checkActionObjectMatches(Action &action, const std::vector<int> &objectHashes)
            -> bool;

        static auto checkActionInventoryObjectsMatches(Action &action) -> bool;

        static constexpr float k_indentWidth{0.01F};
        static constexpr float k_lineHeight{0.035F};
        static constexpr float k_margin{0.01F};
        static constexpr float k_defaultWidth{0.2F};
        const int k_renderIDActionsString{hash("GUIInteractionMenuActionsString")};
        const int k_maxNumMenuEntries{40};
        constexpr static int k_renderIDHoveredRow{hash("GUIInteractionMenuHoveredRow")};
        std::vector<Action> m_actions{};
        std::vector<int> m_renderIDsMenuEntryStrings{};
        std::vector<GUIInteractionMenuEntry> m_entries{};
        Point m_clickedCoordinate{-1, -1};
        std::vector<std::shared_ptr<Object> *> m_clickedObjects{};
    };
}
