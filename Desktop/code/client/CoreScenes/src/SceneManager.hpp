/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include <SDL2/SDL.h>
#include <string_view>
#include <unordered_map>

namespace Forradia
{
    class IScene;

    /**
     *  The manager for the scenes.
     */
    class SceneManager
    {
      public:
        static auto instance() -> SceneManager &
        {
            static SceneManager instance;
            return instance;
        }

        // Delete copy/move
        SceneManager(const SceneManager &) = delete;

        auto operator=(const SceneManager &) -> SceneManager & = delete;

        SceneManager() = default;

        /**
         *  Adds a scene to the manager.
         *
         *  @param sceneName The name of the scene.
         *  @param scene The scene to add.
         */
        auto addScene(std::string_view sceneName, IScene &scene) -> void;

        /**
         *  Goes to a scene.
         *
         *  @param sceneName The name of the scene to go to.
         */
        auto goToScene(std::string_view sceneName) -> void;

        auto onMouseDownCurrentScene(Uint8 mouseButton) -> void;

        auto onMouseUpCurrentScene(Uint8 mouseButton, int clickSpeed) -> void;

        auto onMouseWheelCurrentScene(int delta) -> void;

        auto onKeyDownCurrentScene(SDL_Keycode key) -> void;

        auto onKeyUpCurrentScene(SDL_Keycode key) -> void;

        auto onTextInputCurrentScene(std::string_view text) -> void;

        /**
         *  Updates the current scene.
         */
        auto updateCurrentScene() -> void;

        /**
         *  Renders the current scene.
         */
        auto renderCurrentScene() const -> void;

        auto getScene(std::string_view sceneName) -> IScene *;

      private:
        std::unordered_map<int, IScene &> m_scenes{};
        int m_currentScene{0};
    };
}
