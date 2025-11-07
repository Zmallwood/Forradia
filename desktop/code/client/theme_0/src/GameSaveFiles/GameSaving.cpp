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

#include "HashCodes.hpp"

#include <array>
#include <utility>

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

                auto groundHash{tile->GetGround()};

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
                auto origin{robot->GetOrigin()};
                robotJson["origin"]["x"] = origin.x;
                robotJson["origin"]["y"] = origin.y;
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

        worldArea->Reset();

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
                                // create the
                                // appropriate object
                                // type
                                if (objectType ==
                                    Hash("ObjectFirTre"
                                         "e"))
                                {
                                    objectsStack->AddObject<
                                        TreeObject>(
                                        "ObjectFirT"
                                        "ree");
                                }
                                else if (objectType ==
                                         Hash("ObjectBi"
                                              "rchT"
                                              "ree"))
                                {
                                    objectsStack->AddObject<
                                        TreeObject>(
                                        "ObjectBirc"
                                        "hTree");
                                }
                                else
                                {
                                    // Regular Object
                                    // type
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

        // Load robots from WorldArea
        if (jsonData.contains("robots") &&
            jsonData["robots"].is_array())
        {
            auto &robots{worldArea->GetRobotsMirrorRef()};

            for (const auto &robotJson : jsonData["robots"])
            {
                if (!robotJson.contains("type") ||
                    !robotJson.contains("position") ||
                    !robotJson.contains("origin"))
                {
                    continue;
                }

                auto robotType{
                    robotJson["type"].get<uint64_t>()};

                if (!robotJson["position"].contains("x") ||
                    !robotJson["position"].contains("y"))
                {
                    continue;
                }

                auto positionX{
                    robotJson["position"]["x"].get<int>()};
                auto positionY{
                    robotJson["position"]["y"].get<int>()};

                if (!worldArea->IsValidCoordinate(
                        positionX, positionY))
                {
                    continue;
                }

                if (!robotJson["origin"].contains("x") ||
                    !robotJson["origin"].contains("y"))
                {
                    continue;
                }

                auto originX{
                    robotJson["origin"]["x"].get<int>()};
                auto originY{
                    robotJson["origin"]["y"].get<int>()};

                auto tile{worldArea->GetTile(positionX,
                                             positionY)};

                if (!tile || tile->GetRobot())
                {
                    continue;
                }

                // Create robot with type hash and
                // origin
                auto newRobot{std::make_shared<Robot>(
                    static_cast<int>(robotType), originX,
                    originY)};

                // Set robot on tile
                tile->SetRobot(newRobot);

                // Insert robot into robotsMirror
                robots.insert(
                    {newRobot, {positionX, positionY}});
            }
        }
    }
}