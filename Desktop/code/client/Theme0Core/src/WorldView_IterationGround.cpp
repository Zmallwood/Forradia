/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "ObjectsStack.hpp"
#include "Player/Player.hpp"
#include "Theme0Properties.hpp"
#include "Tile.hpp"
#include "Update/TileHovering.hpp"
#include "World.hpp"
#include "WorldArea.hpp"
#include "WorldView.hpp"
#include "TimeUtilities.hpp"

namespace Forradia::Theme0
{
    auto WorldView::IterationGround(int x, int y) -> void
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

        auto xCoordinate{playerPos.x - (groundGridSize.width - 1) / 2 + x};
        auto yCoordinate{playerPos.y - (groundGridSize.height - 1) / 2 + y};

        if (!worldArea->IsValidCoordinate(xCoordinate, yCoordinate))
        {
            return;
        }

        auto tile{worldArea->GetTile(xCoordinate, yCoordinate)};
        auto objectsStack{tile->GetObjectsStack()};
        auto objects{objectsStack->GetObjects()};

        auto coordinateNWW{Point{xCoordinate - 1, yCoordinate}};
        auto coordinateNNW{Point{xCoordinate, yCoordinate - 1}};
        auto coordinateNNWW{Point{xCoordinate - 1, yCoordinate - 1}};
        auto coordinateNNE{Point{xCoordinate + 1, yCoordinate - 1}};
        auto coordinateSWW{Point{xCoordinate - 1, yCoordinate + 1}};
        auto coordinateNW{Point{xCoordinate, yCoordinate}};
        auto coordinateNE{Point{xCoordinate + 1, yCoordinate}};
        auto coordinateSW{Point{xCoordinate, yCoordinate + 1}};
        auto coordinateSE{Point{xCoordinate + 1, yCoordinate + 1}};
        auto coordinateNEE{Point{xCoordinate + 2, yCoordinate}};
        auto coordinateSEE{Point{xCoordinate + 2, yCoordinate + 1}};
        auto coordinateSESE{Point{xCoordinate + 2, yCoordinate + 2}};
        auto coordinateSES{Point{xCoordinate + 1, yCoordinate + 2}};
        auto coordinateSS{Point{xCoordinate, yCoordinate + 2}};

        if (!worldArea->IsValidCoordinate(coordinateNW) ||
            !worldArea->IsValidCoordinate(coordinateNE) ||
            !worldArea->IsValidCoordinate(coordinateSW) ||
            !worldArea->IsValidCoordinate(coordinateSE))
        {
            return;
        }

        auto tileNWW{worldArea->GetTile(coordinateNWW)};
        auto tileNNW{worldArea->GetTile(coordinateNNW)};
        auto tileNNWW{worldArea->GetTile(coordinateNNWW)};
        auto tileNNE{worldArea->GetTile(coordinateNNE)};
        auto tileSWW{worldArea->GetTile(coordinateSWW)};
        auto tileNW{worldArea->GetTile(coordinateNW)};
        auto tileNE{worldArea->GetTile(coordinateNE)};
        auto tileSW{worldArea->GetTile(coordinateSW)};
        auto tileSE{worldArea->GetTile(coordinateSE)};
        auto tileNEE{worldArea->GetTile(coordinateNEE)};
        auto tileSEE{worldArea->GetTile(coordinateSEE)};
        auto tileSESE{worldArea->GetTile(coordinateSESE)};
        auto tileSES{worldArea->GetTile(coordinateSES)};
        auto tileSS{worldArea->GetTile(coordinateSS)};

        std::vector<float> elevations;

        auto elevationNW{tileNW ? tileNW->GetElevation() : 0.0F};
        auto elevationNE{tileNE ? tileNE->GetElevation() : 0.0F};
        auto elevationSE{tileSE ? tileSE->GetElevation() : 0.0F};
        auto elevationSW{tileSW ? tileSW->GetElevation() : 0.0F};
        auto elevationNEE{tileNEE ? tileNEE->GetElevation() : 0.0F};
        auto elevationSEE{tileSEE ? tileSEE->GetElevation() : 0.0F};
        auto elevationSESE{tileSESE ? tileSESE->GetElevation() : 0.0F};
        auto elevationSES{tileSES ? tileSES->GetElevation() : 0.0F};
        auto elevationSS{tileSS ? tileSS->GetElevation() : 0.0F};

        elevations.push_back(elevationNW);
        elevations.push_back(elevationNE);
        elevations.push_back(elevationNEE);
        elevations.push_back(elevationSW);
        elevations.push_back(elevationSE);
        elevations.push_back(elevationSEE);
        elevations.push_back(elevationSS);
        elevations.push_back(elevationSES);
        elevations.push_back(elevationSESE);

