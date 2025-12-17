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
  void ClearObjects();

  /**
   * Adds a new object to the stack.
   *
   * @param objectName The object name.
   */
  void AddObject(StringView objectName);

  /**
   * Removes one object of a specific type from the stack.
   *
   * @param objectTypeName The object type by name.
   */
  void RemoveOneOfObjectOfType(StringView objectTypeName);

  /**
   * Gets the number of objects in the stack.
   *
   * @return The number of objects in the stack.
   */
  int GetSize() const;

  /**
   * Pops one object from the stack.
   *
   * @return The object popped from the stack.
   */
  SharedPtr<Object> PopObject();

  /**
   * Counts the number of objects of a specific type in the stack.
   *
   * @param objectTypeName The object type by name.
   * @return The number of objects of the specified type in the stack.
   */
  int CountHasObject(StringView objectTypeName) const;

  /**
   * Gets the collection of objects in the stack.
   *
   * @return The collection of objects in the stack.
   */
  auto GetObjects() const {
    return m_objects;
  }

 private:
  Vector<SharedPtr<Object>> m_objects;
};
}