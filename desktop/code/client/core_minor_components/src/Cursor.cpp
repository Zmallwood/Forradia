//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "Cursor.hpp"

#include "SDLDevice.hpp"

#include "Images2D/Image2DRenderer.hpp"

namespace Forradia
{
    void Cursor::Initialize()
    {
        // Disable the default system cursor.

        this->DisableSystemCursor();
    }

    void Cursor::DisableSystemCursor()
    {
        // Hide the default system cursor using SDL.

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

            cursorImage = "CursorNormal";

            break;

        case CursorStyles::HoveringClickableGUI:

            cursorImage = "CursorHoveringClickableGUI";

            break;
        }

        // Draw the cursor image.

        _<Image2DRenderer>().DrawImageByName(
            cursorImage, mousePosition.x - width / 2,
            mousePosition.y - height / 2, width, height);
    }
}