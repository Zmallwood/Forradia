/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "scene_manager.hpp"
#include "i_scene.hpp"

namespace forr {
  void SceneManager::AddScene(str_view sceneName, IScene &scene) {
    scene.Initialize();
    m_scenes.insert({Hash(sceneName), scene});
  }

  void SceneManager::GoToScene(str_view sceneName) {
    m_currentScene = Hash(sceneName);
    if (m_scenes.contains(m_currentScene)) {
      m_scenes.at(m_currentScene).OnEnter();
    }
  }

  void SceneManager::UpdateCurrentScene() {
    if (m_scenes.contains(m_currentScene)) {
      m_scenes.at(m_currentScene).Update();
    }
  }

  void SceneManager::RenderCurrentScene() const {
    if (m_scenes.contains(m_currentScene)) {
      m_scenes.at(m_currentScene).Render();
    }
  }
}
