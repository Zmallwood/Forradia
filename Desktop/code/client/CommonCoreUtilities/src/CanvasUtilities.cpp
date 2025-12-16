//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Complete.
// TODO:

#include "CanvasUtilities.hpp"
#include "Functions.hpp"

namespace Forradia {
    Size GetCanvasSize(SharedPtr<SDL_Window> window) {
        Size canvasSize;
        SDL_GetWindowSize(window.get(), &canvasSize.width, &canvasSize.height);
        return canvasSize;
    }

    float CalcAspectRatio(SharedPtr<SDL_Window> window) {
        auto canvasSize{GetCanvasSize(window)};
        auto aspectRatio{CFloat(canvasSize.width) / canvasSize.height};
        return aspectRatio;
    }

    float ConvertWidthToHeight(float width, SharedPtr<SDL_Window> window) {
        return width * CalcAspectRatio(window);
    }

    float ConvertHeightToWidth(float height, SharedPtr<SDL_Window> window) {
        return height / CalcAspectRatio(window);
    }
}