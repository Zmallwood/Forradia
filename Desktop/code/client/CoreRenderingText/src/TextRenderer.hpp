/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "Coloring/Palette.hpp"
#include "FontSizes.hpp"
#include "Hash.hpp"
#include <memory>
#include <unordered_map>

struct SDL_Surface;
using TTF_Font = struct _TTF_Font;

namespace Forradia
{
    /**
        Renders text strings to the screen using SDL_ttf and OpenGL.
     */
    class TextRenderer
    {
      public:
        static auto instance() -> TextRenderer &
        {
            static TextRenderer instance;
            return instance;
        }

        // Delete copy/move
        TextRenderer(const TextRenderer &) = delete;

        auto operator=(const TextRenderer &) -> TextRenderer & = delete;

        /**
            Constructs a TextRenderer and initializes the rendering system.
         */
        TextRenderer()
        {
            // Initialize SDL TTF and load fonts.
            this->initialize();
        }

        /**
            Draws a text string at the specified position.

            @param uniqueRenderID A unique identifier for the render operation.
            @param text The text string to render.
            @param xPos The x-coordinate of the text position (in normalized coordinates).
            @param yPos The y-coordinate of the text position (in normalized coordinates).
            @param fontSizes The font size to use for rendering (default: FontSizes::_20).
            @param centerAlign If true, centers the text at the specified position (default: false).
            @param forceRerender If true, forces the text to be rerendered even if it already
           exists.
            @param textColor The color to use for the text (default: WheatTransparent).
         */
        auto drawString(int uniqueRenderID, std::string_view text, float xPos, float yPos,
                        FontSizes fontSizes = FontSizes::_20, bool centerAlign = false,
                        bool forceRerender = false,
                        Color textColor = Palette::getColor<hash("WheatTransparent")>()) const
            -> void;

      private:
        auto initialize() -> void;

        auto addFonts() -> void;

        static auto setupState() -> void;

        static auto restoreState() -> void;

        static auto defineTexture(const std::shared_ptr<SDL_Surface> &surface) -> void;

        const std::string k_defaultFontPath{"./Resources/Fonts/PixeloidSans.ttf"};
        std::unordered_map<FontSizes, std::shared_ptr<TTF_Font>> m_fonts{};
    };
}
