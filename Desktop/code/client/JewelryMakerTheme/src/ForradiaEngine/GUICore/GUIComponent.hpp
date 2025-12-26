/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include "ForradiaEngine/Common/Matter/Geometry.hpp"
    #include <SDL2/SDL.h>
    #include <memory>
    #include <vector>
// clang-format on

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

        virtual auto onMouseDown(Uint8 mouseButton) -> bool;

        virtual auto onMouseUp(Uint8 mouseButton, int clickSpeed) -> bool;

        virtual auto onMouseWheel(int delta) -> bool;

        virtual auto onKeyDown(SDL_Keycode key) -> bool;

        virtual auto onKeyUp(SDL_Keycode key) -> bool;

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

        virtual auto mouseHoveringGUI() const -> bool;

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
