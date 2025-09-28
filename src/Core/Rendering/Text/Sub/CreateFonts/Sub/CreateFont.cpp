/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "CreateFont.hpp"

namespace Forradia
{
    SharedPtr<TTF_Font> CreateFont(StringView fontFilePath,
                                   FontSizes fontSize)
    {
        auto fontPathUnixStyle{
            Replace(fontFilePath, '\\', '/')};

        auto fontSizeN{static_cast<int>(fontSize)};

        auto newFont{
            SharedPtr<TTF_Font>(
                TTF_OpenFont(
                    fontPathUnixStyle.c_str(),
                    fontSizeN),
                SDLDeleter())};

        if (!newFont)
        {
            PrintLine("Error loading font.");

            return nullptr;
        }

        return newFont;
    }
}