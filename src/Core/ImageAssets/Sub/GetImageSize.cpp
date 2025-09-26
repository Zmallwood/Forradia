/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

 #include "GetImageSize.hpp"

 namespace Forradia
 {
    Size GetImageSize(std::shared_ptr<SDL_Texture> texture)
    {
        Size size;

        if (texture)
        {
            SDL_QueryTexture(
                texture.get(),
                nullptr,
                nullptr,
                &size.width,
                &size.height);
        }

        return size;
    }
 }