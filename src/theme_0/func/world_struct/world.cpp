/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "world.hpp"
#include "world_area.hpp"

namespace forr {
  void world::init(size w_area_sz, float world_scaling) {
    m_curr_w_area = std::make_shared<world_area>(w_area_sz, world_scaling);
  }
}