/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "ObjectsStack.hpp"
    #include "Object.hpp"
    #include <algorithm>
// clang-format on

namespace Forradia::Theme0
{
    auto ObjectsStack::clearObjects() -> void
    {
        m_objects.clear();
    }

    auto ObjectsStack::addObject(std::string_view objectName) -> void
    {
        m_objects.push_back(std::make_shared<Object>(hash(objectName)));
    }

    auto ObjectsStack::removeOneOfObjectOfType(std::string_view objectTypeName) -> void
    {
        for (auto it = m_objects.begin(); it != m_objects.end();)
        {
            // If the object type matches.
            if ((*it)->getType() == hash(objectTypeName))
            {
                // Delete the object.
                m_objects.erase(it);

                // Stop iterating since only one object should be removed.
                return;
            }
            else
            {
                ++it;
            }
        }
    }

    auto ObjectsStack::getSize() const -> int
    {
        return m_objects.size();
    }

    auto ObjectsStack::popObject() -> std::shared_ptr<Object>
    {
        if (m_objects.empty())
        {
            return nullptr;
        }

        auto object{m_objects.back()};
        m_objects.pop_back();

        return object;
    }

    auto ObjectsStack::getTopObjectPtrPtr() -> std::shared_ptr<Object> *
    {
        if (m_objects.empty())
        {
            return nullptr;
        }

        return &m_objects.back();
    }

    auto ObjectsStack::countHasObject(std::string_view objectTypeName) const -> int
    {
        // Return the number of objects of the specified type in the stack.
        return std::count_if(m_objects.begin(), m_objects.end(),
                             [&](const std::shared_ptr<Object> &object)
                             { return object->getType() == hash(objectTypeName); });
    }
}
