#pragma once

#include "CursorStyles.hpp"

namespace Forradia
{
    class Cursor
    {
    public:
        Cursor();

        void Render();

    private:
        constexpr static float k_cursorSize {0.05f};

        CursorStyles m_cursorStyle{CursorStyles::Default};
    };
}