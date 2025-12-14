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
}