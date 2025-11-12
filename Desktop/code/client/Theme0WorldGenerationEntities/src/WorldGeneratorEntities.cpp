//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "WorldGeneratorEntities.hpp"

#include "WorldArea.hpp"

#include "Tile.hpp"

#include "ObjectsStack.hpp"

#include "Creature.hpp"

#include "Robot.hpp"

namespace Forradia::Theme0
{
    void WorldGeneratorEntities::GenerateCreaturesInEcosystems() const
    {
        auto worldArea{GetWorldArea()};

        auto size{worldArea->GetSize()};

        auto scale{GetScale()};

        // Generate white rabbits - prefer areas near water and in meadows/grass
        auto numWhiteRabbits{180 * scale + GetRandomInt(40 * scale)};

        for (auto i = 0; i < numWhiteRabbits; i++)
        {
            auto x{GetRandomInt(size.width)};
            auto y{GetRandomInt(size.height)};

            auto tile = worldArea->GetTile(x, y);
            if (!tile || tile->GetCreature() || tile->GetGround() == Hash("GroundWater"))
            {
                continue;
            }

            // Rabbits prefer grass areas, especially near water
            auto prefersLocation = false;

            if (tile->GetGround() == Hash("GroundGrass"))
            {
                // Higher chance if near water
                if (IsNearWater(x, y, 8))
                {
                    prefersLocation = GetRandomInt(100) < 40;
                }
                else
                {
                    prefersLocation = GetRandomInt(100) < 20;
                }
            }
            else if (tile->GetGround() == Hash("GroundDirt"))
            {
                // Lower chance on dirt
                prefersLocation = GetRandomInt(100) < 5;
            }

            if (prefersLocation)
            {
                auto newCreature = std::make_shared<Theme0::Creature>("CreatureWhiteRabbit");

                tile->SetCreature(newCreature);

                worldArea->GetCreaturesMirrorRef().insert({tile->GetCreature(), {x, y}});
            }
        }

        // Generate red birds - prefer areas with trees (forests) but also allow in open areas
        auto numRedBirds{120 * scale + GetRandomInt(30 * scale)};

        for (auto i = 0; i < numRedBirds; i++)
        {
            auto x{GetRandomInt(size.width)};
            auto y{GetRandomInt(size.height)};

            auto tile = worldArea->GetTile(x, y);
            if (!tile || tile->GetCreature() || tile->GetGround() == Hash("GroundWater"))
            {
                continue;
            }

            // Birds prefer areas with trees nearby (forests)
            // Check for trees in surrounding area
            int nearbyTreesCount = 0;
            for (auto checkY = y - 3; checkY <= y + 3; checkY++)
            {
                for (auto checkX = x - 3; checkX <= x + 3; checkX++)
                {
                    if (checkX == x && checkY == y)
                    {
                        continue; // Skip the current tile
                    }

                    if (!worldArea->IsValidCoordinate(checkX, checkY))
                    {
                        continue;
                    }

                    auto nearbyTile = worldArea->GetTile(checkX, checkY);
                    if (nearbyTile)
                    {
                        auto objectsStack = nearbyTile->GetObjectsStack();
                        if (objectsStack->GetSize() > 0)
                        {
                            // Check if it's a tree (FirTree or BirchTree)
                            // Note: We check if there are objects, which likely includes trees
                            // Birds can perch on trees, so nearby trees increase probability
                            nearbyTreesCount++;
                        }
                    }
                }
            }

            auto prefersLocation = false;

            // Birds strongly prefer areas with trees (forests)
            if (nearbyTreesCount >= 2)
            {
                // High probability in forest areas
                prefersLocation = GetRandomInt(100) < 50;
            }
            else if (nearbyTreesCount == 1)
            {
                // Moderate probability near a single tree
                prefersLocation = GetRandomInt(100) < 25;
            }
            else if (tile->GetGround() == Hash("GroundGrass"))
            {
                // Lower probability in open grass areas (birds can still be found there)
                prefersLocation = GetRandomInt(100) < 8;
            }

            if (prefersLocation)
            {
                auto newCreature = std::make_shared<Theme0::Creature>("CreatureRedBird");

                tile->SetCreature(newCreature);

                worldArea->GetCreaturesMirrorRef().insert({tile->GetCreature(), {x, y}});
            }
        }

        // Create creature clusters near water sources (more realistic ecosystems)
        auto numWaterSources{15 + GetRandomInt(10)};

        for (auto source = 0; source < numWaterSources; source++)
        {
            auto attempts = 0;
            int waterX = 0;
            int waterY = 0;
            bool foundWater = false;

            // Find a water tile
            while (attempts < 30 && !foundWater)
            {
                waterX = GetRandomInt(size.width);
                waterY = GetRandomInt(size.height);

                auto tile = worldArea->GetTile(waterX, waterY);
                if (tile && tile->GetGround() == Hash("GroundWater"))
                {
                    foundWater = true;
                }
                attempts++;
            }

            if (!foundWater)
            {
                continue;
            }

            // Create a small ecosystem around the water source
            auto ecosystemRadius{5 + GetRandomInt(8)};
            auto creaturesInEcosystem{3 + GetRandomInt(5)};

            for (auto c = 0; c < creaturesInEcosystem; c++)
            {
                auto angle = GetRandomInt(360) * M_PI / 180.0f;
                auto distance = 2 + GetRandomInt(ecosystemRadius);
                auto creatureX = waterX + CInt(std::cos(angle) * distance);
                auto creatureY = waterY + CInt(std::sin(angle) * distance);

                if (!worldArea->IsValidCoordinate(creatureX, creatureY))
                {
                    continue;
                }

                auto creatureTile = worldArea->GetTile(creatureX, creatureY);
                if (!creatureTile || creatureTile->GetCreature() ||
                    creatureTile->GetGround() == Hash("GroundWater"))
                {
                    continue;
                }

                // Prefer grass for the ecosystem
                if (creatureTile->GetGround() == Hash("GroundGrass") && GetRandomInt(100) < 60)
                {
                    auto newCreature = std::make_shared<Theme0::Creature>("CreatureWhiteRabbit");

                    creatureTile->SetCreature(newCreature);

                    worldArea->GetCreaturesMirrorRef().insert(
                        {creatureTile->GetCreature(), {creatureX, creatureY}});
                }
            }
        }
    }

