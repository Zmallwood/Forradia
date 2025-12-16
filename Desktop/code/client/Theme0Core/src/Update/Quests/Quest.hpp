//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#pragma once

namespace Forradia::Theme0 {
    class Quest {
      public:
        virtual void Update() = 0;

        virtual String GetStatus() const = 0;

        String name;
        String description;
        bool isCompleted{false};
    };
}