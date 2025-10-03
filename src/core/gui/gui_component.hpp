/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class gui_component {
   public:
    gui_component(float x, float y, float w, float h)
        : m_bounds({x, y, w, h}) {}

    s_ptr<gui_component> add_child_component(s_ptr<gui_component> comp);

    void update();

    void render() const;

    rect_f get_bounds() const;

    void toggle_visibility();

    void set_visible(bool value) { m_visible = value; }

    void set_parent_component(gui_component *value) { m_parent_comp = value; }

   protected:
    virtual void update_derived() {}

    virtual void render_derived() const {}

    void set_position(point_f new_position);

   private:
    rect_f m_bounds;
    vec<s_ptr<gui_component>> m_children;
    bool m_visible{true};
    bool m_enabled{true};
    gui_component *m_parent_comp{nullptr};
  };
}
