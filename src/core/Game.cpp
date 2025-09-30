/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "Game.hpp"
#include "engine/Engine.hpp"

namespace Forradia {
  void Game::Start() const { GetSingleton<Engine>().Run(); }
}
