/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "Content/WorldStructure/Entity.hpp"
    #include "Content/WorldStructure/Object.hpp"
    #include "Content/WorldStructure/ObjectsStack.hpp"
    #include "Content/WorldStructure/Tile.hpp"
    #include "Content/WorldStructure/WorldArea.hpp"
    #include "WorldGeneratorEntities.hpp"
// clang-format on

namespace ForradiaEngine::JewelryMakerTheme
{
    auto WorldGeneratorEntities::generateEntitiesInEcosystems() const -> void
    {
        auto worldArea{getWorldArea()};
        auto worldAreaSize{worldArea->getSize()};
        auto worldScaling{getWorldScaling()};

        // Generate white rabbits - prefer areas near water and in meadows/grass.
        auto numWhiteRabbits{180 * worldScaling + getRandomInt(40 * worldScaling)};

        for (auto i = 0; i < numWhiteRabbits; i++)
        {
            auto x{getRandomInt(worldAreaSize.width)};
            auto y{getRandomInt(worldAreaSize.height)};

            auto tile{worldArea->getTile(x, y)};

            if (!tile || tile->getEntity() || tile->getGround() == hash("GroundWater"))
            {
                continue;
            }

            auto prefersLocation{false};

            if (tile->getGround() == hash("GroundGrass"))
            {
                if (isNearWater(x, y, 8))
                {
                    prefersLocation = getRandomInt(100) < 40;
                }
                else
                {
                    prefersLocation = getRandomInt(100) < 20;
                }
            }
            else if (tile->getGround() == hash("GroundDirt"))
            {
                prefersLocation = getRandomInt(100) < 5;
            }

            if (prefersLocation)
            {
                auto newEntity{std::make_shared<JewelryMakerTheme::Entity>("CreatureWhiteRabbit")};

                tile->setEntity(newEntity);

                worldArea->getEntitiesMirrorRef().insert({tile->getEntity(), {x, y}});
            }
        }

        auto numWolves{180 * worldScaling + getRandomInt(40 * worldScaling)};

        for (auto i = 0; i < numWolves; i++)
        {
            auto x{getRandomInt(worldAreaSize.width)};
            auto y{getRandomInt(worldAreaSize.height)};

            auto tile{worldArea->getTile(x, y)};

            if (!tile || tile->getEntity() || tile->getGround() == hash("GroundWater"))
            {
                continue;
            }

            auto prefersLocation{false};

            if (tile->getGround() == hash("GroundGrass"))
            {
                if (isNearWater(x, y, 8))
                {
                    prefersLocation = getRandomInt(100) < 40;
                }
                else
                {
                    prefersLocation = getRandomInt(100) < 20;
                }
            }
            else if (tile->getGround() == hash("GroundDirt"))
            {
                prefersLocation = getRandomInt(100) < 5;
            }

            if (prefersLocation)
            {
                auto newEntity{std::make_shared<JewelryMakerTheme::Entity>("CreatureWolf")};

                tile->setEntity(newEntity);

                worldArea->getEntitiesMirrorRef().insert({tile->getEntity(), {x, y}});
            }
        }

        // Generate red birds - prefer areas with trees (forests) but also allow in open areas.
        auto numRedBirds{120 * worldScaling + getRandomInt(30 * worldScaling)};

        for (auto i = 0; i < numRedBirds; i++)
        {
            auto x{getRandomInt(worldAreaSize.width)};
            auto y{getRandomInt(worldAreaSize.height)};

            auto tile{worldArea->getTile(x, y)};

            if (!tile || tile->getEntity() || tile->getGround() == hash("GroundWater"))
            {
                continue;
            }

            // Birds prefer areas with trees nearby (forests).
            // Check for trees in surrounding area.

            auto nearbyTreesCount{0};

            // Check for trees in the surrounding area.
            for (auto checkY = y - 3; checkY <= y + 3; checkY++)
            {
                for (auto checkX = x - 3; checkX <= x + 3; checkX++)
                {
                    if (checkX == x && checkY == y)
                    {
                        continue;
                    }

                    if (!worldArea->isValidCoordinate(checkX, checkY))
                    {
                        continue;
                    }

                    auto nearbyTile{worldArea->getTile(checkX, checkY)};

                    if (nearbyTile)
                    {
                        auto objectsStack{nearbyTile->getObjectsStack()};

                        if (objectsStack->getSize() > 0)
                        {
                            for (auto object : objectsStack->getObjects())
                            {
                                auto objectType{object->getType()};

                                if (objectType == hash("ObjectFirTree") ||
                                    objectType == hash("ObjectBirchTree"))
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
            {
                // High probability in forest areas.
                prefersLocation = getRandomInt(100) < 50;
            }
            else if (nearbyTreesCount == 1)
            {
                // Moderate probability near a single tree.
                prefersLocation = getRandomInt(100) < 25;
            }
            else if (tile->getGround() == hash("GroundGrass"))
            {
                // Lower probability in open grass areas (birds can still be found there).
                prefersLocation = getRandomInt(100) < 8;
            }

            if (prefersLocation)
            {
                auto newEntity{std::make_shared<JewelryMakerTheme::Entity>("CreatureRedBird")};

                tile->setEntity(newEntity);

                worldArea->getEntitiesMirrorRef().insert({tile->getEntity(), {x, y}});
            }
        }

        // Create creature clusters near water sources (more realistic ecosystems).
        auto numWaterSources{15 + getRandomInt(10)};

        for (auto source = 0; source < numWaterSources; source++)
        {
            auto x{getRandomInt(worldAreaSize.width)};
            auto y{getRandomInt(worldAreaSize.height)};

            auto tile{worldArea->getTile(x, y)};

            auto attempts{0};

            auto waterX{0};
            auto waterY{0};

            auto foundWater{false};

            // Find a water tile.
            while (attempts < 30 && !foundWater)
            {
                waterX = getRandomInt(worldAreaSize.width);
                waterY = getRandomInt(worldAreaSize.height);

                auto tile{worldArea->getTile(waterX, waterY)};

                if (tile && tile->getGround() == hash("GroundWater"))
                {
                    foundWater = true;
                }

                attempts++;
            }

            if (!foundWater)
                continue;

            // Create a small ecosystem around the water source.

            auto ecosystemRadius{5 + getRandomInt(8)};

            auto creaturesInEcosystem{3 + getRandomInt(5)};

            // Generate the creatures in the ecosystem.
            for (auto c = 0; c < creaturesInEcosystem; c++)
            {
                // Generate a random angle.
                auto angle{getRandomInt(360) * M_PI / 180.0F};

                // Generate a random distance.
                auto distance{2 + getRandomInt(ecosystemRadius)};

                auto creatureX{waterX + static_cast<int>(std::cos(angle) * distance)};
                auto creatureY{waterY + static_cast<int>(std::sin(angle) * distance)};

                // If the coordinates are out of bounds.
                if (!worldArea->isValidCoordinate(creatureX, creatureY))
                {
                    continue;
                }

                auto creatureTile{worldArea->getTile(creatureX, creatureY)};

                if (!creatureTile || creatureTile->getEntity() ||
                    creatureTile->getGround() == hash("GroundWater"))
                {
                    continue;
                }

                // Prefer grass for the ecosystem.
                if (creatureTile->getGround() == hash("GroundGrass") && getRandomInt(100) < 60)
                {
                    auto newEntity{std::make_shared<JewelryMakerTheme::Entity>("CreatureWhiteRabbit")};

                    creatureTile->setEntity(newEntity);

                    worldArea->getEntitiesMirrorRef().insert(
                        {creatureTile->getEntity(), {creatureX, creatureY}});
                }
            }
        }
    }
}
