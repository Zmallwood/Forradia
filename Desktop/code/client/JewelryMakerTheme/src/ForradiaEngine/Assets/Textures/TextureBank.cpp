/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "TextureBank.hpp"

    #include <filesystem>
    #include <ranges>

    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    
    #include "ForradiaEngine/Common/Utilities.hpp"
    #include "ForradiaEngine/Common/General.hpp"
// clang-format on

namespace ForradiaEngine
{
    /* Initialize and cleanup */ // clang-format off
        auto TextureBank::initialize() -> void
        {
            TextureBank::loadTextures();
        }

        auto TextureBank::cleanup() -> void
        {
            for (auto val : m_textureEntries | std::views::values)
            {
                glDeleteTextures(1, &val.textureID);
            }

            for (auto val : m_textTextureIDs | std::views::values)
            {
                glDeleteTextures(1, &val);
            }

            m_textureEntries.clear();
            
            m_textTextureIDs.clear();
        }
    // clang-format on

    /* Texture loading */ // clang-format off
        auto TextureBank::loadTextures() -> void
        {
            /* Create and validate images path */ // clang-format off
                auto basePath{std::string(SDL_GetBasePath())};
                auto imagesPath{basePath + k_relativeImagesPath};
                
                if (std::filesystem::exists(imagesPath) == false)
                {
                    return;
                }
            /**/

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
            /**/
        }

        auto TextureBank::loadSingleTexture(const std::shared_ptr<SDL_Surface> &surface) -> GLuint
        {
            GLuint textureID;
            glGenTextures(1, &textureID);

            glBindTexture(GL_TEXTURE_2D, textureID);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA,
                        GL_UNSIGNED_BYTE, surface->pixels);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            return textureID;
        }

    /**/ // clang-format on

    /* Texture data retrieval */ // clang-format off
        // ReSharper disable once CppMemberFunctionMayBeStatic
        auto TextureBank::getTexture(int imageNameHash) const -> GLuint
        {
            if (m_textureEntries.contains(imageNameHash))
            {
                return m_textureEntries.at(imageNameHash).textureID;
            }

            return -1;
        }

        auto TextureBank::getTextureDimensions(int imageNameHash) -> Size
        {
            if (m_textureEntries.contains(imageNameHash))
            {
                return m_textureEntries.at(imageNameHash).dimensions;
            }

            return {-1, -1};
        }

        // ReSharper disable once CppMemberFunctionMayBeStatic
        auto TextureBank::obtainTextTexture(int uniqueTextureID, GLuint &textureID) const -> bool
        {
            // Check if the text texture exists.
            if (m_textTextureIDs.contains(uniqueTextureID))
            {
                textureID = m_textTextureIDs.at(uniqueTextureID);

                return true;
            }

            // If it doesn't, create it.
            glGenTextures(1, &textureID);
            m_textTextureIDs[uniqueTextureID] = textureID;

            return false;
        }
    // clang-format on
}
