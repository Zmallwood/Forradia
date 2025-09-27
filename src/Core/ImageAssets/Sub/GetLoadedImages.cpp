/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "GetLoadedImages.hpp"
#include "LoadSingleImage.hpp"

namespace Forradia
{
    Map<int, SharedPtr<SDL_Texture>> GetLoadedImages(StringView imagesPath)
    {
        std::map<int, std::shared_ptr<SDL_Texture>> imagesResult;

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

                auto hash{Hash(fileName)};

                auto image{
                    LoadSingleImage(filePath)};

                imagesResult.insert({hash, image});
            }
        }

        return imagesResult;
    }
}