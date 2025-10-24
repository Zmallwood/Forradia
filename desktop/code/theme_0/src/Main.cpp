//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)
//

#include "Core.hpp"
#include "GameProps.hpp"
#include "Scripts.hpp"
#include "WorldStruct.hpp"

int main(int argc, char **argv)
{
    using namespace Forradia;

    _<Engine>().Initialize(_<Theme0::GameProperties>().k_gameWindowTitle,
                           _<Theme0::GameProperties>().k_clearColor);

    _<Theme0::ScriptEngine>().Initialize();

    _<Theme0::ScriptEngine>().LoadScripts();

    _<Theme0::WorldStructure::World>().Initialize(
        _<Theme0::GameProperties>().k_worldAreaSize,
        _<Theme0::GameProperties>().k_worldScaling);

    _<Engine>().Run();

    return 0;
}
