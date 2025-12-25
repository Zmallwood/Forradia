/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

namespace ForradiaEngine::Theme0
{
    class WorldArea;

    /**
     *  The WorldGenerator class is responsible for generating a new world.
     */
    class WorldGenerator
    {
      public:
        static WorldGenerator &instance()
        {
            static WorldGenerator instance;
            return instance;
        }

        WorldGenerator(const WorldGenerator &) = delete;

        WorldGenerator &operator=(const WorldGenerator &) = delete;

        WorldGenerator() = default;

        /**
         *  Generates a new world.
         */
        static auto generateNewWorld() -> void;

      private:
        static auto prepare() -> void;
    };
}
