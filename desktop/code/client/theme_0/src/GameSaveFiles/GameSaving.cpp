//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "GameSaving.hpp"

#include "World.hpp"

#include "WorldArea.hpp"

#include "Tile.hpp"

#include "ObjectsStack.hpp"

#include "Object.hpp"

#include "TreeObject.hpp"

#include "Robot.hpp"

#include "Creature.hpp"

#include <fstream>

#include <nlohmann/json.hpp>

#include "GroundRenderer.hpp"

namespace Forradia::Theme0
{
    void GameSaving::SaveGame()
    {
        auto worldArea{_<World>().GetCurrentWorldArea()};

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

        for (auto y = 0; y < worldAreaSize.height; y++)
        {
            for (auto x = 0; x < worldAreaSize.width; x++)
            {
                auto tile{worldArea->GetTile(x, y)};

                if (!tile)
                {
                    continue;
                }

                nlohmann::json tileJson;
                tileJson["x"] = x;
                tileJson["y"] = y;
                tileJson["elevation"] =
                    tile->GetElevation();
                tileJson["ground"] = static_cast<uint64_t>(
                    tile->GetGround());

                // Serialize objects on this tile
                auto objectsStack{tile->GetObjectsStack()};
                if (objectsStack)
                {
                    auto objects{
                        objectsStack->GetObjects()};
                    tileJson["objects"] =
                        nlohmann::json::array();

                    for (auto &object : objects)
                    {
                        if (object)
                        {
                            nlohmann::json objectJson;
                            objectJson["type"] =
                                static_cast<uint64_t>(
                                    object->GetType());
                            tileJson["objects"].push_back(
                                objectJson);
                        }
                    }
                }

                // Serialize robot on this tile
                auto robot{tile->GetRobot()};
                if (robot)
                {
                    nlohmann::json robotJson;
                    robotJson["type"] =
                        static_cast<uint64_t>(
                            robot->GetType());
                    robotJson["position"]["x"] = x;
                    robotJson["position"]["y"] = y;
                    tileJson["robot"] = robotJson;
                }

                jsonData["tiles"].push_back(tileJson);
            }
        }

        // Serialize robots from WorldArea
        auto &robots{worldArea->GetRobotsMirrorRef()};
        jsonData["robots"] = nlohmann::json::array();

        for (auto &[robot, position] : robots)
        {
            if (robot)
            {
                nlohmann::json robotJson;
                robotJson["type"] =
                    static_cast<uint64_t>(robot->GetType());
                robotJson["position"]["x"] = position.x;
                robotJson["position"]["y"] = position.y;
                jsonData["robots"].push_back(robotJson);
            }
        }

        // Serialize creatures from WorldArea
        auto &creatures{worldArea->GetCreaturesMirrorRef()};
        jsonData["creatures"] = nlohmann::json::array();

        for (auto &[creature, position] : creatures)
        {
            if (creature)
            {
                nlohmann::json creatureJson;
                creatureJson["type"] =
                    static_cast<uint64_t>(
                        creature->GetType());
                creatureJson["position"]["x"] = position.x;
                creatureJson["position"]["y"] = position.y;
                jsonData["creatures"].push_back(
                    creatureJson);
            }
        }

        // Write to file
        std::ofstream file("savegame.json");
        if (file.is_open())
        {
            file << jsonData.dump(
                4); // Pretty print with 4-space indent
            file.close();
        }
    }

