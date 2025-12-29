/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "ForradiaEngine/ScenesCore.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    /**
     *  The main menu scene is the second scene that is displayed when the game is started.
     *  It displays the title of the game and the main menu.
     */
    class MainMenuScene : public IScene
    {
      public:
        MainMenuScene() = default;

      protected:
        /**
         *  Initializes the main menu scene.
         */
        auto initializeDerived() -> void override;

        /**
         *  Called every frame to render the scene.
         */
        auto renderDerived() const -> void override;
    };
}