        m_elevationsAll[xCoordinate][yCoordinate] = elevations;

        auto elevationAverage{(elevationNW + elevationNE + elevationSW + elevationSE) / 4};

        auto elevationMax{
            std::max(elevationNW, std::max(elevationNE, std::max(elevationSE, elevationSW)))};

        auto ground{tile->GetGround()};

        auto color00{Palette::GetColor<Hash("White")>()};
        auto color10{Palette::GetColor<Hash("White")>()};
        auto color11{Palette::GetColor<Hash("White")>()};
        auto color01{Palette::GetColor<Hash("White")>()};

        if (ground != Hash("GroundStoneSlab"))
        {
            switch (ground)
            {
            case Hash("GroundGrass"):
                color00 = Palette::GetColor<Hash("DarkGreen")>();
                break;

            case Hash("GroundWater"):
                color00 = Palette::GetColor<Hash("LightBlue")>();
                break;

            case Hash("GroundDirt"):
                color00 = Palette::GetColor<Hash("Brown")>();
                break;

            case Hash("GroundRock"):
                color00 = Palette::GetColor<Hash("Gray")>();
                break;

            case Hash("GroundStoneSlab"):
                color00 = Palette::GetColor<Hash("White")>();
                break;
            }

            if (tileNE)
            {
                switch (tileNE->GetGround())
                {
                case Hash("GroundGrass"):
                    color10 = Palette::GetColor<Hash("DarkGreen")>();
                    break;

                case Hash("GroundWater"):
                    color10 = Palette::GetColor<Hash("LightBlue")>();
                    break;

                case Hash("GroundDirt"):
                    color10 = Palette::GetColor<Hash("Brown")>();
                    break;

                case Hash("GroundRock"):
                    color10 = Palette::GetColor<Hash("Gray")>();
                    break;

                case Hash("GroundStoneSlab"):
                    color10 = Palette::GetColor<Hash("White")>();
                    break;
                }
            }

            if (tileSE)
            {
                switch (tileSE->GetGround())
                {
                case Hash("GroundGrass"):
                    color11 = Palette::GetColor<Hash("DarkGreen")>();
                    break;

                case Hash("GroundWater"):
                    color11 = Palette::GetColor<Hash("LightBlue")>();
                    break;

                case Hash("GroundDirt"):
                    color11 = Palette::GetColor<Hash("Brown")>();
                    break;

                case Hash("GroundRock"):
                    color11 = Palette::GetColor<Hash("Gray")>();
                    break;

                case Hash("GroundStoneSlab"):
                    color11 = Palette::GetColor<Hash("White")>();
                    break;
                }
            }

            if (tileSW)
            {
                switch (tileSW->GetGround())
                {
                case Hash("GroundGrass"):
                    color01 = Palette::GetColor<Hash("DarkGreen")>();
                    break;

                case Hash("GroundWater"):
                    color01 = Palette::GetColor<Hash("LightBlue")>();
                    break;

                case Hash("GroundDirt"):
                    color01 = Palette::GetColor<Hash("Brown")>();
                    break;

                case Hash("GroundRock"):
                    color01 = Palette::GetColor<Hash("Gray")>();
                    break;

                case Hash("GroundStoneSlab"):
                    color01 = Palette::GetColor<Hash("White")>();
                    break;
                }
            }
        }

        auto forceRedraw{tile->GetForceRedraw()};

        tile->SetForceRedraw(false);

        if (ground == Hash("GroundWater"))
        {
            auto waterDepth{tile->GetWaterDepth()};

            waterDepth = std::min(waterDepth, k_maxWaterDepthRendering);

            std::string waterImageString{"GroundWater_Depth" + std::to_string(waterDepth)};

            auto animationIndex{(GetTicks() + ((xCoordinate + yCoordinate) * 100)) / 500 % 3};

            waterImageString += "_" + std::to_string(animationIndex);

            ground = Hash(waterImageString);

            tile->SetForceRedraw(true);
        }

        // Check if this tile is within the normal grid size for object/entity
        // rendering.
        auto isWithinNormalGrid{x >= (groundGridSize.width - gridSize.width) / 2 &&
                                x < (groundGridSize.width + gridSize.width) / 2 &&
                                y >= (groundGridSize.height - gridSize.height) / 2 &&
                                y < (groundGridSize.height + gridSize.height) / 2};

        m_tiles.push_back({m_renderIDsGround.at(xCoordinate).at(yCoordinate), ground, xCoordinate,
                           yCoordinate, rendTileSize, elevations, forceRedraw, color00, color10,
                           color11, color01});
    }
}