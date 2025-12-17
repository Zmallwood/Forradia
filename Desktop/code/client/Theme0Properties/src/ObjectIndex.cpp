/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "ObjectIndex.hpp"

namespace Forradia::Theme0 {
ObjectIndex::ObjectIndex() {
  AddObjectEntry("ObjectFirTree", 2.0f, false);
  AddObjectEntry("ObjectBirchTree", 2.0f, false);
  AddObjectEntry("ObjectBush1", 1.2f, false);
  AddObjectEntry("ObjectBush2", 1.2f, false);
  AddObjectEntry("ObjectStoneWall", 0.8f, true);
  AddObjectEntry("ObjectStoneWallDoor", 0.8f, true);
}

void ObjectIndex::AddObjectEntry(StringView objectName, float modelScaling,
                                 bool ignoreIndividualModelScaling) {
  m_entries.insert({Hash(objectName), {modelScaling, ignoreIndividualModelScaling}});
}

float ObjectIndex::GetModelScaling(int objectHash) const {
  if (m_entries.contains(objectHash))
    return m_entries.at(objectHash).modelScaling;
  return 1.0f;
}

bool ObjectIndex::ObjectEntryExists(int objectHash) const {
  return m_entries.contains(objectHash);
}

bool ObjectIndex::GetIgnoreIndividualModelScaling(int objectHash) const {
  if (m_entries.contains(objectHash))
    return m_entries.at(objectHash).ignoreIndividualModelScaling;
  return false;
}
}