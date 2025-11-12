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

        AddCreatureEntry("CreatureRedBird", 0.5f, 3.0f);
    }

    void CreatureIndex::AddCreatureEntry(StringView creatureName, float modelScaling,
                                         float levitationHeight)
    {
        // Add a creature entry to the index.

        m_entries.insert({Hash(creatureName), {modelScaling, levitationHeight}});
    }

    float CreatureIndex::GetModelScaling(int creatureHash) const
    {
        // Return the model scaling for a given creature hash.

        if (m_entries.contains(creatureHash))
        {
            return m_entries.at(creatureHash).modelScaling;
        }

        // If no entry exists, return the default model scaling.

        return 1.0f;
    }

    float CreatureIndex::GetLevitationHeight(int creatureHash) const
    {
        // Return the levitation height for a given creature hash.

        if (m_entries.contains(creatureHash))
        {
            return m_entries.at(creatureHash).levitationHeight;
        }

        // If no entry exists, return the default levitation height.

        return 0.0f;
    }

    bool CreatureIndex::CreatureEntryExists(int creatureHash) const
    {
        // Return true if a creature entry exists for a given creature hash.

        return m_entries.contains(creatureHash);
    }
}