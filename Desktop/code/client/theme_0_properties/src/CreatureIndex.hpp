//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "CreatureIndexEntry.hpp"

namespace Forradia::Theme0
{
    class CreatureIndex
    {
      public:
        CreatureIndex();

        float GetModelScaling(int creatureHash) const;

        float GetLevitationHeight(int creatureHash) const;

        bool CreatureEntryExists(int creatureHash) const;

      private:
        std::map<int, CreatureIndexEntry> m_entries;
    };
}