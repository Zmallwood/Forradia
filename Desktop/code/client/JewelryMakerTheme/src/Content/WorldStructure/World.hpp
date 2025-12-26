/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include <memory>
    #include <unordered_map>
// clang-format on

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
        [[nodiscard]] auto getCurrentWorldArea() -> std::shared_ptr<WorldArea>;

      private:
        std::unordered_map<
            int, std::unordered_map<int, std::unordered_map<int, std::shared_ptr<WorldArea>>>>
            m_worldAreas{};
    };
}
