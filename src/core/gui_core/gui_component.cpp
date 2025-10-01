/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui_component.hpp"

namespace forr {
  s_ptr<GUIComponent>
  GUIComponent::AddChildComponent(s_ptr<GUIComponent> component) {
    component->SetParentComponent(this);
    m_childComponents.push_back(component);
    return component;
  }

  void GUIComponent::Update() {
    if (!m_visible || !m_enabled) {
      return;
    }
    for (auto component : std::views::reverse(m_childComponents)) {
      component->Update();
    }
    UpdateDerived();
  }

  void GUIComponent::Render() const {
    if (!m_visible) {
      return;
    }
    RenderDerived();
    for (std::shared_ptr<GUIComponent> component : m_childComponents) {
      component->Render();
    }
  }

  RectF GUIComponent::GetBounds() const {
    auto boundsResult{m_bounds};
    if (m_parentComponent) {
      auto parentPosition{m_parentComponent->GetBounds().GetPosition()};
      boundsResult.Offset(parentPosition);
    }
    return boundsResult;
  }

  void GUIComponent::ToggleVisibility() { m_visible = !m_visible; }

  void GUIComponent::SetPosition(PointF newPosition) {
    m_bounds.x = newPosition.x;
    m_bounds.y = newPosition.y;
  }
}
