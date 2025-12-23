/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "Geometry/Point.hpp"
#include "Quest.hpp"
#include <set>

namespace Forradia::Theme0
{
    class MoveQuest : public Quest
    {
      public:
        MoveQuest()
        {
            this->name = "Movement";
            this->description = "Try to walk somewhere, 3 times.";
        }

        auto Update() -> void override;

        [[nodiscard]] auto GetStatus() const -> std::string override;

      private:
        int m_numStepsLeft{3};
    };

    class ForageQuest : public Quest
    {
      public:
        ForageQuest()
        {
            this->name = "Forage";
            this->description = "Try to gather some resources, 3 times.";
        }

        auto Update() -> void override;

        [[nodiscard]] auto GetStatus() const -> std::string override;

      private:
        int m_numForagingsLeft{3};
    };

    class CraftStonePickaxeQuest : public Quest
    {
      public:
        CraftStonePickaxeQuest()
        {
            this->name = "First Crafting: Stone Pickaxe";
            this->description = "Craft a stone pickaxe.";
        }

        auto Update() -> void override;

        [[nodiscard]] auto GetStatus() const -> std::string override;

      private:
        bool m_numBranchPicked{false};
        bool m_numStonePicked{false};
    };

    class CraftStoneBowlQuest : public Quest
    {
      public:
        CraftStoneBowlQuest()
        {
            this->name = "Craft Stone Bowl";
            this->description = "Craft a stone bowl.";
        }

        auto Update() -> void override;

        [[nodiscard]] auto GetStatus() const -> std::string override;

      private:
        bool m_stonedMined{false};
    };

    class CraftCampfireQuest : public Quest
    {
      public:
        CraftCampfireQuest()
        {
            this->name = "Craft Campfire";
            this->description = "Craft a campfire.";
        }

        auto Update() -> void override;

        [[nodiscard]] auto GetStatus() const -> std::string override;

      private:
        constexpr static int k_numBranchesNeeded{8};
        int m_numBranchesLeft{k_numBranchesNeeded};
    };

    class MineStoneFromBoulderQuest1 : public Quest
    {
      public:
        MineStoneFromBoulderQuest1()
        {
            this->name = "Mine Stone";
            this->description = "Mine 10 stones from a boulder.";
        }

        auto Update() -> void override;

        [[nodiscard]] auto GetStatus() const -> std::string override;

      private:
        constexpr static int k_numStonesNeeded{10};
        int m_numMinedStonesLeft{k_numStonesNeeded};
    };

    class CraftStoneSlabsQuest : public Quest
    {
      public:
        CraftStoneSlabsQuest()
        {
            this->name = "Craft Stone Slabs";
            this->description = "Craft 10 stone slabs.";
        }

        auto Update() -> void override;

        [[nodiscard]] auto GetStatus() const -> std::string override;

      private:
        constexpr static int k_numSlabsNeeded{10};
        int m_numCraftedSlabsLeft{k_numSlabsNeeded};
    };

    class LayStoneSlabsQuest : public Quest
    {
      public:
        LayStoneSlabsQuest()
        {
            this->name = "Lay Stone Slabs";
            this->description = "Lay 10 stone slabs.";
        }

        auto Update() -> void override;

        [[nodiscard]] auto GetStatus() const -> std::string override;

      private:
        constexpr static int k_numSlabsPlacedNeeded{10};
        int m_numLaidSlabsLeft{k_numSlabsPlacedNeeded};
    };

    class MineStoneFromBoulderQuest2 : public Quest
    {
      public:
        MineStoneFromBoulderQuest2()
        {
            this->name = "Mine Stone";
            this->description = "Mine 10 stones from a boulder.";
        }

        auto Update() -> void override;

        [[nodiscard]] auto GetStatus() const -> std::string override;

      private:
        constexpr static int k_numMinedStonesNeeded{10};
        int m_numMinedStonesLeft{k_numMinedStonesNeeded};
    };

    class CraftStoneBricksQuest : public Quest
    {
      public:
        CraftStoneBricksQuest()
        {
            this->name = "Craft Stone Bricks";
            this->description = "Craft 10 stone bricks.";
        }

        auto Update() -> void override;

        [[nodiscard]] auto GetStatus() const -> std::string override;

      private:
        constexpr static int k_numCraftedBricksNeeded{10};
        int m_numCraftedBricksLeft{k_numCraftedBricksNeeded};
    };

    class BuildStoneWallsQuest : public Quest
    {
      public:
        BuildStoneWallsQuest()
        {
            this->name = "Build Stone Wall";
            this->description = "Build stone walls (and a door) around the stone slabs floor.";
        }

        auto Update() -> void override;

        [[nodiscard]] auto GetStatus() const -> std::string override;

      private:
        static auto GetNumIncompleteWallTiles(const std::set<Point> &wallPositions) -> int;
    };
}
