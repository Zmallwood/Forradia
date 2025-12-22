/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "Entity.hpp"
#include "Object.hpp"
#include "ObjectsStack.hpp"
#include "Tile.hpp"
#include "WorldArea.hpp"
#include "WorldGeneratorEntities.hpp"

namespace Forradia::Theme0
{
    auto WorldGeneratorEntities::GenerateEntitiesInEcosystems() const -> void
    {
        auto worldArea{GetWorldArea()};
        auto worldAreaSize{worldArea->GetSize()};
        auto worldScaling{GetWorldScaling()};

        // Generate white rabbits - prefer areas near water and in meadows/grass.
        auto numWhiteRabbits{180 * worldScaling + GetRandomInt(40 * worldScaling)};

        for (auto i = 0; i < numWhiteRabbits; i++)
        {
            auto x{GetRandomInt(worldAreaSize.width)};
            auto y{GetRandomInt(worldAreaSize.height)};

            auto tile{worldArea->GetTile(x, y)};

            if (!tile || tile->GetEntity() || tile->GetGround() == Hash("GroundWater"))
                continue;

            auto prefersLocation{false};

            if (tile->GetGround() == Hash("GroundGrass"))
            {
                if (IsNearWater(x, y, 8))
                    prefersLocation = GetRandomInt(100) < 40;
                else
                    prefersLocation = GetRandomInt(100) < 20;
            }
            else if (tile->GetGround() == Hash("GroundDirt"))
            {
                prefersLocation = GetRandomInt(100) < 5;
            }

            if (prefersLocation)
            {
                auto newEntity{std::make_shared<Theme0::Entity>("CreatureWhiteRabbit")};

                tile->SetEntity(newEntity);

                worldArea->GetEntitiesMirrorRef().insert({tile->GetEntity(), {x, y}});
            }
        }

        auto numWolves{180 * worldScaling + GetRandomInt(40 * worldScaling)};

        for (auto i = 0; i < numWolves; i++)
        {
            auto x{GetRandomInt(worldAreaSize.width)};
            auto y{GetRandomInt(worldAreaSize.height)};

            auto tile{worldArea->GetTile(x, y)};

            if (!tile || tile->GetEntity() || tile->GetGround() == Hash("GroundWater"))
                continue;

            auto prefersLocation{false};

            if (tile->GetGround() == Hash("GroundGrass"))
            {
                if (IsNearWater(x, y, 8))
                    prefersLocation = GetRandomInt(100) < 40;
                else
                    prefersLocation = GetRandomInt(100) < 20;
            }
            else if (tile->GetGround() == Hash("GroundDirt"))
            {
                prefersLocation = GetRandomInt(100) < 5;
            }

            if (prefersLocation)
            {
                auto newEntity{std::make_shared<Theme0::Entity>("CreatureWolf")};

                tile->SetEntity(newEntity);

                worldArea->GetEntitiesMirrorRef().insert({tile->GetEntity(), {x, y}});
            }
        }

        // Generate red birds - prefer areas with trees (forests) but also allow in open areas.
        auto numRedBirds{120 * worldScaling + GetRandomInt(30 * worldScaling)};

        for (auto i = 0; i < numRedBirds; i++)
        {
            auto x{GetRandomInt(worldAreaSize.width)};
            auto y{GetRandomInt(worldAreaSize.height)};

            auto tile{worldArea->GetTile(x, y)};

            if (!tile || tile->GetEntity() || tile->GetGround() == Hash("GroundWater"))
                continue;

            // Birds prefer areas with trees nearby (forests).
            // Check for trees in surrounding area.

            auto nearbyTreesCount{0};

            // Check for trees in the surrounding area.
            for (auto checkY = y - 3; checkY <= y + 3; checkY++)
            {
                for (auto checkX = x - 3; checkX <= x + 3; checkX++)
                {
                    if (checkX == x && checkY == y)
                        continue;

                    if (!worldArea->IsValidCoordinate(checkX, checkY))
                        continue;

                    auto nearbyTile{worldArea->GetTile(checkX, checkY)};

                    if (nearbyTile)
                    {
                        auto objectsStack{nearbyTile->GetObjectsStack()};

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

            if (nearbyTreesCount >= 2)
                // High probability in forest areas.
                prefersLocation = GetRandomInt(100) < 50;
            else if (nearbyTreesCount == 1)
                // Moderate probability near a single tree.
                prefersLocation = GetRandomInt(100) < 25;
            else if (tile->GetGround() == Hash("GroundGrass"))
                // Lower probability in open grass areas (birds can still be found there).
                prefersLocation = GetRandomInt(100) < 8;

            if (prefersLocation)
            {
                auto newEntity{std::make_shared<Theme0::Entity>("CreatureRedBird")};

                tile->SetEntity(newEntity);

                worldArea->GetEntitiesMirrorRef().insert({tile->GetEntity(), {x, y}});
            }
        }

        // Create creature clusters near water sources (more realistic ecosystems).
        auto numWaterSources{15 + GetRandomInt(10)};

        for (auto source = 0; source < numWaterSources; source++)
        {
            auto x{GetRandomInt(worldAreaSize.width)};
            auto y{GetRandomInt(worldAreaSize.height)};

            auto tile{worldArea->GetTile(x, y)};

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
                    foundWater = true;

                attempts++;
            }

            if (!foundWater)
                continue;

            // Create a small ecosystem around the water source.

            auto ecosystemRadius{5 + GetRandomInt(8)};

            auto creaturesInEcosystem{3 + GetRandomInt(5)};

            // Generate the creatures in the ecosystem.
            for (auto c = 0; c < creaturesInEcosystem; c++)
            {
                // Generate a random angle.
                auto angle{GetRandomInt(360) * M_PI / 180.0F};

                // Generate a random distance.
                auto distance{2 + GetRandomInt(ecosystemRadius)};

                auto creatureX{waterX + static_cast<int>(std::cos(angle) * distance)};
                auto creatureY{waterY + static_cast<int>(std::sin(angle) * distance)};

                // If the coordinates are out of bounds.
                if (!worldArea->IsValidCoordinate(creatureX, creatureY))
                    continue;

                auto creatureTile{worldArea->GetTile(creatureX, creatureY)};

                if (!creatureTile || creatureTile->GetEntity() ||
                    creatureTile->GetGround() == Hash("GroundWater"))
                    continue;

                // Prefer grass for the ecosystem.
                if (creatureTile->GetGround() == Hash("GroundGrass") && GetRandomInt(100) < 60)
                {
                    auto newEntity{std::make_shared<Theme0::Entity>("CreatureWhiteRabbit")};

                    creatureTile->SetEntity(newEntity);

                    worldArea->GetEntitiesMirrorRef().insert(
                        {creatureTile->GetEntity(), {creatureX, creatureY}});
                }
            }
        }
    }
}
