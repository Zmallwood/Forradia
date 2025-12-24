/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "Geometry/PointF.hpp"
#include <SDL2/SDL.h>

namespace Forradia::Theme0
{
    /**
     *  Manages the rotation of the camera.
     */
    class CameraRotator
    {
      public:
        static auto instance() -> CameraRotator &
        {
            static CameraRotator instance;
            return instance;
        }

        CameraRotator(const CameraRotator &) = delete;

        auto operator=(const CameraRotator &) -> CameraRotator & = delete;

        CameraRotator() = default;

        auto onMouseDown(Uint8 mouseButton) -> void;

        auto onMouseUp(Uint8 mouseButton) -> void;

        /**
         *  Updates the camera rotation.
         */
        auto update() const -> void;

      private:
        bool m_isRotating{false};
        PointF m_mousePositionLastUpdate{-1.0F, -1.0F};
    };
}
