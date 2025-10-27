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
        m_objects.clear();
    }

    void ObjectsStack::AddObject(StringView objectTypeName)
    {
        m_objects.push_back(
            std::make_shared<Object>(objectTypeName));
    }

    void
    ObjectsStack::AddTreeObject(StringView objectTypeName)
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