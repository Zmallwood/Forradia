/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "CreateFonts.hpp"
#include "CreateFont.hpp"

namespace Forradia
{
    std::map<FontSizes, std::shared_ptr<TTF_Font>> CreateFonts(std::vector<FontSizes> fontSizes,
                                                               std::string_view relativeFontPath)
    {
        std::map<FontSizes, std::shared_ptr<TTF_Font>> fontsResult;

        auto absoluteFontPath{
            std::string(SDL_GetBasePath()) + relativeFontPath.data()};

        for (auto fontSize : fontSizes)
        {
            auto newFont{CreateFont(absoluteFontPath, fontSize)};

            fontsResult.insert({fontSize, newFont});
        }

        return fontsResult;
    }
}