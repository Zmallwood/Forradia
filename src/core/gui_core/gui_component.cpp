/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui_component.hpp"

namespace forr {
  s_ptr<gui_component>
  gui_component::AddChildComponent(s_ptr<gui_component> component) {
    component->SetParentComponent(this);
    m_childComponents.push_back(component);
    return component;
  }

  void gui_component::Update() {
    if (!m_visible || !m_enabled) {
      return;
    }
    for (auto component : std::views::reverse(m_childComponents)) {
      component->Update();
    }
    UpdateDerived();
  }

  void gui_component::Render() const {
    if (!m_visible) {
      return;
    }
    RenderDerived();
    for (std::shared_ptr<gui_component> component : m_childComponents) {
      component->Render();
    }
  }

  rect_f gui_component::GetBounds() const {
    auto boundsResult{m_bounds};
    if (m_parentComponent) {
      auto parentPosition{m_parentComponent->GetBounds().GetPosition()};
      boundsResult.Offset(parentPosition);
    }
    return boundsResult;
  }

  void gui_component::ToggleVisibility() { m_visible = !m_visible; }

  void gui_component::SetPosition(point_f newPosition) {
    m_bounds.x = newPosition.x;
    m_bounds.y = newPosition.y;
  }
}
