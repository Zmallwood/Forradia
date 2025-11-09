//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "ObjectsStack.hpp"

#include "Object.hpp"

#include "TreeObject.hpp"

namespace Forradia::Theme0
{
    void ObjectsStack::ClearObjects()
    {
        // Delete all objects in the stack.

        m_objects.clear();
    }

    void ObjectsStack::AddObject(int objectNameHash)
    {
        // Add new object of type Object to the stack.

        m_objects.push_back(std::make_shared<Object>(objectNameHash));
    }

    template <>
    void ObjectsStack::AddObject<Object>(StringView objectTypeName)
    {
        // Add new object of Object type to the stack.

        m_objects.push_back(std::make_shared<Object>(objectTypeName));
    }

    template <>
    void ObjectsStack::AddObject<TreeObject>(StringView objectTypeName)
    {
        // Add new object of TreeObject type to the stack.

        m_objects.push_back(std::make_shared<TreeObject>(objectTypeName));
    }

    void ObjectsStack::RemoveOneOfObjectOfType(StringView objectTypeName)
    {
        // Iterate through the stack.

        for (auto it = m_objects.begin(); it != m_objects.end();)
        {
            // If the object type matches.

            if ((*it)->GetType() == Hash(objectTypeName))
            {
                // Delete the object.

                m_objects.erase(it);

                // Stop iterating since only one object should be removed.

                return;
            }
            else
            {
                // If no match, move to the next object.

                ++it;
            }
        }
    }

    int ObjectsStack::GetSize() const
    {
        // Return the number of objects in the stack.

        return m_objects.size();
    }
}