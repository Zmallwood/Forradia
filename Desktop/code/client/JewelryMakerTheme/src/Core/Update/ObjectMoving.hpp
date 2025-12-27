/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include <memory>
#include <SDL2/SDL.h>
#include "ForradiaEngine/Common/General.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    class Object;

    class ObjectMoving
    {
      public:
        static auto instance() -> ObjectMoving &
        {
            static ObjectMoving instance;
            return instance;
        }

        ObjectMoving(const ObjectMoving &) = delete;

        auto operator=(const ObjectMoving &) -> ObjectMoving & = delete;

        ObjectMoving() = default;

        auto onMouseDown(Uint8 mouseButton) -> bool;

        auto onMouseUp(Uint8 mouseButton, int clickSpeed) -> bool;

        auto render() const -> void;

      private:
        constexpr static float k_objectImageWidth{0.05F};
        constexpr static int k_renderIDImage{hash("ObjectInAir")};
        std::shared_ptr<Object> m_objectInAir{};
    };
}
