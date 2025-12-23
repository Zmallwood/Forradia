/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GUIComponent.hpp"
#include "MouseUtilities.hpp"
#include "SDLDevice.hpp"
#include <algorithm>
#include <ranges>

namespace Forradia
{
    auto GUIComponent::addChildComponent(std::shared_ptr<GUIComponent> component)
        -> std::shared_ptr<GUIComponent>
    {
        component->setParentComponent(this);

        m_childComponents.push_back(component);

        return component;
    }

    // NOLINTNEXTLINE(readability-make-member-function-const)
    auto GUIComponent::onMouseDown(Uint8 mouseButton) -> bool
    {
        if (!m_visible)
        {
            return false;
        }

        if (std::any_of(m_childComponents.rbegin(), m_childComponents.rend(),
                        [=](const std::shared_ptr<GUIComponent> &comp)
                        { return comp->onMouseDown(mouseButton); }))
        {
            return true;
        }

        return false;
    }

    // NOLINTNEXTLINE(readability-make-member-function-const)
    auto GUIComponent::onMouseUp(Uint8 mouseButton, int clickSpeed) -> bool
    {
        if (!m_visible)
        {
            return false;
        }

        if (std::any_of(m_childComponents.rbegin(), m_childComponents.rend(),
                        [=](const std::shared_ptr<GUIComponent> &comp)
                        { return comp->onMouseUp(mouseButton, clickSpeed); }))
        {
            return true;
        }

        return false;
    }

    auto GUIComponent::onMouseWheel(int delta) -> bool
    {
        if (!m_visible)
        {
            return false;
        }

        if (std::any_of(m_childComponents.rbegin(), m_childComponents.rend(),
                        [=](const std::shared_ptr<GUIComponent> &comp)
                        { return comp->onMouseWheel(delta); }))
        {
            return true;
        }

        return false;
    }

    auto GUIComponent::onKeyDown(SDL_Keycode key) -> bool
    {
        if (!m_visible)
        {
            return false;
        }

        if (std::any_of(m_childComponents.rbegin(), m_childComponents.rend(),
                        [=](const std::shared_ptr<GUIComponent> &comp)
                        { return comp->onKeyDown(key); }))
        {
            return true;
        }

        return false;
    }

    auto GUIComponent::onKeyUp(SDL_Keycode key) -> bool
    {
        if (!m_visible)
        {
            return false;
        }

        if (std::any_of(m_childComponents.rbegin(), m_childComponents.rend(),
                        [=](const std::shared_ptr<GUIComponent> &comp)
                        { return comp->onKeyUp(key); }))
        {
            return true;
        }

        return false;
    }

    auto GUIComponent::onTextInput(std::string_view text) -> bool
    {
        if (!m_visible)
        {
            return false;
        }

        if (std::any_of(m_childComponents.rbegin(), m_childComponents.rend(),
                        [=](const std::shared_ptr<GUIComponent> &comp)
                        { return comp->onTextInput(text); }))
        {
            return true;
        }

        return false;
    }

    auto GUIComponent::mouseHoveringGUI() const -> bool
    {
        if (!m_visible)
        {
            return false;
        }

        auto mousePos{getNormalizedMousePosition(SDLDevice::instance().getWindow())};

        auto result{getBounds().contains(mousePos)};

        for (const auto &childComponent : std::ranges::reverse_view(m_childComponents))
        {
            result |= childComponent->mouseHoveringGUI();
        }

        return result;
    }

    auto GUIComponent::update() -> void
    {
        if (!m_visible)
        {
            return;
        }

        for (auto &childComponent : std::ranges::reverse_view(m_childComponents))
        {
            childComponent->update();
        }

        this->updateDerived();
    }

    auto GUIComponent::render() const -> void
    {
        if (!m_visible)
        {
            return;
        }

        this->renderDerived();

        for (const auto &component : m_childComponents)
        {
            component->render();
        }
    }

    auto GUIComponent::getBounds() const -> RectF
    {
        auto boundsResult{m_bounds};

        // If this component has a parent, offset bounds by parent's position.
        if (m_parentComponent != nullptr)
        {
            auto parentPosition{m_parentComponent->getBounds().getPosition()};

            boundsResult.offset(parentPosition);
        }

        return boundsResult;
    }

    auto GUIComponent::toggleVisibility() -> void
    {
        m_visible = !m_visible;
    }

    auto GUIComponent::setPosition(PointF newPosition) -> void
    {
        m_bounds.x = newPosition.x;
        m_bounds.y = newPosition.y;
    }

    auto GUIComponent::setHeight(float newHeight) -> void
    {
        m_bounds.height = newHeight;
    }
}
