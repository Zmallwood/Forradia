/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "WorldStructure/ContainedObjects.hpp"

namespace ForradiaEngine::JewelryMakerTheme
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
        PlayerObjectsInventory() : ContainedObjects(k_defaultMaxObjects)
        {
            this->initialize();
        }

      private:
        constexpr static int k_defaultMaxObjects{30};

        auto initialize() -> void;
    };
}
