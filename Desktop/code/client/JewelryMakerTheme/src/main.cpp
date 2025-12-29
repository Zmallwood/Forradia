/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "Properties/ThemeProperties.hpp"
#include "WorldStructure/World.hpp"
#include "ForradiaEngine/Engine.hpp"
#include "setupScenes.hpp"
#include "WorldGeneration/Main/WorldGenerator.hpp"

auto main(int argc, char **argv) -> int
{
    using namespace ForradiaEngine;
    using namespace JewelryMakerTheme;

    Engine::initialize(ThemeProperties::getGameWindowTitle(), ThemeProperties::getClearColor());

    WorldGenerator worldGenerator;

    setupScenes(worldGenerator);

    World::instance().initialize(ThemeProperties::getBaseWorldAreaSize(),
                                 ThemeProperties::getWorldScaling());

    Engine::instance().run();

    return 0;
}
