/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

namespace Forradia {
    /**
     * Class for the FPS counter.
     */
    class FPSCounter {
      public:
        /**
         * Updates the FPS counter.
         */
        auto Update() -> void;

        /**
         * Gets the current FPS.
         * @return The current FPS.
         */
        [[nodiscard]] auto GetFPS() const {
            return m_fps;
        }

      private:
        int m_fps{0};
        int m_framesCount{0};
        int m_ticksLastUpdate{0};
    };
}
