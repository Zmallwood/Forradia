//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#pragma once

#include "Quest.hpp"

namespace Forradia::Theme0::GameplayCore
{
    class MoveQuest : public Quest
    {
      public:
        MoveQuest()
        {
            this->name = "Movement";
            this->description = "Try to walk somewhere, 3 times.";
        }

        void Update() override;

        String GetStatus() const override;

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

        void Update() override;

        String GetStatus() const override;

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

        void Update() override;

        String GetStatus() const override;

      private:
        bool m_numBranchPicked{false};

        bool m_numStonePicked{false};
    };

    class MineStoneFromBoulderQuest1 : public Quest
    {
      public:
        MineStoneFromBoulderQuest1()
        {
            this->name = "Mine Stone";
            this->description = "Mine 10 stones from a boulder.";
        }

        void Update() override;

        String GetStatus() const override;

      private:
        int m_numMinedStonesLeft{10};
    };

    class CraftStoneSlabsQuest : public Quest
    {
      public:
        CraftStoneSlabsQuest()
        {
            this->name = "Craft Stone Slabs";
            this->description = "Craft 10 stone slabs.";
        }

        void Update() override;

        String GetStatus() const override;

      private:
        int m_numCraftedSlabsLeft{10};
    };

    class LayStoneSlabsQuest : public Quest
    {
      public:
        LayStoneSlabsQuest()
        {
            this->name = "Lay Stone Slabs";
            this->description = "Lay 10 stone slabs.";
        }

        void Update() override;

        String GetStatus() const override;

      private:
        int m_numLaidSlabsLeft{10};
    };

    class MineStoneFromBoulderQuest2 : public Quest
    {
      public:
        MineStoneFromBoulderQuest2()
        {
            this->name = "Mine Stone";
            this->description = "Mine 10 stones from a boulder.";
        }

        void Update() override;

        String GetStatus() const override;

      private:
        int m_numMinedStonesLeft{10};
    };

    class CraftStoneBricksQuest : public Quest
    {
      public:
        CraftStoneBricksQuest()
        {
            this->name = "Craft Stone Bricks";
            this->description = "Craft 10 stone bricks.";
        }

        void Update() override;

        String GetStatus() const override;

      private:
        int m_numCraftedBricksLeft{10};
    };
}