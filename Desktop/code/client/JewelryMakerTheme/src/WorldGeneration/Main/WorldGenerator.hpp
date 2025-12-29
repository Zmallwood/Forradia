/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

namespace ForradiaEngine::JewelryMakerTheme
{
    class WorldArea;

    /**
     *  The WorldGenerator class is responsible for generating a new world.
     */
    class WorldGenerator
    {
      public:
        WorldGenerator() = default;

        /**
         *  Generates a new world.
         */
        static auto generateNewWorld() -> void;

      private:
        static auto prepare() -> void;
    };
}
