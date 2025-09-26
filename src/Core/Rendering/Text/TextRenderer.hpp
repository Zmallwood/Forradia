#pragma once

#include "FontSizes.hpp"

namespace Forradia
{
    class TextRenderer
    {
        TextRenderer();

        void DrawString(std::string_view text,
                        float x,
                        float y,
                        FontSizes fontSize = FontSizes::_20,
                        bool centerAlign = false,
                        Color textColor = Colors::wheat) const;

        void AddFontSize(FontSizes fontSize);

        const std::string k_defaultFontPath{"./Resources/Fonts/PixeloidSans.ttf"};

        std::map<FontSizes, std::shared_ptr<TTF_Font>> m_fonts;
    };
}