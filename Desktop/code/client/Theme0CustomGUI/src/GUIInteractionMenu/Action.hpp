//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace Forradia::Theme0
{
    class Action
    {
      public:
        Vector<int> groundMatches;
        Vector<int> objectMatches;
        Function<void()> action;
    };
}