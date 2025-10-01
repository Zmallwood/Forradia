/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class engine {
  public:
    void run();

    void stop();

  private:
    bool m_running{true};
  };
}
