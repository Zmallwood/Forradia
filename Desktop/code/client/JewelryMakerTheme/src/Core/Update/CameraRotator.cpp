/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "CameraRotator.hpp"
#include "ForradiaEngine/Common/Utilities.hpp"
#include "ForradiaEngine/Devices/SDLDevice.hpp"
#include "ForradiaEngine/Rendering/Base/3D/Camera.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    auto CameraRotator::onMouseDown(Uint8 mouseButton) -> void
    {
        if (mouseButton == SDL_BUTTON_RIGHT)
        {
            m_isRotating = true;

            m_mousePositionLastUpdate =
                getNormalizedMousePosition(SDLDevice::instance().getWindow());
        }
    }

    auto CameraRotator::onMouseUp(Uint8 mouseButton) -> void
    {
        if (mouseButton == SDL_BUTTON_RIGHT)
        {
            if (m_isRotating)
            {
                m_isRotating = false;
            }
        }
    }

    auto CameraRotator::update() const -> void
    {
        if (m_isRotating)
        {
            auto mousePosition{getNormalizedMousePosition(SDLDevice::instance().getWindow())};

            auto deltaX{mousePosition.x - m_mousePositionLastUpdate.x};

            Camera::instance().addRotationDeltaSideways(deltaX);

            auto deltaY{mousePosition.y - m_mousePositionLastUpdate.y};

            Camera::instance().addRotationDeltaVertical(deltaY);
        }
    }
}
