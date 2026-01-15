/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "GUIContainerWindow/GUIContainerWindow.hpp"
#include "Player/Player.hpp"
#include "Player/PlayerObjectsInventory.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    class GUIInventoryWindow : public GUIContainerWindow
    {
      public:
        static auto instance() -> GUIInventoryWindow &
        {
            static GUIInventoryWindow instance(Player::instance().getObjectsInventoryRef(),
                                               hash("Inventory"));
            return instance;
        }

        GUIInventoryWindow(const GUIInventoryWindow &) = delete;

        auto operator=(const GUIInventoryWindow &) -> GUIInventoryWindow & = delete;

        /**
         *  Constructor.
         *
         *  @param containedObjects The contained objects.
         */
        using GUIContainerWindow::GUIContainerWindow;
    };
}
