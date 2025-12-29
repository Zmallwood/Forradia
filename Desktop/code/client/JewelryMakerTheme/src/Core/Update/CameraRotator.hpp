/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include <SDL2/SDL.h>
#include "ForradiaEngine/Common/Matter/Geometry.hpp"

namespace ForradiaEngine::JewelryMakerTheme
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

        /**
         *  Called when the mouse is pressed down.
         *
         *  @param mouseButton The mouse button that was pressed.
         */
        auto onMouseDown(Uint8 mouseButton) -> void;

        /**
         *  Called when the mouse is released.
         *
         *  @param mouseButton The mouse button that was released.
         */
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
