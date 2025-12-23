/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "WorldView.hpp"
#include "GroundRenderer.hpp"
#include "ModelRenderer.hpp"
#include "Player/Player.hpp"
#include "SkyRenderer.hpp"
#include "Theme0Properties.hpp"
#include "Update/TileHovering.hpp"
#include "World.hpp"
#include "WorldArea.hpp"

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

        m_sunDirection = glm::normalize(k_sunDirectionRaw);
    }

    auto WorldView::Render() -> void
    {
        SkyRenderer::Instance().Render(m_sunDirection, k_sunElevation);

        m_elevationsAll.clear();

        m_gridSize = Theme0Properties::Instance().GetGridSize();

        // Calculate extended ground rendering size
        m_groundGridSize =
            decltype(m_gridSize){static_cast<decltype(m_gridSize.width)>(
                                     m_gridSize.width * k_groundRenderingDistanceMultiplier),
                                 static_cast<decltype(m_gridSize.height)>(
                                     m_gridSize.height * k_groundRenderingDistanceMultiplier)};

        m_playerPos = Player::Instance().GetPosition();
        m_worldArea = World::Instance().GetCurrentWorldArea();
        m_worldAreaSize = m_worldArea->GetSize();
        m_rendTileSize = Theme0Properties::Instance().GetTileSize();
        m_hoveredCoordinate = TileHovering::GetHoveredCoordinate();

        GroundRenderer::Instance().SetupState();

        // First pass: Render ground tiles at extended distance.
        for (auto yPos = 0; yPos < m_groundGridSize.height; yPos++)
        {
            for (auto xPos = 0; xPos < m_groundGridSize.width; xPos++)
            {
                auto xCoordinate{m_playerPos.x - (m_groundGridSize.width - 1) / 2 + xPos};
                auto yCoordinate{m_playerPos.y - (m_groundGridSize.height - 1) / 2 + yPos};

                if (xCoordinate % k_tilesGroupSize == 0 && yCoordinate % k_tilesGroupSize == 0)
                {
                    m_tiles.clear();

                    for (auto yy = 0; yy < k_tilesGroupSize; yy++)
                    {
                        for (auto xx = 0; xx < k_tilesGroupSize; xx++)
                        {
                            this->IterationGround(xPos + xx, yPos + yy);
                        }
                    }

                    if (!m_tiles.empty())
                    {
                        GroundRenderer::Instance().DrawTiles(m_tiles);
                    }
                }
            }
        }

        m_tiles.clear();

        GroundRenderer::Instance().RestoreState();

        //ModelRenderer::Instance().SetupState();

        // Second pass: Render all except ground tiles.
        for (auto yPos = 0; yPos < m_worldAreaSize.height; yPos++)
        {
            for (auto xPos = 0; xPos < m_worldAreaSize.width; xPos++)
            {
                this->IterationAllExceptGround(xPos, yPos);
            }
        }

        //ModelRenderer::Instance().RestoreState();
    }
}
