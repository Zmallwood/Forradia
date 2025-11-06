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

#include "Robot.hpp"

#include "Creature.hpp"

#include <sstream>
#include <iomanip>

namespace Forradia::Theme0
{
    void GameSaving::SaveGame()
    {
        if (!std::filesystem::is_directory("SavedGames") ||
            !std::filesystem::exists("SavedGames"))
        {
            std::filesystem::create_directory("SavedGames");
        }
    }

    void GameSaving::SaveWorldAreaToJSON(WorldArea *worldArea,
                                         const std::string &filename)
    {
        if (!worldArea)
        {
            return;
        }

        std::string fullPath = "SavedGames/" + filename;
        if (!filename.empty() && filename[0] == '/')
        {
            fullPath = filename;
        }

        std::ofstream out(fullPath);
        if (!out.is_open())
        {
            return;
        }

        WriteWorldAreaToJSON(worldArea, out);
        out.close();
    }

    void GameSaving::LoadWorldAreaFromJSON(WorldArea *worldArea,
                                           const std::string &filename)
    {
        // TODO: Implement JSON loading if needed
        // For now, this is a placeholder
        (void)worldArea;
        (void)filename;
    }

    void GameSaving::WriteWorldAreaToJSON(WorldArea *worldArea,
                                          std::ofstream &out)
    {
        auto size = worldArea->GetSize();

        out << "{\n";
        out << "  \"version\": 1,\n";
        out << "  \"width\": " << size.width << ",\n";
        out << "  \"height\": " << size.height << ",\n";
        out << "  \"tiles\": [\n";

        bool isFirstTile = true;
        for (int y = 0; y < size.height; y++)
        {
            for (int x = 0; x < size.width; x++)
            {
                WriteTileToJSON(x, y, worldArea, out, isFirstTile);
            }
        }

        out << "\n  ],\n";

        // Write robots
        out << "  \"robots\": [\n";
        auto &robots = worldArea->GetRobotsMirrorRef();
        bool isFirstRobot = true;
        for (const auto &[robot, position] : robots)
        {
            if (!isFirstRobot)
            {
                out << ",\n";
            }
            isFirstRobot = false;

            out << "    {\n";
            out << "      \"position\": {\"x\": " << position.x
                << ", \"y\": " << position.y << "},\n";
            WriteRobotToJSON(robot, out);
            out << "\n    }";
        }
        out << "\n  ],\n";

        // Write creatures
        out << "  \"creatures\": [\n";
        auto &creatures = worldArea->GetCreaturesMirrorRef();
        bool isFirstCreature = true;
        for (const auto &[creature, position] : creatures)
        {
            if (!isFirstCreature)
            {
                out << ",\n";
            }
            isFirstCreature = false;

            out << "    {\n";
            out << "      \"position\": {\"x\": " << position.x
                << ", \"y\": " << position.y << "},\n";
            WriteCreatureToJSON(creature, out);
            out << "\n    }";
        }
        out << "\n  ]\n";

        out << "}\n";
    }

    void GameSaving::WriteTileToJSON(int x, int y, WorldArea *worldArea,
                                      std::ofstream &out, bool &isFirst)
    {
        if (!isFirst)
        {
            out << ",\n";
        }
        isFirst = false;

        auto tile = worldArea->GetTile(x, y);
        if (!tile)
        {
            out << "    null";
            return;
        }

        out << "    {\n";
        out << "      \"x\": " << x << ",\n";
        out << "      \"y\": " << y << ",\n";
        out << "      \"elevation\": " << std::fixed
            << std::setprecision(6) << tile->GetElevation() << ",\n";
        out << "      \"ground\": " << tile->GetGround() << ",\n";

        // Write objects
        auto objectsStack = tile->GetObjectsStack();
        if (objectsStack)
        {
            auto objects = objectsStack->GetObjects();
            out << "      \"objects\": [\n";
            bool isFirstObject = true;
            for (auto &object : objects)
            {
                WriteObjectToJSON(object, out, isFirstObject);
            }
            out << "\n      ],\n";
        }
        else
        {
            out << "      \"objects\": [],\n";
        }

        // Write robot (if present on tile)
        auto robot = tile->GetRobot();
        if (robot)
        {
            out << "      \"robot\": ";
            WriteRobotToJSON(robot, out);
            out << ",\n";
        }
        else
        {
            out << "      \"robot\": null,\n";
        }

        // Write creature (if present on tile)
        auto creature = tile->GetCreature();
        if (creature)
        {
            out << "      \"creature\": ";
            WriteCreatureToJSON(creature, out);
            out << "\n";
        }
        else
        {
            out << "      \"creature\": null\n";
        }

        out << "    }";
    }

    void GameSaving::WriteObjectToJSON(void *object, std::ofstream &out,
                                       bool &isFirst)
    {
        if (!object)
        {
            return;
        }

        auto *obj = static_cast<Object *>(object);

        if (!isFirst)
        {
            out << ",\n";
        }
        isFirst = false;

        out << "        {\n";
        out << "          \"type\": " << obj->GetType() << "\n";
        out << "        }";
    }

    void GameSaving::WriteRobotToJSON(void *robot, std::ofstream &out)
    {
        if (!robot)
        {
            out << "null";
            return;
        }

        auto *r = static_cast<Robot *>(robot);

        out << "{\n";
        out << "        \"type\": " << r->GetType() << ",\n";
        auto destination = r->GetDestination();
        out << "        \"destination\": {\"x\": " << destination.x
            << ", \"y\": " << destination.y << "},\n";
        out << "        \"movementSpeed\": " << std::fixed
            << std::setprecision(6) << r->GetMovementSpeed() << ",\n";
        out << "        \"ticksLastMovement\": " << r->GetTicksLastMovement();
        out << "\n      }";
    }

    void GameSaving::WriteCreatureToJSON(void *creature,
                                         std::ofstream &out)
    {
        if (!creature)
        {
            out << "null";
            return;
        }

        auto *c = static_cast<Creature *>(creature);

        out << "{\n";
        out << "        \"type\": " << c->GetType() << ",\n";
        auto destination = c->GetDestination();
        out << "        \"destination\": {\"x\": " << destination.x
            << ", \"y\": " << destination.y << "},\n";
        out << "        \"movementSpeed\": " << std::fixed
            << std::setprecision(6) << c->GetMovementSpeed() << ",\n";
        out << "        \"ticksLastMovement\": " << c->GetTicksLastMovement();
        out << "\n      }";
    }

    void GameSaving::EscapeJSONString(const std::string &str,
                                      std::ofstream &out)
    {
        for (char c : str)
        {
            switch (c)
            {
            case '"':
                out << "\\\"";
                break;
            case '\\':
                out << "\\\\";
                break;
            case '\b':
                out << "\\b";
                break;
            case '\f':
                out << "\\f";
                break;
            case '\n':
                out << "\\n";
                break;
            case '\r':
                out << "\\r";
                break;
            case '\t':
                out << "\\t";
                break;
            default:
                if (static_cast<unsigned char>(c) < 0x20)
                {
                    out << "\\u" << std::hex << std::setw(4)
                        << std::setfill('0')
                        << static_cast<int>(static_cast<unsigned char>(c))
                        << std::dec;
                }
                else
                {
                    out << c;
                }
                break;
            }
        }
    }
}