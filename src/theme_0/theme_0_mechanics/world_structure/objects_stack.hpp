/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class Object;

  class ObjectsStack {
  public:
    void ClearObjects();

    void AddObject(str_view objectTypeName);

    void AddTreeObject(str_view objectTypeName);

    int GetSize() const;

    auto GetObjects() const { return m_objects; }

  private:
    vec<s_ptr<Object>> m_objects;
  };
}