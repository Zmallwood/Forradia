/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "Engine.hpp"
#include "GUIChatBox.hpp"
#include "GUIExperienceBar.hpp"
#include "SetupScenes.hpp"
#include "StdAfx.hpp"
#include "Theme0Properties.hpp"
#include "World.hpp"

auto main(int argc, char **argv) -> int {
  using namespace Forradia;
  using namespace Theme0;

  _<Engine>().Initialize(_<Theme0Properties>().GetGameWindowTitle(),
                         _<Theme0Properties>().GetClearColor());
  SetupScenes();
  _<World>().Initialize(_<Theme0Properties>().GetBaseWorldAreaSize(),
                        _<Theme0Properties>().GetWorldScaling());
  _<Engine>().Run();
  return 0;
}
