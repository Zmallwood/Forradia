//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "CreatureIndex.hpp"

namespace Forradia::Theme0
{
    CreatureIndex::CreatureIndex()
    {
        // Add creatures here with their specific properties.
        // Note: Creatures not added here will get default properties.

        m_entries.insert({Hash("CreatureRedBird"), CreatureIndexEntry{2.0f, 3.0f}});
    }

    float CreatureIndex::GetModelScaling(int creatureHash) const
    {
        // Return the model scaling for a given creature hash.

        if (m_entries.contains(creatureHash))
        {
            return m_entries.at(creatureHash).modelScaling;
        }

        return 1.0f;
    }

    float CreatureIndex::GetLevitationHeight(int creatureHash) const
    {
        // Return the levitation height for a given creature hash.

        if (m_entries.contains(creatureHash))
        {
            return m_entries.at(creatureHash).levitationHeight;
        }

        return 0.0f;
    }

    bool CreatureIndex::CreatureEntryExists(int creatureHash) const
    {
        // Return true if a creature entry exists for a given creature hash.

        return m_entries.contains(creatureHash);
    }
}