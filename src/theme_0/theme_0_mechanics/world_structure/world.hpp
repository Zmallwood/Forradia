/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class world_area;

  class world {
  public:
    world() { Initialize(); }

    auto GetCurrentWorldArea() const { return m_currentWorldArea; }

  private:
    void Initialize();

    s_ptr<world_area> m_currentWorldArea;
  };
}