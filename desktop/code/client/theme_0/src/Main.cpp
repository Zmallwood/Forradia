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

    //auto c {Palette::GetColor<Hash("Black")>()};

    //static_assert(Palette::ColorExists<123>());

    //auto colorExists {_<Palette>().ColorExists("Red")};
    //const Palette p = Palette();
    //static_assert(p.ColorExists("Red"));
    //std::cout << colorExists << std::endl;
    //auto color {_<Palette>().GetColor("Black")};

    //auto c {GET_COLOR(Black)};

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
