/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "WorldGeneration/Common/WorldGeneratorBase.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    class Tile;

    /**
     *  The world generator for objects.
     */
    class WorldGeneratorObjects : public WorldGeneratorBase
    {
      public:
        static WorldGeneratorObjects &instance()
        {
            static WorldGeneratorObjects instance;
            return instance;
        }

        WorldGeneratorObjects(const WorldGeneratorObjects &) = delete;

        WorldGeneratorObjects &operator=(const WorldGeneratorObjects &) = delete;

        WorldGeneratorObjects() = default;

        /**
         *  Generate the objects in the world.
         */
        auto generateObjects() const -> void;

      private:
        auto generateForests() const -> void;

        auto shouldAddForestObjects(float treeDensity, float distance, float radius) const -> bool;

        auto addTreeToForestTile(const std::shared_ptr<Tile> &forestTile, bool useFir) const
            -> void;

        auto addUndergrowthToForestTile(const std::shared_ptr<Tile> &forestTile) const -> void;

        auto generateMeadows() const -> void;

        auto generateObjectsInBiomes() const -> void;

        [[nodiscard]] auto isValidForFlora(int x, int y) const -> bool;
    };
}
