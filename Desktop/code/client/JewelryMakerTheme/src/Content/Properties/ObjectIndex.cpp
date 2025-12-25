/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "ObjectIndex.hpp"
// clang-format on

namespace ForradiaEngine::JewelryMakerTheme
{
    ObjectIndex::ObjectIndex()
    {
        addObjectEntry("ObjectFirTree", 2.0F, false, 0, false);
        addObjectEntry("ObjectBirchTree", 2.0F, false, 0, false);
        addObjectEntry("ObjectBush1", 1.2F, false, 0, false);
        addObjectEntry("ObjectBush2", 1.2F, false, 0, false);
        addObjectEntry("ObjectStoneWall", 0.8F, true, 0, true);
        addObjectEntry("ObjectStoneWallDoor", 0.8F, true, 0, false);
        addObjectEntry("ObjectStoneBowl", 1.0F, true, 4, false);
        addObjectEntry("ObjectUnlitCampfire", 1.3F, true, 8, false);
        addObjectEntry("ObjectLitCampfire", 1.3F, true, 8, false);
        addObjectEntry("ObjectStoneBoulder", 1.0F, false, 0, true);
    }

    auto ObjectIndex::addObjectEntry(std::string_view objectName, float modelScaling,
                                     bool ignoreIndividualModelScaling, int numContainerSlots,
                                     bool blocksMovement) -> void
    {
        m_entries.insert(
            {hash(objectName),
             {modelScaling, ignoreIndividualModelScaling, numContainerSlots, blocksMovement}});
    }

    auto ObjectIndex::getModelScaling(int objectHash) const -> float
    {
        if (m_entries.contains(objectHash))
        {
            return m_entries.at(objectHash).modelScaling;
        }

        return 1.0F;
    }

    auto ObjectIndex::objectEntryExists(int objectHash) const -> bool
    {
        return m_entries.contains(objectHash);
    }

    auto ObjectIndex::getIgnoreIndividualModelScaling(int objectHash) const -> bool
    {
        if (m_entries.contains(objectHash))
        {
            return m_entries.at(objectHash).ignoreIndividualModelScaling;
        }

        return false;
    }

    auto ObjectIndex::getNumContainerSlots(int objectHash) const -> int
    {
        if (m_entries.contains(objectHash))
        {
            return m_entries.at(objectHash).numContainerSlots;
        }

        return 0;
    }

    auto ObjectIndex::getBlocksMovement(int objectHash) const -> bool
    {
        if (m_entries.contains(objectHash))
        {
            return m_entries.at(objectHash).blocksMovement;
        }

        return false;
    }
}
