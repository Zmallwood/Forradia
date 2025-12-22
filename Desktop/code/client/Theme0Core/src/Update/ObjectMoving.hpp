/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

namespace Forradia::Theme0 {
    class Object;

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

        auto OnMouseDown(Uint8 mouseButton) -> bool;

        auto OnMouseUp(Uint8 mouseButton, int clickSpeed) -> bool;

        auto Render() const -> void;

      private:
        constexpr static float k_objectImageWidth{0.05F};
        constexpr static int k_renderIDImage{Hash("ObjectInAir")};
        std::shared_ptr<Object> m_objectInAir{};
    };
}
