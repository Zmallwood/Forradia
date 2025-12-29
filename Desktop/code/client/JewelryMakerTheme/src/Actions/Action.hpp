/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace ForradiaEngine::JewelryMakerTheme
{
    class Tile;
    class Object;

    /**
     *  Represents an action that can be performed by the player.
     */
    class Action
    {
      public:
        /** The label for the action shown in the interaction menu. */
        std::string label{};

        /** The types of ground that the action can be performed on. */
        std::vector<int> groundMatches{};

        /** The types of objects that the action can be performed on. */
        std::vector<int> objectMatches{};

        /** The types of objects that need to be in the players inventory. */
        std::vector<int> objectsInInventory{};

        /** The function that performs the action. */
        std::function<void(const std::shared_ptr<Tile> &,
                           const std::vector<std::shared_ptr<Object> *> &)>
            action{};
    };
}
