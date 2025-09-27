/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

#include "GUIComponent.hpp"

namespace Forradia
{
    class GUI : public GUIComponent
    {
    public:
        GUI()
            : GUIComponent(0.0f, 0.0f, 1.0f, 1.0f)
        {
        }
    };
}
