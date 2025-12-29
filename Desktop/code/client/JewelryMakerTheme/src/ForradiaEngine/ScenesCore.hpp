/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include <string_view>
#include <unordered_map>
#include <memory>
#include <SDL2/SDL.h>

namespace ForradiaEngine
{
    class GUI;

    /**
     *  The base class for all scenes.
     */
    class IScene
    {
      public:
        virtual ~IScene() = default;

        /**
         *  Initializes the scene.
         */
        auto initialize() -> void;

        /**
         *  Called when the scene is entered.
         */
        auto onEnter() -> void;

        virtual auto onMouseDown(Uint8 mouseButton) -> void;

        virtual auto onMouseUp(Uint8 mouseButton, int clickSpeed) -> void;

        virtual auto onMouseWheel(int delta) -> void;

        virtual auto onKeyDown(SDL_Keycode key) -> void;

        virtual auto onKeyUp(SDL_Keycode key) -> void;

        virtual auto onTextInput(std::string_view text) -> void;

        /**
         *  Updates the scene.
         */
        virtual auto update() -> void;

        /**
         *  Renders the scene.
         */
        virtual auto render() const -> void;

        /**
         *  Gets the GUI.
         *
         *  @return The GUI.
         */
        [[nodiscard]] auto getGUI() const -> std::shared_ptr<GUI>
        {
            return m_gui;
        }

      protected:
        /**
         *  Initializes the scene. Should be specific to the deriving class.
         */
        virtual auto initializeDerived() -> void
        {
        }

        /**
         *  Called when the scene is entered. Should be specific to the deriving class.
         */
        virtual auto onEnterDerived() -> void
        {
        }

        /**
         *  Updates the scene. Should be specific to the deriving class.
         */
        virtual auto updateDerived() -> void
        {
        }

        /**
         *  Renders the scene. Should be specific to the deriving class.
         */
        virtual auto renderDerived() const -> void
        {
        }

      private:
        std::shared_ptr<GUI> m_gui{};
    };

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

        SceneManager(const SceneManager &) = delete;

        auto operator=(const SceneManager &) -> SceneManager & = delete;

        SceneManager() = default;

        /**
         *  Adds a scene to the manager.
         *
         *  @param sceneName The name of the scene.
         *  @param scene The scene to add.
         */
        auto addScene(std::string_view sceneName, std::shared_ptr<IScene> scene) -> void;

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

        auto getScene(std::string_view sceneName) -> std::shared_ptr<IScene>;

      private:
        std::unordered_map<int, std::shared_ptr<IScene>> m_scenes{};
        int m_currentScene{0};
    };
}
