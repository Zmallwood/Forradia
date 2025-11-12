//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace Forradia::Theme0
{
    ///
    /// An object, either in the game world, a container or inventory.
    ///
    class Object
    {
      public:
        ///
        /// Constructor.
        ///
        /// @param objectNameHash The object name as a hash.
        ///
        Object(int objectNameHash) : m_type(objectNameHash)
        {
        }

        ///
        /// Constructor.
        ///
        /// @param objectTypeName The object type by name.
        ///
        Object(StringView objectTypeName) : m_type(Hash(objectTypeName))
        {
        }

        ///
        /// Gets the object type.
        ///
        /// @return The object type as a hash.
        ///
        auto GetType() const
        {
            return m_type;
        }

      private:
        int m_type{0}; ///< The object type as a hash.
    };
}