/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "SceneManager.hpp"
#include "IScene.hpp"
#include "StdAfx.hpp"

namespace Forradia {
auto SceneManager::AddScene(StringView sceneName, IScene &scene) -> void {
  scene.Initialize();

  m_scenes.insert({Hash(sceneName), scene});
}

auto SceneManager::GoToScene(StringView sceneName) -> void {
  m_currentScene = Hash(sceneName);

  if (m_scenes.contains(m_currentScene))
    m_scenes.at(m_currentScene).OnEnter();
}

auto SceneManager::UpdateCurrentScene() -> void {
  if (m_scenes.contains(m_currentScene))
    m_scenes.at(m_currentScene).Update();
}

auto SceneManager::RenderCurrentScene() const -> void {
  if (m_scenes.contains(m_currentScene))
    m_scenes.at(m_currentScene).Render();
}
}
