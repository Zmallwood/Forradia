/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

namespace Forradia::Theme0 {
    class ObjectMoving {
      public:
        static ObjectMoving &Instance() {
            static ObjectMoving instance;
            return instance;
        }

        // Delete copy/move
        ObjectMoving(const ObjectMoving &) = delete;

        ObjectMoving &operator=(const ObjectMoving &) = delete;

        ObjectMoving() = default;

        auto Update() -> void;
    };
}
