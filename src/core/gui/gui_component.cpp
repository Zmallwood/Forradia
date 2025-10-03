/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui_component.hpp"

namespace forr {
  s_ptr<gui_component>
  gui_component::add_child_component(s_ptr<gui_component> comp) {
    comp->set_parent_comp(this);
    m_children.push_back(comp);
    return comp;
  }

  void gui_component::update() {
    if (!m_visible || !m_enabled) {
      return;
    }
    for (auto comp : std::views::reverse(m_children)) {
      comp->update();
    }
    update_derived();
  }

  void gui_component::render() const {
    if (!m_visible) {
      return;
    }
    render_derived();
    for (auto comp : m_children) {
      comp->render();
    }
  }

  rect_f gui_component::get_bounds() const {
    auto b_res{m_bounds};
    if (m_parent_comp) {
      auto parent_pos{m_parent_comp->get_bounds().get_pos()};
      b_res.offs(parent_pos);
    }
    return b_res;
  }

  void gui_component::toggle_visibility() { m_visible = !m_visible; }

  void gui_component::set_pos(point_f new_pos) {
    m_bounds.x = new_pos.x;
    m_bounds.y = new_pos.y;
  }
}
