/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "scenes_core.hpp"
#include "gui/gui.hpp"

namespace forr {
  void i_scene::init() {
    m_gui = std::make_shared<gui>();
    init_derived();
  }

  void i_scene::on_enter() { on_enter_derived(); }

  void i_scene::update() {
    m_gui->update();
    update_derived();
  }

  void i_scene::render() const {
    render_derived();
    m_gui->render();
  }

  void scene_manager::add_scene(str_view scene_name, i_scene &scene) {
    scene.init();
    m_scenes.insert({hash(scene_name), scene});
  }

  void scene_manager::go_to_scene(str_view scene_name) {
    m_curr_scene = hash(scene_name);
    if (m_scenes.contains(m_curr_scene)) {
      m_scenes.at(m_curr_scene).on_enter();
    }
  }

  void scene_manager::update_curr_scene() {
    if (m_scenes.contains(m_curr_scene)) {
      m_scenes.at(m_curr_scene).update();
    }
  }

  void scene_manager::render_curr_scene() const {
    if (m_scenes.contains(m_curr_scene)) {
      m_scenes.at(m_curr_scene).render();
    }
  }
}