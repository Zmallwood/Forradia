//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "GroundRenderer.hpp"

namespace Forradia
{
    Vector<float> GroundRenderer::CalcTileVerticesNoNormals(
        int xCoordinate, int yCoordinate, float tileSize,
        const Vector<float> &elevations,
        float elevationHeight)
    {
        auto x{tileSize * xCoordinate};

        auto y{tileSize * yCoordinate};

        auto width{tileSize};

        auto height{tileSize};

        // clang-format off

        return {x, y, elevations.at(0) * elevationHeight,
                1.0f, 1.0f, 1.0f, 0.0, 0.0,
                x + width, y, elevations.at(1) * elevationHeight,
                1.0f, 1.0f, 1.0f, 1.0, 0.0,
                x + width + width, y, elevations.at(2) * elevationHeight,
                1.0f, 1.0f, 1.0f, 1.0, 1.0,
                x, y + height, elevations.at(3) * elevationHeight,
                1.0f, 1.0f, 1.0f, 0.0, 1.0,
                x + width, y + height, elevations.at(4) * elevationHeight,
                1.0f, 1.0f, 1.0f, 1.0, 1.0,
                x + width + width, y + height, elevations.at(5) * elevationHeight,
                1.0f, 1.0f, 1.0f, 1.0, 1.0,
                x, y + height + height, elevations.at(6) * elevationHeight,
                1.0f, 1.0f, 1.0f, 1.0, 1.0,
                x + width, y + height + height, elevations.at(7) * elevationHeight,
                1.0f, 1.0f, 1.0f, 1.0, 1.0,
                x + width + width, y + height + height, elevations.at(8) * elevationHeight,
                1.0f, 1.0f, 1.0f, 1.0, 1.0};

        // clang-format on
    }
}