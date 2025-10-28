//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "Theme0Properties.hpp"

namespace Forradia::Theme0
{
    String Theme0Properties::GetGameWindowTitle() const
    {
        return "Forradia";
    }

    Color Theme0Properties::GetClearColor() const
    {
        return Colors::MildBlue;
    }

    Size Theme0Properties::GetGridSize() const
    {
        return {30, 35};
    }

    Size Theme0Properties::GetWorldAreaSize() const
    {
        return {120, 100};
    }

    float Theme0Properties::GetWorldScaling() const
    {
        return 5.0f;
    }

    float Theme0Properties::GetTileSize() const
    {
        return 0.8f;
    }
}