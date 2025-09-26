#pragma once

namespace Forradia
{
    class ImageBank
    {
    public:
        ImageBank();

        std::shared_ptr<SDL_Texture> GetImage(int imageNameHash) const;

        Size GetImageSize(int imageNameHash) const;

    private:
        void LoadImages();

        inline static const std::string k_relativeImagesPath{"./Resources/Images/"};

        std::map<int, std::shared_ptr<SDL_Texture>> m_images;
    };
}
