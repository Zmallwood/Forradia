/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GUIComponent.hpp"
#include "MouseUtilities.hpp"
#include "SDLDevice.hpp"
#include "Singleton.hpp"
#include <algorithm>
#include <ranges>

namespace Forradia {
    auto GUIComponent::AddChildComponent(std::shared_ptr<GUIComponent> component)
        -> std::shared_ptr<GUIComponent> {
        component->SetParentComponent(this);

        m_childComponents.push_back(component);

        return component;
    }

    // NOLINTNEXTLINE(readability-make-member-function-const)
    auto GUIComponent::OnMouseDown(Uint8 mouseButton) -> bool {
        if (!m_visible || !m_enabled)
            return false;

        if (std::any_of(m_childComponents.rbegin(), m_childComponents.rend(),
                        [=](const std::shared_ptr<GUIComponent> &comp) {
                            return comp->OnMouseDown(mouseButton);
                        }))
            return true;

        return false;
    }

    // NOLINTNEXTLINE(readability-make-member-function-const)
    auto GUIComponent::OnMouseUp(Uint8 mouseButton, int clickSpeed) -> bool {
        if (!m_visible || !m_enabled)
            return false;

        if (std::any_of(m_childComponents.rbegin(), m_childComponents.rend(),
                        [=](const std::shared_ptr<GUIComponent> &comp) {
                            return comp->OnMouseUp(mouseButton, clickSpeed);
                        }))
            return true;

        return false;
    }

    auto GUIComponent::OnMouseWheel(int delta) -> bool {
        if (!m_visible || !m_enabled)
            return false;

        if (std::any_of(m_childComponents.rbegin(), m_childComponents.rend(),
                        [=](const std::shared_ptr<GUIComponent> &comp) {
                            return comp->OnMouseWheel(delta);
                        }))
            return true;

        return false;
    }

    auto GUIComponent::OnKeyDown(SDL_Keycode key) -> bool {
        if (!m_visible || !m_enabled)
            return false;

        if (std::any_of(
                m_childComponents.rbegin(), m_childComponents.rend(),
                [=](const std::shared_ptr<GUIComponent> &comp) { return comp->OnKeyDown(key); }))
            return true;

        return false;
    }

    auto GUIComponent::OnKeyUp(SDL_Keycode key) -> bool {
        if (!m_visible || !m_enabled)
            return false;

        if (std::any_of(
                m_childComponents.rbegin(), m_childComponents.rend(),
                [=](const std::shared_ptr<GUIComponent> &comp) { return comp->OnKeyUp(key); }))
            return true;

        return false;
    }

    auto GUIComponent::OnTextInput(std::string_view text) -> bool {
        if (!m_visible || !m_enabled)
            return false;

        if (std::any_of(
                m_childComponents.rbegin(), m_childComponents.rend(),
                [=](const std::shared_ptr<GUIComponent> &comp) { return comp->OnTextInput(text); }))
            return true;

        return false;
    }

    auto GUIComponent::MouseHoveringGUI() const -> bool {
        if (!m_visible || !m_enabled)
            return false;

        auto mousePos{GetNormallizedMousePosition(Singleton<SDLDevice>().GetWindow())};

        auto result{GetBounds().Contains(mousePos)};

        for (const auto &childComponent : std::ranges::reverse_view(m_childComponents))
            result |= childComponent->MouseHoveringGUI();

        return result;
    }

    auto GUIComponent::Update() -> void {
        if (!m_visible || !m_enabled)
            return;

        for (auto &childComponent : std::ranges::reverse_view(m_childComponents))
            childComponent->Update();

        this->UpdateDerived();
    }

    auto GUIComponent::Render() const -> void {
        if (!m_visible)
            return;

        this->RenderDerived();

        for (const auto &component : m_childComponents)
            component->Render();
    }

    auto GUIComponent::GetBounds() const -> RectF {
        auto boundsResult{m_bounds};

        // If this component has a parent, offset bounds by parent's position.
        if (m_parentComponent != nullptr) {
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
