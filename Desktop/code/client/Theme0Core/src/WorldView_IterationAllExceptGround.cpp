/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "Entity.hpp"
#include "GroundRenderer.hpp"
#include "ModelRenderer.hpp"
#include "Object.hpp"
#include "ObjectsStack.hpp"
#include "Player/Player.hpp"
#include "Theme0Properties.hpp"
#include "Tile.hpp"
#include "Update/TileHovering.hpp"
#include "World.hpp"
#include "WorldArea.hpp"
#include "WorldView.hpp"

namespace Forradia::Theme0
{
    auto WorldView::IterationAllExceptGround(int xPos, int yPos) -> void
    {
        auto xCoordinate{m_playerPos.x - (m_groundGridSize.width - 1) / 2 + xPos};
        auto yCoordinate{m_playerPos.y - (m_groundGridSize.height - 1) / 2 + yPos};

        if (!m_worldArea->IsValidCoordinate(xCoordinate, yCoordinate))
        {
            return;
        }

        auto tile{m_worldArea->GetTile(xCoordinate, yCoordinate)};
        auto objectsStack{tile->GetObjectsStack()};

        auto objects{objectsStack->GetObjects()};

        if (!m_elevationsAll.contains(xCoordinate) ||
            !m_elevationsAll[xCoordinate].contains(yCoordinate))
        {
            return;
        }

        std::vector<float> &elevations = m_elevationsAll[xCoordinate][yCoordinate];

        // NOLINTNEXTLINE(readability-magic-numbers)
        auto &elevationNW = elevations[0];
        // NOLINTNEXTLINE(readability-magic-numbers)
        auto &elevationNE = elevations[1];
        // NOLINTNEXTLINE(readability-magic-numbers)
        auto &elevationSW = elevations[3];
        // NOLINTNEXTLINE(readability-magic-numbers)
        auto &elevationSE = elevations[4];

        auto elevationMax{
            std::max(elevationNW, std::max(elevationNE, std::max(elevationSE, elevationSW)))};

        // Check if this tile is within the normal grid size for object/entity
        // rendering.
        auto isWithinNormalGrid{xPos >= (m_groundGridSize.width - m_gridSize.width) / 2 &&
                                xPos < (m_groundGridSize.width + m_gridSize.width) / 2 &&
                                yPos >= (m_groundGridSize.height - m_gridSize.height) / 2 &&
                                yPos < (m_groundGridSize.height + m_gridSize.height) / 2};

        // Only render objects, and entities within the normal grid size.
        if (isWithinNormalGrid)
        {
            for (const auto &object : objects)
            {
                auto objectType{object->GetType()};

                ModelRenderer::Instance().DrawModel(
                    objectType, (xCoordinate)*m_rendTileSize + m_rendTileSize / 2,
                    (yCoordinate)*m_rendTileSize + m_rendTileSize / 2, elevationMax,
                    object->GetModelScaling());
            }

            if (auto entity{tile->GetEntity()})
            {
                auto entityType{entity->GetType()};

                ModelRenderer::Instance().DrawModel(
                    entityType, (xCoordinate)*m_rendTileSize + m_rendTileSize / 2,
                    (yCoordinate)*m_rendTileSize + m_rendTileSize / 2, elevationMax);
            }

            if (xCoordinate == m_playerPos.x && yCoordinate == m_playerPos.y)
            {
                auto playerSmoothPosition{Player::Instance().GetSmoothPosition()};
                ModelRenderer::Instance().DrawModel(
                    Hash("Player"), (playerSmoothPosition.x) * m_rendTileSize + m_rendTileSize / 2,
                    (playerSmoothPosition.y) * m_rendTileSize + m_rendTileSize / 2, elevationMax);
            }
        }

        if (xCoordinate == m_hoveredCoordinate.x && yCoordinate == m_hoveredCoordinate.y)
        {
            for (auto &elevation : elevations)
            {
                // NOLINTNEXTLINE(readability-magic-numbers)
                elevation += 0.01F;
            }

            ModelRenderer::Instance().RestoreState();

            GroundRenderer::Instance().SetupState();
            GroundRenderer::Instance().DrawTile(k_renderIDGroundSymbolHoveredTile,
                                                Hash("HoveredTile"), xCoordinate, yCoordinate,
                                                m_rendTileSize, elevations, true);

            GroundRenderer::RestoreState();
            ModelRenderer::Instance().SetupState();
        }
    }
}