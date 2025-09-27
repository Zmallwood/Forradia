/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "LoadSingleImage.hpp"
#include "Core/SDLDevice/SDLDevice.hpp"

namespace Forradia
{
    SharedPtr<SDL_Texture> LoadSingleImage(StringView path)
    {
        auto surface{
            std::shared_ptr<SDL_Surface>(
                IMG_Load(path.data()),
                SDLDeleter())};

        if (surface)
        {
            auto renderer{
                _<SDLDevice>().GetRenderer().get()};

            auto texture{
                std::shared_ptr<SDL_Texture>(
                    SDL_CreateTextureFromSurface(renderer,
                                                 surface.get()),
                    SDLDeleter())};

            return texture;
        }

        return nullptr;
    }
}