/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "core/scenes_core/i_scene.hpp"

namespace forr {
  class world_generation_scene : public i_scene {
  protected:
    void on_enter_derived() override;
  };
}
