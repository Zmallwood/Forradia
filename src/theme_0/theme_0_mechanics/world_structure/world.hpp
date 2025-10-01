/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class WorldArea;

  class World {
  public:
    World() { Initialize(); }

    auto GetCurrentWorldArea() const { return m_currentWorldArea; }

  private:
    void Initialize();

    s_ptr<WorldArea> m_currentWorldArea;
  };
}