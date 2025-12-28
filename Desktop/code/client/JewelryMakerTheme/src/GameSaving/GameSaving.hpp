/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include <memory>
#include <nlohmann/json.hpp>
#include "ForradiaEngine/Common/Matter/Geometry.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    class WorldArea;
    class Tile;

    /**
     *  Manages the saving and loading of the game.
     */
    class GameSaving
    {
      public:
        static auto instance() -> GameSaving &
        {
            static GameSaving instance;
            return instance;
        }

        GameSaving(const GameSaving &) = delete;

        auto operator=(const GameSaving &) -> GameSaving & = delete;

        GameSaving() = default;

        /**
         *  Saves the game to a file.
         */
        static auto saveGame() -> void;

        /**
         *  Loads the game from a file.
         */
        static auto loadGame() -> void;

      private:
        static auto saveTile(const std::shared_ptr<Tile> &tile, Point coordinate,
                             nlohmann::json &jsonData) -> void;

        static auto loadTiles(const std::shared_ptr<WorldArea> &worldArea,
                              const nlohmann::json &jsonData) -> void;

        static auto loadTileObjects(const std::shared_ptr<Tile> &tile,
                                    const nlohmann::json &tileJson) -> void;
    };
}
