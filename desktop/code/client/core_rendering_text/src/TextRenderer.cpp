//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "TextRenderer.hpp"

namespace Forradia
{
    void TextRenderer::Initialize()
    {
        // Initialize the SDL TTF library.

        TTF_Init();

        // Load all available fonts.

        this->AddFonts();
    }

    void TextRenderer::AddFonts()
    {
        // Construct the absolute path to the font file.

        auto absFontPath{String(SDL_GetBasePath()) +
                         k_defaultFontPath.data()};

        // Convert path once outside the loop for
        // efficiency.

        auto fontPathUnixStyle{
            Replace(absFontPath, '\\', '/')};

        // Iterate over all available font sizes.

        for (auto fontSize :
             {FontSizes::_20, FontSizes::_26})
        {
            // Convert the font size enum to an integer
            // value.

            auto fontSizeN{CInt(fontSize)};

            // Open the font file with the specified size.

            auto newFont{SharedPtr<TTF_Font>(
                TTF_OpenFont(fontPathUnixStyle.c_str(),
                             fontSizeN),
                SDLDeleter())};

            if (!newFont)
            {
                // Continue loading other fonts even if one
                // fails, and provide specific error
                // information.

                PrintLine("Error loading font size " +
                          std::to_string(fontSizeN) +
                          " from: " + fontPathUnixStyle);

                continue;
            }

            // Store the successfully loaded font in the
            // map.

            m_fonts.insert({fontSize, newFont});
        }
    }

    void TextRenderer::SetupState() const
    {
        // Set pixel storage alignment for texture data.

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        // Enable 2D texture rendering.

        glEnable(GL_TEXTURE_2D);

        // Enable alpha blending for transparency.

        glEnable(GL_BLEND);

        // Configure blend function for proper alpha
        // compositing.

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void TextRenderer::RestoreState() const
    {
        // Disable alpha blending.

        glDisable(GL_BLEND);

        // Disable 2D texture rendering.

        glDisable(GL_TEXTURE_2D);

        // Unbind the current texture.

        glBindTexture(GL_TEXTURE_2D, 0);
    }
}