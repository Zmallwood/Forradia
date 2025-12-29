/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include <unordered_map>
#include <string_view>
#include "ObjectIndexEntry.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    /**
     *  Class for managing object properties.
     */
    class ObjectIndex
    {
      public:
        static auto instance() -> ObjectIndex &
        {
            static ObjectIndex instance;
            return instance;
        }

        ObjectIndex(const ObjectIndex &) = delete;

        auto operator=(const ObjectIndex &) -> ObjectIndex & = delete;

        /**
         *  Constructor.
         */
        ObjectIndex()
        {
            this->initialize();
        }

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

        /**
         *  Gets the number of container slots for a given object hash. 0 means it is not a
         * container.
         *
         *  @param objectHash The hash of the object.
         *  @return The number of container slots for the given object.
         */
        auto getNumContainerSlots(int objectHash) const -> int;

        /**
         *  Gets whether the object type with the given hash should block movement.
         *
         *  @param objectHash The hash of the object.
         *  @return True if the object should block movement, otherwise false.
         */
        auto getBlocksMovement(int objectHash) const -> bool;

      private:
        void initialize();

        auto addObjectEntry(std::string_view objectName, float modelScaling,
                            bool ignoreIndividualModelScaling, int numContainerSlots,
                            bool blocksMovement) -> void;

        std::unordered_map<int, ObjectIndexEntry> m_entries{};
    };
}
