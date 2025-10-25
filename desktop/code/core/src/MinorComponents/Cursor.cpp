//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "Cursor.hpp"
#include "GraphicsDevices/SDLDevice.hpp"
#include "Rendering.hpp"

namespace Forradia
{

    void Cursor::Initialize()
    {
        DisableSystemCursor();
    }

    void Cursor::DisableSystemCursor()
    {
        SDL_ShowCursor(SDL_DISABLE);
    }

    void Cursor::ResetStyleToNormal()
    {
        m_cursorStyle = CursorStyles::Normal;
    }

    void Cursor::Render()
    {
        auto mousePosition{GetNormallizedMousePosition(
            _<SDLDevice>().GetWindow())};

        auto width{k_cursorSize};

        auto height{ConvertWidthToHeight(
            k_cursorSize, _<SDLDevice>().GetWindow())};

        String cursorImage;

        switch (m_cursorStyle)
        {
        case CursorStyles::Normal:

            cursorImage = "curs_normal";

            break;

        case CursorStyles::HoveringClickableGUI:

            cursorImage = "curs_hovering_clickable_gui";

            break;
        }

        _<RenderersCollection::Image2DRenderer>().DrawImage(
            cursorImage, mousePosition.x - width / 2,
            mousePosition.y - height / 2, width, height);
    }
}