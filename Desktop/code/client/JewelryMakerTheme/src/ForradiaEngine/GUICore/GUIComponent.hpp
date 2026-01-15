/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include "ForradiaEngine/Common/Matter/Geometry.hpp"

namespace ForradiaEngine
{
    /**
     *  Base class for all GUI components.
     */
    class GUIComponent : public std::enable_shared_from_this<GUIComponent>
    {
      public:
        virtual ~GUIComponent() = default;

        /**
         *  Constructor.
         *
         *  @param xPos The x-coordinate of the component.
         *  @param yPos The y-coordinate of the component.
         *  @param width The width of the component.
         *  @param height The height of the component.
         */
        GUIComponent(float xPos, float yPos, float width, float height)
            : m_bounds({xPos, yPos, width, height})
        {
        }

        /**
         *  Adds a child component to this component.
         *
         *  @param component The child component to add.
         *  @return The added component.
         */
        auto addChildComponent(std::shared_ptr<GUIComponent> component)
            -> std::shared_ptr<GUIComponent>;

        /**
         *  Handles the mouse down event.
         *
         *  @param mouseButton The mouse button that was pressed.
         *  @return True if the mouse down event was handled, false otherwise.
         */
        virtual auto onMouseDown(Uint8 mouseButton) -> bool;

        /**
         *  Handles the mouse up event.
         *
         *  @param mouseButton The mouse button that was released.
         *  @param clickSpeed The speed of the click.
         *  @return True if the mouse up event was handled, false otherwise.
         */
        virtual auto onMouseUp(Uint8 mouseButton, int clickSpeed) -> bool;

        /**
         *  Handles the mouse wheel event.
         *
         *  @param delta The delta of the mouse wheel.
         *  @return True if the mouse wheel event was handled, false otherwise.
         */
        virtual auto onMouseWheel(int delta) -> bool;

        /**
         *  Handles the key down event.
         *
         *  @param key The key that was pressed.
         *  @return True if the key down event was handled, false otherwise.
         */
        virtual auto onKeyDown(SDL_Keycode key) -> bool;

        /**
         *  Handles the key up event.
         *
         *  @param key The key that was released.
         *  @return True if the key up event was handled, false otherwise.
         */
        virtual auto onKeyUp(SDL_Keycode key) -> bool;

        /**
         *  Handles the text input event.
         *
         *  @param text The text that was input.
         *  @return True if the text input event was handled, false otherwise.
         */
        virtual auto onTextInput(std::string_view text) -> bool;

        /**
         *  Updates the component and all its children.
         */
        virtual auto update() -> void;

        /**
         *  Renders the component and all its children.
         */
        virtual auto render() const -> void;

        /**
         *  Gets the bounds of the component in screen coordinates.
         *
         *  @return The bounds of the component in screen coordinates.
         */
        [[nodiscard]] virtual auto getBounds() const -> RectF;

        /**
         *  Checks if the mouse is hovering over this component or any of its children in the GUI.
         *
         *  @return True if the mouse is hovering over any GUI component, false otherwise.
         */
        virtual auto mouseHoveringGUI() const -> bool;

        /**
         *  Gets all child components recursively.
         *
         *  @return All child components recursively.
         */
        auto getChildComponentsRecursively() const -> std::vector<std::shared_ptr<GUIComponent>>;

        /**
         *  Sets the bounds of the component.
         *
         *  @param value The new bounds of the component.
         */
        auto setBounds(RectF value) -> void
        {
            m_bounds = value;
        }

        /**
         *  Sets the position of the component.
         *
         *  @param newPosition The new position of the component.
         */
        auto setPosition(PointF newPosition) -> void;

        /**
         *  Sets the height of the component.
         *
         *  @param newHeight The new height of the component.
         */
        auto setHeight(float newHeight) -> void;

        /**
         *  Toggles the visibility of the component.
         */
        auto toggleVisibility() -> void;

        /**
         *  Gets whether the component is visible.
         *
         *  @return Whether the component is visible.
         */
        auto getVisible() const -> bool
        {
            return m_visible;
        }

        /**
         *  Sets whether the component is visible.
         *
         *  @param value Whether the component should be visible.
         */
        auto setVisible(bool value) -> void
        {
            m_visible = value;
        }

        /**
         *  Sets the parent component of this component.
         *
         *  @param value The parent component.
         */
        auto setParentComponent(GUIComponent *value) -> void
        {
            m_parentComponent = value;
        }

        /**
         *  Update tasks specific to the derived class, called by the Update method.
         */
        virtual auto updateDerived() -> void
        {
        }

        /**
         *  Render tasks specific to the derived class, called by the Render method.
         */
        virtual auto renderDerived() const -> void
        {
        }

      protected:
        auto getChildComponents() const -> std::vector<std::shared_ptr<GUIComponent>>
        {
            return m_childComponents;
        }

      private:
        RectF m_bounds{};
        std::vector<std::shared_ptr<GUIComponent>> m_childComponents{};
        bool m_visible{true};
        GUIComponent *m_parentComponent{nullptr};
    };
}
