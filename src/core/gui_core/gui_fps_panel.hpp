/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "gui_movable_panel.hpp"

namespace forr {
  class gui_label;

  class gui_fps_panel : public gui_movable_panel {
  public:
    gui_fps_panel() : gui_movable_panel(0.92f, 0.02f, 0.07f, 0.04f) {
      Initialize();
    }

  protected:
    void UpdateDerived() override;

  private:
    void Initialize();

    s_ptr<gui_label> m_fpsTextPanel;
  };
}