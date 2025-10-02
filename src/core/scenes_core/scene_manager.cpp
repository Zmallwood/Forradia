/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "scene_manager.hpp"
#include "i_scene.hpp"

namespace forr {
  void scene_manager::add_scene(str_view scene_name, i_scene &scene) {
    scene.initialize();
    m_scenes.insert({hash(scene_name), scene});
  }

  void scene_manager::go_to_scene(str_view scene_name) {
    m_current_scene = hash(scene_name);
    if (m_scenes.contains(m_current_scene)) {
      m_scenes.at(m_current_scene).on_enter();
    }
  }

  void scene_manager::update_current_scene() {
    if (m_scenes.contains(m_current_scene)) {
      m_scenes.at(m_current_scene).update();
    }
  }

  void scene_manager::render_current_scene() const {
    if (m_scenes.contains(m_current_scene)) {
      m_scenes.at(m_current_scene).render();
    }
  }
}
