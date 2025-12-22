/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "ObjectIndex.hpp"

namespace Forradia::Theme0 {
    ObjectIndex::ObjectIndex() {
        AddObjectEntry("ObjectFirTree", 2.0F, false, 0);
        AddObjectEntry("ObjectBirchTree", 2.0F, false, 0);
        AddObjectEntry("ObjectBush1", 1.2F, false, 0);
        AddObjectEntry("ObjectBush2", 1.2F, false, 0);
        AddObjectEntry("ObjectStoneWall", 0.8F, true, 0);
        AddObjectEntry("ObjectStoneWallDoor", 0.8F, true, 0);
        AddObjectEntry("ObjectStoneBowl", 1.0F, true, 4);
        AddObjectEntry("ObjectUnlitCampfire", 1.3F, true, 8);
        AddObjectEntry("ObjectLitCampfire", 1.3F, true, 8);
    }

    auto ObjectIndex::AddObjectEntry(std::string_view objectName, float modelScaling,
                                     bool ignoreIndividualModelScaling, int numContainerSlots)
        -> void {
        m_entries.insert(
            {Hash(objectName), {modelScaling, ignoreIndividualModelScaling, numContainerSlots}});
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

    auto ObjectIndex::GetNumContainerSlots(int objectHash) const -> int {
        if (m_entries.contains(objectHash))
            return m_entries.at(objectHash).numContainerSlots;
        return 0;
    }
}
