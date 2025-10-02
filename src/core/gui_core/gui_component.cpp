/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui_component.hpp"

namespace forr {
  s_ptr<gui_component>
  gui_component::add_child_component(s_ptr<gui_component> comp) {
    comp->set_parent_component(this);
    m_child_components.push_back(comp);
    return comp;
  }

  void gui_component::update() {
    if (!m_visible || !m_enabled) {
      return;
    }
    for (auto comp : std::views::reverse(m_child_components)) {
      comp->update();
    }
    update_derived();
  }

  void gui_component::render() const {
    if (!m_visible) {
      return;
    }
    render_derived();
    for (auto comp : m_child_components) {
      comp->render();
    }
  }

  rect_f gui_component::get_bounds() const {
    auto bounds_result{m_bounds};
    if (m_parent_component) {
      auto parent_position{m_parent_component->get_bounds().get_position()};
      bounds_result.offset(parent_position);
    }
    return bounds_result;
  }

  void gui_component::toggle_visibility() { m_visible = !m_visible; }

  void gui_component::set_position(point_f new_position) {
    m_bounds.x = new_position.x;
    m_bounds.y = new_position.y;
  }
}
