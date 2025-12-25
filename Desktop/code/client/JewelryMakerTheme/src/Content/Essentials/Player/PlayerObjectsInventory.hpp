/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include "Content/WorldStructure/ContainedObjects.hpp"
// clang-format on

namespace ForradiaEngine::Theme0
{
    /**
     *  Represents the inventory of objects for the player.
     *
     *  TODO: Decide if should be used also for other entities.
     */
    class PlayerObjectsInventory : public ContainedObjects
    {
      public:
        /**
         *  Constructor.
         */
        PlayerObjectsInventory() : ContainedObjects(30)
        {
            this->initialize();
        }

      private:
        auto initialize() -> void;
    };
}
