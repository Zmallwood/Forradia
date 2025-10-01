/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "scene_manager.hpp"
#include "i_scene.hpp"

namespace forr {
  void scene_manager::AddScene(str_view sceneName, i_scene &scene) {
    scene.Initialize();
    m_scenes.insert({Hash(sceneName), scene});
  }

  void scene_manager::GoToScene(str_view sceneName) {
    m_currentScene = Hash(sceneName);
    if (m_scenes.contains(m_currentScene)) {
      m_scenes.at(m_currentScene).OnEnter();
    }
  }

  void scene_manager::UpdateCurrentScene() {
    if (m_scenes.contains(m_currentScene)) {
      m_scenes.at(m_currentScene).Update();
    }
  }

  void scene_manager::RenderCurrentScene() const {
    if (m_scenes.contains(m_currentScene)) {
      m_scenes.at(m_currentScene).Render();
    }
  }
}
