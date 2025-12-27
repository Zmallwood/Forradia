/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "GUIContainerWindow/GUIContainerWindow.hpp"
#include "Content/Essentials/Player/Player.hpp"
#include "Content/Essentials/Player/PlayerObjectsInventory.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    class GUIInventoryWindow : public GUIContainerWindow
    {
      public:
        static auto instance() -> GUIInventoryWindow &
        {
            static GUIInventoryWindow instance(Player::instance().getObjectsInventoryRef());
            return instance;
        }

        GUIInventoryWindow(const GUIInventoryWindow &) = delete;

        auto operator=(const GUIInventoryWindow &) -> GUIInventoryWindow & = delete;

        using GUIContainerWindow::GUIContainerWindow;
    };
}
