/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "ImageBank.hpp"
#include "Sub/GetImageSize.hpp"
#include "Sub/GetLoadedImages.hpp"

namespace Forradia
{
    ImageBank::ImageBank()
    {
        LoadImages();
    }

    void ImageBank::LoadImages()
    {
        auto basePath{
            String(SDL_GetBasePath())};

        auto imagesPath{
            basePath + k_relativeImagesPath.data()};

        if (!std::filesystem::exists(imagesPath))
        {
            return;
        }

        m_images = GetLoadedImages(imagesPath);
    }

    SharedPtr<SDL_Texture> ImageBank::GetImage(int imageNameHash) const
    {
        if (m_images.contains(imageNameHash))
        {
            return m_images.at(imageNameHash);
        }

        return nullptr;
    }

    Size ImageBank::GetImageSize(int imageNameHash) const
    {
        if (m_images.contains(imageNameHash))
        {
            auto texture{
                m_images.at(imageNameHash)};

            return Forradia::GetImageSize(texture);
        }

        return {0, 0};
    }
}
