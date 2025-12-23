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
#include "TimeUtilities.hpp"
#include "Update/TileHovering.hpp"
#include "World.hpp"
#include "WorldArea.hpp"
#include "WorldView.hpp"

namespace Forradia::Theme0
{
    auto WorldView::IterationAllExceptGround(int xPos, int yPos) -> void
    {
        auto playerPos{Player::Instance().GetPosition()};
        auto gridSize{Theme0Properties::Instance().GetGridSize()};
        auto worldArea{World::Instance().GetCurrentWorldArea()};
        auto rendTileSize{Theme0Properties::Instance().GetTileSize()};
        auto hoveredCoordinate{TileHovering::GetHoveredCoordinate()};

        // Calculate extended ground rendering size
        auto groundGridSize{
            decltype(gridSize){static_cast<decltype(gridSize.width)>(
                                   gridSize.width * k_groundRenderingDistanceMultiplier),
                               static_cast<decltype(gridSize.height)>(
                                   gridSize.height * k_groundRenderingDistanceMultiplier)}};

        auto xCoordinate{playerPos.x - (groundGridSize.width - 1) / 2 + xPos};
        auto yCoordinate{playerPos.y - (groundGridSize.height - 1) / 2 + yPos};

        if (!worldArea->IsValidCoordinate(xCoordinate, yCoordinate))
        {
            return;
        }

        auto tile{worldArea->GetTile(xCoordinate, yCoordinate)};
        auto objectsStack{tile->GetObjectsStack()};
        auto objects{objectsStack->GetObjects()};

        if (m_elevationsAll.find(xCoordinate) == m_elevationsAll.end() ||
            m_elevationsAll[xCoordinate].find(yCoordinate) == m_elevationsAll[xCoordinate].end())
        {
            return;
        }

        std::vector<float> &elevations = m_elevationsAll[xCoordinate][yCoordinate];

        // NOLINTNEXTLINE(readability-magic-numbers)
        auto &elevationNW = elevations[0];
        // NOLINTNEXTLINE(readability-magic-numbers)
        auto &elevationNE = elevations[1];
        // NOLINTNEXTLINE(readability-magic-numbers)
        auto &elevationNEE = elevations[2];
        // NOLINTNEXTLINE(readability-magic-numbers)
        auto &elevationSW = elevations[3];
        // NOLINTNEXTLINE(readability-magic-numbers)
        auto &elevationSE = elevations[4];
        // NOLINTNEXTLINE(readability-magic-numbers)
        auto &elevationSEE = elevations[5];
        // NOLINTNEXTLINE(readability-magic-numbers)
        auto &elevationSS = elevations[6];
        // NOLINTNEXTLINE(readability-magic-numbers)
        auto &elevationSES = elevations[7];
        // NOLINTNEXTLINE(readability-magic-numbers)
        auto &elevationSESE = elevations[8];

        auto elevationAverage{(elevationNW + elevationNE + elevationSW + elevationSE) / 4};

        auto elevationMax{
            std::max(elevationNW, std::max(elevationNE, std::max(elevationSE, elevationSW)))};

        auto ground{tile->GetGround()};

        if (ground == Hash("GroundWater"))
        {
            auto waterDepth{tile->GetWaterDepth()};
            waterDepth = std::min(waterDepth, k_maxWaterDepthRendering);

            std::string waterImageString{"GroundWater_Depth" + std::to_string(waterDepth)};

            // NOLINTNEXTLINE(readability-magic-numbers)
            auto animationIndex{(GetTicks() + ((xCoordinate + yCoordinate) * 100)) / 500 % 3};

            waterImageString += "_" + std::to_string(animationIndex);

            ground = Hash(waterImageString);
        }

        // Check if this tile is within the normal grid size for object/entity
        // rendering.
        auto isWithinNormalGrid{xPos >= (groundGridSize.width - gridSize.width) / 2 &&
                                xPos < (groundGridSize.width + gridSize.width) / 2 &&
                                yPos >= (groundGridSize.height - gridSize.height) / 2 &&
                                yPos < (groundGridSize.height + gridSize.height) / 2};

        // Only render objects, and entities within the normal grid size.
        if (isWithinNormalGrid)
        {
            for (const auto &object : objects)
            {
                auto objectType{object->GetType()};

                ModelRenderer::Instance().DrawModel(objectType,
                                                    (xCoordinate)*rendTileSize + rendTileSize / 2,
                                                    (yCoordinate)*rendTileSize + rendTileSize / 2,
                                                    elevationMax, object->GetModelScaling());
            }

            auto entity{tile->GetEntity()};

            if (entity)
            {
                auto entityType{entity->GetType()};

                ModelRenderer::Instance().DrawModel(
                    entityType, (xCoordinate)*rendTileSize + rendTileSize / 2,
                    (yCoordinate)*rendTileSize + rendTileSize / 2, elevationMax);
            }

            if (xCoordinate == playerPos.x && yCoordinate == playerPos.y)
                ModelRenderer::Instance().DrawModel(
                    Hash("Player"), (xCoordinate)*rendTileSize + rendTileSize / 2,
                    (yCoordinate)*rendTileSize + rendTileSize / 2, elevationMax);
        }

        if (xCoordinate == hoveredCoordinate.x && yCoordinate == hoveredCoordinate.y)
        {
            for (auto &elevation : elevations)
            {
                // NOLINTNEXTLINE(readability-magic-numbers)
                elevation += 0.01F;
            }

            GroundRenderer::Instance().SetupState();
            GroundRenderer::Instance().DrawTile(k_renderIDGroundSymbolHoveredTile,
                                                Hash("HoveredTile"), xCoordinate, yCoordinate,
                                                rendTileSize, elevations, true);

            GroundRenderer::RestoreState();
        }
    }
}