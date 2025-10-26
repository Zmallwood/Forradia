//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

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

        Size GetImageSize(int imageNameHash) const;

        bool TextTextureExists(float x, float y,
                               int uniqueID) const;

        GLuint ObtainTextTexture(float x, float y,
                                 int textHash);

      private:
        void Initialize();

        void Cleanup();

        void LoadImages();

        GLuint
        LoadSingleTexture(SharedPtr<SDL_Surface> surface);

        inline static const String k_relativeImagesPath{
            "./Resources/Images/"};

        std::map<int, GLuint> m_textures;

        std::map<int, Size> m_textureSizes;

        std::map<float,
                 std::map<float, std::map<int, GLuint>>>
            m_textTextures;
    };
}