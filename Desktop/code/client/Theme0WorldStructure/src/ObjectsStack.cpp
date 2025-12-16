//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Complete.
// TODO:

#include "ObjectsStack.hpp"
#include "Object.hpp"

namespace Forradia::Theme0 {
    void ObjectsStack::ClearObjects() {
        m_objects.clear();
    }

    void ObjectsStack::AddObject(StringView objectName) {
        m_objects.push_back(std::make_shared<Object>(Hash(objectName)));
    }

    void ObjectsStack::RemoveOneOfObjectOfType(StringView objectTypeName) {
        for (auto it = m_objects.begin(); it != m_objects.end();) {
            // If the object type matches.
            if ((*it)->GetType() == Hash(objectTypeName)) {
                // Delete the object.
                m_objects.erase(it);

                // Stop iterating since only one object should be removed.
                return;
            } else {
                ++it;
            }
        }
    }

    int ObjectsStack::GetSize() const {
        return m_objects.size();
    }

    SharedPtr<Object> ObjectsStack::PopObject() {
        if (m_objects.empty()) {
            return nullptr;
        }

        auto object{m_objects.back()};
        m_objects.pop_back();
        return object;
    }

    int ObjectsStack::CountHasObject(StringView objectTypeName) const {
        // Return the number of objects of the specified type in the stack.
        return std::count_if(m_objects.begin(), m_objects.end(),
                             [&](const SharedPtr<Object> &object) {
                                 return object->GetType() == Hash(objectTypeName);
                             });
    }
}