/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "game.hpp"
#include "engine/engine.hpp"

namespace forr {
  void game::start() const { get_singleton<engine>().run(); }
}
