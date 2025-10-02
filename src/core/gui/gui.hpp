/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "gui_component.hpp"

namespace forr {
  class gui : public gui_component {
   public:
    gui() : gui_component(0.0f, 0.0f, 1.0f, 1.0f) {}
  };
}
