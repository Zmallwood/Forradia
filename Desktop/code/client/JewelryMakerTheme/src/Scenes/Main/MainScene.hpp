/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include "ForradiaEngine/ScenesCore/IScene.hpp"
// clang-format on

namespace ForradiaEngine::Theme0
{
    class GUIInteractionMenu;

    /**
     *  The main scene is the scene where the actual game is played.
     */
    class MainScene : public IScene
    {
      public:
        static MainScene &instance()
        {
            static MainScene instance;
            return instance;
        }

        MainScene(const MainScene &) = delete;

        MainScene &operator=(const MainScene &) = delete;

        MainScene() = default;

      protected:
        /**
         *  Initializes the main scene.
         */
        virtual auto initializeDerived() -> void override;

        /**
         *  Called when the main scene is entered.
         */
        virtual auto onEnterDerived() -> void override;

        virtual auto onMouseDown(Uint8 mouseButton) -> void override;

        virtual auto onMouseUp(Uint8 mouseButton, int clickSpeed) -> void override;

        virtual auto onMouseWheel(int delta) -> void override;

        virtual auto onKeyDown(SDL_Keycode key) -> void override;

        virtual auto onKeyUp(SDL_Keycode key) -> void override;

        virtual auto onTextInput(std::string_view text) -> void override;

        virtual auto render() const -> void override;

        /**
         *  Called every frame.
         */
        virtual auto updateDerived() -> void override;

        /**
         *  Called every frame to render the scene.
         */
        virtual auto renderDerived() const -> void override;

      private:
        std::shared_ptr<GUIInteractionMenu> m_guiInteractionMenu{};
    };
}
