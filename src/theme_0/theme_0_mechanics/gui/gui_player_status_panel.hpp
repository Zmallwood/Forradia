/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "core/gui/gui_panel.hpp"

namespace forr {
  class gui_player_status_panel : public gui_panel {
  public:
    gui_player_status_panel() : gui_panel(0.0f, 0.0f, 0.2f, 0.14f) {}

  protected:
    virtual void render_derived() const override;
  };
}
