/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GroundRenderer.hpp"
#include "Theme0Properties.hpp"

namespace Forradia {
    auto GroundRenderer::CalcTileVerticesNoNormals(int xCoordinate, int yCoordinate, float tileSize,
                                                   const std::vector<float> &elevations,
                                                   std::vector<Color> colors)
        -> std::vector<float> {
        auto xPos{xCoordinate * tileSize};
        auto yPos{yCoordinate * tileSize};
        auto width{tileSize};
        auto height{tileSize};

        auto elevationHeight{Theme0::Theme0Properties::Instance().GetElevationHeight()};

        constexpr int k_elevIdx00{0};
        constexpr int k_elevIdx10{1};
        constexpr int k_elevIdx20{2};
        constexpr int k_elevIdx01{3};
        constexpr int k_elevIdx11{4};
        constexpr int k_elevIdx21{5};
        constexpr int k_elevIdx02{6};
        constexpr int k_elevIdx12{7};
        constexpr int k_elevIdx22{8};

        // Return the nine vertices.
        // clang-format off
        return {xPos, yPos, elevations.at(k_elevIdx00) * elevationHeight,
                colors.at(0).r, colors.at(0).g, colors.at(0).b, 0.0F, 0.0F,
                xPos + width, yPos, elevations.at(k_elevIdx10) * elevationHeight,
                colors.at(1).r, colors.at(1).g, colors.at(1).b, 1.0F, 0.0F,
                xPos + width + width, yPos, elevations.at(k_elevIdx20) * elevationHeight,
                1.0F, 1.0F, 1.0F, 1.0F, 1.0F,
                xPos, yPos + height, elevations.at(k_elevIdx01) * elevationHeight,
                colors.at(3).r, colors.at(3).g, colors.at(3).b, 0.0F, 1.0F,
                xPos + width, yPos + height, elevations.at(k_elevIdx11) * elevationHeight,
                colors.at(2).r, colors.at(2).g, colors.at(2).b, 1.0F, 1.0F,
                xPos + width + width, yPos + height, elevations.at(k_elevIdx21) * elevationHeight,
                1.0F, 1.0F, 1.0F, 1.0F, 1.0F,
                xPos, yPos + height + height, elevations.at(k_elevIdx02) * elevationHeight,
                1.0F, 1.0F, 1.0F, 1.0F, 1.0F,
                xPos + width, yPos + height + height, elevations.at(k_elevIdx12) * elevationHeight,
                1.0F, 1.0F, 1.0F, 1.0F, 1.0F,
                xPos + width + width, yPos + height + height, elevations.at(k_elevIdx22) * elevationHeight,
                1.0F, 1.0F, 1.0F, 1.0F, 1.0F};
        // clang-format on
    }
}
