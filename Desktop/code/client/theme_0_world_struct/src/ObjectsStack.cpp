//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "ObjectsStack.hpp"

#include "Object.hpp"

namespace Forradia::Theme0
{
    void ObjectsStack::ClearObjects()
    {
        // Delete all objects in the stack.

        m_objects.clear();
    }

    void ObjectsStack::AddObject(StringView objectName)
    {
        // Add new object of type Object to the stack.

        m_objects.push_back(std::make_shared<Object>(Hash(objectName)));
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

    SharedPtr<Object> ObjectsStack::PopObject()
    {
        // Pop one object from the stack.

        if (m_objects.empty())
        {
            return nullptr;
        }

        auto object{m_objects.back()};

        m_objects.pop_back();

        return object;
    }
}