//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "WorldGeneratorEntities.hpp"

#include "WorldArea.hpp"

#include "Tile.hpp"

#include "Creature.hpp"

#include "ObjectsStack.hpp"

#include "Object.hpp"

namespace Forradia::Theme0
{
    void WorldGeneratorEntities::GenerateCreaturesInEcosystems() const
    {
        // Obtain required data.

        auto worldArea{GetWorldArea()};

        auto worldAreaSize{worldArea->GetSize()};

        auto worldScaling{GetWorldScaling()};

        // Generate white rabbits - prefer areas near water and in meadows/grass.

        // Number of white rabbits to generate.

        auto numWhiteRabbits{180 * worldScaling + GetRandomInt(40 * worldScaling)};

        // Generate white rabbits.

        for (auto i = 0; i < numWhiteRabbits; i++)
        {
            // Generate a random position.

            auto x{GetRandomInt(worldAreaSize.width)};

            auto y{GetRandomInt(worldAreaSize.height)};

            // Get the tile at the position.

            auto tile{worldArea->GetTile(x, y)};

            // If the tile is invalid, or already has a creature or is water.

            if (!tile || tile->GetCreature() || tile->GetGround() == Hash("GroundWater"))
            {
                // Skip this position.

                continue;
            }

            // To hold result from the algorithm for determining if the rabbit should be placed at
            // this position.

            auto prefersLocation{false};

            // Rabbits prefer grass areas.

            if (tile->GetGround() == Hash("GroundGrass"))
            {
                // Check if there is water within 8 tiles of the rabbit.

                if (IsNearWater(x, y, 8))
                {
                    // Higher chance if near water.

                    prefersLocation = GetRandomInt(100) < 40;
                }
                else
                {
                    // Lower chance if not near water.

                    prefersLocation = GetRandomInt(100) < 20;
                }
            }
            else if (tile->GetGround() == Hash("GroundDirt"))
            {
                // Lower chance on dirt.

                prefersLocation = GetRandomInt(100) < 5;
            }

            // If the rabbit should be placed at this position.

            if (prefersLocation)
            {
                // Create a new rabbit.

                auto newCreature{std::make_shared<Theme0::Creature>("CreatureWhiteRabbit")};

                // Set the rabbit on the tile.

                tile->SetCreature(newCreature);

                // Add the rabbit to the world area creatures mirror.

                worldArea->GetCreaturesMirrorRef().insert({tile->GetCreature(), {x, y}});
            }
        }

        // Generate red birds - prefer areas with trees (forests) but also allow in open areas.

        // Number of red birds to generate.

        auto numRedBirds{120 * worldScaling + GetRandomInt(30 * worldScaling)};

        // Generate the red birds.

        for (auto i = 0; i < numRedBirds; i++)
        {
            // Generate a random position.

            auto x{GetRandomInt(worldAreaSize.width)};

            auto y{GetRandomInt(worldAreaSize.height)};

            // Get the tile at the position.

            auto tile{worldArea->GetTile(x, y)};

            // If the tile is invalid, or already has a creature or is water.

            if (!tile || tile->GetCreature() || tile->GetGround() == Hash("GroundWater"))
            {
                // Skip this position.

                continue;
            }

            // Birds prefer areas with trees nearby (forests).
            // Check for trees in surrounding area.

            // To hold the number of trees nearby.

            auto nearbyTreesCount{0};

            // Check for trees in the surrounding area.

            for (auto checkY = y - 3; checkY <= y + 3; checkY++)
            {
                for (auto checkX = x - 3; checkX <= x + 3; checkX++)
                {
                    // If the current tile is the same as the bird's tile.

                    if (checkX == x && checkY == y)
                    {
                        // Skip the current tile.

                        continue;
                    }

                    // If the current tile is out of bounds.

                    if (!worldArea->IsValidCoordinate(checkX, checkY))
                    {
                        // Skip the current tile.

                        continue;
                    }

                    // Get the tile at the position.

                    auto nearbyTile{worldArea->GetTile(checkX, checkY)};

                    // If the tile is valid.

                    if (nearbyTile)
                    {
                        // Get the objects stack from the tile.

                        auto objectsStack{nearbyTile->GetObjectsStack()};

                        // If the objects stack is not empty.

                        if (objectsStack->GetSize() > 0)
                        {
                            for (auto object : objectsStack->GetObjects())
                            {
                                auto objectType{object->GetType()};

                                if (objectType == Hash("ObjectFirTree") ||
                                    objectType == Hash("ObjectBirchTree"))
                                {
                                    nearbyTreesCount++;

                                    // Birds can perch on trees, so nearby trees increase
                                    // probability.

                                    nearbyTreesCount++;
                                }
                            }
                        }
                    }
                }
            }

            auto prefersLocation{false};

            // Birds strongly prefer areas with trees (forests).

            if (nearbyTreesCount >= 2)
            {
                // High probability in forest areas.

                prefersLocation = GetRandomInt(100) < 50;
            }
            else if (nearbyTreesCount == 1)
            {
                // Moderate probability near a single tree.

                prefersLocation = GetRandomInt(100) < 25;
            }
            else if (tile->GetGround() == Hash("GroundGrass"))
            {
                // Lower probability in open grass areas (birds can still be found there).

                prefersLocation = GetRandomInt(100) < 8;
            }

            if (prefersLocation)
            {
                auto newCreature{std::make_shared<Theme0::Creature>("CreatureRedBird")};

                tile->SetCreature(newCreature);

                worldArea->GetCreaturesMirrorRef().insert({tile->GetCreature(), {x, y}});
            }
        }

        // Create creature clusters near water sources (more realistic ecosystems).

        auto numWaterSources{15 + GetRandomInt(10)};

        for (auto source = 0; source < numWaterSources; source++)
        {
            auto attempts{0};

            auto waterX{0};

            auto waterY{0};

            auto foundWater{false};

            // Find a water tile.

            while (attempts < 30 && !foundWater)
            {
                waterX = GetRandomInt(worldAreaSize.width);

                waterY = GetRandomInt(worldAreaSize.height);

                auto tile{worldArea->GetTile(waterX, waterY)};

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

            // Create a small ecosystem around the water source.

            auto ecosystemRadius{5 + GetRandomInt(8)};

            auto creaturesInEcosystem{3 + GetRandomInt(5)};

            for (auto c = 0; c < creaturesInEcosystem; c++)
            {
                auto angle{GetRandomInt(360) * M_PI / 180.0f};

                auto distance{2 + GetRandomInt(ecosystemRadius)};

                auto creatureX{waterX + CInt(std::cos(angle) * distance)};

                auto creatureY{waterY + CInt(std::sin(angle) * distance)};

                if (!worldArea->IsValidCoordinate(creatureX, creatureY))
                {
                    continue;
                }

                auto creatureTile{worldArea->GetTile(creatureX, creatureY)};

                if (!creatureTile || creatureTile->GetCreature() ||
                    creatureTile->GetGround() == Hash("GroundWater"))
                {
                    continue;
                }

                // Prefer grass for the ecosystem.

                if (creatureTile->GetGround() == Hash("GroundGrass") && GetRandomInt(100) < 60)
                {
                    auto newCreature{std::make_shared<Theme0::Creature>("CreatureWhiteRabbit")};

                    creatureTile->SetCreature(newCreature);

                    worldArea->GetCreaturesMirrorRef().insert(
                        {creatureTile->GetCreature(), {creatureX, creatureY}});
                }
            }
        }
    }
}