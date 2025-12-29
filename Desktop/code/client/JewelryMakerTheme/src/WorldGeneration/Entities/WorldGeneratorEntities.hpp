/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "WorldGeneration/Common/WorldGeneratorBase.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    /**
     *  Generates entities for the world.
     */
    class WorldGeneratorEntities : public WorldGeneratorBase
    {
      public:
        WorldGeneratorEntities() = default;

        /**
         *  Generates entities for the world.
         */
        static auto generateEntities() -> void;

      private:
        static auto generateEntitiesInEcosystems() -> void;
    };
}
