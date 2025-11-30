//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "GUIComponent.hpp"

namespace AAK
{
    namespace Forradia
    {
        SharedPtr<GUIComponent> GUIComponent::AddChildComponent(SharedPtr<GUIComponent> component)
        {
            // Set this component as the parent of the child component.

            component->SetParentComponent(this);

            // Add the child component to the list of children.

            m_childComponents.push_back(component);

            // Return the added component.

            return component;
        }

        void GUIComponent::Update()
        {
            // Skip update if component is not visible or not enabled.

            if (!m_visible || !m_enabled)
            {
                return;
            }

            // Update all child components in reverse order (from last to first).

            for (auto component : std::views::reverse(m_childComponents))
            {
                component->Update();
            }

            // Call derived class update method.

            this->UpdateDerived();
        }

        void GUIComponent::Render() const
        {
            // Skip rendering if component is not visible.

            if (!m_visible)
            {
                return;
            }

            // Render this component's derived class content first.

            this->RenderDerived();

            // Render all child components in order.

            for (auto component : m_childComponents)
            {
                component->Render();
            }
        }

        RectF GUIComponent::GetBounds() const
        {
            // Start with this component's local bounds.

            auto boundsResult{m_bounds};

            // If this component has a parent, offset bounds by parent's position.

            if (m_parentComponent)
            {
                // Get the parent's position in screen coordinates.

                auto parentPosition{m_parentComponent->GetBounds().GetPosition()};

                // Offset this component's bounds by the parent's position.

                boundsResult.Offset(parentPosition);
            }

            // Return the final bounds in screen coordinates.

            return boundsResult;
        }

        void GUIComponent::ToggleVisibility()
        {
            // Toggle the visibility flag (true becomes false, false becomes true).

            m_visible = !m_visible;
        }

        void GUIComponent::SetPosition(PointF newPosition)
        {
            // Update the x coordinate of the component's bounds.

            m_bounds.x = newPosition.x;

            // Update the y coordinate of the component's bounds.

            m_bounds.y = newPosition.y;
        }

        void GUIComponent::SetHeight(float newHeight)
        {
            // Update the height of the component's bounds.

            m_bounds.height = newHeight;
        }
    }
}