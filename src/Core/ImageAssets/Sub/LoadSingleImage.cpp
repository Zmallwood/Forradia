#include "LoadSingleImage.hpp"
#include "Core/SDLDevice/SDLDevice.hpp"

namespace Forradia
{
    std::shared_ptr<SDL_Texture> LoadSingleImage(std::string_view path)
    {
        auto surface{
            std::shared_ptr<SDL_Surface>(
                IMG_Load(path.data()),
                SDLDeleter())};

        if (surface)
        {
            auto renderer{
                _<SDLDevice>().GetRenderer().get()};

            auto texture{
                std::shared_ptr<SDL_Texture>(
                    SDL_CreateTextureFromSurface(renderer,
                                                 surface.get()),
                    SDLDeleter())};

            return texture;
        }

        return nullptr;
    }
}