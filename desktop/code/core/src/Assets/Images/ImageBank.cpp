//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "ImageBank.hpp"

namespace Forradia
{
    void ImageBank::Initialize()
    {
        LoadImages();
    }

    void ImageBank::Cleanup()
    {
        for (auto entry : m_textures)
        {
            glDeleteTextures(1, &entry.second);
        }

        for (auto entry1 : m_textTextures)
        {
            for (auto entry2 : entry1.second)
            {
                for (auto texture : entry2.second)
                {
                    glDeleteTextures(1, &texture.second);
                }
            }
        }
    }

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

                auto texture{LoadSingleTexture(surface)};

                m_textures.insert({hash, texture});
            }
        }
    }

    GLuint ImageBank::GetTexture(int imageNameHash) const
    {
        return m_textures.at(imageNameHash);
    }

    Size ImageBank::GetImageSize(int imageNameHash) const
    {
        if (m_textureSizes.contains(imageNameHash))
        {
            return m_textureSizes.at(imageNameHash);
        }

        return {-1, -1};
    }

    GLuint ImageBank::LoadSingleTexture(
        SharedPtr<SDL_Surface> surface)
    {
        GLuint texture;

        glGenTextures(1, &texture);

        glBindTexture(GL_TEXTURE_2D, texture);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w,
                     surface->h, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, surface->pixels);

        glTexParameteri(GL_TEXTURE_2D,
                        GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,
                        GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        return texture;
    }

    bool ImageBank::TextTextureExists(float x, float y,
                                      int textHash) const
    {
        return m_textTextures.contains(x) &&
               m_textTextures.at(x).contains(y) &&
               m_textTextures.at(x).at(y).contains(
                   textHash);
    }

    GLuint ImageBank::ObtainTextTexture(float x, float y,
                                        int textHash)
    {
        if (TextTextureExists(x, y, textHash))
        {
            return m_textTextures.at(x).at(y).at(textHash);
        }

        GLuint texture;

        glGenTextures(1, &texture);

        m_textTextures[x][y][textHash] = texture;

        return texture;
    }
}