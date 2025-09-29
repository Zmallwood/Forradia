/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "GUIComponent.hpp"

namespace Forradia
{
    SharedPtr<GUIComponent> GUIComponent::AddChildComponent(SharedPtr<GUIComponent> component)
    {
        component->SetParentComponent(this);

        m_childComponents.push_back(component);

        return component;
    }

    void GUIComponent::Update()
    {
        if (!m_visible || !m_enabled)
        {
            return;
        }

        UpdateDerived();

        for (auto component : std::views::reverse(m_childComponents))
        {
            component->Update();
        }
    }

    void GUIComponent::Render() const
    {
        if (!m_visible)
        {
            return;
        }

        RenderDerived();

        for (std::shared_ptr<GUIComponent> component : m_childComponents)
        {
            component->Render();
        }
    }

    void GUIComponent::ToggleVisibility()
    {
        m_visible = !m_visible;
    }

    void GUIComponent::SetPosition(PointF newPosition)
    {
        m_bounds.x = newPosition.x;
        m_bounds.y = newPosition.y;
    }
}
