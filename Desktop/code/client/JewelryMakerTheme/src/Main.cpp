/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "Content/Properties/ThemeProperties.hpp"
#include "Content/WorldStructure/World.hpp"
#include "ForradiaEngine/Engine.hpp"
#include "Scenes/SetupScenes.hpp"

auto main(int argc, char **argv) -> int
{
    using namespace ForradiaEngine;
    using namespace JewelryMakerTheme;

    Engine::initialize(ThemeProperties::getGameWindowTitle(), ThemeProperties::getClearColor());
    
    setupScenes();

    World::instance().initialize(ThemeProperties::getBaseWorldAreaSize(),
                                 ThemeProperties::getWorldScaling());

    Engine::instance().run();

    return 0;
}
