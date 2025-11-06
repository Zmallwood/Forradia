//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "FontSizes.hpp"

namespace Forradia
{
    class TextRenderer
    {
      public:
        TextRenderer()
        {
            this->Initialize();
        }

        void
        DrawString(StringView text, float x, float y,
                   FontSizes fontSizes = FontSizes::_20,
                   bool centerAlign = false,
                   Color textColor = Palette::GetColor<
                       Hash("WheatTransparent")>()) const;

      private:
        void Initialize();

        void AddFonts();

        void SetupState() const;

        void RestoreState() const;

        void DefineTexture(SharedPtr<SDL_Surface> surface) const;

        const String k_defaultFontPath{
            "./Resources/Fonts/PixeloidSans.ttf"};

        std::map<FontSizes, SharedPtr<TTF_Font>> m_fonts;
    };
}