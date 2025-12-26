/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include "ForradiaEngine/ScenesCore.hpp"
// clang-format on

namespace ForradiaEngine::JewelryMakerTheme
{
    class GUIInteractionMenu;

    /**
     *  The main scene is the scene where the actual game is played.
     */
    class MainScene : public IScene
    {
      public:
        static auto instance() -> MainScene &
        {
            static MainScene instance;
            return instance;
        }

        MainScene(const MainScene &) = delete;

        auto operator=(const MainScene &) -> MainScene & = delete;

        MainScene() = default;

      protected:
        /**
         *  Initializes the main scene.
         */
        auto initializeDerived() -> void override;

        /**
         *  Called when the main scene is entered.
         */
        auto onEnterDerived() -> void override;

        auto onMouseDown(Uint8 mouseButton) -> void override;

        auto onMouseUp(Uint8 mouseButton, int clickSpeed) -> void override;

        auto onMouseWheel(int delta) -> void override;

        auto onKeyDown(SDL_Keycode key) -> void override;

        auto onKeyUp(SDL_Keycode key) -> void override;

        auto onTextInput(std::string_view text) -> void override;

        auto render() const -> void override;

        /**
         *  Called every frame.
         */
        auto updateDerived() -> void override;

        /**
         *  Called every frame to render the scene.
         */
        auto renderDerived() const -> void override;

      private:
        std::shared_ptr<GUIInteractionMenu> m_guiInteractionMenu{};
    };
}
