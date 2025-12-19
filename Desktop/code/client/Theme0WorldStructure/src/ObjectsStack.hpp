/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once

namespace Forradia::Theme0 {
  class Object;

  /**
   * A stack of objects, primarily a component of a tile.
   */
  class ObjectsStack {
   public:
    /**
     * Deletes all objects in the stack.
     */
    auto ClearObjects() -> void;

    /**
     * Adds a new object to the stack.
     *
     * @param objectName The object name.
     */
    auto AddObject(std::string_view objectName) -> void;

    /**
     * Removes one object of a specific type from the stack.
     *
     * @param objectTypeName The object type by name.
     */
    auto RemoveOneOfObjectOfType(std::string_view objectTypeName) -> void;

    /**
     * Gets the number of objects in the stack.
     *
     * @return The number of objects in the stack.
     */
    auto GetSize() const -> int;

    /**
     * Pops one object from the stack.
     *
     * @return The object popped from the stack.
     */
    auto PopObject() -> std::shared_ptr<Object>;

    /**
     * Counts the number of objects of a specific type in the stack.
     *
     * @param objectTypeName The object type by name.
     * @return The number of objects of the specified type in the stack.
     */
    auto CountHasObject(std::string_view objectTypeName) const -> int;

    /**
     * Gets the collection of objects in the stack.
     *
     * @return The collection of objects in the stack.
     */
    auto GetObjects() const {
      return m_objects;
    }

   private:
    std::vector<std::shared_ptr<Object>> m_objects;
  };
}
