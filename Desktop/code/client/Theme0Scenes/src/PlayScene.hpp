/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "IScene.hpp"

namespace Forradia::Theme0
{
    /**
        The play scene is the scene where the player can choose to play a new game or continue a
        saved game.
     */
    class PlayScene : public IScene
    {
      public:
        static PlayScene &Instance()
        {
            static PlayScene instance;
            return instance;
        }

        // Delete copy/move
        PlayScene(const PlayScene &) = delete;

        PlayScene &operator=(const PlayScene &) = delete;

        PlayScene() = default;

      protected:
        /**
            Initializes the play scene.
         */
        virtual auto InitializeDerived() -> void override;

        /**
            Called every frame to render the scene.
         */
        virtual auto RenderDerived() const -> void override;
    };
}
