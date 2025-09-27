/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

#include "Sub/CursorStyles.hpp"

namespace Forradia
{
    class Cursor
    {
    public:
        Cursor()
        {
            DisableSystemCursor();
        }

        void ResetStyleToDefault();

        void Render();

        auto SetCursorStyle(CursorStyles value)
        {
            m_cursorStyle = value;
        }

    private:
        void DisableSystemCursor();

        constexpr static float k_cursorSize{0.05f};

        CursorStyles m_cursorStyle{CursorStyles::Default};
    };
}