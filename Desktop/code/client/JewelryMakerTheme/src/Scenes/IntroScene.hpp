/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "ForradiaEngine/ScenesCore.hpp"

namespace ForradiaEngine
{
    class GUIComponent;
}

namespace ForradiaEngine::JewelryMakerTheme
{
    /**
     *  The intro scene is the first scene that is displayed when the game is started.
     *  It displays the title of the game and the main menu.
     */
    class IntroScene : public IScene
    {
      public:
        IntroScene() = default;

      protected:
        /**
         *  Initializes the intro scene.
         */
        auto initializeDerived() -> void override;

        /**
         *  Called when the intro scene is entered.
         */
        auto onEnterDerived() -> void override;

        auto onMouseDown(Uint8 mouseButton) -> void override;

        auto onKeyDown(SDL_Keycode key) -> void override;

        /**
         *  Called every frame.
         */
        auto updateDerived() -> void override;

        /**
         *  Called every frame to render the scene.
         */
        auto renderDerived() const -> void override;

      private:
        std::shared_ptr<GUIComponent> m_startText{};
    };
}
