/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "gui.hpp"

namespace forr {
  class gui_inventory_window : public gui_window {
   public:
    gui_inventory_window() : gui_window(0.5f, 0.2f, 0.2f, 0.5f, "Inventory") {}

   protected:
    void render_derived() const override;
  };
}