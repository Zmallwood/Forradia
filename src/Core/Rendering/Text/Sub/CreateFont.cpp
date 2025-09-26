/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "CreateFont.hpp"

namespace Forradia
{
    std::shared_ptr<TTF_Font> CreateFont(std::string_view fontFilePath,
                                         FontSizes fontSize)
    {
        auto fontPathUnixStyle{
            Replace(fontFilePath, '\\', '/')};

        auto fontSizeN{static_cast<int>(fontSize)};

        auto newFont{
            std::shared_ptr<TTF_Font>(
                TTF_OpenFont(
                    fontPathUnixStyle.c_str(),
                    fontSizeN),
                SDLDeleter())};

        if (!newFont)
        {
            std::cout << "Error loading font.\n";

            return nullptr;
        }

        return newFont;
    }
}