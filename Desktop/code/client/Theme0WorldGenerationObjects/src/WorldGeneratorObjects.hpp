/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "WorldGeneratorBase.hpp"

namespace Forradia::Theme0
{
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

        // Delete copy/move
        WorldGeneratorObjects(const WorldGeneratorObjects &) = delete;

        WorldGeneratorObjects &operator=(const WorldGeneratorObjects &) = delete;

        WorldGeneratorObjects() = default;

        /**
         *  Generate the objects in the world.
         */
        auto generateObjects() const -> void;

      private:
        auto generateForests() const -> void;

        auto generateMeadows() const -> void;

        auto generateObjectsInBiomes() const -> void;

        [[nodiscard]] auto isValidForFlora(int x, int y) const -> bool;
    };
}
