/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "Engine.hpp"
#include "GUIChatBox.hpp"
#include "GUIExperienceBar.hpp"
#include "SetupScenes.hpp"
#include "Theme0Properties.hpp"
#include "World.hpp"

auto main(int argc, char **argv) -> int {
    using namespace Forradia;
    using namespace Theme0;

    Singleton<Engine>().Initialize(Singleton<Theme0Properties>().GetGameWindowTitle(),
                                   Singleton<Theme0Properties>().GetClearColor());
    SetupScenes();
    Singleton<World>().Initialize(Singleton<Theme0Properties>().GetBaseWorldAreaSize(),
                                  Singleton<Theme0Properties>().GetWorldScaling());
    Singleton<Engine>().Run();
    return 0;
}
