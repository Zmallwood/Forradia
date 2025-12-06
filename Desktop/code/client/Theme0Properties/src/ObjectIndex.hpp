//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "ObjectIndexEntry.hpp"

namespace Forradia::Theme0
{
    ///
    /// Class for managing object properties.
    ///
    class ObjectIndex
    {
      public:
        ///
        /// Constructor.
        ///
        ObjectIndex();

        ///
        /// Get the model scaling for a given object hash.
        ///
        /// @param objectHash The hash of the object.
        /// @return The model scaling for the given object.
        ///
        float GetModelScaling(int objectHash) const;

        ///
        /// Check if an object entry exists for a given object hash.
        ///
        /// @param objectHash The hash of the object.
        /// @return True if an object entry exists for the given object hash, false otherwise.
        ///
        bool ObjectEntryExists(int objectHash) const;

      private:
        ///
        /// Add an object entry to the index.
        ///
        /// @param objectName The name of the object.
        /// @param modelScaling The scaling factor for the object model.
        ///
        void AddObjectEntry(StringView objectName, float modelScaling);

        std::map<int, ObjectIndexEntry>
            m_entries; ///< Map of object hashes to object index entries.
    };
}