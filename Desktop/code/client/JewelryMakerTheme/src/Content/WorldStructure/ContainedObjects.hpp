/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

namespace Forradia::Theme0
{
    class Object;

    class ContainedObjects
    {
      public:
        ContainedObjects(int numSlots)
        {
            this->initialize(numSlots);
        }

        /**
         *  Gets an object from the inventory.
         *
         *  @param index The index of the object.
         * @return The object.
         */
        auto getObject(int index) -> std::shared_ptr<Object>;

        auto getObjectPtrPtr(int index) -> std::shared_ptr<std::shared_ptr<Object>>;

        /**
         *  Adds an object to the inventory.
         *
         *  @param objectType The type of the object as a hash.
         */
        auto addObject(int objectType) -> void;

        /**
         *  Adds an object to the inventory.
         *
         *  @param objectName The name of the object as a string.
         */
        auto addObject(std::string_view objectName) -> void;

        /**
         *  Counts the number of objects in the inventory that have the given name.
         *
         *  @param objectName The name of the object as a string.
         * @return The number of objects in the inventory that have the given name.
         */
        auto countHasObject(std::string_view objectName) -> int;

        auto countHasObject(int objectHash) -> int;

        /**
         *  Removes objects from the inventory with the specified name and count.
         *
         *  @param objectName The name of the object as a string.
         * @param count How many objects of the given type to remove.
         */
        auto removeObject(std::string_view objectName, int count = 1) -> void;

        auto size() const -> int;

      private:
        auto initialize(int numSlots) -> void;

        std::vector<std::shared_ptr<std::shared_ptr<Object>>> m_objects{};
    };
}
