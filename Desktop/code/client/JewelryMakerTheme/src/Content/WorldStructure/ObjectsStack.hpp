/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include <vector>
// clang-format on

namespace ForradiaEngine::Theme0
{
    class Object;

    /**
     *  A stack of objects, primarily a component of a tile.
     */
    class ObjectsStack
    {
      public:
        /**
         *  Deletes all objects in the stack.
         */
        auto clearObjects() -> void;

        /**
         *  Adds a new object to the stack.
         *
         *  @param objectName The object name.
         */
        auto addObject(std::string_view objectName) -> void;

        /**
         *  Removes one object of a specific type from the stack.
         *
         *  @param objectTypeName The object type by name.
         */
        auto removeOneOfObjectOfType(std::string_view objectTypeName) -> void;

        /**
         *  Gets the number of objects in the stack.
         *
         *  @return The number of objects in the stack.
         */
        auto getSize() const -> int;

        /**
         *  Pops one object from the stack.
         *
         *  @return The object popped from the stack.
         */
        auto popObject() -> std::shared_ptr<Object>;

        auto getTopObjectPtrPtr() -> std::shared_ptr<Object> *;

        /**
         *  Counts the number of objects of a specific type in the stack.
         *
         *  @param objectTypeName The object type by name.
         * @return The number of objects of the specified type in the stack.
         */
        auto countHasObject(std::string_view objectTypeName) const -> int;

        /**
         *  Gets the collection of objects in the stack.
         *
         *  @return The collection of objects in the stack.
         */
        auto getObjects() const
        {
            return m_objects;
        }

      private:
        std::vector<std::shared_ptr<Object>> m_objects{};
    };
}
