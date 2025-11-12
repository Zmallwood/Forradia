//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "ObjectIndex.hpp"

namespace Forradia::Theme0
{
    ObjectIndex::ObjectIndex()
    {
        // Add objects here with their specific properties.
        // Note: Objects not added here will get default properties.

        m_entries.insert({Hash("ObjectFirTree"), ObjectIndexEntry{2.0f}});

        m_entries.insert({Hash("ObjectBirchTree"), ObjectIndexEntry{2.0f}});

        m_entries.insert({Hash("ObjectBush1"), ObjectIndexEntry{2.0f}});

        m_entries.insert({Hash("ObjectBush2"), ObjectIndexEntry{2.0f}});
    }

    float ObjectIndex::GetModelScaling(int objectHash) const
    {
        // Return the model scaling for a given object hash.

        if (m_entries.contains(objectHash))
        {
            return m_entries.at(objectHash).modelScaling;
        }
        return 1.0f;
    }

    bool ObjectIndex::ObjectEntryExists(int objectHash) const
    {
        // Return true if an object entry exists for a given object hash.

        return m_entries.contains(objectHash);
    }
}