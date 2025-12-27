/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include <string_view>
    
    #include "ForradiaEngine/Common/Matter/Coloring.hpp"
// clang-format on

namespace ForradiaEngine
{
    /**
     *  The engine class is responsible for initializing, running and stopping
     *  the game.
     */
    class Engine
    {
      public:
        static auto instance() -> Engine &
        {
            static Engine instance;
            return instance;
        }

        Engine(const Engine &) = delete;

        auto operator=(const Engine &) -> Engine & = delete;

        Engine() = default;

        /**
         *  Initializes the engine.
         *
         *  @param gameWindowTitle The title of the game window.
         *  @param clearColor The color to clear the canvas with.
         */
        static auto initialize(std::string_view gameWindowTitle, Color clearColor) -> void;

        /**
         *  Runs the engine.
         */
        auto run() -> void;

        /**
         *  Stops the engine.
         */
        auto stop() -> void;

      private:
        auto handleEvents() -> void;

        auto handleSingleEvent(SDL_Event &event) -> void;

        bool m_running{true};
        int m_ticksLeftMouseButtonFired{0};
        int m_ticksRightMouseButtonFired{0};
    };
}
