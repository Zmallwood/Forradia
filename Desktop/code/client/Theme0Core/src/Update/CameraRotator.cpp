/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "CameraRotator.hpp"
#include "3D/Camera.hpp"
#include "MouseUtilities.hpp"
#include "SDLDevice.hpp"

namespace Forradia::Theme0
{
    auto CameraRotator::OnMouseDown(Uint8 mouseButton) -> void
    {
        if (mouseButton == SDL_BUTTON_RIGHT)
        {
            m_isRotating = true;

            m_mousePositionLastUpdate =
                GetNormalizedMousePosition(SDLDevice::Instance().GetWindow());
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

    auto CameraRotator::Update() const -> void
    {
        if (m_isRotating)
        {
            auto mousePosition{GetNormalizedMousePosition(SDLDevice::Instance().GetWindow())};

            auto deltaX{mousePosition.x - m_mousePositionLastUpdate.x};

            Camera::Instance().AddRotationDeltaSideways(deltaX);

            auto deltaY{mousePosition.y - m_mousePositionLastUpdate.y};

            Camera::Instance().AddRotationDeltaVertical(deltaY);
        }
    }
}
