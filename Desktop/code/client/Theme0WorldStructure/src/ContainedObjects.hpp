/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

namespace Forradia::Theme0 {
    class ContainedObjects {
      public:
        ContainedObjects(int numSlots) : m_numSlots(numSlots) {
        }

      private:
        int m_numSlots{0};
    };
}
