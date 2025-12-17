/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "GameSaving.hpp"
#include "Creature.hpp"
#include "GroundRenderer.hpp"
#include "HashCodes.hpp"
#include "Object.hpp"
#include "ObjectsStack.hpp"
#include "Robot.hpp"
#include "Tile.hpp"
#include "World.hpp"
#include "WorldArea.hpp"

namespace Forradia::Theme0 {
auto GameSaving::SaveGame() -> void {
  auto worldArea{_<World>().GetCurrentWorldArea()};

  if (!worldArea)
    return;

  nlohmann::json jsonData;

  // Get world area size
  auto worldAreaSize{worldArea->GetSize()};
  jsonData["size"]["width"] = worldAreaSize.width;
  jsonData["size"]["height"] = worldAreaSize.height;

  // Serialize tiles
  jsonData["tiles"] = nlohmann::json::array();

  for (auto y = 0; y < worldAreaSize.height; y++) {
    for (auto x = 0; x < worldAreaSize.width; x++) {
      auto tile{worldArea->GetTile(x, y)};

      if (!tile)
        continue;

      nlohmann::json tileJson;
      tileJson["x"] = x;
      tileJson["y"] = y;
      tileJson["elevation"] = tile->GetElevation();
      tileJson["ground"] = GetNameFromAnyHash(tile->GetGround());

      // Serialize objects on this tile
      auto objectsStack{tile->GetObjectsStack()};
      if (objectsStack) {
        auto objects{objectsStack->GetObjects()};
        tileJson["objects"] = nlohmann::json::array();

        for (auto &object : objects) {
          if (object) {
            nlohmann::json objectJson;
            objectJson["type"] = GetNameFromAnyHash(object->GetType());
            tileJson["objects"].push_back(objectJson);
          }
        }
      }

      // Serialize creature on this tile
      auto creature{tile->GetCreature()};
      if (creature) {
        nlohmann::json creatureJson;
        creatureJson["type"] = GetNameFromAnyHash(creature->GetType());
        tileJson["creature"] = creatureJson;
      }

      // Serialize robot on this tile
      auto robot{tile->GetRobot()};
      if (robot) {
        nlohmann::json robotJson;
        robotJson["type"] = GetNameFromAnyHash(robot->GetType());
        robotJson["position"]["x"] = x;
        robotJson["position"]["y"] = y;
        auto origin{robot->GetOrigin()};
        robotJson["origin"]["x"] = origin.x;
        robotJson["origin"]["y"] = origin.y;
        tileJson["robot"] = robotJson;
      }

      jsonData["tiles"].push_back(tileJson);
    }
  }

  // Write to file
  std::ofstream file("savegame.json");
  if (file.is_open()) {
    file << jsonData.dump(4); // Pretty print with 4-space indent
    file.close();
  }
}

auto GameSaving::LoadGame() -> void {
  _<GroundRenderer>().Reset();

  std::ifstream file("savegame.json");
  if (!file.is_open())
    return;

  nlohmann::json jsonData;
  try {
    file >> jsonData;
    file.close();
  } catch (const std::exception &) {
    return;
  }

  auto worldArea{_<World>().GetCurrentWorldArea()};

  if (!worldArea)
    return;

  worldArea->Reset();

  auto &robots{worldArea->GetRobotsMirrorRef()};
  auto &creatures{worldArea->GetCreaturesMirrorRef()};

  if (jsonData.contains("size")) {
    auto savedWidth{jsonData["size"]["width"].get<int>()};
    auto savedHeight{jsonData["size"]["height"].get<int>()};
    auto currentSize{worldArea->GetSize()};
  }

  if (jsonData.contains("tiles") && jsonData["tiles"].is_array()) {
    for (const auto &tileJson : jsonData["tiles"]) {
      if (!tileJson.contains("x") || !tileJson.contains("y"))
        continue;

      auto x{tileJson["x"].get<int>()};
      auto y{tileJson["y"].get<int>()};

      if (!worldArea->IsValidCoordinate(x, y))
        continue;

      auto tile{worldArea->GetTile(x, y)};

      if (!tile)
        continue;

      if (tileJson.contains("elevation")) {
        auto elevation{tileJson["elevation"].get<float>()};
        tile->SetElevation(elevation);
      }

      if (tileJson.contains("ground")) {
        auto groundHash{Hash(tileJson["ground"].get<String>())};
        tile->SetGround(groundHash);
      }

      if (tileJson.contains("objects") && tileJson["objects"].is_array()) {
        auto objectsStack{tile->GetObjectsStack()};
        if (objectsStack) {
          objectsStack->ClearObjects();

          for (const auto &objectJson : tileJson["objects"]) {
            if (objectJson.contains("type")) {
              auto objectType{objectJson["type"].get<String>()};

              objectsStack->AddObject(objectType);
            }
          }
        }
      }

      if (tileJson.contains("creature")) {
        auto creatureType{Hash(tileJson["creature"]["type"].get<String>())};

        auto creature{std::make_shared<Creature>(creatureType)};

        tile->SetCreature(creature);

        creatures.insert({creature, {x, y}});
      }

      if (tileJson.contains("robot")) {
        auto robotType{Hash(tileJson["robot"]["type"].get<String>())};

        auto originX{tileJson["robot"]["origin"]["x"].get<int>()};
        auto originY{tileJson["robot"]["origin"]["y"].get<int>()};

        auto robot{std::make_shared<Robot>(robotType, originX, originY)};

        tile->SetRobot(robot);

        robots.insert({robot, {x, y}});
      }
    }
  }
}
}
