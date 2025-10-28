//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "TextureEntry.hpp"

struct SDL_Surface;

namespace Forradia
{
    class ImageBank
    {
      public:
        ImageBank()
        {
            Initialize();
        }

        ~ImageBank()
        {
            Cleanup();
        }

        GLuint GetTexture(int imageNameHash) const;

        Size GetTextureDimensions(int imageNameHash) const;

        bool TextTextureExists(float x, float y,
                               int uniqueID) const;

        GLuint ObtainTextTexture(float x, float y,
                                 int textHash);

      private:
        void Initialize();

        void Cleanup();

        void LoadTextures();

        GLuint
        LoadSingleTexture(SharedPtr<SDL_Surface> surface);

        inline static const String k_relativeImagesPath{
            "./Resources/Images/"};

        std::map<int, TextureEntry> m_textureEntries;

        std::map<float,
                 std::map<float, std::map<int, GLuint>>>
            m_textTextureIDs;
    };
}