/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "IScene.hpp"

namespace Forradia
{
    class GUIComponent;
}

namespace Forradia::Theme0
{
    /**
     *  The intro scene is the first scene that is displayed when the game is started.
     *  It displays the title of the game and the main menu.
     */
    class IntroScene : public IScene
    {
      public:
        static IntroScene &instance()
        {
            static IntroScene instance;
            return instance;
        }

        IntroScene(const IntroScene &) = delete;

        IntroScene &operator=(const IntroScene &) = delete;

        IntroScene() = default;

      protected:
        /**
         *  Initializes the intro scene.
         */
        virtual auto initializeDerived() -> void override;

        /**
         *  Called when the intro scene is entered.
         */
        virtual auto onEnterDerived() -> void override;

        virtual auto onMouseDown(Uint8 mouseButton) -> void override;

        virtual auto onKeyDown(SDL_Keycode key) -> void override;

        /**
         *  Called every frame.
         */
        virtual auto updateDerived() -> void override;

        /**
         *  Called every frame to render the scene.
         */
        virtual auto renderDerived() const -> void override;

      private:
        std::shared_ptr<GUIComponent> m_startText{};
    };
}
