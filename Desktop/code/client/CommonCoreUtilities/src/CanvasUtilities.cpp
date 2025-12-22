/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "CanvasUtilities.hpp"
#include "ErrorUtilities.hpp"
#include <SDL2/SDL.h>

namespace Forradia {
    auto GetCanvasSize(const std::shared_ptr<SDL_Window> &window) -> Size {
        if (window == nullptr) {
            ThrowError("window is null");
        }
        Size canvasSize;
        SDL_GetWindowSize(window.get(), &canvasSize.width, &canvasSize.height);
        return canvasSize;
    }

    auto CalcAspectRatio(const std::shared_ptr<SDL_Window> &window) -> float {
        if (window == nullptr) {
            ThrowError("window is null");
            return 0.0F;
        }
        auto canvasSize{GetCanvasSize(window)};
        auto aspectRatio{static_cast<float>(canvasSize.width) / canvasSize.height};
        return aspectRatio;
    }

    auto ConvertWidthToHeight(float width, const std::shared_ptr<SDL_Window> &window) -> float {
        if (window == nullptr) {
            ThrowError("window is null");
            return 0.0F;
        }
        return width * CalcAspectRatio(window);
    }

    auto ConvertHeightToWidth(float height, const std::shared_ptr<SDL_Window> &window) -> float {
        if (window == nullptr) {
            ThrowError("window is null");
            return 0.0F;
        }
        return height / CalcAspectRatio(window);
    }
}
