/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once

namespace Forradia {
  class IScene;

  /**
   * The manager for the scenes.
   */
  class SceneManager {
   public:
    /**
     * Adds a scene to the manager.
     *
     * @param sceneName The name of the scene.
     * @param scene The scene to add.
     */
    auto AddScene(std::string_view sceneName, IScene &scene) -> void;

    /**
     * Goes to a scene.
     *
     * @param sceneName The name of the scene to go to.
     */
    auto GoToScene(std::string_view sceneName) -> void;

    /**
     * Updates the current scene.
     */
    auto UpdateCurrentScene() -> void;

    /**
     * Renders the current scene.
     */
    auto RenderCurrentScene() const -> void;

   private:
    std::map<int, IScene &> m_scenes;
    int m_currentScene{0};
  };
}
