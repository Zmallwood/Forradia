/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "WorldGeneratorBase.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    class Tile;

    /**
     *  The world generator for objects.
     */
    class WorldGeneratorObjects : public WorldGeneratorBase
    {
      public:
        /**
         *  Generate the objects in the world.
         */
        static auto generateObjects() -> void;

      private:
        static auto generateForests() -> void;

        static auto shouldAddForestObjects(float treeDensity, float distance, float radius) -> bool;

        static auto addTreeToForestTile(const std::shared_ptr<Tile> &forestTile, bool useFir)
            -> void;

        static auto addUndergrowthToForestTile(const std::shared_ptr<Tile> &forestTile) -> void;

        static auto generateMeadows() -> void;

        static auto generateObjectsInBiomes() -> void;

        [[nodiscard]] static auto isValidForFlora(int x, int y) -> bool;
    };
}
