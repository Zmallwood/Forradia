/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "TextureBank.hpp"

    #include <filesystem>

    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    
    #include "ForradiaEngine/Common/Utilities.hpp"
    #include "ForradiaEngine/Common/General.hpp"
// clang-format on

namespace ForradiaEngine
{
    auto TextureBank::loadTextures() -> void
    {
        /* Create and validate images path */ // clang-format off
            auto basePath{std::string(SDL_GetBasePath())};
            auto imagesPath{basePath + k_relativeImagesPath};

            if (std::filesystem::exists(imagesPath) == false)
            {
                return;
            }
        // clang-format on

        std::filesystem::recursive_directory_iterator rdi{imagesPath};

        /* Iterate through the directory using the rdi */ // clang-format off
            for (const auto &file : rdi)
            {
                auto filePath{replace(file.path().string(), '\\', '/')};

                if (getFileExtension(filePath) == "png")
                {
                    auto fileName{getFileNameNoExtension(filePath)};
                    auto hash{ForradiaEngine::hash(fileName)};
                    auto surface{std::shared_ptr<SDL_Surface>(IMG_Load(filePath.data()), SDLDeleter())};
                    auto textureID{TextureBank::loadSingleTexture(surface)};
                    auto imageSize{Size{surface->w, surface->h}};

                    TextureEntry newTextureEntry;
                    newTextureEntry.textureID = textureID;
                    newTextureEntry.dimensions = imageSize;

                    m_textureEntries[hash] = newTextureEntry;
                }
            }
        // clang-format on
    }
}
