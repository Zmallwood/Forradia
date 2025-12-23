/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "IScene.hpp"

namespace Forradia::Theme0
{
    class GUIInteractionMenu;

    /**
        The main scene is the scene where the actual game is played.
     */
    class MainScene : public IScene
    {
      public:
        static MainScene &Instance()
        {
            static MainScene instance;
            return instance;
        }

        // Delete copy/move
        MainScene(const MainScene &) = delete;

        MainScene &operator=(const MainScene &) = delete;

        MainScene() = default;

      protected:
        /**
            Initializes the main scene.
         */
        virtual auto InitializeDerived() -> void override;

        /**
            Called when the main scene is entered.
         */
        virtual auto OnEnterDerived() -> void override;

        virtual auto OnMouseDown(Uint8 mouseButton) -> void override;

        virtual auto OnMouseUp(Uint8 mouseButton, int clickSpeed) -> void override;

        virtual auto OnMouseWheel(int delta) -> void override;

        virtual auto OnKeyDown(SDL_Keycode key) -> void override;

        virtual auto OnKeyUp(SDL_Keycode key) -> void override;

        virtual auto OnTextInput(std::string_view text) -> void override;

        virtual auto Render() const -> void override;

        /**
            Called every frame.
         */
        virtual auto UpdateDerived() -> void override;

        /**
            Called every frame to render the scene.
         */
        virtual auto RenderDerived() const -> void override;

      private:
        std::shared_ptr<GUIInteractionMenu> m_guiInteractionMenu{};
    };
}
