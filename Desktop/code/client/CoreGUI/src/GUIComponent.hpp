/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once

namespace Forradia {
/**
 * Base class for all GUI components.
 */
class GUIComponent : public std::enable_shared_from_this<GUIComponent> {
 public:
  /**
   * Constructor.
   *
   * @param x The x-coordinate of the component.
   * @param y The y-coordinate of the component.
   * @param width The width of the component.
   * @param height The height of the component.
   */
  GUIComponent(float x, float y, float width, float height) : m_bounds({x, y, width, height}) {
  }

  /**
   * Adds a child component to this component.
   *
   * @param component The child component to add.
   * @return The added component.
   */
  auto AddChildComponent(SharedPtr<GUIComponent> component) -> SharedPtr<GUIComponent>;

  /**
   * Updates the component and all its children.
   */
  auto Update() -> void;

  /**
   * Renders the component and all its children.
   */
  auto Render() const -> void;

  /**
   * Gets the bounds of the component in screen coordinates.
   *
   * @return The bounds of the component in screen coordinates.
   */
  virtual auto GetBounds() const -> RectF;

  /**
   * Sets the position of the component.
   *
   * @param newPosition The new position of the component.
   */
  auto SetPosition(PointF newPosition) -> void;

  /**
   * Sets the height of the component.
   *
   * @param newHeight The new height of the component.
   */
  auto SetHeight(float newHeight) -> void;

  /**
   * Toggles the visibility of the component.
   */
  auto ToggleVisibility() -> void;

  /**
   * Gets whether the component is visible.
   *
   * @return Whether the component is visible.
   */
  auto GetVisible() const {
    return m_visible;
  }

  /**
   * Sets whether the component is visible.
   *
   * @param value Whether the component should be visible.
   */
  auto SetVisible(bool value) -> void {
    m_visible = value;
  }

  /**
   * Sets the parent component of this component.
   *
   * @param value The parent component.
   */
  auto SetParentComponent(GUIComponent *value) -> void {
    m_parentComponent = value;
  }

 protected:
  /**
   * Update tasks specific to the derived class, called by the Update method.
   */
  virtual auto UpdateDerived() -> void {
  }

  /**
   * Render tasks specific to the derived class, called by the Render method.
   */
  virtual auto RenderDerived() const -> void {
  }

 private:
  RectF m_bounds;
  Vector<SharedPtr<GUIComponent>> m_childComponents;
  bool m_visible{true};
  bool m_enabled{true};
  GUIComponent *m_parentComponent{nullptr};
};
}
