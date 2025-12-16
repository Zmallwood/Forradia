//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#include "SceneManager.hpp"
#include "IScene.hpp"

namespace Forradia {
void SceneManager::AddScene(StringView sceneName, IScene &scene) {
  scene.Initialize();

  m_scenes.insert({Hash(sceneName), scene});
}

void SceneManager::GoToScene(StringView sceneName) {
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