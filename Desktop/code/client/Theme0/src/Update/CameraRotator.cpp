//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "CameraRotator.hpp"
#include "3D/Camera.hpp"
#include "Mouse/MouseInput.hpp"
#include "SDLDevice.hpp"

namespace Forradia::Theme0::GameplayCore
{
    void CameraRotator::Update()
    {
        if (_<MouseInput>().GetRightMouseButtonRef().HasBeenFiredPickResult())
        {
            m_isRotating = true;

            m_mousePositionLastUpdate = GetNormallizedMousePosition(_<SDLDevice>().GetWindow());
        }

        if (_<MouseInput>().GetRightMouseButtonRef().HasBeenReleased())
        {
            if (m_isRotating)
            {
                _<MouseInput>().GetRightMouseButtonRef().Reset();
            }

            m_isRotating = false;
        }

        if (m_isRotating)
        {
            auto mousePosition{GetNormallizedMousePosition(_<SDLDevice>().GetWindow())};

            auto dX{mousePosition.x - m_mousePositionLastUpdate.x};

            _<Camera>().AddRotationDeltaSideways(dX);

            auto dY{mousePosition.y - m_mousePositionLastUpdate.y};

            _<Camera>().AddRotationDeltaVertical(dY);
        }
    }
}