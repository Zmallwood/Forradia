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
        The manager for the scenes.
     */
    class SceneManager
    {
      public:
        static auto Instance() -> SceneManager &
        {
            static SceneManager instance;
            return instance;
        }

        // Delete copy/move
        SceneManager(const SceneManager &) = delete;

        auto operator=(const SceneManager &) -> SceneManager & = delete;

        SceneManager() = default;

        /**
            Adds a scene to the manager.

            @param sceneName The name of the scene.
            @param scene The scene to add.
         */
        auto AddScene(std::string_view sceneName, IScene &scene) -> void;

        /**
            Goes to a scene.

            @param sceneName The name of the scene to go to.
         */
        auto GoToScene(std::string_view sceneName) -> void;

        auto OnMouseDownCurrentScene(Uint8 mouseButton) -> void;

        auto OnMouseUpCurrentScene(Uint8 mouseButton, int clickSpeed) -> void;

        auto OnMouseWheelCurrentScene(int delta) -> void;

        auto OnKeyDownCurrentScene(SDL_Keycode key) -> void;

        auto OnKeyUpCurrentScene(SDL_Keycode key) -> void;

        auto OnTextInputCurrentScene(std::string_view text) -> void;

        /**
            Updates the current scene.
         */
        auto UpdateCurrentScene() -> void;

        /**
            Renders the current scene.
         */
        auto RenderCurrentScene() const -> void;

        auto GetScene(std::string_view sceneName) -> IScene *;

      private:
        std::unordered_map<int, IScene &> m_scenes{};
        int m_currentScene{0};
    };
}
