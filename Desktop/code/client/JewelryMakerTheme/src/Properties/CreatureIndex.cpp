/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "CreatureIndex.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    CreatureIndex::CreatureIndex()
    {
        addCreatureEntry("CreatureRedBird", 0.5F, 3.0F);
    }

    auto CreatureIndex::addCreatureEntry(std::string_view creatureName, float modelScaling,
                                         float levitationHeight) -> void
    {
        m_entries.insert({hash(creatureName), {modelScaling, levitationHeight}});
    }

    auto CreatureIndex::getModelScaling(int creatureHash) const -> float
    {
        if (m_entries.contains(creatureHash))
        {
            return m_entries.at(creatureHash).modelScaling;
        }

        return 1.0F;
    }

    auto CreatureIndex::getLevitationHeight(int creatureHash) const -> float
    {
        if (m_entries.contains(creatureHash))
        {
            return m_entries.at(creatureHash).levitationHeight;
        }

        return 0.0F;
    }

    auto CreatureIndex::creatureEntryExists(int creatureHash) const -> bool
    {
        return m_entries.contains(creatureHash);
    }
}
