/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "Content/Essentials/Player/Player.hpp"
    #include "Content/Properties/CreatureIndex.hpp"
    #include "Content/Properties/ObjectIndex.hpp"
    #include "Content/Properties/ThemeProperties.hpp"
    #include "Content/WorldStructure/Entity.hpp"
    #include "Content/WorldStructure/Object.hpp"
    #include "Content/WorldStructure/ObjectsStack.hpp"
    #include "Content/WorldStructure/Tile.hpp"
    #include "Content/WorldStructure/World.hpp"
    #include "Content/WorldStructure/WorldArea.hpp"
    #include "ForradiaEngine/Rendering/Ground/GroundRenderer.hpp"
    #include "ForradiaEngine/Rendering/Models/ModelRenderer.hpp"
    #include "Update/TileHovering.hpp"
    #include "WorldView.hpp"
// clang-format on

namespace ForradiaEngine::JewelryMakerTheme
{
    auto WorldView::iterationAllExceptGround(int xPos, int yPos) -> void
    {
        auto xCoordinate{m_playerPos.x - (m_groundGridSize.width - 1) / 2 + xPos};
        auto yCoordinate{m_playerPos.y - (m_groundGridSize.height - 1) / 2 + yPos};

        if (!m_worldArea->isValidCoordinate(xCoordinate, yCoordinate))
        {
            return;
        }

        auto tile{m_worldArea->getTile(xCoordinate, yCoordinate)};
        auto objectsStack{tile->getObjectsStack()};

        auto objects{objectsStack->getObjects()};

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
            /* Render the objects on the tile */ // clang-format off
                for (const auto &object : objects)
                {
                    auto objectType{object->getType()};

                    auto totModelScaling{1.0F};

                    totModelScaling = object->getModelScaling();

                    if (!ObjectIndex::instance().getIgnoreIndividualModelScaling(objectType))
                    {
                        totModelScaling *= ObjectIndex::instance().getModelScaling(objectType);
                    }

                    // totModelScaling *= ObjectIndex::instance().getModelScaling(objectType);

                    ModelRenderer::instance().drawModel(
                        objectType, (xCoordinate)*m_rendTileSize + m_rendTileSize / 2,
                        (yCoordinate)*m_rendTileSize + m_rendTileSize / 2, elevationMax,
                        totModelScaling, ThemeProperties::getElevationHeight());
                }
            // clang-format on

            /* Render the entity on the tile */ // clang-format off
                if (auto entity{tile->getEntity()})
                {
                    auto entityType{entity->getType()};

                    auto totModelScaling{1.0F};

                    totModelScaling = CreatureIndex::instance().getModelScaling(entityType);

                    auto levitationHeight{CreatureIndex::instance().getLevitationHeight(entityType)};

                    ModelRenderer::instance().drawModel(
                        entityType, (xCoordinate)*m_rendTileSize + m_rendTileSize / 2,
                        (yCoordinate)*m_rendTileSize + m_rendTileSize / 2, elevationMax,
                        totModelScaling, ThemeProperties::getElevationHeight(),
                        levitationHeight);
                }
            // clang-format on

            /* Render the player */ // clang-format off
                if (xCoordinate == m_playerPos.x && yCoordinate == m_playerPos.y)
                {
                    auto playerSmoothPosition{Player::instance().getSmoothPosition()};
                    
                    ModelRenderer::instance().drawModel(
                        hash("Player"), (playerSmoothPosition.x) * m_rendTileSize + m_rendTileSize / 2,
                        (playerSmoothPosition.y) * m_rendTileSize + m_rendTileSize / 2, elevationMax);
                }
            // clang-format on
        }

        /* Render the hovered tile */ // clang-format off
            if (xCoordinate == m_hoveredCoordinate.x && yCoordinate == m_hoveredCoordinate.y)
            {
                for (auto &elevation : elevations)
                {
                    // NOLINTNEXTLINE(readability-magic-numbers)
                    elevation += 0.01F;
                }

                ModelRenderer::restoreState();

                GroundRenderer::instance().setupState();
                GroundRenderer::instance().drawTile(k_renderIDGroundSymbolHoveredTile,
                                                    hash("HoveredTile"), xCoordinate, yCoordinate,
                                                    m_rendTileSize, elevations, true);

                GroundRenderer::restoreState();
                ModelRenderer::instance().setupState();
            }
        // clang-format on
    }
}