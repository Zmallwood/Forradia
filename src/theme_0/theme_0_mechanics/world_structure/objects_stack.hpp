/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

namespace Forradia {
  class Object;

  class ObjectsStack {
  public:
    void ClearObjects();

    void AddObject(StringView objectTypeName);

    void AddTreeObject(StringView objectTypeName);

    int GetSize() const;

    auto GetObjects() const { return m_objects; }

  private:
    Vector<SharedPtr<Object>> m_objects;
  };
}