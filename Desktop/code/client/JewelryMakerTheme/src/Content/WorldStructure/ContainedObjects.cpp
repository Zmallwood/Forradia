/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "ContainedObjects.hpp"
    #include "Object.hpp"
// clang-format on

namespace ForradiaEngine::JewelryMakerTheme
{
    auto ContainedObjects::initialize(int numSlots) -> void
    {
        for (auto i = 0; i < numSlots; ++i)
        {
            m_objects.push_back(std::make_shared<std::shared_ptr<Object>>());
        }
    }

    auto ContainedObjects::getObject(int index) -> std::shared_ptr<Object>
    {
        if (index >= 0 && index < m_objects.size())
        {
            return *m_objects[index];
        }

        return nullptr;
    }

    auto ContainedObjects::getObjectPtrPtr(int index) -> std::shared_ptr<std::shared_ptr<Object>>
    {
        if (index >= 0 && index < m_objects.size())
        {
            return m_objects[index];
        }

        return nullptr;
    }

    auto ContainedObjects::addObject(int objectType) -> void
    {
        // Check if there is an empty slot.
        for (size_t i = 0; i < m_objects.size(); i++)
        {
            // Check if slot is empty.
            if (!*m_objects[i])
            {
                // Add object to slot.
                *m_objects[i] = std::make_shared<Object>(objectType);

                // Dont continue as the object has been added.
                return;
            }
        }
    }

    auto ContainedObjects::addObject(std::string_view objectName) -> void
    {
        addObject(hash(objectName));
    }

    auto ContainedObjects::countHasObject(std::string_view objectName) -> int
    {
        return countHasObject(hash(objectName));
    }

    auto ContainedObjects::countHasObject(int objectHash) -> int
    {
        auto findCount{0};

        // Check each slot in the inventory.
        for (size_t i = 0; i < m_objects.size(); i++)
        {
            // Check if slot is not empty.
            if (*m_objects[i])
            {
                // Check if object type matches.
                if ((*m_objects[i])->getType() == objectHash)
                {
                    // Increment count if object type matches.
                    ++findCount;
                }
            }
        }

        return findCount;
    }

    auto ContainedObjects::removeObject(std::string_view objectName, int count) -> void
    {
        // Check each slot in the inventory.
        for (size_t i = 0; i < m_objects.size() && count > 0; i++)
        {
            // Check if slot is not empty.
            if (*m_objects[i])
            {
                // Check if object type matches.
                if ((*m_objects[i])->getType() == hash(objectName))
                {
                    // Remove object from slot.
                    *m_objects[i] = nullptr;

                    // Decrement count.
                    count--;
                }
            }
        }
    }

    auto ContainedObjects::size() const -> int
    {
        return m_objects.size();
    }
}
