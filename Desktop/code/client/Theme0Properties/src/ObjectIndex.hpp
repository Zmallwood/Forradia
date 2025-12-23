/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "ObjectIndexEntry.hpp"
#include <unordered_map>

namespace Forradia::Theme0
{
    /**
     * Class for managing object properties.
     */
    class ObjectIndex
    {
      public:
        static ObjectIndex &Instance()
        {
            static ObjectIndex instance;
            return instance;
        }

        // Delete copy/move
        ObjectIndex(const ObjectIndex &) = delete;

        ObjectIndex &operator=(const ObjectIndex &) = delete;

        /**
         * Constructor.
         */
        ObjectIndex();

        /**
         * Get the model scaling for a given object hash.
         *
         * @param objectHash The hash of the object.
         * @return The model scaling for the given object.
         */
        auto GetModelScaling(int objectHash) const -> float;

        /**
         * Check if an object entry exists for a given object hash.
         *
         * @param objectHash The hash of the object.
         * @return True if an object entry exists for the given object hash, false otherwise.
         */
        auto ObjectEntryExists(int objectHash) const -> bool;

        /**
         * Gets whether the object type with the given hash should have individual model scaling
         * ignored.
         *
         * @param objectHash The hash of the object.
         * @return True if individual model scaling should be ignored, otherwise false.
         */
        auto GetIgnoreIndividualModelScaling(int objectHash) const -> bool;

        auto GetNumContainerSlots(int objectHash) const -> int;

        auto GetBlocksMovement(int objectHash) const -> bool;

      private:
        auto AddObjectEntry(std::string_view objectName, float modelScaling,
                            bool ignoreIndividualModelScaling, int numContainerSlots,
                            bool blocksMovement) -> void;

        std::unordered_map<int, ObjectIndexEntry> m_entries{};
    };
}
