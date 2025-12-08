//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#include "ObjectIndex.hpp"

namespace Forradia::Theme0
{
    ObjectIndex::ObjectIndex()
    {
        // Add objects here with their specific properties.
        // Note: Objects not added here will get default properties.

        AddObjectEntry("ObjectFirTree", 2.0f);

        AddObjectEntry("ObjectBirchTree", 2.0f);

        AddObjectEntry("ObjectBush1", 1.2f);

        AddObjectEntry("ObjectBush2", 1.2f);
    }

    void ObjectIndex::AddObjectEntry(StringView objectName, float modelScaling)
    {
        // Add an object entry to the index.

        m_entries.insert({Hash(objectName), {modelScaling}});
    }

    float ObjectIndex::GetModelScaling(int objectHash) const
    {
        // Return the model scaling for a given object hash.

        if (m_entries.contains(objectHash))
        {
            return m_entries.at(objectHash).modelScaling;
        }

        // If no entry exists, return the default model scaling.

        return 1.0f;
    }

    bool ObjectIndex::ObjectEntryExists(int objectHash) const
    {
        // Return true if an object entry exists for a given object hash.

        return m_entries.contains(objectHash);
    }
}