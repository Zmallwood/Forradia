/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once

namespace Forradia {
class IScene;

///
/// The manager for the scenes.
///
class SceneManager {
 public:
  ///
  /// Adds a scene to the manager.
  ///
  /// @param sceneName The name of the scene.
  /// @param scene The scene to add.
  ///
  void AddScene(StringView sceneName, IScene &scene);

  ///
  /// Goes to a scene.
  ///
  /// @param sceneName The name of the scene to go to.
  ///
  void GoToScene(StringView sceneName);

  ///
  /// Updates the current scene.
  ///
  void UpdateCurrentScene();

  ///
  /// Renders the current scene.
  ///
  void RenderCurrentScene() const;

 private:
  std::map<int, IScene &> m_scenes; ///< The scenes.
  int m_currentScene{0};            ///< The current scene, as the name hash of the scene.
};
}