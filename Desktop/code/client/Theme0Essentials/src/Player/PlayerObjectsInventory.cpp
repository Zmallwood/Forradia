//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#include "PlayerObjectsInventory.hpp"
#include "Object.hpp"

namespace Forradia::Theme0 {
    PlayerObjectsInventory::PlayerObjectsInventory() {
        // Add starting objects.

        AddObject("ObjectRedApple");

        AddObject("ObjectRedApple");

        AddObject("ObjectPlasticAxe");
    }

    SharedPtr<Object> PlayerObjectsInventory::GetObject(int index) {
        // Check if index is valid.

        if (index >= 0 && index < m_objects.size()) {
            // Return object at index.

            return m_objects[index];
        }

        // Return nullptr if index is invalid.

        return nullptr;
    }

    void PlayerObjectsInventory::AddObject(int objectType) {
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

    void PlayerObjectsInventory::AddObject(StringView objectName) {
        // Forward to the other AddObject function.

        AddObject(Hash(objectName));
    }

    int PlayerObjectsInventory::CountHasObject(StringView objectName) {
        // Initialize the count to 0.

        auto findCount{0};

        // Check each slot in the inventory.

        for (size_t i = 0; i < m_objects.size(); i++) {
            // Check if slot is not empty.

            if (m_objects[i]) {
                // Check if object type matches.

                if (m_objects[i]->GetType() == Hash(objectName)) {
                    // Increment count if object type matches.

                    ++findCount;
                }
            }
        }

        // Return the count.

        return findCount;
    }

    void PlayerObjectsInventory::RemoveObject(StringView objectName, int count) {
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
}