//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "Core.hpp"

#include "Scripts.hpp"

#include "Theme0Properties.hpp"

#include "WorldStruct.hpp"

int main(int argc, char **argv)
{
    using namespace Forradia;
    using namespace Theme0;

    _<Engine>().Initialize(
        _<Theme0Properties>().k_gameWindowTitle,
        _<Theme0Properties>().k_clearColor);

    _<ScriptEngine>().Initialize();

    _<ScriptEngine>().LoadScripts();

    _<World>().Initialize(
        _<Theme0Properties>().k_worldAreaSize,
        _<Theme0Properties>().k_worldScaling);

    _<Engine>().Run();

    return 0;
}
