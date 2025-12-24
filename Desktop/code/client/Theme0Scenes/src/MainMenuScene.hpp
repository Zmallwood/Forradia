/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "IScene.hpp"

namespace Forradia::Theme0
{
    /**
     *  The main menu scene is the second scene that is displayed when the game is started.
     *  It displays the title of the game and the main menu.
     */
    class MainMenuScene : public IScene
    {
      public:
        static MainMenuScene &instance()
        {
            static MainMenuScene instance;
            return instance;
        }

        // Delete copy/move
        MainMenuScene(const MainMenuScene &) = delete;

        MainMenuScene &operator=(const MainMenuScene &) = delete;

        MainMenuScene() = default;

      protected:
        /**
         *  Initializes the main menu scene.
         */
        virtual auto initializeDerived() -> void override;

        /**
         *  Called every frame to render the scene.
         */
        virtual auto renderDerived() const -> void override;
    };
}
