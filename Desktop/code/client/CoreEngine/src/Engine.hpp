/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once

namespace Forradia {
  /**
   * The engine class is responsible for initializing, running and stopping
   * the game.
   */
  class Engine {
   public:
    /**
     * Initializes the engine.
     *
     * @param gameWindowTitle The title of the game window.
     * @param clearColor The color to clear the canvas with.
     */
    auto Initialize(std::string_view gameWindowTitle, Color clearColor) const -> void;

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
  };
}
