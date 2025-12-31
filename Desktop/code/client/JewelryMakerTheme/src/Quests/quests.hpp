/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include <set>
#include "ForradiaEngine/Common/Matter/Geometry.hpp"
#include "Quest.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    /**
     *  A quest to move the player somewhere.
     */
    class MoveQuest : public Quest
    {
      public:
        /**
         *  Constructs the quest.
         */
        MoveQuest()
        {
            this->name = "Movement";
            this->description = "Try to walk somewhere, 3 times.";
        }

        /**
         *  Updates the quest.
         */
        auto update() -> void override;

        /**
         *  Gets the status of the quest.
         *
         *  @return The status of the quest.
         */
        [[nodiscard]] auto getStatus() const -> std::string override;

      private:
        int m_numStepsLeft{10};
    };

    /**
     *  A quest to forage for resources.
     */
    class ForageQuest : public Quest
    {
      public:
        /**
         *  Constructs the quest.
         */
        ForageQuest()
        {
            this->name = "Forage";
            this->description = "Try to gather some resources, 3 times.";
        }

        /**
         *  Updates the quest.
         */
        auto update() -> void override;

        /**
         *  Gets the status of the quest.
         *
         *  @return The status of the quest.
         */
        [[nodiscard]] auto getStatus() const -> std::string override;

      private:
        int m_numForagingsLeft{3};
    };

    /**
     *  A quest to craft a stone pickaxe.
     */
    class CraftStonePickaxeQuest : public Quest
    {
      public:
        /**
         *  Constructs the quest.
         */
        CraftStonePickaxeQuest()
        {
            this->name = "First Crafting: Stone Pickaxe";
            this->description = "Craft a stone pickaxe.";
        }

        /**
         *  Updates the quest.
         */
        auto update() -> void override;

        /**
         *  Gets the status of the quest.
         *
         *  @return The status of the quest.
         */
        [[nodiscard]] auto getStatus() const -> std::string override;

      private:
        bool m_numBranchPicked{false};
        bool m_numStonePicked{false};
    };

    /**
     *  A quest to craft a stone bowl.
     */
    class CraftStoneBowlQuest : public Quest
    {
      public:
        /**
         *  Constructs the quest.
         */
        CraftStoneBowlQuest()
        {
            this->name = "Craft Stone Bowl";
            this->description = "Craft a stone bowl.";
        }

        /**
         *  Updates the quest.
         */
        auto update() -> void override;

        /**
         *  Gets the status of the quest.
         *
         *  @return The status of the quest.
         */
        [[nodiscard]] auto getStatus() const -> std::string override;

      private:
        bool m_stonedMined{false};
    };

    class PutForagedItemsInStoneBowlQuest : public Quest
    {
      public:
        /**
         *  Constructs the quest.
         */
        PutForagedItemsInStoneBowlQuest()
        {
            this->name = "Put Foraged Items in Stone Bowl";
            this->description = "Put foraged items in a stone bowl.";
        }

        /**
         *  Updates the quest.
         */
        auto update() -> void override;

        /**
         *  Gets the status of the quest.
         *
         *  @return The status of the quest.
         */
        [[nodiscard]] auto getStatus() const -> std::string override;
    };

    /**
     *  A quest to craft a campfire.
     */
    class CraftCampfireQuest : public Quest
    {
      public:
        /**
         *  Constructs the quest.
         */
        CraftCampfireQuest()
        {
            this->name = "Craft Campfire";
            this->description = "Craft a campfire.";
        }

        /**
         *  Updates the quest.
         */
        auto update() -> void override;

        /**
         *  Gets the status of the quest.
         *
         *  @return The status of the quest.
         */
        [[nodiscard]] auto getStatus() const -> std::string override;

      private:
        constexpr static int k_numBranchesNeeded{8};
        int m_numBranchesLeft{k_numBranchesNeeded};
    };

    /**
     *  A quest to mine stones from a boulder.
     */
    class MineStoneFromBoulderQuest1 : public Quest
    {
      public:
        /**
         *  Constructs the quest.
         */
        MineStoneFromBoulderQuest1()
        {
            this->name = "Mine Stone";
            this->description = "Mine 10 stones from a boulder.";
        }

        /**
         *  Updates the quest.
         */
        auto update() -> void override;

        /**
         *  Gets the status of the quest.
         *
         *  @return The status of the quest.
         */
        [[nodiscard]] auto getStatus() const -> std::string override;

      private:
        constexpr static int k_numStonesNeeded{10};
        int m_numMinedStonesLeft{k_numStonesNeeded};
    };

    /**
     *  A quest to craft stone slabs.
     */
    class CraftStoneSlabsQuest : public Quest
    {
      public:
        /**
         *  Constructs the quest.
         */
        CraftStoneSlabsQuest()
        {
            this->name = "Craft Stone Slabs";
            this->description = "Craft 10 stone slabs.";
        }

        /**
         *  Updates the quest.
         */
        auto update() -> void override;

        /**
         *  Gets the status of the quest.
         *
         *  @return The status of the quest.
         */
        [[nodiscard]] auto getStatus() const -> std::string override;

      private:
        constexpr static int k_numSlabsNeeded{10};
        int m_numCraftedSlabsLeft{k_numSlabsNeeded};
    };

    /**
     *  A quest to lay stone slabs.
     */
    class LayStoneSlabsQuest : public Quest
    {
      public:
        /**
         *  Constructs the quest.
         */
        LayStoneSlabsQuest()
        {
            this->name = "Lay Stone Slabs";
            this->description = "Lay 10 stone slabs.";
        }

        /**
         *  Updates the quest.
         */
        auto update() -> void override;

        /**
         *  Gets the status of the quest.
         *
         *  @return The status of the quest.
         */
        [[nodiscard]] auto getStatus() const -> std::string override;

      private:
        constexpr static int k_numSlabsPlacedNeeded{10};
        int m_numLaidSlabsLeft{k_numSlabsPlacedNeeded};
    };

    /**
     *  A quest to mine stones from a boulder.
     */
    class MineStoneFromBoulderQuest2 : public Quest
    {
      public:
        /**
         *  Constructs the quest.
         */
        MineStoneFromBoulderQuest2()
        {
            this->name = "Mine Stone";
            this->description = "Mine 10 stones from a boulder.";
        }

        /**
         *  Updates the quest.
         */
        auto update() -> void override;

        /**
         *  Gets the status of the quest.
         *
         *  @return The status of the quest.
         */
        [[nodiscard]] auto getStatus() const -> std::string override;

      private:
        constexpr static int k_numMinedStonesNeeded{10};
        int m_numMinedStonesLeft{k_numMinedStonesNeeded};
    };

    /**
     *  A quest to craft stone bricks.
     */
    class CraftStoneBricksQuest : public Quest
    {
      public:
        /**
         *  Constructs the quest.
         */
        CraftStoneBricksQuest()
        {
            this->name = "Craft Stone Bricks";
            this->description = "Craft 10 stone bricks.";
        }

        /**
         *  Updates the quest.
         */
        auto update() -> void override;

        /**
         *  Gets the status of the quest.
         *
         *  @return The status of the quest.
         */
        [[nodiscard]] auto getStatus() const -> std::string override;

      private:
        constexpr static int k_numCraftedBricksNeeded{10};
        int m_numCraftedBricksLeft{k_numCraftedBricksNeeded};
    };

    /**
     *  A quest to build stone walls.
     */
    class BuildStoneWallsQuest : public Quest
    {
      public:
        /**
         *  Constructs the quest.
         */
        BuildStoneWallsQuest()
        {
            this->name = "Build Stone Wall";
            this->description = "Build stone walls (and a door) around the stone slabs floor.";
        }

        /**
         *  Updates the quest.
         */
        auto update() -> void override;

        /**
         *  Gets the status of the quest.
         *
         *  @return The status of the quest.
         */
        [[nodiscard]] auto getStatus() const -> std::string override;

      private:
        static auto getNumIncompleteWallTiles(const std::set<Point> &wallPositions) -> int;
    };

    // TODO: Think about if this should be kept or not.
    // class PlaceSpouseQuest : public Quest
    // {
    //   public:
    //     PlaceSpouseQuest()
    //     {
    //         this->name = "Place Spouse";
    //         this->description = "Invite your spouse to the house.";
    //     }

    //     auto update() -> void override;

    //     [[nodiscard]] auto getStatus() const -> std::string override;
    // };
}
