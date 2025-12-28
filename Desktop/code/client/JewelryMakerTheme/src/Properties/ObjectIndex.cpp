/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "ObjectIndex.hpp"
#include "ForradiaEngine/Common/General.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    void ObjectIndex::initialize()
    {
        // NOLINTNEXTLINE(readability-magic-numbers)
        addObjectEntry("ObjectFirTree", 1.2F, false, 0, false);
        // NOLINTNEXTLINE(readability-magic-numbers)
        addObjectEntry("ObjectBirchTree", 1.2F, false, 0, false);
        // NOLINTNEXTLINE(readability-magic-numbers)
        addObjectEntry("ObjectBush1", 1.2F, false, 0, false);
        // NOLINTNEXTLINE(readability-magic-numbers)
        addObjectEntry("ObjectBush2", 1.2F, false, 0, false);
        // NOLINTNEXTLINE(readability-magic-numbers)
        addObjectEntry("ObjectStoneWall", 0.8F, true, 0, true);
        // NOLINTNEXTLINE(readability-magic-numbers)
        addObjectEntry("ObjectStoneWallDoor", 0.8F, true, 0, false);
        // NOLINTNEXTLINE(readability-magic-numbers)
        addObjectEntry("ObjectStoneBowl", 1.0F, true, 4, false);
        // NOLINTNEXTLINE(readability-magic-numbers)
        addObjectEntry("ObjectUnlitCampfire", 1.3F, true, 8, false);
        // NOLINTNEXTLINE(readability-magic-numbers)
        addObjectEntry("ObjectLitCampfire", 1.3F, true, 8, false);
        // NOLINTNEXTLINE(readability-magic-numbers)
        addObjectEntry("ObjectStoneBoulder", 1.0F, false, 0, true);
        // NOLINTNEXTLINE(readability-magic-numbers)
        addObjectEntry("ObjectMineEntrance", 1.0F, true, 0, false);
        // NOLINTNEXTLINE(readability-magic-numbers)
        addObjectEntry("ObjectStoneBlock", 1.0F, true, 0, true);
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
