/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "Coloring/Color.hpp"
#include <string_view>

namespace Forradia {
    /**
     * The engine class is responsible for initializing, running and stopping
     * the game.
     */
    class Engine {
      public:
        static auto Instance() -> Engine & {
            static Engine instance;
            return instance;
        }

        // Delete copy/move
        Engine(const Engine &) = delete;

        auto operator=(const Engine &) -> Engine & = delete;

        Engine() = default;

        /**
         * Initializes the engine.
         *
         * @param gameWindowTitle The title of the game window.
         * @param clearColor The color to clear the canvas with.
         */
        static auto Initialize(std::string_view gameWindowTitle, Color clearColor) -> void;

        /**
         * Runs the engine.
         */
        auto Run() -> void;

        /**
         * Stops the engine.
         */
        auto Stop() -> void;

      private:
        auto HandleEvents() -> void;

        bool m_running{true};
        int m_ticksLeftMouseButtonFired{0};
        int m_ticksRightMouseButtonFired{0};
    };
}
