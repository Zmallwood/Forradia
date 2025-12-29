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
        static auto instance() -> WorldGeneratorEntities &
        {
            static WorldGeneratorEntities instance;
            return instance;
        }

        WorldGeneratorEntities(const WorldGeneratorEntities &) = delete;

        auto operator=(const WorldGeneratorEntities &) -> WorldGeneratorEntities & = delete;

        WorldGeneratorEntities() = default;

        /**
         *  Generates entities for the world.
         */
        auto generateEntities() const -> void;

      private:
        auto generateEntitiesInEcosystems() const -> void;
    };
}
