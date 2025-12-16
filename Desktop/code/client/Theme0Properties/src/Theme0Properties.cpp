//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#include "Theme0Properties.hpp"

namespace Forradia::Theme0 {
    String Theme0Properties::GetGameWindowTitle() const {
        return "Forradia";
    }

    Color Theme0Properties::GetClearColor() const {
        return Palette::GetColor<Hash("MildBlue")>();
    }

    Size Theme0Properties::GetGridSize() const {
        return {45, 45};
    }

    Size Theme0Properties::GetBaseWorldAreaSize() const {
        return {120, 100};
    }

    float Theme0Properties::GetWorldScaling() const {
        return 5.0f;
    }

    float Theme0Properties::GetTileSize() const {
        return 1.6f;
    }

    float Theme0Properties::GetElevationHeight() const {
        return 0.15f;
    }
}