/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "WorldView.hpp"
#include "GroundRenderer.hpp"
#include "Player/Player.hpp"
#include "SkyRenderer.hpp"
#include "World.hpp"
#include "WorldArea.hpp"
#include "Theme0Properties.hpp"

namespace Forradia::Theme0
{
    auto WorldView::Initialize() -> void
    {
        auto worldArea{World::Instance().GetCurrentWorldArea()};
        auto worldAreaSize{worldArea->GetSize()};

        for (auto yPos = 0; yPos < worldAreaSize.height; yPos++)
        {
            for (auto xPos = 0; xPos < worldAreaSize.width; xPos++)
            {
                m_renderIDsGround[xPos][yPos] =
                    Hash("Ground_" + std::to_string(xPos) + "_" + std::to_string(yPos));
            }
        }
    }

    auto WorldView::Render() -> void
    {
        // 45 degrees up in +Z
        // NOLINTNEXTLINE(readability-magic-numbers)
        glm::vec3 sunDirection = glm::normalize(glm::vec3(0.7F, 0.0F, 0.7F));

        // 45 degrees
        // NOLINTNEXTLINE(readability-magic-numbers)
        float sunElevation = M_PI / 4.0F;

        SkyRenderer::Instance().Render(sunDirection, sunElevation);

        m_tiles.clear();
        m_elevationsAll.clear();

        auto gridSize{Theme0Properties::Instance().GetGridSize()};

        // Calculate extended ground rendering size
        auto groundGridSize{
            decltype(gridSize){static_cast<decltype(gridSize.width)>(
                                   gridSize.width * k_groundRenderingDistanceMultiplier),
                               static_cast<decltype(gridSize.height)>(
                                   gridSize.height * k_groundRenderingDistanceMultiplier)}};

        auto playerPos{Player::Instance().GetPosition()};
        auto worldArea{World::Instance().GetCurrentWorldArea()};
        auto worldAreaSize{worldArea->GetSize()};

        GroundRenderer::Instance().SetupState();

        constexpr auto k_tilesGroupSize{20};

        // First pass: Render ground tiles at extended distance.
        for (auto yPos = 0; yPos < groundGridSize.height; yPos++)
        {
            for (auto xPos = 0; xPos < groundGridSize.width; xPos++)
            {
                auto xCoordinate{playerPos.x - (groundGridSize.width - 1) / 2 + xPos};
                auto yCoordinate{playerPos.y - (groundGridSize.height - 1) / 2 + yPos};

                if (xCoordinate % k_tilesGroupSize == 0 && yCoordinate % k_tilesGroupSize == 0)
                {
                    for (auto yy = 0; yy < k_tilesGroupSize; yy++)
                    {
                        for (auto xx = 0; xx < k_tilesGroupSize; xx++)
                        {
                            this->IterationGround(xPos + xx, yPos + yy);
                        }
                    }
                }
            }
        }

        if (!m_tiles.empty())
        {
            GroundRenderer::Instance().DrawTiles(m_tiles);
        }

        m_tiles.clear();

        GroundRenderer::Instance().SetupState();

        // Second pass: Render all except ground tiles.
        for (auto yPos = 0; yPos < worldAreaSize.height; yPos++)
        {
            for (auto xPos = 0; xPos < worldAreaSize.width; xPos++)
            {
                this->IterationAllExceptGround(xPos, yPos);
            }
        }
    }
}
