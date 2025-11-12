//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace Forradia::Theme0
{
    class Object;
}

namespace Forradia::Theme0::GameplayCore
{
    class ObjectsInventory
    {
      public:
        ObjectsInventory();

        SharedPtr<Object> GetObject(int index);

        void AddObject(int objectType);

        void AddObject(StringView objectName);

        int CountHasObject(StringView objectName);

        void RemoveObject(StringView objectName, int count = 1);

      private:
        Vector<SharedPtr<Object>> m_objects;
    };
}