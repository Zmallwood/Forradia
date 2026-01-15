/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include <unordered_map>
#include <string_view>
#include "CreatureIndexEntry.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    /**
     *  Class for managing creature properties.
     */
    class CreatureIndex
    {
      public:
        static auto instance() -> CreatureIndex &
        {
            static CreatureIndex instance;
            return instance;
        }

        CreatureIndex(const CreatureIndex &) = delete;

        auto operator=(const CreatureIndex &) -> CreatureIndex & = delete;

        /**
         *  Constructor.
         */
        CreatureIndex()
        {
            this->initialize();
        }

        /**
         *  Get the model scaling for a given creature hash.
         *
         *  @param creatureHash The hash of the creature.
         *  @return The model scaling for the given creature.
         */
        auto getModelScaling(int creatureHash) const -> float;

        /**
         *  Get the levitation height for a given creature hash.
         *
         *  @param creatureHash The hash of the creature.
         *  @return The levitation height for the given creature.
         */
        auto getLevitationHeight(int creatureHash) const -> float;

        /**
         *  Check if a creature entry exists for a given creature hash.
         *
         *  @param creatureHash The hash of the creature.
         *  @return True if a creature entry exists for the given creature hash, false otherwise.
         */
        auto creatureEntryExists(int creatureHash) const -> bool;

      private:
        void initialize();

        auto addCreatureEntry(std::string_view creatureName, float modelScaling,
                              float levitationHeight) -> void;

        std::unordered_map<int, CreatureIndexEntry> m_entries{};
    };
}
