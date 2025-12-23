/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GameSaving.hpp"
#include "Entity.hpp"
#include "GroundRenderer.hpp"
#include "HashCodes.hpp"
#include "Object.hpp"
#include "ObjectsStack.hpp"
#include "Tile.hpp"
#include "World.hpp"
#include "WorldArea.hpp"
#include <fstream>
#include <string>

namespace Forradia::Theme0
{
    auto GameSaving::SaveGame() -> void
    {
        auto worldArea{World::Instance().GetCurrentWorldArea()};

        if (!worldArea)
        {
            return;
        }

        nlohmann::json jsonData;

        // Get world area size
        auto worldAreaSize{worldArea->GetSize()};

        jsonData["size"]["width"] = worldAreaSize.width;
        jsonData["size"]["height"] = worldAreaSize.height;

        // Serialize tiles
        jsonData["tiles"] = nlohmann::json::array();

        for (auto yCoord = 0; yCoord < worldAreaSize.height; yCoord++)
        {
            for (auto xCoord = 0; xCoord < worldAreaSize.width; xCoord++)
            {
                auto tile{worldArea->GetTile(xCoord, yCoord)};

                if (!tile)
                {
                    continue;
                }

                nlohmann::json tileJson;

                tileJson["x"] = xCoord;
                tileJson["y"] = yCoord;
                tileJson["elevation"] = tile->GetElevation();
                tileJson["ground"] = GetNameFromAnyHash(tile->GetGround());

                // Serialize objects on this tile
                auto objectsStack{tile->GetObjectsStack()};

                if (objectsStack)
                {
                    auto objects{objectsStack->GetObjects()};
                    tileJson["objects"] = nlohmann::json::array();

                    for (auto &object : objects)
                    {
                        if (object)
                        {
                            nlohmann::json objectJson;

                            objectJson["type"] = GetNameFromAnyHash(object->GetType());
                            tileJson["objects"].push_back(objectJson);
                        }
                    }
                }

                // Serialize entity on this tile
                auto entity{tile->GetEntity()};

                if (entity)
                {
                    nlohmann::json entityJson;

                    entityJson["type"] = GetNameFromAnyHash(entity->GetType());
                    tileJson["entity"] = entityJson;
                }

                jsonData["tiles"].push_back(tileJson);
            }
        }

        // Write to file
        std::ofstream file("savegame.json");

        if (file.is_open())
        {
            file << jsonData.dump(4); // Pretty print with 4-space indent
            file.close();
        }
    }

    auto GameSaving::LoadGame() -> void
    {
        GroundRenderer::Instance().Reset();

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

        auto worldArea{World::Instance().GetCurrentWorldArea()};

        if (!worldArea)
        {
            return;
        }

        worldArea->Reset();

        GameSaving::LoadTiles(worldArea, jsonData);
    }

    auto GameSaving::LoadTiles(const std::shared_ptr<WorldArea> &worldArea,
                               const nlohmann::json &jsonData) -> void
    {
        auto &entities{worldArea->GetEntitiesMirrorRef()};

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

            if (!worldArea->IsValidCoordinate(xCoord, yCoord))
            {
                continue;
            }

            auto tile{worldArea->GetTile(xCoord, yCoord)};

            if (!tile)
            {
                continue;
            }

            if (tileJson.contains("elevation"))
            {
                auto elevation{tileJson["elevation"].get<float>()};
                tile->SetElevation(elevation);
            }

            if (tileJson.contains("ground"))
            {
                auto groundHash{Hash(tileJson["ground"].get<std::string>())};
                tile->SetGround(groundHash);
            }

            GameSaving::LoadTileObjects(tile, tileJson);

            if (tileJson.contains("entity"))
            {
                auto entityType{Hash(tileJson["entity"]["type"].get<std::string>())};

                auto entity{std::make_shared<Entity>(entityType)};

                tile->SetEntity(entity);

                entities.insert({entity, {xCoord, yCoord}});
            }
        }
    }

    auto GameSaving::LoadTileObjects(const std::shared_ptr<Tile> &tile,
                                     const nlohmann::json &tileJson) -> void
    {
        if (tileJson.contains("objects") && tileJson["objects"].is_array())
        {
            auto objectsStack{tile->GetObjectsStack()};
            if (objectsStack)
            {
                objectsStack->ClearObjects();

                for (const auto &objectJson : tileJson["objects"])
                {
                    if (objectJson.contains("type"))
                    {
                        auto objectType{objectJson["type"].get<std::string>()};

                        objectsStack->AddObject(objectType);
                    }
                }
            }
        }
    }
}
