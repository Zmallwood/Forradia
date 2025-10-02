/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "core/gui/gui_component.hpp"

namespace forr {
  class gui_system_menu : public gui_component {
  public:
    gui_system_menu() : gui_component(0.0f, 0.0f, 1.0f, 1.0f) { initialize(); }

  protected:
    void initialize();

    virtual void update_derived() override;

    virtual void render_derived() const override;
  };
}