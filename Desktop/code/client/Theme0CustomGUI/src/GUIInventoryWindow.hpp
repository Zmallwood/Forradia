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
        static GUIInventoryWindow &Instance()
        {
            static GUIInventoryWindow instance(Player::Instance().GetObjectsInventoryRef());
            return instance;
        }

        // Delete copy/move
        GUIInventoryWindow(const GUIInventoryWindow &) = delete;

        GUIInventoryWindow &operator=(const GUIInventoryWindow &) = delete;

        using GUIContainerWindow::GUIContainerWindow;
    };
}
