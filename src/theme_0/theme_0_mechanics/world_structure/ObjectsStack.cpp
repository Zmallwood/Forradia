/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "ObjectsStack.hpp"
#include "Object.hpp"
#include "TreeObject.hpp"

namespace Forradia {
  void ObjectsStack::ClearObjects() { m_objects.clear(); }

  void ObjectsStack::AddObject(StringView objectTypeName) {
    m_objects.push_back(std::make_shared<Object>(objectTypeName));
  }

  void ObjectsStack::AddTreeObject(StringView objectTypeName) {
    m_objects.push_back(std::make_shared<TreeObject>(objectTypeName));
  }

  int ObjectsStack::GetSize() const { return m_objects.size(); }
}