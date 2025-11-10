//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace Forradia::Theme0
{
    class Object;

    ///
    /// A stack of objects, primarily a component of a tile.
    ///
    class ObjectsStack
    {
      public:
        ///
        /// Delete all objects in the stack.
        ///
        void ClearObjects();

        ///
        /// Add new object to the stack.
        ///
        /// @param objectNameHash The object name hash.
        ///
        void AddObject(int objectNameHash);

        ///
        /// Add new object of type T to the stack.
        ///
        /// @tparam T The object type, defaults to Object.
        /// @param objectTypeName The object type by name.
        ///
        template <class T = Object>
        void AddObject(StringView objectTypeName);

        ///
        /// Remove one object of a specific type from the stack.
        ///
        /// @param objectTypeName The object type by name.
        ///
        void RemoveOneOfObjectOfType(StringView objectTypeName);

        ///
        /// Gets the number of objects in the stack.
        ///
        /// @return The number of objects in the stack.
        ///
        int GetSize() const;

        ///
        /// Gets the collection of objects in the stack.
        ///
        /// @return The collection of objects in the stack.
        ///
        auto GetObjects() const
        {
            return m_objects;
        }

      private:
        Vector<SharedPtr<Object>> m_objects; ///< The collection of objects in the stack.
    };
}