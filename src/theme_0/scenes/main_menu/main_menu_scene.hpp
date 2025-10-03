/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "scenes_core.hpp"

namespace forr {
  class main_menu_scene : public i_scene {
  protected:
    void init_derived() override;

    void update_derived() override;

    void render_derived() const override;
  };
}
