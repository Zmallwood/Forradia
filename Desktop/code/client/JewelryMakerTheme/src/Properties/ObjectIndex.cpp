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
        addObjectEntry("ObjectFirTree", 1.2F, false, 0, false, false);
        // NOLINTNEXTLINE(readability-magic-numbers)
        addObjectEntry("ObjectBirchTree", 1.2F, false, 0, false, false);
        // NOLINTNEXTLINE(readability-magic-numbers)
        addObjectEntry("ObjectBush1", 1.2F, false, 0, false, false);
        // NOLINTNEXTLINE(readability-magic-numbers)
        addObjectEntry("ObjectBush2", 1.2F, false, 0, false, false);
        // NOLINTNEXTLINE(readability-magic-numbers)
        addObjectEntry("ObjectStoneWall", 1.05F, true, 0, true, false);
        // NOLINTNEXTLINE(readability-magic-numbers)
        addObjectEntry("ObjectStoneWallDoor", 1.05F, true, 0, false, false);
        // NOLINTNEXTLINE(readability-magic-numbers)
        addObjectEntry("ObjectStoneBowl", 1.0F, true, 4, false, true);
        // NOLINTNEXTLINE(readability-magic-numbers)
        addObjectEntry("ObjectUnlitCampfire", 1.3F, true, 8, false, false);
        // NOLINTNEXTLINE(readability-magic-numbers)
        addObjectEntry("ObjectLitCampfire", 1.3F, true, 8, false, false);
        // NOLINTNEXTLINE(readability-magic-numbers)
        addObjectEntry("ObjectStoneBoulder", 1.0F, false, 0, true, false);
        // NOLINTNEXTLINE(readability-magic-numbers)
        addObjectEntry("ObjectMineEntrance", 1.0F, true, 0, false, false);
        // NOLINTNEXTLINE(readability-magic-numbers)
        addObjectEntry("ObjectStoneBlock", 1.0F, true, 0, true, false);
        // NOLINTNEXTLINE(readability-magic-numbers)
        addObjectEntry("ObjectStone", 1.5F, false, 0, false, true);
        // NOLINTNEXTLINE(readability-magic-numbers)
        addObjectEntry("ObjectWoodLog", 1.3F, false, 0, false, true);
        // NOLINTNEXTLINE(readability-magic-numbers)
        addObjectEntry("ObjectWoodPlank", 1.4F, false, 0, false, true);
        // NOLINTNEXTLINE(readability-magic-numbers)
        addObjectEntry("ObjectWoodWallNorth", 1.3F, true, 0, true, false);
        // NOLINTNEXTLINE(readability-magic-numbers)
        addObjectEntry("ObjectWoodWallSouth", 1.3F, true, 0, true, false);
        // NOLINTNEXTLINE(readability-magic-numbers)
        addObjectEntry("ObjectWoodWallEast", 1.3F, true, 0, true, false);
        // NOLINTNEXTLINE(readability-magic-numbers)
        addObjectEntry("ObjectWoodWallWest", 1.3F, true, 0, true, false);
        // NOLINTNEXTLINE(readability-magic-numbers)
        addObjectEntry("ObjectAnvil", 1.3F, true, 0, false, false);
    }

    auto ObjectIndex::addObjectEntry(std::string_view objectName, float modelScaling,
                                     bool ignoreIndividualModelScaling, int numContainerSlots,
                                     bool blocksMovement, bool canBePickedUp) -> void
    {
        m_entries.insert({hash(objectName),
                          {modelScaling, ignoreIndividualModelScaling, numContainerSlots,
                           blocksMovement, canBePickedUp}});
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

    auto ObjectIndex::getCanBePickedUp(int objectHash) const -> bool
    {
        if (m_entries.contains(objectHash))
        {
            return m_entries.at(objectHash).canBePickedUp;
        }

        return false;
    }
}
