//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#pragma once

#include "CreatureIndexEntry.hpp"

namespace Forradia::Theme0 {
    ///
    /// Class for managing creature properties.
    ///
    class CreatureIndex {
      public:
        ///
        /// Constructor.
        ///
        CreatureIndex();

        ///
        /// Get the model scaling for a given creature hash.
        ///
        /// @param creatureHash The hash of the creature.
        /// @return The model scaling for the given creature.
        ///
        float GetModelScaling(int creatureHash) const;

        ///
        /// Get the levitation height for a given creature hash.
        ///
        /// @param creatureHash The hash of the creature.
        /// @return The levitation height for the given creature.
        ///
        float GetLevitationHeight(int creatureHash) const;

        ///
        /// Check if a creature entry exists for a given creature hash.
        ///
        /// @param creatureHash The hash of the creature.
        /// @return True if a creature entry exists for the given creature hash, false
        /// otherwise.
        ///
        bool CreatureEntryExists(int creatureHash) const;

      private:
        ///
        /// Add a creature entry to the index.
        ///
        /// @param creatureName The name of the creature.
        /// @param modelScaling The scaling factor for the creature model.
        /// @param levitationHeight The height at which the creature levitates.
        ///
        void AddCreatureEntry(StringView creatureName, float modelScaling, float levitationHeight);

        std::map<int, CreatureIndexEntry>
            m_entries; ///< Map of creature hashes to creature index entries.
    };
}