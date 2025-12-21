/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "ContainedObjects.hpp"
#include "Object.hpp"

namespace Forradia::Theme0 {
    auto ContainedObjects::Initialize(int numSlots) -> void {
        for (auto i = 0; i < numSlots; ++i)
            m_objects.push_back(nullptr);
    }

    auto ContainedObjects::GetObject(int index) -> std::shared_ptr<Object> {
        if (index >= 0 && index < m_objects.size())
            return m_objects[index];
        return nullptr;
    }

    auto ContainedObjects::GetObjectPtrPtr(int index) -> std::shared_ptr<Object> * {
        if (index >= 0 && index < m_objects.size())
            return &m_objects[index];
        return nullptr;
    }

    auto ContainedObjects::AddObject(int objectType) -> void {
        // Check if there is an empty slot.
        for (size_t i = 0; i < m_objects.size(); i++) {
            // Check if slot is empty.
            if (!m_objects[i]) {
                // Add object to slot.
                m_objects[i] = std::make_shared<Object>(objectType);
                // Dont continue as the object has been added.
                return;
            }
        }

        // If no empty slot is found, add object to the end of the inventory.
        m_objects.push_back(std::make_shared<Object>(objectType));
    }

    auto ContainedObjects::AddObject(std::string_view objectName) -> void {
        AddObject(Hash(objectName));
    }

    auto ContainedObjects::CountHasObject(std::string_view objectName) -> int {
        return CountHasObject(Hash(objectName));
    }

    auto ContainedObjects::CountHasObject(int objectHash) -> int {
        auto findCount{0};

        // Check each slot in the inventory.
        for (size_t i = 0; i < m_objects.size(); i++) {
            // Check if slot is not empty.
            if (m_objects[i]) {
                // Check if object type matches.
                if (m_objects[i]->GetType() == objectHash)
                    // Increment count if object type matches.
                    ++findCount;
            }
        }

        return findCount;
    }

    auto ContainedObjects::RemoveObject(std::string_view objectName, int count) -> void {
        // Check each slot in the inventory.
        for (size_t i = 0; i < m_objects.size() && count > 0; i++) {
            // Check if slot is not empty.
            if (m_objects[i]) {
                // Check if object type matches.
                if (m_objects[i]->GetType() == Hash(objectName)) {
                    // Remove object from slot.
                    m_objects[i] = nullptr;
                    // Decrement count.
                    count--;
                }
            }
        }
    }

    auto ContainedObjects::Size() const -> int {
        return m_objects.size();
    }
}
