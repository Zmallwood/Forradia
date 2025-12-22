/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "CameraRotator.hpp"
#include "3D/Camera.hpp"
#include "SDLDevice.hpp"

namespace Forradia::Theme0
{
    auto CameraRotator::OnMouseDown(Uint8 mouseButton) -> void
    {
        if (mouseButton == SDL_BUTTON_RIGHT)
        {
            m_isRotating = true;

            m_mousePositionLastUpdate =
                GetNormallizedMousePosition(SDLDevice::Instance().GetWindow());
        }
    }

    auto CameraRotator::OnMouseUp(Uint8 mouseButton) -> void
    {
        if (mouseButton == SDL_BUTTON_RIGHT)
        {
            if (m_isRotating)
            {
                m_isRotating = false;
            }
        }
    }

    auto CameraRotator::Update() -> void
    {
        if (m_isRotating)
        {
            auto mousePosition{GetNormallizedMousePosition(SDLDevice::Instance().GetWindow())};

            auto dX{mousePosition.x - m_mousePositionLastUpdate.x};

            Camera::Instance().AddRotationDeltaSideways(dX);

            auto dY{mousePosition.y - m_mousePositionLastUpdate.y};

            Camera::Instance().AddRotationDeltaVertical(dY);
        }
    }
}
