/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

namespace Forradia::Theme0 {
    class Tile;
    class Object;

    /**
     * Represents an action that can be performed by the player.
     */
    class Action {
      public:
        std::string label{}; ///< The label for the action shown in the interaction menu.
        std::vector<int>
            groundMatches{}; ///< The types of ground that the action can be performed on.
        std::vector<int>
            objectMatches{}; ///< The types of objects that the action can be performed on.
        std::vector<int> objectsInInventory{}; ///< The types of objects that need to be in the
                                               ///< players inventory.
        std::function<void(std::shared_ptr<Tile>, std::vector<std::shared_ptr<Object> *>)>
            action{}; ///< The function that performs the action.
    };
}
