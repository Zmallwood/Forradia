//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "ObjectsInventory.hpp"

#include "Object.hpp"

namespace Forradia::Theme0::GameplayCore
{
    ObjectsInventory::ObjectsInventory()
    {
        AddObject("ObjectComputer");
        AddObject("ObjectRedApple");
        AddObject("ObjectRedApple");
    }

    SharedPtr<Object> ObjectsInventory::GetObject(int index)
    {
        if (index >= 0 && index < m_objects.size())
        {
            return m_objects[index];
        }

        return nullptr;
    }

    void ObjectsInventory::AddObject(int objectType)
    {
        for (size_t i = 0; i < m_objects.size(); i++)
        {
            if (!m_objects[i])
            {
                m_objects[i] = std::make_shared<Object>(objectType);

                return;
            }
        }

        m_objects.push_back(std::make_shared<Object>(objectType));
    }

    void ObjectsInventory::AddObject(StringView objectName)
    {
        AddObject(Hash(objectName));
    }

    int ObjectsInventory::CountHasObject(StringView objectName)
    {
        auto findCount{0};

        for (size_t i = 0; i < m_objects.size(); i++)
        {
            if (m_objects[i])
            {
                if (m_objects[i]->GetType() == Hash(objectName))
                {
                    ++findCount;
                }
            }
        }

        return findCount;
    }

    void ObjectsInventory::RemoveObject(StringView objectName, int count)
    {
        for (size_t i = 0; i < m_objects.size() && count > 0; i++)
        {
            if (m_objects[i])
            {
                if (m_objects[i]->GetType() == Hash(objectName))
                {
                    m_objects[i] = nullptr;

                    count--;
                }
            }
        }
    }
}