/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "TextRenderer.hpp"
#include "ErrorUtilities.hpp"
#include "SDLDeleter.hpp"
#include "StringUtilities.hpp"
#include <SDL2/SDL_ttf.h>
// clang-format off
#include <GL/glew.h>
#include <GL/gl.h>
// clang-format on
namespace Forradia
{
    auto TextRenderer::initialize() -> void
    {
        TTF_Init();

        this->addFonts();
    }

    auto TextRenderer::addFonts() -> void
    {
        auto absFontPath{std::string(SDL_GetBasePath()) + k_defaultFontPath};
        auto fontPathUnixStyle{replace(absFontPath, '\\', '/')};

        // Iterate over all available font sizes.
        for (auto fontSize : {FontSizes::_20, FontSizes::_26})
        {
            auto fontSizeN{static_cast<int>(fontSize)};

            // Open the font file with the specified size.
            auto newFont{std::shared_ptr<TTF_Font>(
                TTF_OpenFont(fontPathUnixStyle.c_str(), fontSizeN), SDLDeleter())};

            if (!newFont)
            {
                throwError("Error loading font size " + std::to_string(fontSizeN) +
                           " from: " + fontPathUnixStyle);
            }

            m_fonts.insert({fontSize, newFont});
        }
    }

    auto TextRenderer::setupState() -> void
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    auto TextRenderer::restoreState() -> void
    {
        glDisable(GL_BLEND);
        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
