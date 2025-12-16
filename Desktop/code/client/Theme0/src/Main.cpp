//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#include "Engine.hpp"
#include "GUIChatBox.hpp"
#include "GUIExperienceBar.hpp"
#include "SetupScenes.hpp"
#include "Theme0Properties.hpp"
#include "World.hpp"

int main(int argc, char **argv) {
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
