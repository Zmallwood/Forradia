/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "GameSaving.hpp"
    #include "Content/WorldStructure/Entity.hpp"
    #include "Content/WorldStructure/Object.hpp"
    #include "Content/WorldStructure/ObjectsStack.hpp"
    #include "Content/WorldStructure/Tile.hpp"
    #include "Content/WorldStructure/World.hpp"
    #include "Content/WorldStructure/WorldArea.hpp"
    #include "ForradiaEngine/Rendering/Ground/GroundRenderer.hpp"
    #include "HashCodes.hpp"
    #include <fstream>
    #include <string>
// clang-format on

namespace ForradiaEngine::JewelryMakerTheme
{
    auto GameSaving::saveGame() -> void
    {
        auto worldArea{World::instance().getCurrentWorldArea()};

        // Validation
        if (!worldArea)
        {
            return;
        }

        nlohmann::json jsonData;

        // Get world area size
        auto worldAreaSize{worldArea->getSize()};

        jsonData["size"]["width"] = worldAreaSize.width;
        jsonData["size"]["height"] = worldAreaSize.height;

        /* Serialize tiles */ // clang-format off
            jsonData["tiles"] = nlohmann::json::array();

            for (auto yCoord = 0; yCoord < worldAreaSize.height; yCoord++)
            {
                for (auto xCoord = 0; xCoord < worldAreaSize.width; xCoord++)
                {
                    auto tile{worldArea->getTile(xCoord, yCoord)};

                    if (!tile)
                    {
                        continue;
                    }

                    nlohmann::json tileJson;

                    tileJson["x"] = xCoord;
                    tileJson["y"] = yCoord;
                    tileJson["elevation"] = tile->getElevation();
                    tileJson["ground"] = getNameFromAnyHash(tile->getGround());

                    // Serialize objects on this tile
                    auto objectsStack{tile->getObjectsStack()};

                    if (objectsStack)
                    {
                        auto objects{objectsStack->getObjects()};
                        tileJson["objects"] = nlohmann::json::array();

                        for (auto &object : objects)
                        {
                            if (object)
                            {
                                nlohmann::json objectJson;

                                objectJson["type"] = getNameFromAnyHash(object->getType());
                                tileJson["objects"].push_back(objectJson);
                            }
                        }
                    }

                    // Serialize entity on this tile
                    auto entity{tile->getEntity()};

                    if (entity)
                    {
                        nlohmann::json entityJson;

                        entityJson["type"] = getNameFromAnyHash(entity->getType());
                        tileJson["entity"] = entityJson;
                    }

                    jsonData["tiles"].push_back(tileJson);
                }
            }
        // clang-format on

        /* Save game to file */ // clang-format off
            std::ofstream file("savegame.json");

            if (file.is_open())
            {
                file << jsonData.dump(4); // Pretty print with 4-space indent
                file.close();
            }
        // clang-format on
    }

    auto GameSaving::loadGame() -> void
    {
        GroundRenderer::instance().reset();

        std::ifstream file("savegame.json");

        if (!file.is_open())
        {
            return;
        }

        nlohmann::json jsonData;

        try
        {
            file >> jsonData;
            file.close();
        }
        catch (const std::exception &)
        {
            return;
        }

        auto worldArea{World::instance().getCurrentWorldArea()};

        if (!worldArea)
        {
            return;
        }

        worldArea->reset();

        GameSaving::loadTiles(worldArea, jsonData);
    }

    auto GameSaving::loadTiles(const std::shared_ptr<WorldArea> &worldArea,
                               const nlohmann::json &jsonData) -> void
    {
        auto &entities{worldArea->getEntitiesMirrorRef()};

        if (!jsonData.contains("tiles") || !jsonData["tiles"].is_array())
        {
            return;
        }

        for (const auto &tileJson : jsonData["tiles"])
        {
            if (!tileJson.contains("x") || !tileJson.contains("y"))
            {
                continue;
            }

            auto xCoord{tileJson["x"].get<int>()};
            auto yCoord{tileJson["y"].get<int>()};

            if (!worldArea->isValidCoordinate(xCoord, yCoord))
            {
                continue;
            }

            auto tile{worldArea->getTile(xCoord, yCoord)};

            if (!tile)
            {
                continue;
            }

            if (tileJson.contains("elevation"))
            {
                auto elevation{tileJson["elevation"].get<float>()};
                tile->setElevation(elevation);
            }

            if (tileJson.contains("ground"))
            {
                auto groundHash{hash(tileJson["ground"].get<std::string>())};
                tile->setGround(groundHash);
            }

            GameSaving::loadTileObjects(tile, tileJson);

            if (tileJson.contains("entity"))
            {
                auto entityType{hash(tileJson["entity"]["type"].get<std::string>())};

                auto entity{std::make_shared<Entity>(entityType)};

                tile->setEntity(entity);

                entities.insert({entity, {xCoord, yCoord}});
            }
        }
    }

    auto GameSaving::loadTileObjects(const std::shared_ptr<Tile> &tile,
                                     const nlohmann::json &tileJson) -> void
    {
        if (tileJson.contains("objects") && tileJson["objects"].is_array())
        {
            auto objectsStack{tile->getObjectsStack()};
            if (objectsStack)
            {
                objectsStack->clearObjects();

                for (const auto &objectJson : tileJson["objects"])
                {
                    if (objectJson.contains("type"))
                    {
                        auto objectType{objectJson["type"].get<std::string>()};

                        objectsStack->addObject(objectType);
                    }
                }
            }
        }
    }
}
