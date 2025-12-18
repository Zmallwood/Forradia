/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "GUIComponent.hpp"
#include "StdAfx.hpp"

namespace Forradia {
  auto GUIComponent::AddChildComponent(SharedPtr<GUIComponent> component)
      -> SharedPtr<GUIComponent> {
    component->SetParentComponent(this);

    m_childComponents.push_back(component);

    return component;
  }

  auto GUIComponent::Update() -> void {
    if (!m_visible || !m_enabled)
      return;

    for (auto it = m_childComponents.rbegin(); it != m_childComponents.rend(); ++it)
      (*it)->Update();

    this->UpdateDerived();
  }

  auto GUIComponent::Render() const -> void {
    if (!m_visible)
      return;

    this->RenderDerived();

    for (auto component : m_childComponents)
      component->Render();
  }

  auto GUIComponent::GetBounds() const -> RectF {
    auto boundsResult{m_bounds};

    // If this component has a parent, offset bounds by parent's position.
    if (m_parentComponent) {
      auto parentPosition{m_parentComponent->GetBounds().GetPosition()};
      boundsResult.Offset(parentPosition);
    }

    return boundsResult;
  }

  auto GUIComponent::ToggleVisibility() -> void {
    m_visible = !m_visible;
  }

  auto GUIComponent::SetPosition(PointF newPosition) -> void {
    m_bounds.x = newPosition.x;
    m_bounds.y = newPosition.y;
  }

  auto GUIComponent::SetHeight(float newHeight) -> void {
    m_bounds.height = newHeight;
  }
}
