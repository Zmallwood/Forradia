/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "ObjectsStack.hpp"
#include "Player/Player.hpp"
#include "Theme0Properties.hpp"
#include "Tile.hpp"
#include "TimeUtilities.hpp"
#include "World.hpp"
#include "WorldArea.hpp"
#include "WorldView.hpp"

namespace Forradia::Theme0
{
    auto WorldView::iterationGround(int xPos, int yPos) -> void
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

        if (!m_worldArea->isValidCoordinate(coordinateNW) ||
            !m_worldArea->isValidCoordinate(coordinateNE) ||
            !m_worldArea->isValidCoordinate(coordinateSW) ||
            !m_worldArea->isValidCoordinate(coordinateSE))
        {
            return;
        }

        auto tileNWW{m_worldArea->getTile(coordinateNWW)};
        auto tileNNW{m_worldArea->getTile(coordinateNNW)};
        auto tileNNWW{m_worldArea->getTile(coordinateNNWW)};
        auto tileNNE{m_worldArea->getTile(coordinateNNE)};
        auto tileSWW{m_worldArea->getTile(coordinateSWW)};
        auto tileNW{m_worldArea->getTile(coordinateNW)};
        auto tileNE{m_worldArea->getTile(coordinateNE)};
        auto tileSW{m_worldArea->getTile(coordinateSW)};
        auto tileSE{m_worldArea->getTile(coordinateSE)};
        auto tileNEE{m_worldArea->getTile(coordinateNEE)};
        auto tileSEE{m_worldArea->getTile(coordinateSEE)};
        auto tileSESE{m_worldArea->getTile(coordinateSESE)};
        auto tileSES{m_worldArea->getTile(coordinateSES)};
        auto tileSS{m_worldArea->getTile(coordinateSS)};

        std::vector<float> elevations;

        auto elevationNW{tileNW ? tileNW->getElevation() : 0.0F};
        auto elevationNE{tileNE ? tileNE->getElevation() : 0.0F};
        auto elevationSE{tileSE ? tileSE->getElevation() : 0.0F};
        auto elevationSW{tileSW ? tileSW->getElevation() : 0.0F};
        auto elevationNEE{tileNEE ? tileNEE->getElevation() : 0.0F};
        auto elevationSEE{tileSEE ? tileSEE->getElevation() : 0.0F};
        auto elevationSESE{tileSESE ? tileSESE->getElevation() : 0.0F};
        auto elevationSES{tileSES ? tileSES->getElevation() : 0.0F};
        auto elevationSS{tileSS ? tileSS->getElevation() : 0.0F};

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

        auto ground{tile->getGround()};

        auto color00{Palette::getColor<hash("White")>()};
        auto color10{Palette::getColor<hash("White")>()};
        auto color11{Palette::getColor<hash("White")>()};
        auto color01{Palette::getColor<hash("White")>()};

        if (ground != hash("GroundStoneSlab"))
        {
            color00 = getColorByGroundType(ground);

            if (tileNE)
            {
                color10 = getColorByGroundType(tileNE->getGround());
            }

            if (tileSE)
            {
                color11 = getColorByGroundType(tileSE->getGround());
            }

            if (tileSW)
            {
                color01 = getColorByGroundType(tileSW->getGround());
            }
        }

        auto forceRedraw{tile->getForceRedraw()};

        tile->setForceRedraw(false);

        if (ground == hash("GroundWater"))
        {
            auto waterDepth{tile->getWaterDepth()};

            waterDepth = std::min(waterDepth, k_maxWaterDepthRendering);

            std::string waterImageString{"GroundWater_Depth" + std::to_string(waterDepth)};

            // NOLINTNEXTLINE(readability-magic-numbers)
            auto animationIndex{(getTicks() + ((xCoordinate + yCoordinate) * 100)) / 500 % 3};

            waterImageString += "_" + std::to_string(animationIndex);

            ground = hash(waterImageString);

            tile->setForceRedraw(true);
        }

        m_tiles.push_back({m_renderIDsGround.at(xCoordinate).at(yCoordinate), ground, xCoordinate,
                           yCoordinate, m_rendTileSize, elevations, forceRedraw, color00, color10,
                           color11, color01});
    }

    auto WorldView::getColorByGroundType(int groundType) -> Color
    {
        switch (groundType)
        {
        case hash("GroundGrass"):
            return Palette::getColor<hash("DarkGreen")>();

        case hash("GroundWater"):
            return Palette::getColor<hash("LightBlue")>();

        case hash("GroundDirt"):
            return Palette::getColor<hash("Brown")>();

        case hash("GroundRock"):
            return Palette::getColor<hash("Gray")>();

        case hash("GroundStoneSlab"):
            return Palette::getColor<hash("White")>();
        default:
            break;
        }
        
        return Palette::getColor<hash("White")>();
    }
}