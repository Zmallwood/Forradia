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

    template <>
    void ObjectsStack::AddObject<Object>(
        StringView objectTypeName)
    {
        m_objects.push_back(
            std::make_shared<Object>(objectTypeName));
    }

    template <>
    void ObjectsStack::AddObject<TreeObject>(
        StringView objectTypeName)
    {
        m_objects.push_back(
            std::make_shared<TreeObject>(objectTypeName));
    }

    void ObjectsStack::RemoveObjectOfType(
        StringView objectTypeName)
    {
        for (auto it = m_objects.begin();
             it != m_objects.end();)
        {
            if ((*it)->GetType() == Hash(objectTypeName))
            {
                it = m_objects.erase(it);

                return;
            }
            else
            {
                it++;
            }
        }
    }

    int ObjectsStack::GetSize() const
    {
        return m_objects.size();
    }
}