/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "Coloring/Palette.hpp"
#include "FontSizes.hpp"
#include <unordered_map>

using TTF_Font = struct _TTF_Font;

namespace Forradia {
    /**
     * Renders text strings to the screen using SDL_ttf and OpenGL.
     */
    class TextRenderer {
      public:
        static TextRenderer &Instance() {
            static TextRenderer instance;
            return instance;
        }

        // Delete copy/move
        TextRenderer(const TextRenderer &) = delete;

        TextRenderer &operator=(const TextRenderer &) = delete;

        /**
         * Constructs a TextRenderer and initializes the rendering system.
         */
        TextRenderer() {
            // Initialize SDL TTF and load fonts.
            this->Initialize();
        }

        /**
         * Draws a text string at the specified position.
         *
         * @param uniqueRenderID A unique identifier for the render operation.
         * @param text The text string to render.
         * @param x The x-coordinate of the text position (in normalized coordinates).
         * @param y The y-coordinate of the text position (in normalized coordinates).
         * @param fontSizes The font size to use for rendering (default: FontSizes::_20).
         * @param centerAlign If true, centers the text at the specified position (default: false).
         * @param forceRerender If true, forces the text to be rerendered even if it already exists.
         * @param textColor The color to use for the text (default: WheatTransparent).
         */
        auto DrawString(int uniqueRenderID, std::string_view text, float x, float y,
                        FontSizes fontSizes = FontSizes::_20, bool centerAlign = false,
                        bool forceRerender = false,
                        Color textColor = Palette::GetColor<Hash("WheatTransparent")>()) const
            -> void;

      private:
        auto Initialize() -> void;

        auto AddFonts() -> void;

        auto SetupState() const -> void;

        auto RestoreState() const -> void;

        auto DefineTexture(std::shared_ptr<SDL_Surface> surface) const -> void;

        const std::string k_defaultFontPath{"./Resources/Fonts/PixeloidSans.ttf"};
        std::unordered_map<FontSizes, std::shared_ptr<TTF_Font>> m_fonts;
    };
}
