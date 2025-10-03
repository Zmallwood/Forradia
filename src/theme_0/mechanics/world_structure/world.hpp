/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class world_area;

  class world {
   public:
    world() { initialize(); }

    auto get_current_world_area() const { return m_curr_w_area; }

   private:
    void initialize();

    s_ptr<world_area> m_curr_w_area;
  };
}