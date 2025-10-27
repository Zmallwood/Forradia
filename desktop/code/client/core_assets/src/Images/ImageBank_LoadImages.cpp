//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "ImageBank.hpp"

namespace Forradia
{
    void ImageBank::LoadImages()
    {
        auto basePath{String(SDL_GetBasePath())};

        auto imagesPath{basePath +
                        k_relativeImagesPath.data()};

        if (!std::filesystem::exists(imagesPath))
        {
            return;
        }

        std::filesystem::recursive_directory_iterator rdi{
            imagesPath};

        for (auto it : rdi)
        {
            auto filePath{
                Replace(it.path().string(), '\\', '/')};

            if (GetFileExtension(filePath) == "png")
            {
                auto fileName{
                    GetFileNameNoExtension(filePath)};

                auto hash{Forradia::Hash(fileName)};

                auto surface{SharedPtr<SDL_Surface>(
                    IMG_Load(filePath.data()),
                    SDLDeleter())};

                auto imageSize{
                    Size{surface->w, surface->h}};

                m_textureSizes.insert({hash, imageSize});

                auto texture{
                    this->LoadSingleTexture(surface)};

                m_textures.insert({hash, texture});
            }
        }
    }
}