/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include "ObjectIndexEntry.hpp"
    #include <unordered_map>
// clang-format on

namespace ForradiaEngine::Theme0
{
    /**
     *  Class for managing object properties.
     */
    class ObjectIndex
    {
      public:
        static ObjectIndex &instance()
        {
            static ObjectIndex instance;
            return instance;
        }

        ObjectIndex(const ObjectIndex &) = delete;

        ObjectIndex &operator=(const ObjectIndex &) = delete;

        /**
         *  Constructor.
         */
        ObjectIndex();

        /**
         *  Get the model scaling for a given object hash.
         *
         *  @param objectHash The hash of the object.
         *  @return The model scaling for the given object.
         */
        auto getModelScaling(int objectHash) const -> float;

        /**
         *  Check if an object entry exists for a given object hash.
         *
         *  @param objectHash The hash of the object.
         *  @return True if an object entry exists for the given object hash, false otherwise.
         */
        auto objectEntryExists(int objectHash) const -> bool;

        /**
         *  Gets whether the object type with the given hash should have individual model scaling
         *  ignored.
         *
         *  @param objectHash The hash of the object.
         *  @return True if individual model scaling should be ignored, otherwise false.
         */
        auto getIgnoreIndividualModelScaling(int objectHash) const -> bool;

        auto getNumContainerSlots(int objectHash) const -> int;

        auto getBlocksMovement(int objectHash) const -> bool;

      private:
        auto addObjectEntry(std::string_view objectName, float modelScaling,
                            bool ignoreIndividualModelScaling, int numContainerSlots,
                            bool blocksMovement) -> void;

        std::unordered_map<int, ObjectIndexEntry> m_entries{};
    };
}
