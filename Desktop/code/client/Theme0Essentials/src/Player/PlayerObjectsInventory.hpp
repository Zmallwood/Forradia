/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "ContainedObjects.hpp"

namespace Forradia::Theme0 {
    /**
     * Represents the inventory of objects for the player.
     * TODO: Decide if should be used also for other entities.
     */
    class PlayerObjectsInventory : public ContainedObjects {
      public:
        /**
         * Constructor.
         */
        PlayerObjectsInventory() : ContainedObjects(30) {
            this->Initialize();
        }

      private:
        auto Initialize() -> void;

        std::shared_ptr<ContainedObjects> m_containedObjects;
    };
}
