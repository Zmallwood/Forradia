/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

namespace Forradia {
  class WorldArea;

  class World {
  public:
    World() { Initialize(); }

    auto GetCurrentWorldArea() const { return m_currentWorldArea; }

  private:
    void Initialize();

    SharedPtr<WorldArea> m_currentWorldArea;
  };
}