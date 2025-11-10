//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "ObjectIndexEntry.hpp"

namespace Forradia::Theme0
{
    class ObjectIndex
    {
      public:
        ObjectIndex();

        float GetModelScaling(int objectHash) const;

      private:
        std::map<int, ObjectIndexEntry> m_entries;
    };
}