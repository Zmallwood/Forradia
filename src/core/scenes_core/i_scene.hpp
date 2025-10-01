/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class gui;

  class i_scene {
  public:
    void initialize();

    void update();

    void render() const;

    void on_enter();

  protected:
    virtual void initialize_derived() {}

    virtual void on_enter_derived() {}

    virtual void update_derived() {}

    virtual void render_derived() const {}

    auto get_gui() const { return m_gui; }

  private:
    s_ptr<gui> m_gui;
  };
}
