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

auto main(int argc, char **argv) -> int
{
    using namespace Forradia;
    using namespace Theme0;

    Engine::Instance().Initialize(Theme0Properties::Instance().GetGameWindowTitle(),
                                  Theme0Properties::Instance().GetClearColor());
    SetupScenes();
    World::Instance().Initialize(Theme0Properties::Instance().GetBaseWorldAreaSize(),
                                 Theme0Properties::Instance().GetWorldScaling());
    Engine::Instance().Run();
    return 0;
}
