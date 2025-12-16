//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#include "CreatureIndex.hpp"

namespace Forradia::Theme0 {
    CreatureIndex::CreatureIndex() {
        AddCreatureEntry("CreatureRedBird", 0.5f, 3.0f);
    }

    void CreatureIndex::AddCreatureEntry(StringView creatureName, float modelScaling,
                                         float levitationHeight) {
        m_entries.insert({Hash(creatureName), {modelScaling, levitationHeight}});
    }

    float CreatureIndex::GetModelScaling(int creatureHash) const {
        if (m_entries.contains(creatureHash)) {
            return m_entries.at(creatureHash).modelScaling;
        }
        return 1.0f;
    }

    float CreatureIndex::GetLevitationHeight(int creatureHash) const {
        if (m_entries.contains(creatureHash)) {
            return m_entries.at(creatureHash).levitationHeight;
        }
        return 0.0f;
    }

    bool CreatureIndex::CreatureEntryExists(int creatureHash) const {
        return m_entries.contains(creatureHash);
    }
}