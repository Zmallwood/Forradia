/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include <memory>
#include <unordered_map>

namespace ForradiaEngine::JewelryMakerTheme
{
    class WorldArea;

    /**
     *  The world in the game.
     */
    class World
    {
      public:
        static auto instance() -> World &
        {
            static World instance;
            return instance;
        }

        World(const World &) = delete;

        auto operator=(const World &) -> World & = delete;

        World() = default;

        /**
         *  Initializes the world.
         *
         *  @param worldAreaSize The size of the world area.
         *  @param worldScaling The scaling of the world.
         */
        auto initialize(Size worldAreaSize, float worldScaling) -> void;

        /**
         *  Gets the current world area.
         *
         *  @return The current world area.
         */
        [[nodiscard]] auto getWorldArea(Point3 coordinate) -> std::shared_ptr<WorldArea>;

      private:
        std::unordered_map<
            int, std::unordered_map<int, std::unordered_map<int, std::shared_ptr<WorldArea>>>>
            m_worldAreas{};
    };
}