    void WorldGeneratorEntities::GenerateRobotsInAreas() const
    {
        auto worldArea{GetWorldArea()};

        auto size{worldArea->GetSize()};

        auto scale{GetScale()};

        // Generate robots in clusters and patrol areas
        // Robots avoid water but can be found in various terrain types

        // First, create robot patrol clusters
        auto numRobotClusters{8 + GetRandomInt(7)};

        for (auto cluster = 0; cluster < numRobotClusters; cluster++)
        {
            auto centerX{GetRandomInt(size.width)};
            auto centerY{GetRandomInt(size.height)};

            auto centerTile = worldArea->GetTile(centerX, centerY);
            if (!centerTile || centerTile->GetGround() == Hash("GroundWater"))
            {
                continue;
            }

            auto clusterRadius{10 + GetRandomInt(15)};
            auto robotsInCluster{5 + GetRandomInt(10)};

            for (auto r = 0; r < robotsInCluster; r++)
            {
                auto angle = GetRandomInt(360) * M_PI / 180.0f;
                auto distance = GetRandomInt(clusterRadius);
                auto robotX = centerX + CInt(std::cos(angle) * distance);
                auto robotY = centerY + CInt(std::sin(angle) * distance);

                if (!worldArea->IsValidCoordinate(robotX, robotY))
                {
                    continue;
                }

                auto robotTile = worldArea->GetTile(robotX, robotY);
                if (!robotTile || robotTile->GetRobot() ||
                    robotTile->GetGround() == Hash("GroundWater"))
                {
                    continue;
                }

                auto newRobot = std::make_shared<Theme0::Robot>("RobotMechWolf", robotX, robotY);

                robotTile->SetRobot(newRobot);

                worldArea->GetRobotsMirrorRef().insert({robotTile->GetRobot(), {robotX, robotY}});
            }
        }

        // Also add scattered robots throughout the world
        auto numScatteredRobots{120 * scale + GetRandomInt(40 * scale)};

        for (auto i = 0; i < numScatteredRobots; i++)
        {
            auto x{GetRandomInt(size.width)};
            auto y{GetRandomInt(size.height)};

            auto tile = worldArea->GetTile(x, y);
            if (!tile || tile->GetRobot() || tile->GetGround() == Hash("GroundWater"))
            {
                continue;
            }

            // Robots can appear anywhere except water, with equal probability
            if (GetRandomInt(100) < 15)
            {
                auto newRobot = std::make_shared<Theme0::Robot>("RobotMechWolf", x, y);

                tile->SetRobot(newRobot);

                worldArea->GetRobotsMirrorRef().insert({tile->GetRobot(), {x, y}});
            }
        }
    }
}