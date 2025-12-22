/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "CreatureIndex.hpp"

namespace Forradia::Theme0
{
    CreatureIndex::CreatureIndex()
    {
        AddCreatureEntry("CreatureRedBird", 0.5F, 3.0F);
    }

    auto CreatureIndex::AddCreatureEntry(std::string_view creatureName, float modelScaling,
                                         float levitationHeight) -> void
    {
        m_entries.insert({Hash(creatureName), {modelScaling, levitationHeight}});
    }

    auto CreatureIndex::GetModelScaling(int creatureHash) const -> float
    {
        if (m_entries.contains(creatureHash))
        {
            return m_entries.at(creatureHash).modelScaling;
        }

        return 1.0F;
    }

    auto CreatureIndex::GetLevitationHeight(int creatureHash) const -> float
    {
        if (m_entries.contains(creatureHash))
        {
            return m_entries.at(creatureHash).levitationHeight;
        }

        return 0.0F;
    }

    auto CreatureIndex::CreatureEntryExists(int creatureHash) const -> bool
    {
        return m_entries.contains(creatureHash);
    }
}
