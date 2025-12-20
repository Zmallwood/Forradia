/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "ObjectIndex.hpp"

namespace Forradia::Theme0 {
    ObjectIndex::ObjectIndex() {
        AddObjectEntry("ObjectFirTree", 2.0F, false);
        AddObjectEntry("ObjectBirchTree", 2.0F, false);
        AddObjectEntry("ObjectBush1", 1.2F, false);
        AddObjectEntry("ObjectBush2", 1.2F, false);
        AddObjectEntry("ObjectStoneWall", 0.8F, true);
        AddObjectEntry("ObjectStoneWallDoor", 0.8F, true);
    }

    auto ObjectIndex::AddObjectEntry(std::string_view objectName, float modelScaling,
                                     bool ignoreIndividualModelScaling) -> void {
        m_entries.insert({Hash(objectName), {modelScaling, ignoreIndividualModelScaling}});
    }

    auto ObjectIndex::GetModelScaling(int objectHash) const -> float {
        if (m_entries.contains(objectHash))
            return m_entries.at(objectHash).modelScaling;
        return 1.0F;
    }

    auto ObjectIndex::ObjectEntryExists(int objectHash) const -> bool {
        return m_entries.contains(objectHash);
    }

    auto ObjectIndex::GetIgnoreIndividualModelScaling(int objectHash) const -> bool {
        if (m_entries.contains(objectHash))
            return m_entries.at(objectHash).ignoreIndividualModelScaling;
        return false;
    }
}
