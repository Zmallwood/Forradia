#include "ImageBank.hpp"
#include "Core/SDLDevice/SDLDevice.hpp"

namespace Forradia
{
    ImageBank::ImageBank()
    {
        LoadImages();
    }

    void ImageBank::LoadImages()
    {
        auto basePath {
            std::string( SDL_GetBasePath() )
        };

        auto imagesPath {
            basePath + k_relativeImagesPath.data()
        };

        if (!std::filesystem::exists( imagesPath ))
        {
            return;
        }

        std::filesystem::recursive_directory_iterator rdi {
            imagesPath
        };

        for (auto it : rdi)
        {
            auto filePath {
                Replace( it.path().string(), '\\', '/' )
            };

            if (GetFileExtension( filePath ) == "png")
            {
                auto fileName {
                    GetFileNameNoExtension( filePath )
                };

                auto hash { Hash( fileName ) };

                auto image {
                    LoadSingleImage( filePath )
                };

                m_images.insert( { hash, image } );
            }
        }
    }

    std::shared_ptr<SDL_Texture> ImageBank::GetImage( int imageNameHash ) const
    {
        if (m_images.contains( imageNameHash ))
        {
            return m_images.at( imageNameHash );
        }

        return nullptr;
    }

    Size ImageBank::GetImageSize( int imageNameHash ) const
    {
        if (m_images.contains( imageNameHash ))
        {
            auto texture {
                m_images.at( imageNameHash ).get()
            };

            int width;
            int height;

            SDL_QueryTexture(
                texture,
                nullptr,
                nullptr,
                &width,
                &height
            );

            return { width, height };
        }

        return { 0, 0 };
    }

    std::shared_ptr<SDL_Texture> ImageBank::LoadSingleImage( std::string_view path )
    {
        auto surface {
            std::shared_ptr<SDL_Surface>(
                IMG_Load( path.data() ),
                SDLDeleter()
            )
        };

        if (surface)
        {
            auto renderer {
                _<SDLDevice>( ).GetRenderer().get()
            };

            auto texture {
                std::shared_ptr<SDL_Texture>(
                    SDL_CreateTextureFromSurface( renderer,
                                                surface.get() ),
                    SDLDeleter())
            };

            return texture;
        }

        return nullptr;
    }
}
