/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "tree_object.hpp"

namespace forr {
  void tree_object::initialize(str_view objectTypeName) {
    if (objectTypeName != "ObjectFirTree" &&
        objectTypeName != "ObjectBirchTree") {
      return;
    }
    int numTrunkParts;
    if (objectTypeName == "ObjectFirTree") {
      numTrunkParts = 55 + random_int(44);
    } else if (objectTypeName == "ObjectBirchTree") {
      numTrunkParts = 25 + random_int(14);
    }
    m_widthFactor *= (random_int(5) + 1) / 2.0f + 1.0f;
    auto offsetX{0.0f};
    for (auto i = 0; i < numTrunkParts; i++) {
      offsetX += (random_int(20) - 10) / 100.0f;
      auto offsetY{i * 0.1f};
      auto position{point_f{offsetX, offsetY}};
      auto needlesType{random_int(5)};
      m_trunkParts.push_back(position);
      str needlesName;
      if (objectTypeName == "ObjectFirTree") {
        needlesName = "ObjectFirTreeNeedles";
      } else if (objectTypeName == "ObjectBirchTree") {
        if (i % 4 != 0) {
          m_needleTypes.push_back(0);
          continue;
        }
        needlesName = "ObjectBirchTreeBranch";
      }
      m_needleTypes.push_back(
          needlesType ? hash(needlesName + std::to_string(needlesType)) : 0);
    }
  }
}