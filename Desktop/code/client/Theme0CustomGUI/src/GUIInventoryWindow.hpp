/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "GUIContainerWindow.hpp"
#include "Player/Player.hpp"
#include "Player/PlayerObjectsInventory.hpp"

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
