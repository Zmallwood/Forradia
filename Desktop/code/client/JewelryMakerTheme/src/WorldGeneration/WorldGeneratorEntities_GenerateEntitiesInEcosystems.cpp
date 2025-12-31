/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "WorldGeneratorBase.hpp"
#include "WorldGeneratorEntities.hpp"
#include "WorldStructure/Entity.hpp"
#include "WorldStructure/Object.hpp"
#include "WorldStructure/ObjectsStack.hpp"
#include "WorldStructure/Tile.hpp"
#include "WorldStructure/WorldArea.hpp"
#include "ForradiaEngine/Common/General.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    namespace
    {
        auto isNearWater(const std::shared_ptr<WorldArea> &worldArea, int xPos, int yPos,
                         int radius) -> bool
        {
            for (auto checkY = yPos - radius; checkY <= yPos + radius; checkY++)
            {
                for (auto checkX = xPos - radius; checkX <= xPos + radius; checkX++)
                {
                    if (!worldArea->isValidCoordinate(checkX, checkY))
                    {
                        continue;
                    }

                    auto tile{worldArea->getTile(checkX, checkY)};

                    if (tile && tile->getGround() == hash("GroundWater"))
                    {
                        auto distance{calcDistance(xPos, yPos, checkX, checkY)};

                        if (distance <= radius)
                        {
                            return true;
                        }
                    }
                }
            }

            return false;
        }

        auto generateScatteredWhiteRabbits(const std::shared_ptr<WorldArea> &worldArea,
                                           int worldScaling) -> void
        {
            auto worldAreaSize{worldArea->getSize()};

            // Generate white rabbits - prefer areas near water and in meadows/grass.
            auto numWhiteRabbits{
                WorldGeneratorBase::getParam<int>("numWhiteRabbitsBase") * worldScaling +
                getRandomInt(WorldGeneratorBase::getParam<int>("numWhiteRabbitsRandom") *
                             worldScaling)};

            for (auto i = 0; i < numWhiteRabbits; i++)
            {
                auto xPos{getRandomInt(worldAreaSize.width)};
                auto yPos{getRandomInt(worldAreaSize.height)};

                auto tile{worldArea->getTile(xPos, yPos)};

                if (!tile || tile->getEntity() || tile->getGround() == hash("GroundWater"))
                {
                    continue;
                }

                auto prefersLocation{false};

                if (tile->getGround() == hash("GroundGrass"))
                {
                    if (isNearWater(worldArea, xPos, yPos, 8))
                    {
                        prefersLocation =
                            getRandomInt(WorldGeneratorBase::getParam<int>("100Percent")) <
                            WorldGeneratorBase::getParam<int>(
                                "whiteRabbitPrefersLocationNearWaterProbability");
                    }
                    else
                    {
                        prefersLocation =
                            getRandomInt(WorldGeneratorBase::getParam<int>("100Percent")) <
                            WorldGeneratorBase::getParam<int>(
                                "whiteRabbitPrefersLocationAwayFromWaterProbability");
                    }
                }
                else if (tile->getGround() == hash("GroundDirt"))
                {
                    prefersLocation =
                        getRandomInt(WorldGeneratorBase::getParam<int>("100Percent")) <
                        WorldGeneratorBase::getParam<int>(
                            "whiteRabbitPrefersLocationOnDirtProbability");
                }

                if (prefersLocation)
                {
                    auto newEntity{
                        std::make_shared<JewelryMakerTheme::Entity>("CreatureWhiteRabbit")};

                    tile->setEntity(newEntity);

                    worldArea->getEntitiesMirrorRef().insert({tile->getEntity(), {xPos, yPos}});
                }
            }
        }

        auto generateScatteredWolves(const std::shared_ptr<WorldArea> &worldArea, int worldScaling)
            -> void
        {
            auto worldAreaSize{worldArea->getSize()};

            auto numWolves{
                WorldGeneratorBase::getParam<int>("numWolvesBase") * worldScaling +
                getRandomInt(WorldGeneratorBase::getParam<int>("numWolvesRandom") * worldScaling)};

            for (auto i = 0; i < numWolves; i++)
            {
                auto xPos{getRandomInt(worldAreaSize.width)};
                auto yPos{getRandomInt(worldAreaSize.height)};

                auto tile{worldArea->getTile(xPos, yPos)};

                if (!tile || tile->getEntity() || tile->getGround() == hash("GroundWater"))
                {
                    continue;
                }

                auto prefersLocation{false};

                if (tile->getGround() == hash("GroundGrass"))
                {
                    if (isNearWater(worldArea, xPos, yPos, 8))
                    {
                        prefersLocation =
                            getRandomInt(WorldGeneratorBase::getParam<int>("100Percent")) <
                            WorldGeneratorBase::getParam<int>(
                                "wolfPrefersLocationNearWaterProbability");
                    }
                    else
                    {
                        prefersLocation =
                            getRandomInt(WorldGeneratorBase::getParam<int>("100Percent")) <
                            WorldGeneratorBase::getParam<int>(
                                "wolfPrefersLocationAwayFromWaterProbability");
                    }
                }
                else if (tile->getGround() == hash("GroundDirt"))
                {
                    prefersLocation =
                        getRandomInt(WorldGeneratorBase::getParam<int>("100Percent")) <
                        WorldGeneratorBase::getParam<int>("wolfPrefersLocationOnDirtProbability");
                }

                if (prefersLocation)
                {
                    auto newEntity{std::make_shared<JewelryMakerTheme::Entity>("CreatureWolf")};

                    tile->setEntity(newEntity);

                    worldArea->getEntitiesMirrorRef().insert({tile->getEntity(), {xPos, yPos}});
                }
            }
        }

        auto calculateNearbyTreesCount(const std::shared_ptr<WorldArea> &worldArea, int xPos,
                                       int yPos) -> int
        {
            auto nearbyTreesCount{0};

            // Check for trees in the surrounding area.
            for (auto checkY = yPos - 3; checkY <= yPos + 3; checkY++)
            {
                for (auto checkX = xPos - 3; checkX <= xPos + 3; checkX++)
                {
                    if (checkX == xPos && checkY == yPos)
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

                        for (const auto &object : objectsStack->getObjects())
                        {
                            auto objectType{object->getType()};

                            if (objectType == hash("ObjectFirTree") ||
                                objectType == hash("ObjectBirchTree"))
                            {
                                // Birds can perch on trees, so nearby trees increase
                                // probability.
                                nearbyTreesCount++;
                            }
                        }
                    }
                }
            }

            return nearbyTreesCount;
        }

        auto generateScatteredRedBirds(const std::shared_ptr<WorldArea> &worldArea,
                                       int worldScaling) -> void
        {
            auto worldAreaSize{worldArea->getSize()};

            // Generate red birds - prefer areas with trees (forests) but also allow in open areas.
            auto numRedBirds{WorldGeneratorBase::getParam<int>("numRedBirdsBase") * worldScaling +
                             getRandomInt(WorldGeneratorBase::getParam<int>("numRedBirdsRandom") *
                                          worldScaling)};

            for (auto i = 0; i < numRedBirds; i++)
            {
                auto xPos{getRandomInt(worldAreaSize.width)};
                auto yPos{getRandomInt(worldAreaSize.height)};

                auto tile{worldArea->getTile(xPos, yPos)};

                if (!tile || tile->getEntity() || tile->getGround() == hash("GroundWater"))
                {
                    continue;
                }

                // Birds prefer areas with trees nearby (forests).
                // Check for trees in surrounding area.

                auto nearbyTreesCount{calculateNearbyTreesCount(worldArea, xPos, yPos)};

                auto prefersLocation{false};

                if (nearbyTreesCount >= 2)
                {
                    // High probability in forest areas.
                    prefersLocation =
                        getRandomInt(WorldGeneratorBase::getParam<int>("100Percent")) <
                        WorldGeneratorBase::getParam<int>(
                            "redBirdsPrefersLocationForestAreasProbability");
                }
                else if (nearbyTreesCount == 1)
                {
                    // Moderate probability near a single tree.
                    prefersLocation =
                        getRandomInt(WorldGeneratorBase::getParam<int>("100Percent")) <
                        WorldGeneratorBase::getParam<int>(
                            "redBirdsPrefersLocationNearSingleTreeProbability");
                }
                else if (tile->getGround() == hash("GroundGrass"))
                {
                    // Lower probability in open grass areas (birds can still be found there).
                    prefersLocation =
                        getRandomInt(WorldGeneratorBase::getParam<int>("100Percent")) <
                        WorldGeneratorBase::getParam<int>(
                            "redBirdsPrefersLocationOpenGrassAreasProbability");
                }

                if (prefersLocation)
                {
                    auto newEntity{std::make_shared<JewelryMakerTheme::Entity>("CreatureRedBird")};

                    tile->setEntity(newEntity);

                    worldArea->getEntitiesMirrorRef().insert({tile->getEntity(), {xPos, yPos}});
                }
            }
        }

        auto generateCreatureClustersNearWaterSources(const std::shared_ptr<WorldArea> &worldArea,
                                                      int worldScaling) -> void
        {
            auto worldAreaSize{worldArea->getSize()};

            // Create creature clusters near water sources (more realistic ecosystems).
            // NOLINTNEXTLINE(readability-magic-numbers)
            auto numWaterSources{15 + getRandomInt(10)};

            for (auto source = 0; source < numWaterSources; source++)
            {
                auto xPos{getRandomInt(worldAreaSize.width)};
                auto yPos{getRandomInt(worldAreaSize.height)};

                auto tile{worldArea->getTile(xPos, yPos)};

                auto attempts{0};

                auto waterX{0};
                auto waterY{0};

                auto foundWater{false};

                // Find a water tile.
                // NOLINTNEXTLINE(readability-magic-numbers)
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

                // NOLINTNEXTLINE(readability-magic-numbers)
                auto ecosystemRadius{5 + getRandomInt(8)};

                // NOLINTNEXTLINE(readability-magic-numbers)
                auto creaturesInEcosystem{3 + getRandomInt(5)};

                // Generate the creatures in the ecosystem.
                for (auto i = 0; i < creaturesInEcosystem; i++)
                {
                    // Generate a random angle.
                    // NOLINTNEXTLINE(readability-magic-numbers)
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
                    // NOLINTNEXTLINE(readability-magic-numbers)
                    if (creatureTile->getGround() == hash("GroundGrass") && getRandomInt(100) < 60)
                    {
                        auto newEntity{
                            std::make_shared<JewelryMakerTheme::Entity>("CreatureWhiteRabbit")};

                        creatureTile->setEntity(newEntity);

                        worldArea->getEntitiesMirrorRef().insert(
                            {creatureTile->getEntity(), {creatureX, creatureY}});
                    }
                }
            }
        }
    }

    auto WorldGeneratorEntities::generateEntitiesInEcosystems() -> void
    {
        auto worldArea{getWorldArea()};
        auto worldScaling{getWorldScaling()};

        generateScatteredWhiteRabbits(worldArea, worldScaling);

        generateScatteredWolves(worldArea, worldScaling);

        generateScatteredRedBirds(worldArea, worldScaling);

        generateCreatureClustersNearWaterSources(worldArea, worldScaling);
    }
}
