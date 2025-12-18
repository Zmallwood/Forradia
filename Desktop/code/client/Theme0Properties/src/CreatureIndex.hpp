/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include "CreatureIndexEntry.hpp"

namespace Forradia::Theme0 {
  /**
   * Class for managing creature properties.
   */
  class CreatureIndex {
   public:
    /**
     * Constructor.
     */
    CreatureIndex();

    /**
     * Get the model scaling for a given creature hash.
     *
     * @param creatureHash The hash of the creature.
     * @return The model scaling for the given creature.
     */
    auto GetModelScaling(int creatureHash) const -> float;

    /**
     * Get the levitation height for a given creature hash.
     *
     * @param creatureHash The hash of the creature.
     * @return The levitation height for the given creature.
     */
    auto GetLevitationHeight(int creatureHash) const -> float;

    /**
     * Check if a creature entry exists for a given creature hash.
     *
     * @param creatureHash The hash of the creature.
     * @return True if a creature entry exists for the given creature hash, false otherwise.
     */
    auto CreatureEntryExists(int creatureHash) const -> bool;

   private:
    auto AddCreatureEntry(StringView creatureName, float modelScaling, float levitationHeight)
        -> void;

    std::map<int, CreatureIndexEntry> m_entries;
  };
}
