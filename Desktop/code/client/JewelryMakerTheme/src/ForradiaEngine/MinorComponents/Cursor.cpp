/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "Cursor.hpp"
    
    #include "ForradiaEngine/Common/Utilities.hpp"
    #include "ForradiaEngine/Rendering/Images/Image2DRenderer.hpp"
    #include "ForradiaEngine/GraphicsDevices/SDLDevice.hpp"
// clang-format on

namespace ForradiaEngine
{
    auto Cursor::initialize() -> void
    {
        Cursor::disableSystemCursor();
    }

    auto Cursor::disableSystemCursor() -> void
    {
        SDL_ShowCursor(SDL_DISABLE);
    }

    auto Cursor::resetStyleToNormal() -> void
    {
        m_cursorStyle = CursorStyles::Normal;
    }

    auto Cursor::render() const -> void
    {
        auto mousePosition{getNormalizedMousePosition(SDLDevice::instance().getWindow())};

        auto width{k_cursorSize};
        auto height{convertWidthToHeight(k_cursorSize, SDLDevice::instance().getWindow())};

        std::string cursorImage;

        switch (m_cursorStyle)
        {
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

        Image2DRenderer::instance().drawImageByName(
            k_renderID, cursorImage, mousePosition.x - width / 2, mousePosition.y - height / 2,
            width, height, true);
    }
}
