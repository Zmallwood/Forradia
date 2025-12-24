/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "Engine.hpp"
#include "Scenes/SetupScenes.hpp"
#include "Content/Properties/Theme0Properties.hpp"
#include "Content/WorldStructure/World.hpp"

auto main(int argc, char **argv) -> int
{
    using namespace Forradia;
    using namespace Theme0;

    Engine::instance().initialize(Theme0Properties::instance().getGameWindowTitle(),
                                  Theme0Properties::instance().getClearColor());
    setupScenes();

    World::instance().initialize(Theme0Properties::instance().getBaseWorldAreaSize(),
                                 Theme0Properties::instance().getWorldScaling());
    Engine::instance().run();

    return 0;
}
