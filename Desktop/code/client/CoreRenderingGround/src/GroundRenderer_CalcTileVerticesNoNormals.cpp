/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GroundRenderer.hpp"
#include "Theme0Properties.hpp"

namespace Forradia {
    auto GroundRenderer::CalcTileVerticesNoNormals(int xCoordinate, int yCoordinate, float tileSize,
                                                   const std::vector<float> &elevations,
                                                   std::vector<Color> colors) const
        -> std::vector<float> {
        auto x{xCoordinate * tileSize};
        auto y{yCoordinate * tileSize};
        auto width{tileSize};
        auto height{tileSize};

        auto elevationHeight{_<Theme0::Theme0Properties>().GetElevationHeight()};

        // Return the nine vertices.
        // clang-format off
        return {x, y, elevations.at(0) * elevationHeight,
                colors.at(0).r, colors.at(0).g, colors.at(0).b, 0.0F, 0.0F,
                x + width, y, elevations.at(1) * elevationHeight,
                colors.at(1).r, colors.at(1).g, colors.at(1).b, 1.0F, 0.0F,
                x + width + width, y, elevations.at(2) * elevationHeight,
                1.0F, 1.0F, 1.0F, 1.0F, 1.0F,
                x, y + height, elevations.at(3) * elevationHeight,
                colors.at(3).r, colors.at(3).g, colors.at(3).b, 0.0F, 1.0F,
                x + width, y + height, elevations.at(4) * elevationHeight,
                colors.at(2).r, colors.at(2).g, colors.at(2).b, 1.0F, 1.0F,
                x + width + width, y + height, elevations.at(5) * elevationHeight,
                1.0F, 1.0F, 1.0F, 1.0F, 1.0F,
                x, y + height + height, elevations.at(6) * elevationHeight,
                1.0F, 1.0F, 1.0F, 1.0F, 1.0F,
                x + width, y + height + height, elevations.at(7) * elevationHeight,
                1.0F, 1.0F, 1.0F, 1.0F, 1.0F,
                x + width + width, y + height + height, elevations.at(8) * elevationHeight,
                1.0F, 1.0F, 1.0F, 1.0F, 1.0F};
        // clang-format on
    }
}
