/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include "ObjectIndexEntry.hpp"

namespace Forradia::Theme0 {
/**
 * Class for managing object properties.
 */
class ObjectIndex {
 public:
  /**
   * Constructor.
   */
  ObjectIndex();

  /**
   * Get the model scaling for a given object hash.
   *
   * @param objectHash The hash of the object.
   * @return The model scaling for the given object.
   */
  float GetModelScaling(int objectHash) const;

  /**
   * Check if an object entry exists for a given object hash.
   *
   * @param objectHash The hash of the object.
   * @return True if an object entry exists for the given object hash, false otherwise.
   */
  bool ObjectEntryExists(int objectHash) const;

  bool GetIgnoreIndividualModelScaling(int objectHash) const;

 private:
  void AddObjectEntry(StringView objectName, float modelScaling, bool ignoreIndividualModelScaling);

  std::map<int, ObjectIndexEntry> m_entries;
};
}