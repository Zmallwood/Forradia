/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "PlayerObjectsInventory.hpp"
#include "Object.hpp"
#include "StdAfx.hpp"

namespace Forradia::Theme0 {
PlayerObjectsInventory::PlayerObjectsInventory() {
  // Add starting objects.
  AddObject("ObjectRedApple");
  AddObject("ObjectRedApple");
  AddObject("ObjectPlasticAxe");
  AddObject("ObjectChisel");
  AddObject("ObjectHammer");
}

auto PlayerObjectsInventory::GetObject(int index) -> SharedPtr<Object> {
  if (index >= 0 && index < m_objects.size())
    return m_objects[index];
  return nullptr;
}

auto PlayerObjectsInventory::AddObject(int objectType) -> void {
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

auto PlayerObjectsInventory::AddObject(StringView objectName) -> void {
  AddObject(Hash(objectName));
}

auto PlayerObjectsInventory::CountHasObject(StringView objectName) -> int {
  auto findCount{0};

  // Check each slot in the inventory.
  for (size_t i = 0; i < m_objects.size(); i++) {
    // Check if slot is not empty.
    if (m_objects[i]) {
      // Check if object type matches.
      if (m_objects[i]->GetType() == Hash(objectName))
        // Increment count if object type matches.
        ++findCount;
    }
  }

  return findCount;
}

auto PlayerObjectsInventory::RemoveObject(StringView objectName, int count) -> void {
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
