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
        m_objects[0][0] =
            std::make_shared<Object>("ObjectRedApple");
        m_objects[2][0] =
            std::make_shared<Object>("ObjectRedApple");
    }

    SharedPtr<Object> ObjectsInventory::GetObject(int x,
                                                  int y)
    {
        if (m_objects.contains(x) &&
            m_objects.at(x).contains(y))
        {
            return m_objects.at(x).at(y);
        }

        return nullptr;
    }
}