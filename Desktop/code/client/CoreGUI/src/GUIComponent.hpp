//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#pragma once

namespace Forradia
{
    ///
    /// Base class for all GUI components.
    ///
    class GUIComponent : public std::enable_shared_from_this<GUIComponent>
    {
      public:
        ///
        /// Constructor.
        ///
        /// @param x The x-coordinate of the component.
        /// @param y The y-coordinate of the component.
        /// @param width The width of the component.
        /// @param height The height of the component.
        ///
        GUIComponent(float x, float y, float width, float height) : m_bounds({x, y, width, height})
        {
        }

        ///
        /// Adds a child component to this component.
        ///
        /// @param component The child component to add.
        /// @return The added component.
        ///
        SharedPtr<GUIComponent> AddChildComponent(SharedPtr<GUIComponent> component);

        ///
        /// Updates the component and all its children.
        ///
        void Update();

        ///
        /// Renders the component and all its children.
        ///
        void Render() const;

        ///
        /// Gets the bounds of the component in screen coordinates.
        ///
        /// @return The bounds of the component in screen coordinates.
        ///
        virtual RectF GetBounds() const;

        ///
        /// Sets the position of the component.
        ///
        /// @param newPosition The new position of the component.
        ///
        void SetPosition(PointF newPosition);

        ///
        /// Sets the height of the component.
        ///
        /// @param newHeight The new height of the component.
        ///
        void SetHeight(float newHeight);

        ///
        /// Toggles the visibility of the component.
        ///
        void ToggleVisibility();

        ///
        /// Gets whether the component is visible.
        ///
        /// @return Whether the component is visible.
        ///
        auto GetVisible() const
        {
            return m_visible;
        }

        ///
        /// Sets whether the component is visible.
        ///
        /// @param value Whether the component should be visible.
        ///
        void SetVisible(bool value)
        {
            m_visible = value;
        }

        ///
        /// Sets the parent component of this component.
        ///
        /// @param value The parent component.
        ///
        void SetParentComponent(GUIComponent *value)
        {
            m_parentComponent = value;
        }

      protected:
        ///
        /// Update tasks specific to the derived class, called by the Update method.
        ///
        virtual void UpdateDerived()
        {
        }

        ///
        /// Render tasks specific to the derived class, called by the Render method.
        ///
        virtual void RenderDerived() const
        {
        }

      private:
        RectF m_bounds; ///< The bounds of the component in local coordinates.
        Vector<SharedPtr<GUIComponent>>
            m_childComponents;                    ///< The child components of this component.
        bool m_visible{true};                     ///< Whether the component is visible.
        bool m_enabled{true};                     ///< Whether the component is enabled.
        GUIComponent *m_parentComponent{nullptr}; ///< The parent component of this component.
    };
}