/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "scene_manager.hpp"
#include "i_scene.hpp"

namespace forr {
  void scene_manager::add_scene(str_view sceneName, i_scene &scene) {
    scene.initialize();
    m_scenes.insert({hash(sceneName), scene});
  }

  void scene_manager::go_to_scene(str_view sceneName) {
    m_currentScene = hash(sceneName);
    if (m_scenes.contains(m_currentScene)) {
      m_scenes.at(m_currentScene).on_enter();
    }
  }

  void scene_manager::update_current_scene() {
    if (m_scenes.contains(m_currentScene)) {
      m_scenes.at(m_currentScene).update();
    }
  }

  void scene_manager::render_current_scene() const {
    if (m_scenes.contains(m_currentScene)) {
      m_scenes.at(m_currentScene).render();
    }
  }
}
