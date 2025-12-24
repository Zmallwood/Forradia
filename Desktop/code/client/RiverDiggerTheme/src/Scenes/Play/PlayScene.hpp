/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "ScenesCore/IScene.hpp"

namespace Forradia::Theme0
{
    /**
     *  The play scene is the scene where the player can choose to play a new game or continue a
     *  saved game.
     */
    class PlayScene : public IScene
    {
      public:
        static PlayScene &instance()
        {
            static PlayScene instance;
            return instance;
        }

        PlayScene(const PlayScene &) = delete;

        PlayScene &operator=(const PlayScene &) = delete;

        PlayScene() = default;

      protected:
        /**
         *  Initializes the play scene.
         */
        virtual auto initializeDerived() -> void override;

        /**
         *  Called every frame to render the scene.
         */
        virtual auto renderDerived() const -> void override;
    };
}
