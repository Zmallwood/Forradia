/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "Cursor.hpp"
#include "CanvasUtilities.hpp"
#include "Image2DRenderer.hpp"
#include "MouseUtilities.hpp"
#include "SDLDevice.hpp"
#include "Singleton.hpp"

namespace Forradia {
    auto Cursor::Initialize() -> void {
        Cursor::DisableSystemCursor();
    }

    auto Cursor::DisableSystemCursor() -> void {
        SDL_ShowCursor(SDL_DISABLE);
    }

    auto Cursor::ResetStyleToNormal() -> void {
        m_cursorStyle = CursorStyles::Normal;
    }

    auto Cursor::Render() const -> void {
        auto mousePosition{GetNormallizedMousePosition(SDLDevice::Instance().GetWindow())};

        auto width{k_cursorSize};
        auto height{ConvertWidthToHeight(k_cursorSize, SDLDevice::Instance().GetWindow())};

        std::string cursorImage;

        switch (m_cursorStyle) {
        case CursorStyles::Normal:
            cursorImage = "CursorNormal";
            break;
        case CursorStyles::HoveringClickableGUI:
            cursorImage = "CursorHoveringClickableGUI";
            break;
        case CursorStyles::HoveringCreature:
            // TODO: Add cursor image for hovering over a creature.
            cursorImage = "CursorNormal";
            break;
        }

        Image2DRenderer::Instance().DrawImageByName(
            k_renderID, cursorImage, mousePosition.x - width / 2, mousePosition.y - height / 2,
            width, height, true);
    }
}
