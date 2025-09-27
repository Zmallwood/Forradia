/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "CreateFonts.hpp"
#include "CreateFont.hpp"

namespace Forradia
{
    Map<FontSizes, SharedPtr<TTF_Font>> CreateFonts(Vector<FontSizes> fontSizes,
                                                    StringView relativeFontPath)
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