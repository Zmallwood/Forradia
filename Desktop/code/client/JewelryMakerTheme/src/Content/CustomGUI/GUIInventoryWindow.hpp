/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include "GUIContainerWindow.hpp"
    #include "Content/Essentials/Player/Player.hpp"
    #include "Content/Essentials/Player/PlayerObjectsInventory.hpp"
// clang-format on

namespace Forradia::Theme0
{
    class GUIInventoryWindow : public GUIContainerWindow
    {
      public:
        static GUIInventoryWindow &instance()
        {
            static GUIInventoryWindow instance(Player::instance().getObjectsInventoryRef());
            return instance;
        }

        GUIInventoryWindow(const GUIInventoryWindow &) = delete;

        GUIInventoryWindow &operator=(const GUIInventoryWindow &) = delete;

        using GUIContainerWindow::GUIContainerWindow;
    };
}
