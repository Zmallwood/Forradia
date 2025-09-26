/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

#include "Sub/FontSizes.hpp"

namespace Forradia
{
    class TextRenderer
    {
    public:
        TextRenderer();

        void DrawString(std::string_view text,
                        float x,
                        float y,
                        FontSizes fontSize = FontSizes::_20,
                        bool centerAlign = false,
                        Color textColor = Colors::wheat) const;

    private:
        void AddFonts();

        void AddFontSize(FontSizes fontSize);

        const std::string k_defaultFontPath{"./Resources/Fonts/PixeloidSans.ttf"};

        std::map<FontSizes, std::shared_ptr<TTF_Font>> m_fonts;
    };
}