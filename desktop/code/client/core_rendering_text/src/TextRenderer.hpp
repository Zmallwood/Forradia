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
    /// Renders text strings to the screen using
    /// SDL_ttf and OpenGL.
    ///
    /// This class manages font loading, texture creation,
    /// and OpenGL state management for rendering text. It
    /// supports multiple font sizes and provides options
    /// for text alignment and color customization.
    ///
    class TextRenderer
    {
      public:
        ///
        /// Constructs a TextRenderer and initializes
        /// the rendering system.
        ///
        /// Initializes SDL_ttf, loads all available fonts,
        /// and prepares the renderer for use.
        ///
        TextRenderer()
        {
            this->Initialize();
        }

        ///
        /// Draws a text string at the specified
        /// position.
        ///
        /// Renders the given text string at the specified
        /// screen coordinates using the specified font
        /// size, alignment, and color. The text is rendered
        /// as a texture and cached for efficient repeated
        /// rendering.
        ///
        /// @param uniqueRenderID A unique identifier for
        /// the render operation.
        /// @param text The text string to render.
        /// @param x The x-coordinate of the text position
        /// (in normalized coordinates).
        /// @param y The y-coordinate of the text position
        /// (in normalized coordinates).
        /// @param fontSizes The font size to use for
        /// rendering (default: FontSizes::_20).
        /// @param centerAlign If true, centers the text at
        /// the specified position
        ///                    (default: false).
        /// @param forceRerender If true, forces the text to
        /// be rerendered even if it already exists.
        /// @param textColor The color to use for the text
        /// (default: WheatTransparent).
        ///
        void
        DrawString(int uniqueRenderID, StringView text,
                   float x, float y,
                   FontSizes fontSizes = FontSizes::_20,
                   bool centerAlign = false,
                   bool forceRerender = false,
                   Color textColor = Palette::GetColor<
                       Hash("WheatTransparent")>()) const;

      private:
        ///
        /// Initializes the text rendering system.
        ///
        /// Initializes SDL_ttf and loads all available
        /// fonts.
        ///
        void Initialize();

        ///
        /// Loads all available font sizes from the
        /// default font file.
        ///
        /// Iterates through all available font sizes and
        /// loads them from the default font path. Fonts are
        /// stored in the m_fonts map for later use.
        ///
        void AddFonts();

        ///
        /// Sets up OpenGL state for text rendering.
        ///
        /// Configures pixel storage alignment, enables 2D
        /// texture rendering, and sets up alpha blending
        /// for proper transparency handling.
        ///
        void SetupState() const;

        ///
        /// Restores the previous OpenGL state after
        /// text rendering.
        ///
        /// Disables blending and texture rendering, and
        /// unbinds the current texture to restore the
        /// OpenGL state to its previous condition.
        ///
        void RestoreState() const;

        ///
        /// Creates an OpenGL texture from an SDL
        /// surface.
        ///
        /// Uploads the pixel data from the SDL surface to
        /// the currently bound OpenGL texture.
        ///
        /// @param surface The SDL surface containing the
        /// text image data.
        ///
        void
        DefineTexture(SharedPtr<SDL_Surface> surface) const;

        ///
        /// Default path to the font file relative to
        /// the application base path.
        ///
        const String k_defaultFontPath{
            "./Resources/Fonts/PixeloidSans.ttf"};

        ///
        /// Map of font sizes to loaded TTF font
        /// objects.
        ///
        /// Stores all loaded fonts indexed by their
        /// FontSizes enum value for efficient lookup during
        /// rendering.
        ///
        std::map<FontSizes, SharedPtr<TTF_Font>> m_fonts;
    };
}