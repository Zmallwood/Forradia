//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include <filesystem>
#include <fstream>
#include <string>

namespace Forradia::Theme0
{
    class WorldArea;

    class GameSaving
    {
      public:
        void SaveGame();

        void SaveWorldAreaToJSON(WorldArea *worldArea,
                                  const std::string &filename);

        void LoadWorldAreaFromJSON(WorldArea *worldArea,
                                   const std::string &filename);

      private:
        void WriteWorldAreaToJSON(WorldArea *worldArea,
                                   std::ofstream &out);

        void WriteTileToJSON(int x, int y, WorldArea *worldArea,
                             std::ofstream &out, bool &isFirst);

        void WriteObjectToJSON(void *object, std::ofstream &out,
                               bool &isFirst);

        void WriteRobotToJSON(void *robot, std::ofstream &out);

        void WriteCreatureToJSON(void *creature, std::ofstream &out);

        void EscapeJSONString(const std::string &str,
                              std::ofstream &out);
    };
}