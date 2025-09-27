/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

namespace Forradia
{
    class ImageBank
    {
    public:
        ImageBank();

        SharedPtr<SDL_Texture> GetImage(int imageNameHash) const;

        Size GetImageSize(int imageNameHash) const;

    private:
        void LoadImages();

        inline static const String k_relativeImagesPath{"./Resources/Images/"};

        Map<int, SharedPtr<SDL_Texture>> m_images;
    };
}
