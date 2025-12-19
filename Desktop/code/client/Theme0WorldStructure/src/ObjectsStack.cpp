/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "ObjectsStack.hpp"
#include "Object.hpp"

namespace Forradia::Theme0 {
  auto ObjectsStack::ClearObjects() -> void {
    m_objects.clear();
  }

  auto ObjectsStack::AddObject(std::string_view objectName) -> void {
    m_objects.push_back(std::make_shared<Object>(Hash(objectName)));
  }

  auto ObjectsStack::RemoveOneOfObjectOfType(std::string_view objectTypeName) -> void {
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

  auto ObjectsStack::GetSize() const -> int {
    return m_objects.size();
  }

  auto ObjectsStack::PopObject() -> std::shared_ptr<Object> {
    if (m_objects.empty())
      return nullptr;

    auto object{m_objects.back()};
    m_objects.pop_back();
    return object;
  }

  auto ObjectsStack::CountHasObject(std::string_view objectTypeName) const -> int {
    // Return the number of objects of the specified type in the stack.
    return std::count_if(m_objects.begin(), m_objects.end(),
                         [&](const std::shared_ptr<Object> &object) {
                           return object->GetType() == Hash(objectTypeName);
                         });
  }
}
