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
        // Return the game window title which will be shown
        // in the title bar.

        return "Forradia";
    }

    Color Theme0Properties::GetClearColor() const
    {
        // Return the clear color of the canvas which is
        // shown as the background behind everything that is
        // being rendered.

        return Palette::GetColor<Hash("MildBlue")>();
    }

    Size Theme0Properties::GetGridSize() const
    {
        // Return the size of the grid rendered by the
        // WorldView.

        return {35, 35};
    }

    Size Theme0Properties::GetBaseWorldAreaSize() const
    {
        // Return the base size of a single world area.

        return {120, 100};
    }

    float Theme0Properties::GetWorldScaling() const
    {
        // Return the world scaling factor, which is applied
        // to the world area size and world generation
        // amounts.

        return 5.0f;
    }

    float Theme0Properties::GetTileSize() const
    {
        // Return the size of a single tile in opengl space.

        return 0.8f;
    }

    float Theme0Properties::GetElevationHeight() const
    {
        // Return the height of one unit of elevation in
        // opengl 3D space.

        return 0.1f;
    }
}