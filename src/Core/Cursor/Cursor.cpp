#include "Cursor.hpp"
#include "Core/Rendering/ImageRenderer.hpp"

namespace Forradia
{
    Cursor::Cursor()
    {
        SDL_ShowCursor(SDL_DISABLE);
    }

    void Cursor::Render()
    {
        auto mousePosition{GetNormalizedMousePosition()};

        auto width{k_cursorSize};
        auto height{ConvertWidthToHeight(k_cursorSize)};

        switch (m_cursorStyle)
        {
        case CursorStyles::Default:
            _<ImageRenderer>().DrawImage(
                "CursorDefault",
                mousePosition.x - width / 2,
                mousePosition.y - height / 2,
                width, height);
            break;
        }
    }
}