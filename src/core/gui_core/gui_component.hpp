/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class gui_component {
  public:
    gui_component(float x, float y, float width, float height)
        : m_bounds({x, y, width, height}) {}

    s_ptr<gui_component> AddChildComponent(s_ptr<gui_component> component);

    void Update();

    void Render() const;

    rect_f GetBounds() const;

    void ToggleVisibility();

    void SetVisible(bool value) { m_visible = value; }

    void SetParentComponent(gui_component *value) { m_parentComponent = value; }

  protected:
    virtual void UpdateDerived() {}

    virtual void RenderDerived() const {}

    void SetPosition(point_f newPosition);

  private:
    rect_f m_bounds;
    vec<s_ptr<gui_component>> m_childComponents;
    bool m_visible{true};
    bool m_enabled{true};
    gui_component *m_parentComponent{nullptr};
  };
}
