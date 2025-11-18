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
    ///
    /// Represents the inventory of objects for the player.
    /// TODO: Decide if should be used also for other entities.
    ///
    class PlayerObjectsInventory
    {
      public:
        PlayerObjectsInventory();

        SharedPtr<Object> GetObject(int index);

        void AddObject(int objectType);

        void AddObject(StringView objectName);

        int CountHasObject(StringView objectName);

        void RemoveObject(StringView objectName, int count = 1);

      private:
        Vector<SharedPtr<Object>> m_objects;
    };
}