/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include "Content/WorldGeneration/Common/WorldGeneratorBase.hpp"
// clang-format on

namespace ForradiaEngine::Theme0
{
    /**
     *  Generates entities for the world.
     */
    class WorldGeneratorEntities : public WorldGeneratorBase
    {
      public:
        static WorldGeneratorEntities &instance()
        {
            static WorldGeneratorEntities instance;
            return instance;
        }

        WorldGeneratorEntities(const WorldGeneratorEntities &) = delete;

        WorldGeneratorEntities &operator=(const WorldGeneratorEntities &) = delete;

        WorldGeneratorEntities() = default;

        /**
         *  Generates entities for the world.
         */
        auto generateEntities() const -> void;

      private:
        auto generateEntitiesInEcosystems() const -> void;

        auto isNearWater(int x, int y, int radius) const -> bool;
    };
}
