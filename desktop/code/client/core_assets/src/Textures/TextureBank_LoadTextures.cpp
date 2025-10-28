//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "TextureBank.hpp"

namespace Forradia
{
    void TextureBank::LoadTextures()
    {
        // Take base path from SDL.

        auto basePath{String(SDL_GetBasePath())};

        // Add relative path to base path.

        auto imagesPath{basePath +
                        k_relativeImagesPath.data()};

        // Ensure the path exists to continue.

        if (!std::filesystem::exists(imagesPath))
        {
            return;
        }

        // Create a recursive directory iterator for the
        // path.

        std::filesystem::recursive_directory_iterator rdi{
            imagesPath};

        // Iterate through the directory using the rdi.

        for (auto it : rdi)
        {
            // Replace backslashes with forward slashes.

            auto filePath{
                Replace(it.path().string(), '\\', '/')};

            // Ensure the file is a png.

            if (GetFileExtension(filePath) == "png")
            {
                // Get the file name without the extension.

                auto fileName{
                    GetFileNameNoExtension(filePath)};

                // Get the hash of the file name.

                auto hash{Forradia::Hash(fileName)};

                // Load the image as a SDL surface.

                auto surface{SharedPtr<SDL_Surface>(
                    IMG_Load(filePath.data()),
                    SDLDeleter())};

                // Load the image as a texture (from the SDL
                // surface) and get its ID.

                auto textureID{
                    this->LoadSingleTexture(surface)};

                // Obtain the image dimensions.

                auto imageSize{
                    Size{surface->w, surface->h}};

                // Create a new texture entry.

                TextureEntry newTextureEntry;

                // Set the texture ID and dimensions.

                newTextureEntry.textureID = textureID;

                newTextureEntry.dimensions = imageSize;

                // Store the texture entry.

                m_textureEntries[hash] = newTextureEntry;
            }
        }
    }
}