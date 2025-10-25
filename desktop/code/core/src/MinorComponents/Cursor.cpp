//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "Cursor.hpp"
#include "Rendering.hpp"
#include "SDLDevice.hpp"

namespace Forradia
{
    void Cursor::Initialize()
    {
        DisableSystemCursor();
    }

    void Cursor::DisableSystemCursor()
    {
        // Hide the default system cursor.

        SDL_ShowCursor(SDL_DISABLE);
    }

    void Cursor::ResetStyleToNormal()
    {
        // Reset the cursor style to normal style.

        m_cursorStyle = CursorStyles::Normal;
    }

    void Cursor::Render()
    {
        // Get the mouse position.

        auto mousePosition{GetNormallizedMousePosition(
            _<SDLDevice>().GetWindow())};

        // Determine cursor image dimensions.

        auto width{k_cursorSize};

        auto height{ConvertWidthToHeight(
            k_cursorSize, _<SDLDevice>().GetWindow())};

        // To hold the cursor image name.

        String cursorImage;

        // Determine the cursor image name.

        switch (m_cursorStyle)
        {
        case CursorStyles::Normal:

            cursorImage = "curs_normal";

            break;

        case CursorStyles::HoveringClickableGUI:

            cursorImage = "curs_hovering_clickable_gui";

            break;
        }

        // Draw the cursor image.

        _<RenderersCollection::Image2DRenderer>().DrawImage(
            cursorImage, mousePosition.x - width / 2,
            mousePosition.y - height / 2, width, height);
    }
}