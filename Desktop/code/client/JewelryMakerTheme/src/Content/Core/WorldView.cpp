/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "WorldView.hpp"
    #include "Content/Essentials/Player/Player.hpp"
    #include "Content/Properties/Theme0Properties.hpp"
    #include "Content/WorldStructure/World.hpp"
    #include "Content/WorldStructure/WorldArea.hpp" 
    #include "ForradiaEngine/Rendering/Ground/GroundRenderer.hpp"
    #include "ForradiaEngine/Rendering/Models/ModelRenderer.hpp"
    #include "ForradiaEngine/Rendering/Sky/SkyRenderer.hpp"
    #include "Update/TileHovering.hpp"
// clang-format on

namespace ForradiaEngine::JewelryMakerTheme
{
    auto WorldView::initialize() -> void
    {
        auto worldArea{World::instance().getCurrentWorldArea()};
        auto worldAreaSize{worldArea->getSize()};

        /* Initialize the render IDs for the ground tiles */ // clang-format off
            for (auto yPos = 0; yPos < worldAreaSize.height; yPos++)
            {
                for (auto xPos = 0; xPos < worldAreaSize.width; xPos++)
                {
                    m_renderIDsGround[xPos][yPos] =
                        hash("Ground_" + std::to_string(xPos) + "_" + std::to_string(yPos));
                }
            }
        // clang-format on

        m_sunDirection = glm::normalize(k_sunDirectionRaw);
    }

    auto WorldView::render() -> void
    {
        SkyRenderer::instance().render(m_sunDirection, k_sunElevation);

        m_elevationsAll.clear();

        m_gridSize = Theme0Properties::instance().getGridSize();

        // Calculate extended ground rendering size
        m_groundGridSize =
            decltype(m_gridSize){static_cast<decltype(m_gridSize.width)>(
                                     m_gridSize.width * k_groundRenderingDistanceMultiplier),
                                 static_cast<decltype(m_gridSize.height)>(
                                     m_gridSize.height * k_groundRenderingDistanceMultiplier)};

        m_playerPos = Player::instance().getPosition();
        m_worldArea = World::instance().getCurrentWorldArea();
        m_worldAreaSize = m_worldArea->getSize();
        m_rendTileSize = Theme0Properties::instance().getTileSize();
        m_hoveredCoordinate = TileHovering::getHoveredCoordinate();

        GroundRenderer::instance().setupState();

        /* First pass: Render ground tiles at extended distance */ // clang-format off
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
                                this->iterationGround(xPos + xx, yPos + yy);
                            }
                        }

                        if (!m_tiles.empty())
                        {
                            GroundRenderer::instance().drawTiles(m_tiles);
                        }
                    }
                }
            }
        // clang-format on

        m_tiles.clear();

        GroundRenderer::instance().restoreState();

        // ModelRenderer::Instance().SetupState();

        /* Second pass: Render all except ground tiles */ // clang-format off
            for (auto yPos = 0; yPos < m_worldAreaSize.height; yPos++)
            {
                for (auto xPos = 0; xPos < m_worldAreaSize.width; xPos++)
                {
                    this->iterationAllExceptGround(xPos, yPos);
                }
            }
        // clang-format on

        // ModelRenderer::Instance().RestoreState();
    }
}
