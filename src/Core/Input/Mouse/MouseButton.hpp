/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

namespace Forradia
{
    class MouseButton
    {
    public:
        void RegisterPress();

        void RegisterRelease();

        bool IsPressedPickResult();

    private:
        bool m_isPressed{false};
    };
}