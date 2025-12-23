/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "FilePathUtilities.hpp"
#include "Hash.hpp"
#include "SDLDeleter.hpp"
#include "StringUtilities.hpp"
#include "TextureBank.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <filesystem>

namespace Forradia
{
    auto TextureBank::loadTextures() -> void
    {
        auto basePath{std::string(SDL_GetBasePath())};
        auto imagesPath{basePath + k_relativeImagesPath};

        if (std::filesystem::exists(imagesPath) == false)
        {
            return;
        }

        std::filesystem::recursive_directory_iterator rdi{imagesPath};

        // Iterate through the directory using the rdi.
        for (const auto &file : rdi)
        {
            auto filePath{replace(file.path().string(), '\\', '/')};

            if (getFileExtension(filePath) == "png")
            {
                auto fileName{getFileNameNoExtension(filePath)};
                auto hash{Forradia::hash(fileName)};
                auto surface{std::shared_ptr<SDL_Surface>(IMG_Load(filePath.data()), SDLDeleter())};
                auto textureID{TextureBank::loadSingleTexture(surface)};
                auto imageSize{Size{surface->w, surface->h}};

                TextureEntry newTextureEntry;
                newTextureEntry.textureID = textureID;
                newTextureEntry.dimensions = imageSize;

                m_textureEntries[hash] = newTextureEntry;
            }
        }
    }
}
