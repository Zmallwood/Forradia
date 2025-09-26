#include "SDLDevice.hpp"
#include "Theme0/Theme0Mechanics/Configuration/GameProperties.hpp"

namespace Forradia
{
    SDLDevice::SDLDevice()
    {
        SDL_Init(SDL_INIT_EVERYTHING);

        auto flags{
            SDL_WINDOW_SHOWN |
            SDL_WINDOW_RESIZABLE |
            SDL_WINDOW_MAXIMIZED |
            SDL_WINDOW_FULLSCREEN_DESKTOP};

        m_window = std::shared_ptr<SDL_Window>(
            SDL_CreateWindow("Forradia World",
                             SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED,
                             660,
                             660,
                             flags),
            SDLDeleter());

        if (!m_window)
        {
            std::cout << "Window could not be created. SDL Error: "
                      << std::string(SDL_GetError()) << std::endl;
            return;
        }

        m_renderer = std::shared_ptr<SDL_Renderer>(
            SDL_CreateRenderer(
                m_window.get(),
                -1,
                SDL_RENDERER_ACCELERATED),
            SDLDeleter());

        if (!m_renderer)
        {
            std::cout << "Renderer could not be created. SDL Error: "
                      << std::string(SDL_GetError()) << std::endl;
            return;
        }
    }

    void SDLDevice::ClearCanvas() const
    {
        SDL_Color clearColor{
            _<GameProperties>().k_clearColor.ToSDLColor()};

        SDL_SetRenderDrawColor(
            m_renderer.get(),
            clearColor.r,
            clearColor.g,
            clearColor.b,
            255);

        SDL_RenderClear(m_renderer.get());
    }

    void SDLDevice::PresentCanvas() const
    {
        SDL_RenderPresent(m_renderer.get());
    }
}
