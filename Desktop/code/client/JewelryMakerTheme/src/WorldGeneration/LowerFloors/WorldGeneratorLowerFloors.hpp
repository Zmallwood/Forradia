/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "WorldGeneration/Common/WorldGeneratorBase.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    /**
     *  Generates lower floors for the world.
     */
    class WorldGeneratorLowerFloors : public WorldGeneratorBase
    {
      public:
        static auto instance() -> WorldGeneratorLowerFloors &
        {
            static WorldGeneratorLowerFloors instance;
            return instance;
        }

        WorldGeneratorLowerFloors(const WorldGeneratorLowerFloors &) = delete;

        auto operator=(const WorldGeneratorLowerFloors &) -> WorldGeneratorLowerFloors & = delete;

        WorldGeneratorLowerFloors() = default;

        /**
         *  Generates entities for the world.
         */
        auto generateLowerFloors() const -> void;

      private:
        auto clearWithDirt() const -> void;

        auto fillWithStoneBlocks() const -> void;
    };
}
