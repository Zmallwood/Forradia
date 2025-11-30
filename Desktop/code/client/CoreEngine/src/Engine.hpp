//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace AAK
{
    namespace Forradia
    {
        ///
        /// The engine class is responsible for initializing, running and stopping
        /// the game.
        ///
        class Engine
        {
          public:
            ///
            /// Initializes the engine.
            ///
            /// @param gameWindowTitle The title of the game window.
            /// @param clearColor The color to clear the canvas with.
            ///
            void Initialize(StringView gameWindowTitle, Color clearColor) const;

            ///
            /// Runs the engine.
            ///
            void Run();

            ///
            /// Stops the engine.
            ///
            void Stop();

          private:
            ///
            /// Polls and handles events.
            ///
            void HandleEvents();

            bool m_running{true}; ///< Whether the engine is running.
        };
    }
}