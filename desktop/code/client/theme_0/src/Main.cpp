//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "Engine.hpp"

#include "Scripts.hpp"

#include "Theme0Properties.hpp"

#include "World.hpp"

#include "Coloring/Palette.hpp"

int main(int argc, char **argv)
{
    using namespace Forradia;
    using namespace Theme0;

    // std::cout << "GroundGrass: "
    //           << static_cast<uint64_t>(Hash("GroundGrass"))
    //           << std::endl;
    // std::cout << "GroundRock: "
    //           << static_cast<uint64_t>(Hash("GroundRock"))
    //           << std::endl;
    // std::cout << "GroundDirt: "
    //           << static_cast<uint64_t>(Hash("GroundDirt"))
    //           << std::endl;
    // std::cout << "GroundWater: "
    //           << static_cast<uint64_t>(Hash("GroundWater"))
    //           << std::endl;

    // std::cout << "ObjectFirTree: "
    //           << static_cast<uint64_t>(
    //                  Hash("ObjectFirTree"))
    //           << std::endl;
    // std::cout << "ObjectBirchTree: "
    //           << static_cast<uint64_t>(
    //                  Hash("ObjectBirchTree"))
    //           << std::endl;
    // std::cout << "ObjectBush1: "
    //           << static_cast<uint64_t>(Hash("ObjectBush1"))
    //           << std::endl;
    // std::cout << "ObjectBush2: "
    //           << static_cast<uint64_t>(Hash("ObjectBush2"))
    //           << std::endl;

    _<Engine>().Initialize(
        _<Theme0Properties>().GetGameWindowTitle(),
        _<Theme0Properties>().GetClearColor());

    _<ScriptEngine>().Initialize();

    _<ScriptEngine>().LoadScripts();

    _<World>().Initialize(
        _<Theme0Properties>().GetBaseWorldAreaSize(),
        _<Theme0Properties>().GetWorldScaling());

    _<Engine>().Run();

    return 0;
}
