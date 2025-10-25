//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "Core.hpp"
#include "GameProps.hpp"
#include "Scripts.hpp"
#include "WorldStruct.hpp"

int main(int argc, char **argv)
{
    using namespace Forradia;
    using namespace Theme0;

    _<Engine>().Initialize(
        _<GameProperties>().k_gameWindowTitle,
        _<GameProperties>().k_clearColor);

    _<ScriptEngine>().Initialize();

    _<ScriptEngine>().LoadScripts();

    _<World>().Initialize(
        _<GameProperties>().k_worldAreaSize,
        _<GameProperties>().k_worldScaling);

    _<Engine>().Run();

    return 0;
}
