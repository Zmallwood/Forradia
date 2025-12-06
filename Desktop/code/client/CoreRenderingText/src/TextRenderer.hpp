//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "FontSizes.hpp"

namespace Forradia
{
    ///
    /// Renders text strings to the screen using SDL_ttf and OpenGL.
    ///
    class TextRenderer
    {
      public:
        ///
        /// Constructs a TextRenderer and initializes the rendering system.
        ///
        TextRenderer()
        {
            // Initialize SDL TTF and load fonts.

            this->Initialize();
        }

        ///
        /// Draws a text string at the specified
        /// position.
        ///
        /// @param uniqueRenderID A unique identifier for the render operation.
        /// @param text The text string to render.
        /// @param x The x-coordinate of the text position (in normalized coordinates).
        /// @param y The y-coordinate of the text position (in normalized coordinates).
        /// @param fontSizes The font size to use for rendering (default: FontSizes::_20).
        /// @param centerAlign If true, centers the text at the specified position (default:
        /// false).
        /// @param forceRerender If true, forces the text to be rerendered even if it already
        /// exists.
        /// @param textColor The color to use for the text (default: WheatTransparent).
        ///
        void DrawString(int uniqueRenderID, StringView text, float x, float y,
                        FontSizes fontSizes = FontSizes::_20, bool centerAlign = false,
                        bool forceRerender = false,
                        Color textColor = Palette::GetColor<Hash("WheatTransparent")>()) const;

      private:
        ///
        /// Initializes the text rendering system.
        ///
        void Initialize();

        ///
        /// Loads all available font sizes from the default font file.
        ///
        void AddFonts();

        ///
        /// Sets up OpenGL state for text rendering.
        ///
        void SetupState() const;

        ///
        /// Restores the previous OpenGL state after text rendering.
        ///
        void RestoreState() const;

        ///
        /// Creates an OpenGL texture from an SDL surface.
        ///
        /// @param surface The SDL surface containing the text image data.
        ///
        void DefineTexture(SharedPtr<SDL_Surface> surface) const;

        ///
        /// Default path to the font file relative to the application base path.
        ///
        const String k_defaultFontPath{"./Resources/Fonts/PixeloidSans.ttf"};

        std::map<FontSizes, SharedPtr<TTF_Font>>
            m_fonts; ///< Map of font sizes to loaded TTF font objects.
    };
}