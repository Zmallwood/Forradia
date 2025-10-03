/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "core.hpp"

namespace forr {
  class world_gen_scene : public i_scene {
   protected:
    void on_enter_derived() override;
  };
}