    void GameSaving::LoadGame()
    {
        _<GroundRenderer>().Reset();

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

        auto worldArea{_<World>().GetCurrentWorldArea()};

        if (!worldArea)
        {
            return;
        }

        if (jsonData.contains("size"))
        {
            auto savedWidth{
                jsonData["size"]["width"].get<int>()};
            auto savedHeight{
                jsonData["size"]["height"].get<int>()};
            auto currentSize{worldArea->GetSize()};
        }

        if (jsonData.contains("tiles") &&
            jsonData["tiles"].is_array())
        {
            for (const auto &tileJson : jsonData["tiles"])
            {
                if (!tileJson.contains("x") ||
                    !tileJson.contains("y"))
                {
                    continue;
                }

                auto x{tileJson["x"].get<int>()};
                auto y{tileJson["y"].get<int>()};

                if (!worldArea->IsValidCoordinate(x, y))
                {
                    continue;
                }

                auto tile{worldArea->GetTile(x, y)};

                if (!tile)
                {
                    continue;
                }

                if (tileJson.contains("elevation"))
                {
                    auto elevation{
                        tileJson["elevation"].get<float>()};
                    tile->SetElevation(elevation);
                }

                if (tileJson.contains("ground"))
                {
                    auto groundHash{
                        tileJson["ground"].get<uint64_t>()};
                    tile->SetGround(groundHash);
                }

                if (tileJson.contains("objects") &&
                    tileJson["objects"].is_array())
                {
                    auto objectsStack{
                        tile->GetObjectsStack()};
                    if (objectsStack)
                    {
                        objectsStack->ClearObjects();

                        for (const auto &objectJson :
                             tileJson["objects"])
                        {
                            if (objectJson.contains("type"))
                            {
                                auto objectType{
                                    objectJson["type"]
                                        .get<uint64_t>()};

                                // Check if this is a
                                // TreeObject type and
                                // create the appropriate
                                // object type
                                if (objectType ==
                                    Hash("ObjectFirTree"))
                                {
                                    objectsStack->AddObject<
                                        TreeObject>(
                                        "ObjectFirTree");
                                }
                                else if (objectType ==
                                         Hash("ObjectBirchT"
                                              "ree"))
                                {
                                    objectsStack->AddObject<
                                        TreeObject>(
                                        "ObjectBirchTree");
                                }
                                else
                                {
                                    // Regular Object type
                                    objectsStack->AddObject(
                                        static_cast<int>(
                                            objectType));
                                }
                            }
                        }
                    }
                }
            }
        }
        /*
                if (jsonData.contains("robots") &&
                    jsonData["robots"].is_array())
                {
                    auto
           &robots{worldArea->GetRobotsMirrorRef()};
                    robots.clear();

                    for (const auto &robotJson :
           jsonData["robots"])
                    {
                        if (robotJson.contains("type") &&
                            robotJson.contains("position"))
                        {
                            auto robotType{
                                robotJson["type"].get<uint64_t>()};
                            auto
           posX{robotJson["position"]["x"] .get<int>()};
                            auto
           posY{robotJson["position"]["y"] .get<int>()};

                            auto robot{
                                std::make_shared<Robot>(robotType)};

                            robots.insert({robot, {posX,
           posY}});

                            if
           (worldArea->IsValidCoordinate(posX, posY))
                            {
                                auto tile{
                                    worldArea->GetTile(posX,
           posY)}; if (tile)
                                {
                                    tile->SetRobot(robot);
                                }
                            }
                        }
                    }
                }

                if (jsonData.contains("creatures") &&
                    jsonData["creatures"].is_array())
                {
                    auto &creatures{
                        worldArea->GetCreaturesMirrorRef()};
                    creatures.clear();

                    for (const auto &creatureJson :
                         jsonData["creatures"])
                    {
                        if (creatureJson.contains("type") &&
                            creatureJson.contains("position"))
                        {
                            auto
           creatureType{creatureJson["type"]
                                                  .get<uint64_t>()};
                            auto
           posX{creatureJson["position"]["x"] .get<int>()};
                            auto
           posY{creatureJson["position"]["y"] .get<int>()};

                            auto creature{
                                std::make_shared<Creature>(
                                    creatureType)};

                            creatures.insert(
                                {creature, {posX, posY}});

                            if
           (worldArea->IsValidCoordinate(posX, posY))
                            {
                                auto tile{
                                    worldArea->GetTile(posX,
           posY)}; if (tile)
                                {
                                    tile->SetCreature(creature);
                                }
                            }
                        }
                    }
                }*/
    }
}