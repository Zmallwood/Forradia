/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "CanvasUtilities.hpp"
    #include "ErrorUtilities.hpp"
    #include <SDL2/SDL.h>
// clang-format on

namespace Forradia
{
    auto getCanvasSize(const std::shared_ptr<SDL_Window> &window) -> Size
    {
        { // Validation
            throwOnFalse(window != nullptr, "window is null");
        }

        Size canvasSize;

        SDL_GetWindowSize(window.get(), &canvasSize.width, &canvasSize.height);

        return canvasSize;
    }

    auto calcAspectRatio(const std::shared_ptr<SDL_Window> &window) -> float
    {
        { // Validation
            throwOnFalse(window != nullptr, "window is null");
        }

        auto canvasSize{getCanvasSize(window)};

        auto aspectRatio{static_cast<float>(canvasSize.width) /
                         static_cast<float>(canvasSize.height)};

        return aspectRatio;
    }

    auto convertWidthToHeight(float width, const std::shared_ptr<SDL_Window> &window) -> float
    {
        { // Validation
            throwOnFalse(window != nullptr, "window is null");
        }

        return width * calcAspectRatio(window);
    }

    auto convertHeightToWidth(float height, const std::shared_ptr<SDL_Window> &window) -> float
    {
        { // Validation
            throwOnFalse(window != nullptr, "window is null");
        }

        return height / calcAspectRatio(window);
    }
}
