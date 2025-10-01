/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui_component.hpp"

namespace forr {
  s_ptr<gui_component>
  gui_component::add_child_component(s_ptr<gui_component> component) {
    component->set_parent_component(this);
    m_childComponents.push_back(component);
    return component;
  }

  void gui_component::update() {
    if (!m_visible || !m_enabled) {
      return;
    }
    for (auto component : std::views::reverse(m_childComponents)) {
      component->update();
    }
    update_derived();
  }

  void gui_component::render() const {
    if (!m_visible) {
      return;
    }
    render_derived();
    for (std::shared_ptr<gui_component> component : m_childComponents) {
      component->render();
    }
  }

  rect_f gui_component::get_bounds() const {
    auto boundsResult{m_bounds};
    if (m_parentComponent) {
      auto parentPosition{m_parentComponent->get_bounds().get_position()};
      boundsResult.offset(parentPosition);
    }
    return boundsResult;
  }

  void gui_component::toggle_visibility() { m_visible = !m_visible; }

  void gui_component::set_position(point_f newPosition) {
    m_bounds.x = newPosition.x;
    m_bounds.y = newPosition.y;
  }
}
