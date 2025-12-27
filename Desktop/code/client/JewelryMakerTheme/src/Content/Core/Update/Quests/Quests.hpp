/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include <set>
    
    #include "ForradiaEngine/Common/Matter/Geometry.hpp"
    #include "Quest.hpp"
// clang-format on

namespace ForradiaEngine::JewelryMakerTheme
{
    /* Move quest */ // clang-format off
        class MoveQuest : public Quest
        {
          public:
            MoveQuest()
            {
                this->name = "Movement";
                this->description = "Try to walk somewhere, 3 times.";
            }

            auto update() -> void override;

            [[nodiscard]] auto getStatus() const -> std::string override;

          private:
            int m_numStepsLeft{3};
        };
    // clang-format on

    /* Forage quest */ // clang-format off
        class ForageQuest : public Quest
        {
          public:
            ForageQuest()
            {
                this->name = "Forage";
                this->description = "Try to gather some resources, 3 times.";
            }

            auto update() -> void override;

            [[nodiscard]] auto getStatus() const -> std::string override;

          private:
            int m_numForagingsLeft{3};
        };
    // clang-format on

    /* Craft stone pickaxe quest */ // clang-format off
        class CraftStonePickaxeQuest : public Quest
        {
          public:
            CraftStonePickaxeQuest()
            {
                this->name = "First Crafting: Stone Pickaxe";
                this->description = "Craft a stone pickaxe.";
            }

            auto update() -> void override;

            [[nodiscard]] auto getStatus() const -> std::string override;

          private:
            bool m_numBranchPicked{false};
            bool m_numStonePicked{false};
        };
    // clang-format on

    /* Craft stone bowl quest */ // clang-format off
        class CraftStoneBowlQuest : public Quest
        {
          public:
            CraftStoneBowlQuest()
            {
                this->name = "Craft Stone Bowl";
                this->description = "Craft a stone bowl.";
            }

            auto update() -> void override;

            [[nodiscard]] auto getStatus() const -> std::string override;

          private:
            bool m_stonedMined{false};
        };
    // clang-format on

    /* Craft campfire quest */ // clang-format off
        class CraftCampfireQuest : public Quest
        {
          public:
            CraftCampfireQuest()
            {
                this->name = "Craft Campfire";
                this->description = "Craft a campfire.";
            }

            auto update() -> void override;

            [[nodiscard]] auto getStatus() const -> std::string override;

          private:
            constexpr static int k_numBranchesNeeded{8};
            int m_numBranchesLeft{k_numBranchesNeeded};
        };
    // clang-format on

    /* Mine stone from boulder quest 1 */ // clang-format off
        class MineStoneFromBoulderQuest1 : public Quest
        {
          public:
            MineStoneFromBoulderQuest1()
            {
                this->name = "Mine Stone";
                this->description = "Mine 10 stones from a boulder.";
            }

            auto update() -> void override;

            [[nodiscard]] auto getStatus() const -> std::string override;

          private:
            constexpr static int k_numStonesNeeded{10};
            int m_numMinedStonesLeft{k_numStonesNeeded};
        };
    // clang-format on

    /* Craft stone slabs quest */ // clang-format off
        class CraftStoneSlabsQuest : public Quest
        {
          public:
            CraftStoneSlabsQuest()
            {
                this->name = "Craft Stone Slabs";
                this->description = "Craft 10 stone slabs.";
            }

            auto update() -> void override;

            [[nodiscard]] auto getStatus() const -> std::string override;

          private:
            constexpr static int k_numSlabsNeeded{10};
            int m_numCraftedSlabsLeft{k_numSlabsNeeded};
        };
    // clang-format on

    /* Lay stone slabs quest */ // clang-format off
        class LayStoneSlabsQuest : public Quest
        {
          public:
            LayStoneSlabsQuest()
            {
                this->name = "Lay Stone Slabs";
                this->description = "Lay 10 stone slabs.";
            }

            auto update() -> void override;

            [[nodiscard]] auto getStatus() const -> std::string override;

          private:
            constexpr static int k_numSlabsPlacedNeeded{10};
            int m_numLaidSlabsLeft{k_numSlabsPlacedNeeded};
        };
    // clang-format on

    /* Mine stone from boulder quest 2 */ // clang-format off
        class MineStoneFromBoulderQuest2 : public Quest
        {
          public:
            MineStoneFromBoulderQuest2()
            {
                this->name = "Mine Stone";
                this->description = "Mine 10 stones from a boulder.";
            }

            auto update() -> void override;

            [[nodiscard]] auto getStatus() const -> std::string override;

          private:
            constexpr static int k_numMinedStonesNeeded{10};
            int m_numMinedStonesLeft{k_numMinedStonesNeeded};
        };
    // clang-format on

    /* Craft stone bricks quest */ // clang-format off
        class CraftStoneBricksQuest : public Quest
        {
          public:
            CraftStoneBricksQuest()
            {
                this->name = "Craft Stone Bricks";
                this->description = "Craft 10 stone bricks.";
            }

            auto update() -> void override;

            [[nodiscard]] auto getStatus() const -> std::string override;

          private:
            constexpr static int k_numCraftedBricksNeeded{10};
            int m_numCraftedBricksLeft{k_numCraftedBricksNeeded};
        };
    // clang-format on

    /* Build stone walls quest */ // clang-format off
        class BuildStoneWallsQuest : public Quest
        {
          public:
            BuildStoneWallsQuest()
            {
                this->name = "Build Stone Wall";
                this->description = "Build stone walls (and a door) around the stone slabs floor.";
            }

            auto update() -> void override;

            [[nodiscard]] auto getStatus() const -> std::string override;

          private:
            static auto getNumIncompleteWallTiles(const std::set<Point> &wallPositions) -> int;
        };
    // clang-format on

    /* Place spouse quest */ // clang-format off
        class PlaceSpouseQuest : public Quest
        {
          public:
            PlaceSpouseQuest()
            {
                this->name = "Place Spouse";
                this->description = "Invite your spouse to the house.";
            }

            auto update() -> void override;

            [[nodiscard]] auto getStatus() const -> std::string override;
        };
    // clang-format on
}
