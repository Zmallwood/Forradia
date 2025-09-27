#include "GUIComponent.hpp"

namespace Forradia
{
    GUIComponent::GUIComponent(float x,
                               float y,
                               float width,
                               float height)
        : m_bounds({x, y, width, height})
    {
    }

    void GUIComponent::AddChildComponent(std::shared_ptr<GUIComponent> component)
    {
        m_childComponents.push_back(component);
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
}
