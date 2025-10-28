//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "Engine.hpp"

#include "Scripts.hpp"

#include "Theme0Properties.hpp"

#include "World.hpp"

int main(int argc, char **argv)
{
    using namespace Forradia;
    using namespace Theme0;

    _<Engine>().Initialize(
        _<Theme0Properties>().GetGameWindowTitle(),
        _<Theme0Properties>().GetClearColor());

    _<ScriptEngine>().Initialize();

    _<ScriptEngine>().LoadScripts();

    _<World>().Initialize(
        _<Theme0Properties>().GetWorldAreaSize(),
        _<Theme0Properties>().GetWorldScaling());

    _<Engine>().Run();

    return 0;
}
