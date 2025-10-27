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

        SharedPtr<Object> GetObject(int x, int y);

      private:
        std::map<int, std::map<int, SharedPtr<Object>>>
            m_objects;
    };
}