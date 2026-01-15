/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
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

        /**
         *  Called when the mouse is pressed down.
         *
         *  @param mouseButton The mouse button that was pressed.
         */
        virtual auto onMouseDown(Uint8 mouseButton) -> void;

        /**
         *  Called when the mouse is released.
         *
         *  @param mouseButton The mouse button that was released.
         *  @param clickSpeed The speed of the click.
         */
        virtual auto onMouseUp(Uint8 mouseButton, int clickSpeed) -> void;

        /**
         *  Called when the mouse wheel is scrolled.
         *
         *  @param delta The delta of the mouse wheel.
         */
        virtual auto onMouseWheel(int delta) -> void;

        /**
         *  Called when a key is pressed down.
         *
         *  @param key The key that was pressed.
         */
        virtual auto onKeyDown(SDL_Keycode key) -> void;

        /**
         *  Called when a key is released.
         *
         *  @param key The key that was released.
         */
        virtual auto onKeyUp(SDL_Keycode key) -> void;

        /**
         *  Called when text is input.
         *
         *  @param text The text that was input.
         */
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

        /**
         *  Called when the mouse is pressed down in the current scene.
         *
         *  @param mouseButton The mouse button that was pressed.
         */
        auto onMouseDownCurrentScene(Uint8 mouseButton) -> void;

        /**
         *  Called when the mouse is released in the current scene.
         *
         *  @param mouseButton The mouse button that was released.
         *  @param clickSpeed The speed of the click.
         */
        auto onMouseUpCurrentScene(Uint8 mouseButton, int clickSpeed) -> void;

        /**
         *  Called when the mouse wheel is scrolled in the current scene.
         *
         *  @param delta The delta of the mouse wheel.
         */
        auto onMouseWheelCurrentScene(int delta) -> void;

        /**
         *  Called when a key is pressed down in the current scene.
         *
         *  @param key The key that was pressed.
         */
        auto onKeyDownCurrentScene(SDL_Keycode key) -> void;

        /**
         *  Called when a key is released in the current scene.
         *
         *  @param key The key that was released.
         */
        auto onKeyUpCurrentScene(SDL_Keycode key) -> void;

        /**
         *  Called when text is input in the current scene.
         *
         *  @param text The text that was input.
         */
        auto onTextInputCurrentScene(std::string_view text) -> void;

        /**
         *  Updates the current scene.
         */
        auto updateCurrentScene() -> void;

        /**
         *  Renders the current scene.
         */
        auto renderCurrentScene() const -> void;

        /**
         *  Gets a scene by name.
         *
         *  @param sceneName The name of the scene to get.
         *  @return The scene.
         */
        auto getScene(std::string_view sceneName) -> std::shared_ptr<IScene>;

      private:
        std::unordered_map<int, std::shared_ptr<IScene>> m_scenes{};
        int m_currentScene{0};
    };
}
