//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace Forradia::Theme0
{
    class Object;

    class ObjectsStack
    {
      public:
        void ClearObjects();

        template<class T = Object>
        void AddObject(StringView objectTypeName);

        void RemoveObjectOfType(StringView objectTypeName);

        int GetSize() const;

        auto GetObjects() const
        {
            return m_objects;
        }

      private:
        Vector<SharedPtr<Object>> m_objects;
    };
}