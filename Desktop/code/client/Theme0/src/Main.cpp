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
#include "Scripts.hpp"
#include "Theme0Properties.hpp"
#include "World.hpp"

int main(int argc, char **argv)
{
    // Use namespaces for readability.

    using namespace Forradia;

    using namespace Theme0;

    // Initialize the engine.

    _<Engine>().Initialize(_<Theme0Properties>().GetGameWindowTitle(),
                           _<Theme0Properties>().GetClearColor());

    // Initialize the script engine.

    _<ScriptEngine>().Initialize();

    // Load the scripts.

    _<ScriptEngine>().LoadScripts();

    // Initialize the world.

    _<World>().Initialize(_<Theme0Properties>().GetBaseWorldAreaSize(),
                          _<Theme0Properties>().GetWorldScaling());

    // Run the engine.

    _<Engine>().Run();

    return 0;
}
