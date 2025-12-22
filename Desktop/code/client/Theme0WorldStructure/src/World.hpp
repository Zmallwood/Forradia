/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

namespace Forradia::Theme0 {
    class WorldArea;

    /**
     * The world in the game.
     */
    class World {
      public:
        static World &Instance() {
            static World instance;
            return instance;
        }
        // Delete copy/move
        World(const World &) = delete;
        World &operator=(const World &) = delete;

        World() = default;

        /**
         * Initializes the world.
         *
         * @param worldAreaSize The size of the world area.
         * @param worldScaling The scaling of the world.
         */
        auto Initialize(Size worldAreaSize, float worldScaling) -> void;

        /**
         * Gets the current world area.
         *
         * @return The current world area.
         */
        auto GetCurrentWorldArea() const {
            return m_currentWorldArea;
        }

      private:
        std::shared_ptr<WorldArea> m_currentWorldArea{};
    };
}
