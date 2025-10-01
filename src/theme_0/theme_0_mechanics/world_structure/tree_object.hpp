/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "object.hpp"

namespace forr {
  class TreeObject : public Object {
  public:
    TreeObject(str_view objectTypeName) : Object(objectTypeName) {
      Initialize(objectTypeName);
    }

    auto GetTrunkparts() const { return m_trunkParts; }

    auto GetNeedleTypes() const { return m_needleTypes; }

    auto GetWidthFactor() const { return m_widthFactor; }

  private:
    void Initialize(str_view objectTypeName);

    vec<PointF> m_trunkParts;
    vec<int> m_needleTypes;
    float m_widthFactor{1.0f};
  };
}